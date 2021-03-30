package main

import (
	"fmt"
)

func main() {
	m := make(map[string]string)

	m["name"] = "lvsj"

	print(m)
	fmt.Printf("main---%#v\n", m)

	m2 := make(map[string]string, 4)
	m3 := make(map[string]string)
	fmt.Printf("%#v\n", m2)
	fmt.Printf("%#v\n", m3)
}


func print(m map[string]string) {
	m["age"]= "28"
	fmt.Printf("func---%#v\n", m)

}
