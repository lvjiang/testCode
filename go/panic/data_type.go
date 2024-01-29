package main

import (
	"fmt"
)

func main() {
	var in interface{}
	a := "lala"
	in = a

	defer func(){
		if msg := recover(); msg!=nil {
			fmt.Printf("msg: %#v\n", msg)
		}
		fmt.Printf("-----\n")
	}()

	b:= in.(int)
	fmt.Printf("in=%#v\n", in)
	fmt.Printf("b=%#v\n", b)
	fmt.Printf("b type=%T\n", b)
}

