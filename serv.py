import socket, traceback

host = '192.168.0.100'
#  Bind to all interfaces
#host = ''
port = 8888

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
s.bind((host, port))
count=0
addrbook = []
while count<7:
     message, address = s.recvfrom(8192)
     print "Got data from", address# Acknowledge it.
     addrbook.append(address)
     count+=1

i=0
while i<10:
    for addr in addrbook:
        s.sendto("synchrrrrr", addr)
    i+=1

    # except (KeyboardInterrupt, SystemExit):
    #     raise
    # except:
    #     traceback.print_exc()

