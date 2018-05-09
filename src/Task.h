#ifndef TASK_H
#define TASK_H
#include <iostream>
using namespace std;

class Task {
public:
	Task();
	friend istream & operator >>(istream & ou, Task & A);
	friend ostream & operator <<(ostream & ou, Task & A);
	friend bool operator >(Task & A, Task & B);
	friend bool operator <=(Task & A, Task & B);
	friend bool operator ==(Task & A, Task & B);
	void setDate();
	string name, description, date;
	int priority, days;
	int day, month, year;

	~Task();
private:
};

#endif // TASK_H
