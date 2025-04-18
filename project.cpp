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

bool checkcell = false;
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
                    // prisonerRecordManagement();
                    break;
                case 2:
                    // cellAndBlockAssignment();
                    break;
                case 3:
                    // guardScheduleManagement();
                    break;
                case 4:
                    // visitorManagment();
                    break;
                case 5:
                    // searchPrisoner();
                    break;
                case 6:
                    exit(0);
                    break;
                
                default:
                    cout<<"invalid number entered. Please enter (1 to 6)."<<endl;
                    break;
                }
        }while(true);
        
    }
    void prisonerRecordManagement(){
        int select;
        cout<<"Select one option"<<endl;
        cout<<"Menu"<<endl;
         cout<<"1.add prisoner"<<endl
            <<"2.release prisoner"<<endl
            <<"3.modify prisoner data"<<endl
           <<"4. search for a prisoner"<<endl
            <<"5. return to mainmenu"<<endl;

           cin>>select;
           switch(select){
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
            cout<<"Enter the ID of prisoner to be removed: "<<endl;
            int tempId;
            cin>>tempId;
            if(intCheck() == false){   //this checks if other than integer type is enetered
                cout<<"Enter only integers. "<<endl;
                continue;
            }else{
                for(int i=1;i<=100;i++){
                    if(isPrisonerIdTaken[tempId] == true){
                        isPrisonerIdTaken[tempId]=false;  //indicates this slot is empty now for any other prsioner to be added
                        cout<<"Prisoner (ID = "<<prisoners[tempId].id<<") has been released. "<<endl;
                    }else{
                        cout<<"Sorry, A Prsioner with this Id doesnot exist.\nPress any key to tryagain or enter (back) to go back."<<endl;
                        string tempstr;
                        cin>>tempstr;
                        if(toLower(tempstr) == "back"){return;}
                        else{continue;}
                    }
                }
            }
        }while(runAgain);
    }

void modifyPrisonerData(){
    int id;
    cout << "Enter the ID of the prisoner you want to modify: ";
    cin >> id;
    if(intCheck() == false) return;

    if (!isPrisonerIdTaken[id]) {
        cout << "No prisoner exists with this ID.\n";
        return;
    }

    int choice;
    do {
        cout << "\nWhat do you want to modify?\n";
        cout << "1. Name\n";
        cout << "2. Age\n";
        cout << "3. ID\n";
        cout << "4. Sentence Duration\n";
        cout << "5. Crime\n";
        cout << "6. Date of Arrest\n";
        cout << "7. Return to Prisoner Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        if(intCheck() == false) continue;

        switch (choice) {
            case 1: {
                cout << "Enter new name: ";
                cin >> prisoners[id].name;
                cout << "Name updated.\n";
                break;
            }
            case 2: {
                cout << "Enter new age: ";
                cin >> prisoners[id].age;
                if (intCheck())
                    cout << "Age updated.\n";
                break;
            }
            case 3: {
                int newId;
                cout << "Enter new ID (1-100): ";
                cin >> newId;
                if (intCheck() && newId >= 1 && newId <= 100 && !isPrisonerIdTaken[newId]) {
                    prisoners[newId] = prisoners[id];  // Copy data
                    isPrisonerIdTaken[newId] = true;
                    isPrisonerIdTaken[id] = false;
                    id = newId; // update the current working ID
                    cout << "ID updated successfully.\n";
                } else {
                    cout << "Invalid or already taken ID. Try again.\n";
                }
                break;
            }
            case 4: {
                int newSentence;
                cout << "Enter new sentence duration (in years): ";
                cin >> newSentence;
                if (intCheck()) {
                    prisoners[id].sentence = newSentence;
                    cout << "Sentence updated.\n";
                }
                break;
            }
            case 5: {
                cout << "Enter new crime: ";
                cin >> prisoners[id].crime;
                cout << "Crime updated.\n";
                break;
            }
            case 6: {
                cout << "Enter new date of arrest: ";
                cin >> prisoners[id].dateOfArrest;
                cout << "Date of arrest updated.\n";
                break;
            }
            case 7: {
                prisonerRecordManagement(); // Return to prisoner menu
                return;
            }
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (true);
}

    }
    void searchPrisoner(){
        bool runAgain;
        do{
            runAgain=false;
            cout<<"ENter the ID of prisoner: "<<endl;
            int tempId;
            cin>>tempId;
            if(intCheck()==false){
                cout<<"Invalid ID entered, please try only integers. "<<endl;
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
                    else{continue;}
                }
            }
        }while(runAgain);
    }

    void cellAndBlockAssignment(){
        //ask for prisoner id
        //print his cell and block
        //ask if user wanna change cell or  block
        //if user wanna change cell ask for which cell(1-50) then check if its empty or not by calling setOccupant(id), if empty then set the prisoner onto that and change the block accordingly
        //if user wanna change block instead, then ask which block(A,B,C or D) and then check the cells in that block, and add the rpsioner into any empty cell, if block is full ask for another block
        //retturn to mainmenu by calling mainmenu()
    }
};


int main(){
    Prison prison;
    // prison.mainMenu();   starts from here and then goes from function to function


    
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

