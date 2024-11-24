#include<iostream>
#include <string>
#include <sstream>
#define maxFlights 10
using namespace std;
//write your code after testing
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

void addFlight(Customer);

Customer searchCustomer(int id);

FlightReservation serachFlight(int number);

void display1Customer(Customer customer);

void display1Flight (FlightReservation flight);

void displayCustomerFlights (Customer customer);

bool CheckID(int id);

int inputID();
int inputAge();

//needed 
void updateCustomerInfo(Customer);

void updateName(Customer);
void updateAge(Customer);
void updateMobileNumber(Customer);

void updateFlight(FlightReservation);
void updateFlightNumber(FlightReservation);
void updateFlightDestination(FlightReservation);

bool CheckFlight(FlightReservation);

//needed for display function
bool isEmpty(Customer *root){
	if(root == NULL)
		return true;
	else
		return false;
};

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
node *removeNode(node *root, int val)
{
    node *curr = root; //curr :the node we looking to delete
    node *prev = NULL; //prev: father of curr
  
    while (curr != NULL && curr->key != val) //search for node
    //until founded or raech null
	{ //move to next
        prev = curr; 
        if (val < curr->key) 
            curr = curr->left; 
        else
            curr = curr->right; 
    } 
    if (curr == NULL) //raech null: not found
	{ 
        cout << "Key " << val 
             << " not found in the"
             << " provided BST.\n"; 
        return root; //exit and return original root ******************
    } 
    //if founded >>>> curr will be @ the node we looking to delete
    //and prev @ parent
    if (curr->left == NULL || curr->right == NULL) //1 or 0 child
	{ 
        node* newCurr=NULL;//used to point to child node, and initialize with null
       
        if (curr->left == NULL) //to set the pos for newCurr 
            newCurr = curr->right; 
        else
            newCurr = curr->left; 
  
        if (prev == NULL) // if we will delete the root and may has one child 
            return newCurr; //exit and return new root*********************
  		//like else***
        if (prev->left == curr) 
            prev->left = newCurr;//re connect from left 
        else
            prev->right = newCurr; //re connect from right
  
        delete curr;
    } 
    else //if the node we looking to delete has 2 child, apply the successor 
    //the successor : The smallest value that greater than it
	{ 
        node* succParent = NULL; //the successor parent like new prev
        node* succ; //the successor node like new curr
  
        succ = curr->right;//right not left because search the successor
		//     \ at first go right one time - first node greater than it
   		//     / go left -> left -> left
    	//    /  until find smallest value that greater than it
	    //  succ 
        while (succ->left != NULL) //search the successor
		{ 
            succParent = succ; //prev=curr
            succ = succ->left; //move curr to new pos
        } 
		curr->key = succ->key;//change value with successor -- new*****
        if (succParent != NULL)//if node we looking to delete isn't the parent for successor
            succParent->left = succ->right; //connect to right because no nods @ left
        else// if node we looking to delete is the parent for successor
            curr->right = succ->right;//connect to right because no nods @ left
        delete succ;
    } 
    return root; //because may the deleted node was the root ******************
}

void printBST(node *root)
{
    if(root == NULL)
        return;
    printBST(root->left);
    //call display
    printBST(root->right);
}

int main()
{
    node *root = NULL;
    
    string i;
    int num;
    do{
    	cout << "ENter i: ";
    	getline(cin, i);
    	stringstream(i) >> num;
    	cout << num << endl;
	}while(num != 7);
    
    
    return 0;
}
