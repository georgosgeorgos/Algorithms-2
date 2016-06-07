Differences between C++, Java, Python
    ```c++
    ```
    ```java
    ```
    ```python
    ```
//----------------------------------------------------------------------------------------------------------------------------------
Classes
    ```c++
    public ClassName : BaseClass {
     public:
      ClassName();
    };
    ```
    ```java
    public ClassName extends ParentClass {
    };
    ```
    ```python
    ```
//----------------------------------------
Comments
    ```c++
    //
    /* */
    ```
    ```java
    //
    /* */
    /** */
    ```
    ```python
    #
    ```
//----------------------------------------
Printing
    ```c++
        cout << "Hello" << endl;
    ```
    ```java
        System.out.println("Hello");
    ```
    ```python
      print "Hello"
    ```
//----------------------------------------
Generic Programming
    ```c++
    Template<typename T>
    void funcName(T& a);
    ```
    ```java
    void funcName(Object a); // every class in Java automatically extends Object
    ```
    ```python
    ```
//----------------------------------------------------------------------------------------------------------------------------------
Style
//----------------------------------------------------------------------------------------------------------------------------------
Getters
    ```c++
    int attribute_name() {
      return this->attribute_name_; // has trailing '_' for member functions
    }
    ```
    ```java
    int getAttributeName() {
      return this.attributeName;
    }
    ```
    ```python
    ```
//----------------------------------------
Variable Names
    ```c++
      int a_variable_name;
    ```
    ```java
      int aVariableName;
    ```
    ```python
      aVariableName;
    ```
//----------------------------------------
