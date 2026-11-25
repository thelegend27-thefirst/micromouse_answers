import asyncio
from bleak import BleakClient, BleakScanner

DEVICE_NAME = "Micromouse"

SERVICE_UUID = "49535343-FE7D-4AE5-8FA9-9FAFD205E455"
TX_UUID = "49535343-1E4D-4BD9-BA61-23C647249616"
RX_UUID = "49535343-8841-43F4-A8D4-ECBE34729BB3"

buffer = bytearray()


def on_receive(sender, data):
    """Receive telemetry from the micromouse."""
    buffer.extend(data)

    # UART/BLE packets can contain partial lines.
    while b"\n" in buffer:
        line, _, remaining = buffer.partition(b"\n")
        buffer[:] = remaining

        message = line.decode("utf-8", errors="replace").strip()
        print(f"\nMicromouse: {message}")


async def main():
    print("Searching for Micromouse...")

    device = await BleakScanner.find_device_by_name(
        DEVICE_NAME,
        timeout=15.0
    )

    if device is None:
        print("Micromouse not found.")
        return

    async with BleakClient(device) as client:
        print("Connected!")

        # Verify that the expected BLE characteristics exist.
        tx = client.services.get_characteristic(TX_UUID)
        rx = client.services.get_characteristic(RX_UUID)

        if tx is None or rx is None:
            print("Transparent UART characteristics not found.")
            print("Available services:")
            for service in client.services:
                print(service.uuid)
                for char in service.characteristics:
                    print("  ", char.uuid, char.properties)
            return

        # Enable continuous incoming telemetry.
        await client.start_notify(tx, on_receive)
        print("Notifications enabled.")
        print("Enter a command, or type 'exit' to disconnect.")

        while client.is_connected:
            command = await asyncio.to_thread(input, "Laptop> ")

            if command.lower().strip() == "exit":
                break

            # Send a newline-terminated command to the STM32.
            data = (command + "\n").encode("utf-8")

            await client.write_gatt_char(
                rx,
                data,
                response=True
            )

        await client.stop_notify(tx)

    print("Disconnected.")


if __name__ == "__main__":
    asyncio.run(main())
