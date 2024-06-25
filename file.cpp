#include <fstream> //for file handling
#include "login.h" //Custom header file for the login function
using namespace std;

int balance; //this will keep track of current balance  
int items=0; //this will assign serials to items in inventory in order so there is no repetition
int corrector=0; // used mainly in case 4 of the outer switch statement(of main function), it will auto correct serials after an item is deleted 

struct Shop{ //main data storing means (BST: Binary search tree)
	int sr;
	string name;
	string packing;
	string price;
	string stock;
	Shop* left;
	Shop* right;
	
	//constructor
	Shop(int ID, string Name, string pack, string value, string quantity){
		this->sr = ID;
		this->name = Name;
		this->packing = pack;
		this->price = value;
		this->stock = quantity;
		this->left = NULL;
		this->right = NULL;
	}
};

struct store{
	int nSerial;
	string prodName;
	string prodPrice;
	store* next;
	store(int id, string n, string p){
		this->nSerial = id;
		this->prodName = n;
		this->prodPrice = p;
		this->next = NULL;
	}
};
store* head = NULL;

struct order{
	int oSr;
	string oName;
	string oPrice;
	string OSize;
	order* next;
	order(int x, string n, string p, string s){
		this->oSr = x;
		this->oName = n;
		this->oPrice = p;
		this->OSize = s;
		this->next = NULL;
	}
};
order* rear;
order* front;

void writeToFile(Shop* s){ //this function will add new items information to .csv file
	ofstream fout;
	
	fout.open("data.csv", ios::app);
	if(fout.is_open()){
    fout<<s->sr<<","<<s->name<<","<<s->packing<<","<<s->price<<","<<s->stock<<endl;
	}
	else{
	Color(4);
	cout<<"\n\n\t\tfailed to open the file"<<endl;
	Color(7);
	}
	fout.close();
}

Shop* insertNew(Shop* root, string name, string pck, string val, string quan){ //this function is used by the main function to insert data in tree 
    if(root == NULL){														   //as well as in the file
	items++;
    root = new Shop(items, name, pck, val, quan);
    writeToFile(root);
    return root;
    }
 	Shop* tempRoot = root;

    if(items < tempRoot->sr){
    tempRoot->left = insertNew(tempRoot->left, name, pck, val, quan);
    }
    else{
    tempRoot->right =	insertNew(tempRoot->right, name, pck, val, quan);
    }
 	return root;
}

Shop* insert(Shop* root, string name, string pck, string val, string quan){ //this function is used by the fetch function to create a new binary tree  
    if(root == NULL){														//at start of the program	
    items++;
    root = new Shop(items, name, pck, val, quan);
    return root;
    }
 	Shop* tempRoot = root;

    if(items < tempRoot->sr){
    tempRoot->left = insert(tempRoot->left, name, pck, val, quan);
    }
    else{
    tempRoot->right = insert(tempRoot->right, name, pck, val, quan);
    }
 	return root;
}

Shop* fetch(Shop* root){ //this function read data from file line by line & cell by cell and store data in the tree using insert() function
	ifstream fin;
	
	fin.open("data.csv", ios::app);
	string line;
	string x, n, p, pri, s;
	if(fin.is_open()){
	while(getline(fin,line)){
	stringstream linestream(line);
	string cell;
	for(int i=0;getline(linestream,cell,',');i++){
		if(i==0){
			x = cell;
		}
		else if(i==1){
			n = cell;
		}
		else if(i==2){
			p = cell;
		}
		else if(i==3){
			pri = cell;
		}
		else if(i==4){
			s = cell;
		}
	}
	root = insert(root, n, p, pri, s);
	}
	}
	else{
		cout<<"Couldn't open the file"<<endl<<endl;
	}
	fin.close();
	return root;
}

Shop* minValueShop(Shop* i){
  Shop* current = i;

  // Find the leftmost leaf
  while(current && current->left != NULL)
    current = current->left;

  return current;
}
	
Shop* removeItem(Shop *root, int id) //this fuction remove data of item cooresponding to its serial provided by the user
{
	if(root == NULL){
	return root;
	}
	if(id < root->sr){
	root->left = removeItem(root->left, id);
	}
	else if(id > root->sr){
	root->right = removeItem(root->right, id);
	}
	else{
	if(root->left == NULL){
  	Shop* temp = root->right;
  	delete root;
  	items--;
  	return temp;
	}	 
	else if(root->right == NULL) {
  	Shop* temp = root->left;
  	delete(root);
  	items--;
  	return temp;
	}
	Shop *temp = minValueShop(root->right);
	root->sr = temp->sr;
	root->right = removeItem(root->right, temp->sr);
	}
	return root;
}

Shop* update(Shop* root, int x){ //this function takes certain serial from user and change that particular items data;
	string n, p, pri, s; 
	while(root != NULL){
	if(root->sr==x){
		Color(8);
		cout<<"\tEnter name: ";
		Color(7);
		cin>>n;
		Color(8);
		cout<<"\tEnter package size: ";
		Color(7);
		cin>>p;
		Color(8);
		cout<<"\tEnter price: ";
		Color(7);
		cin>>pri;
		Color(8);
		cout<<"\tEnter stock: ";
		Color(7);
		cin>>s;
		
		root->name = n;
		root->packing = p;
		root->price = pri;
		root->stock = s;
		return root;
	}
	else if(x < root->sr){
		root = root->left;
	}
	else{
		root = root->right;	
	}
	}
	return root;
}

bool check(Shop* root, int x) //this function takes serial from user and check whether that item is present in inventory or not
{
Color(2);
	if(root == NULL){	
	cout<<"\n\t\tInventory is empty"<<endl<<endl;
	Color(7);
	return false; 	
	}
	while(root != NULL){
	if(root->sr==x){
		cout<<"\n\t\t"<<x<<" found in the Inventory"<<endl<<endl;
		Color(7);
		return true;
	}
	else if(x < root->sr){
		root = root->left;
	}
	else{
		root = root->right;	
	}
	}
	cout<<"\n\t\tItem not found in the inventory"<<endl<<endl;
	Color(7);
	return false;
}
	

void search(Shop* root) 
{
	int x;
	string str;
	Color(8);
	cout<<"\n\n\tEnter sr# of item you want to find: ";
	Color(7);
	cin.ignore();
	getline(cin, str);
	stringstream ToInt(str);
	ToInt>>x;
	Color(2);
	if(root == NULL){
	cout<<"\n\t\tInventory is empty"<<endl<<endl;
	Color(7);
	return; 	
	}
	while(root != NULL){
	if(root->sr==x){
	Color(2);
	cout<<"\n\t"<<x<<" found in the Inventory"<<endl<<endl;
	Color(8);
	cout<<"\n\n\tDisplaying Information"<<endl;
	cout<<"\n\n\tProduct ID: "<<root->sr<<endl;
    cout<<"\tProduct Name: "<<root->name<<endl;
    cout<<"\tProduct Packing: "<<root->packing<<endl;
    cout<<"\tProduct Price: "<<root->price<<endl;
    cout<<"\tProduct Stock: "<<root->stock<<endl<<endl;
	Color(7);
	return;	
	}
	else if(x < root->sr){
		root = root->left;
	}
	else{
		root = root->right;	
	}
	}
	cout<<"\n\tItem not found in the inventory"<<endl<<endl;
	Color(7);
}
	
void RewriteFile(Shop* root){ //this function will write all the current tree items in teh file  
	ofstream fout;
	fout.open("data.csv", ios::app);
	
 	if (root == NULL){
 		fout.close();
        return;
    }
    RewriteFile(root->left);
    if(fout.is_open()){
    fout<<root->sr<<','<<root->name<<','<<root->packing<<','<<root->price<<','<<root->stock<<endl;
	}
	else{
	Color(2);
	cout<<"\n\n\t\tError in loading file"<<endl<<endl;
	Color(7);
	}
	RewriteFile(root->right);
}

void Backup(Shop* root){ //this function is same as above but it is only called to create backup when deleting the file
	ofstream backup;
	
	backup.open("backup.csv", ios::app);
 	if (root == NULL){
 		backup.close();
        return;
    }
    Backup(root->left);
    if(backup.is_open()){
    backup<<root->sr<<','<<root->name<<','<<root->packing<<','<<root->price<<','<<root->stock<<endl;
	}
	else{
	Color(2);
	cout<<"\n\n\t\tError in loading file"<<endl<<endl;
	Color(7);
	}
	Backup(root->right);
}
	
void display(Shop* root){ 
    if (root == NULL){
        return;
    }
    display(root->left);
    Color(8);
    cout<<setw(6)<<root->sr<<setw(23)<<root->name<<setw(27)<<root->packing<<setw(25)<<root->price<<setw(25)<<root->stock<<endl<<endl;
    Color(7);
	display(root->right);
}

void arrange(Shop* root){ //this function will auto adjust all the serials so new item can be inserted accordingly
	if (root == NULL){
        return;
    }
    arrange(root->left);
    corrector++;
    root->sr = corrector;
	arrange(root->right);
}

void mainmenu(){
	system("cls");
	Color(3);
	cout<<"\n\n\t\t\t Trade Depot Management System"<<endl;
	cout<<"\t\t\t \xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\n"<<endl;
	cout<<"\n\t\t1. Insert new item to Inventory"<<endl;
	cout<<"\n\t\t2. View stock report"<<endl;
	cout<<"\n\t\t3. Find item from Inventory"<<endl;
	cout<<"\n\t\t4. Manage existing Inventory"<<endl;
	cout<<"\n\t\t5. Delete Inventory"<<endl;
	cout<<"\n\t\t6. Add orders"<<endl;
	cout<<"\n\t\t7. Display orders"<<endl;
	cout<<"\n\t\t8. Exit"<<endl;
	cout<<"\n>>";
	Color(7);
} 

void menu1(){
	Color(3);
	cout<<"\n\n\t\t\t Inventory Management"<<endl;
	cout<<"\t\t\t \xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc\xdc"<<endl;
	cout<<"\n\t\tPress 1 to remove an item from Inventory"<<endl<<endl;
	cout<<"\t\tPress 2 to change item's detail"<<endl<<endl;
	cout<<"\t\tPress 3 to return to main menu"<<endl;
	cout<<"\n>>";
	Color(7);
}

void BalanceFetcher(){ //this function will read balance from mentioned file and assign a pre number(if any) to the global variable balance;
	ifstream bal;
	string balInString;
	int balInNum;
	
	bal.open("balance.csv", ios::app);
	if(bal.is_open()){
	while(bal.good()){
		getline(bal, balInString, ',');
	}	
	}
	else{
	Color(2);
	cout<<"\n\n\t\tError in loading file"<<endl<<endl;
	Color(7);
	}
	stringstream ToInt(balInString);
	ToInt>>balInNum;
	balance = balInNum;
}

bool StockValidity(Shop* root, int nSerial, int xStock)
{
	stringstream ss;
	ss<<xStock;
	string str = ss.str();
	
	if(root == NULL){	
	return false; 	
	}
	while(root != NULL){
	if(root->sr==nSerial){
		stringstream ToInt(root->stock);
		int nStock;
		ToInt>>nStock;
		if(xStock <= nStock){
			return true;
		}
		else{
			return false;
		}
		
	}
	else if(nSerial < root->sr){
		root = root->left;
	}
	else{
		root = root->right;	
	}
	}
	return false;
}

void insertToStore(int x, string pName, string pPrice){		
store* temp = new store(x, pName, pPrice);
if(head == NULL){
	head = temp;
	return;
}
store* ptr = head;
while(ptr->next != NULL){
	ptr = ptr->next;
}	
ptr->next = temp;
}

void fetchMyOrdersList(){ 
	ifstream MyOrder;
	
	MyOrder.open("data.csv", ios::app);
	string line;
	string x, n, p, pri, s;
	if(MyOrder.is_open()){
	while(getline(MyOrder,line)){
	stringstream linestream(line);
	string cell;
	for(int i=0;getline(linestream,cell,',');i++){
		if(i==0){
			x = cell;
		}
		else if(i==1){
			n = cell;
		}
		else if(i==2){
			p = cell;
		}
		else if(i==3){
			pri = cell;
		}
		else if(i==4){
			s = cell;
		}
	}
	stringstream ToInt(x);
	int nX1;
	ToInt>>nX1;
	insertToStore(nX1, n, pri);
	}
	}
	else{
		Color(4);
		cout<<"\n\n\tCouldn't open the file"<<endl<<endl;
		Color(7);
	}
	MyOrder.close();
}

void showItemsForOrder(){
	store* temp = head;
	Color(8);
	cout<<"\n\n"<<"\t\t"<<"Product Serial"<<"\t\t\t"<<"Product Name"<<"\t\t\t"<<"Product Price"<<endl<<endl;
	while(temp != NULL){
	cout<<setw(25)<<temp->nSerial<<setw(32)<<temp->prodName<<setw(32)<<temp->prodPrice<<endl;
	temp = temp->next;
	}
	cout<<endl;
	Color(7);
}

void saleExporter(int id, string itemName, string itemPrice, int itemSold){
	ofstream fout;
	fout.open("orders.csv", ios::app);
	if(fout.is_open()){
	fout<<id<<','<<itemName<<','<<itemPrice<<','<<itemSold<<endl;
	}
	else{
		Color(4);
		cout<<"\n\n\tCouldn't open the file"<<endl<<endl;
		Color(7);
	}
	fout.close();
}
	

int saleItem(Shop* root, int id){ 
	int orderSizeInNum;
	store* ptr = head;
	int flag=0;
	char confirm;
	bool ans;

	while(ptr != NULL){
		if(ptr->nSerial == id){
			flag++;
			Color(8);
			cout<<"\n\tEnter how many goods you want to purchase: ";
			while(1){
			Color(7);
			cin>>orderSizeInNum;
	
			ans = StockValidity(root, id, orderSizeInNum);
			if(ans == true){
			Color(8);
			cout<<"\n\n\tConfirm purchase(Press Y to proceed): ";
			Color(7);
			cin>>confirm;
			if(confirm == 'Y' || confirm == 'y'){
			Color(2);
			cout<<"\n\t\titem bought"<<endl<<endl;
			saleExporter(ptr->nSerial, ptr->prodName, ptr->prodPrice, orderSizeInNum);
			return orderSizeInNum;
			}
			else{
				Color(2);
				cout<<"\n\n\tOrder Cancelled"<<endl<<endl;
				Color(7);
				return 0;
			}
			}
			else{
				Color(2);
				cout<<"\n\n\tInsufficient items in inventory";
				Color(8);
				cout<<"\n\n\tChange order size: ";
				Color(7);
				continue;
			}
			break;
			}
		}
		ptr = ptr->next;
	}
	
	if(flag==0){
		Color(4);
		cout<<"\n\n\tInvalid serial"<<endl<<endl;
		Color(7);
	}
}

void managerstock(Shop* root, int id, int preOrder){
	int xPriceInNum;
	if(root == NULL){
	return;
	}
	int xStock;
	
	while(root != NULL){
	if(root->sr == id){
		stringstream ToInt(root->stock);
		ToInt>>xStock;
		xStock -= preOrder;
		stringstream ToInt1(root->price);
		ToInt1>>xPriceInNum;
		
		int tempBal = preOrder * xPriceInNum;
		balance += tempBal;
		
		ofstream balWriter;
		balWriter.open("balance.csv");
		balWriter<<balance;
		balWriter.close();
		
		stringstream ss;
		ss<<xStock;
		string str = ss.str();
		root->stock = str;
		return;
	}
	else if(id < root->sr){
		root = root->left;
	}
	else{
		root = root->right;
	}
	}
}

void fetchOrderList(){ 
	ifstream orderImporter;
	
	rear = NULL;
	front = NULL;
	
	orderImporter.open("orders.csv", ios::app);
	string line;
	string x, n, pri, s;
	if(orderImporter.is_open()){
	while(getline(orderImporter,line)){
	stringstream linestream(line);
	string cell;
	for(int i=0;getline(linestream,cell,',');i++){
		if(i==0){
			x = cell;
		}
		else if(i==1){
			n = cell;
		}
		else if(i==2){
			pri = cell;
		}
		else if(i==3){
			s = cell;
		}
	}
	int xInNum;
	stringstream ToInt(x);
	ToInt>>xInNum;
	order* newNode = new order(xInNum, n, pri , s);
	if(front==NULL){
		front = rear = newNode;
	}
	else{
      rear -> next = newNode;
      rear = newNode;
   	}
	}
	}
	else{
		Color(4);
		cout<<"\n\n\tCouldn't open the file"<<endl<<endl;
		Color(7);
	}
	orderImporter.close();
}

order* popOrder(){
	if (front == NULL){
        return NULL;
    }
    order* temp = front;
    front = front->next;
 
    if (front == NULL)
        rear = NULL;
 
    return temp;
}



void displayOrders(){
	order* temp = front;
	
	if(front == NULL){
		Color(2);
		cout<<"\n\tNo order currently"<<endl;
		Color(7);
	}
	
	order* ptr;
	Color(8);
	cout<<"\n\n\t\t\t\t\tOrders List\n"<<endl;
	cout<<"\n"<<setw(10)<<"Serial"<<"\t\t\t"<<"Name"<<"\t\t\t"<<"Price"<<"\t\t\t"<<"Size"<<endl<<endl;
	do{
	ptr = popOrder();	
	cout<<setw(10)<<ptr->oSr<<setw(27)<<ptr->oName<<setw(24)<<ptr->oPrice<<setw(22)<<ptr->OSize<<endl<<endl;
	ptr = ptr->next;
	}while(ptr != NULL);
	Color(7);
}

int main()
{
Shop* root = NULL;
char choice, c1;
string id;
int nId;
bool ans;
root = fetch(root);
BalanceFetcher();
login();

while(1)
{
	mainmenu();
	cin>>choice;
	
	switch(choice){
		case '1':
		{
			string name, pack, val, quan;
			Color(8);
			cout<<"\n\n\tEnter product name: ";
			Color(7);
			cin.ignore();
			getline(cin, name);
			Color(8);
			cout<<"\tEnter package size: ";
			Color(7);
			getline(cin, pack);
			Color(8);
			cout<<"\tEnter product price: ";
			Color(7);
			getline(cin, val);
			Color(8);
			cout<<"\tEnter product stock: ";
			Color(7);
			getline(cin, quan);
			root = insertNew(root, name, pack, val, quan);
			cout<<endl;
			Color(2);
			system("pause");
			break;		
		}
		case '2':
		{
			Color(8);
			cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tBalance: "<<balance;
			cout<<"\n\n\t\t\t\t\tInventory Details"<<endl<<endl;
			cout<<setw(6)<<"Sr#"<<setw(23)<<"Name"<<setw(27)<<"Packing"<<setw(25)<<"Price"<<setw(25)<<"Stock"<<endl<<endl;
			display(root);
			cout<<endl;
			Color(2);
			system("pause");
			break;
		}	
		case '3':
		{
			search(root);
			Color(2);
			system("pause");
			break;	
		}
		case '4':
		{
			Color(8);
			cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tBalance: "<<balance;
			cout<<"\n\n\t\t\t\t\tInventory Details"<<endl<<endl;
			cout<<setw(6)<<"Sr#"<<setw(23)<<"Name"<<setw(27)<<"Packing"<<setw(25)<<"Price"<<setw(25)<<"Stock"<<endl<<endl;
			display(root);
			Color(8);
			cout<<"\n\n\tEnter sr# of item you want to manage: ";
			cin.ignore();
			while(1){//outer loop for case 4 
			id = "";
			nId = 0;
			Color(7);
			getline(cin, id);
			stringstream ToInt(id);
			ToInt>>nId;
			ans = check(root, nId);
			Color(2);
			if(ans == true){
			while(1){ //inner loop for case 4
			menu1();
			cin>>c1;
			switch(c1){
				case '1':
				{
					root = removeItem(root, nId);
					arrange(root);
					items = corrector;
					corrector = 0;
					fstream del;
					del.open("data.csv");
					RewriteFile(root);
					del.close();
					Color(2);
					cout<<"\n\n\tDeletion Successful"<<endl;
					cout<<endl;
					system("pause");
					break;
				}
				case '2':
				{
					update(root, nId);
					ofstream del;
					del.open("data.csv");
					RewriteFile(root);
					del.close();
					Color(2);
					cout<<"\n\n\tUpdation Successful"<<endl;
					cout<<endl;
					system("pause");
					break;
				}
				case '3':
				{
					break;
				}
				default:
				{
					Color(4);
					cout<<"\n\t\tInvalid choice!!"<<endl<<endl;
					Color(2);
					system("pause");
					continue; //this will keep the inner loop running
				}
		}
		break;
		}//end of inner loop of case 4
		}
		else{
			Color(4);
			cout<<"\n\tInvalid serial number";
			Color(8);
			cout<<"\n\n\tEnter again: ";
			Color(7);
			continue;
		}
			break;
		}//end of outer loop of case 4
			break;
		}
		case '5':
		{
			char choicex;
			system("del backup.csv");
			system("del data.csv");
			Color(8);
			cout<<"\n\n\t\tDo you want to create backup(Y/N): ";
			for(;;){
			Color(7);
			cin>>choicex;
			Color(2);
			if(choicex=='y' || choicex=='Y'){
			Backup(root);
			Color(2);
			cout<<"\n\t\tBackup Created Successfully"<<endl<<endl;
			Color(7);	
			root = NULL;
			items = 0;
			cout<<endl<<endl;
			break;	
			}
			else if(choicex=='n' || choicex=='N'){
			root = NULL;
			items = 0;
			Color(2);
			cout<<"\n\tInventory deleted successfully"<<endl<<endl;	
			Color(7);
			break;
			}
			else{
				Color(4);
				cout<<"\t\tInvalid choice";
				Color(8);
				cout<<"\n\n\tEnter again: ";
				continue;
			}
				break;
			}
			Color(2);
			system("pause");
			break;
		}
		case '6':
		{
			fetchMyOrdersList();
			int Orderindex;
			showItemsForOrder();
			string orderSr;
			Color(8);
			cout<<"\n\tEnter sr# of item you want to buy: ";
			cin.ignore();
			while(1){
			Color(7);
			getline(cin, orderSr);
			
			stringstream ToInt3(orderSr);
			int OrderSrInNum;
			ToInt3>>OrderSrInNum;
			
			bool checkSr;
			checkSr = check(root, OrderSrInNum);
			if(checkSr == true){
			Orderindex = saleItem(root, OrderSrInNum);
			managerstock(root, OrderSrInNum, Orderindex);
			ofstream del;
			del.open("data.csv");
			RewriteFile(root);
			del.close();
			break;	
			}
			else{
				Color(4);
				cout<<"\n\t\tInvalid Serial";
				Color(8);
				cout<<"\n\n\t\tEnter again: ";
				Color(7);
				continue;
			}
			break;
			}
			Color(2);
			system("pause");
			Color(7);
			break;	
		}	
		case '7':
		{
			fetchOrderList();
			displayOrders();
			Color(2);
			system("pause");
			Color(7);
			break;
			
		}
		case '8':
		{
			exit(0);	
		}
		default:
		{
			Color(4);
			cout<<"\n\n\tInvalid Choice"<<endl<<endl;
			Color(2);
			system("pause");
		}	
}
}	
}
