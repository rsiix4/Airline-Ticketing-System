#include<iostream>
#include <string>
#include <sstream>
#define maxFlights 10
using namespace std;

struct FlightReservations{
	int number;
	string destination;
};

struct Customer{
	string name;
	int id;
	int age;
	string moblieNumber;
	int flightCounter;
	FlightReservations flights[maxFlights];
	
	Customer *left;//like node * link1
    	Customer *right;//like node * link2
};

Customer addCustomer();

void addFlight(Customer customer);

Customer searchCustomer(int id);
bool CheckID(int id);

FlightReservation serachFlight(int number);
bool CheckFlight(FlightReservation flight);

void display1Customer(Customer customer);

void display1Flight (FlightReservation flight);

void displayCustomerFlights (Customer customer);

int inputID();
int inputAge();
void updateName(Customer customer){
            cout << "Old Name: " << customer->name << endl;
            cout << "Enter new name: ";
            getline(cin, customer->name);
            cout << "Name updated successfully.\n";
}
void updateAge(Customer customer){
            cout << "Old Age: " << customer->age << endl;
            cout << "Enter new age: ";
            cin >> customer->age;
            cout << "Age updated successfully.\n";
}
void updateMobileNumber(Customer customer){
	    cout << "Old Mobile Number: " << customer->mobileNumber << endl;
            cout << "Enter new mobile number: ";
            getline(cin, customer->mobileNumber);
            cout << "Mobile number updated successfully.\n";
}
void updateCustomerInfo(Customer customer){
int choice ; 
	do
	{
	cout << " Choose the item number that you want to update : \n\n" ;
	cout << "   1- Update the name \n   2- Update the age \n    3- Update the moblieNumber \n    4- Add extra flight   5- Exit" ;
	cout << "Your chioce : " ;
	cin >> choice ;
	cout<<endl ;
	
	switch ( choice )
	{
		case 1 :
		updateName(customer) ;
		break ;
		
		case 2 :
		updateAge(customer);	
		break;
		
		case 3 :
	        updateMobileNumber(customer) ;
	        break ;
		
	        case 4:
	        addFlight(customer);
		break ;	
		
		case 5 :
		 return ; 
		
	        default :
	         cout << "Invalid choice. Please try again.\n";
	    
}
}

//needed for display function
bool isEmpty(Customer *root){
	if(root == NULL)
		return true;
	else
		return false;
};

//Iwrote next fuctions as comments so you don't get errors when you run the program
/*
node *insert(node *root, int key) 
{
    node *newnode = getNewNode(key);
    
	node *curr = root; //child node
    node *prev = NULL;//parent or father node
 
    while (curr != NULL) //To reach to the right place to insert
	{
        prev = curr;
        if (key < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (prev == NULL)//if no parent >> first node
        prev = newnode;
    else if (key < prev->key)//set @ left
        prev->left = newnode;
    else//set @ right
        prev->right = newnode;
    
	return prev;//needed if its the first node
}

void printBST(node *root)
{
    if(root == NULL)
        return;
    printBST(root->left);
    //call display
    printBST(root->right);
}*/

int main()
{
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1 - Enter New Customer\n";
        cout << "2 - Update Existing Customer Information\n";
        cout << "3 - Add Flight Reservation for Customer\n";
        cout << "4 - Display All Customer Information\n";
        cout << "5 - Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
            case 2: 
		{
	   	int id ; 
                cout <<  "Enter Customer ID to update: ";
                cin >> id ; 
            
                bool cheak = CheckID(id) ;
                
                  if(cheak == true)
                    updateCustomerInfo(searchCustomer(id));
                  else
                    cout << " Customer not exist\n";
                break ;    
		        }
		        
            case 3: 
            case 4:
                
            case 5:
                cout << "Exiting the system .. Thank you.\n";
                break;
            default:
                cout << "Invalid choice ,Please try again.\n";
        }
    } while (choice != 5);	
    return 0;
}
