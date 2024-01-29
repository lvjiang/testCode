package main

import (
	"context"
	"fmt"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"go.mongodb.org/mongo-driver/mongo/readpref"
	"time"
)

var Mongodb MongoUtils

type MongoUtils struct {
	Con      *mongo.Client
	Db       *mongo.Database
	Username string
	Password string
	ServerIp string
	Port     int
}

func (o *MongoUtils) OpenConn() (con *mongo.Client) {
	//connString := fmt.Sprintf("mongodb://%s:%s@%s:%d", o.Username, o.Password, o.ServerIp, o.Port)
	connString := fmt.Sprintf("mongodb://%s:%d", o.ServerIp, o.Port)
	fmt.Println(connString)
	//_, err := url.Parse(connString)
	//if err != nil {
	//	fmt.Println("url parse:", err)
	//	return
	//}

	opts := &options.ClientOptions{}
	opts.SetAuth(options.Credential{AuthMechanism: "SCRAM-SHA-1", AuthSource: "crawler", Username: "crawler", Password: "qlycrawler!#%"})
	opts.SetMaxPoolSize(100) //设置连接池大小
	opts.SetMinPoolSize(10)  //设置连接池最小值

	ctx, _ := context.WithTimeout(context.Background(), 30*time.Second)
	con, err := mongo.Connect(ctx, options.Client().ApplyURI(connString), opts)
	if err != nil {
		fmt.Println("mongo connect:", err)
		return nil
	}
	err = con.Ping(ctx, readpref.Primary())
	if err != nil {
		fmt.Println("client ping:", err)
		return nil
	}
	o.Con = con
	return con
}

func (o *MongoUtils) SetDb(db string) {
	if o.Con == nil {
		panic("连接为空...")
	}
	o.Db = o.Con.Database(db)
}

func InitMongoDb(user, password, ip string, port int, db string) {
	Mongodb.ServerIp = ip
	Mongodb.Port = port
	Mongodb.Username = user
	Mongodb.Password = password

	Mongodb.OpenConn()
	Mongodb.SetDb(db)
}

func main() {
	InitMongoDb("crawler", "qlycrawler!#%25", "112.125.88.206", 27017, "crawler")
	coll := Mongodb.Db.Collection("car_news")

	id, _ := primitive.ObjectIDFromHex("625994f058c75e814d6ade78")
	ctx, _ := context.WithTimeout(context.Background(), 30*time.Second)
	cur := coll.FindOne(ctx, bson.D{{"_id", id}},
		options.FindOne().SetProjection(bson.D{{"_id", false}}))
	result := bson.M{}
	cur.Decode(result)
	fmt.Printf("%#v", result)
	fmt.Println("lalala")
}
