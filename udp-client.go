package main
import (
	"fmt"
	"net"
)
func main() {
	ip := net.ParseIP("192.168.0.100")
	//srcAddr := &net.UDPAddr{IP: net.IPv4zero, Port: 0}
	dstAddr := &net.UDPAddr{IP: ip, Port: 8888}
	conn, err := net.DialUDP("udp", nil, dstAddr)
	if err != nil {
		fmt.Println(err)
	}
	conn.Write([]byte("hello from client no.1"))
		for {
			data := make([]byte, 512)
			read, remoteAddr, err := conn.ReadFromUDP(data)
			if err != nil {
				fmt.Println("recv data error ", err)
				return
			}
			if read > 0{
				break
			}

			fmt.Printf("server addr [%v], response data len:%v [%s]\n", remoteAddr, read, string(data[:read]))
		}
		fmt.Print("finish\n")
	}