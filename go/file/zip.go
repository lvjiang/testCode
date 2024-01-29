package main

import (
	"os"
	"io"
	"fmt"
//	"errors"
	"archive/zip"
	"path/filepath"
//	"strings"
)


// srcFile could be a single file or a directory
func Zip(srcFile string, destZip string) error {
	zipfile, err := os.Create(destZip)
	if err != nil {
		return err
	}
	defer zipfile.Close()

	archive := zip.NewWriter(zipfile)
	defer archive.Close()

	filepath.Walk(srcFile, func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}

		header, err := zip.FileInfoHeader(info)
		if err != nil {
			return err
		}


		//header.Name = strings.TrimPrefix(path, filepath.Dir(srcFile))
		header.Name, _ = filepath.Rel(filepath.Dir(srcFile), path)
		header.Method = zip.Deflate

		writer, err := archive.CreateHeader(header)
		if err != nil {
			return err
		}

		if ! info.IsDir() {
			file, err := os.Open(path)
			if err != nil {
				return err
			}
			defer file.Close()
			_, err = io.Copy(writer, file)
		}
		return err
	})

	return err
}


func main() {
	root := "/home/lvsj/study/testCode/go"

	filepath.Walk(root, func(path string, info os.FileInfo, err error) error {
//		fmt.Println(path)
//		fmt.Println(strings.TrimPrefix(path, filepath.Dir(root)))
		fmt.Println(filepath.Rel(filepath.Dir(root), path))
		return nil
	})
	//fmt.Println(filepath.Rel("/home/lvsj/study/testCode/go", "/home/lvsj/study/testCode/go/ee"))
	Zip(root, "/home/lvsj/tttt8.zip")
}
