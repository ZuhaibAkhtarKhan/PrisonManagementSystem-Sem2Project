#include<iostream>
#include<algorithm>
using namespace std;

/*write it after taking an integer type input such as
    cin>>num;
    intcheck();
    but you have to run a do while loop to keep asking for a correct input
*/
bool intCheck(); //defined below main used for integer type input validation, program wont crash if user enters alphabets instead of numbers
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// checks if a name is valid or not
bool stringcheck(string &value)
{   
    // Check if string is empty
    if (value.empty())
    {
        return false;
    }else{
        // Check each character if only one is integer, return false
        for (char x : value)
        {
            if (isdigit(x))
            {
                return false;
            }
        } //if false not returned means name is valid
        return true;
    }
}

bool checkcell;

class Person{
    public:
    string name;
    int age;
    protected:
    int id;
    
};

enum Block{
    A=1,B,C,D
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
    void setSentence(int sentence){};
    void setId(int id){};
    void changeSentence(int newSentence){}
    void changeId(int newId){}
};
int Prisoner::numOfPrisoners = 0;

//each prisoner will be assigned a block
//for block assignment (if cell of prisoner is from 1-20 set A, if 20-30 set B,if 30-40 set C,40-50 set D) and then assign it to prisonerBlock

//each prisoner will be assigned a cell in Prison class(cells are from 1-50)
class Cell{
    int occupant1 = 0;
    int occupant2 = 0;
    public:
    bool setOccupant(int id){
        if(occupant1==0){
            occupant1 = id;
            cout<<"cell has been assigned to occupant"<<endl;
            return true;
        }
        else if(occupant2 == 0){
            occupant2 = id;
            cout<<"cell has been assigned to occupant"<<endl;
            return true;
        }
        else{
            cout<<"The cell is full, Try another"<<endl;
            return false;
        }
    }
};


//VISITOR CLASS DERIVED FROM PERSON
// class Visitor:public Person{
//     string date;
//     string time;
//     string relation;
// };



class Prison{
    bool isPrisonerIdTaken[101]={false}; //set the value to true at index equal to id of prisoner when a prisoner is being added
    Prisoner prisoners[101]; 
    Cell cells[51]; //we can go from 1 to 50(ignore 0) and can accomodate 100 prisoner

    public:
    void mainMenu(){
            do{
                cout<<"\t\tWELCOME TO AZKABAN PRISON"<<endl;
                cout<<"Total prisoners: "<<Prisoner::numOfPrisoners<<endl;
                cout<<"Total Guards: "<<endl;
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
                    // guardScheduleManagement();
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
    void prisonerRecordManagement(){
        int tempotion;
        while (true)
        {  
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
    void addPrisoner(){
        //ask for all  input, make sure to add input validations
        int id;
       bool check = false;
       while(!check)
       {
       	cout<<"Enter Prisoner's id: ";
       	cin>>id;
       	if(id>0 && id<=100)
      	{
      		check = true;
		  }
	    else
	    cout<<"Invalid id"<<endl;
		   
	   }
      
        for(int i=0;i<101;i++)
        {
        	if (isPrisonerIdTaken[id]== false)
        	{
        		isPrisonerIdTaken[id] = true;
        		break;
			}
			else{
				cout<<"This id is already taken. Please enter a different id"<<endl;
				cin>>id;
			}
		}
		cout<<"Enter name of the prisoner: ";
		cin>>prisoners[id].name;
		
		cout<<"Enter age of the prisoner: ";
		cin>>prisoners[id].age;

        //for private attributes--> prisoners[id].setId(x);
        
        Cell cell; //dont need this
        for(int i=1;i<51;i++)
        {
        	cell.setOccupant(id);
        	if(checkcell == true)
        	{
        		prisoners[id].prisonerCell = i;
        		break;
			}
            /*instead of above code 
            use if(cells[i].setOccupant(id)==true){
                    prisoners[id].prisonerCell = i;
                }
                as i chnaged the setOccuppant() to directly return true or false so u dont need extra variable
            */

		}
       if(prisoners[id].prisonerCell >=1 && prisoners[id].prisonerCell<=20)
       {
       	prisoners[id].prisonerBlock = A;
	   }
	   else {
	   	if(prisoners[id].prisonerCell>20 && prisoners[id].prisonerCell<=30)
	   	{
  			prisoners[id].prisonerBlock = B;
		   }
	    else if(prisoners[id].prisonerCell>30 && prisoners[id].prisonerCell<=40)
	    {
	    	prisoners[id].prisonerBlock = C;
		}
		else{
			prisoners[id].prisonerBlock = D;
		}
	   }
       
        mainMenu();
    }
    
    void releasePrisoner(){
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
                    cout<<"Prisoner (ID = "<<prisoners[tempId].id<<") has been released. "<<endl;
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
    void modifyPrisonerData(){
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
                    cin >> prisoners[tempid].crime;
                    cout << "Crime updated.\n";
                    break;
                }
                case 5: {
                    cout << "Update date of arrest(eg; 12 April 2022): ";
                    cin >> prisoners[tempid].dateOfArrest;
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

    void searchPrisoner(){
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
                    cout<<"PRISONER FOUND"<<endl;
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
                        default:
                            cout<<"Error"<<endl;
                            break;
                    }
                }else{
                    cout<<"A prisoner with ID: "<<tempId<<" doesnot exist.\npress any key to tryAgain OR enter (back) to go back"<<endl;
                    string tempstr;
                    cin>>tempstr;
                    if(toLower(tempstr) == "back"){return;}
                    else{runAgain=true;}
                }
            }
        }while(runAgain);
    }

    void changeCell(int tempid){
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
                    if(cells[newcell].setOccupant(tempid)==false){
                        continue;
                    }else{
                        prisoners[tempid].prisonerCell=newcell;
                        break;
                    }
                }
            }
    }

    void changeBlock(int tempid){
        string newblock;
        while (true)
        {
            cout<<"Enter new block(A,B,C,D) or enter (back) to go back: ";
            cin>>newblock;
            if(newblock=="A" || newblock=="a"){
                for(int i=1;i<=20;i++){
                    if(cells[i].setOccupant(tempid)==true){
                        prisoners[tempid].prisonerCell==i;
                        prisoners[tempid].prisonerBlock=A;
                        cout<<"Prisoner transfered to Block A."<<endl;
                        break;
                    }else{
                        cout<<"Block A is full. choose another."<<endl;
                        continue;
                    }
                }
            }
            else if(newblock=="B" || newblock=="b"){
                for(int i=21;i<=30;i++){
                    if(cells[i].setOccupant(tempid)==true){
                        prisoners[tempid].prisonerCell==i;
                        prisoners[tempid].prisonerBlock=B;
                        cout<<"Prisoner transfered to Block B."<<endl;
                        break;
                    }else{
                        cout<<"Block B is full. choose another."<<endl;
                        continue;
                    }
                }
            }
            else if(newblock=="C" || newblock=="c"){
                for(int i=31;i<=40;i++){
                    if(cells[i].setOccupant(tempid)==true){
                        prisoners[tempid].prisonerCell==i;
                        prisoners[tempid].prisonerBlock=C;
                        cout<<"Prisoner transfered to Block C."<<endl;
                        break;
                    }else{
                        cout<<"Block C is full. choose another."<<endl;
                        continue;
                    }
                }
            }
            else if(newblock=="D" || newblock=="d"){
                for(int i=41;i<=50;i++){
                    if(cells[i].setOccupant(tempid)==true){
                        prisoners[tempid].prisonerCell==i;
                        prisoners[tempid].prisonerBlock=D;
                        cout<<"Prisoner transfered to Block D."<<endl;
                        break;
                    }else{
                        cout<<"Block D is full. choose another."<<endl;
                        continue;
                    }
                }
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

    void cellAndBlockAssignment(){
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


    void visitorManagment(){
        cout<<"Welcome to Visitor Management: "<<endl;
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
    void showVisitorHistory(){
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
    void addVisitorInfo(){
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
            cin.ignore();
            getline(cin,tempdate);
            while(true){
                cout<<"Enter the visitor's iD: ";
                cin>>visitortempid;
                if(intCheck()==false){
                    continue;
                }else{break;}
            }
            
            cout<<"Enter the visitor's relationship with prisoner: ";
            cin.ignore();
            getline(cin,relation);

            //storing visiotr's data
            prisoners[prisonerTempid].visits++;
            int newArraySize = prisoners[prisonerTempid].visits;
            string *temphistory = new string[newArraySize];
            for(int i=0;i<newArraySize-1;i++){
                temphistory[i] = prisoners[prisonerTempid].visitorHistory[i];

            }
            delete[] prisoners[prisonerTempid].visitorHistory;
            prisoners[prisonerTempid].visitorHistory = temphistory;
            delete[] temphistory;
            prisoners[prisonerTempid].visitorHistory[newArraySize-1]= tempname+" {ID = "+to_string(visitortempid)+"} visited "+prisoners[prisonerTempid].name+" {relation = "+relation+"} on "+tempdate;
            cout<<"Thank you, visitor's information added."<<endl;
        }
        else{
            cout<<"SORRY, Prisoner with that ID doesnot exist."<<endl;
        }
        
    
    }
};


int main(){
    Prison prison;
    prison.mainMenu();   //starts from here and then goes from function to function


    
    return 0;
}


bool intCheck()
{
    
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout << ">>> Please Enter valid input <<<" << endl;
        return false;
    }
    else{
        return true;
    }
}

