#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


void Show_Menu()
{
	printf("========================================\n");
	printf("学生成绩管理系统\n");
	printf("========================================\n");
	printf("请输入0-9功能键：\n");

	printf("1：成绩录入\n");
	printf("2：信息查询\n");
	printf("3：信息删除\n");
	printf("4：信息修改\n");
	printf("5：按数学成绩排序\n");
	printf("6：按英语成绩排序\n");
	printf("7：按平均成绩排序\n");
	printf("8：按学号排序\n");
	printf("9：信息保存\n");
	printf("0：退出程序\n");
	printf("输入（0-9）：");
}

STU * Create_List(STU * phead)
{
	char ans;
	STU * pnew;
	//STU * pend;
	phead = NULL;
	FILE * fp;
	
	printf("是否从已有的文件中读取信息（y/n）？");
	scanf(" %c", &ans);
	if (ans == 'y' || ans == 'Y')
	{
		if ((fp = fopen(FILENAME, "r")) == NULL)
		{
			printf("未找到已保存的文件！\n");
		}
		else
		{
			do
			{
				if ((pnew = (STU *)malloc(sizeof(STU))) == NULL)
				{
					printf("堆区内存已用完！\n");
					exit(1);
				}
				fscanf(fp, "%u %s %c %f %f %f\n", &pnew->num, pnew->name, &pnew->sex, &pnew->math, &pnew->English, &pnew->average);
				pnew->next = NULL;

				if (phead == NULL)
				{
					phead = pnew;
				}
				else
				{
					phead = Insert_Node(phead, pnew);
				}
			} while (feof(fp) != 1);
		}
		return phead;
	}

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
		pnew->average = (pnew->math + pnew->English) / 2;

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
	pnode->average = (pnode->math + pnode->English) / 2;
	pnode->next = NULL;
}

void Show_List(STU * phead)
{
	int listcount = 0;
	float mathavg=0, engavg=0;
	STU * pcur;
	if (NULL == phead)
	{
		printf("目前还没有录入学生信息\n");
		return;
	}
	printf("学号\t姓名\t性别\t数学成绩\t英语成绩\t平均分\n");
	pcur = phead;
	while (pcur != NULL)
	{
		printf("%u\t%s\t%c\t%3.1f\t\t%3.1f\t\t%3.1f\n", pcur->num, pcur->name, pcur->sex, pcur->math, pcur->English, pcur->average);
		mathavg += pcur->math;
		engavg += pcur->English;
		listcount++;
		pcur = pcur->next;
	}
	mathavg = mathavg / listcount;
	engavg = engavg / listcount;
	printf("学生数：%d\t数学平均分：%3.1f\t英语平均分：%3.1f", listcount, mathavg, engavg);
	printf("\n");
}

STU * Insert_Node(STU * phead, STU * pnew)
{
	STU * pcur;
	if (phead->num > pnew->num)
	{
		pnew->next = phead;
		return pnew;
	}
	if (phead->num == pnew->num)
	{
		printf("学号已存在，已将信息替换为新输入的信息！\n");
		pnew->next = phead->next;
		free(phead);
		return pnew;
	}
	for (pcur = phead; pcur->next != NULL; pcur = pcur->next)
	{
		if (pcur->next->num == pnew->num)
		{
			printf("学号已存在，已将信息替换为新输入的信息！\n");
			pnew->next = pcur->next->next;
			free(pcur->next);
			pcur->next = pnew;	
		}
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
		printf("没有可删除的数据鸭 (>_<) \n");
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
		printf("没有可修改的数据鸭 (>_<) \n");
		return;
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
			pupd->average = (pupd->math + pupd->English) / 2;
		}


		printf("输入考生的英语成绩（%3.1f）是否修改（y/n）？", pupd->English);
		scanf(" %c", &ans);
		if (ans == 'y' || ans == 'Y')
		{
			printf("输入考生的英语成绩：");
			scanf("%f", &pupd->English);
			pupd->average = (pupd->math + pupd->English) / 2;
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
	STU * pfirst = NULL, * pend = NULL;

	void * pdata;
	int data_size = sizeof(STU) - sizeof(STU *);

	if ((pdata = malloc(data_size)) == NULL)
	{
		printf("堆区内存已用完！\n");
		exit(1);
	}

	//冒泡排序
	pfirst = phead;
	while (pfirst != pend)
	{
		while (pfirst->next != pend)
		{
			switch (sort_by)
			{
			case NUM:
				if (pfirst->num > pfirst->next->num)
				{
					memcpy(pdata, (void *)pfirst, data_size);
					memcpy((void *)pfirst, (void *)pfirst->next, data_size);
					memcpy((void *)pfirst->next, pdata, data_size);
				}
				break;
			case MATH:
				if (pfirst->math > pfirst->next->math)
				{
					memcpy(pdata, (void *)pfirst, data_size);
					memcpy((void *)pfirst, (void *)pfirst->next, data_size);
					memcpy((void *)pfirst->next, pdata, data_size);
				}
				break;
			case ENGLISH:
				if (pfirst->English > pfirst->next->English)
				{
					memcpy(pdata, (void *)pfirst, data_size);
					memcpy((void *)pfirst, (void *)pfirst->next, data_size);
					memcpy((void *)pfirst->next, pdata, data_size);
				}
				break;
			case AVERAGE:
				if (pfirst->average > pfirst->next->average)
				{
					memcpy(pdata, (void *)pfirst, data_size);
					memcpy((void *)pfirst, (void *)pfirst->next, data_size);
					memcpy((void *)pfirst->next, pdata, data_size);
				}
				break;
			default:
				break;
			}
			
			pfirst = pfirst->next;
		}
		pend = pfirst;
		pfirst = phead;
	}
	free(pdata);
}

int Save_List2File(STU * phead, const char * filename)
{
	STU * pcur;
	FILE * fp;
	if (NULL == phead)
	{
		printf("目前还没有录入学生信息\n");
		return 1;
	}
	if ((fp = fopen(filename, "w+")) == NULL)
	{
		printf("不能打开文件\n");
		return 1;
	}	
	
	pcur = phead;
	while (pcur != NULL)
	{
		fprintf(fp,"%u\t%s\t%c\t%3.1f\t\t%3.1f\t\t%3.1f\n", pcur->num, pcur->name, pcur->sex, pcur->math, pcur->English, pcur->average);
		pcur = pcur->next;
	}
	fclose(fp);
	return 0;
}

int main()
{
	STU * head = NULL;
	int menu_input,n,result;
	STU * pn;

	head=Create_List(head);

	Show_Menu();

	while (1)
	{

		scanf("%d", &menu_input);

		switch (menu_input)
		{
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
			break;
		case 3: //信息删除
			printf("请输入您要删除的学生的学号：");
			scanf("%d", &n);
			head=Delete_Node(head, n);
			break;
		case 4: //信息修改
			printf("请输入要修改学生的学号：");
			scanf("%d", &n);
			Update_Node(head, n);
			break;
		case 5: //按数学成绩排序
			Sort_Node(head, MATH);
			Show_List(head);
			break;
		case 6: //按英语成绩排序
			Sort_Node(head, ENGLISH);
			Show_List(head);
			break;
		case 7: //按平均成绩排序
			Sort_Node(head, AVERAGE);
			Show_List(head);
			break;
		case 8: //按学号排序
			Sort_Node(head, NUM);
			Show_List(head);
			break;
		case 9: //信息保存
			result=Save_List2File(head, FILENAME);
			if (result == 0) printf("信息保存成功\n");
			else printf("信息保存失败！\n");
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