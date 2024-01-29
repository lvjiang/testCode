package main

import "fmt"

type Student struct {
	Name string
	Age int
	性别 bool
}

func main() {
	s := Student{
		Name:"lvsj",
		Age:18,
	}
	fmt.Printf("%#v", s)
}
