# Uniform Initialization with {}
In this lesson, we will learn about initialization with {} and how it prevents narrowing.
We'll cover the following

- Two Forms of Initialization
  - Direct Initialization
  - Copy Initialisation
- Preventing Narrowing

The initialization of variables was uniform in C++11.

## Two Forms of Initialization
> Rule: A {}-Initialization is always applicable.

### Direct Initialization
```
string str{"my String"};
```

### Copy Initialization
```
string str = {"my String"};
```

## Preventing Narrowing
The initialization with {} prohibits narrowing conversion.

Narrowing, or more precisely narrowing conversion is an implicit conversion of arithmetic values. This can lead to a less accurate result which is extremely dangerous.

The following example outlines the issue with the classical initialization for fundamental types. It doesn’t matter whether we use direct initialization or assignment.
```
#include <iostream>

int main(){

  char c1(999);     
  char c2= 999;
  std::cout << "c1: " << c1 << std::endl;
  std::cout << "c2: " << c2 << std::endl;
  
  int i1(3.14); 
  int i2= 3.14;
  std::cout << "i1: " << i1 << std::endl;
  std::cout << "i2: " << i2 << std::endl;
  
}
```

The output of the program shows that there are two warnings in the code. First, the int literal 999 does not fit into the type char. Second, the double literal does not fit into the int type.

That is not possible with {}-initialization.
```
// narrowingSolved.cpp

#include <iostream>

int main(){

  char c1{999};     
  char c2 = {999};
  std::cout << "c1: " << c1 << std::endl;
  std::cout << "c2: " << c2 << std::endl;
  
  int i1{3.14}; 
  int i2 = {3.14};
  std::cout << "i1: " << i1 << std::endl;
  std::cout << "i2: " << i2 << std::endl;

  char c3{8};     
  std::cout << "c3: " << c3 << std::endl;
}
```
There can be confusion while using different versions of GCC compilers. It makes a difference as to which compiler version we are using. With GCC 6.1 and the versions above, we get an error. With the versions below GCC 6.1, we get a warning. To generate an error rather than a warning in the versions below GCC 6.1, we use the -Werror=narrowing, flag and the program will generate an error instead. You can try this out with this compiler.

In comparison, the clang++ compiler is much more predictable than GCC.

>  Compile your program in such a way that narrowing is an error.
Look at another example below:
```
#include <iostream>
using namespace std;

int main() {
  char c3{97};     
  std::cout << "c3: " << c3 << std::endl;
}
```
In the code above, if we used the expression char c3{8}, it will be indeed not narrow since 8 fits in the type char. The same holds for char c3 = {8}.

Let’s take a look at a couple of examples in the next lesson for a better understanding of this technique.

## - Examples
Examples for using {} for uniform initialization and initializer lists.

## Example 1
```
// uniformInitialization.cpp

#include <map>
#include <vector>
#include <string>

// Initialization of a C-Array as attribute of a class
class Array{
  public:
    Array(): myData{1,2,3,4,5}{}    
  private:
    int myData[5];
};

class MyClass{			
  public: 
    int x;
    double y;
};

class MyClass2{		
  public:
    MyClass2(int fir, double sec):x{fir},y{sec} {};
  private: 
    int x;
    double y;
};

int main(){

  // Direct Initialization of a standard container
  int intArray[] = {1,2,3,4,5};   
  std::vector<int> intArray1{1,2,3,4,5};  
  std::map<std::string,int> myMap{{"Scott",1976}, {"Dijkstra",1972}};

  // Initialization of a const heap array
  const float* pData= new const float[3]{1.1,2.2,3.3};

  Array arr;

  // Defaut Initialization of a arbitrary object   
  int i{};                // i becomes 0
  std::string s{};        // s becomes ""
  std::vector<float> v{}; // v becomes an empty vector
  double d{};             // d becomes 0.0
	
  // Initializations of an arbitrary object using public attributes	
  MyClass myClass{2011,3.14};      
  MyClass myClass1 = {2011,3.14};    

  // Initializations of an arbitrary object using the constructor
  MyClass2 myClass2{2011,3.14};     
  MyClass2 myClass3 = {2011,3.14};   

}
```

## Explanation
- Firstly, the direct initialization of the C array, the std::vector, and the std::map (lines 32 - 34) is quite easy. In the case of the std::map, the inner {}-pairs are the key and value pairs.
- The next special use case is the direct initialization of a const C array on the heap (line 36). The special thing about the array arr in line 39 is that C arrays can be directly initialized in the constructor initializer (line 10).
- The default initialization in lines 42 - 45 looks quite simple. That does not sound good. Why? Wait for the next section. We directly initialize, in lines 48 and 49, the public attributes of the objects. It is also possible to call the constructor with curly braces (lines 52 and 53).

## Example 2
```
// initializerList.cpp

#include <initializer_list>
#include <iostream>
#include <string>

class MyData{
  public:

    MyData(std::string, int){
      std::cout << "MyData(std::string, int)" << std::endl;
    }

    MyData(int, int){
      std::cout << "MyData(int, int)" << std::endl;
    }

    MyData(std::initializer_list<int>){
      std::cout << "MyData(std::initializer_list<int>)" << std::endl;
    }
};

template<typename T>
void printInitializerList(std::initializer_list<T> inList){
  for (auto& e: inList) std::cout << e << " ";
}

int main(){

  std::cout << std::endl;

  // sequence constructor has a higher priority
  MyData{1, 2};

  // invoke the classical constructor explicitly
  MyData(1, 2);

  // use the classical constructor
  MyData{"dummy", 2};

  std::cout << std::endl;

  // print the initializer list of ints
  printInitializerList({1, 2, 3, 4, 5, 6, 7, 8, 9});

  std::cout << std::endl;

  // print the initializer list of strings
  printInitializerList({"Only", "for", "testing", "purpose."});

  std::cout << "\n\n";
}
```
> **Special Rule:** The {} initialization is always applicable. We must remember that if we use automatic type deduction with auto in combination with a {}-initialization, we will get an std::initializer_list in C++14.

## Explanation
- When you invoke the constructor with curly braces such as in line 33, the sequence constructor (line 18) is used first. The classical constructor in line 14 serves as a fallback, but this fallback does not work the other way around.
- When we invoke the constructor with round braces such as in line 36, the sequence constructor does no fallback for the classical constructor in line 18. The sequence constructor takes a std::initalizer_list.

>  In C++14, auto with {} always generates initializer_list.
```
auto a = {42};   // std::initializer_list<int>
auto b {42};     // std::initializer_list<int>
auto c = {1, 2}; // std::initializer_list<int>
auto d {1, 2};   // std::initializer_list<int>
```

>  With C++17, the rules are more complicated than intuitive.
```
auto a = {42};   // std::initializer_list<int>
auto b {42};     // int
auto c = {1, 2}; // std::initializer_list<int>
auto d {1, 2};   // error, too many 
```

Let’s test your understanding with an exercise in the next lesson.

## Task
Initialize the following containers:

- std::array
- std::vector
- std::set
- std::unordered_multiset

with the {-10, 5, 1, 4, 5} initializer list.
```
#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <unordered_set>

template<typename T>
void print(T arrayName){
  for (auto& e: arrayName) std::cout << e << " ";
  std::cout << std::endl;
}


int main() {
  // your code goes here
  std::array<int,5> intArray1{-10,5,1,4,5};
  print(intArray1);
  /*for(const auto& elm : intArray1 )
  {
    std::cout << elm << "   ";
  }*/
  
  std::vector<int> intArray2{-10,5,1,4,5};
  print(intArray2);
  std::set<int> intArray3 = {-10,5,1,4,5};
  print(intArray3);
  std::unordered_multiset<int> intArray4{-10,5,1,4,5};
  print(intArray4);
  std::cout << "Hello World";
  return 0;
}
```
Let’s go over the solution to this problem in the next lesson.
## Solution
```
// initializerList.cpp
#include <array>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

int main(){

  std::cout << std::endl;
  std::array<int, 5> myArray = {-10, 5, 1, 4, 5};
  for (auto i: myArray) std::cout << i << " ";
  std::cout << "\n\n";

  std::vector<int> myVector = {-10, 5, 1, 4, 5};
  for (auto i: myVector) std::cout << i << " ";
  std::cout << "\n\n";

  std::set<int> mySet = {-10, 5, 1, 4, 5};
  for (auto i: mySet) std::cout << i << " ";
  std::cout << "\n\n";

  std::unordered_multiset<int> myUnorderedMultiSet = {-10, 5, 1, 4, 5};
  for (auto i: myUnorderedMultiSet) std::cout << i << " ";
  std::cout << "\n";

  std::cout << std::endl;

}
```

## Explanation
- In line 11, an std::array, of size 5 and type integers, is created with the given data.
- In line 15, an std::vector is created, of type integers, with the given data. Integers are not inserted in numerical order.
- In line 19, an std::set is created, of type integers, with the given data. Integers are inserted in numerical order and duplicate elements (in this case 5) are not inserted in the set.
- In line 23, an std::unordered_multiset is created, of type integers, with the given data. The keys are not sorted, and duplicate keys are allowed in std::unordered_multiset.

In the next lesson, we will learn about automatic type deductions using the auto keyword.
