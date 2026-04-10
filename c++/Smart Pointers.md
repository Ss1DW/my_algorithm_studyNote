智能指针有这么几种

```c++
std::unique_ptr
std::shared_ptr
std::weak_ptr
```

在创建新的对象时，一般会使用new关键字，但是往往会忘记delete，smart pointers就是一种不需要delete的创建对象的方法

简单来说，smart pointer就是普通的pointer加上一层包装,用下面的类进行实验

```c++
class Entity
{
public:
  Entity()
  {
    std::cout << "entity created" << std::endl;//构造方法
  }
  ~Entity()
  {
    std::cout << "entity distroyed"<< std::endl;//摧毁方法
  }
};
```

**std::unique_ptr**

独特指针是一个scoped pointer，意味着只能在特定作用域下发挥作用，出作用域就自动调用delete

创建unique ptr

```c++
int main()
{
  {//在这里的作用域用来限制创建的e1
    std::unique_ptr<Entity> e1 = std::make_unique<Entity>(); // 调用构造函数进行构造，括号内是构造时的参数
    // 这里的e1就是创建的entity的指针，可以进行类方法的调用
    e1->Print();
  }
}//当程序运行到此行，e1自动调用delete并且执行~Entity（）破坏器
```

最好使用std自带的make_unique<>()方法，e1作用与指针相同

当我们想要复制指针的时候就会出现一些问题

![](assets/image-20260410160631287.png)

查阅源代码，发现

![image-20260410160845650](assets/image-20260410160845650.png)

对于‘=’，底层是直接禁止了这个操作，因为如果直接复制指针，当e1和e2在同时执行destructor时，会将同一片内存删除两次，导致系统崩溃（见Copying and copy constructors）.所以如果我们想要使用复制，就需要用到共享指针

**std::shared_ptr**

```c++
std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();//创建被引用（分享）的ptr
std::shared_ptr<Entity> e0;//只有sharedPtr之间才能复制
e0 = sharedEntity;
```

共享指针除了本身可以当做指针正常使用之外，还可以保证被共享指针的存活

![image-20260410165801313](assets/image-20260410165801313.png)

简单来说，若程序进行到B处，会发现没有执行sharedEntity的破坏器，因为e0依然在作用域中生效，使得sharedEntity不会自动执行delete。这件事底层原理用到了引用计数器，引用计数器在e0中被放置在单独的内存中，引用一次（e0），计数器为1，当计数器为0时才会自动执行delete

假如我们不想要让e0保护sharedEntity的存活，只是把e0作为一个引用sharedEntity里面的方法的一个途径，无所谓sharedEntity是否存活，这个时候我们需要用到弱指针（weak pointer）

**std::weak_ptr**

weak_ptr属于共享指针的变种，所以只能复制共享指针的对象,所以我们执行：

```c++
std::weak_ptr<Entity> e0;
e0= sharedEntity;
```

此时若程序进行到B位置，sharedEntity会直接自动delete。

**很多人在学习智能指针后不再使用new和delete关键字，但是这两者并非完全一样，前者更简单，后者更灵活**