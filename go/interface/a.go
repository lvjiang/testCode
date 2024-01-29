package main
import "fmt"

func main (){
	var l *[]string
	var a interface{}
	fmt.Printf("%#v\n", a)
	a=l
	if s, ok :=a.(*[]string); ok {
		fmt.Printf("%#v\n", s)
	} else {
		fmt.Println("-----")
	}
	fmt.Printf("%#v\n", a)
	return
}
