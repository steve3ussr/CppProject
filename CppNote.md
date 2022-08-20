# Cpp TODO

- enum
- 

# Cpp Hello World

``` c++
#include <iostream>
// using namespace std;
int main()
{
    printf("Hello, World!\n");
    std::cout << "hello std::" << std::endl;
    return 0;
}
```

> - endl和'\n'差不多，但是endl会flush
>
> - <>先去系统目录中找头文件，如果没有在到当前目录下找。所以像标准的头文件 stdio.h、stdlib.h 等用这个方法。
>
> - **" "** 首先在当前目录下寻找，如果找不到，再到系统目录中寻找。 这个用于 include 自定义的头文件，让系统优先使用当前目录中定义的。
>
> - 真正的开发过程中， 尽量避免使用 **using namespace std;** 等直接引入整个命名空间，否则会因为命名空间污染导致很多不必要的问题， 比如自己写的某个函数，名称正好和 **std** 中的一样， 编译器会不知道使用哪一个， 引起编译报错， 建议使用: `std::cout`
>
> - **.cpp** 文件和 **.h** 文件的区别：
>
>   cpp文件用于存放类的定义 definition，h 文件用于存放类的声明 declaration。
>
>   在头文件中声明了一个函数或者类，需要定义或者使用这个函数或者类时，需要在 cpp 文件中 include 这个头文件

# Cpp 数据类型, typedef, enum

> `sizeof(type), numeric_limits<type>::max/min`可获取下面的值

| 类型               | 位            | 范围                                                         |
| :----------------- | :------------ | :----------------------------------------------------------- |
| char               | 1 个字节      | -128 到 127 或者 0 到 255                                    |
| unsigned char      | 1 个字节      | 0 到 255                                                     |
| signed char        | 1 个字节      | -128 到 127                                                  |
| int                | 4 个字节      | -2147483648 到 2147483647                                    |
| unsigned int       | 4 个字节      | 0 到 4294967295                                              |
| signed int         | 4 个字节      | -2147483648 到 2147483647                                    |
| short int          | 2 个字节      | -32768 到 32767                                              |
| unsigned short int | 2 个字节      | 0 到 65,535                                                  |
| signed short int   | 2 个字节      | -32768 到 32767                                              |
| long int           | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| signed long int    | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| unsigned long int  | 8 个字节      | 0 到 18,446,744,073,709,551,615                              |
| float              | 4 个字节      | 精度型占4个字节（32位）内存空间，+/- 3.4e +/- 38 (~7 个数字) |
| double             | 8 个字节      | 双精度型占8 个字节（64位）内存空间，+/- 1.7e +/- 308 (~15 个数字) |
| long double        | 16 个字节     | 长双精度型 16 个字节（128位）内存空间，可提供18-19位有效数字。 |
| wchar_t            | 2 或 4 个字节 | 1 个宽字符                                                   |

---

可以自定义类型的别名，如`typedef int zsa; zsa a = 1;`

> 关键字 typedef 在编译阶段有效，由于是在编译阶段，因此 typedef 有类型检查的功能，有自己的作用域。
>
> \#define 则是宏定义，发生在预处理阶段，也就是编译之前，它只进行简单而机械的字符串替换，而不进行任何检查。没有自己的作用域





# Cpp 常量

字符串分行：

``` c++
string a = "htrg \
           awd";
```

> C++的字符串：std::string
>
> C的字符串：char *a = "e2131e"

# Cpp 函数，lambda

## Call Method

- 传值；
- 指针调用：传入地址给形参；`void func(int *a, int *b)`
- **引用调用**：`void func(int &a, int &b)`

``` c++
# include <stdio.h>

void swapVal(int a, int b) {
    int tmp = a;
    a = b;
    b = a;
    return;
}

void swapPnt(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void swapRef(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
    return;
}

int main() {
    int x = 114; 
    int y = 514;

    swapVal(x, y);
    printf("x = %d, y = %d\n", x, y);

    swapPnt(&x, &y);
    printf("x = %d, y = %d\n", x, y);

    swapRef(x, y);
    printf("x = %d, y = %d\n", x, y);
    return 0;
}
```

## LAMBDA

创建一个函数对象。

示例：`auto funcName = [](intsa, int b){return a+b;};`

完整表达式的组成：

``` c++
[ capture-list ] ( params ) mutable(optional) exception(optional) attribute(optional) -> return(optional) { body } 
```

- params：和普通函数一样；
- mutable：**默认按值捕获的类型是 const 的， 要修改需要加这个关键字**
- exception
- attribute
- return：可省略，会自动推导
- body：具体逻辑
- 捕获列表：在Lambda表达式内可以访问当前作用域的变量
  - `[]`什么都不捕获
  - `[a]`传值
  - `[&b]`引用
  - `[&]`按值捕获可见范围内的所有局部变量（不建议）
  - `[=]`按引用捕获可见范围内的所有局部变量（不建议）
- 在成员函数中的 Lambda 表达式可以捕获当前对象的 this 指针，让 Lambda 表达式拥有和当前类成员同样的访问权限，可以修改类的成员变量，使用类的成员函数：this 指针只能按值捕获 `[this]` ，不能按引用捕获 `[&this]` 。





# Cpp数字，随机数，数学运算

## 数学计算

> `#include <cmath>`

| 序号 | 函数 & 描述                                                  |
| :--- | :----------------------------------------------------------- |
| 1    | **double cos(double);** 该函数返回弧度角（double 型）的余弦。 |
| 2    | **double sin(double);** 该函数返回弧度角（double 型）的正弦。 |
| 3    | **double tan(double);** 该函数返回弧度角（double 型）的正切。 |
| 4    | **double log(double);** 该函数返回参数的自然对数。           |
| 5    | **double pow(double, double);** 假设第一个参数为 x，第二个参数为 y，则该函数返回 x 的 y 次方。 |
| 6    | **double hypot(double, double);** 该函数返回两个参数的平方总和的平方根，也就是说，参数为一个直角三角形的两个直角边，函数会返回斜边的长度。 |
| 7    | **double sqrt(double);** 该函数返回参数的平方根。            |
| 8    | **int abs(int);** 该函数返回整数的绝对值。                   |
| 9    | **double fabs(double);** 该函数返回任意一个浮点数的绝对值。  |
| 10   | **double floor(double);** 该函数返回一个小于或等于传入参数的最大整数。 |

## 随机数

设置种子：`#incliude <ctime>; srand((unsigned)time(NULL))；`

- time() 不需要传入参数，返回时间戳
- (unsigned)，将`time_t`转化为`unsigned`

生成随机数：`rand()`返回0~32767（随系统变化）的数字



# Cpp 数组

声明：`type NAME[size];`

定义：`int lst[] = {1, 1, 4, 5, 1, 4};`自动生成长度为6的数组，当然也可以手动定义`lst[6]`

## 二维数组

声明`int lst[4][3];`定义一个4*3的二维数组

初始化可以有两种：

``` c++
int a[3][4] = {  
 {0, 1, 2, 3} ,   /*  初始化索引号为 0 的行 */
 {4, 5, 6, 7} ,   /*  初始化索引号为 1 的行 */
 {8, 9, 10, 11}   /*  初始化索引号为 2 的行 */
};

int a[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};
```

![](https://www.runoob.com/wp-content/uploads/2014/09/two_dimensional_arrays.jpg)

## 数组指针

数组标识符可以直接当指针使用。

``` c++
#include <stdio.h>

int main() {
    int lst[6] = {1, 1, 4, 5, 1, 4};
    //int *p = lst;
    printf("%d\n", *(lst+3));  // lst[3] == 5
    return 0;
}
```

如果是二维数组：

``` c++
int main() {
    int lst[3][2] = {1, 1, 4, 5, 1, 4};
    //int *p = lst;
    printf("%d\n", *(lst[0]+1)); // 
    return 0;
}
```

`lst+1`是`lst[1]`的指针

可以改lst对应的值，但是不能更改lst这个指针指向的地址。

## 传递数组至函数

> 就函数而言，数组的长度是无关紧要的，因为 C++ 不会对形式参数执行边界检查。

1. `retType name(elementType *arg);`
2. `retType name(elementType arg[size]);`
3. `retType name(elementType arg[]);`

以上三种方法都一样，因为编译器都会把形参作为一个指针。



## 从函数返回数组

只能返回一个指针：`int * func(){return pnt;};`

**C++ 不支持在函数外返回局部变量的地址，除非定义局部变量为 static 变量，因为return后释放栈上空间了。**

# Cpp 字符串

> `\0`为终止符，NULL

`char name[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', '\0'};`

`char name[] = "abcdefg";`

以上两种都很C。

| 序号 | 函数 & 目的                                                  |
| :--- | :----------------------------------------------------------- |
| 1    | **strcpy(s1, s2);** 复制字符串 s2 到字符串 s1。              |
| 2    | **strcat(s1, s2);** 连接字符串 s2 到字符串 s1 的末尾。连接字符串也可以用 **+** 号，例如: `string str1 = "runoob"; string str2 = "google"; string str = str1 + str2;` |
| 3    | **strlen(s1);** 返回字符串 s1 的长度。                       |
| 4    | **strcmp(s1, s2);** 如果 s1 和 s2 是相同的，则返回 0；如果 s1<s2 则返回值小于 0；如果 s1>s2 则返回值大于 0。 |
| 5    | **strchr(s1, ch);** 返回一个指针，指向字符串 s1 中字符 ch 的第一次出现的位置。 |
| 6    | **strstr(s1, s2);** 返回一个指针，指向字符串 s1 中字符串 s2 的第一次出现的位置。 |

---

C++提供了`string`类：`string a = "eewfrg";`

string类提供了一系列针对字符串的操作，比如：

1. append() -- 在字符串的末尾添加字符

2. find() -- 在字符串中查找字符串
3.  insert() -- 插入字符
4. length() -- 返回字符串的长度
5. replace() -- 替换字符串
6. substr() -- 返回某个子字符串

# Cpp 引用

> 变量的别名
>
> 类似指针，但是是隐式的

## 声明

- 必须声明时定义；
- 不存在NULL引用，必须指向一个合法的地址。
- 作用和`int const *p = a`差不多

## 把引用作为参数

就和python里的引用一样，只不过在c++所有都是mutable的。

比如定义一个交换函数，只要我在函数声明里写了引用类型，就可以正常交换（不用考虑什么取地址取内容）。

## 把引用作为返回值

和返回指针一样，返回时要看作用域。

1. 不能返回局部变量的引用。主要原因是局部变量会在函数返回后被销毁，因此被返回的引用就成为了"无所指"的引用，程序会进入未知状态。
2. 不能返回函数内部new分配的内存的引用。虽然不存在局部变量的被动销毁问题，可对于这种情况（返回函数内部new分配内存的引用），又面临其它尴尬局面。例如，被函数返回的引用只是作为一 个临时变量出现，而没有被赋予一个实际的变量，那么这个引用所指向的空间（由new分配）就无法释放，造成memory leak。
3. 可以返回类成员的引用，但最好是const。主要原因是当对象的属性是与某种业务规则（business rule）相关联的时候，其赋值常常与某些其它属性或者对象的状态有关，因此有必要将赋值操作封装在一个业务规则当中。如果其它对象可以获得该属性的非常 量引用（或指针），那么对该属性的单纯赋值就会破坏业务规则的完整性。







