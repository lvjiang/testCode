package main

import (
	"fmt"
	"regexp"
)

func main() {
	re, err := regexp.Compile(`^https?://[\w-.]+(:[1-9][0-9]{0,5})?([\w-./]+)?$`)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(re.Match([]byte("https://www.aaa.com:890983/index.html")))
}
