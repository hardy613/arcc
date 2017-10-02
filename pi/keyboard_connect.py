#!/usr/bin/env python3

from bluetooth import discover_devices, BluetoothSocket
import curses
import sys
import os

bluetooth_port = 4097
device_name = 'arcc ' if len(sys.argv) == 1 else sys.argv[1]

COMMAND_FORWARD = 0b00000001
COMMAND_BACKWARD = 0b00000010
COMMAND_LEFT = 0b00000100
COMMAND_RIGHT = 0b00001000


def bluetooth_connect():
    if os.environ.get('BLUETOOTH_STUB'):
        return None
    devices = discover_devices(
        duration=8, lookup_names=True, flush_cache=True,
        lookup_class=False)

    for address, name in devices:
        if name == device_name:
            socket = BluetoothSocket()
            socket.connect((address, bluetooth_port))
            return socket

    raise Exception(
        'Could not find device of name ' + device_name)


class KeyboardState:
    def __init__(self):
        self.left = False
        self.right = False
        self.forward = False
        self.backward = False

    def encode(self):
        command = 0b00000000
        steering_power = 200
        propulsion_power = 200

        if self.left:
            command |= COMMAND_LEFT
        elif self.right:
            command |= COMMAND_RIGHT
        else:
            steering_power = 0

        if self.forward:
            command |= COMMAND_FORWARD
        elif self.backward:
            command |= COMMAND_BACKWARD
        else:
            propulsion_power = 0

        return bytes([command, steering_power, propulsion_power])

    def __repr__(self):
        template = '<KeyboardState left={}, right={}, forward={}, backword={}'
        return template.format(
            self.left, self.right, self.forward, self.backward)


state = KeyboardState()
socket = bluetooth_connect()

screen = curses.initscr()
curses.noecho()
curses.cbreak()
screen.keypad(True)
screen.addstr('use arrow keys to move around (enter to exit)')

while True:
    event = screen.getch()
    screen.clear()
    if event == curses.KEY_RIGHT:
        state.right = True
        state.left = False
    if event == curses.KEY_LEFT:
        state.right = False
        state.left = True
    if event == curses.KEY_DOWN:
        state.backward = True
        state.forward = False
    if event == curses.KEY_UP:
        state.backward = False
        state.forward = True

    if event == curses.KEY_ENTER or event == -1 or event == 10 or event == 49:
        curses.nocbreak()
        screen.keypad(False)
        curses.echo()
        curses.endwin()
        if socket is not None:
            socket.close()
        break
    else:
        if socket is not None:
            socket.send(state.encode())
        screen.addstr(str(state))
