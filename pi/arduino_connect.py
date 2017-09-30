import sys
import bluetooth

print "Looking for ScottsArduino"

all_devices = bluetooth.discover_devices(
        duration=8, lookup_names=True,
        flush_cache=True, lookup_class=False)

for addr, name in all_devices:
    try:
        if name == "ScottsArduino":
            print "Found ScottsArduino at address: %s" % addr

            sock = bluetooth.BluetoothSocket()
            
            port = 0x1001

            if sys.version < '3':
                input = raw_input
                
            print "Trying to connect"
                
            sock.connect((addr, port))
                
            print("connected. Type to send data.")
                
            while True:    
                data = input()
                if len(data) == 0:
                    break        
                sock.send(data)  
                data = sock.recv(1024)
                print "Data received:", str(data)
    
            sock.close()

    except: 
        print "Error", sys.exc_info()
