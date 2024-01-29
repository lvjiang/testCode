package main

import (
	"fmt"
	"encoding/json"
)

type Student struct {
	Name string
	Age int
}

type Bus struct {
	Sum int
	Stu []*Student
}

type Bus2 struct {
	Sum int
	Stu *[]Student
}


func main() {
	bus := Bus{Stu: make([]*Student, 2)}
	b, err := json.Marshal(bus)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(string(b))
	}

	bus2 := Bus2{Stu: &[]Student{}}
	b, err = json.Marshal(bus2)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(string(b))
	}
	return
}
