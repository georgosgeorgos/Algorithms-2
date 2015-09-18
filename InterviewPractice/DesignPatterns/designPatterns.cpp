/* 
Table of Contents
0. SOLID 
//-------------------------------
A) Creational Design Pattern
//-------------------------------
3. Factory Design Pattern
    - To create random child class objects in a game. A 'factory' that returns random objects created 
5. Singleton Design Pattern
    - Only 1 object of a particular class 
    - e.g. Global Counter, Logging, Accessing shared resource
6. Builder Design Pattern
    - When Object construction is complicated, takes a long time, has too many variables to construct 
        and when you won't know all variables at once. 
    - You can construct each variable step by step
    - You can construct the objects differently using different classes
7. Prototype Design Pattern
    - When want to create a clone of an object to 'prototype' with it first before reassigning as original
    - e.g. Bank Account transactions 
//-------------------------------
B) Behavioral Design Pattern
//-------------------------------
1. Strategy Design Pattern 
    - Separate method definition from classes
    - This way, each child class can have their own method definition of a specific interface 
    - Application: Sorting (MergeSort may work better in some cases, QuickSort in other cases)
9. Command Design Pattern
    - To be able to queue a set of commands
    - To be ablt to keep track of commands executed
    - To encapsulate a set of methods that are executed in order for a command to execute
    - Application: Client-Server Interface, where commands must be queued and sent over the server to execute an inner method. 
2. Observer Design Pattern
    - Subscriber and Publisher
    - All subscribers are notified whenever a publisher makes a change
11. Template Method Design Pattern
    - TemplateMethod define in mainInterface is how the method structure is gonna work
    - It calls a bunch of abstract submethods that are defined differently in different subclasses
    - Think of template implementation in C++ that allows you to customize the datatypes. 
    - For this, you have a template methods where you can customize the methods inside that template method
    - You can customize local variables by defining abstract methods that returns different local variables
//-------------------------------
C) Structural Design Pattern
//-------------------------------
8. Decorator Design Pattern 
    - To be able to extend functionality inheritance by creating each other recursively, passing in a variable that grows between creations
    e.g. A PlainPizza that you can recursively add in different toppings which adds to the cost
10. Adapter Design Pattern
    - To adapt an existing interface (Target Interface) with a new interface
    - Create an adapter class that maps all existing methods to the new methods 
        that should be called instead
12. Composite Design Pattern
    - Allows a client on running methods on both single objects and composite objects (composed of many single objects and/or composite objects) the same way
    - Component Interface => Interface for all objects including composite objects. 
                             Allows accessing components recursively
    - Primitive/Leaf => Represent end points of the composition
    - Composite => Represent a component that may have children
    - note: Both primitive and composite needs to be handled differently, but on Component Interface, they are called the same
    - Application: e.g. Computer Graphics project where you multiply the matrix recursively along the tree. 
13. Flyweight Design Pattern
    - To save space by sharing data 
//-------------------------------
TODO:
14. State Design Pattern
4. Abstract Factory Design Pattern
21. Facade Design Pattern
22. Iterator Design Pattern
*/ 
//---------------------------------------------------------------------------------------------------------------------------------
// 0 SOLID 
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
//      - Factory Design Pattern
//      - Singleton Design Pattern
//      - Builder Design Pattern
//      - Prototype Design Pattern
// b) Behavioral Design Pattern 
//      - Strategy Design Pattern
//      - Command Design Pattern
//      - Observer Design Pattern
//      - Template Method Design Pattern
//      - Iterator Design Pattern
//      - Mediator Design Pattern
//      - Memento Design Pattern
//      - Visitor Design Pattern
// c) Structural Design Pattern 
//      - Decorator Design Pattern
//      - Adapter Design Pattern
//      - Facade Design Pattern
//      - Composite Design Pattern
//      - Flyweight Design Pattern
//      - Bridge Design Pattern
//  
//---------------------------------------------------------------------------------------------------------------------------------
// 14 State Design Pattern
//-------------------------------
// used when:
//-------------------------------
//
#include <string>
#include <iostream>
using namespace std;

int main(void)
{
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
// 2 Observer Design Pattern
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
// 3 Factory Design Pattern
//-------------------------------
// used when:
// Method returns one of several possible classes that share a common superclass
// Basically, when don't know what class object will be needed
// Centralize class selection code

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
// 5 Singleton Design Pattern
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
// 6 Builder Design Pattern
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
// 7 Prototype Design Pattern
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
// 8 Decorator Design Pattern
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
// 10 Adapter Design Pattern
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
// 11 Template Method Design Pattern
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
    virtual void methodOne() = 0;
    virtual void methodTwo() = 0;
    virtual void methodThree() = 0;
    virtual string getVarStr() = 0;
    // This is the template method 
    // It will always be the same, its just the variables inside it may change
    void mainTemplateMethod() 
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
// 12 Composite Design Pattern
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
// 13 Flyweight Design Pattern
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
