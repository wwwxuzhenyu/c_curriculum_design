#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


void Show_Menu()
{
	printf("========================================\n");
	printf("学生成绩管理系统\n");
	printf("请输入0~5功能键：\n");

	printf("1：成绩录入\n");
	printf("2：信息查询\n");
	printf("3：信息删除\n");
	printf("4：信息修改\n");
	printf("5：信息保存\n");
	printf("0：退出程序\n");
	printf("输入（0-5）：");
}

STU * Create_List(STU * phead)
{
	STU * pnew;
	//STU * pend;
	phead = NULL;
	do
	{
		printf("\n");
		if ((pnew = (STU *)malloc(sizeof(STU))) == NULL)
		{
			printf("堆区内存已用完！\n");
			exit(1);
		}
		printf("输入新考生的考号（为0则结束建表！）：");
		scanf("%u", &pnew->num);
		if (pnew->num == 0)
			break;

		printf("输入考生的姓名：");
		scanf_s("%s", pnew->name, 20);
		getchar(); //处理回车

		pnew->sex = 'a';
		while (pnew->sex != 'M' && pnew->sex != 'F')
		{
			printf("输入考生的性别(M/F)：");
			scanf("%c", &pnew->sex);
			getchar(); //处理回车
			if (pnew->sex == 'm') pnew->sex = 'M';
			if (pnew->sex == 'f') pnew->sex = 'F';
		}
		

		printf("输入考生的数学成绩：");
		scanf("%f", &pnew->math);
		printf("输入考生的英语成绩：");
		scanf("%f", &pnew->English);

		pnew->next = NULL;

		if (phead == NULL)
		{
			phead = pnew;
			//pend = phead;
		}
		else
		{
			/*pend->next = pnew;
			pend = pnew;*/
			phead = Insert_Node(phead, pnew);
		}

	} while (pnew->num != 0);
	//pend->next = NULL;
	free(pnew);                                 //释放考号为0的节点所分配的空间
	return phead;
}

void Set_Node(STU * pnode)
{
	printf("输入考生的考号：");
	scanf("%u", &pnode->num);

	printf("输入考生的姓名：");
	scanf_s("%s", pnode->name, 20);
	getchar(); //处理回车

	pnode->sex = 'a';
	while (pnode->sex != 'M' && pnode->sex != 'F')
	{
		printf("输入考生的性别(M/F)：");
		scanf("%c", &pnode->sex);
		getchar(); //处理回车
		if (pnode->sex == 'm') pnode->sex = 'M';
		if (pnode->sex == 'f') pnode->sex = 'F';
	}


	printf("输入考生的数学成绩：");
	scanf("%f", &pnode->math);
	printf("输入考生的英语成绩：");
	scanf("%f", &pnode->English);

	pnode->next = NULL;
}

void Show_List(STU * phead)
{
	STU * pcur;
	printf("学号\t姓名\t性别\t数学成绩\t英语成绩\n");
	pcur = phead;
	while (pcur != NULL)
	{
		printf("%u\t%s\t%c\t%3.1f\t\t%3.1f\n", pcur->num, pcur->name, pcur->sex, pcur->math, pcur->English);
		pcur = pcur->next;
	}
	printf("\n");
}

void gradeinput()
{
	printf("成绩录入函数\n");
}

STU * Insert_Node(STU * phead, STU * pnew)
{
	STU * pcur;
	if (phead->num > pnew->num)
	{
		pnew->next = phead;
		phead = pnew;
		return phead;
	}
	for (pcur = phead; pcur->next != NULL; pcur = pcur->next)
	{
		if (pcur->next->num > pnew->num)
		{
			pnew->next = pcur->next;
			pcur->next = pnew;
			return phead;
		}
	}
	pcur->next = pnew;
	pnew->next = NULL;
	return phead;
}

STU * Delete_Node(STU * phead, unsigned n)
{
	STU * pcur, *pdel;
	if (phead == NULL)
	{
		printf("没有可删除的数据鸭 (>_<) ");
		return phead;
	}
	if (phead->num == n)
	{
		pcur = phead;
		phead = phead->next;
		printf("考号为%d的学生“%s”已被您删除\n",pcur->num,pcur->name);
		free(pcur);
		return phead;
	}
	for (pcur = phead; pcur->next != NULL; pcur = pcur->next)
	{
		if (pcur->next->num == n)
		{
			pdel = pcur->next;
			pcur->next = pdel->next;
			printf("考号为%d的学生“%s”已被您删除\n", pdel->num, pdel->name);
			free(pdel);
			return phead;
		}
	}
	printf("操作成功。表单中已经没有学号为%d的学生\n", n);
	return phead;
}

void Update_Node(STU * phead, unsigned n)
{
	STU * pcur, * pupd = NULL;
	if (phead == NULL)
	{
		printf("没有可修改的数据鸭 (>_<) ");
		return phead;
	}

	for (pcur = phead; pcur != NULL; pcur = pcur->next)
	{
		if (pcur->num == n)
		{
			pupd = pcur;
			break;
		}
	}

	if (pupd != NULL)
	{
		char ans;

		printf("输入考生的姓名（%s）是否修改（y/n）？", pupd->name);
		scanf(" %c", &ans); //scanf接收的数据之前就有换行时，没有加空格的scanf 会把上一行的换行符作为字符接收掉
		if (ans == 'y' || ans == 'Y')
		{
			printf("\n输入考生的姓名：");
			scanf_s("%s", pupd->name, 20);
			getchar(); //处理回车
		}

		printf("输入考生的性别（%c）是否修改（y/n）？", pupd->sex);
		scanf(" %c", &ans);
		if (ans == 'y' || ans == 'Y')
		{
			pupd->sex = 'a';
			while (pupd->sex != 'M' && pupd->sex != 'F')
			{
				printf("输入考生的性别(M/F)：");
				scanf(" %c", &pupd->sex);
				if (pupd->sex == 'm') pupd->sex = 'M';
				if (pupd->sex == 'f') pupd->sex = 'F';
			}
		}

		printf("输入考生的数学成绩（%3.1f）是否修改（y/n）？", pupd->math);
		fflush(stdin);
		scanf(" %c", &ans);
		if (ans == 'y' || ans == 'Y')
		{
			printf("输入考生的数学成绩：");
			scanf("%f", &pupd->math);
		}

		printf("输入考生的英语成绩（%3.1f）是否修改（y/n）？", pupd->English);
		scanf(" %c", &ans);
		if (ans == 'y' || ans == 'Y')
		{
			printf("输入考生的英语成绩：");
			scanf("%f", &pupd->English);
		}
		printf("操作成功。考号为%d的学生信息更新成功\n", n);
	}
	else
	{
		printf("表单无考号为%d的学生\n", n);
	}
}

void Sort_Node(STU * phead, enum SORT_BY sort_by)
{
	float t;

	//冒泡排序
	for (STU* temp = phead; temp->next != NULL; temp = temp->next) 
	{
		for (STU* p = phead; p->next != NULL; p = p->next) 
		{
			switch (sort_by)
			{
			case NUM:
				if (p->num > p->next->num)
				{
					t = p->num;
					p->num = p->next->num;
					p->next->num = t;
				}
				break;
			case MATH:
				if (p->math > p->next->math)
				{
					t = p->math;
					p->math = p->next->math;
					p->next->math = t;
				}
				break;
			case ENGLISH:
				if (p->English > p->next->English)
				{
					t = p->English;
					p->English = p->next->English;
					p->next->English = t;
				}
				break;
			case AVERAGE:
				printf("敬请期待\n");
				break;
			default:
				break;
			}
		}
	}

}

int main()
{
	STU * head = NULL;
	int menu_input,n;
	STU * pn;

	head=Create_List(head);

	Show_Menu();

	while (1)
	{

		scanf("%d", &menu_input);

		switch (menu_input)
		{
		/*
		printf("4：信息修改\n");
		printf("5：信息保存\n");
		printf("0：退出程序\n");
		*/
		case 0:
			exit(0);
		case 1: //成绩录入
			if ((pn = (STU *)malloc(sizeof(STU))) == NULL)
			{
				printf("堆区内存已用完！\n");
				exit(1);
			}
			Set_Node(pn);
			head = Insert_Node(head, pn);
			Show_List(head);
			break;
		case 2: //信息查询
			Show_List(head);
			printf("按数学排序\n");
			getchar();
			Sort_Node(head, MATH);
			Show_List(head);
			break;
		case 3: //信息删除
			printf("请输入您要删除的学生的学号：");
			scanf("%d", &n);
			head=Delete_Node(head, n);
			break;
		case 4:
			printf("请输入要修改学生的学号：");
			scanf("%d", &n);
			Update_Node(head, n);
			break;
		default:
			printf("请输入正确的值(0-5)\n\n");
			break;
		}
		
		getchar(); //处理回车
		Show_Menu();
		
	}
	
	return 0;
}