package main
import "fmt"

func printStr(str string) {
	fmt.Printf("%s, %d\n", str, len(str))
}

func main() {
	var Mac [32]byte
	Mac[0]='a'
	Mac[1]='a'
	mmm := string(Mac[:])
	printStr(mmm)
	fmt.Println(mmm,"****", len(mmm))
	Mac[2]='b'
	fmt.Println(mmm,"****", len(mmm))
	sss :="lalala"
	fmt.Println(sss,"****", len(sss))

	mac := fmt.Sprintf("%s", Mac)
	fmt.Println(mac, len(mac))
	fmt.Printf("%T##,%d\n", mac, len(mac))
	fmt.Printf("%v##\n", mac)
	fmt.Printf("%#02x%#02x%#02x##\n", Mac[0], Mac[1], Mac[2])
}
