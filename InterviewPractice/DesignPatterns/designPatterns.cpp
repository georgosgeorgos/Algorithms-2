/* 
Table of Contents
0. SOLID 
1. Strategy Design Pattern 
2. Observer Design Pattern
3. Factory Design Pattern
5. Singleton Design Pattern

TODO:
4. Abstract Factory Design Pattern
6. Iterator Design Pattern
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
//---------------------------------------------------------------------------------------------------------------------------------
// 1 Strategy Design Pattern 
// - Avoid duplicated code
// - Keep class changes from forcing other class changes
// - don't add methods that are not used by all subclasses
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
#include <string>
#include <iostream>
using namespace std;

// Create an Interface called Flys
class Fly
{
public:
    virtual string fly() = 0;
} ;

// make a subclass for animals that implements the interface Flys
class ItFly : public Fly
{
    string fly()
    {
        return "Fly!!";
    }
};

// make a subclass for animals that implements the interface Flys
class CantFly : public Fly
{
    string fly()
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
// Used when:
// - need many other objects to receive an update when another object changes

// Subject = Publishers
//  - maintain a list of its observers and notify them of any state chnages calling one of their methods
// Observer = Subscribers

// Advantage:
//  - Subject don't have to know anything about Observers
// Disadvantage:
//  - Subject may send updates that don't relate to some Observers to all of them

// In this example:
// Interface : Observer(), Subject()
// Implement Interface: StockObserver(), StockGrabber()
// Each Observer() contains a subject pointer so when it is created, it adds itself
// automatically to the subject's list of observers.
// Similarly, each subject automatically calls each of its list of observers update() method
// when it updates any of its values.
#include <vector> // vector of Observers

#include <iostream>
using namespace std;

// Observer Interface
class Observer
{
public:
    virtual void update(double _ibmPrice, double _applePrice, double _googlePrice) = 0;
};

// Define Iterface
class Subject
{
public:
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

int StockObserver::observerIDTracker = 0; // initialization in CPP file instead of header file!

class StockGrabber : public Subject
{
private:
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

// used when:
// Method returns one of several possible classes that share a common superclass
// Basically, when don't know what class object will be needed
// Centralize class selection code

// For instance,
// Create a new enemy in a game
// RNG picks a random enemy type
// Factory object will return a dynamically created enemy and throw it on the screen


// In this example:
// Parent Class : EnemyShip(), EnemyShipFactory
// Child Class : UFOEnemyShip(), RocketEnemyShip()
// GrandChild Class: BigUFOShip
// note: EnemyShipFactory basically returns a type of EnemyShip since you can't have a class returning itself.

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

// gloabl functions

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
// 4 Abstract Factory Design Pattern
// refer to Derek Banas's video on youtube

// Like a factory, but everything is encapsulated
// This includes:
// - Method that orders the object
// - Fatory that builds the object
// - Final Objects
// - Final object that contain objects that use the Strategy Pattern
//---------------------------------------------------------------------------------------------------------------------------------
// 5 Singleton Design Pattern

// used when can only instantiate 1 object from a class
// Examples: File Logging, Global Clock/Counter
// Logging is acceptable for good design as it doesn't affect execution of code.

// In this example:
// Parent Class : SingletonCounter()
// note: This demonstrates how to implement a global counter for all classes that needs to
// access a global counter/clock  in a game for example as it should be the same clock.
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
// 6 Iterator Design Pattern

// used to access different collections of Objects
// Treat iterator the same for Array, HashTable, Queue, BST, etc.
// Can write polymorphic code as treat each collection of objects the same way
// as each collection of objects implement the same interface.
// Also, you won't be able to modify the container for those objects as you only have access to
// each individual elements separately.
//----------------------------- ---------------------------------------------------------------------------
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
