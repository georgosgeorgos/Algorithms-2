/* 
Table of Contents
0. Design Principles: SOLID 
//-------------------------------
A) Creational Design Pattern
//-------------------------------
1. Singleton Design Pattern
    - Only 1 object of a particular class 
    - e.g. Global Counter, Logging, Accessing shared resource
2. Factory Design Pattern
    - To create random child class objects in a game. A 'factory' that returns random objects created 
3. Builder Design Pattern
    - When Object construction is complicated, takes a long time, has too many variables to construct 
        and when you won't know all variables at once. 
    - You can construct each variable step by step
    - You can construct the objects differently using different classes
4. Prototype Design Pattern
    - When want to create a clone of an object to 'prototype' with it first before reassigning as original
    - e.g. Bank Account transactions 
//-------------------------------
B) Behavioral Design Pattern
//-------------------------------
1. Strategy Design Pattern 
    - Separate method definition from classes
    - This way, each child class can have their own method definition of a specific interface 
    - Application: Sorting (MergeSort may work better in some cases, QuickSort in other cases)
2. Visitor Design Pattern
    - To add methods to different classes without modifying those classes (honors open-closed principle)
    - Uses double dispatch => Operation depends on: 2 dynamic classes 
    -                          2 receivers are: The type of visitor class and the type element it visits (visitable)
3. Observer Design Pattern
    - Subscriber and Publisher
    - All subscribers are notified whenever a publisher makes a change
4. Template Method Design Pattern
    - TemplateMethod define in mainInterface is how the method structure is gonna work
    - It calls a bunch of abstract submethods that are defined differently in different subclasses
    - Think of template implementation in C++ that allows you to customize the datatypes. 
    - For this, you have a template methods where you can customize the methods inside that template method
    - You can customize local variables by defining abstract methods that returns different local variables
5. Chain Of Responsibility Design Pattern
    - Basically, a request comes to a linked list of objects, 
    - each object take turns to see if it is able to handle the request. 
    - If it does not, it sends the request to the next node in the list
    - If it is, it will handle it. After that, it can either:
        - i) continue to send the request to next node 
        - ii) end the request as it is handled
6. State Design Pattern
    - To allow an objects behavior to vary based on its state during runtime without too many conditional statements
    - All state specific behavior is in a ConcreteState class, this ease maintenance such as adding a new state 
    - Do not rely on current state based on a variable in the Context class, doing so will require lots of conditional statements in that one class
    - Decentralization of State Classes => Each ConcreteState defines which other Concrete State it transitions to. 
    -      => Advantage: Easy to maintain 
    -      => Disadvantage: A coupling between ConcreteStates, each state must know of each other's existence
7. Memento Design Pattern
    - To restore an object to its previous state after applying a temporary change (moment)
8. Mediator Design Pattern 
    - To implement communication between objects
    - Application: Control Tower for planes, Router for internet connection between different devices
9. Command Design Pattern
    - To be able to queue a set of commands
    - To be ablt to keep track of commands executed
    - To encapsulate a set of methods that are executed in order for a command to execute
    - Application: Client-Server Interface, where commands must be queued and sent over the server to execute an inner method. 
10. Interpreter Design Pattern
    - To handle parsing of languages
    - Convert from one data representation to another
//-------------------------------
C) Structural Design Pattern
//-------------------------------
1. Decorator Design Pattern 
    - To be able to extend functionality inheritance by creating each other recursively, passing in a variable that grows between creations
    e.g. A PlainPizza that you can recursively add in different toppings which adds to the cost
2. Flyweight Design Pattern
    - To save space by sharing data 
3. Adapter Design Pattern
    - To adapt an existing interface (Target Interface) with a new interface
    - Create an adapter class that maps all existing methods to the new methods 
        that should be called instead
4. Proxy Design Pattern
    - Interface for (expensive, remote) objects
5. Composite Design Pattern
    - Allows a client on running methods on both single objects and composite objects (composed of many single objects and/or composite objects) the same way
    - Component Interface => Interface for all objects including composite objects. 
                             Allows accessing components recursively
    - Primitive/Leaf => Represent end points of the composition
    - Composite => Represent a component that may have children
    - note: Both primitive and composite needs to be handled differently, but on Component Interface, they are called the same
    - Application: e.g. Computer Graphics project where you multiply the matrix recursively along the tree. 
//-------------------------------
D) Concurrency Design Pattern
//-------------------------------
- Always set thread pools for anything that deals with (database, FileIO)
//-------------------------------
TODO:
. Abstract Factory Design Pattern
. Facade Design Pattern
    - Simplify Interface
. Iterator Design Pattern
. Reference Counting Pointer Garbage Collection Class Wrapper Automation (Bloomberg Interview)
        - using Proxy Design Pattern  and Flyweight Pattern

How to design TinyURL (url shorterner) 

Twitter is real-time and back and forth conversation and Google is not. Therefore, different problems with both companies. 
Database Sharding



Give all anagrams of a word, given dictionary. 
Sort all words in dictionary with mapping to original, 
     then can just hash from sorted to all anagrams 
     Long pre-computation but short actual look-up
*/ 
//---------------------------------------------------------------------------------------------------------------------------------
// 0 Design Principles: SOLID 
//-------------------------------
// SOLID => Guidelines on Design Patterns to create maintainable and extensible software
// i) Single Responsibility Principle
//      - Every class has a single responsibility
// ii) Open/Closd Principle
//      - Software entities should be open for extension but closed for modification
//      - No modifying existing classes, but can create subclasses of existing classes
// iii) Liskov Substitution Principle
//      - If B is a child of A, we should be able to substitute all A with B in code without breaking it
// iv) Interface Segregation Principle
//      - Class should only implement interface if it uses all its methods
//      - Many small specific interface > Few large interfaces
// v) Dependency Inversion Principle
//      - Design Top Level Down
//      - Any changes to bottom level classes will not affect top level classes
//      - Introduce abstraction layer between classes to handle compatibility for any changes in any level.
// - Avoid duplicated code
// - Keep class changes from forcing other class changes
// - don't add methods that are not used by all subclasses
// Types of Design Patterns: 
// a) Creational Design Pattern 
//      - Singleton Design Pattern
//      - Factory Design Pattern
//      - Builder Design Pattern
//      - Prototype Design Pattern
// b) Behavioral Design Pattern 
//      - Strategy Design Pattern
//      - Visitor Design Pattern
//      - Observer Design Pattern
//      - Template Method Design Pattern
//      - Chain Of Responsibility Design Pattern
//      - State Design Pattern
//      - Memento Design Pattern
//      - Mediator Design Pattern
//      - Command Design Pattern
//      - Interpreter Design Pattern
//      - Iterator Design Pattern
// c) Structural Design Pattern 
//      - Decorator Design Pattern
//      - Flyweight Design Pattern
//      - Adapter Design Pattern
//      - Proxy Design Pattern => Interface for high time/space complexity objects, to get them only when needed
//      - Composite Design Pattern
//      - Facade Design Pattern => Interface for complicated implementation objects
//      - Bridge Design Pattern
/*
What are the differences between Interface and Abstract class?
Abstract Class	Interfaces
An abstract class can provide complete, default code and/or just the details that have to be overridden.	An interface cannot provide any code at all,just the signature.
In case of abstract class, a class may extend only one abstract class.	A Class may implement several interfaces.
An abstract class can have non-abstract methods.	All methods of an Interface are abstract.
An abstract class can have instance variables.	An Interface cannot have instance variables.
An abstract class can have any visibility: public, private, protected.	An Interface visibility must be public (or) none.
If we add a new method to an abstract class then we have the option of providing default implementation and therefore all the existing code might work properly.	If we add a new method to an Interface then we have to track down all the implementations of the interface and define implementation for the new method.
An abstract class can contain constructors .	An Interface cannot contain constructors .
Abstract classes are fast.	Interfaces are slow as it requires extra indirection to find corresponding method in the actual class.
*/
//Interview Notes:
/*
0. DON't JUMP TO SOLVING THE PROBLEM RIGHT AWAY
1. Understand how product will be used
    - Target Audience
    - How will it scale? 
    - What should the end user experience? 
2. Break down problem into smaller sub-problems that needs to be handled 
   - DON'T DESIGN EACH ELEMENT, JUST NOTE THAT THEY EXIST. THEN DESIGN ONE AT A TIME
3. Don't Be Messy 
    - Don't jump from initial design the detail to initial to detail and make changes. 
    - Design from top to bottom, making passes (ignore details of some) if necessary 
    - Design to be able to adapt to change
4. Communicate Design Decisions (WHAT & HOW & WHY)
    WHAT: The current sub-problem you are solving
    HOW: How you are solving the problem 
    WHY: Why do you solve the problem this way 
    - You may know what you are doing, the interview may know why you are doing what you are doing BUT
     YOU NEED INTERVIEW TO KNOW YOU KNOW WHY YOU ARE DOING WHAT YOU ARE DOING
    - Communicate assumptions as questions
        e.g. Can I assume the users are < 100 (WRONG) 
        e.g. What is the maximum number of applicant the program should expect? (CORRECT)  
    - Explain how a design decision works
    - Explain why a design decision is made
        e.g. Will use SQL instead of No-SQL because ... 
    - Tradeoffs that are made 
    - COMPARE DESIGNS, Multiple Design Ideas and TradeOffs are important as they show how you think! 
5. Design for Scale 
    - How will software work across multiple machines 
6. Know how existing things work 
    - Map Reduce
    - FileSystem 
    - Apache Kafka  
7. Complete Your Design
    - DESIGN MUST BE COMPLETED TO SOLUTION
Interviewers will look to ADD REQUIREMENTS:
    - This will expose how hacky your solution was. Do not implement another hacky solution. 
    Think carefully on what you are going to do. 
*/  
//---------------------------------------------------------------------------------------------------------------------------------
//TODO:
// 4 Abstract Factory Design Pattern
//-------------------------------
// refer to Derek Banas's video on youtube
// Like a factory, but everything is encapsulated
// This includes:
// - Method that orders the object
// - Factory that builds the object
// - Final Objects
// - Final object that contain objects that use the Strategy Pattern
//-------------------------------
/*
#include <iostream> 
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 1 Singleton Design Pattern
//-------------------------------
// used when can only instantiate 1 object from a class
// Examples: File Logging, Global Clock/Counter
// Logging is acceptable for good design as it doesn't affect execution of code.
// Basically, if object does not exist yet, create it. If it exist, return the existing object
// Make sure sconstructor is private so there is no other way to create an object except using the createInstance in the static way

// In this example:
// Parent Class : SingletonCounter()
// note: This demonstrates how to implement a global counter for all classes that needs to
// access a global counter/clock  in a game for example as it should be the same clock.
//-------------------------------
/* // 
#include <iostream>
using namespace std;

// A Singleton class
class SingletonCounter
{
private:
    int counterValue;
    static SingletonCounter* firstInstance;
    SingletonCounter()
    {
        // do nothing, but make it private so main() cannot use the constructor since it is private
        // and is forced to use getInstance() method below
        counterValue = 0;
    }
public:
    // To return a static object, need to declare that you are returning a static object here
    static SingletonCounter* getInstance()
    {
        if (firstInstance == NULL)
        {
            firstInstance = new SingletonCounter();
        }
        return firstInstance;
    }
    int getValue() {return counterValue;}
    void setValue(int _value) {counterValue = _value;}
};

// To ensure that at start of program, firstInstance is NULL
SingletonCounter* SingletonCounter::firstInstance = NULL;


int main(void)
{
    SingletonCounter* uniqueInstance = SingletonCounter::getInstance();
    cout << uniqueInstance->getValue() << endl;
    // The below doesn't do anything as it retrieves back the same instace
    uniqueInstance = SingletonCounter::getInstance();
    // uniqueInstance2 points to the same object as uniqueInstance
    SingletonCounter* uniqueInstance2 = SingletonCounter::getInstance();
    uniqueInstance2->setValue(3);
    // Note: Both having same value proving they are pointing to same object
    cout << uniqueInstance2->getValue() << endl;
    cout << uniqueInstance->getValue() << endl;
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 2 Factory Design Pattern
//-------------------------------
// used when:
// Method returns one of several possible classes that share a common superclass
// Basically, when don't know what class object will be needed
// Centralize class selection code

// Want to help control automatic allocation and deallocation of classes for clients
// Want to help share common resources for clients 
//      (e.g. The objects you construct can share a common thread-safe object that you can construct as well, therefore saving space and time)

// For instance,
// Create a new enemy in a game
// RNG picks a random enemy type
// Factory object will return a dynamically created enemy and throw it on the screen

// In this example:
// Parent Class : EnemyShip(), EnemyShipFactory()
// Child Class : UFOEnemyShip(), RocketEnemyShip()
// GrandChild Class: BigUFOShip
// note: EnemyShipFactory basically returns a type of EnemyShip since you can't have a class returning itself.
//-------------------------------
/* //
#include <string>
#include <iostream>
using namespace std;

class EnemyShip
{
private:
    string name;
    double amountDamage;

public:
    string getName(){return name;}
    void setName(string newName) {name = newName;}
    double getDamage(){return amountDamage;}
    void setDamage(double _amountDamage) {amountDamage = _amountDamage;}

    // AI to follow the hero as an enemy
    void followHeroShip()
    {
        cout << name << " is following hero" << endl;
    }

    void displayEnemyShip()
    {
        cout << name << " is on the screen" << endl;
    }

    void enemyShipShoots()
    {
        cout << name << " attacks!" << endl;
    }
};

class UFOEnemyShip: public EnemyShip
{
public:
    UFOEnemyShip()
    {
        setName("UFO Enemy Ship");
        setDamage(20.0);
    }
};

class RocketEnemyShip: public EnemyShip
{
public:
    RocketEnemyShip()
    {
        setName("Rocket Enemy Ship");
        setDamage(10.0);
    }
};

class BigUFOShip: public UFOEnemyShip
{
public:
    BigUFOShip()
    {
        setName("BIG UFO Enemy Ship");
        setDamage(50.0);
    }
};

// Factory Design Pattern handles decision making
class EnemyShipFactory
{
public:
    EnemyShip* makeEnemyShip(int newShipType)
    {
        EnemyShip* newShip = NULL;
        if(newShipType == 1)
        {
            return new UFOEnemyShip();
        }
        else if(newShipType == 2)
        {
            return new RocketEnemyShip();
        }
        else
        {
            return new BigUFOShip();
        }
    }
};

// global functions

void doStuffEnemy(EnemyShip* anEnemyShip)
{
    anEnemyShip->followHeroShip();
    anEnemyShip->displayEnemyShip();
    anEnemyShip->enemyShipShoots();
}
int main(void)
{
    //---------------------------------------------------------
    // Old Method which is terrible
    //---------------------------------------------------------
    // Get user input
    // If user input is 1, create ufoShip
    int userInput = 0;
    cout << "Pleas enter 0 or 1" << endl;
    cin >> userInput;
    EnemyShip* Ship;
    // Note: You basically put all these if, else into a class instead
    if (userInput)
    {
        Ship = new UFOEnemyShip();
    }
    else
    {
        Ship = new RocketEnemyShip();
    }
    doStuffEnemy(Ship); // old ways to program a game , but not dynamic!
    //---------------------------------------------------------
    // Using Factory Design Method
    //---------------------------------------------------------

    EnemyShipFactory* shipFactory = new EnemyShipFactory();
    EnemyShip* enemy = NULL;
    cout << "Pleas enter 0 or 1 or 2" << endl;
    cin >> userInput;
    enemy = shipFactory->makeEnemyShip(userInput); // notice how the code is so much simpler cause you put selection into a class.
    doStuffEnemy(enemy); // old ways to program a game , but not dynamic!
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 3 Builder Design Pattern
//-------------------------------
// To create an object made from a bunch of other objects
// Each creation part is independent of main object
// Hide creation of parts from user
// Only builder knows the specifics 

// Use Case 1: Too many Variables
// Basically, if there is an object that contains a lot of member variables/objects. 
// Lets say 100. 
// Problem is: 
//  Passing all 100 into 1 constructor is tedious
//  Constructing all 100 variables is not efficient. 
//  You may only get the variables 1 at a time instead of all 100. Waiting until you have all 100 variables 
//  before you start constructing anything is a waste of time. 
//
//  Thus, you have the Builder class, each time you get 1 variable, you pass it to the Builder class to construct. 
//  By the time you are done with passing in the 100th variable, the builder class already constructed all 99 other variables, 
//  this final variable allows constructor class to finish constructing. Only when you are very sure with the 100 variables you pass in, 
//  you can ask the Builder class to return to you the object that was constructed

// Use Case 2: Similar Complex Design process 
// Constructing a robot is a similar design proces. You need to make the arms and then make the legs. 
// However, you can pass it variables so it does a different construction for arms and legs 
// You can have classes that initialize all 100 variables for you. 
// Then, you can pass those classes in as a parameter to the Builder, which reads those pre-defined variables and constructs the robot

// Use Case 3: Required and Optional variables
// When your class has required variables and optional variables, the user won't know which is which. 
// Therefore, you make required variables variables in the constructor for the builder, 
// and optional variables as variables that are set by the builder.
// Then, it will be clear
//-------------------------------
/* //
#include <string>
#include <iostream> 
using namespace std;

// Interface
class RobotPlan 
{
public:
    // Each different construction method that accepts each different variable
    virtual void setRobotArms(string arms) = 0;
    virtual void setRobotLegs(string legs) = 0;
    // Imagine there are 100 more of these
};

// Implement the plan with a specific robot
class Robot : public RobotPlan
{
private: 
    string robotArms;
    string robotLegs;
    // Imagine there are 100 more of these
public:
    void setRobotArms(string arms) 
    {
        this->robotArms = arms;
    }
    void setRobotLegs(string legs) 
    {
        this->robotLegs = legs;
    }
    string getRobotArms()
    {
        return robotArms;
    }
    string getRobotLegs()
    {
        return robotLegs;
    }
};

// Interface For Building
class RobotBuilder
{
public:
    virtual void buildRobotArms() = 0;
    virtual void buildRobotLegs() = 0;
    virtual Robot* getRobot() = 0;
};

// A special type of robotBuilder that builds the robot with the 'Tamiya' Brand
// Basically initializes all 100 paramaters for you so you don't have to remember them
class TamiyaRobotBuilder : public RobotBuilder
{
private:
    // The robot to be build
    // note: can only declare pointers when have abstract classes
    Robot* robot; // note: Similar to Strategy Design Pattern
public:
    // Build the robot
    TamiyaRobotBuilder() 
    {
        this->robot = new Robot();
    }
    // Build the arms 
    void buildRobotArms()
    {
        // Arms Version Tamiya is the default value forthe Arms variable for TamiyaRobot
        robot->setRobotArms("Arms Version Tamiya");
    }
    // Build the legs
    void buildRobotLegs()
    {
        // Legs Version Tamiya is the default value forthe Arms variable for TamiyaRobot
        robot->setRobotLegs("Legs Version Tamiya");
    }
    // Return the robot that was build
    Robot* getRobot() 
    {
        return this->robot;
    }
};

// 
class RobotEngineer 
{
private:
    // Has a robot to build the robot
    RobotBuilder* robotBuilder; // Note: Can only declare pointers for Abstract Classes
public:
    // Receives a variable robotBuilder, different variable returns the 
    RobotEngineer(RobotBuilder* _robotBuilder)
    {
        this->robotBuilder = _robotBuilder;
    }
    // Get the robotBuilder to build the robot
    Robot* getRobot() 
    {
        return this->robotBuilder->getRobot();
    }
    // Build the robot
    void makeRobot() 
    {
        // Strategy Design Pattern here
        this->robotBuilder->buildRobotArms();
        this->robotBuilder->buildRobotLegs();
    }
};

int main(void)
{
    // Create the robot using the blueprint defined in TamiyaRobotBuilder()
    // This blueprint allows you to start passing in variables to start constructing each component
    // Use the Tamiya Robot Builder brand
    RobotBuilder* instanceRobot = new TamiyaRobotBuilder();
    // Pass robot specification (you want it to be a Tamiya Robot) to engineer
    // The Tamiya Robot class already contains the default values of all 100 parameters to create a Tamiya Robot
    RobotEngineer* robotEngineer = new RobotEngineer(instanceRobot);
    // Make engineer build the robot after passing in all specifications and variables
    robotEngineer->makeRobot();
    // Get the robot that is completely constructed and made by the engineer
    Robot* completedRobot = robotEngineer->getRobot();
    // Use the robot
    cout << "Robot Built" << endl; 
    cout << completedRobot->getRobotArms() << " | " << completedRobot->getRobotLegs() << endl;
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 4 Prototype Design Pattern
//-------------------------------
// Create new objects by cloning other objects
// Adding of any subclass instance of known parent class at runtime 
// A number of potential classes that want to use only if needed during runtime
// Reduces need for creating subclasses
// Used whenever you want to clone something instead of creating a new one
// Clone => Maintains all attributes and properties
// New => Make a new object with initial attribute and properties
//
// Application: 
//      Bank Operations -> Clone your account information, perform work on clone until succeed
//                         replace from original account only when done
//                         You are essentally 'prototyping' on the clone and then releasing once it works
//-------------------------------
/* //
#include <string>
#include <iostream>
using namespace std;

// Interface
class Animal
{
public:
    // All animals must have a way to clone itself
    // For polymorphism
    virtual Animal* makeCopy() const = 0;
};

class Sheep : public Animal 
{
private:
    int weight;
public:
    Sheep() : weight(20) {};
    Sheep(int _weight) : weight(_weight) {};
    Animal* makeCopy() const
    {
        // note: NULL can only be passed into pointers
        Sheep* sheepObj = NULL;
        // Clone this sheep with same properties
        sheepObj = new Sheep(this->weight);
        return  sheepObj;
    }
    int getWeight() { return weight; }
};

class CloneFactory
{
public:
    // Get the clone of this animal passed in
    Animal* getClone(Animal* animal)
    {
        return animal->makeCopy();
    }
};

int main(void)
{
    CloneFactory* animalMaker = new CloneFactory();
    Sheep * a = new Sheep();
    Sheep * clonedSheep = (Sheep *) animalMaker->getClone(a);
    // Print to show that they are different
    if (a == clonedSheep)
        cout << "Both refer to same sheep" << endl;
    else
    {
        cout << "Both refer to different sheep" << endl;
        cout << " original: " << a->getWeight() << " | cloned: " << clonedSheep->getWeight() << endl;
    }
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 1 Strategy Design Pattern 
//-------------------------------
// Demonstrates Decoupling => Separate implementation of class with implementation of algorithms
//  => Interface is used as an instance variable (Fly)
// that dynamically changes.
// It is implemented with a parent class aggregating this interface
// with a pointer.
// Each subclass of this parent class will point this flying pointer to the right
// class from the set of classes that implements the interface
// In this example:
// Parent Class : Animal()
// Child Class : Dog(), Bird()
// Interface : Fly()
// Implement Interface: ItFly(), CantFly()
// note: ItFly() & CantFly() is known as a family of algorithms, encapsulated in Interface Fly()
// whereby, you define the algorithms differently from the subclass (Dog(), Birds())
// by doing so, you don't have to redefie ItFly() methods and CantFly() methods in every single animal subclass
// Strengths: You have a list of algorithms that can be called dynamically at runtime. 
//            Each class can just change its algorithms during runtime or sometime in future. 
//            Dont couple a class permanently with its algorithm choices
//-------------------------------
/* //
#include <string>
#include <iostream>
using namespace std;

// Create an Interface called Flys
class Fly
{
public:
    virtual string fly() const = 0;
};

// make a subclass for animals that implements the interface Flys
class ItFly : public Fly
{
    string fly() const
    {
        return "Fly!!";
    }
};

// make a subclass for animals that implements the interface Flys
class CantFly : public Fly
{
    string fly() const
    {
        return "Don't Fly!!";
    }
};

class Animal
{
private:
    string sound; // e.g. "bark" for dog, "meow" for cat
    int weight;
public:
    // composition: Change behaviors at runtime
    // => An animal that didn't fly before can start flying
    Fly* flyingType; // aggregate inheritance Flys
                    // note: Can't be variables for inheritance (cause virtual class)
                    // can only be pointer types

    Animal() : sound(""), weight(0) {};

    void setSound(string _sound)
    {
        sound = _sound;
    }
    string getSound(){ return sound;}

    void setWeight(int _weight)
    {
        weight = weight;
    }
    int getWeight() { return weight; }

    // NOT ALL ANIMALS FLY, so use interface

    string tryToFly()
    {
        return flyingType->fly();
    }

    void setFlyingAbility(Fly* newFlyType)
    {
        flyingType = newFlyType;
    }
};

class Dog: public Animal
{
public:
    Dog() : Animal() // inherit parent constructor
    {
        flyingType = new CantFly();
    }
};


class Bird: public Animal
{
public:
    Bird() : Animal() // inherit parent constructor
    {
        flyingType = new ItFly();
    }
};

int main(void)
{
    Animal* doggy = new Dog();
    Animal* birdy = new Bird();

    cout <<"Dog: " << doggy->tryToFly() << endl;
    cout <<"Bird: " << birdy->tryToFly() << endl;

    // Therefore, if few years later you decide Dogs can fly,
    // simply do this
    doggy->setFlyingAbility(new ItFly());
    cout <<"Dog: " << doggy->tryToFly() << endl;

    // Therefore , in Strategy Design Pattern,
    // each class can have it's own strategies in handling functions
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 2 Visitor Design Pattern
//-------------------------------
// To add methods to different classes without modifying those classes (honors open-closed principle)
// Uses double dispatch => Operation depends on: 2 dynamic classes 
//                          2 receivers are: The type of visitor class and the type element it visits (visitable)
// Requires Visitable class to have an interface that allows you to add to it by just defining a new Visitor class. 
// Thus, each time you need to make a new change, as long as your different classes already implements the Visitable Interface, 
// you just need to make a new concreteVisitor and pass in that as a parameter to the object's accept function.
// Classes:
//      - Visitor Interface => A new interface that needs to be implemented by a new concreteClass that handles each different class differently. 
//      - Concrete Visitor => Implements the Visitor Interface by adding many different visit() function accepting different type of classes (function overloading)
//                            It implements the visit() method
//                            Each different class has its own visit() method in ConcreteVisitor class
//      - Visitable Interface => A new interface that needs to be implemented by the different classes that needs to change. 
//                              Contains the Visit function. Instead of changing each different class, you just need to add in the method
//                              accept(Visitor * visitor) { visitor->visit(this); }
//      - Accept Function() => This is a simple method that is added to each different class that needs to be changed
//      - Visit Function() => This is a method implemented by ConcreteVisitor
// Applications: 
//      Public API - Make new Visitor class for existing class to call the accept(visitor) function)_
//-------------------------------
/* //
#include <string>
#include <iostream>
using namespace std;

// Visitor Interface
class Visitor 
{
public:
    virtual void visit(class TypeA* A) = 0;
    virtual void visit(class TypeB* B) = 0;
};

// Concrete Visitor 1 => Count
// note: Each type of class needs its own visit() method
class CountVisitor : public Visitor 
{
private:
    int numA, numB;
public:
    void visit(TypeA* A); 
    void visit(TypeB* B);
};

// Concrete Visitor 2 => print
class PrintVisitor : public Visitor 
{
public:
    void visit(TypeA* A); 
    void visit(TypeB* B);
};

// Visitable Interface
// Each class that you want to change must implement Visitable Interface
class Visitable
{
public:
    virtual void accept(Visitor * visitor) = 0;
    // note: Every class's accept implementation will be the same
};

class TypeA : public Visitable
{
public:
    void accept(Visitor * visitor) 
    {
        visitor->visit(this);
    }
}; 

class TypeB : public Visitable
{
public:
    void accept(Visitor * visitor) 
    {
        visitor->visit(this);
    }
}; 

void CountVisitor::visit(TypeA* A) 
{
    numA++;
    cout << "numA is: " << numA << endl;
}

void CountVisitor::visit(TypeB* B) 
{
    numB--;
    cout << "numB is: " << numB << endl;
}

void PrintVisitor::visit(TypeA* A) 
{
    cout << "Type A" << endl;
}
void PrintVisitor::visit(TypeB* B) 
{
    cout << "Type B" << endl;
}

int main(void)
{
    TypeA * a = new TypeA();
    TypeB * b = new TypeB();
    Visitor * v1 = new CountVisitor();
    Visitor * v2 = new PrintVisitor();
    a->accept(v1);
    a->accept(v2);
    b->accept(v1);
    b->accept(v2);
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 3 Observer Design Pattern
//-------------------------------
// Used when:
// - need many other objects to receive an update when another object changes

// Subject = Publishers
//  - maintain a list of its observers and notify them of any state chnages calling one of their methods
// Observer = Subscribers

// Advantage:
//  - Subject don't have to know anything about Observers
// Disadvantage:
//  - Subject may send updates that don't relate to some Observers 

// In this example:
// Interface : Observer(), Subject()
// Implement Interface: StockObserver(), StockGrabber()
// Each Observer() contains a subject pointer so when it is created, it adds itself
// automatically to the subject's list of observers.
// Similarly, each subject automatically calls each of its list of observers update() method
// when it updates any of its values.
//-------------------------------
/* //
#include <vector> // vector of Observers
#include <iostream>
using namespace std;

// Observer Interface
class Observer
{
public:
    // Note: It is public so the Subject can call it
    virtual void update(double _ibmPrice, double _applePrice, double _googlePrice) = 0;
    // Note: Interface doesn't contain any members 
};


// Subject Interface 
class Subject
{
public:
    // Note: It is public so the Observer can call it
    virtual void registerObs(Observer* o) = 0;
    virtual void unregisterObs(Observer* o) = 0;
    virtual void notifyObserver() = 0;
};


// Note: class A: B  == class A: private B
// Implement Observer Interface with Stocks
class StockObserver: public Observer
{
private:
    double ibmPrice, applePrice, googlePrice;
    static int observerIDTracker;  // a counter so each observer has a unique number for observerID
    int observerID; // unique ID for each observer
    Subject* stockGrabber;

    void printThePrices()
    {
        cout << observerID << "IBM: " << this->ibmPrice <<" AAPL: " << this->applePrice << " GOOG " << this->googlePrice << endl;
    }

public:
    StockObserver(Subject* _stockGrabber)
    {
        this->stockGrabber = _stockGrabber;
        this->observerID = ++observerIDTracker;
        cout <<"New Observer: " << this->observerID << " created" << endl;
        stockGrabber->registerObs(this); // make the subject register this observer
    }

    // This method is called by the Subject/Subscriber when an update is made
    void update(double _ibmPrice, double _applePrice, double _googlePrice)
    {
        this->ibmPrice = _ibmPrice;
        this->applePrice = _applePrice;
        this->googlePrice = _googlePrice;
        // Print prices after updating.
        this->printThePrices();
    }
};

// A global int for observer class to keep track of which observer it is in Subscriber
// Serves as an ID
int StockObserver::observerIDTracker = 0; // initialization in CPP file instead of header file!

class StockGrabber : public Subject
{
private:
    // Note: Ensure this is a weak reference
        // This is so that if an Observer forgets to unregister itself, the termination of the Observer itself 
        // will handling cleaning up its memory. 
        // If this was a strong reference and Observer forgets to unregister itself, the termination of the Observer itself
        // does not remove it from the list of observers here. Then, the Subscriber will be holding a reference to an object that no 
        // longer exist in the observer and is useless. Wasted memory
    vector<Observer*> observers; // vector of Observer pointers
    double ibmPrice, applePrice, googlePrice;
public:
    StockGrabber()
    {
    }

    // This method is called by a new observer that is created to register itself
    void registerObs(Observer* o)
    {
        observers.push_back(o);
        return;
    }
    void unregisterObs(Observer* o)
    {
        // TODO: Find where o is in observers
        // and delete it from the index
        int observerIndex = 0; // TODO: Find index of o , temporary set to first element
        observers.erase(observers.begin() + observerIndex);
        cout << "Observer at index " << observerIndex << " is deleted" << endl;
        return;
    }
    void notifyObserver()
    {
        for(auto i = observers.begin(); i !=  observers.end(); i++)
        {
            (*i)->update(ibmPrice, applePrice, googlePrice);
        }
    }

    void setIBMPrice(double newIbmPrice)
    {
        ibmPrice = newIbmPrice;
        notifyObserver();
    }

    void setApplePrice(double newApplePrice)
    {
        applePrice = newApplePrice;
        notifyObserver();
    }

    void setGooglePrice(double newGooglePrice)
    {
        googlePrice = newGooglePrice;
        notifyObserver();
    }
};

int main(void)
{
    StockGrabber* stockGrabber = new StockGrabber();
    StockObserver* observer1 = new StockObserver(stockGrabber);
    StockObserver* observer2 = new StockObserver(stockGrabber);
    stockGrabber->setIBMPrice(197.00);
    stockGrabber->setApplePrice(677.60);
    stockGrabber->setGooglePrice(676.40);
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 4 Template Method Design Pattern
//-------------------------------
// Basically a Template Method will be defined in the mainInterface and how it is gonna work. 
// Then in template method, it calls a bunch of submethods that are defined differently in different subclasses that implements this Template Method interface
// Think of template implementation in C++ that allows you to customize the datatypes. 
// For this, you have a template methods where you can customize the methods inside that template methods
// You can customize local variables by defining abstract methods that returns different local variables
//-------------------------------
/* //
#include <string>
#include <iostream>
using namespace std;

// TemplateMethod Interface
class TemplateMethod
{
public:
    // These are submethods that needs to be defined in children that implements this method
    virtual void methodOne() = 0; // these must be implemented in derived
    virtual void methodTwo() = 0;
    virtual void methodThree() = 0;
    virtual string getVarStr() = 0;
    // This is the template method 
    // It will always be the same, its just the variables inside it may change
    void mainTemplateMethod()  // notice how this is non-virtual, which means any derive class that do not override this function will call this template
    {
        cout << "Doing some stuff before calling method 1" << endl;
        // Call method one
        methodOne();
        cout << "Doing some stuff between method 1 and method 2" << endl;
        methodTwo();
        cout << "Doing some stuff between method 2 and method 3" << endl;
        string haha = getVarStr(); 
        cout << haha << endl;
        // Call method 3 5 times
        for(int i = 0; i < 5; i++)
        {
            methodThree();
        }
        cout << "Done calling method 3" << endl;
    }
};

class subClassOne : public TemplateMethod
{
    // Override the abstract methods that needs to be implemented
    void methodOne()
    {
        cout << "haha " << endl;
    }
    void methodTwo()
    {
        cout << "bebe " << endl;
    }
    void methodThree()
    {
        cout << "kiki " << endl;
    }
    string getVarStr() 
    {
        return "ChangeVariablesToo!";
    }
};

int main(void)
{
    TemplateMethod* a = new subClassOne();
    a->mainTemplateMethod();
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 5 Chain Of Responsibility Design Pattern
//-------------------------------
// Basically, a request comes to a linked list of objects, 
// each object take turns to see if it is able to handle the request. 
// If it does not, it sends the request to the next node in the list
// If it is, it will handle it. After that, it can either:
// i) continue to send the request to next node 
// ii) end the request as it is handled
// If no nodes are able to handle the request, the last node needs to handle the request the default way defined in the parent
// used when: Want to set a chain of methods to try out on a request, easily extensible by just adding a new node into the chain
// Classes: 
//      Handler: Contains the default handle() if no nodes can process the request
//      ConcreteHandler: Each node in the handler with its own implemented method to process the request
//      Request: The class containing information about the request to be handled
// Applications: Communication Networks where you only respond to a request if it matches your memory address ID. Otherwise, just pass it along the list 
//-------------------------------
/* //
#include <string>
#include <iostream>
using namespace std;

// Note: In this example, the Request class is simply a double

// Default handler if none of the node is able to handle
class Handler 
{
protected:
    Handler * successor; // next handler to call 
public:
    Handler() 
    {
        successor = NULL;
    }
    Handler(Handler * _next) 
    {
        successor = _next;
    }
    virtual void handle(double request) 
    {
        cout << "The cost: " << request << " is too high for any budget" << endl;
    }
    void setNext(Handler * _next)
    {
        successor = _next; 
    }
};

// Handler in the first node
class SubHandler : public Handler
{
private:
    double budget; // specific for this example
public:
    SubHandler() : Handler() { budget = -1;}
    SubHandler(double _budget) : Handler() 
    {
        this->budget = _budget;
    }
    SubHandler(double _budget, Handler* _next) : Handler(_next) 
    {
        this->budget = _budget;
    }
    void handle(double request) 
    {
        if (request <= this->budget) 
        {
            cout << "Purchase is made by this handler with budget " << budget << endl;
        }
        else 
        {
            // Note: Can directly access successor because it is defined as protected
            if (successor)
            {
                // Let the next node process the request
                successor->handle(request);
            }
            else
            {
                // Call the default parent behavior
                Handler::handle(request);
            }
        }
    }
};

int main(void)
{
    double purchase = 80.0; // price of requested item
    Handler * ceo = new SubHandler(100000.0);
    Handler * manager = new SubHandler(10000.0, ceo);
    Handler * employee = new SubHandler(1000.0, manager);
    Handler * intern = new SubHandler(100.0, employee);
    Handler * a = intern;
    // MISTAKE: A pointer of a parent class to a parent class object will automatically call the parent's class method!
    //          Used to have:
    //          Handler * a = new Handler(); a->setNext(intern);
    //          Which was wrong cause you default to calling the parent's method in the calls to handle() below
    a->handle(purchase);
    purchase = 180.0;
    a->handle(purchase);
    purchase = 1180.0;
    a->handle(purchase);
    purchase = 11180.0;
    a->handle(purchase);
    purchase = 999999.0;
    a->handle(purchase);
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 6 State Design Pattern
//-------------------------------
// To allow an objects behavior to vary based on its state during runtime without too many conditional statements
// All state specific behavior is in a ConcreteState class, this ease maintenance such as adding a new state 
// Do not rely on current state based on a variable in the Context class, doing so will require lots of conditional statements in that one class
// Decentralization of State Classes => Each ConcreteState defines which other Concrete State it transitions to. 
//      => Advantage: Easy to maintain 
//      => Disadvantage: A coupling between ConcreteStates, each state must know of each other's existence
// Classes: 
//      Context/Machine => Interface for client  (Finite State Machine)
//              => Maintains an instance of current concreteState using a StateInterface pointer, which identifies what state the Context is currently in
//              => If implementing decentralization of state classes, need allow a way for ConcreteState to change the current state explicitly
//              (Uses Strategy Design Pattern)
//      State Interface => Interface for behavior of current state
//      ConcreteState => Each individual state and its behavior
// Applications: Finite State Machine
//-------------------------------
/* //
#include <string>
#include <iostream>
using namespace std;

// Finite State Machine
class Machine
{
private:
    // NOTE: You need the word class here as State is only defined below
    class State * current; // A pointer to the current state
    double input; 
public:
    Machine();
    // To set the current state
    void setCurrent(State *s) 
    {
        this->current = s;
    }
    double getInput()
    {
        return this->input;
    }
    void setInput(double in)
    {
        this->input = in;
    }
    void act();
};

// State Interface 
class State
{
public:
    // Method to change state to set Machine m to state s
    virtual void changeState(Machine *m) = 0; 
    // A behavior
    virtual void doAction() = 0 ; 
};

class ConcreteStateOne : public State
{
    void doAction() 
    {
        cout << "Action from State One" << endl;
    }
    void changeState(Machine *m);
};

class ConcreteStateTwo : public State
{
    void doAction() 
    {
        cout << "Action from State Two" << endl;
    }
    void changeState(Machine *m);
};

class ConcreteStateThree : public State
{
    void doAction() 
    {
        cout << "Action from State Three" << endl;
    }
    void changeState(Machine *m);
};

// Note: Whenever you have circular dependencies, you can only define the implementation after 
//      providing all header file details (class definitions)
// Constructor for Machine
Machine::Machine()
{
    input = 0; 
    // Initialize to first state
    current = new ConcreteStateOne();
}

void Machine::act()
{
    // Note: Both doAction() and changeState() must be public and not protected for Machine to access them here
    this->current->doAction();
    this->current->changeState(this);
}

// Need only give implementation after including all classes that exist
void ConcreteStateOne::changeState(Machine *m)
{
        m->setCurrent(new ConcreteStateTwo);
        delete this;
}
void ConcreteStateTwo::changeState(Machine *m)
{
        if (m->getInput() < 0)
            m->setCurrent(new ConcreteStateOne);
        else
            m->setCurrent(new ConcreteStateThree);
        delete this;
}
void ConcreteStateThree::changeState(Machine *m)
{
        return;
        // Always stay at state three
}

int main(void)
{
    Machine* m = new Machine();
    // Perform action
    m->act();
    // Perform action
    m->act();
    m->act();
    m->act();
    m->act();
    delete m;
    cout << "To show next state depends on inputs" << endl;
    m = new Machine();
    m->setInput(-1);
    m->act();
    m->act();
    m->act();
    m->act();

    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 7 Memento Design Pattern
//-------------------------------
// To restore an object to its previous state after applying a temporary change (moment)
// Classes:
//      Originator => Object that saves Memento original state and creates a new temporary Memento with current state
//      Caretaker => Going to modify  Memento but wants to undo the change, it requests Memento from Originator
//                   It passes Memento back to Originator to revert the Memento back to original state.
//                   Contains all previous versions of Memento.
//      Memento => Object requested to Originator by Caretaker, which is later passed back into Originator to revert to original state
//                 Must have interface for accessing necessary state variables for Originator, so that does not violate encapsulation
//  Applications: 
//      Random Number Generator always generates same number sequence with same seed(state)
//      Saving a game`
//      Undo and Redo operations in text editors
//
//-------------------------------
/* //
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Object that is to be saved
class Memento
{
private:
    string state;
public:
    Memento(string s) : state(s) {}
    string getState() {return state;}
    void setState(string s) { state = s;}
};

// Class that saves the current state, or restores a Memento to a saved state
class Originator
{
private:
    string savedState;
public:
    void save(Memento* m) 
    {
        savedState = m->getState();
    }
    Memento* createMemento()
    {
        Memento* m = new Memento(savedState);
        return m;
    }
}; 

class CareTaker
{
private:
    vector<Memento *> mementos; // a list of all the saved momentos
public:
    void addMemento(Memento * m)
    {
        mementos.push_back(m);
    }
    Memento * getMemento(int index)
    {
        return mementos[index];
    }
};

int main(void)
{
    Originator* origin = new Originator(); 
    CareTaker* care = new CareTaker();
    Memento * m1 = new Memento("State 1");
    origin->save(m1);
    // Add first State
    care->addMemento(origin->createMemento());
    Memento * m2 = new Memento("State 2");
    origin->save(m2);
    // Add second State
    care->addMemento(origin->createMemento());

    // Get back first state
    origin->save(care->getMemento(0));
    Memento * m3 = origin->createMemento();
    cout << "First saved state is: " << m3->getState() << endl;
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 8 Mediator Design Pattern
//-------------------------------
// Handles communication between objects
// Reduces dependencies between how objects communicate => loosely coupled
// Allows many to many relationships, mappings between relationships is easier
// Classes:
//      - Mediator Interface => Interface for communication betwee Colleague Objects
//      - ConcreteMediator > Coordinates communication between Colleague objects 
//      - Colleague -> Communicates with other Colleague through its Mediator
//  Applications:
//      Control Tower => All airplanes communicate via control tower. 
//      Router => All devices (phone, laptop) communicate via router
//      Unix Control Groups => A group can have >= 0 users, a user can have >= groups
//-------------------------------
/* //
#include <map>
#include <string>
#include <iostream>
using namespace std;

class Mediator
{
public:
    virtual void send(const int id, const string message) = 0;
};

class ConcreteMediator : public Mediator
{
private:
    map<int, class Colleague*> colleagues;
    bool exist(int id);
public:
    void setColleague(Colleague * c);
    void send(int id, const string message);
};

class Colleague
{
private:
    Mediator * mediator; 
    int id;
public:
    Colleague(int _id) : id(_id) {}
    int getId() { return id; }
    // MISTAKE: Only constructors take the form  className() : mediator(m) {}
    void setMediator(Mediator * m) 
    {
        mediator = m;
    }
    void receive (const string  msg)
    {
        cout << "Message received by " << id << ": " << msg << endl;
    }
    void send (int sendId, string msg)
    {
        cout << id << " send message to " << sendId << ": " << msg << endl;
        mediator->send(sendId, msg);
    }
};

bool ConcreteMediator::exist(int id)
{
    return colleagues.find(id) != colleagues.end();
}
void ConcreteMediator::setColleague(Colleague * c)
{
    if (!exist(c->getId()))
    {
        c->setMediator(this);
        colleagues[c->getId()] = c;
    } 
}
void ConcreteMediator::send(int id, const string message)
{
    if(exist(id))
    {
        Colleague *c = colleagues[id];
        c->receive(message);
    }
}

int main(void)
{
    Colleague * peter = new Colleague(1);
    Colleague * paul = new Colleague(2);
    ConcreteMediator * m = new ConcreteMediator();
    m->setColleague(peter);
    m->setColleague(paul);
    peter->send(2, "haha");
    paul->send(1, "lala");
    // Note: Can also send message to self through mediator
    paul->send(2, "lala");
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 9 Command Design Pattern
//-------------------------------
//  An object is used to encapsulate all information needed for calling a method.
//  Information includes: methodName, ownerOfMethod, methodParameterValues
//  Terminology: 
//      1. Receiver: The actual object that executes the methods in lowest level
//          e.g. Television with up() and down() methods
//      2. Command: A set of commands that can be seen by the invoker
//          - ConcreteCommand: An implementation of the command with respect to a receiver
//          - Knows "WHAT" to do
//      3. Invoker: Invokes the commands, to keep track of which commands are executed, or place them in queues
//          - e.g.: A button
//          - Knows "WHEN" to do
//      4. Client: What the user of your program sees
//          - e.g.: PressRedButton(), UnpressRedButton()
//  Stores: 
//      - List of code executed many times or later by Invoker 
//      - Can implement undo procedures for past commands
//  Application:
//      - Queue a list of commands to be executed later
//      - Grouping up a set of actual methods into a command that does everthing
//  Disadvantages:
//      Command Design Pattern results in many small classes that stores list of commands
//      Basically, a lot of different classes that executes similar commands in different order
//  Differences with Strategy Pattern: 
//      - Strategy is the hope of implementing methods differently in subclasses, polymorphism
//      - Strategy is hope of decoupling algorithms with classes
//      - Strategy is about 'HOW' something is done
//      - Command is about 'WHAT' needs to be done
//      - Command is hope of attaching a bunch of code to a command seen by the client
//      - Command is hope of encapsulation of methods 
//      - Command is to be able to queue a list of commands and keep track of commands executed
//      - Command is to be able to transport a command (e.g. from client to server remotely, needs queue)
//-------------------------------
/* //
#include <string>
#include <iostream>
using namespace std;

// Receiver Interface
class ElectronicDevice
{
public:
    virtual void up() = 0;
    virtual void down() = 0;
};

// An actual Receiver, 
// Television receives the commands
class Television : public ElectronicDevice
{
private: 
    int volume;
public:
    Television()
    {
        volume = 0;
    }
    void up()
    {
        volume++;
        cout << "Up: " << volume << endl;
    }
    void down()
    {
        volume--;
        cout << "Down: " << volume << endl;
    }
};

// Command Interface
// Types of commands that the Invoker can execute
class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Method 1 , also known as ConcreteCommand. 
// It connects the Command and Receiver. 
// ConcreteCommand -> Implementation of Command Interface on the Receiver
class TurnTvUp : public Command
{
private:
    ElectronicDevice* theDevice; // Receiver
public:
    TurnTvUp(ElectronicDevice * newDevice)
    {
        theDevice = newDevice;
    }
    void execute()
    {
        theDevice->up();
    }
    void undo()
    {
        theDevice->down();
    }
};

// Method 2, a ConcreteCommand
class TurnTvDown : public Command
{
private:
    ElectronicDevice* theDevice;
public:
    TurnTvDown(ElectronicDevice * newDevice)
    {
        theDevice = newDevice;
    }
    void execute()
    {
        theDevice->down();
    }
    void undo()
    {
        theDevice->up();
    }
};

// Invoker Interface
// It can only use the Command Interface's methods
class DeviceButton
{
private:
    Command* theCommand;
public:
    DeviceButton(Command* newCommand)
    {
        theCommand = newCommand;
    }
    void press()
    {
        theCommand->execute();
    }
    void undo()
    {
        theCommand->undo();
    }
};

// Client Interface
// It creates a ConcreteCommand and set its Receivers
class  TvRemote
{
public:
    // Static here is so that you can use this function publicly without making an object
    static ElectronicDevice* getDevice()
    {
        return new Television();
    }
};

int main(void)
{
    // Get the device
    // Note: Can use TvRemote's getDevice method without having an object as method is declared static
    ElectronicDevice* newReceiver = TvRemote::getDevice(); // let the receiver be a television
    // First turn tv up`
    // Pass in Client to get the Command for that client
    // note: Client interface contains the Receiver
    TurnTvUp* increaseVolumeCommand= new TurnTvUp(newReceiver); 
    // To invoke command, pass Command Object to Invoker Object
    // Can pass different Command Object to Invoker object
    DeviceButton* upButtonInvoker= new DeviceButton(increaseVolumeCommand);
    // note: Invoker allows book keeping of commands executed
    // note: Invoker can place commands into a queue to be executed later
    upButtonInvoker->press();
    upButtonInvoker->undo();
    // Now turn tv down
    TurnTvDown* reduceVolumeCommand= new TurnTvDown(newReceiver);
    DeviceButton* downButtonInvoker = new DeviceButton(reduceVolumeCommand);
    // Turn tv down 3 times
    downButtonInvoker->press();
    downButtonInvoker->press();
    downButtonInvoker->press();
    downButtonInvoker->undo();
    // note: TV's up() and down() commands are hidden
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 10 Interpreter Design Pattern
//-------------------------------
// To evaluate sentences in a language 
// Convert one representation of data into another
// Classes: 
//      Expression Interface`: Interface for nodes. Contains the method interpret() 
//      Terminal Nodes: Nodes that do not contain other expressions (Leaf nodes in tree)
//      Non-Terminal Nodes: Nodes that contain other expression (Leaf nodes in tree)
// Application: Convert Roman Numerals to actual integers
// Application: Convert feet to metres
// Application: Compilers 
//-------------------------------
/* //
#include <cstdlib>
#include <cstring>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
using namespace std;
// need C++11

// e.g. Postfix mathematics notation, 3 = 1 2 + (instead of 3 = 1+2 which is infix)
// e.g. (3 - 2 + 1) * 4 (infix) = 4 3 2 - 1 + * (postfix) = 8
// Tree representation
//               *
//              / \
//             +  4
//            / \
//           -   1
//          / \
//         3   2

// Expression Interface`
class Expression
{
public: 
    virtual int interpret() = 0;
};

// Terminal Node
class NumberExpression : public Expression
{
private:
    int num;
public:
    NumberExpression(int i) : num(i) {}
    NumberExpression(string i) 
    {
        num = atoi(i.c_str());
    } 
    int interpret()
    {
        return num;
    }
};

// Non-Terminal Node
class Multiply : public Expression
{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    Multiply(Expression * left, Expression * right) 
    {
        this->leftExpression = left;
        this->rightExpression = right;
    }
    int interpret()
    {
        return leftExpression->interpret() * rightExpression->interpret();
    }
};

// Non-Terminal Node
class Plus: public Expression
{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    Plus(Expression * left, Expression * right) 
    {
        this->leftExpression = left;
        this->rightExpression = right;
    }
    int interpret()
    {
        return leftExpression->interpret() + rightExpression->interpret();
    }
};

class Minus: public Expression
{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    Minus(Expression * left, Expression * right) 
    {
        this->leftExpression = left;
        this->rightExpression = right;
    }
    int interpret()
    {
        return leftExpression->interpret() - rightExpression->interpret();
    }
};

bool isOperator(const string s)
{
    const char* temp = s.c_str();
    if (strcmp("+",temp) == 0)
    {
        return true;
    }
    else if (strcmp("-",temp) == 0)
    {
        return true;
    }
    else if (strcmp("*",temp) == 0)
    {
        return true;
    }
    return false;
}

Expression * getOperator(const string s, Expression * left, Expression * right)
{
    const char* temp = s.c_str();
    if (strcmp("+",temp) == 0)
    {
        return new Plus(left, right);
    }
    else if (strcmp("-",temp) == 0)
    {
        return new Minus(left, right);
    }
    else if (strcmp("*",temp) == 0)
    {
        return new Multiply(left, right);
    }
    cout << " NOT AN OPERATOR ERROR! " << endl;
    return NULL;
}

int main(void)
{
    string pattern = "4 3 2 - 1 + *";
    vector<string> v; 
    v.push_back("4");
    v.push_back("3");
    v.push_back("2");
    v.push_back("-");
    v.push_back("1");
    v.push_back("+");
    v.push_back("*");
    stack<NumberExpression*> s; 
    // note: auto needs >> g++ -std=c++11 fileName.cpp
    for(auto i = v.begin(); i != v.end(); i++)
    {
        // Pop latest 2 elements, and push
        if(isOperator(*i))
        {
            Expression * right = s.top();
            s.pop();
            Expression * left = s.top();
            s.pop();
            Expression * op = getOperator(*i, left, right);
            int result = op->interpret();
            s.push(new NumberExpression(result));
        }
        else
        {
            NumberExpression * a = new NumberExpression(*i);
            s.push(a);
        }
    }
    Expression * z = s.top();
    s.pop();
    cout << "Result: " << z->interpret() << endl;
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 1 Decorator Design Pattern
//-------------------------------
// Modify an object dynamically 
// Extend capability of object (similar to inheritance) but do so at runtime. 
// Add functionality using many simple classes
// Basically, keep passing each class into each other's constructor and adding properties to its variables as passed into constructors

// Example application: Pizza Toppings, Each different topping you add on a pizza increases its costs. 
//-------------------------------
/* //
#include <string>
#include <iostream>
using namespace std;

// Interface 
class Pizza 
{
public:
    virtual string getDescription() const = 0;
    virtual double getCost() const = 0;
};    

// An empty pizza
class PlainPizza : public Pizza
{
private:
    string description;
    double cost; 
public:
    PlainPizza() 
    {
        cost = 0.20;
        description = "A plain Pizza"; 
    }
    string getDescription() const
    {
        return description;
    }
    double getCost() const
    {
        return cost;
    }
};

// Toppings implements the interface and contains a pizza 
class Toppings : public Pizza
{
private: 
    Pizza* abc; 
public:
    Toppings(Pizza * a)
    {
        this->abc = a; 
    }
    string getDescription() const
    {
        return this->abc->getDescription();
    }
    double getCost() const
    {
        return this->abc->getCost();
    }
};

class ToppingTypeOne : public Toppings
{
public:
    ToppingTypeOne(Pizza * a) : Toppings(a)
    {
        // Call parent constructor above
    }
    string getDescription() const
    {
        return Toppings::getDescription() + ", Topping One";
    }
    double getCost() const
    {
        return Toppings::getCost() + 0.50;
    }
};

class ToppingTypeTwo : public Toppings
{
public:
    ToppingTypeTwo(Pizza * a) : Toppings(a)
    {
        // Call parent constructor above
    }
    string getDescription() const
    {
        return Toppings::getDescription() + ", Topping Two";
    }
    double getCost() const
    {
        return Toppings::getCost() + 0.35;
    }
};

int main(void) 
{
    Pizza* basicPizza = new ToppingTypeTwo(new ToppingTypeOne(new PlainPizza()));
    cout << "Pizza is: " <<  basicPizza->getDescription() << endl;
    cout << "Total Cost: " << basicPizza->getCost() << endl;
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 2 Flyweight Design Pattern
//-------------------------------
// Flyweight object -> Objects that do not contain a lot of data => light weight => can fly
// To minimize memory use by sharing as much data as possible
// Share some part of the object state
// Intrinsic State => State that can be shared
// Extrinsic State => State that is unique to each object
// Used when data is constant (intrinsic data) in a lot of different objects
// A client class for containing extrinsic data and pass the extrinsic data to flyweight objects as necessary 
// Flyweight object contains intrinsic data
// note: Flyweight object must be immutable so that sharing of data is safe during concurrency
// Classes:
// i) Flyweight Interface: How flyweight object retrieves extrinsic data and act on it
// ii) ConcreteFlyweight : Implementation of Flyweight interface storing only intrinsic data
// iii) FlyweightFactory : Create and manage sharing of flyweight objects, garbage collection of flyweight objects
// iv) Client: Keeps references to flyweight objects needed, stores/computes extrinsic data, can only obtain flyweight objects using FlyweightFactory
//
// Application: Text editor, each alphabet's data to draw on a screen is stored in a class
//              Then, text editor only has to keep track of the position alphabet to be drawn instead of how exactly to draw the alphabet
// Application: Cache -> Load all images at once and store inside Flyweight objects, refer to Flyweight objects later
// Problem: Longer runtime as need to compute extrinsic data and retrieve intrinsic data from client
//-------------------------------
/* // 
#include <map> 
#include <string>
#include <iostream>
using namespace std;

// Define external data to pass in to it (in this case, int x and int y)
class FlyweightInterface
{
public:
    virtual void draw(int x, int y) const = 0;
};

// Implement FlyweightInterface including intrinsic data
class ConcreteFlyweight : public FlyweightInterface
{
private:
    string color; // intrinsic data that is shared
public:
    ConcreteFlyweight(string _color)
    {
        this->color = _color;
    }
    void draw(int x, int y) const
    {
        cout << "Drawing an object with color: " << color << " and positions x:" << x << " y:" << y << endl;
    }
};

class FlyweightFactory
{
private:
    // Maintains existing ConcreteFlyweight objects and returns them as necessary 
    // Mistake: Must also declare the shared hashtable of objects to be static
    static map<string, ConcreteFlyweight*> mappings;

    // Needed to initialize static map in C++ 
    static map<string, ConcreteFlyweight*> initMap()
    {
       map<string, ConcreteFlyweight*> temp;
       temp["none"] =  new ConcreteFlyweight("none");
       return temp;
    }
public:
    static ConcreteFlyweight* getFlyWeight(string color)
    {
        ConcreteFlyweight* flyObj = mappings[color];
        // If flyObj returns NULL
        if(!flyObj)
        {
            cout << "Creating new flyweight object with color: " << color << endl;
            flyObj = new ConcreteFlyweight(color);
            mappings[color] = flyObj;
        }
        else 
        {
            cout << "Using created flyweight object" << endl;
        }
        return flyObj;
    }
};

// IMPORTANT!
// Mistake: Must initialize static members
// Thus, must define initMap() function privately for initialization of static map
map<string, ConcreteFlyweight*> FlyweightFactory::mappings = initMap();

int main(void)
{
    // Client
    ConcreteFlyweight* blueRect = FlyweightFactory::getFlyWeight("blue");
    blueRect->draw(3, 5);
    blueRect->draw(7, 8);
    ConcreteFlyweight* redRect = FlyweightFactory::getFlyWeight("red");
    redRect->draw(1,2);
    blueRect->draw(4, 6);
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 3 Adapter Design Pattern
//-------------------------------
// To allow 2 incompatible interfaces to work together. 
// Used when client expects a certain interface
// All classes must implement every method defined by the shared interface
// 
//-------------------------------
/* //
#include <string>
#include <iostream>
using namespace std;

// Target Interface
// note: This is what the client expects to see
class TargetInterface
{
public:
    virtual void attackSwords() const = 0; 
    virtual void defendShields() const = 0; 
};

// Implementation of Client Interface
class OldWeapons : public TargetInterface
{
public:
    void attackSwords() const
    {
        cout << "Attack with Swords" << endl;
    }
    void defendShields() const 
    {
        cout << "Defend with Shields" << endl;
    }
};

// Implementation of Actual Interface that exists
class ActualInterface
{
public:
    void attackBombs() 
    {
        cout << "Attack with Bombs" << endl;
    }
    void defendTowers()
    {
        cout << "Defend with Towers" << endl;
    }
};

class Adapter : public TargetInterface
{
private:
    ActualInterface* act; 
public:
    Adapter(ActualInterface* a)
    {
        act = a;
    }
    void attackSwords() const
    {
        act->attackBombs();
    }
    void defendShields() const
    {
        act->defendTowers();
    }
};

int main(void)
{
    ActualInterface* latest = new ActualInterface;
    Adapter* adapt = new Adapter(latest);
    adapt->attackSwords(); // note: It calls the bombs instead of sword
    adapt->defendShields(); // note: It calls the towers instead of shields
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 4 Proxy Design Pattern
//-------------------------------
// Create a wrapper for high time/space complexity objects, and get them only when needed
// Defer full cost of creation until we need the actual object. 
// Proxy => A place holder for an expensive object
// Application: Copy on write (Copying a large object takes a long time, if its read only, then use flyweight)
//              Only when you wanna write it (change it to be unique, then you can copy it)
// Application: Garbage Collection Automation (Reference Counting Pointer)
//              Proxy keeps a reference count to an actual object being read, when no more pointers 
//              points to that object, delete it from memory as it is no longer needed
// Application: Large Files
//      Images in Webpages, (images in webpages take long time to load, so put a proxy(placeholder) 
//      first and load them later only when the user has scrolled down to them and it is needed
// Application: Security
//      Limit access to actual class based on security
//  Application: Lock
//      Ensure current thread has a lock before accessing a resource
//-------------------------------
/* //
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

// Interface to Proxy an actual object, known as Subject
// Need to be implemented by both actual object and proxy object
class ProxyInterface
{
public:
    virtual void drawImage() = 0;
};

class ActualImage : public ProxyInterface
{
private:    
    // The actual image
    double** image; 
    int N; // specific only for this example
public:
    // Creating an actual image is an expensive process
    ActualImage(string pathToImage)
    {
        cout << "Loading image from " << pathToImage << endl;
        N = 3;
        image = (double **) malloc(sizeof(double*) * N); 
        for(int i = 0; i < N; i++)
        {
            image[i] = (double *) malloc(sizeof(double) * N);
        }
        for(int i = 0; i < N;i++)
        {
            for(int j = 0; j < N; j++)
            {
                image[i][j] = i-j;
            }
        }
    }
    void drawImage()
    {
        for(int i = 0; i < N;i++)
        {
            for(int j = 0; j < N; j++)
            {
                cout << image[i][j] << " ";
            }
            cout << endl;
        }
    }
};

class ProxyImage : public ProxyInterface
{
private:
    // ProxyImage must contain a reference to ActualImage
    ActualImage* placeHolder; 
    string pathToImage; // ProxyImage need to contain data to load ActualImage only when necessary. This is like temporary small data needed for loading 
public:
    ProxyImage(string _pathToImage) 
    {
        this->pathToImage = _pathToImage;
        this->placeHolder = NULL;
    }
    void drawImage()
    {
        // Now only create image when needed
        placeHolder = new ActualImage(pathToImage);
        placeHolder->drawImage();
        delete placeHolder;
    }
};

int main(void)
{
    string imagePath = "data/img.jpg";
    // Create a proxy image, fast operation
    cout << "Creating Proxy Image" << endl;
    ProxyInterface* a = new ProxyImage(imagePath);
    cout << "Drawing Proxy Image" << endl;
    // Draw proxy image, slow operation as it only creates the actual image as needed now
    a->drawImage();
    return 0;
}    
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 5 Composite Design Pattern
//-------------------------------
// To represent part-whole hierarchies 
// Can structure data, or represent inner working of every part of an object individually
// Allows a client on running methods on both single objects and composite objects (composed of many single objects and/or composite objects) the same way
// Component Interface => Interface for all objects including composite objects. 
//                      Allows accessing components recursively
//  Primitive/Leaf => Represent end points of the composition
//  Composite => Represent a component that may have children
//  note: Both primitive and composite needs to be handled differently, but on Component Interface, they are called the same
// Application: e.g. Computer Graphics project where you multiply the matrix recursively along the tree. 
//-------------------------------
/* //
#include <vector> 
#include <string>
#include <iostream>
using namespace std;

// Component Interface
class Component
{
public:
    virtual void traverse() const = 0;
};

class Primitive : public Component
{
private:
    int value;
public: 
    Primitive(int _value) 
    {
        this->value = _value;
    }
    void traverse() const
    {
        cout << value << " ";
    }
};

class Composite : public Component
{
private:
    int value;
    vector<Component *> vec; // note: It is Component to be able to contain either Primitive or another Composite
public:
    Composite(int _value)
    {
        value = _value;
    }
    void traverse() const
    {
        cout << value << " ";
        for(int i = 0 ; i < vec.size() ; i++)
        {
            vec[i]->traverse();
        }
    }
    // Mistake: Used add Composite* instead of add Component * here, then it couldn't add Primitive*
    void add(Component* a) 
    {
        vec.push_back(a);
    }
};


// Can have further classes defined inside Composite itself
class Row : public Composite
{
public:
    Row(int val) : Composite(val) {}
    void traverse() const
    {
        cout << "Row:"; 
        // Call parent's traverse
        Composite::traverse();
    }
};

class Col : public Composite
{
public:
    Col(int val) : Composite(val) {}
    void traverse() const
    {
        cout << "Col:"; 
        // Call parent's traverse
        Composite::traverse();
    }
};

int main(void)
{
    Row * first = new Row(1);
    Col * second = new Col(2);
    Col * third = new Col(3);
    Row * fourth = new Row(4);
    Row * fifth = new Row(5);
    first->add(second);
    first->add(third);
    third->add(fourth);
    third->add(fifth);
    // Add leaves
    first->add(new Primitive(6));
    second->add(new Primitive(7));
    third->add(new Primitive(8));
    fourth->add(new Primitive(9));
    fifth->add(new Primitive(10));
    // note: It does a DFS
    first->traverse();
    // 1-6
    // |\
    // 2 3-8
    // | |\
    // 7 4 5
    //   |  \
    //   9   10
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
// 21 Facade Design Pattern
// TODO: Too simple, implement later, you kind of understand it
//-------------------------------
// To create a simple interface for users
// Application: Withdraw(50)
//          - Enter clientID and password
//          - Authenticate
//          - Check  Balance
//          - Give out 50  & deduct from account
//          - Receipt
//-------------------------------
/* 
#include <string>
#include <iostream>
using namespace std;

int main(void)
{
    return 0;
}

// */
//---------------------------------------------------------------------------------------------------------------------------------
// 22 Iterator Design Pattern
//-------------------------------
// Basically same as C++ Iterators
// Lets you iterate through different representations without knowing how the representations work
// Therefore, it decouples Algorithms with the Data Structures 
// The algorithm runs on the iterators, the iterators handle iterating differently on different data structures and apply that algorithm to them.
// Iterator allows a same way to access a different collection of objects
// Thus, don't need to know what data structure is being used when implementing an algorithm. 
// But of course, you need to implement iterators for each different data structure that allows the algorithm to call them
// In addition, you can also traverse the same data structure in a different order using iterators
// Iterator keeps track of its own traversal state, therefore, you can have more than 1 iterator running simultaneously.

// Example Application:
//          Different iterators to traverse a BST for (preorder, inorder, postorder)
// Note: You won't be able to modify the container for those objects as you only have access to each individual elements separately.
//       Just means you can only do the foreach loop instead of the normal C style for loop
//-------------------------------
/* //
#include <string>
#include <iostream>
using namespace std;

class SongInfo
{
private:
    string songName;
    string bandName;
    int yearReleased;
public:
    SongInfo(string newSongName, string newBandName, int newYearReleased)
    {
        songName = newSongName;
        bandName = newBandName;
        yearReleased = newYearReleased;
    }
    string getSongName() {return songName;}
    string getBandName() {return bandName;}
    int getYearReleased() {return yearReleased;}
};

int main(void)
{
    return 0;
}
// */
//---------------------------------------------------------------------------------------------------------------------------------
