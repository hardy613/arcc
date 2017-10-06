import sys
import os
from bluetooth import discover_devices, BluetoothSocket


bluetooth_port = 4097
device_name = 'arcc' if len(sys.argv) == 1 else sys.argv[1]

COMMAND_FORWARD = 0b00000001
COMMAND_BACKWARD = 0b00000010
COMMAND_LEFT = 0b00000100
COMMAND_RIGHT = 0b00001000


class ArdiunoClient:

    def __init__(self):
        self.left = False
        self.right = False
        self.forward = False
        self.backward = False
        self.steering_power = 0
        self.propulsion_power = 0
        self._socket = None
        self._stub_bluetooth = os.environ.get('BLUETOOTH_STUB') != '1'

    def connect(self):
        if not self._stub_bluetooth:

            devices = discover_devices(
                duration=4, lookup_names=True, flush_cache=True,
                lookup_class=False)

            for address, name in devices:
                if name == device_name:
                    socket = BluetoothSocket()
                    socket.connect((address, bluetooth_port))
                    self._socket = socket

            if self._socket is None:
                raise Exception(
                    'Could not find device of name ' + device_name)

    def encode(self):
        command = 0b00000000

        if self.left:
            command |= COMMAND_LEFT
        elif self.right:
            command |= COMMAND_RIGHT
        else:
            self.steering_power = 0

        if self.forward:
            command |= COMMAND_FORWARD
        elif self.backward:
            command |= COMMAND_BACKWARD
        else:
            self.propulsion_power = 0

        return bytes([command, self.steering_power, self.propulsion_power])

    def send_state(self):
        if not self._stub_bluetooth:
            self._socket.send(self.encode())

    def close(self):
        if not self._stub_bluetooth:
            self._socket.close()

    def __repr__(self):
        template = '<ArdiunoClient left={}, right={}, forward={}, ' \
            + 'backward={}, steering_power={}, propulsion_power={}>'
        return template.format(
            self.left, self.right, self.forward, self.backward,
            self.steering_power, self.propulsion_power)
