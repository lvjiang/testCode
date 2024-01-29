package main
import "fmt"

func main (){
	var l []string
	l=nil
	fmt.Printf("l:%p\n",l)
	conv(nil)
	return
}

func conv(data interface{}) {
	if data == nil {
		fmt.Println("111111111111")
		return
	}
	fmt.Println("22222222")
}
