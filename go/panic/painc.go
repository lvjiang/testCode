package main

import (
	"fmt"
	"runtime/debug"
)

func main() {
	pan()
	fmt.Printf("11111111111111\n")
	fmt.Printf("22222222222222\n")
}


func pan() {
	var in interface{}
	a := "lala"
	in = a

	defer func(){
		if msg := recover(); msg!=nil {
			fmt.Printf("msg: %v\n", msg)
			fmt.Printf("stack: %s\n", debug.Stack())
		}
		fmt.Printf("-----\n")
	}()

	b:= in.(int)
	fmt.Printf("in=%#v\n", in)
	fmt.Printf("b=%#v\n", b)
	fmt.Printf("b type=%T\n", b)

}
