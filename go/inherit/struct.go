package main

import "fmt"

type Person struct {
	Sex int
}

func (p *Person) Print() {
	fmt.Printf("my type: %T\n", p)
}

type student struct {
	Person
	Number int
}

func main() {
	s := student{}
	s.Print()

	return
}
