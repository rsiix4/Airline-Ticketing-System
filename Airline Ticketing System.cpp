#include<iostream>
#include <string>
#include <sstream>
//to use function sleep for(seconds(int))
#include <thread>
#include <chrono>
#define maxFlights 10
using namespace std;
using namespace this_thread;
using namespace chrono;

struct FlightReservation{
	int number;
	string destination;
};

struct Customer{
	string name;
	int id;
	int age;
	string mobileNumber;
	
	int flightCounter;
	FlightReservation flights[maxFlights];
};

struct Node{
	Customer customer;
	Node *left;
	Node *right;
};

//required for several functions
//Check if the node is empty
bool isEmpty(Node *root){
	if(root == NULL)
		return true;
	else
		return false;
};

//checkID duplication
bool checkID(Node *root, int id){
	
	if(!isEmpty(root)){
		Node *curr = root;
		Node *prev = NULL;
		
		while (!isEmpty(curr)) 
		{
			if(curr->customer.id == id){
				cout << "There exist a customer with this ID. Try again!"<< endl;
				cout << "------------------------" << endl;
				sleep_for(seconds(3));
				cout << "\033[3A" << "\r" << "\033[J"; 
				return true;
			}
			
	        prev = curr;
	        if (id < curr->customer.id)
	            curr = curr->left;
	        else
	            curr = curr->right;
	    }
	}
		
    return false;
}

//check if the number(id or age) is within the acceptable range
bool isCorrect(int number){
	if(number <= 0)
		return false;
	else
		return true;
}

//input integer number, such as ID, using exception handling
int inputInt(string Info){
	int number;
	
	do{
			// cin.sync() can be used to discard all unread characters from the input buffer. 
			cin.sync();
			cout << "Enter " << Info << ": ";
			cin >> number;
			
			//cin.fail() returns true if the entered value does not fit the variable(not acceptable for the variable type)
			if(cin.fail() || !isCorrect(number)){
				//cin.clear() clears the error flag in cin, so next inputs can be taken without problems
				cin.clear();
				cout << "Invalid input try again!" << endl;
				cout << "------------------------" << endl;
				
				/*sleep_for(seconds(3)) is used to sleep the particular 
				thread (single sequential flow of control within a program) for a period of time*/  
				sleep_for(seconds(3));
				
				//"\033[nA" is used to move the cursor up n lines
				//"\r" is used to move the cursor to the beginning of the current line
				//"\033[J" is used to clear from the cursor o the end of the screen
				cout << "\033[3A" << "\r" << "\033[J"; 
				continue;
			}
			
			return number;
			
	}while(true);
	
	
}

//input ID and check for duplication, until the id is unique
int inputID(Node *root){
	int id;
	do
	{
		id = inputInt("customer ID");	
	}while(checkID(root, id));
	
	return id;
}

void updateName(Customer &customer){
            cout << "Old Name: " << customer.name << endl;
            cout << "Enter new name: ";
            getline(cin, customer.name);
            cout << "Name updated successfully.\n";
}

void updateAge(Customer &customer){
            cout << "Old Age: " << customer.age << endl;
            customer.age = inputInt("new Age");
            cout << "Age updated successfully.\n";
}

void updateMobileNumber(Customer &customer){
	    cout << "Old Mobile Number: " << customer.mobileNumber << endl;
        cout << "Enter new mobile number: ";
        getline(cin, customer.mobileNumber);
        cout << "Mobile number updated successfully.\n";
}

void updateCustomerInfo(Customer &customer){
	int choice ; 
	
	do
	{
		cout << " Choose the item number that you want to update :\n\n" ;
		cout << "1- Update the Name\n";
		cout << "2- Update the Age\n";
		cout << "3- Update the Moblie Number\n";
		cout << "4- Add extra Flight\n";
		cout << "5- Exit\n" ;
		choice = inputInt("Your chioce");
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
				return;			  
			
		    default :
		         cout << "Invalid choice. Please try again.\n";
		}
	}
}

//0000
void addFlight(Customer &customer) {
    if (customer.flightCounter >= maxFlights) {
        cout << "Cannot add more flights. Maximum limit reached.\n";
        return;
    }
}

FlightReservation serachFlight(int number){
	FlightReservations newFlight;
    cout << "Enter flight number: ";
    cin >> newFlight.number;
    cin.ignore(); // Clear input buffer

    cout << "Enter flight destination: ";
    getline(cin, newFlight.destination);

    customer.flights[customer.flightCounter] = newFlight;
    customer.flightCounter++;

    cout << "Flight added successfully.\n";
}

bool CheckFlight(FlightReservations flight, Customer &customer) {
    for (int i = 0; i < customer.flightCounter; i++) {
        if (customer.flights[i].number == flight.number) {
            return true; // Flight already exists for the customer
        }
    }

    return false; // Flight does not exist
}

Node *getNewNode(Node *root){
	
	//creat a new node with dynamic allocation
	Node *newCustomer = new Node;
	//Initialize the node left, right pointers to NULL
	newCustomer->left = newCustomer->right = 0;
	//using update methods to insert information about the Customer
	//....
	return newCustomer;
}

//Add a new customer to the Binary search tree
Node *addCustomer(Node *root) 
{
    Node *newNode = getNewNode(root);
    
    if(isEmpty(root)){
    	return newNode;
	}
    
	Node *curr = root; //child node
    Node *prev = NULL;//parent or father node
 
    while (!isEmpty(curr)) //To reach to the right place to insert
	{
        prev = curr;
        if (newNode->customer.id < curr->customer.id)
            curr = curr->left;
        else
            curr = curr->right;
    }
    
    if (newNode->customer.id < prev->customer.id)//set @ left
        prev->left = newNode;
    else//set @ right
        prev->right = newNode;
        
    return prev;
}

//Search for a customer in the Binary search tree by using id
Customer searchCustomer(Node *root, int id){
	Customer customer;
	customer.id = -1; 
	
	if(isEmpty(root)){
		cout << "There is no customer in the system!" <<endl; 
	}
	
	else{
		Node *curr = root;
		Node *prev = NULL;
		
		while (!isEmpty(curr)) 
		{
			if(curr->customer.id == id){
				customer = curr->customer;
				break;
			}
			
	        prev = curr;
	        if (id < curr->customer.id)
	            curr = curr->left;
	        else
	            curr = curr->right;
	    }
	    
	    if (isEmpty(curr)) //raech null: not found
		{ 
	        cout << "Customer with id " << id << " is not found in the System.";
	    } 
	}
	
	if(customer.id == -1){
		cout << "Wrong!";
	}
	
    return customer;
}

void display1Flight(FlightReservations flight) {
    cout << "Flight Number: " << flight.number << endl;
    cout << "Destination: " << flight.destination << endl;
}

void displayCustomerFlights(Customer customer) {
    if (customer.flightCounter == 0) {
        cout << "No flights reserved for this customer.\n";
        return;
    }

    cout << "Flights reserved for customer " << customer.name << ":\n";
    for (int i = 0; i < customer.flightCounter; i++) {
        cout << "--- Flight " << (i + 1) << " ---\n";
        display1Flight(customer.flights[i]);
    }
}

//display 1 customer record
void display1Customer(Customer &customer){
	cout << "Name: " << customer.name << endl;
	cout << "ID: " << customer.id << endl; 
	cout << "Age: " << customer.age << endl;
	cout << "Mobile Number: " << customer.mobileNumber << endl;
	//displayCustomerFlights(customer);
}


void printBST(Node *root)
{
    if(isEmpty(root))
        return;
    printBST(root->left);
    display1Customer(root->customer);
    cout << "---------------------------------\n";
    printBST(root->right);
}


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
