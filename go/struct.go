package main

import "fmt"

type student struct {
	nub int
	name string
	struct {
		sex bool
		age int
	}
}


func main() {
	s := student{
	}

	fmt.Println(s)
}
