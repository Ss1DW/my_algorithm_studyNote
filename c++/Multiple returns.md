## 一个函数同时输出不同类型的数据

正常的函数在c++中只能有一个返回值类型，而很多情况下我们需要一个函数就能执行功能，并返回两个以上种类类型的数据。一般的做法是，在函数形参中加入加入两个变量，来承接数据

```c++
void transFer(int a, std::string &Str_src , int &Int_src){
	//........
	Str_src = .....;
	Int_src = .....;
	return;
}
```

当然也可以构建一个struct，包含你需要的数据，这样更加直观，在使用的时候可以直接用->或 "."来获取

```c++
struct Ineed transFer(int a){
    //........
    Str_src = .....;
    Int_src = .....;
    return{Str_src,Int_src};
}
```

EZPZ