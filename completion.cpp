#include "iostream"
#include "conio.h"
#include<dos.h>
#include <windows.h>
using namespace std;
class Node{
	public:
	string name;
	long phone;
	int acn;
	int pin;
	long balance;
	Node* next;
	Node* prev;
};

class Account{
	private:
	Node *head;
	Node *useracc;
	Node *accs;
	int nofacc;
	public:
	
	Account(){
		head=nullptr;
		useracc=nullptr;
		accs=nullptr;
		nofacc=0;
	}
	
	void addAccount(string nm, long p,int pin){
		if(nofacc!=0){
			accs->next=new Node();
			accs->next->prev=accs;
			accs=accs->next;
			accs->name=nm;
			accs->balance=0;
			accs->phone=p;
			accs->acn=genid();
			accs->pin=pin;
			this->nofacc++;
			cout<<"ur account number is:"<<accs->acn<<endl;
		}
		else{
			accs=new Node();
			head=accs;
			accs->name=nm;
			accs->balance=0;
			accs->phone=p;
			accs->prev=nullptr;
			accs->acn=genid();
			accs->pin=pin;
			this->nofacc++;
			cout<<"ur account number is:"<<accs->acn<<endl;	
		}
	}
	
	int genid();
	void showDetails();
	void Deposit(int sum);
	void withdraw(int sum);
	
	bool login(int a, int p){
		useracc=head;
		while(useracc){
			if(useracc->acn==a && useracc->pin==p){
				cout<<"login successfull"<<endl;
				return true;
			}
			useracc=useracc->next;
		}
		cout<<"incorrect pin or account number"<<endl;
		return false;
	}
	
	void setName(string nm){
		useracc->name=nm;
	}
	
	void setphone(long p){
		useracc->phone=p;
	}
	
	void setpin(int p){
		useracc->acn=p;
	}
	
	void deleteAcc();
};

void Account::showDetails(){
	cout<<"Account details are as follows:"<<endl;
	cout<<"Account Holder Name: "<<useracc->name<<endl;
	cout<<"Account Holder Phone: "<<useracc->phone<<endl;
	cout<<"Account Holder Id: "<<useracc->acn<<endl;
	cout<<"\n\n Balance:"<<useracc->balance<<endl;
}

void Account::Deposit(int sum){
	useracc->balance+=sum;
}

void Account::withdraw(int sum){
	if(useracc->balance-sum >= 0)
		useracc->balance-=sum;
	else
		cout<<"Insufficient balance"<<endl;
}

void Account::deleteAcc(){
	useracc->prev->next=useracc->next;
	delete useracc;
	useracc=nullptr;
	cout<<"The Account has been deleted"<<endl;
}

int Account::genid(){
	return rand()%10000;
}

void transact(Account *o){
	while(true){
		system("cls");
		cout<<"Press 1 to get details for the account"<<endl;
		cout<<"Press 2 to deposit to the account"<<endl;
		cout<<"Press 3 to withdraw from the account"<<endl;
		cout<<"Press 4 to change name"<<endl;
		cout<<"Press 5 to change phone number"<<endl;
		cout<<"Press 6 to change pin"<<endl;
		cout<<"Press 7 to  open a new Account"<<endl;
		cout<<"Press 8 to delete the Account"<<endl;
		cout<<"Press q to exit\n====================="<<endl;
		if(kbhit()){
			char ch= getch();
			switch(ch){
				case '1':{
					o->showDetails();
					Sleep(5000);
					break;
				}
				
				case '2':{
					
					cout<<"Enter the sum to deposit"<<endl;
					int sum;
					cin>>sum;
					o->Deposit(sum);
					break;
				}
				
				case '3':{
					cout<<"Enter the sum to withdraw"<<endl;
					int sum;
					cin>>sum;
					o->withdraw(sum);
					break;
				}
				
				case '4':{
					cout<<"Enter new name"<<endl;
					string n;
					cin>>n;
					o->setName(n);
					break;
				}		
				
				case '5':{
					cout<<"Enter the phone"<<endl;
					long p;
					cin>>p;
					o->setphone(p);
					break;
				}
				
				case '6':{
					cout<<"Enter the new pin(must be of 4 digits)"<<endl;
					int pin;
					cin>>pin;
					o->setpin(pin);
					break;
				}
				
				case '7':{
					cout<<"Enter the name";
					Node tmp;
					cin>>tmp.name;
					cout<<"Enter the phone";
					cin>>tmp.phone;
					cout<<"Enter the pin";
					cin>>tmp.pin;
					o->addAccount(tmp.name,tmp.phone,tmp.pin);
					cout<<"Please note the account number";
					Sleep(4000);
					break;
				}
				
				case '8':{
					cout<<"Write \"confirm\" to delete the account"<<endl;
					string test;
					cin>>test;
					if(test.compare("confirm")==0)
					{
							cout<<"The account has been deleted";	
							o->deleteAcc();
					}
					return;
				}
				
				case 'q':
					return;
				
				default:
					cout<<"Provide an appropiate request";
			}
		}
	}
}

int main(){
	cout<<"start of program\n---------------------"<<endl;
	Account *o=new Account();
	while(true){
		cout<<"Press l to login and c to create a new account\n----------------------------\nPress q to exit"<<endl;
		if(kbhit()){
			char ch = getch();
			if(ch=='c'){
				cout<<"Enter your name"<<endl;
				Node *tmp=new Node();
				cin>>tmp->name;
				cout<<"Enter your phone"<<endl;
				cin>>tmp->phone;
				cout<<"Enter security pin(must be four digit)"<<endl;
				cin>>tmp->pin;
				o->addAccount(tmp->name,tmp->phone,tmp->pin);
				delete tmp;
				cout<<"The account has been added\nPlease login to transact.";
				cout<<"Redirecting to login page"<<endl;
				Sleep(5000);
				continue;
			}
			else if(ch=='l'){
				Node *tmp=new Node();
				cout<<"Enter the Account number"<<endl;
				cin>>tmp->acn;
				cout<<"Enter security pin(must be four digit)"<<endl;
				cin>>tmp->pin;
				if( o->login(tmp->acn,tmp->pin) )
				{
					transact(o);
				}
			}
			else if(ch=='q'){
				break;
			}
		}
		system("cls");
	}
}
