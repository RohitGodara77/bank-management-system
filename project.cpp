#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;


class account
{
private:
	int ac_no;
	int deposit;
	char name[70];
	char type;
public:
	void create_account();	    //function to add a new account
	void show_account() const;	//function to display info of particular account
	void modify();				//function to modify data of existing account
	void dep(int);				//function to deposit money to an acoount
	void draw(int);				//function to withdraw money from an account
	void report() const;		//function to generate report (tabular format)
	int ret_acno() const;		//function to return account number
	int ret_balance() const;	//function to return balance amount
	char ret_type() const;		//function to return type of account
};       

void account::create_account()
{
	cout<<endl<<"Enter The account No. :";
	cin>>ac_no;
	cout<<endl<<"Enter The Name of The account Holder : ";
	cin.ignore();				//to ensure clearance of buffer
	cin.getline(name,70);
	cout<<endl<<"Enter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);         //to convert the data in uppercase
	cout<<endl<<"Enter The Initial amount(>=1000 for Saving and >=2000 for current ) : ";
	cin>>deposit;
	cout<<endl<<endl<<"Account Created..";
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<ac_no;
	cout<<"\nAccount Holder Name : "<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nAccount No. : "<<ac_no;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,70);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

	
void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<ac_no<<setw(10)<<" "<<name<<setw(4)<<" "<<type<<setw(6)<<" "<<deposit<<endl;
}

	
int account::ret_acno() const
{
	return ac_no;
}

int account::ret_balance() const
{
	return deposit;
}

char account::ret_type() const
{
	return type;
}


void write_account();	    	 //function to write record in binary file
void display_sp(int);			 //function to display account details given by user
void modify_account(int);		 //function to modify record of file
void delete_account(int);	 	 //function to delete record of file
void display_all();				 //function to display all account details
void deposit_withdraw(int, int); //function to desposit/withdraw amount for given account
void intro();					 //introductory screen function

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\t01. NEW ACCOUNT";
		cout<<"\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\t04. BALANCE ENQUIRY";
		cout<<"\n\t05. ACCOUNT HOLDER'S LIST";
		cout<<"\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\t08. EXIT";   
		cout<<"\n\tSelect Your Option \n\n";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThank you for choosing our bank";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}


void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.ret_acno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.ret_acno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.ret_acno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.  |      NAME     |  Type |    Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.ret_acno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.ret_balance()-amt;
				if((bal<500 && ac.ret_type()=='S') || (bal<1000 && ac.ret_type()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


void intro()
{
	cout<<"\n\n\twelcome to CREDIT $UI$$E Bank";
	cout<<"\n\t     how can we help you";
	cout<<"\n\n\n\nMADE BY : ROHIT GODARA";
	cout<<"\nCOLLEGE : ARMY INSTITUTE OF TECHNOLOGY,PUNE ";
	cin.get();
}
