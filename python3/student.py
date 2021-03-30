#!/usr/bin/python3

class Student:
    def __init__(self,name, age):
        self.__name = name
        self.__age = age
        self._sex = 1
    
    def show(self):
        print(self.__name, self.__age)

def main():
    s1 = Student('lvshuaijiang', 18)
    s1.show()
    print(dir(s1))
    print(s1._Student__age)

if __name__ == '__main__':
    main()

