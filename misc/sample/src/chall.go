package main

import (
    "fmt"
	"os"
	"io/ioutil"
	"path/filepath"
)

func printFlag() {
	ex, err := os.Executable()
    if err != nil {
        fmt.Println("Unable to get the location of the running executable.")
		panic(err)
    }
    dirPath := filepath.Dir(ex)
	
	
	content, err := ioutil.ReadFile(dirPath + "/flag.txt")
	
	if err != nil {
		fmt.Println("Unable to open flag file. Please create a flag.txt file for debugging.")
		panic(err)
	}

   fmt.Println(string(content))
}

func main() {
    var password string

    fmt.Print("Enter in the password: ")
    fmt.Scanln(&password)

    if password == "ofthenorth" {
        printFlag()
    } else {
        fmt.Println("Incorrect password... read the instructions.")
    }
}
