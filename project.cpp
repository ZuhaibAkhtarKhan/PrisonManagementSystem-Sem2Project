#include<iostream>
using namespace std;


/*write it after taking an integer type input such as
    cin>>num;
    intcheck();
    but you have to run a do while loop to keep asking for a correct input
*/
void intCheck(); //defined below main used for integer type input validation, program wont crash if user enters alphabets instead of numbers
bool  isIntValid;
class Prison{
    bool isPrisonerIdTaken[101]={false}; //set the value to true at index equal to id of prisoner when a prisoner is being added
    Prisoner prisoners[101]; 
    Cell cells[51]; //we can go from 1 to 50(ignore 0) and can accomodate 100 prisoner

    public:
    void mainMenu(){
        /*  says welcome
            prints the number of prisoner(other staff will be added later)
            then the following menu;
            1.Prisoner record management (Add, Edit, Search, Release)
            2.Cell and block assignment
            3.Guard schedule management
            4.Visitor management
            5.Search prisoner by ID
            6.exit

            then call the relevant functions currently  only prionser record management will be made
*/
    }
    void prisonerRecordManagement(){
        /*
            print menu;
            1.add prisoner
            2.release prisoner
            3.modify prisoner data
            4. search for a prisoner
            5. return to mainmenu

            then just call the relevant functions givem below
            */
    }
    void addPrisoner(){
        //ask for all  input, make sure to add input validations
        //id should be greater than 0 and less than 100 as thats then capacity of prisoners currently
        //before adding prisoner itirate through the isPrisonerIdTaken[100] array to check if the specific id is taken or available,if value at index=givenid is true then taken and run the loop again for asking different id
        //before adding the data of prioner,set the value to true at index equal to id of prisoner in the array isPrisonerIdTaken[100] so that we know that id is occupied now
        //store all data at index equal to prisoner's id as it will help us in finding out prioners easily by their id
        //for public attributes--> prisoners[id].name=xyz;
        //for private attributes--> prisoners[id].setId(x);
        // for cell assignment use for loop for cells[51] arrray and keep calling the setOccupant() fun, if occupant is placed in a cell then store that index in int prisonerCell attribute
        // for block assignment ask user to choose  A,B,C or D and then assign it to prisonerBlock which is an enum type
        //retturn to mainmenu by calling mainmenu()
    }
    void releasePrisoner(){
        //ask for id of priosner
        // set value to false in the isPrisonerTaken[id] array at index=id so now the id is available  for  other prisoner.
        // set the int datatypes to 0 and the string datatypes to " "
        //retturn to mainmenu by calling mainmenu()
    }
    void modifyPrisonerData(){
        //show menu of data to choose what they wannna change
        /*  do not change cell or block here, there will be a separate section for that
            1.name 
            2.id 
            and so on
            at  last n.return to prisoner menu i.e prisonerRecordManagement()
        */
        //after choosing ask for  that newdata and change it accordingly
        //retturn to mainmenu by calling mainmenu()
    }
    void searchPrisoner(){
        //ask for id 
        //iterate over isPrisoneridTaken[] array to check if prisoner exist at that id or not, if yes print his details in a good format
        // if not say prisoner at that id doesnot exist
        // ask wanna search another id or wanna move back to mainmenu
        //retturn to mainmenu by calling mainmenu()
    }
};

class Person{
    public:
    string name;
    int age;
    protected:
    int id;
};

class Prisoner:public Person{
    private:
    int sentence;

    public:
    static int numOfPrisoners; //add to 1 each time when prioner is added, delete 1 when priosner is removed
    string crime;
    int prisonerCell;
    Block prisonerBlock;
    string dateOfArrest;
    void setSentence(int sentence){};
    void setId(int id){};
    void changeSentence(int newSentence){}
    void changeId(int newId){}
};
int Prisoner::numOfPrisoners = 0;

//each prisoner will be assigned a block
enum Block{
    A=1,B,C,D
};
//each prisoner will be assigned a cell in Prison class
class Cell{
    int occupant1 = 0;
    int occupant2 = 0;
    public:
    void setOccupant(int id){
        if(occupant1==0){
            occupant1 = id;
        }
        else if(occupant2 == 0){
            occupant2 = id;
        }
        else{
            cout<<"The cell is full, Try another"<<endl;
        }
    }
};


int main(){
    Prison prison;
    // prison.mainMenu();   starts from here and then goes from function to function


    
    return 0;
}


void intCheck()
{
    isIntValid = true; //declared globally
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << ">>> Please Enter valid input <<<" << endl;
        isIntValid = false; //use this to control your dowhile loop
    }
}