package main

import (
	"encoding/json"
	"fmt"
)

type Person struct {
	Sex int
}

func (p *Person) Print() {
	fmt.Printf("my type: %T\n", p)
	b, _ := json.Marshal(p)
	fmt.Println(string(b))

}

type Student struct {
	Person
	Number int
}

func (s *Student) Print() {
	s.Person.Print()
}

func main() {
	s := Student{Number:10}
	s.Print()
	s.Print()

	return
}
