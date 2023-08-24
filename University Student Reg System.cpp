#include<iostream>   
#include<cstring>    /* library to acces string*/
#include<fstream>    /* library to access file*/
#include <cstdlib>
#include<iomanip>
using namespace std;
class std_base						/* Declaration of a class named std_base */
{
	public:
		string name;
		char grade[1000];
		char status;
		int roll_no,number;
		int credit_hours[1000]={0};
		string course_code[1000];
		string course_name[1000];
		float GPA,amount;
	get_data()						/* function to take data from the user */									
	{
		
		cout<<"Enter student's roll number :";
		cin>>roll_no;
		cin.ignore();
		cout<<"Enter student's name: ";
		getline(cin,name);
		cout<<"Enter the number of courses:";
		cin>>number;
		cin.ignore();
		cout<<"Enter all the courses, their codes and credit hours :"<<endl;
		for(int i=0;i<number;i++)
		{
			cout<<"Course"<<i+1<<":"<<endl;
			cout<<"Name : ";
			cin.ignore();
			getline(cin,course_name[i]);
			cout<<"Code :";
			getline(cin,course_code[i]);
			cout<<"Credit hours:";
			cin>>credit_hours[i];
			cout<<"Grade :";
			cin>>grade[i];
		}
	}
	float g_p_a()					/* function to calculate gpa of a student */
	{
		int c_h=0;
		float gpa=0;
		for(int i=0;i<number;i++)
		{
			c_h=c_h+credit_hours[i];
		}
		for(int i=0;i<number;i++)
		{
			if(grade[i]=='A')
			gpa=gpa+credit_hours[i]*4;
			else if(grade[i]=='B')
			gpa=gpa+credit_hours[i]*3;
			else if(grade[i]=='C')
			gpa=gpa+credit_hours[i]*2;
			else if(grade[i]=='D')
			gpa=gpa+credit_hours[i]*1;
			else if(grade[i]=='F')
			gpa=gpa+credit_hours[i]*0;
		}
		GPA=gpa/c_h;
	}
	int check_status()						/* function to check the fee status of a student */
	{
	 	cout<<"Is the fees paid ?(Press Y if paid / Press N if not paid): ";
	 	cin>>status;
	}
};

void menu()								/* Menu for the user */
{
	cout<<"******WELCOME TO REGISTER OFFICE******"<<endl;
	cout<<"Press 1 to register a student"<<endl;
	cout<<"Press 2 to check a student's record"<<endl;
	cout<<"Press 3 to exit"<<endl;
}

int main()
{
	int choice; 
	int num;
	do							/* do while loop to allow user to choose the menu several times*/
	{
		menu();
		cin>>choice;
		system("CLS");      /* clearing the screen to improve visibility*/
		
	switch(choice)           /* switch to run the program according to user's choice*/
	{
		case 1:
			{
				ofstream myfile;		/* writing to file */
				myfile.open("file3.txt",ios::in|ios::out|ios::app); /* file has been opened*/
				cout<<"How many students you want to register?";
				cin>>num;
				system("CLS");
				std_base obj[num];
				for(int i=0;i<num;i++)
				{
					obj[i].get_data();   /* Object of class std_base being created in for loop */
					obj[i].check_status();
					myfile<<"Student name: "<<obj[i].name<<endl;
					myfile<<"Student ID: "<<obj[i].roll_no<<endl;		 /* Student data saving in file */
					if(obj[i].status=='N')
					{												
						cout<<"Enter the balance amount: ";
						cin>>obj[i].amount;
						myfile<<"Due amount: "<<obj[i].amount<<endl;
					    myfile<<"Fee status: "<<obj[i].status<<endl;    /* Fee status being updated in the file*/
					}
					else if(obj[i].status=='Y')
					{
					    myfile<<"Fee status: "<<obj[i].status<<endl;
					}
					myfile<<left<<setw(15)<<"Course name ";
		     		myfile<<left<<setw(15)<<"Course code ";
					myfile<<left<<setw(10)<<"Course credit hours "<<endl;			
					for(int j=0;j<obj[i].number;j++)
					{
						myfile<<left<<setw(15)<<obj[i].course_name[j];		/* Data being stored in tabular form*/
						myfile<<left<<setw(15)<<obj[i].course_code[j];
						myfile<<left<<setw(10)<<obj[i].credit_hours[j]<<endl;
					}
					obj[i].g_p_a();
					myfile<<"GPA: "<<obj[i].GPA<<endl;
					myfile<<"."<<endl;
				}
					myfile.close();
					system("CLS");
			}
			break;
			case 2:
				{	
					string rollno,line;
					int loc_1,loc_2;
					cout<<"Enter the roll number of the student : ";
					cin>>rollno;
					ifstream myfile("file3.txt");     /* Reading data of a student from a file */
					int var=0;
					if(myfile.is_open())
					{
						while(!myfile.eof())
						{	
							loc_2=-1;
							getline(myfile,line);      /* Program is searching for a specific line in the file*/
							loc_1=line.find(rollno);
							if(loc_1!=-1||var==1)
							{
								loc_2=line.find("N");  /* Fee status check*/
								if(loc_2!=-1)
								{
									cout<<"Fee not paid !"<<endl;
									cout<<line<<endl;
								}
								else
								{
									cout<<line<<endl;
									loc_2=line.find(".");
									var=1;	
						
								}
								
							}
							if(loc_2!=-1)                /* Ending the reading */
							break;
						}
					}
				system("PAUSE");	
				system("CLS");
				}
				break;
			
	}	
		
} while(choice!=3);

}
	
