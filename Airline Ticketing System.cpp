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

void updateCustomerInfo(Customer customer);
void updateName(Customer customer);
void updateAge(Customer customer);
void updateMobileNumber(Customer customer);



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
