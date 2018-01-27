//------------------------------------------------------------------
// File name:   InventoryReport.cpp
// Assign ID:   Project 1A 
// Due Date:    1/19/18 at 12:30 pm
//
// Purpose:     Design, Implement, and Test a C++ program that reads a series of data records from a file
//              and stores each record in a linked list (in ascending order by items number). After creating 
//              the linked list the program should traverse the list and print the report to a file.
//              
// Author:      Tishauna Wilson
//------------------------------------------------------------------

#include "DataRecord.cpp"

int main()
{
	//Declare Variables
	AccessData Data; 

   //-| ----------------------------------------------------------------------
   //-| Print the copyright notice declaring authorship.
   //-| ----------------------------------------------------------------------
   cout << endl << "(c) 2018, Tishauna Wilson" << endl << endl; 


   //-| ----------------------------------------------------------------------
   //-| 1. Call The Funtion That Reads Data From File
   //-| ----------------------------------------------------------------------
   Data.Read();

   //-| ----------------------------------------------------------------------
   //-| 2. Call The Function That Prints Inventory Report
   //-| ----------------------------------------------------------------------
   Data.Print();

   //-| ----------------------------------------------------------------------
   //-| 3.Call The Function That Finds The Item In The List From The Purge File 
   //-| ----------------------------------------------------------------------
   Data.FindItem();

   //-| ----------------------------------------------------------------------
   //-| 4.Call The Function That Prints The Purge File
   //-| ----------------------------------------------------------------------
   Data.PrintPurge();
	   
   //-| ----------------------------------------------------------------------
   //-| 5.Call The Function That Prints The New Inventory Report
   //-| ----------------------------------------------------------------------
   Data.PrintNewReport();
	   
   //-| ----------------------------------------------------------------------
   //-| Print the copyright notice declaring authorship again.
   //-| ----------------------------------------------------------------------
   cout << endl << "(c) 2018, Tishauna Wilson" << endl << endl; 

   return 0;
}//main
