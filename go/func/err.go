package main

import (
	"fmt"
)

func f1() (a, b int) {
	c, b := 1, 2
	c +=1
	return
}

func main() {
	fmt.Println(f1())
	return
}
