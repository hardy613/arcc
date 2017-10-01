import cwiid
import sys
import bluetooth
import json
# connecting to the Wiimote. This allows several attempts
# as first few often fail.
print("Press 1 + 2 on your Wiimote now...")
wm = None
i = 1
while not wm:
    try:
        wm = cwiid.Wiimote()
    except RuntimeError:
        if (i > 10):
            quit()
            break
    print("Error opening wiimote connection")
    print("attempt " + str(i))
    i += 1

# set Wiimote to report button presses and accelerometer state
wm.rpt_mode = cwiid.RPT_BTN | cwiid.RPT_ACC

# turn on led to show connected
wm.led = 1

print("Connected to Wiimote, connecting to arcc")

all_devices = bluetooth.discover_devices(
        duration=8, lookup_names=True,
        flush_cache=True, lookup_class=False)

for addr, name in all_devices:
    try:
        if name == "arcc":
            print("Found arcc at address: %s" % addr)

            sock = bluetooth.BluetoothSocket()

            port = 0x1001

            print("Trying to connect")

            sock.connect((addr, port))

            print("connected. Sending data Wiimote state.")

            while True:
                data = json.dumps(wm.state["buttons"])
                if len(data) == 0:
                    break
                sock.send(data)
                data = sock.recv(1024)
                print("Data received:", str(data))

            sock.close()

    except:
        print("Error", sys.exc_info())
