
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

void Prison::mainMenu(){
    do{
        cout<<"\n\n==============================================================================="<<endl;
        cout<<"\tWELCOME TO |||| A Z K A B A N |||| (From Where Escape is Impossible)"<<endl;
        cout<<"==============================================================================="<<endl;
        cout<<"Total prisoners: "<<Prisoner::numOfPrisoners<<endl;
        cout<<"Total Guards: "<<Guard::noOfGuards<<endl;
        cout<<"Total Officers: "<<Officer::noOfOfficers<<endl;
        cout<<"==============================="<<endl;
        cout<<"Choose Action(1 to 6): "<<endl;
        cout<<"1.Prisoner record management\n2.Cell and Block Assignment\n3.Guard Schedule management\n4.Visitor management\n5.Search Prisoner By ID\n6.Exit"<<endl;
        int option;
        cin>>option;
        if(intCheck()==false) continue;
        switch (option)
        {
        case 1:
            prisonerRecordManagement();
            break;
        case 2:
            cellAndBlockAssignment();
            break;
        case 3:
            guardManagement();
            break;
        case 4:
            visitorManagment();
            break;
        case 5:
            searchPrisoner();
            break;
        case 6:
            for(int i=1;i<=100;i++){ //release the dynamically allocated memory
                delete[] prisoners[i].visitorHistory;
            }
            exit(0); //end whole program
            break;
        
        default:
            cout<<"invalid number entered. Please enter (1 to 6)."<<endl;
            break;
        }
    }while(true);

}

void Prison::prisonerRecordManagement(){
    int tempotion;
    while (true)
    {  
        cout<<"\n================================================"<<endl;
        cout<<"\tPrisoner Record Management"<<endl;
        cout<<"================================================"<<endl;
        cout<<"Choose one option"<<endl;
        cout<<"1.Add prisoner\n2.Release prisoner\n3.Modify Prisoner Data\n4.Search prisoner\n5.Go back"<<endl;
        cin>>tempotion;
        switch(tempotion){
            case 1:
                addPrisoner();
                break;
            case 2:
                releasePrisoner();
                break;
            case 3:
                modifyPrisonerData();
                break;
            case 4:
                searchPrisoner();
                break;
            case 5:
                mainMenu();
                break;
            default:
                cout<<"Invalid input"<<endl;
                break;        
        }
    }
    
}


void Prison::addPrisoner(){
    //getting ID first
    int tempid;
    while (true)
    {
        cout<<"ENter Prisoner's ID(1-100): ";
        cin>>tempid;
        if(intCheck()==false || tempid<1 || tempid>100){  //intcheck() returns false if input was other than integer
            continue;
        }else{
            if(isPrisonerIdTaken[tempid]==true){
                cout<<"Prisoner with this ID already exists."<<endl;
                continue;
            }else{
                isPrisonerIdTaken[tempid]=true;
                prisoners[tempid].id=tempid;
                break;
            }
        }
    }

    //getting name
    string tempname;
    cin.ignore();
    while (true)
    {
        cout<<"Enter name of the prisoner: ";
        getline(cin,tempname);
        if(stringcheck(tempname)==false){
            cout<<"Name should not contain integers and should not be empty."<<endl;
            continue;
        }
        else{
            prisoners[tempid].name=tempname;
            break;
        }   
    }

    //getting Age
    int tempage;
    while (true)
    {
        cout<<"Enter age of the prisoner: ";
        cin>>tempage;
        if(intCheck()==false || tempage<1){
            continue;
        }else{
            prisoners[tempid].age=tempage;
            break;
        }     
    }

    //what crime did he do
    cout<<"What crime did Prisoner do? ";
    cin.ignore();
    getline(cin,prisoners[tempid].crime);
        
    //date of arrest
    cout<<"Date of Arrest (eg: 12 April 2025): ";
    getline(cin,prisoners[tempid].dateOfArrest);
    
    //sentence
    int tempSentence;
    while (true)
    {
        cout<<"How many years is Prisoner sentenced(only an integer)? ";
        cin>>tempSentence;
        if(intCheck()==false || tempSentence<1){
            continue;
        }else{
            prisoners[tempid].sentence=tempSentence;
            break;
        }
    }
    
    //cell assignment
    for(int i=1;i<=50;i++){
        if(cells[i].setOccupant(tempid)==true){
            prisoners[tempid].prisonerCell=i;
            cout<<"Prisoner assigned to cell no: "<<i<<endl;
            break;
        }else{continue;}
    }
    //block  assignment (A=1-20 cells, B=20-30 cells, C=30-40 cells, D=40-50 cells)
    if(prisoners[tempid].prisonerCell > 0 && prisoners[tempid].prisonerCell<=20){
        prisoners[tempid].prisonerBlock=A;
        cout<<"Prisoner sent to Block: A"<<endl;
    }
    else if(prisoners[tempid].prisonerCell > 20 && prisoners[tempid].prisonerCell<=30){
        prisoners[tempid].prisonerBlock=B;
        cout<<"Prisoner sent to Block: B"<<endl;
    }
    else if(prisoners[tempid].prisonerCell > 30 && prisoners[tempid].prisonerCell<=40){
        prisoners[tempid].prisonerBlock=C;
        cout<<"Prisoner sent to Block: C"<<endl;
    }
    else if(prisoners[tempid].prisonerCell > 40 && prisoners[tempid].prisonerCell<=50){
        prisoners[tempid].prisonerBlock=D;
        cout<<"Prisoner sent to Block: D"<<endl;
    }
    else{
        cout<<"Error in block assignment."<<endl;
    }
    
    //Add one to total no of prisoners
    Prisoner::numOfPrisoners++; 
    
    cout<<"=============================="<<endl;
    
    
    
}


void Prison::releasePrisoner(){
    bool runAgain; // for dealing with while loop
    do{
        runAgain=false; //by default its false
        cout<<"Enter the ID of prisoner to be removed(1-100): "<<endl;
        int tempId;
        cin>>tempId;
        if(intCheck() == false || tempId<1 || tempId>100){   //this checks if other than integer type is enetered
            runAgain=true;
            continue;
        }else{
            if(isPrisonerIdTaken[tempId] == true){
                isPrisonerIdTaken[tempId]=false;  //indicates this slot is empty now for any other prsioner to be added
                cout<<"\nPrisoner "<<prisoners[tempId].name<<" (ID = "<<prisoners[tempId].id<<") has been released. "<<endl;
                Prisoner::numOfPrisoners--; //remove one from total
                prisoners[tempId].visits=0; //change visits to zero now
                delete[] prisoners[tempId].visitorHistory; //delete old visitorHistory which is an array of string
                prisoners[tempId].visitorHistory = new string[0]; //initiate a new array with size 0
                //empty the prisoner's cell
                if(cells[prisoners[tempId].prisonerCell].occupant1 == tempId){
                    cells[prisoners[tempId].prisonerCell].occupant1=0;
                }else if(cells[prisoners[tempId].prisonerCell].occupant2 == tempId){
                    cells[prisoners[tempId].prisonerCell].occupant2=0;
                }else{cout<<"error in emptying cell"<<endl;}
                
            }else{
                cout<<"Sorry, A Prsioner with this Id doesnot exist.\nPress any key to tryagain or enter (back) to go back."<<endl;
                string tempstr;
                cin>>tempstr;
                if(toLower(tempstr) == "back"){return;}
                else{runAgain=true;}
            }
        }
        
    }while(runAgain);
}


void Prison::modifyPrisonerData(){
    int tempid;
    while (true)
    {
        cout << "Enter the ID of the prisoner you want to modify(or enter 0 to go back): ";
        cin >> tempid;
        if(intCheck() == false || tempid<1 || tempid>100){
            if(tempid==0){
                return;
            }else{continue;}
        }
        else if(!isPrisonerIdTaken[tempid]) {
            cout << "No prisoner exists with this ID."<<endl;
            continue;
        }else{break;}
    }
    
    int choice;
    do {
        cout << "\nWhat do you want to modify?\n";
        cout << "1. Name\n";
        cout << "2. Age\n";
        cout << "3. Sentence Duration\n";
        cout << "4. Crime\n";
        cout << "5. Date of Arrest\n";
        cout << "6. Go back\n";
        cout << "Enter choice: ";
        cin >> choice;
        if(intCheck() == false) continue;

        switch (choice) {
            case 1: {
                cout << "Enter new name: ";
                string tempname;
                cin.ignore();
                getline(cin,tempname);
                if(stringcheck(tempname)==false){
                    cout<<"Name should not be empty and should not contain integers."<<endl;
                    continue;
                }else{
                    prisoners[tempid].name = tempname;
                    cout << "Name updated.\n";
                }
                break;
            }
            case 2: {
                cout << "Enter new age: ";
                int tempage;
                cin >> tempage;
                if (intCheck()==false || tempage<1 || tempage>100){
                    cout<<"Invalid age entered."<<endl;
                    continue;
                }else{
                    prisoners[tempid].age=tempage;
                    cout<<"Age updated"<<endl;
                }
                break;
            }
            case 3: {
                int newSentence;
                cout << "Enter new sentence duration (in years): ";
                cin >> newSentence;
                if (intCheck()==false) {
                    continue;
                }else{
                    prisoners[tempid].sentence = newSentence;
                    cout << "Sentence updated.\n";
                }
                break;
            }
            case 4: {
                cout << "Update crime: ";
                cin.ignore();
                getline(cin,prisoners[tempid].crime);
                cout << "Crime updated.\n";
                break;
            }
            case 5: {
                cout << "Update date of arrest(eg; 12 April 2022): ";
                getline(cin,prisoners[tempid].dateOfArrest);
                cout << "Date of arrest updated.\n";
                break;
            }
            case 6: {
                return;
                break;
            }
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (true);
}


void Prison::searchPrisoner(){
    bool runAgain;
    do{
        runAgain=false;
        cout<<"ENter the ID of prisoner(1-100): "<<endl;
        int tempId;
        cin>>tempId;
        if(intCheck()==false || tempId<1 || tempId>100){
            runAgain=true;
            continue;
        }else{
            if(isPrisonerIdTaken[tempId]==true){
                cout<<"\n========================================="<<endl;
                cout<<"\tPRISONER FOUND"<<endl;
                cout<<"Name: "<<prisoners[tempId].name<<endl;
                cout<<"ID: "<<prisoners[tempId].id<<endl;
                cout<<"Age: "<<prisoners[tempId].age<<endl;
                cout<<"Date of Arrest: "<<prisoners[tempId].dateOfArrest<<endl;
                cout<<"Sentence: "<<prisoners[tempId].sentence<<endl;
                cout<<"Crime: "<<prisoners[tempId].crime<<endl;
                cout<<"Cell Allocated: "<<prisoners[tempId].prisonerCell<<endl;
                switch(prisoners[tempId].prisonerBlock){  // prisonerBlock is an enumm type so thats why
                    case 1:
                        cout<<"Block Allocated: A"<<endl;
                        break;
                    case 2:
                        cout<<"Block Allocated: B"<<endl;
                        break;
                    case 3:
                        cout<<"Block Allocated: C"<<endl;
                        break;
                    case 4:
                        cout<<"Block Allocated: D"<<endl;
                        break;
                    default:
                        cout<<"Error"<<endl;
                        break;
                }
                cout<<"========================================="<<endl;
            }else{
                cout<<"\nA prisoner with ID: "<<tempId<<" doesnot exist.\npress any key to tryAgain OR enter (back) to go back"<<endl;
                string tempstr;
                cin>>tempstr;
                if(toLower(tempstr) == "back"){return;}
                else{runAgain=true;}
            }
        }
    }while(runAgain);
}

void Prison::changeCell(int tempid){
    int newcell;
    while (true)
    {
        cout<<"Enter new cell(or enter 0 to go  back): ";
        cin>>newcell;
        if(intCheck()==false || newcell<1 || newcell>50){
            if(newcell==0){
                return;
            }else{
                continue;
            }
        }
        else{
            if(cells[newcell].setOccupant(tempid)==false){ //means that cell is already full
                continue;
            }else{
                // first clear old cell
                int oldcell;
                oldcell = prisoners[tempid].prisonerCell;
                if(cells[oldcell].occupant1==tempid){
                    cells[oldcell].occupant1=0;
                }
                else if(cells[oldcell].occupant2==tempid){
                    cells[oldcell].occupant2=0;
                }

                //now transfer to new cell
                prisoners[tempid].prisonerCell=newcell;

                //block  assignment (A=1-20 cells, B=20-30 cells, C=30-40 cells, D=40-50 cells)
                if(prisoners[tempid].prisonerCell > 0 && prisoners[tempid].prisonerCell<=20){
                    prisoners[tempid].prisonerBlock=A;
                    cout<<"Prisoner sent to Block: A"<<endl;
                }
                else if(prisoners[tempid].prisonerCell > 20 && prisoners[tempid].prisonerCell<=30){
                    prisoners[tempid].prisonerBlock=B;
                    cout<<"Prisoner sent to Block: B"<<endl;
                }
                else if(prisoners[tempid].prisonerCell > 30 && prisoners[tempid].prisonerCell<=40){
                    prisoners[tempid].prisonerBlock=C;
                    cout<<"Prisoner sent to Block: C"<<endl;
                }
                else if(prisoners[tempid].prisonerCell > 40 && prisoners[tempid].prisonerCell<=50){
                    prisoners[tempid].prisonerBlock=D;
                    cout<<"Prisoner sent to Block: D"<<endl;
                }
                else{
                    cout<<"Error in block assignment."<<endl;
                }
                break;
            }
        }
    }
}

void Prison::changeBlock(int tempid){
    string newblock;
    while (true)
    {
        cout<<"Enter new block(A,B,C,D) or enter (back) to go back: ";
        cin>>newblock;
        if(newblock=="A" || newblock=="a"){
            for(int i=1;i<=20;i++){
                if(cells[i].setOccupant(tempid)==true){
                    // first clear old cell
                    int oldcell;
                    oldcell = prisoners[tempid].prisonerCell;
                    if(cells[oldcell].occupant1==tempid){
                        cells[oldcell].occupant1=0;
                    }
                    else if(cells[oldcell].occupant2==tempid){
                        cells[oldcell].occupant2=0;
                    }
                    //now assign new cell
                    prisoners[tempid].prisonerCell=i;
                    prisoners[tempid].prisonerBlock=A;
                    cout<<"Prisoner transfered to Block A."<<endl;
                    return;
                    break;
                }else{
                    continue;
                }
            }
            cout<<"Block A is full. choose another."<<endl;
        }
        else if(newblock=="B" || newblock=="b"){
            for(int i=21;i<=30;i++){
                if(cells[i].setOccupant(tempid)==true){
                    // first clear old cell
                    int oldcell;
                    oldcell = prisoners[tempid].prisonerCell;
                    if(cells[oldcell].occupant1==tempid){
                        cells[oldcell].occupant1=0;
                    }
                    else if(cells[oldcell].occupant2==tempid){
                        cells[oldcell].occupant2=0;
                    }
                    //now  assign new cell
                    prisoners[tempid].prisonerCell=i;
                    prisoners[tempid].prisonerBlock=B;
                    cout<<"Prisoner transfered to Block B."<<endl;
                    return;
                    break;
                }else{
                    continue;
                }
            }
            cout<<"Block B is full. choose another."<<endl;
        }
        else if(newblock=="C" || newblock=="c"){
            for(int i=31;i<=40;i++){
                if(cells[i].setOccupant(tempid)==true){
                    // first clear old cell
                    int oldcell;
                    oldcell = prisoners[tempid].prisonerCell;
                    if(cells[oldcell].occupant1==tempid){
                        cells[oldcell].occupant1=0;
                    }
                    else if(cells[oldcell].occupant2==tempid){
                        cells[oldcell].occupant2=0;
                    }
                    //now assign new cell
                    prisoners[tempid].prisonerCell=i;
                    prisoners[tempid].prisonerBlock=C;
                    cout<<"Prisoner transfered to Block C."<<endl;
                    return;
                    break;
                }else{
                    continue;
                }
            }
            cout<<"Block C is full. choose another."<<endl;
        }
        else if(newblock=="D" || newblock=="d"){
            for(int i=41;i<=50;i++){
                if(cells[i].setOccupant(tempid)==true){
                    // first clear old cell
                    int oldcell;
                    oldcell = prisoners[tempid].prisonerCell;
                    if(cells[oldcell].occupant1==tempid){
                        cells[oldcell].occupant1=0;
                    }
                    else if(cells[oldcell].occupant2==tempid){
                        cells[oldcell].occupant2=0;
                    }
                    //now assign new cell
                    prisoners[tempid].prisonerCell=i;
                    prisoners[tempid].prisonerBlock=D;
                    cout<<"Prisoner transfered to Block D."<<endl;
                    return;
                    break;
                }else{
                    continue;
                }
            }
            cout<<"Block D is full. choose another."<<endl;
        }
        else if(toLower(newblock)=="back"){
            return;
        }
        else{
            cout<<"Invalid input."<<endl;
            continue;
        }
    }

}

void Prison::cellAndBlockAssignment(){
    int tempid;
    while (true)
    {
        cout<<"Enter prisoner's ID(1-100) or enter 0 to go back: ";
        cin>>tempid;
        if(intCheck()==false || tempid<1 || tempid>100 || isPrisonerIdTaken[tempid]==false){
            if(tempid==0){
                return;
            }else{
                if(isPrisonerIdTaken[tempid]==false){
                    cout<<"Prisoner with that ID doesnot exist."<<endl;
                }
                continue;
            }
        }
        else{break;}
    }
    cout<<"Prsioner's current cell: "<<prisoners[tempid].prisonerCell<<endl;
    switch(prisoners[tempid].prisonerBlock){
        case 1:
            cout<<"Prisoner's current block: A"<<endl;
            break;
        case 2:
            cout<<"Prisoner's current block: B"<<endl;
            break;
        case 3:
            cout<<"Prisoner's current block: C"<<endl;
            break;
        case 4:
            cout<<"Prisoner's current block: D"<<endl;
            break;
        default:
            cout<<"default error"<<endl;
            break;
    }
    int tempoption;
    while (true)
    {
        cout<<"1.Change Cell.\n2.Change Block.\n3.Go back.\nchoose(1-3): ";
        cin>>tempoption;
        if(intCheck()==false || tempoption<1 || tempoption>3){
            continue;
        }else{break;}
    }
    switch (tempoption)
    {
    case 1:
        changeCell(tempid);
        break;
    case 2:
        changeBlock(tempid);
        break;
    case 3:
        return;
        break;

    default:
        cout<<"default error."<<endl;
        break;
    }  
}


void Prison::visitorManagment(){
    cout<<"\n=============================================="<<endl;
    cout<<"\tWelcome to Visitor Management: "<<endl;
    cout<<"=============================================="<<endl;
    cout<<"1.See visits history.\n2.Add new visitor's info.\n3.Go back."<<endl;
    int tempoption;
    //input validation
    while(true){
        cout<<"Enter option(1-3): ";
        cin>>tempoption;
        if(intCheck()==false || tempoption<1 || tempoption>3){
            continue;
        }else{break;}
    }
    switch(tempoption)
    {
    case 1:
        showVisitorHistory();
        break;
    case 2:
        addVisitorInfo(); 
        break;  
    case 3:
        return;//back to previous function
        break;  
    default:
        cout<<"default error"<<endl;
        break;
    }

}
void Prison::showVisitorHistory(){
    int tempid;
    while(true){
        cout<<"Enter ID of prisoner(1-100): ";
        cin>>tempid;
        if(intCheck()==false || tempid<1 || tempid>100){
            continue;
        }else{break;}
    }
    if(isPrisonerIdTaken[tempid]==true){
        for(int i=0;i<prisoners[tempid].visits;i++){
        cout<<prisoners[tempid].visitorHistory[i]<<endl;
        }
    }else{
        cout<<"SORRY, Prisoner with that ID doesnot Exist."<<endl;
    }

}
void Prison::addVisitorInfo(){
    int prisonerTempid;
    while (true){
        cout<<"Enter the prisoner's ID (the one who met the visitor): ";
        cin>>prisonerTempid;
        if(intCheck()==false || prisonerTempid<1 || prisonerTempid>100){
            continue;
        }else{break;}
    }
    if(isPrisonerIdTaken[prisonerTempid]==true){
        string tempname;
        string tempdate;
        string relation;
        int visitortempid;

        cout<<"Enter the visitor's Name: ";
        cin.ignore();
        getline(cin,tempname);
        cout<<"Enter the Date of visit: ";
        getline(cin,tempdate);
        while(true){
            cout<<"Enter the visitor's iD(in int): ";
            cin>>visitortempid;
            if(intCheck()==false){
                continue;
            }else{break;}
        }
        
        cout<<"Enter the visitor's relationship with prisoner: ";
        cin.ignore();
        getline(cin,relation);

        //storing visiotr's data and expanding array size dynamically
        prisoners[prisonerTempid].visits++; 
        int newArraySize = prisoners[prisonerTempid].visits;
        string *temphistory = new string[newArraySize]; //create new array with expanded size
        for(int i=0;i<newArraySize-1;i++){
            temphistory[i] = prisoners[prisonerTempid].visitorHistory[i];  //transfer old info to new larger array

        }
        delete[] prisoners[prisonerTempid].visitorHistory;  //delete old array
        prisoners[prisonerTempid].visitorHistory = temphistory;  //assign new array to old pointer
        // add visitors info at the new last index as string
        prisoners[prisonerTempid].visitorHistory[newArraySize-1]= tempname+" {ID = "+to_string(visitortempid)+"} visited "+prisoners[prisonerTempid].name+" {relation = "+relation+"} on "+tempdate;
        cout<<"Thank you, visitor's information added."<<endl;
    }
    else{
        cout<<"SORRY, Prisoner with that ID doesnot exist."<<endl;
    }


}

void Prison::guardManagement(){
    int temOption;
    while (true)
    {
        cout<<"\n=============================================="<<endl;
        cout<<"\tWelcome to Staff and Guards."<<endl;
        cout<<"=============================================="<<endl;
        cout<<"1.Add Officer.\n2.Add Guard.\n3.See Officer list.\n4.See guards list.\n5.Go back."<<endl;
        cout<<"Choose (1-5): ";
        cin>>temOption;
        if(intCheck()==false || temOption<1 || temOption>5){
            continue;
        }else{
            switch (temOption)
            {
            case 1:
                cout<<endl;
                addOfficer();
                break;
            
            case 2:
                cout<<endl;
                addGuard();
                break;
            
            case 3:
                cout<<endl;
                for(int i=0;i<Officer::noOfOfficers;i++){
                    officers[i].performDuty();
                }
                break;
            
            case 4:
                cout<<endl;
                for(int i=0;i<Guard::noOfGuards;i++){
                    guards[i].performDuty();
                }
                break;
            case 5:
                return;
                break;
            default:
            cout<<"default error"<<endl;
                break;
            }
        }
    }
    
}
void Prison::addOfficer(){
    //name input
    string tempname;
    cin.ignore();
    while (true)
    {
        cout<<"Enter name of the Officer: ";
        getline(cin,tempname);
        if(stringcheck(tempname)==false){
            cout<<"Name should not contain integers and should not be empty."<<endl;
            continue;
        }
        else{
            officers[Officer::noOfOfficers].name=tempname;
            break;
        }   
    }
    //id input
    int tempid;
    while (true)
    {
        cout<<"Enter id: ";
        cin>>tempid;
        if(intCheck()==false){
            continue;
        }else{
            officers[Officer::noOfOfficers].id=tempid;
            break;
        }
    }
    //block assignment
    string tempBlock;
    cin.ignore();
    while (true)
    {
        cout<<"Assign Block (A, B, C, D): ";
        getline(cin,tempBlock);
        if(toLower(tempBlock)=="a"){
            officers[Officer::noOfOfficers].block=A;
            break;
        }
        else if(toLower(tempBlock)=="b"){
            officers[Officer::noOfOfficers].block=B;
            break;
        }
        else if(toLower(tempBlock)=="c"){
            officers[Officer::noOfOfficers].block=C;
            break;
        }
        else if(toLower(tempBlock)=="d"){
            officers[Officer::noOfOfficers].block=D;
            break;
        }
        else{
            cout<<"Invalid input."<<endl;
            continue;
        }

    }
    Officer::noOfOfficers++;  
}
void Prison::addGuard(){
    //name input
    string tempname;
    cin.ignore();
    while (true)
    {
        cout<<"Enter name of the Guard: ";
        getline(cin,tempname);
        if(stringcheck(tempname)==false){
            cout<<"Name should not contain integers and should not be empty."<<endl;
            continue;
        }
        else{
            guards[Guard::noOfGuards].name=tempname;
            break;
        }   
    }
    //id input
    int tempid;
    while (true)
    {
        cout<<"Enter id: ";
        cin>>tempid;
        if(intCheck()==false){
            continue;
        }else{
            guards[Guard::noOfGuards].id=tempid;
            break;
        }
    }
    //block assignment
    string tempBlock;
    cin.ignore();
    while (true)
    {
        cout<<"Assign Block (A, B, C, D): ";
        getline(cin,tempBlock);
        if(toLower(tempBlock)=="a"){
            guards[Guard::noOfGuards].block=A;
            break;
        }
        else if(toLower(tempBlock)=="b"){
            guards[Guard::noOfGuards].block=B;
            break;
        }
        else if(toLower(tempBlock)=="c"){
            guards[Guard::noOfGuards].block=C;
            break;
        }
        else if(toLower(tempBlock)=="d"){
            guards[Guard::noOfGuards].block=D;
            break;
        }
        else{
            cout<<"Invalid input."<<endl;
            continue;
        }

    }
    Guard::noOfGuards++; 
}




#endif