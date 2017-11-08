import socket

host='192.168.0.100' #host pi's ip address
port=1444 #host pi's port number

addr=(host,port)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(addr)
s.send(socket.gethostname())
print(s.recv(1024))
print 'closing socket...'
s.close()