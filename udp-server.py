import socket   
import time
    
HOST_IP = "192.168.0.100"
HOST_PORT = 8888

print("Starting socket: UDP...")
socket_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 
print("UDP server bind @ %s:%d!" %(HOST_IP, HOST_PORT) )
host_addr = (HOST_IP, HOST_PORT)
socket_udp.bind(host_addr)
 
print("Receiving package...")
while True:
    data, (src_addr, src_port) = socket_udp.recvfrom(512)  
    if len(data)>0: 
        print("Received from %s: %s" %(src_addr, data))
        time.sleep(1) 
        continue