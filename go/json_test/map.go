package main

import (
	"fmt"
	"encoding/json"
)

func main() {
	m := make(map[string]interface{})
//	m["name"] = "lvsj"
//	m["age"] = 18
	b, err := json.Marshal(m)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(string(b))
	}

	return
}
