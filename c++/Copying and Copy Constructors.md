c++中的复制和复制器

1.基本的复制:

类和对象复制都是开辟一个新的内存空间，用于存放复制体，所以a和b两个东西本身位于两个不同的内存中，互不干扰，只是数值一样。这是c++底层为我们做的 叫做浅复制(Shallow copying)

```c++
//值复制 
{int a =2; int b;
b = a;}
//类复制
class Vector2{
    float x,y;
};
int main(){
   Vector2 a ={2,3};
   Vector2 b = a;
   std::cin<< b.x;//2
    
   //如果我们使用指针,指针变量包含的地址会被复制
   Vector2* c = {4,5};
   Vector2* d = c;
   d.x = 6;
   std::cin<< c.x;//6  c的数值随着d改变,因为二个指针指向同一片内存
}
```

浅复制用下面的例子更能清晰说明：

这里我们自己写一个简单的String类

```c++
class String
{
private:
  char *m_Buffer;      // string的字符缓冲区
  unsigned int m_Size; // 字符串长度
public:
  String(const char* string){//构造
      m_Size = strlen(string);
      m_Buffer = new char(m_Size+1);
      for(int i = 0 ; i < m_Size ; i++){
        m_Buffer[i] = string[i];
      }
      m_Buffer[m_Size] = 0;
  }
  ~String(){//destructor析构函数
    delete[] m_Buffer;
  }
  friend std::ostream& operator<<(std::ostream& stream, const String& string);
  //用到了friend关键词
};
std::ostream& operator<<(std::ostream& stream, const String& string){
  stream<< string.m_Buffer;
  return stream;
}
```

**「friend关键词，声明一个友元函数，简单来说声明后，该外部函数可以调用内部的private和public对象，但是调用非静态（static）成员变量的时候，形参要加入该类的实例」**

然后我们现在进行复制

```c++
{
String a = "sdwdasda";
String b = a;
}
```

在执行完毕后，当该作用域结束出栈时会发生程序崩溃，这是因为浅复制使得a和b的m_Buffer具有同一个地址，导致这一个地址进行了两次delete。

所以<u>如果在一个结构体或者类的实例之间进行复制，其成员如果含有指针，在浅复制的时候会出现两个指针指向一片内存，但是在delete这两个实例的时候，会对同一个地址进行两次delete，这样会直接导致崩溃，修改实例内容时也会因此导致两个实例同时更改</u>，所以我们需要**深复制（deep copying）**

深复制通过Copy Constructor实现，当然是自己手动实现。只需要在public中加入

```c++
String(const String& other)//注意形参的格式，不可更改，other的类型与类名相同
  :m_Size(other.m_Size)
  {
    //实现深复制：new一个新的空间，然后再将值复制过来
  }
```

这样可以直接进行之前的操作让b=a，这样实现的就是深复制，而不是原来的浅复制



如果你要你的类作为函数的参数时，尽量使用（const 类& 类名），这样避免了值传递导致的无用内存，（如果不想要这个函数修改传入对象的值，可以用const）