import socket   
# import time
    
HOST_IP = "192.168.0.100"
HOST_PORT = 8888

print("Starting socket: UDP...")

socket_udp=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


print("UDP server bind @ %s:%d!" %(HOST_IP, HOST_PORT) )
host_addr = (HOST_IP, HOST_PORT)
socket_udp.bind(host_addr)

print("Receiving package...")
count = 0
addrBook = []
while count<2:
    data, (src_addr, src_port) = socket_udp.recvfrom(512)
    print("Received %s from %s: %s" %(src_addr, data))
    addr =  (src_addr, src_port)
    print("%s" %data )
    addrBook.append(addr)

socket_udp.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)
socket_udp.sendto('this is testing',(addrBook[:]))

