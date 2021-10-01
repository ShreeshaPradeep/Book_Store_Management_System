#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>
#include <ctime>

using namespace std;

//Record specification
class student{
public:
char ind[5],bn[5],bna[25],ana[25],nob[5],cost[5],bill_no[5],customer[25],date[10];

}
stdrec[80];

int no;

int get_num_records()
{
int I=0;
fstream file2;             
	  
	file2.open("record.txt",ios::in);
	if(!file2)
	{
		return 0;
	}
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(stdrec[I].ind,5,'|');
		file2.getline(stdrec[I].bn,5,'|');
		file2.getline(stdrec[I].bna,25,'|');
		file2.getline(stdrec[I].ana,25,'|');
		file2.getline(stdrec[I].nob,5,'|');
		file2.getline(stdrec[I].cost,5,'\n');
		I++; 	
 	}
	I--;
	file2.close();
	return I;
}
void retrieve_details(char st_no[])
{

	no = get_num_records();
	for(int i=0;i<no;i++)
 	{
		if(strcmp(stdrec[i].ind,st_no)==0) 
	 	{
		cout<<"\n\n"<<"\t\t\t\t\t\t\t\t\t\t\tBook Details   \n\n";
		cout<<"\n\nBook Number   :"<<stdrec[i].bn<<"\n\nBook Name     :"<<stdrec[i].bna<<"\n\nAuthor Name   :" <<stdrec[i].ana<<"\n\nNo Of Books   :"<<stdrec[i].nob<<"\n\nBook price    :"<<stdrec[i].cost<<"\n\n";
		break;
	 	}
 	}
}


void add_record()
{
char buf1[100],buf2[100];
fstream file1,file2;
int I,cnt;
student s;
cout<<"\n_____________________________________________________________________\n";
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tADD BOOKS\n";
cout<<"\n_____________________________________________________________________\n";

	cnt=get_num_records();

	file1.open("index.txt",ios::out|ios::app);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}

	file2.open("record.txt",ios::out|ios::app);
	if(!file2)
	{
		cout<<"\nError !\n";
		exit(0);
	}

	cout<<"\n\nEnter The Number Of Books To Add : ";
	cin>>no;
	cout<<"\n";
	cout<<"\nEnter Book Details :\n"; 

	for(I=cnt; I<(cnt+no); I++)
   {                  
		cout<<"\nBook No     : ";
		cin>>s.bn;
		cout<<"\n";
		cout<<"\nBook Name   : ";
		cin.ignore();
        cin.getline(s.bna,25);
		cout<<"\n";
		cout<<"\nAuthor Name : ";
		cin.getline(s.ana,25);
		cin.ignore();
		cout<<"\n";
		cout<<"\nNo Of Books : ";
		cin>>s.nob;
		cout<<"\n";
		cout<<"\nPrice       : ";
		cin>>s.cost;
		cout<<"\n";
        
		sprintf(buf2,"%s|%d\n",s.bn,I);
		file1<<buf2;

		sprintf(buf1,"%d|%s|%s|%s|%s|%s\n",I,s.bn,s.bna,s.ana,s.nob,s.cost);
		file2<<buf1;
	}
		file1.close();
		file2.close();
		cout<<"\n_____________________________________________________________________\n";
}

void search_record()
{
int I,flag1;
char st_no[5],st_usn[5],rt_usn[5];
fstream file1;
cout<<"\n_____________________________________________________________________\n";
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tSEARCH\n";
cout<<"\n_____________________________________________________________________\n";

	cout<<"\n\nPlease Enter Book Number ";
	cout<<" To Check Its Details : \n\n";
	cin>>st_usn;
	file1.open("index.txt",ios::in); 
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag1=0;
	while(!file1.eof())
	{
		file1.getline(rt_usn,5,'|');
		file1.getline(st_no,5,'\n');    
		if(strcmp(st_usn,rt_usn)==0)
		{
			retrieve_details(st_no);         
			flag1=1;                  
			break;
		}
	}
	if(!flag1)
	cout<<"\nRecord search failed !!\n"; 
	file1.close();
	cout<<"\n_____________________________________________________________________\n";
}

void delete_stdrecord(char usno[])
{
int I=0;
fstream file1,file2;

	no = get_num_records();	
	int flag=-1;
	for(I=0;I<no;I++)       //Check for the record's existence
	{
		if(strcmp(stdrec[I].ind,usno)==0)
		{
			flag=I;
			break;
		}	

	}
	if(flag==-1)                //Record not found
	{
		cout<<"\nError !\n";
		return;
	}
	if(flag==(no-1))            //Delete found last record
	{
		no--;
		cout<<"\n\nDeleted !\n\n";
		
	}
	else
	{
		for(I=flag;I<no;I++)
		{
			stdrec[I] = stdrec[I+1];
		}
		no--;
		cout<<"\n\nDeleted !\n\n";
	}

	file1.open("index.txt",ios::out);  
	file2.open("record.txt",ios::out);  
	for(I=0;I<no;I++)                   
	{                                   
		file1<<stdrec[I].bn<<"|"<<I<<"\n";
		file2<<I<<"|"<<stdrec[I].bn<<"|"<<stdrec[I].bna <<"|"<<stdrec[I].ana<<"|"<<stdrec[I].nob<<"|"<<stdrec[I].cost<<"\n";
	}
	file1.close();
	file2.close();
	return;
}



void delete_record()
{
int I,flag;
char st_no[5],st_usn[5],rt_usn[5];
fstream file1;
cout<<"\n_____________________________________________________________________\n";
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tDELETE\n";
cout<<"\n_____________________________________________________________________\n";
	cout<<"\n\nPlease Enter Book Number ";
	cout<<" To Be Deleted : \n\n";
	cin>>st_usn;
	file1.open("index.txt",ios::in);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}
	flag=0;

	while(!file1.eof())
	{
		file1.getline(rt_usn,5,'|');      //Search index file and
		file1.getline(st_no,5,'\n');       //call deletion
		//if index found
		if(strcmp(st_usn,rt_usn)==0)
		{
			delete_stdrecord(st_no); 
			flag=1;
			break;
		}
	}
	if(!flag)
	cout<<"\nDeletion failed !\n"; 
	file1.close();
	cout<<"\n_____________________________________________________________________\n";
	
}

void display_records()
{
fstream file2;
student s;
cout<<"\n_____________________________________________________________________\n";
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tDISPLAY\n";
cout<<"\n_____________________________________________________________________\n";
	
	file2.open("record.txt",ios::in);
cout<<"\n\n"<<"Book Details : \n";
cout<<"Index"<<setw(25)<<"Book Number"<<setw(30)<<"Book Name"<<setw(33)<<"Author Name"<<setw(35)<<"Number Of Books"<<setw(19)<<"Price"<<setw(10)<<endl; 
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(s.ind,5,'|');
		file2.getline(s.bn,5,'|');
		file2.getline(s.bna,25,'|');
		file2.getline(s.ana,25,'|');
		file2.getline(s.nob,5,'|');
		file2.getline(s.cost,5,'\n');
        //cout<<s.ind<<s.bn<<s.bna<<s.ana<<s.nob<<s.cost<<"\n";
		cout<<"\n";
cout<<s.ind<<setw(25)<<s.bn<<setw(35)<<s.bna<<setw(35)<<s.ana<<setw(25)<<s.nob<<setw(25)<<s.cost<<"\n\n";	 	
 	}
	file2.close();
cout<<"\n_____________________________________________________________________\n";
}

void modify()
{
fstream in;
char bn[5],buffer[45],extra[45];
int I,j;
student s[100];
cout<<"\n_____________________________________________________________________\n";
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tMODIFY\n";
cout<<"\n_____________________________________________________________________\n";

in.open("record.txt",ios::in);

if(!in)
{
cout<<"\n\nUnable to open the file in input mode\n\n";
return;
}

cout<<"\n\nEnter the book number : ";
cin>>bn;

I=0;

//Loading the file to Main memory   ind[5],bn[5],bna[25],ana[25],nob[5],cost[5]

while(!in.fail())
  {
	 
in.getline(s[I].ind,5,'|');
in.getline(s[I].bn,5,'|');
in.getline(s[I].bna,25,'|');
in.getline(s[I].ana,25,'|');
in.getline(s[I].nob,5,'|');
in.getline(s[I].cost,5,'\n');
//in.getline(extra,45,'\n');
I++;
 }

I--;

for(j=0;j<I;j++)
{ 
if(strcmp(bn,s[j].bn)==0)
{
/*cin.ignore();
cin.getline(s.bna,25);
cin.getline(s[j].ana,25);
cin.ignore();*/

cout<<"\n\nEnter the new values \n\n";
//cout<<"\nbook no     = ";  cin>>s1[j].bn;
cout<<"\nbook name   = ";  
cin.ignore();
cin.getline(s[j].bna,25);
cout<<"\n";
cout<<"\nauthor name = ";  
cin.getline(s[j].ana,25);
cin.ignore();
cout<<"\n";
cout<<"\nno of books = ";  
cin>>s[j].nob;
cout<<"\n";
cout<<"\nprice       = ";  
cin>>s[j].cost;
cout<<"\n\n";

break;

  }
 }

if(j==I)
 {
cout<<"\n\nThe record with book number "<<bn<<" is not present\n\n"; 
return;
 }

in.close();
fstream out1;
out1.open("record.txt",ios::out);
if(!out1)
 {
cout<<"\nUnable to open the file in output mode"; 
return;
 }

for(j=0;j<I;j++)
 {
strcpy(buffer,s[j].ind);
strcat(buffer,"|");
strcat(buffer,s[j].bn);
strcat(buffer,"|");
strcat(buffer,s[j].bna);
strcat(buffer,"|");
strcat(buffer,s[j].ana);
strcat(buffer,"|");
strcat(buffer,s[j].nob);
strcat(buffer,"|");
strcat(buffer,s[j].cost);
strcat(buffer,"\n");



out1<<buffer;
 
}

out1.close();
cout<<"\n_____________________________________________________________________\n";
}

int get_bill()
{
int I=0;
fstream file2;

	
	file2.open("bill.txt",ios::in);
	if(!file2)
	{
		return 0;
	}
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(stdrec[I].ind,5,'|');
		file2.getline(stdrec[I].bn,5,'|');
		file2.getline(stdrec[I].bna,25,'|');
		file2.getline(stdrec[I].customer,25,'|');
		file2.getline(stdrec[I].cost,5,'|');
		file2.getline(stdrec[I].date,10,'\n');
		I++; 	
 	}
	I--;
	file2.close();
	return I;
}




void add_bill()
{
char buf3[100],buf4[100];
fstream file1,file2;
int I,cnt;
student s2;
cout<<"\n_____________________________________________________________________\n";
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tBILL\n";
cout<<"\n_____________________________________________________________________\n";
	cnt=get_bill();

	file1.open("index1.txt",ios::out|ios::app);
	if(!file1)
	{
		cout<<"\nError !\n";
		exit(0);
	}

	file2.open("bill.txt",ios::out|ios::app);
	if(!file2)
	{
		cout<<"\nError !\n";
		exit(0);
	}

	cout<<"\nEnter The No. Of Bills To Add : ";
	cin>>no;
	

	for(I=cnt; I<(cnt+no); I++)
   {     
       cout<<"\nEnter the Bill Details :\n";              
		cout<<"\nBook No       : ";
		cin>>s2.bn;
		cout<<"\n";
		cout<<"\nBook Name     : ";
		cin>>s2.bna;
		cout<<"\n";
		cout<<"\nCustomer Name : ";
		cin.ignore();
        cin.getline(s2.customer,25);
		cout<<"\n";
		cout<<"\nCost          : ";
		cin>>s2.cost;
		cout<<"\n";
		cout<<"\nDate          : ";
		cin>>s2.date;
		cout<<"\n\n";

		sprintf(buf4,"%s|%d\n",s2.bill_no,I);
		file1<<buf4;

		sprintf(buf3,"%d|%s|%s|%s|%s|%s\n",I,s2.bn,s2.bna,s2.customer,s2.cost,s2.date);
		file2<<buf3;
	}
		file1.close();
		file2.close();
		cout<<"\n_____________________________________________________________________\n";
}


void display_bill()
{
fstream file2;
student s2;
	cout<<"\n_____________________________________________________________________\n";
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tDISPLAY BILLS\n";
cout<<"\n_____________________________________________________________________\n";
	file2.open("bill.txt",ios::in);
cout<<"\n\n"<<"\n\t\t\t\t\t\t\t\t\t\t\tBill details  \n\n";
//cout<<"Index"<<setw(25)<<"Book Number"<<setw(30)<<"Book Name"<<setw(33)<<"Author Name"<<setw(35)<<"Number Of Books"<<setw(19)<<"Price"<<setw(10)<<endl;
cout<<"Index"<<setw(25)<<"Book Number"<<setw(30)<<"Book Name"<<setw(33)<<"Customer Name"<<setw(30)<<"Cost"<<setw(25)<<"Date"<<setw(10)<<endl;  
	while(!file2.fail()) //Unpacking record data
 	{
		file2.getline(s2.ind,5,'|');
		file2.getline(s2.bn,5,'|');
		file2.getline(s2.bna,25,'|');
		file2.getline(s2.customer,25,'|');
		file2.getline(s2.cost,5,'|');
		file2.getline(s2.date,10,'\n');
        cout<<"\n";
cout<<s2.ind<<setw(25)<<s2.bn<<setw(35)<<s2.bna<<setw(35)<<s2.customer<<setw(25)<<s2.cost<<setw(25)<<s2.date<<"\n";
//cout<<s.ind<<setw(25)<<s.bn<<setw(35)<<s.bna<<setw(35)<<s.ana<<setw(25)<<s.nob<<setw(25)<<s.cost<<"\n";	 	 	
 	}
	file2.close();
cout<<"\n_____________________________________________________________________\n";
}

void login()
{
fstream file2;
char xc[50];
char buff2[60];
   // current date and time on the current system
    time_t now = time(0);

   // convert now to string form
   char* date_time = ctime(&now);
strcpy(xc,date_time);
//cout<<"xc = "<<xc;

   int id;
   
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\t  LOG-IN\n";

   cout<<"\n\n\n\n\n";
   cout<<"Enter Your Id To Continue\n\n";
   cout<<"\n-> ";
   cin>>id;
   cout<<"\n";

   if(id==123 | id==456 | id==789)
   {
   file2.open("time.txt",ios::out|ios::app);
   sprintf(buff2,"%d|%s\n",id,date_time);
   file2<<buff2;
   file2.close();
   }
   
 else 
     {
		  int ch;
       cout<<"\n1:Login Again\n\n2:Exit\n\n";
	   cout<<"Enter Your Choice : ";
	   cin>>ch;
	   cout<<"\n";
	   switch (ch)
	   
	   {
	   case 1:login();
		      break;
	   case 2:exit(0);
	   		  break;
	   default:
		   break;
	   }
	 }
  // cout << "The current date and time is: " << date_time << endl;


}

void login_history()
{
fstream file7;

char date_time[25],ide[5];

	file7.open("time.txt",ios::in);
cout<<"\n_____________________________________________________________________\n";
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tLOGIN HISTORY\n";
cout<<"\n_____________________________________________________________________\n";
cout<<"\n";
cout<<"Id"<<"\t"<<"Date And Time"<<"\t\n"<<endl; 
	while(!file7.fail()) //Unpacking record data
 	{
		
		file7.getline(ide,5,'|');
        file7.getline(date_time,25,'\n');
		
        cout<<ide<<"\t"<<date_time<<"\n";
	 	
 	}
	file7.close();
	cout<<"\n_____________________________________________________________________\n";

}

int main()
{
int choice;
 

cout<<"\n_____________________________________________________________________\n";
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tBOOK STORE\n";
cout<<"\n_____________________________________________________________________\n";
   login();  
	for(;;)
	{ 
		cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
cout<<"\n_____________________________________________________________________\n";
cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tCONTROL PANEL\n";
cout<<"\n_____________________________________________________________________\n";
		cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\t1:Add Record\n\n";
		cout<<"\t\t\t\t\t\t\t\t\t\t\t2:Search Record\n\n\t\t\t\t\t\t\t\t\t\t\t3:Delete Record\n\n";
		cout<<"\t\t\t\t\t\t\t\t\t\t\t4:Display Record\n\n";
        cout<<"\t\t\t\t\t\t\t\t\t\t\t5:Modify Record\n\n\t\t\t\t\t\t\t\t\t\t\t6:Bill\n\n\t\t\t\t\t\t\t\t\t\t\t7:Display Bill\n\n\t\t\t\t\t\t\t\t\t\t\t8:Display Login History\n\n";
		
		cout<<"\nEnter Your Choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1: add_record(); break;
			case 2: search_record(); break;
			case 3: delete_record(); break;
			case 4: display_records();break;
            case 5: modify();break;
            case 6: add_bill();break;
            case 7: display_bill();break;
            case 8: login_history();break;
			default:
			cout<<"\nInvalid choice !\n"; exit(0);	
		}
	}
}
