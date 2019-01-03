#pragma once

typedef struct student
{
	char name[20];
	unsigned num;
	char sex;
	float math;
	float English;
	float average;
	struct student *next;
}STU;

enum SORT_BY {NUM, MATH, ENGLISH, AVERAGE};

#define FILENAME "stu_list.txt"

STU * Insert_Node(STU * phead, STU * pnew);
void Set_Node(STU * pnode);
int Back_To_Menu();
void Show_Menu();
STU * Create_List(STU * phead);
void Show_List(STU * phead);
STU * Delete_Node(STU * phead, unsigned n);
void Update_Node(STU * phead, unsigned n);
void Sort_Node(STU * phead, enum SORT_BY sort_by);
int Save_List2File(STU * phead, const char * filename);