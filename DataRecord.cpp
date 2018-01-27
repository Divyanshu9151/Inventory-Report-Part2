#include <iostream>
using namespace std;
#include "DataRecord.h"
#include <fstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

void AccessData:: Read()
{
   //Declare variables
	ifstream inF;                   
	unsigned int Item_Number1;
    string Item_Category1;
	int Item_Purchase_DateM1, Item_Purchase_DateD1, Item_Purchase_DateY1, Item_Count1, Item_Sold1;
	float Item_Cost1;
	vector <int> InputNumbers;
	TotalRevenue = 0.0; 
	
	//Open File
	inF.open("Data.txt");
	
	//Test File For Error
	if(inF.fail())
	{
		   cout << endl << "FATAL ERROR: UNABLE TO OPEN FILE \"Data.txt\". TERMINATING..."
                << endl << endl;
           exit (1);
	}
	else
	{
		while(inF >> Item_Number1 >> Item_Category1 >> Item_Purchase_DateM1 
			      >> Item_Purchase_DateD1 >> Item_Purchase_DateY1 >> Item_Cost1 
			      >> Item_Count1 >> Item_Sold1)
		{
			//---------------------------------------
			//If Error Are Encountered, Skip The Line
			//---------------------------------------
			//Check If Date Is Beyond Today's Date
			if(CheckDate(Item_Purchase_DateM1, Item_Purchase_DateD1, Item_Purchase_DateY1) == false)
				continue;
			
			//Check Month For Out Of Range
			if(Item_Purchase_DateM1 < 1 || Item_Purchase_DateM1 > 12 || Item_Purchase_DateM1 == 0)
				continue;
			
			//Check Day For Out Of Range
			if(Item_Purchase_DateD1 < 1 || Item_Purchase_DateD1 > 31 || Item_Purchase_DateD1 == 0)
				continue;
			
		    //Check if Year Is Negative
		    if(Item_Purchase_DateY1 < 0 || Item_Purchase_DateY1 == 0)
				continue;
			
			//Check Item Cost For Negative Numbers
			if(Item_Cost1 < 0.0)
				continue;
			
			//Check Item Count For Negative Numbers
			if(Item_Count1 < 0)
				continue;
			
			//Check Item Sold For Negative Numbers
			if(Item_Sold1 < 0)
				continue;
						
			//Input Numbers Into Vector To Make Sure No Duplicates Get Inserted Into The List
			InputNumbers.push_back(Item_Number1);
				
			//Check To Make Sure There Is No Duplicate Item_Number
			if(LinearSearch(InputNumbers, Item_Number1) > 1)
				continue;
			
			else
			{
				//If The Data Passes The Test, Send It To The Linked List
				Insert(Item_Number1, Item_Category1, Item_Purchase_DateM1, 
					   Item_Purchase_DateD1, Item_Purchase_DateY1, Item_Cost1,
			           Item_Count1, Item_Sold1);
				TotalRevenue += (Item_Sold1 * Item_Cost1);
			}//else
		}//while
	}//else
	            //Close The Input File
			    inF.close();
}//Read
	

void AccessData:: Insert(unsigned int Item_Number2, string Item_Category2, int Item_Purchase_DateM2, 
						  int Item_Purchase_DateD2, int Item_Purchase_DateY2, float Item_Cost2,
			              int Item_Count2, int Item_Sold2) 
{
	Node *temp = NULL;
	temp = new Node(Item_Number2, Item_Category2, Item_Purchase_DateM2, Item_Purchase_DateD2, Item_Purchase_DateY2, 
					Item_Cost2, Item_Count2, Item_Sold2, temp);
	
	/*Check To See If Head Is Null || Check To See If Head's Value Is Greater Than Current Value, 
	If So, Insert Value At Head*/
	if(Head == NULL || Head->Item_Number > Item_Number2)
	{
		temp->next = Head;
		Head = temp;
	}//if
	
	//Check To See If The Next Item In The List Is Greater Than The Current Value, 
	//If So, Insert Value Before Greater Number
	else if(Head->next != NULL && Head->next->Item_Number >= Item_Number2)
	{
		Node *tempNext = new Node;
		tempNext = Head->next;
		temp->next = tempNext;
		Head->next = temp;
	}//elseif
	
	//Check To See If The Next Item In The List Is Less Than The Current Value, 
	//If So, Insert Value After Lesser Number
	else
	{
		Node *current = new Node;
		current = Head;
		while(current ->next != NULL && current->next->Item_Number <= Item_Number2)
		{
			current = current -> next;
		}//while
		temp->next = current->next;
		current->next = temp;
	}//else 
}//Insert

void AccessData:: Print()
{
	//CHANGE SETW: INCLUDE LEFT & RIGHT
	ofstream OutF;  
	int Month, Day, Year;
	
	//Open File
	OutF.open("BeginningFile.txt");
	
	//Test File For Error
	if(OutF.fail())
	{
		   cout << endl << "FATAL ERROR: UNABLE TO OPEN FILE \"BeginningFile.txt\". TERMINATING..."
                << endl << endl;
           exit (1);
	}
	else
	{
		//Print Out The Contents For The Inventory Report
		OutF << fixed << setw(70) << "Inventory Report" << endl;
		OutF << fixed << setw(100) << "Date: ";
		GetDate(Month, Day, Year);
		OutF << Date(Month) << Day << ", " << Year << endl;
		OutF << endl << endl << endl << endl;
		OutF << fixed << setw(0) << "Item" << setw(24) << "Item Purchase" << setw(14) << "Item"
			 << setw (18) << "Item" << setw(18) << "Item" << setw(15) << "Item" << endl;
		OutF << fixed << setw(0) << "Number" << setw(17) << "Date" << setw(19) << "Cost"
			 << setw (18) << "Sold" << setw(17) << "Age" << setw(18) << "Revenue" << endl;
	
		//Print Out The Contents In The Linked List As A Inventory Report
		Node *temp = new Node;
		temp = Head;
		while(temp != NULL)
		{
			OutF << setfill('0') << setw(4) << temp->Item_Number;
			OutF << setfill(' ') << setw(16) << Date(temp->Item_Purchase_DateM) << temp->Item_Purchase_DateD 
				 << setw(0) << ",\t" << temp->Item_Purchase_DateY;
			OutF << setw(10) << "$ " << setprecision(2) << temp->Item_Cost;
			OutF << setw(16) << temp->Item_Sold; 
			OutF << setw(17) << ConvertAge(temp->Item_Purchase_DateM, temp->Item_Purchase_DateD, temp->Item_Purchase_DateY);
			OutF << setw(14) << "$ " << setprecision(2) << (temp->Item_Cost * temp->Item_Sold) << endl;
			temp = temp->next;
		}//while
	
		//Print Out Total Revenue
		OutF << endl << setw(65) << "Total Revenue" << '\t' << setw(19) << "$ " << setprecision(2) << TotalRevenue;
	 }//else
	OutF.close();
}//Print
int AccessData:: ConvertAge(int Month1, int Day1, int Year1)
{
	int Date1[] = {Month1, Day1, Year1};
	
	//Get current time and date
	time_t t = time(0);
	tm* ltm = localtime(&t);
	int Year2 = 1900 + ltm->tm_year;
	int Month2 = 1 + ltm->tm_mon;
	int Day2 = ltm->tm_mday;
	int Date2[] = {Month2, Day2, Year2};
	
	//Subtract Date From Given Date
    tm a = {0,0,0,Day1,Month1,Year1};
	tm b = {0,0,0,Day2,Month2,Year2};
	time_t x = mktime(&a);
	time_t y = mktime(&b);
	
	if(x != (time_t)(-1) && y != (time_t)(-1))
	{
       double difference = difftime(y,x)/(60*60*24);
		    int rounding = (int)round(difference);
			int year = rounding/365;
			int days = rounding%365;
			int months = days/30;
		
			if(year >= 1 && months >= 6 && days >= 183)
				return (year+1);
		    else if(year >= 1 && months <= 5 && days <= 182)
				return (year);
		    else
				return 0;
	}//if
}//ConvertAge
	
//Function to convert the Month number into its abbreviation 
string AccessData:: Date(int Month)
{
   const string DateAbbr[12] = {"Jan. ", "Feb. ", "Mar. ", "Apr. ", 
		                  "May ", "Jun. ", "Jul. ", "Aug. ", 
						  "Sep. ", "Oct. ", "Nov. ", "Dec. "};
   switch(Month)
   {
	   case 1: return DateAbbr[0];
		       break;
	   case 2: return DateAbbr[1];
		       break;
	   case 3: return DateAbbr[2];
		       break;
	   case 4: return DateAbbr[3];
			   break;
	   case 5: return DateAbbr[4];
		       break;
	   case 6: return DateAbbr[5];
			   break;
	   case 7: return DateAbbr[6];
			   break;
	   case 8: return DateAbbr[7];
			   break;
	   case 9: return DateAbbr[8];
		       break;
	   case 10: return DateAbbr[9];
			   break;
	   case 11: return DateAbbr[10];
				break;
	   case 12: return DateAbbr[11];
				break;
	   default: return ("Wrong Month Inserted....");
		        break;
   }//Switch
}//Date

//Search Vector For Duplicate Item Numbers
int AccessData:: LinearSearch(vector<int> ItemHolder, int ItemNumber)
{
	int ItemCounter = 0;
	for(int i = 0; i < ItemHolder.size(); i++)
	{
		if(ItemHolder.at(i) == ItemNumber)
			ItemCounter++;
	}//for
	
	return ItemCounter;
}//LinearSearch

void AccessData:: GetDate(int &Mon, int &Day, int &Year)
{
	//Get Today's Date
	time_t t = time(0);
	tm* ltm = localtime(&t);
	Mon = (ltm->tm_mon + 1);
	Day = ltm->tm_mday;
	Year = (ltm->tm_year + 1900);
}//GetDate

bool AccessData:: CheckDate(int Month, int Day, int Year)
{
	time_t t = time(0);
	tm* ltm = localtime(&t);
	//Return False If Today's Year Is Less Than or Equal To File's Year
	if((ltm->tm_year + 1900) < Year)
		return false;
	//Return False If Today's Month Is Less Than or Equal To File's Month, Today's Day Is Less Than File's Day, and 
	//Today's Year Is Less Than or Equal To File's Year (e.g - Today: 1/23/2018 ----> File's Date: 1/24/2018)
	else if((ltm->tm_mon + 1) <= Month && (ltm->tm_mday) < Day && (ltm->tm_year + 1900) <= Year)
		return false;
	//Return False If Today's Month Is Less Than File's Month, Today's Day Is Less Than File's Day, and 
	//Today's Year Is Less Than or Equal To File's Year (e.g - Today: 1/23/2018 ----> File's Date: 2/27/2018)
	else if((ltm->tm_mon + 1) < Month && (ltm->tm_mday) < Day && (ltm->tm_year + 1900) <= Year)
		return false;
	//Return False If Today's Month Is Less Than File's Month, Today's Day Is Less Than or Equal To File's Day, and 
	//Today's Year Is Less Than or Equal To File's Year (e.g - Today: 1/23/2018 ----> File's Date: 2/23/2018)
	else if((ltm->tm_mon + 1) < Month && (ltm->tm_mday) <= Day && (ltm->tm_year + 1900) <= Year)
		return false;
	else 
		return true;
}//CheckDate

void AccessData:: FindItem()
{
	//Declare Variables
	ifstream inF;
	int ItemNum = 0;
	const int age = 5;
	float itemCountPer;    //10% Of Item Counter
	const float itemSoldMul = 0.1;  //Find 10% Of Item Count
	const int Hundred = 100;
	
	//Open File
	inF.open("purge_items.dat");
	
	//Test File For Error
	if(inF.fail())
	{
		   cout << endl << "FATAL ERROR: UNABLE TO OPEN FILE \"purge_items.dat\". TERMINATING..."
                << endl << endl;
           exit (1);
	}//if
	    //Read in Purge Item Number
		while(inF >> ItemNum)
		{
			Node *temp = new Node;
			Node *prev = new Node;
			temp = Head; 

			//Traverese Through The List
			while(temp != NULL)
			{
				
				//Determine If # In Purge File Matches Data In List
				if(temp->Item_Number == ItemNum)
				{
					//Prevent From Dividing By Zero
					if(temp->Item_Sold <= temp->Item_Count)
					{
						//Determine 10% of The Item Count
						itemCountPer = (temp->Item_Count*itemSoldMul);
					}//if
					else
					{
						cout << "For Item Number " << temp->Item_Number << " Data is Incorrect" << endl;
					}//else
					//Check To See If Item Number Data Matches The Criteria
					if(ConvertAge(temp->Item_Purchase_DateM, temp->Item_Purchase_DateD, temp->Item_Purchase_DateY) > age 
					   && temp->Item_Sold < itemCountPer)
					{
						//Send Purge Data To PurgeInsert
						PurgeInsert(temp->Item_Number, temp->Item_Purchase_DateM, temp->Item_Purchase_DateD, 
								    temp-> Item_Purchase_DateY, temp->Item_Cost, temp->Item_Count, temp->Item_Sold);
							
						    //If temp is not NULL, Delete the item 
							if(temp != NULL) 
							{   
								if(Head->Item_Number == ItemNum)
								{
									Node *tptr= new Node;
									tptr = Head;
									Head = Head->next;
									delete tptr;
								}//if
								else
								{
									Node * delPtr = temp;
									prev->next = delPtr->next;
									delete delPtr;
								}
							}//if
					}//Outer-if
				}//Outer-if
					prev = temp;
					temp = temp ->next;
		  }//Inner-while
	 }//Outer-while
}//FindItem

void AccessData:: PurgeInsert(unsigned int Item_Number4, int Item_Purchase_DateM4, 
						  int Item_Purchase_DateD4, int Item_Purchase_DateY4, float Item_Cost4,
			              int Item_Count4, int Item_Sold4)
{
    Node1 *temp = new Node1(Item_Number4, Item_Purchase_DateM4, Item_Purchase_DateD4, Item_Purchase_DateY4, 
					Item_Cost4, Item_Count4, Item_Sold4, NULL);
	  //If H == NULL, insert item into the Head
      if(H == NULL)
      {
        H = temp;
        tail = temp;
        temp = NULL;
      }
	  //Else, Insert The Item Into The Tail
      else
      {	
        tail->next1 = temp;
        tail = temp;
      }
}//PurgeInsert

void AccessData:: PrintPurge()
{
    //Declare Variables	
	ofstream OutF;  
	Counter = 0;
	RevenueLost = 0.0; //Calculate Revenue Lost
	const float itemSoldMul = 0.1; //Assist With Finding Percent Of Item Sold from Item Count
	int Month, Day, Year; //Retrieve Month, Day, and Year Back 
	const int Hundred = 100;
	int Percent = 0;
	Node1 *temp = new Node1;
	temp = H;
	//Open File
	OutF.open("PurgeFile.txt");

		//Test File For Error
		if(OutF.fail())
		{
		   cout << endl << "FATAL ERROR: UNABLE TO OPEN FILE \"PurgeFile.txt\". TERMINATING..."
                << endl << endl;
           exit (1);
		}//if
	  while(temp != NULL){
		if(Counter < 1)
		{
			OutF << fixed << setw(70) << "Inventory Purge Report" << endl;
			OutF << fixed << setw(90) << "Date: ";
			GetDate(Month, Day, Year);
			OutF << Date(Month) << Day << ", " << Year << endl;
			OutF << endl << endl << endl << endl;
			OutF << fixed << setw(0) << "Item" << setw(24) << "Item Purchase" << setw(13) << "Item"
			     << setw (17) << "%" << setw(19) << "Item" << setw(14) << "Item" << setw(13) 
				 << "Item" << endl;
		    OutF << fixed << setw(0) << "Number" << setw(17) << "Date" << setw(19) << "Count"
			     << setw (18) << "Sold" << setw(17) << "Sold" << setw(13) << "Age" << setw(19) 
				 << "Revenue_Lost" << endl;
			Percent = (temp->Item_Sold1*Hundred)/temp->Item_Count1;
			OutF << setfill('0') << setw(4) << temp->Item_Number1;
			OutF << setfill(' ') << setw(16) << Date(temp->Item_Purchase_DateM1) << temp->Item_Purchase_DateD1 
				 << setw(0) << ",\t" << temp->Item_Purchase_DateY1;
			OutF << setw(13) << temp->Item_Count1;
			OutF << setw(17) << Percent << "%";
			OutF << setw(16) << temp->Item_Sold1; 
			OutF << setw(15) << ConvertAge(temp->Item_Purchase_DateM1, temp->Item_Purchase_DateD1, temp->Item_Purchase_DateY1);
			OutF << setw(9) << "$ " << setprecision(2) << temp->Item_Cost1 * (temp->Item_Count1 - temp->Item_Sold1) << endl;
			RevenueLost += temp->Item_Cost1 * (temp->Item_Count1 - temp->Item_Sold1); 
			Counter++;
		}//if

	else
	{ 
			Percent = (temp->Item_Sold1*Hundred)/temp->Item_Count1;
			OutF << setfill('0') << setw(4) << temp->Item_Number1;
			OutF << setfill(' ') << setw(16) << Date(temp->Item_Purchase_DateM1) << temp->Item_Purchase_DateD1 
				 << setw(0) << ",\t" << temp->Item_Purchase_DateY1;
			OutF << setw(13) << temp->Item_Count1;
			OutF << setw(17) << Percent << "%";
			OutF << setw(16) << temp->Item_Sold1; 
			OutF << setw(15) << ConvertAge(temp->Item_Purchase_DateM1, temp->Item_Purchase_DateD1, temp->Item_Purchase_DateY1);
			OutF << setw(9) << "$ " << setprecision(2) << temp->Item_Cost1 * (temp->Item_Count1 - temp->Item_Sold1) << endl;
			RevenueLost += temp->Item_Cost1 * (temp->Item_Count1 - temp->Item_Sold1); 
			Counter++;
	}//else
		  temp = temp->next1;
	  }//while
	OutF << endl << setw(79) << "Total Revenue" << '\t' << setw(19) << "$ " << setprecision(2) << RevenueLost;
	OutF.close();
}//PrintPurge

void AccessData:: PrintNewReport()
{
	//CHANGE SETW: INCLUDE LEFT & RIGHT
	ofstream OutF;  
	int Month, Day, Year;
	NewRevenue = 0.0;
	
	//Open File
	OutF.open("EndingFile.txt");
	
	//Test File For Error
	if(OutF.fail())
	{
		   cout << endl << "FATAL ERROR: UNABLE TO OPEN FILE \"EndingFile.txt\". TERMINATING..."
                << endl << endl;
           exit (1);
	}
	else
	{
		//Print Out The Contents For The Inventory Report
		OutF << fixed << setw(70) << "Inventory Report" << endl;
		OutF << fixed << setw(68) << "{After Purge}";
		OutF << fixed << setw(30) << "Date: ";
		GetDate(Month, Day, Year);
		OutF << Date(Month) << Day << ", " << Year << endl;
		OutF << endl << endl << endl << endl;
		OutF << fixed << setw(0) << "Item" << setw(24) << "Item Purchase" << setw(14) << "Item"
			 << setw (18) << "Item" << setw(18) << "Item" << setw(15) << "Item" << endl;
		OutF << fixed << setw(0) << "Number" << setw(17) << "Date" << setw(19) << "Cost"
			 << setw (18) << "Sold" << setw(17) << "Age" << setw(18) << "Revenue" << endl;
	
		//Print Out The Contents In The Linked List As A Inventory Report
		Node *temp = new Node;
		temp = Head;
		while(temp != NULL)
		{
			OutF << setfill('0') << setw(4) << temp->Item_Number;
			OutF << setfill(' ') << setw(16) << Date(temp->Item_Purchase_DateM) << temp->Item_Purchase_DateD 
				 << setw(0) << ",\t" << temp->Item_Purchase_DateY;
			OutF << setw(10) << "$ " << setprecision(2) << temp->Item_Cost;
			OutF << setw(16) << temp->Item_Sold; 
			OutF << setw(17) << ConvertAge(temp->Item_Purchase_DateM, temp->Item_Purchase_DateD, temp->Item_Purchase_DateY);
			OutF << setw(14) << "$ " << setprecision(2) << (temp->Item_Cost * temp->Item_Sold) << endl;
			NewRevenue += (temp->Item_Sold * temp->Item_Cost);
			temp = temp->next;
		}//while
	
		//Print Out Total Revenue
		OutF << endl << setw(65) << "Total Revenue" << '\t' << setw(19) << "$ " << setprecision(2) << NewRevenue;
		OutF << endl << left << setprecision(1) << "The percent decrease in revenue is " << ((TotalRevenue - NewRevenue)/TotalRevenue)*100 << "%";
	 }//else
	OutF.close();
}