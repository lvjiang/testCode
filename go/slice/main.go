package main
import (
	"fmt"
	"reflect"
)


func main() {
	a := []int{0,1,2,3,4}
	b := a[2:4]
	b[0]=22
	fmt.Println(a,b,reflect.TypeOf(a))
}
