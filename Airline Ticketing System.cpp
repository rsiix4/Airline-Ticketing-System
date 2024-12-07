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

//used to delete uneccessary information outputed to screen
void deleteText(int rows, int time){
	/*sleep_for(seconds(time)) is used to sleep the particular 
	thread (single sequential flow of control within a program) for a period of time*/ 
	sleep_for(seconds(time));

	//"\033[nA" is used to move the cursor up n lines
	//"\r" is used to move the cursor to the beginning of the current line
	//"\033[J" is used to clear from the cursor o the end of the screen 
	cout << "\033[" << rows << "A" << "\r" << "\033[J";
}

//required for several functions
//Check if the node is empty
bool isEmpty(Node *root){
	if(root == NULL)
		return true;
	else
		return false;
};

//checkID duplication
bool IDExist(Node *root, int id){
	
	if(!isEmpty(root)){
		Node *curr = root;
		Node *prev = NULL;
		
		while (!isEmpty(curr)) 
		{
			if(curr->customer.id == id){
				cout << "There exist a customer with this ID. Try again!"<< endl;
				cout << "------------------------" << endl;
				deleteText(3,2);
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

bool FlightExist(FlightReservation flight, Customer &customer){
    for (int i = 0; i < customer.flightCounter; i++) {
        if (customer.flights[i].number == flight.number) {
        	if(customer.flights[i].destination == flight.destination)
            	return true; // Flight already exists for the customer
        }
    }

    return false; // Flight does not exist
}

//input integer number, such as ID, using exception handling
int inputInt(string Info){
	string input;
	int number;
	
	do{
			cout << "Enter " << Info << ": ";
			getline(cin, input);
			
			stringstream(input) >> number;
						
			if(isCorrect(number)){
				return number;
			}
	
			cout << "Invalid input try again!" << endl;
			cout << "------------------------" << endl;
			
			//erase the last 3 lines from screen before asking the user to enter int again
			deleteText(3, 2);
			
	}while(true);
}

//input ID and check for duplication, until the id is unique
int inputID(Node *root){
	int id;
	do
	{
		id = inputInt("customer ID");	
	}while(IDExist(root, id));
	
	return id;
}

void inputName(Customer &customer, string info){
        cout << "Enter " << info << " Name: ";
        getline(cin, customer.name);
}

void inputAge(Customer &customer, string info){
	customer.age = inputInt(info + " Age");
}

void inputMobileNumber(Customer &customer, string info){
        cout << "Enter " << info << " mobile number: ";
        getline(cin, customer.mobileNumber);
}

void updateName(Customer &customer){
            cout << "Old Name: " << customer.name << endl;
            inputName(customer, "new");
            cout << "Name updated successfully.\n";
}

void updateAge(Customer &customer){
        cout << "Old Age: " << customer.age << endl;
        inputAge(customer, "new");
        cout << "Age updated successfully.\n";
}

void updateMobileNumber(Customer &customer){
	    cout << "Old Mobile Number: " << customer.mobileNumber << endl;
        inputMobileNumber(customer, "new");
        cout << "Mobile number updated successfully.\n";
}

void add1Flight(Customer &customer){
	
    if (customer.flightCounter == maxFlights) {
        cout << "Cannot add more flights. Maximum limit reached.";
        return;
    }
    
    FlightReservation newFlight;
	do{
		cout << "_________Flight " << customer.flightCounter + 1 << " information_________" << endl;
		newFlight.number = inputInt("flight number");

	    cout << "Enter flight destination: ";
	    getline(cin, newFlight.destination);
	    
	    if(!FlightExist(newFlight, customer))
	    	break;
	    	
	    cout << "Flight already exists for the customer!";
		deleteText(3, 2);
	    
	}while(FlightExist(newFlight, customer));
    

    customer.flights[customer.flightCounter] = newFlight;
    customer.flightCounter++;

    cout << "Flight " << customer.flightCounter << " is added successfully." << endl;
    cout << "--------------------------------------" << endl;
}

bool addMore(){
	int choice;
	do{
			cout << "Do you want to add another flight?" << endl;
			choice = inputInt("1 for yes, 2 for no");
			
			if(choice != 1 && choice != 2){
				cout << "Invalid input try again!" << endl;
				cout << "------------------------" << endl;
				
				deleteText(4,2);
				continue;
			}
			
			deleteText(2,0);
			
			if(choice == 1)
				return true;
			else{
				deleteText(0,0);
				return false;
			}
				
							
		}while(true);
}

void addExtraFlights(Customer &customer){
	
	int flightCounter;
	do{
		cout << endl;
		
		if(!addMore())
			break;
			
		flightCounter = customer.flightCounter;
		add1Flight(customer);
		
		if(flightCounter + 1 > maxFlights){
			deleteText(2,2);
			break;
		}		
	}while(true);
}

void updateCustomerInfo(Customer &customer){
	int choice ; 
	int flightCounter;
	
	cout << endl;
	do
	{
		cout << "________Update Menu_________" << endl;
		cout << "1-Update the Name" << endl;
		cout << "2-Update the Age" << endl;
		cout << "3-Update the Moblie Number" << endl;
		cout << "4-Add extra Flight" << endl;
		cout << "5-Stop updating" << endl;
		cout << "----------------------------" << endl;
		choice = inputInt("Your chioce");
		cout<<endl;
	
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
		    	flightCounter = customer.flightCounter;
		        add1Flight(customer);
				if(flightCounter + 1 > maxFlights){
					deleteText(9,2);
				}
				else{
					cout << endl;
				}
				continue;	
			
			case 5 :
				deleteText(9,0);
				return;			  
			
		    default :
		         cout << "Invalid choice. Please try again.";
		         deleteText(9,1);
		         continue;
		}
		cout << "----------------------------" << endl << endl;
	}while(choice != 5);
}

Node *getNewNode(Node *root){
	
	//creat a new node with dynamic allocation
	Node *newCustomer = new Node;
	//Initialize the node left, right pointers to NULL
	newCustomer->left = NULL;
	newCustomer->right = NULL;
	
	//Initialize the customer flight Counter to 0
	newCustomer->customer.flightCounter = 0;
	
	//using input methods to insert information about the Customer
	inputName(newCustomer->customer, "Customer");
	
	newCustomer->customer.id = inputID(root);
	
	inputAge(newCustomer->customer, "Customer");
	
	inputMobileNumber(newCustomer->customer, "Customer");
	
	cout << endl;
	add1Flight(newCustomer->customer);
	addExtraFlights(newCustomer->customer);
	
	return newCustomer;
}

//Add a new customer to the Binary search tree
Node *addCustomer(Node *root){
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
        deleteText(11,2);
    }
	
    return customer;
}

void display1Flight(FlightReservation flight) {
    cout << "Flight Number: " << flight.number << endl;
    cout << "Destination: " << flight.destination << endl;
}

void displayCustomerFlights(Customer customer) {
	cout << endl;
    cout << "Flights reserved for customer ";
	cout << customer.name << ":" << endl;
    cout << endl;
    
    for(int i = 0; i < customer.flightCounter; i++) {
        cout << "__________Flight " << (i + 1) << "__________" << endl;
        display1Flight(customer.flights[i]);
    }
}

//display 1 customer record
void display1Customer(Customer &customer){
	cout << "Name: " << customer.name << endl;
	cout << "ID: " << customer.id << endl; 
	cout << "Age: " << customer.age << endl;
	cout << "Mobile Number: " << customer.mobileNumber << endl;
	displayCustomerFlights(customer);
	cout << endl;
}

void displayAllCustomers(Node *root , int &order){
    if(isEmpty(root))
        return;
    displayAllCustomers(root->left, order);
    
    cout << "__________Customer " << order++ << " information__________" << endl;
    display1Customer(root->customer);
    
    displayAllCustomers(root->right, order);
}

void emptySystem(){
	cout << "There is no customer in the system!";
	deleteText(10,3);	
}

void displayMenu(){
	cout << "_________________Menu_________________" << endl;
	cout << "1-Enter New Customer" << endl;
	cout << "2-Update Existing Customer Information" << endl;
	cout << "3-Display All Customer Information" << endl;
	cout << "4-Display All Flight Reservations for" << endl;
	cout << "  specific Customer" << endl;
	cout << "5-Exit" << endl;
	cout << "--------------------------------------" << endl;
}

int main()
{
    Node *root = NULL;
    int choice;
    int order;
    int id ;
	Customer customer;

    do {
        displayMenu();
        choice = inputInt("Your choice");
        cout << endl;

        switch(choice) {
			case 1:
				if(isEmpty(root))
					root = addCustomer(root);
				
				else
					addCustomer(root);
            	break;
            
            case 2:
				if(isEmpty(root)){
	   				emptySystem();
	   				continue;
				} 
				
	   			id = inputInt("Customer ID to update");
	   			customer = searchCustomer(root, id);
	   				   			
	   			if(isCorrect(customer.id)){
	   				updateCustomerInfo(customer);
	   			}
	   			
	   			continue;
                
            case 3: 
            	if(isEmpty(root)){
	   				emptySystem();
	   				continue;
				} 
				
        		order = 1;
        		displayAllCustomers(root, order);
        		cout << "--------------------------------------" << endl;
            	break;
            	
            case 4:
            	if(isEmpty(root)){
	   				emptySystem();
	   				continue;
				}
				
	   			id = inputInt("Customer ID to display his flights information");
	   			customer = searchCustomer(root, id);
	   			
	   			if(!isCorrect(customer.id)){
	   				continue;
				}
				
				displayCustomerFlights(customer);
	   			cout << "----------------------------" << endl;
				break;
	   			
                
            case 5:
                cout << "Exiting the system .. Thank you.";
                continue;
                
            default:
                cout << "Invalid choice ,Please try again.";
                deleteText(10, 2);
                continue;
        }
        cout << endl;
    } while (choice != 5);
    
    return 0;
}
