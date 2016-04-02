/*
Q4: Two dates are given in a 8 node single linked list form,where each node
has one digit only, dates 01-31, months 01-12, year 0000-9999.

Find the number of days in between those two dates .[Exclusive]

Ex : Date1:  0->1->0->1->2->0->0->4 .
     Date2 : 0->5->0->1->2->0->0->4 should return 3 .
As there are 3 days between Jan1st 2004 and Jan 5th 2004.

Ex 2 : Date1 : 3->1->1->2->2->0->1->2.
       Date2 : 0->2->0->1->2->0->1->3 should return 1 .
(There is only one day between 31st Dec 2012 and 2nd  Jan 2013 .)

Note : Consecutive Days and Same Days should return 0;
->Return -1 for NULL Inputs .
->Between Days have to be calculated by not including start and end date .
->The SLL will have 8 Nodes in all cases . Month 9 will be represented as 09.

Difficulty : Hard 
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct node{
	int data;
	struct node *next;
};
int isLeap(int);
int abs(int, int);
int isSame(struct node*, struct node*);
int isConsecutive(struct node*, struct node*);
int between_days(struct node *date1head, struct node *date2head){
	if (date1head == NULL || date2head == NULL) {
		return -1;
	}
	if (isSame(date1head, date2head) || isConsecutive(date1head, date2head)) {
		return 0;
	}
	struct node *head1 = date1head;
	struct node *head2 = date2head;
	int day1 = (date1head->data * 10) + date1head->next->data;
	int day2 = (date2head->data * 10) + date2head->next->data;
	date1head = date1head->next->next;
	date2head = date2head->next->next;
	int month1 = (date1head->data * 10) + date1head->next->data;
	int month2 = (date2head->data * 10) + date2head->next->data;
	date1head = date1head->next->next;
	date2head = date2head->next->next;
	int year1 = (date1head->data * 1000) + (date1head->next->data * 100) + (date1head->next->next->data * 10) + date1head->next->next->next->data;
	int daysInMonth[12];
	int year2 = (date2head->data * 1000) + (date2head->next->data * 100) + (date2head->next->next->data * 10) + date2head->next->next->next->data;
	if (isLeap(year2)) {
		int days[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		for (int i = 0; i < 12; i++) {
			daysInMonth[i] = days[i];
		}
	}
	else {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		for (int i = 0; i < 12; i++) {
			daysInMonth[i] = days[i];
		}
	}
	if (year2 == year1) {
		if (month2 > month1) {
			int result = daysInMonth[month1 - 1];
			result += (abs(day1, day2));
		}
		else if (month1 == month2) {
			return (day2 - day1) - 1;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}
int abs(int num1, int num2) {
	if (num1 > num2) {
		return num1 - num2;
	}
	return num2 - num1;
}
int isLeap(int year) {
	if (year % 400 == 0) {
		return 1;
	}
	else if (year % 100 == 0) {
		return 0;
	}
	else if (year % 4 == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
int isConsecutive(struct node *date1head, struct node *date2head) {
	int date1, date2;
	date1 = (date1head->data * 10) + date1head->next->data;
	date2 = (date1head->data * 10) + date1head->next->data;
	if (date1 - date2 == 1 || date2 - date1 == 1) {
		return 1;
	}
	return 0;
}
int isSame(struct node *date1head, struct node *date2head) {
	while (date1head != NULL) {
		if (date1head->data != date2head->data)
			return 0;
		date1head = date1head->next;
		date2head = date2head->next;
	}
	return 1;
}