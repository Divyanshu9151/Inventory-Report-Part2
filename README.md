			                   Inventory Organizer Program in C++ - Part 2
														
This program is a C++ program that reads a series of data records from a file and stores each record in a linked list 
(in ascending order by items number). After creating the linked list the program should traverse the list and print the report to a file.

After the program reads to a file, it now needs to input a list of items numbers from a file named (purge_items.dat).
The program will locate the items numbers on the file and delete the items record it the items age is more than 5 years old 
and the item sold is less than 10% of the items_count.

If the items number is NOT in the list, the program will ignore it and go on to the next items number in the purge file.
After the program purge's the data, it will generate a Purge Report and print to the Purge Report file, with the Total
Revenue Lost.

Total Revenue Lost = [items_cost * (items_count - items_sold)]

After purging the items that match the purge criteria, the program will generate a new inventory report.

This new inventory report will not include the purge data. But, it will include the percent decrease in revenue.

Percent Decrease in Revenue = ((Old Revenue - New Revenue)/Old Revenue) * 100 
