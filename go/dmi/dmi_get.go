package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

type DMI struct {
	BiosDate    string
	BiosVendor  string
	BiosVersion string

	BoardAssetTag string
	BoardName     string
	BoardSerial   string
	BoardVendor   string
	BoardVersion  string

	ChassisAssetTag string
	ChassisSerial   string
	ChassisType     string
	ChassisVendor   string
	ChassisVersion  string

	ProductName    string
	ProductSerial  string
	ProductUuid    string
	ProductVersion string

	Modalias  string
	SysVendor string
	Uevent    string
}

var SysinfoDmi DMI

func init() {
	//bios
	SysinfoDmi.BiosDate = getStringFromFile("/sys/class/dmi/id/bios_date")
	SysinfoDmi.BiosVendor = getStringFromFile("/sys/class/dmi/id/bios_vendor")
	SysinfoDmi.BiosVersion = getStringFromFile("/sys/class/dmi/id/bios_version")
	//board
	SysinfoDmi.BoardAssetTag = getStringFromFile("/sys/class/dmi/id/board_asset_tag")
	SysinfoDmi.BoardName = getStringFromFile("/sys/class/dmi/id/board_name")
	SysinfoDmi.BoardSerial = getStringFromFile("/sys/class/dmi/id/board_serial")
	SysinfoDmi.BoardVendor = getStringFromFile("/sys/class/dmi/id/board_vendor")
	SysinfoDmi.BoardVersion = getStringFromFile("/sys/class/dmi/id/board_version")
	//chassis
	SysinfoDmi.ChassisAssetTag = getStringFromFile("/sys/class/dmi/id/chassis_asset_tag")
	SysinfoDmi.ChassisSerial = getStringFromFile("/sys/class/dmi/id/chassis_serial")
	SysinfoDmi.ChassisType = getStringFromFile("/sys/class/dmi/id/chassis_type")
	SysinfoDmi.ChassisVendor = getStringFromFile("/sys/class/dmi/id/chassis_vendor")
	SysinfoDmi.ChassisVersion = getStringFromFile("/sys/class/dmi/id/chassis_version")

	SysinfoDmi.ProductName = getStringFromFile("/sys/class/dmi/id/product_name")
	SysinfoDmi.ProductSerial = getStringFromFile("/sys/class/dmi/id/product_serial")
	SysinfoDmi.ProductUuid = getStringFromFile("/sys/class/dmi/id/product_uuid")
	SysinfoDmi.ProductVersion = getStringFromFile("/sys/class/dmi/id/product_version")

	SysinfoDmi.Modalias = getStringFromFile("/sys/class/dmi/id/modalias")
	SysinfoDmi.SysVendor = getStringFromFile("/sys/class/dmi/id/sys_vendor")
	SysinfoDmi.Uevent = getStringFromFile("/sys/class/dmi/id/uevent")

}

func getStringFromFile(path string) string {
	//读取文件全部内容
	b, err := ioutil.ReadFile(path)
	if err != nil {
		return err.Error()
	}
	return strings.Replace(string(b), "\n", "", -1)
}

func main() {
	fmt.Println("#############bios info#############")
	fmt.Println("bios_date:", SysinfoDmi.BiosDate)
	fmt.Println("bios_vend:", SysinfoDmi.BiosVendor)
	fmt.Println("bios_vers:", SysinfoDmi.BiosVersion)
	fmt.Println("#############board info############")
	fmt.Println("board_asset_tag:", SysinfoDmi.BoardAssetTag)
	fmt.Println("board_name     :", SysinfoDmi.BoardName)
	fmt.Println("board_serial   :", SysinfoDmi.BoardSerial)
	fmt.Println("board_vendor   :", SysinfoDmi.BoardVendor)
	fmt.Println("board_version  :", SysinfoDmi.BoardVersion)

	fmt.Println("#############chassis info############")
	fmt.Println("chassis_asset_tag:", SysinfoDmi.ChassisAssetTag)
	fmt.Println("chassis_type     :", SysinfoDmi.ChassisType)
	fmt.Println("chassis_serial   :", SysinfoDmi.ChassisSerial)
	fmt.Println("chassis_vendor   :", SysinfoDmi.ChassisVendor)
	fmt.Println("chassis_version  :", SysinfoDmi.ChassisVersion)

	fmt.Println("#############product info############")
	fmt.Println("product_name   :", SysinfoDmi.ProductName)
	fmt.Println("product_serial :", SysinfoDmi.ProductSerial)
	fmt.Println("product_uuid   :", SysinfoDmi.ProductUuid)
	fmt.Println("product_version:", SysinfoDmi.ProductVersion)

	fmt.Println("#############other   info############")
	fmt.Println("Modalias :", SysinfoDmi.Modalias)
	fmt.Println("SysVendor:", SysinfoDmi.SysVendor)
	fmt.Println("Uevent   :", SysinfoDmi.Uevent)
	fmt.Println("bay")

	// fmt.Printf("%+v\n", SysinfoDmi)
}
