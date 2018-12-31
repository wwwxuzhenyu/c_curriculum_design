#pragma once

typedef struct student
{
	char name[20];
	unsigned num;
	char sex;
	float math;
	float English;
	struct student *next;
}STU;

enum SORT_BY {NUM, MATH, ENGLISH, AVERAGE};

STU * Insert_Node(STU * phead, STU * pnew);
void Set_Node(STU * pnode);

void Show_Menu();
STU * Create_List(STU * phead);
void Show_List(STU * phead);
STU * Delete_Node(STU * phead, unsigned n);
void Update_Node(STU * phead, unsigned n);
void Sort_Node(STU * phead, enum SORT_BY sort_by);