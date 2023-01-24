#include<stdio.h>
#include<windows.h>
#include<stdbool.h>
#include<string.h>

int originX=5, originY=2, height, width;	//global variable

struct student
{
	char Id[15];
	char Name[30];
	char Email[50];
	int Grade;
	float Percentage;
	int ContactNo;
};

struct student stu;

COORD coordinates;

void CursorPosition(int x, int y)
{
	coordinates.X=x;
	coordinates.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}

void DrawRectangle()
{
	int x,y;
	width= GetScreenWidth()-2*originX;
	height= GetScreenHeight()-originX;
	
//	top left corner
	CursorPosition(originX,originY);
	printf("%c",201);
	
//	top horizontal
	for(x=originX+1;x<originX+width;x++)
	{
		CursorPosition(x,originY);
		printf("%c",205);
	}

//	top right corner
	CursorPosition(originX+width,originY);
	printf("%c",187);
	
//right vertical
	for(y=originY+1;y<originY+height;y++)
	{
		CursorPosition(originX+width,y);
		if(y==8)
		{
			printf("%c",185);
		}
		else
		{
			printf("%c",186);
		}
	}

//	bottom Right Corner
	CursorPosition(originX+width,originY+height);
	printf("%c",188);
	
//	Bottom Horizontal
	for (x=originX+1;x<originX+width;x++)
	{
		CursorPosition(x,originY+height);
		if(x==width/2)
		{
			printf("%c",202);
		}
		else
		{
			printf("%c",205);
		}
	}

//	Left Bottom corner
	CursorPosition(originX,originY+height);
	printf("%c",200);

//	left vertical
	for(y=originY+1;y<originY+height;y++)
	{
		CursorPosition(originX,y);
		if(y==8)
		{
			printf("%c",204);
		}
		else
		{
			printf("%c",186);
		}
	}
	
//	Central Horizontal line
	for(x=originX+1;x<originX+width;x++)
	{
		CursorPosition(x,8);
		if(x==width/2)
		{
			printf("%c",203);
		}
		else
		{
			printf("%c",205);
		}
	}
	
//	Central vertical line
	for(y=originY+7;y<originY+height;y++)
	{
		CursorPosition(width/2,y);
		printf("%c",186);
	}
}

//Sets title in the table
SetTitle()
{
	CursorPosition(width*0.46,originY+2);
	printf("Student Management System");
	CursorPosition(width*0.44,originY+3);
	printf("Texas College of Management and IT");
	CursorPosition(width*0.45,originY+4);
	printf("Mitrapark, Chahabil, Kathmandu");
}

//Returns console screen width
GetScreenWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	
	return columns;
}

//Return console screen height
GetScreenHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	
	return rows;
}

//Store student details in a file
AddStudent()
{
	int x=width/2+2, y=originY+8;
	CursorPosition(x,y);
	printf("Add New Student");
	FILE *openfile;
	openfile=fopen("student_record.txt","ab+");
	
//	drive full or same file with current name, then file doesnt create
	if(openfile==NULL)
	{
		MessageBox(0,"Error in opening/creating file.","Warning",0);
	}
	else
	{
		fflush(stdin);  
		
		CursorPosition(x,y+2);
		printf("ID: ");
		gets(stu.Id);
		
		CursorPosition(x,y+4);
		printf("NAME: ");
		gets(stu.Name);
		
		CursorPosition(x,y+6);
		printf("EMAIL: ");
		gets(stu.Email);
		
		CursorPosition(x,y+8);
		printf("CONTACT NUMBER: ");
		scanf("%d",&stu.ContactNo);
		
		CursorPosition(x,y+10);
		printf("GRADE: ");
		scanf("%d",&stu.Grade);
		
		CursorPosition(x,y+12);
		printf("PERCENTAGE: ");
		scanf("%f",&stu.Percentage);
		
		fwrite(&stu,sizeof(stu),1,openfile);		//store structure variable in file
		
		MessageBox(0,"New Student is added successfully.","Success",1);				
	}
	fclose(openfile);
}

//Clear right side of the box
void ClearScreen()
{
	int x,y;
	for(x=width/2+1;x<originX+width;x++)
	{
		for(y=originY+7;y<originY+height;y++)
		{
			CursorPosition(x,y);
			printf(" ");
		}
	}
}

//Search Students for Record
void SearchStudent()
{
	int x=width/2+2,y=originY+8;
	CursorPosition(x,y);
	printf("Search Student From ID.");
	char student_id[15];
	bool isFound=false;
	
	CursorPosition(x,y+2);
	printf("Enter Student ID: ");
	fflush(stdin);
	gets(student_id);
	
	FILE *openfile;
	openfile=fopen("student_record.txt","rb");
	while(fread(&stu,sizeof(stu),1,openfile)==1)
	{
		if(strcmp(student_id,stu.Id)==0)
		{
			isFound=true;
			break;
		}
	}
	if(isFound==true)
	{
		CursorPosition(x,y+4);
		printf("Student Record Available.");
		
		CursorPosition(x,y+6);
		printf("ID: %s",stu.Id);
		
		CursorPosition(x,y+8);
		printf("NAME: %s",stu.Name);
			
		CursorPosition(x,y+10);
		printf("EMAIL: %s",stu.Email);
		
		CursorPosition(x,y+10);
		printf("COTACT NUMMBER: %d",stu.ContactNo);
		
		CursorPosition(x,y+12);
		printf("GRADE: %d",stu.Grade);
		
		CursorPosition(x,y+6);
		printf("PERCENTAGE: %f",stu.Percentage);

	}
	else
	{
		CursorPosition(x,y+2);
		printf("Sorry, No record found in database.");
	}
	fclose(openfile);
}

ModifyStudent()
{
	int x=width/2+2,y=originY+8;
	CursorPosition(x,y);
	printf("Modify Student From ID.");
	char student_id[15];
	bool isFound=false;
	
	CursorPosition(x,y+2);
	printf("Enter Student ID to modify: ");
	fflush(stdin);
	gets(student_id);
	
	FILE *openfile;
	openfile=fopen("student_record.txt","rb+");
	
	while(fread(&stu,sizeof(stu),1,openfile)==1)
	{
		if(strcmp(student_id,stu.Id)==0)
		{
			//Modify related codes
			
			fflush(stdin);
			CursorPosition(x,y+4);
			printf("ID: ");
			gets(stu.Id);
			
			CursorPosition(x,y+6);
			printf("NAME: ");
			gets(stu.Name);
			
			CursorPosition(x,y+8);
			printf("EMAIL: ");
			gets(stu.Email);
			
			CursorPosition(x,y+10);
			printf("CONTACT NUMBER: ");
			scanf("%d",&stu.ContactNo);
			
			CursorPosition(x,y+12);
			printf("GRADE: ");
			scanf("%d",&stu.Grade);
			
			CursorPosition(x,y+14);
			printf("PERCENTAGE: ");
			scanf("%f",&stu.Percentage);
			
			fseek(openfile,-sizeof(stu), SEEK_CUR);
			fwrite(&stu,sizeof(stu),1,openfile);
			CursorPosition(x,y+16);
			printf("Student Updated Successfully.");
			
			isFound=true;
			break;
		}
	}
	
	if(isFound==false)
	{
		//msg sadas
	}
	fclose(openfile);
}

DeleteStudent()
{
	int x=width/2+2, y=originY+8;
	CursorPosition(x,y);
	printf("Delete Student Record.");
	
	char student_id[15];
	bool isFound=false;

	CursorPosition(x,y+2);
	printf("Enter ID to Delete.");
	fflush(stdin);
	gets(student_id);
	
	FILE *openfile, *tempfile;
	openfile=fopen("student_record.txt","rb");
	tempfile=fopen("temporary_record.txt","wb");
	
	while(fread(&stu,sizeof(stu),1,openfile)==1)
	{
		if(strcmp(student_id,stu.Id)!=0)
		{
			fwrite(&stu,sizeof(stu),1,tempfile);
		}
		else
		{
			isFound=true;
			
		}
	}
	
	fclose(openfile);
	fclose(tempfile);
	remove("student_record.txt");
	rename("temporary_record.txt","student_record.txt");
	CursorPosition(x,y+4);
	if("isFound=true")
	{
		printf("Student Record Deleted Successfully");
	}
	else
	{
		printf("Student Not Found.");
	}
}

//Lists all students name
ListStudent()
{	
//	for table
	int x=width/2+2, y=originY+10;
	
//	for title
	int a=width/2+width/2*0.42, b=originY+8;
	CursorPosition(a,b);
	printf("Student Record List.");
	
	int partition=(originX+width-width/2)/7;
	
	CursorPosition(x,y);
	printf("ID");
	CursorPosition(x+partition,y);
	printf("Name");
	CursorPosition(x+partition*2,y);
	printf("Email");
	CursorPosition(x+partition*3,y);
	printf("Contact");
	CursorPosition(x+partition*4,y);
	printf("Class");
	CursorPosition(x+partition*5,y);
	printf("Percentage");
	CursorPosition(x+partition*6,y);
	printf("Rank");
	
	DrawLine(originY+1);
	FILE *openfile;
	openfile=fopen("student_record.txt","rb");
	
	int i=0;
	//Read student
	while(fred(&stu,sizeof(stu),1,openfile)==1)
	{
		stu_array[i]=stu;
		total_student=i+1;
		i++;
	}
	
}

//Draw line inside the right side of the table
DrawLine(y_cord)
{
	int i;
	for(i=width/2+2;i<width+originX-1;i++)
	{
		CursorPosition(i,y_cord);
		printf("=");
	}
}

ChooseOptions()
{
	int option;
	
	while(1)
	{
		CursorPosition(originX+2,originY+8);
		printf("Choose 1. Add Student.");
		
		CursorPosition(originX+2,originY+10);
		printf("Choose 2. Search Student");
		
		CursorPosition(originX+2,originY+12);
		printf("Choose 3. Modify Student Detail.");
		
		CursorPosition(originX+2,originY+14);
		printf("Choose 4. Delete Student Detail.");
		
		CursorPosition(originX+2,originY+16);
		printf("Choose 5. List of Student.");
		
		CursorPosition(originX+2,originY+18);
		printf("Choose 6. Exit.");
		
		CursorPosition(originX+2,originY+20);
		printf("Enter your choice.");
		
		scanf("%d",&option);
		
		switch(option)
		{
			case 1:
				ClearScreen();
				AddStudent();
				break;
				
			case 2:
				ClearScreen();
				SearchStudent();
				break;
				
			case 3:
				ClearScreen();
				ModifyStudent();
				break;
				
			case 4:
				ClearScreen();
				DeleteStudent();
				break;
				
			case 5:
				ClearScreen();
				ListStudent();
				break;
				
			case 6:
				CursorPosition(0,height+originY+1);
				exit(0);
				break;
				
			default:
				MessageBox(0,"Please Enter correct Option.","Warning",0);  //default, message k display garni, message box ko title or warning, kasto khalko box display garne ta
		}
	}
}

int main()
{
	SetConsoleTitle("STUDENT MANAGEMENT SYSTEM - TCMIT");
	system("color F0");
	
//	to make Full Screen
	ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
	
	GetScreenWidth();
	GetScreenHeight();
	
	DrawRectangle();
	SetTitle();
	ChooseOptions();
	
	
	return 0;
}