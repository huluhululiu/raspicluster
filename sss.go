package main
import (
	"fmt"
	"net"
	"time"
)
func main() {
	go func() {
		server, _ := net.ListenPacket("udp", ":8888")
		fmt.Println("server ip:", server.LocalAddr().String(), "  ", server.LocalAddr().Network())
		_buff := make([]byte, 8192)
		for {
			_count, _addr, _ := server.ReadFrom(_buff)
			fmt.Println("upd ip:", _addr.String(), "  ", _addr.Network())
			fmt.Println("package length:", _count)
			fmt.Println("content:", string(_buff[0:_count]))
			_wc, _err_w := server.WriteTo([]byte("ok"), _addr)
			if _err_w != nil {
				panic(_err_w)
			} else {
				fmt.Println("write count:", _wc)
			}
		}
	}()
	time.Sleep(time.Second * 2)
	//_radd, _ := net.ResolveUDPAddr("udp", "127.0.0.1:8888")  更换为这个是单播,结果是正常的
	_radd, _ := net.ResolveUDPAddr("udp", "255.255.255.255:8888")
	_udp, _err_udp := net.DialUDP("udp", nil, _radd)
	if _err_udp != nil {
		panic(_err_udp)
	} else {
		_udp.SetDeadline(time.Now().Add(time.Second * 3))
		_, _err_write := _udp.Write([]byte("test"))
		if _err_write != nil {
			panic(_err_write)
		}
		_buff := make([]byte, 8192)
		_count, _err_read := _udp.Read(_buff)
		if _err_read != nil {
			panic(_err_read)
		}
		fmt.Println("read result:", string(_buff[:_count]))
	}
}