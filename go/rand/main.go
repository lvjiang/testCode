package main

import(
	"time"
	"math"
	"math/rand"
	"fmt"
)

func main() {
	time.Now()
	rand.Seed(100)

	for i :=0; i < 100; i++ {
		fmt.Printf("rand=%d\n", rand.Intn(math.MaxInt32))
	}
	return
}
