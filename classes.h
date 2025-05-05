
#ifndef CLASSES_H
#define  CLASSES_H
#include<iostream>
using namespace std;

// SOME USEFULL FUNCTIONS USED THROUGHOUT PROGRAM
bool intCheck(); //defined below main used for integer type input validation, program wont crash if user enters alphabets instead of numbers
string toLower(string s); //converts capital to lower
bool stringcheck(string &value); // checks if a name is valid or not (if name has integers then its invalid)



class Person{
    public:
    string name;
    int age;
    protected:
    int id;
    
};



//for block assignment (if cell of prisoner is from 1-20 set A, if 20-30 set B,if 30-40 set C,40-50 set D) and then assign it to prisonerBlock
enum Block{
    A=1,B,C,D
};




//an array of Cell with size 50 has been initialised in Prison class
class Cell{
    //each cell can accomodate 2 prisoners in below variables
    int occupant1 = 0;
    int occupant2 = 0;
    public:
    friend class Prison;
    //this function asssigns cell to a prsioner and returns true if empty cell is available, or false if no cell is empty
    bool setOccupant(int id){
        if(occupant1==0){
            occupant1 = id; //occupant1 got assigned
            cout<<"cell has been assigned to occupant"<<endl;
            return true;
        }
        else if(occupant2 == 0){
            occupant2 = id; //occupant2 got assigned
            cout<<"cell has been assigned to occupant"<<endl;
            return true;
        }
        else{
            cout<<"The cell is full, Try another"<<endl;
            return false;
        }
    }
};



class Prisoner:public Person{
    private:
    int sentence;
    int visits=0;
    string *visitorHistory = new string[visits];

    public:
    friend class Prison;
    static int numOfPrisoners; //add to 1 each time when prioner is added, delete 1 when priosner is removed
    string crime;
    int prisonerCell;
    Block prisonerBlock;
    string dateOfArrest;
    void setSentence(int sentence){this->sentence=sentence;}
    void setId(int id){this->id=id;}
};
int Prisoner::numOfPrisoners = 0; //initialise total number of prisoners with 0





//guards section
class Staff:public Person{
    friend class Prison;
    public:
    Block block;
    virtual void performDuty()=0;
};


class Officer:public Staff{
    public:
    friend class Prison; //give access to Prison class
    static int noOfOfficers;
    void performDuty() override{
        cout<<"Officer "<<name<<" {Id = "<<id<<"} is currently working in his office at block: ";
        switch (block)
        {
        case 1:
            cout<<"A\n";
            break;
        case 2:
            cout<<"B\n";
            break;
        case 3:
            cout<<"C\n";
            break;
        case 4:
            cout<<"D\n";
            break;
        
        default:
            cout<<"error at block"<<endl;
            break;
        }
    }
};
int Officer::noOfOfficers=0;


class Guard:public Staff{
    public:
    friend class Prison; //give access to Prison class
    static int noOfGuards;
    void performDuty() override{
        cout<<"Guard "<<name<<" {Id = "<<id<<"} is currently patrolling at block: ";
        switch (block)
        {
        case 1:
            cout<<"A\n";
            break;
        case 2:
            cout<<"B\n";
            break;
        case 3:
            cout<<"C\n";
            break;
        case 4:
            cout<<"D\n";
            break;
        
        default:
            cout<<"error at block"<<endl;
            break;
        }
    }
};
int Guard::noOfGuards=0;



class Prison{
    bool isPrisonerIdTaken[101]={false}; //set the value to true at index equal to id of prisoner when a prisoner is being added
    Prisoner prisoners[101];  //ignore index 0, and we can accomodate 100 prisoner
    Cell cells[51]; //we can go from 1 to 50(ignore 0) and can accomodate 100 prisoner
    Guard guards[20];
    Officer officers[10];
    public:
    void mainMenu();
    void prisonerRecordManagement();
    void addPrisoner();
    void releasePrisoner();
    void modifyPrisonerData();
    void searchPrisoner();
    void changeCell(int tempid);
    void changeBlock(int tempid);
    void cellAndBlockAssignment();
    void visitorManagment();
    void showVisitorHistory();
    void addVisitorInfo();
    void guardManagement();
    void addOfficer();
    void addGuard();

    
};






#endif