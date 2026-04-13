->

一个解引用的符号

```c++
class SDW{
private:
	void print(){
	std::cout<<"sdw"<<std::endl;
	}
}
SDW s1;
SDW* ptr = &s1;

(*ptr).print();
ptr->print();//10 11行执行的内容相同
```

对结构体指针和类指针能够直接解引用 调用（public修饰）成员方法

同样这个符号也可以进行重载

我们先写一个简单的具有作用域的类
```c++
class SDW{
  private:
    int val;
  public:
    void print(){
      std::cout<<"sdw"<<std::endl; 
    }  
};
class Scoped_pointer{
  private:
    SDW* MY_PTR;
  public:
    Scoped_pointer(SDW& sdw)
    :MY_PTR(&sdw)
    {
    }
    ~Scoped_pointer(){
      delete MY_PTR;
    }
};
```

```c++
int main(){
Scoped_pointer ptr =new SDW();
}
```

当我们要通过ptr引用sdw的成员时，我们似乎需要先在ptr类里把private的成员通过get方法拿出来再用->，但实际上我们可以直接重载->，如下

```c++
SDW* operator->(){
      return MY_PTR;
}
```

这样可以直接用ptr->print();

接下来是比较抽象的用法，用来直接寻找类里面变量的字节偏移量

比如

```c++
class SDW{
private:
	float x,y,z;
};
```

对于这个类，float类型变量占据4个字节，所以x y z的字节偏移量分别为 0 4 8，在c语言中通过offsetof()求出，c++中要求这个量可以通过->得出

```c++
(int) &((SDW*)0)->x;
```

对一个任意量 转化为SDW指针，引用x，取地址再转化为int