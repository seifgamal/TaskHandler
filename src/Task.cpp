#include "Task.h"
#include <bits/stdc++.h>
Task::Task() {
	name = description = date = "";
	priority = days = 0;
	year = month = day = 0; // initialize
}
istream& operator >>(istream & ou, Task & A) {
	cout << "Enter the task name : ";
	cin.ignore();
	getline(ou, A.name);
	cout << "Enter the task description : ";
	getline(ou, A.description);
	cout << "Enter the task priority : ";
	ou >> A.priority;
	cout << "Enter the task date on format DD/MM/YYYY: ";
	ou >> A.date;
	cout << "Enter the number of days : ";
	ou >> A.days;
	return ou;
}
ostream & operator <<(ostream & ou, Task & A) {
	cout << "Task's name : ";
	ou << A.name << endl;
	cout << "Task's description : ";
	ou << A.description << endl;
	cout << "Task's priority : ";
	ou << A.priority << endl;
	cout << "Task's date : ";
	ou << A.date << endl;
	cout << "Number of days : ";
	ou << A.days << endl;
	return ou;
}
void Task::setDate() /// to make Date format from DD/MM/YYYY as a string to int Day , int month , int year
{
	day = (date[0] - 48) * 10 + (date[1] - 48);
	month = (date[3] - 48) * 10 + (date[4] - 48);
	year = (date[6] - 48) * 1000 + (date[7] - 48) * 100 + (date[8] - 48) * 10
			+ (date[9] - 48);
}
bool operator >(Task & A, Task & B) {
	return (A.name > B.name);
}
bool operator <=(Task & A, Task & B) /// return true if date of A < date of B
		{
	return (A.name <= B.name);
}
bool operator ==(Task & A, Task & B) /// return true if date of A < date of B
		{
	return (A.name == B.name);
}

Task::~Task() {
}
