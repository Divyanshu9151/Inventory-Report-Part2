#ifndef DATARECORD_H
#define DATARECORD_H
#include <vector>

class AccessData
{
	public:
	    //Open File & Read In Data
	    void Read();
		
	    //Insert The Data Into The Linked List In Order
		void Insert(unsigned int, string, int, int, int, float, int, int);
		
		//Insert Purge Data Into Purge Linked List
		void PurgeInsert(unsigned int, int, int, int, float, int, int);
		
		//Print The Data In The Linked List To A File
		void Print();
		
		//Convert Today's Date & The Item Purchase Date Into Age Years
		int ConvertAge(int, int, int);
		
		//Convert Date Into Its Abbreviation
		string Date(int);
		
		//Search Vector For Duplicate Item Numbers
		int LinearSearch(vector<int>, int);
		
		//Get Today's Date
		void GetDate(int &, int &, int &);
		
		//Check Dates In File For Being Out Of Bounds
		bool CheckDate(int Month, int Day, int Year);
		
		//Find Item_Number From purge_items.dat File In List.
		// If Item Matches Criteria, Send To PrintPurge(), Then Delete The Item
		void FindItem();
		
		//Print Purged Items To A Inventory Purge Report
		void PrintPurge();
		
		//Print The New Report
		void PrintNewReport();
		
		//Destructor for Linked List
		~AccessData()
		{
			Node *ptr;
			Node1 *ptr1;
            for (ptr = Head; Head; ptr = Head)
            {
                Head = Head->next;
                delete ptr;
            }//for
			for (ptr1 = H; H; ptr1 = H)
            {
                H = H->next1;
                delete ptr;
            }//for
			
		}//Destructor
    private:
		struct Node1
		{
			unsigned int Item_Number1; //Item Number
			int Item_Purchase_DateM1;  //Purchase Date (MMDDYY) - Month
			int Item_Purchase_DateD1;  //Purchase Date (MMDDYY) - Day
			int Item_Purchase_DateY1;  //Purchase Date (MMDDYY) - Year
			float Item_Cost1;          //Item Cost
			int Item_Count1;           //Item Count
			int Item_Sold1;            //Item Sold
			Node1 *next1;               //Node Pointer
			Node1(){}                  //First Constructor
			Node1(unsigned int Item_Number2, int Item_Purchase_DateM2,
			     int Item_Purchase_DateD2, int Item_Purchase_DateY2, float Item_Cost2, 
			     int Item_Count2, int Item_Sold2, Node1 *next2 = NULL)
			{
				Item_Number1 = Item_Number2;
				Item_Purchase_DateM1 = Item_Purchase_DateM2;
				Item_Purchase_DateD1 = Item_Purchase_DateD2;
				Item_Purchase_DateY1 = Item_Purchase_DateY2;
				Item_Cost1 = Item_Cost2;
				Item_Count1 = Item_Count2;
				Item_Sold1 = Item_Sold2;
				next1 = next2;
			}//Second Constructor
		};//struct Node1
		struct Node
		{
			unsigned int Item_Number; //Item Number
			string Item_Category;    //Item Category
			int Item_Purchase_DateM;  //Purchase Date (MMDDYY) - Month
			int Item_Purchase_DateD;  //Purchase Date (MMDDYY) - Day
			int Item_Purchase_DateY;  //Purchase Date (MMDDYY) - Year
			float Item_Cost;          //Item Cost
			int Item_Count;           //Item Count
			int Item_Sold;            //Item Sold
			Node *next;               //Node Pointer
			Node(){}                  //First Constructor
			Node(unsigned int Item_Number1, string Item_Category1, int Item_Purchase_DateM1,
			     int Item_Purchase_DateD1, int Item_Purchase_DateY1, float Item_Cost1, 
			     int Item_Count1, int Item_Sold1, Node *next1 = NULL)
			{
				Item_Number = Item_Number1;
				Item_Category = Item_Category1;
				Item_Purchase_DateM = Item_Purchase_DateM1;
				Item_Purchase_DateD = Item_Purchase_DateD1;
				Item_Purchase_DateY = Item_Purchase_DateY1;
				Item_Cost = Item_Cost1;
				Item_Count = Item_Count1;
				Item_Sold = Item_Sold1;
				next = next1;
			}//Second Constructor
		};//struct Node
		Node *Head = NULL;            //Node Head Pointer
		Node1 *H = NULL;              //Node1 Head Pointer
		Node1 *tail = NULL;           //Node1 Tail Pointer
		float TotalRevenue;           //TotalRevenue Counter
		float RevenueLost;            //RevenueLost Counter
		float NewRevenue;             //NewRevenue Counter
		int Counter; //Counter To Ensure Title Is Only Printed Once
};
#endif