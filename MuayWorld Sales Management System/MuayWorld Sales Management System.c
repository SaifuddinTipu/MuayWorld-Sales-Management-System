//=================================================================================================
// MuayWorld Sales Management System

//=================================================================================================
// Md. Saifuddin Tipu

//=================================================================================================


#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


//constant declarations

#define LETTER 20
#define TAG 15
#define DISCOUNT 0.10

//function prototype declaration
void interface(); //display interface
void Mainmenu();  //display main menu
void SUBmenu();   //display sub menu
void records();   //display list of record
void edit();      //display menu for edit
void exit();      //exit program
void items(int options); //display the items from data

void grandtotal();  //calculate for bill and display the receipt
void member();      //get info from customer
void add();         //add new item(s) in data
void del_item();    //delete item(s) in data
void edit_item();   //edit current item(s) in data
void bill_2(int options); /*Calculate the price,discount,make change in quantity*/
void bill(int options);
void gloves1();
int check_items(char[],int options); //check the validity of item

//structure for record of data
typedef struct{
	char  type[20];         //item type
    char  name[LETTER];     //item name
    char  ID[TAG];          //item ID
    float price;            //item price
    int   quantity;         //item quantity
} record;
record item; //item is variable to the structure

//structure to keep data of items and receipt
typedef struct{
	int   id_receipt;       //receipt id
	char  cusname[30];      //customer name
	char  member[20];       //member
	char  type[20];         //item type
	char  item_name[LETTER];//item name
	char  id[TAG];          //item id
	int   quan;             //item quantity
	float cash;             //cash
	float change;           //change after payment
	int   dd[20];               //day
	int   mm[20];               //month
	int   yy[20];               //year
	float total;            //total price
	float discount;         //discount
	float discount2;        //total discount
	float memberPrice;      //assign the price to this variable
}dec;
dec info;  //info is variable to this structure

int main()
{
	Mainmenu();//function call

}
//function definiton for interface.Display the interface
void interface()
{

      printf ("\n");
      printf ("                               o8                                  \n");
      printf ("                               888              o888b              \n");
      printf ("        ooo. .oo. .ooo.      888oooo.           oood88p            \n");
      printf ("        888P'Y88bP'Y88b        d88               oo8               \n");
      printf ("        888   888   888        888   888          888              \n");
      printf ("        888   888   888        888   888      dob  888             \n");
      printf ("       o888o o888o o888o       `Y8bod8P'      oooooob              \n");

}

//function definiton for Mainmenu
void Mainmenu()
{
	//variable declaration
	int i;
	int choice;
	const char *menu[] = {" Purchase item"," Edit inventory"," Records"," Exit"};  //string for menu

	do
	{
	system("cls");  //new screen
	interface();	//call function interface
	printf("\n");
	printf ("\t Welcome to MuayWorld Muay Thai Shop!\n");
	printf("\t\t     Main Menu\n");
	for(i=0;i<4;i++)
	{
		printf("\t\t%d. %s\n",i+1,menu[i]); //display menu
	}
	printf("\t\tChoice: ");
	scanf("%d",&choice); //get input for choice
	switch(choice)
	{
	//choice 1
	case 1:
		member();  //call function
		SUBmenu(); //call function
		break; //break switch
	//choice 2
	case 2:
		edit(); //call function
		 //break switch
	//choice 3
	case 3:
		records(); //call function
		//break switch
	//choice 4
	case 4:
		exit();
		break;//break switch
	//if choice not 1-4
	default:
		printf("Wrong input.Please enter again\n");
		break; //break switch
	}
	}while(choice!=4);
}
//fuction definition for member
void member()
{
	static int id=1; //declare static variable
	static int i=1;

	FILE *fptr;  //fptr=receipt.dat file pointer
	fptr=fopen("receipt.dat","wb");
	system("cls"); //new screen
	interface();
    printf("\t\tReceipt ID: %04d\n",id);
	info.id_receipt=id; //assign id to info.id_receipt
	id++;               //increase id by 1
	printf("\t\tEnter customer name: ");
	scanf("%s",info.cusname); //get input and put it in info.cusname
	printf("\t\tMember(Y/N) : ");
	getchar();  //gets a character
	if(toupper(getchar())=='Y')
	{
		strcpy(info.member,"Member");  //copy "Member" into info.member if Y

	}
	else
	strcpy(info.member,"Not member"); //copy "Not member" into info.member if N

	printf("\t\tEnter date:\n ");
	printf("\t\tDay  : ");  //Get date//
	scanf("%d",&info.dd[i]);   //get input for day//
	printf("\t\tMonth: ");
	scanf("%d",&info.mm[i]);    //get input for month//
	printf("\t\tYear : ");
	scanf("%d",&info.yy[i]);  //get input for year
	i++;
	fwrite(&info,sizeof(info),1,fptr); //transfer bytes in memory into receipt.dat

	fclose(fptr);  //close file
	SUBmenu();  //go to sub menu

}

//function definiton for SUBmenu
void SUBmenu()
{
	//variable declaration
	int options,i;
	const char *menu[] = {" Gloves"," Gloves"," Guards"," Tshirt"," Shorts"," Shorts"," Training Pads"," Total","Back to Main Menu"};  //array that kept string for menu
	const char *menu2[] = {"Muay Thai Gloves","MMA Gloves","Shin Guard","Combat","Muay Thai","Muay Boran","-","",""};  //array that kept string for menu2

    do
	{
	system("cls");  //new screen
	interface();	//call function
	printf("Purchase item\n");
	printf("Options     List of items\t  Category\n");
	for(i=0;i<9;i++)
	{
		printf("%2d. %20s\t  %s\n",i+1,menu[i],menu2[i]); //display menu
	}
	printf("Choose:");
	scanf("%d",&options);  //get input for options
	switch(options)
	{
		//choice 1
	case 1:
		system("cls"); //new screen
		interface(); //call function
		printf("\nGLOVES: Muay Thai Gloves\n");
		printf(" ItemID  Item Name     Price  Quantity\n");
		items(options);  //call function
		gloves1();  //call function
		break;  //exit switch
		//choice 2
	case 2:
		system("cls"); //new screen
		interface(); //call function
		printf("\nGLOVES: MMA Gloves\n");
		printf(" ItemID  Item Name     Price  Quantity\n");
		items(options); //call function
		bill_2(options); //call function
		break; //exit switch
		//choice 3
	case 3:
		system("cls"); //new screen
		interface(); //call function
		printf("\nGUARDS: Shin Guard\n");
		printf(" ItemID  Item Name     Price  Quantity\n");
		items(options); //call function
		bill_2(options); //call function
		break; //exit switch
		//choice 4
	case 4:
		system("cls"); //new screen
		interface(); //call function
		printf("\nTSHIRT: Combat\n");
		printf(" ItemID  Item Name     Price  Quantity\n");
		items(options); //call function
		bill(options);//call function
		break; //exit switch
		//choice 5
	case 5:
		system("cls"); //new screen
		interface(); //call function
		printf("\nSHORTS: Muay Thai\n");
		printf(" ItemID  Item Name     Price  Quantity\n");
		items(options); //call function
		bill(options);//call function
		break; //exit switch
		//choice 6
	case 6:
		system("cls");  //new screen
		interface(); //call function
		printf("\nSHORTS: Muay Boran\n");
		printf(" ItemID  Item Name     Price  Quantity\n");
		items(options);//call function
		bill(options);//call function
		break; //exit switch
		//choice 7
	case 7:
		system("cls");  //new screen
		interface(); //call function
		printf("\nTRAINING PADS\n");
		printf(" ItemID  Item Name     Price  Quantity\n");
		items(options); //call function
		bill(options);//call function
		break; //exit switch
		//choice 8
	case 8:
		system("cls");  //new screen
		interface(); //call function
		printf("Total all:\n");
		grandtotal(); //call function
		break; //exit switch
		//choice 9
	case 9:
		Mainmenu(); //call function
		//wrong input
	default :
		printf("Please enter again");
		break; //exit switch
	}
	}while(options!=9);  //the options is not in range 1 to 9
}

//function definiton for items
void items(int options)
{
	//variable declaration
	char file_item[10];

	sprintf(file_item,"%d.dat",options); //stored string into file_item

	FILE *fptr;  //file_item file pointer
	fptr = fopen(file_item,"rb"); //open file in reading binary mode
	rewind(fptr); //repositions file pointer to beginning of file

	//print description of item according to number of items stored in file
	while(fread(&item,sizeof(item),1,fptr))
	{
		printf("%7s\t%10s  \t%3.2f\t%3d\n",item.ID,item.name,item.price,item.quantity);
	}
	fclose(fptr); //close file

}

//function definition for gloves1
void gloves1()
{
	int size=0; //initialize size to 0
	printf("**enter \"f\" to finish input**");

	FILE *fptr; //1.dat file pointer

	//fopen opens file;exits program if file could not be opened
	if((fptr=fopen("1.dat","rb+"))==NULL)
	{
		printf("File could not be opened\n");
	}
	while(1){
	   	printf("\n");
		printf("Enter item name:");
		scanf("%s",info.item_name);       //get input for item name
		if(strcmp(info.item_name,"f")==0) //break the while loop if user enter 'f'
		break;
		printf("enter quantity:");
		scanf("%d",&info.quan);       //get input for quantity
		rewind(fptr);                //reposition the file pointer to beginning

		while(fread(&item,sizeof(item),1,fptr)){  //read all contents in file
			if((strcmp(item.name,info.item_name)==0)){  //comparing 2 strings

				strcpy(info.id,item.ID);           //copy item id into info.id
				strcpy(info.type,item.type);        //copy item type into info.type
				info.total=item.price*(info.quan);  //calculate the price with quantity
				info.memberPrice=info.total;        //assign the info.total to info.memberPrice
				size=sizeof(item);                  //assign the sizeof to size variable
				item.quantity=item.quantity-(info.quan);  //calculate the new quantity
				fseek(fptr,-size,SEEK_CUR);               //seek position in file to correct record
				fwrite(&item,sizeof(item),1,fptr);      //write information in 1.dat


				FILE *fcptr;                              //receipt.dat file pointer
				fcptr=fopen("receipt.dat","ab+");        //open file
				fwrite(&info,sizeof(info),1,fcptr);     //write all informations in file
				fclose(fcptr);                         //close file

				FILE *rec;    //Records.dat file pointer
				rec=fopen("Records.dat","ab+");
				fwrite(&info,sizeof(info),1,rec);  //write all informations in file
				fclose(rec);  //close file

				break; //exit loop


			}
		}
	}
		fclose(fptr); //close file
		SUBmenu(); //go to sub menu
}

//function definition for bill_2
void bill_2(int options)
{
	//variables declarations
	int size=0;
	char file_item[10];

	sprintf(file_item,"%d.dat",options);  //stored string into file_item

	FILE *fptr;  //file_item file pointer
	printf("**enter \"f\" to finish input**");
    //fopen opens file;exits program if file could not be opened
	if((fptr=fopen(file_item,"rb+"))==NULL)
	{
		printf("File cannot be found\n");
		printf("Please check the file\n");
	}
	while(1){
	   	printf("\n");
		printf("Enter item id:");
		scanf("%s",info.id);    //get input for item id
		if(strcmp(info.id,"f")==0)  //exit while loop
		break;
		printf("enter quantity:");
		scanf("%d",&info.quan); //get input for quantity
		rewind(fptr);           //reposition the file pointer to beginning
        //read all informations in file
		while(fread(&item,sizeof(item),1,fptr)){
			if((strcmp(item.ID,info.id)==0)){ //comparing 2 strings

				strcpy(info.item_name,item.name);  //copying item name to info.item
				strcpy(info.type,item.type);       //copying the item type into info.type
				info.total=item.price*(info.quan); //price of item with quantity
				info.memberPrice=info.total;       //assigning variable
				size=sizeof(item);                 //assign the sizeof to size variable
				item.quantity=item.quantity-(info.quan);//calculate the new quantity
				fseek(fptr,-size,SEEK_CUR);    //seek position in file to correct record in file
				fwrite(&item,sizeof(item),1,fptr);  //write updated quantity over old record in file


				FILE *fcptr;                         //receipt.dat file pointer
				fcptr=fopen("receipt.dat","ab+");     //open file for updating
				fwrite(&info,sizeof(info),1,fcptr);  //write all informations in file
				fclose(fcptr);  //close file

				FILE *rec;                          //Records.dat file pointer
				rec=fopen("Records.dat","ab+");     //open file for updating
				fwrite(&info,sizeof(info),1,rec);   //write all informations in file
				fclose(rec);  //close file

				break; //exit loop
			}

		}
	}

		fclose(fptr);  //close file
		SUBmenu();  //go to sub menu
}

//function definiton for bill
void bill(int options)
{
	//variables declaration
    int q=0;	//assign q with 0
	int size=0;  //assign size with 0
	int i;
	float total=0,gtotal=0;  //assign total and gtotal with 0
	char file_item[10];  //array file item


	sprintf(file_item,"%d.dat",options);  //stored string into file_item

	printf("**enter \"f\" to finish input**");

	FILE *fptr; //file_item file pointer
	//open file;exit program if file could not be open
	if((fptr=fopen(file_item,"rb+"))==NULL)
	{
		printf("File could not be found\n");
	}
	while(1){
	   	printf("\n");
		printf("Enter item ID:");
		scanf("%s",info.id);         //get input for item id
		if(strcmp(info.id,"f")==0)  //exit while loop
		break;
		printf("enter quantity:");
		scanf("%d",&info.quan);     //get input for item quantity
		rewind(fptr);  //reposition the file pointer to beginning
        //reads all informations in file
		while(fread(&item,sizeof(item),1,fptr)){
			if((strcmp(item.ID,info.id)==0)){  //comparing 2 strings

				strcpy(info.item_name,item.name);  //copying item name to info.item_name
				strcpy(info.type,item.type);       //copying item type to info.type
				if(strcmp(info.member,"Member")==0)  //if string in info.member is "Member"
				{
					info.discount=item.price*(info.quan)*DISCOUNT;  //calculate the discount
					info.discount2=info.discount2+info.discount;    //sum up all discount
					info.total=item.price*info.quan;                //price of item according to quantity without discount
					info.memberPrice=info.total-info.discount;		//price item after discount
					size=sizeof(item);                              //assign variable
				    item.quantity=item.quantity-(info.quan);        //update the change of quantity
				    fseek(fptr,-size,SEEK_CUR);                     //move file pointer to correct record
				    fwrite(&item,sizeof(item),1,fptr);              //write the changes for quantity


				}
				if (strcmp(info.member,"Not member")==0)            //if string in info.member is "Not member"
				{
					info.total=item.price*info.quan;                //calculate price according to quantity
					info.memberPrice=info.total;                    //assign info.total to info.memberPrice
				    size=sizeof(item);                               // assign sizeof to size
				    item.quantity=item.quantity-(info.quan);         //calculate the new quantity
				    fseek(fptr,-size,SEEK_CUR);                      //move file to correct recor
				    fwrite(&item,sizeof(item),1,fptr);               //write the new quantity
				}


				FILE *fcptr;  //receipt.dat file pointer
				fcptr=fopen("receipt.dat","ab+"); //open file for updating
				fwrite(&info,sizeof(info),1,fcptr);  //writes all informations into the file
				fclose(fcptr);  //close file

				FILE *rec;  //Records.dat file pointer
				rec=fopen("Records.dat","ab+");  //open file for updating
				fwrite(&info,sizeof(info),1,rec);  //writes all informations into the file
				fclose(rec);

				break; //exit loop
			}

		}
	}

		fclose(fptr); //close file
		SUBmenu();
}
//function definition for grandtotal
void grandtotal()
{
	//variables declarations
	    float grand_total=0;
		float cash;
		int i=1;
		static int m=1;

	    FILE *fcptr; //receipt.dat file pointer
		FILE *fptr;  //Receipt2.dat file pointer

	    fcptr = fopen("receipt.dat","rb"); //open file
		fptr=fopen("Receipt2.txt","a+");

		rewind(fcptr);  //repostions file pointer to beginning
		fread(&info,sizeof(info),1,fcptr); //reads information in file

		printf("\t\t     MuayWorld Muay Thai Shop\n");        /*display all informations stored in file to screen*/
		printf("\t\t        Purchase Receipt\n");
		printf("Receipt No: %04d\n",info.id_receipt);
		printf("Customer name: %s\n",info.cusname);
		printf("Member: %s\n",info.member);
		printf("Date: %d/%d/%d\n",info.dd[m],info.mm[m],info.yy[m]);
		printf("-----------------------------------------------------------------------------\n");
		printf("No.  Item ID\tItem Name\tItem Type\tQuantity\tTotal Price(RM) \n");
		printf("-----------------------------------------------------------------------------\n");

		fprintf( fptr,"Receipt No: %04d\n",info.id_receipt);   /*writes the informations into file*/
	    fprintf( fptr,"Customer name: ");
		fprintf( fptr,"%s\n",info.cusname);
		fprintf( fptr,"Member: ");
		fprintf( fptr,"%s\n",info.member);
		fprintf( fptr,"Date: %d/%d/%d\n",info.dd[m],info.mm[m],info.yy[m]);
		fprintf( fptr,"\n-----------------------------------------------------------------------------\n");
		fprintf( fptr,"Item ID\tItem Name\tItem Type\tQuantity\tTotal Price(RM) \n");
		fprintf( fptr,"-----------------------------------------------------------------------------\n");

		while(fread(&info,sizeof(info),1,fcptr)){ //read data from file point by fcptr

			printf("%d     %-9s%  -10s\t%-10s\t%4d\t\t%8.2f\n",i,info.id,info.item_name,info.type,info.quan,info.total); //display the data
			grand_total=grand_total+info.total; //calculate total price
			i++;  //increment i by 1
			if((i%16)==0) //when i reach 16
			{
				printf("This receipt can only display 15 items purchase\n");
				break; //exit loop
			}
			fprintf( fptr,"%-9s%-10s\t%-10s\t%4d\t\t%8.2f\n",info.id,info.item_name,info.type,info.quan,info.total); //writes all informations into the file

		}
		printf("-----------------------------------------------------------------------------\n");
		if(strcmp(info.member,"Member")==0) //if string in info.member is "Member"
		{

			printf("\t\t\t\t\t\t\tDiscount: RM %.2f",info.discount2); //display total discount
			grand_total=grand_total-info.discount2;                   //calculate total price minus discount
			printf("\n\t\t\t\t\t\t    Total amount: RM %.2f",grand_total); //display total price after discount
			printf("\n\t\t\t\t\t\t            Cash: RM ");
			scanf("%f",&info.cash);                                     //get input for cash
			info.change=info.cash-grand_total;                          //calculate the change
			printf("\t\t\t\t\t\t\t  Change: RM %.2f\n",info.change);   //display the change


		}
		else //if "Not member"
		{
			printf("\t\t\t\t\t\t\tDiscount: -");
			printf("\n\t\t\t\t\t\t    Total amount: RM %.2f",grand_total); //display total price
			printf("\n\t\t\t\t\t\t            Cash: RM ");
			scanf("%f",&info.cash);                                          //get input for cash
			info.change=info.cash-grand_total;                                //calculate the change
			printf("\t\t\t\t\t\t\t  Change: RM %.2f\n",info.change);          //display the change

		}
         //writes all the informations into file
		fprintf(fptr,"\n-----------------------------------------------------------------------------\n");
		if(strcmp(info.member,"Member")==0)
		{
			//writes all informations into the file
			fprintf(fptr,"\t\t\t\t\t\tDiscount: RM %.2f",info.discount2);
			fprintf(fptr,"\n\t\t\t\t\t    Total amount: RM %.2f\n",grand_total);
			fprintf(fptr,"\t\t\t\t\t          Cash: RM %.2f\n",info.cash);
			fprintf(fptr,"\t\t\t\t\t        Change: RM %.2f\n",info.change);


		}
		else
		{   //writes all informations into the file
			fprintf(fptr,"\t\t\t\t\t\tDiscount: RM-");
			fprintf(fptr,"\n\t\t\t\t\t    Total amount: RM %.2f\n",grand_total);
			fprintf(fptr,"\t\t\t\t\t          Cash: RM %.2f\n",info.cash);
			fprintf(fptr,"\t\t\t\t\t        Change: RM %.2f\n",info.change);

		}
		//writes all informations into the file
		fprintf(fptr,"\t\tTHANK YOU PLEASE COME AGAIN\n");
		fprintf(fptr,"\t\tTHIS IS YOUR OFFICIAL RECEIPT\n");
		fprintf(fptr,"-----------------------------------------------------------------------------\n\n");

        m++;
		fclose(fptr); //close file
		fclose(fcptr);
		getch();		//get input
	    Mainmenu();     //go to Mainmenu
}

//function definition for records
void records()
{
	//variables declarations
	float totalAll=0;
	int i=1;
	static int m=1;

	FILE *fptr; //Records.dat file pointer
	fptr=fopen("Records.dat","rb"); //open file
	system("cls"); //new screen
	interface(); //function call
	printf("\n\t\t\tMuayWorld Muay Thai Shop\n");  //display data on screen
	printf("\t\t\tWeekly Income Summary\n");
	printf("Week: %d/%d/%d\ - %d/%d/%d\n",info.dd[m],info.mm[m],info.yy[m],info.dd[m]+6,info.mm[m],info.yy[m]);
	printf("--------------------------------------------------------------------------------------------------------------\n");
	printf("No\tItem code\tTitle\t\tItem Type\tCustomer Type\t\tReceipt No\tRental fees\n");
	printf("--------------------------------------------------------------------------------------------------------------\n");
	while(fread(&info,sizeof(info),1,fptr)) //reads the data from file
	{
		//print the informations
		printf("%d\t%s\t\t%-10s\t%-10s\t%s/%s\t\t%04d\t\t%.2f\n",i,info.id,info.item_name,info.type,info.cusname,info.member,info.id_receipt,info.memberPrice);
		i++; //increment by 1
		totalAll=totalAll+info.memberPrice; //calculate the weekly sale

	}
	printf("--------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\tWeekly Total Sale(RM)\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t%.2f\n",totalAll);  //display the weekly sale

	system("PAUSE");
	Mainmenu();

}
//function defintion for exit
void exit()
{
	//print the string
	printf("THANK YOU USING THIS PROGRAM\n");
	exit(0);//exit the program

}
//function definition for edit
void edit()
{
	//variables declaration
	int i;
	int choice;
	const char *menu[] = {" Add item"," Edit item"," Delete item","Back to Main Menu"};
	do
	{
	system("cls"); //new screen
	interface();  //function call
	printf("--------------------#Muay Thai Shop#---------------------\n");

	for(i=0;i<4;i++)
	{
		printf("\t\t%d. %s\n",i+1,menu[i]);  //dispaly menu
	}
	printf("\t\tChoice: ");
	scanf("%d",&choice);  //get input for choice

	switch(choice)
	{
		//choice 1
	case 1:
		add();
	    break; //exit switch
		//choice 2
	case 2:
		edit_item();
		break; //exit switch
		//choice 3
	case 3:
		del_item();
		break; //exit switch
        //choice 4
	case 4:
		Mainmenu();
		break; //exit switch
		//wrong input
	default:
		printf("Please enter choice again\n");
		break; //exit switch
	}
	}while(choice !=4);

}
//function definition for add
void add()
{
	//variables declaration
	int pick;
	int m;
	char id[15];
	char c='A';

    char file_item[20];
	const char *menu[] = {" Gloves"," Gloves"," Guards"," Tshirt"," Shorts"," Shorts"," Training Pads"};
	const char *menu2[] = {"Muay Thai Gloves","MMA Gloves","Shin Guard","Combat","Muay Thai","Muay Boran","-"};
	system("cls"); //new screen
	interface();  //function call
	printf("Choose file item to be added:\n");
	printf("Options     List of items\t  Category\n");
	for(m=0;m<7;m++)
	{
		printf("%2d. %20s\t  %s\n",m+1,menu[m],menu2[m]); //display menu
	}
	printf("Choice: ");
	scanf("%d",&pick); //get input
	sprintf(file_item,"%d.dat",pick); //stored string in file_item
	FILE *fptr;                       //file_item file pointer
	FILE *fcptr;                     //file_item file pointer
	fcptr=fopen(file_item,"rb");     //open file
	while(fread(&item,sizeof(item),1,fcptr))  //read data from file
	{
		strcpy(info.type,item.type);  //copy item type
	}
	printf("\n");
	printf("Enter record(Y/N)?");
	getchar();
	while(toupper(getchar())=='Y')  //if 'y',convert it to capital 'Y'
	{
		fptr=fopen(file_item,"ab+");// open file for updating
		sprintf(id,"%04c",c);
		printf("Auto-generated id:%s",id);
		c++;
		strcpy(item.ID,id);
		printf("\nName of item : ");
		scanf("%s",item.name);     //stored in item.name
		printf("Price of item: ");
		scanf("%f",&item.price);   //stored in item.price
		printf("Quantity     : ");
		scanf("%d",&item.quantity); //stored in item.quantity
		printf("\n");
		fseek(fptr,0,SEEK_END);  //reposition file pointer to end of file
		fwrite(&item,sizeof(item),1,fptr); //writes all informations into the file
		printf("Enter another record(Y/N))?");
		getchar();  //get input
		fclose(fptr);  //file close

	}
	fclose(fcptr); //file close

	edit();   //go to edit menu

}
//function defintion for del_item
void del_item()
{
	//variables declaration
	int check;
	int i;
	int options;
	char id[LETTER];
	char file_item[10];
	char file_item2[10];
	const char *menu[] = {" Gloves"," Gloves"," Guards"," Tshirt"," Shorts"," Shorts"," Training Pads"};   //string for menu
	const char *menu2[] = {"Muay Thai Gloves","MMA Gloves","Shin Guard","Combat","Muay Thai","Muay Boran","-"}; //string for menu2

	FILE *fptr,*fptr2; //file_item file pointers
	system("cls");  //new screen
	interface();  //function call interface
	printf("Delete item in inventory\n");
	printf("Choose item in file to delete:\n");
	printf("Options     List of items\t  Category\n");
	for(i=0;i<7;i++)
	{
		printf("%2d. %20s\t  %s\n",i+1,menu[i],menu2[i]); //display menu from array
	}
	printf("Choice: ");
	scanf("%d",&options);  //get input for options
	sprintf(file_item,"%d.dat",options);  //stored string in file_item
	sprintf(file_item2,"%d2.dat",options);  //stored string in file_item2
	printf("ItemID  Item Name     Price  Quantity\n");
	items(options);  //function call items
	printf("enter item ID: ");
	scanf("%s",id);  //get input for id
	check=check_items(id,options);  //check the validity of items
	if(check==0)  //if it exists
	{
		fptr2=fopen(file_item2,"ab"); //file open
		fptr=fopen(file_item,"rb");  //file open
		rewind(fptr);  //reposition the file pointer to beginning

		while(fread(&item,sizeof(item),1,fptr))  //read data stored in file
		{
			if(strcmp(item.ID,id) !=0)  //comparing the id
				fwrite(&item,sizeof(item),1,fptr2); //writes all informations that are not same into the another file

		}
		printf("-----The item succesfully being deleted-----\n");
		fclose(fptr);  //close file
	    fclose(fptr2);  //close file


		remove(file_item);  //remove original file
	    rename(file_item2,file_item);  //rename second file to original file

	}
	if(check==1)  //item not exists
	{
		printf("----The item not exist----\n");
		printf("Please enter again\n");
	}

	getch();  //get input from keyboard
	edit();  //go to edit menu
}

//function definition for check_items
int check_items(char id[LETTER],int options)
{
	//declaration of array
	char file_item[10];
	//declaration of variable
	int check=1;

	FILE *fptr; //file_item file pointer

	sprintf(file_item,"%d.dat",options);  //stored string into file_item
	fptr=fopen(file_item,"rb");  //opening file
	rewind(fptr);   //reposition the file pointer to beginning
	while(fread(&item,sizeof (item),1,fptr))  //read the data from file
	{
		if(strcmp(item.ID,id) ==0)  //comparing id
		{
			check=0;  //if same assign check with 0
			break;   //exit the loop
		}
	}
	fclose(fptr); //close file
	return check;  //return the value of check
}
//function definition for edit_item
void edit_item()
{
	//declaration variables
	int check=0;
	int choice;
	int options;
	float price;
	int quantity;
	int size;
	int i;
	char id[LETTER];
	char y[TAG];
	char file_item[10];
	//declaration for array
	const char *menu[] = {" Gloves"," Gloves"," Guards"," Tshirt"," Shorts"," Shorts"," Training Pads"};  //menu
	const char *menu2[] = {"Muay Thai Gloves","MMA Gloves","Shin Guard","Combat","Muay Thai","Muay Boran","-"};  //menu2

	FILE *fptr;  //file_item file pointer

	system("cls");  //new screen
	interface();    //call function interface
	printf("Edit records\n");
	printf("File to be edited:\n");
	printf("Options     List of items\t  Category\n");
	for(i=0;i<7;i++)
	{
		printf("%2d. %20s\t  %s\n",i+1,menu[i],menu2[i]);  //display menu
	}
	printf("Choice: ");
	scanf("%d",&options);  //get input for options

	sprintf(file_item,"%d.dat",options);  //stored string into variables

	printf("Enter item ID: \n");
START:  //redirect to this current position if item not exist
	scanf("%s",id);  //get iput for id
	printf("\n");
	check=check_items(id,options);    //check the vadility of item
	if(check==0)  //if item exists
	{
		fptr=fopen(file_item,"rb+");  //file open for update
		rewind(fptr);   //reposition the file pointer to beginning
		while(fread(&item,sizeof(item),1,fptr))  //read the data from file
		{
			if(strcmp(item.ID,id)==0)  //compare the id
			{
				printf(" Item ID   : %s\n",item.ID);    //display the item information
				printf(" Item name : %s\n",item.name);
				printf(" Price     : %.2f\n",item.price);
				printf(" Quantity  : %d\n",item.quantity);
				printf("Edit this record(Y/N):");
				if(toupper(getch())=='Y')  //if input is 'Y';'y' will be converted to capital 'Y'
				{
					printf("\n1 - edit Item name\n");  //display menu
					printf("2 - edit price\n");
					printf("3 - edit quantity\n");
					printf(" Enter the choice to be edited:\n");
					scanf("%d",&choice);  //get input for choice

					switch(choice)
					{
						//choice 1
					case 1:
						printf("Enter new Item name:");
						scanf("%s",item.name);   //get input for new item name
						size=sizeof(item);  //assign the sizeof to size
						fseek(fptr,-size,SEEK_CUR);  //seek the correct data record
						fwrite(&item,sizeof(item),1,fptr); //writes the new information over older data in the file
						break;  //exit switch
					case 2:
						printf("Enter new price:");
						scanf("%f",&price);  //get input for new price
						item.price=price;   //assign the price to item.price
						size=sizeof(item);  //assign the sizeof to size
						fseek(fptr,-size,SEEK_CUR);  //seek the correct data record
						fwrite(&item,sizeof(item),1,fptr);//writes the new information over older data in the file
						break; //exit switch
					case 3:
						printf("Enter new quantity:");
						scanf("%d",&quantity);   //get input for new quantty
						item.quantity=quantity;  //assign the quantity to item.quantity
						size=sizeof(item);  //assign the sizeof to size
						fseek(fptr,-size,SEEK_CUR);  //seek the correct data record
						fwrite(&item,sizeof(item),1,fptr); //writes the new information over older data in the file
						break;  //exit switch
					}
					printf("----item has been edited----\n");
					system("PAUSE");
					break; //exit if
				}
			}
		}
	}
	if(check==1) //item not exists
	{
		printf("Item does not exist\n");
		printf("Please enter again\n");
		goto START;  //go to START
	}
	getchar();   //get input from keyboard
	fclose(fptr);  //close file
	edit();  //back to edit menu

}
