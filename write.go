package main

import (
	"io/ioutil"
	"fmt"
	//"os"
)

func main() {
	fn :="myfile"
s := []byte("Hello World!")
ioutil.WriteFile(fn, s, 0777)

rf, _ := ioutil.ReadFile(fn)
fmt.Printf("%s", rf)
// Hello World!
}