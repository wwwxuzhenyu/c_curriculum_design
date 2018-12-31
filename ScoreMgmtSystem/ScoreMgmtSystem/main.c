#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


void Show_Menu()
{
	printf("========================================\n");
	printf("ѧ���ɼ�����ϵͳ\n");
	printf("������0~5���ܼ���\n");

	printf("1���ɼ�¼��\n");
	printf("2����Ϣ��ѯ\n");
	printf("3����Ϣɾ��\n");
	printf("4����Ϣ�޸�\n");
	printf("5����Ϣ����\n");
	printf("0���˳�����\n");
	printf("���루0-5����");
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
			printf("�����ڴ������꣡\n");
			exit(1);
		}
		printf("�����¿����Ŀ��ţ�Ϊ0�������������");
		scanf("%u", &pnew->num);
		if (pnew->num == 0)
			break;

		printf("���뿼����������");
		scanf_s("%s", pnew->name, 20);
		getchar(); //����س�

		pnew->sex = 'a';
		while (pnew->sex != 'M' && pnew->sex != 'F')
		{
			printf("���뿼�����Ա�(M/F)��");
			scanf("%c", &pnew->sex);
			getchar(); //����س�
			if (pnew->sex == 'm') pnew->sex = 'M';
			if (pnew->sex == 'f') pnew->sex = 'F';
		}
		

		printf("���뿼������ѧ�ɼ���");
		scanf("%f", &pnew->math);
		printf("���뿼����Ӣ��ɼ���");
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
	free(pnew);                                 //�ͷſ���Ϊ0�Ľڵ�������Ŀռ�
	return phead;
}

void Set_Node(STU * pnode)
{
	printf("���뿼���Ŀ��ţ�");
	scanf("%u", &pnode->num);

	printf("���뿼����������");
	scanf_s("%s", pnode->name, 20);
	getchar(); //����س�

	pnode->sex = 'a';
	while (pnode->sex != 'M' && pnode->sex != 'F')
	{
		printf("���뿼�����Ա�(M/F)��");
		scanf("%c", &pnode->sex);
		getchar(); //����س�
		if (pnode->sex == 'm') pnode->sex = 'M';
		if (pnode->sex == 'f') pnode->sex = 'F';
	}


	printf("���뿼������ѧ�ɼ���");
	scanf("%f", &pnode->math);
	printf("���뿼����Ӣ��ɼ���");
	scanf("%f", &pnode->English);

	pnode->next = NULL;
}

void Show_List(STU * phead)
{
	STU * pcur;
	printf("ѧ��\t����\t�Ա�\t��ѧ�ɼ�\tӢ��ɼ�\n");
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
	printf("�ɼ�¼�뺯��\n");
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
		printf("û�п�ɾ��������Ѽ (>_<) ");
		return phead;
	}
	if (phead->num == n)
	{
		pcur = phead;
		phead = phead->next;
		printf("����Ϊ%d��ѧ����%s���ѱ���ɾ��\n",pcur->num,pcur->name);
		free(pcur);
		return phead;
	}
	for (pcur = phead; pcur->next != NULL; pcur = pcur->next)
	{
		if (pcur->next->num == n)
		{
			pdel = pcur->next;
			pcur->next = pdel->next;
			printf("����Ϊ%d��ѧ����%s���ѱ���ɾ��\n", pdel->num, pdel->name);
			free(pdel);
			return phead;
		}
	}
	printf("�����ɹ��������Ѿ�û��ѧ��Ϊ%d��ѧ��\n", n);
	return phead;
}

void Update_Node(STU * phead, unsigned n)
{
	STU * pcur, * pupd = NULL;
	if (phead == NULL)
	{
		printf("û�п��޸ĵ�����Ѽ (>_<) ");
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

		printf("���뿼����������%s���Ƿ��޸ģ�y/n����", pupd->name);
		scanf(" %c", &ans); //scanf���յ�����֮ǰ���л���ʱ��û�мӿո��scanf �����һ�еĻ��з���Ϊ�ַ����յ�
		if (ans == 'y' || ans == 'Y')
		{
			printf("\n���뿼����������");
			scanf_s("%s", pupd->name, 20);
			getchar(); //����س�
		}

		printf("���뿼�����Ա�%c���Ƿ��޸ģ�y/n����", pupd->sex);
		scanf(" %c", &ans);
		if (ans == 'y' || ans == 'Y')
		{
			pupd->sex = 'a';
			while (pupd->sex != 'M' && pupd->sex != 'F')
			{
				printf("���뿼�����Ա�(M/F)��");
				scanf(" %c", &pupd->sex);
				if (pupd->sex == 'm') pupd->sex = 'M';
				if (pupd->sex == 'f') pupd->sex = 'F';
			}
		}

		printf("���뿼������ѧ�ɼ���%3.1f���Ƿ��޸ģ�y/n����", pupd->math);
		fflush(stdin);
		scanf(" %c", &ans);
		if (ans == 'y' || ans == 'Y')
		{
			printf("���뿼������ѧ�ɼ���");
			scanf("%f", &pupd->math);
		}

		printf("���뿼����Ӣ��ɼ���%3.1f���Ƿ��޸ģ�y/n����", pupd->English);
		scanf(" %c", &ans);
		if (ans == 'y' || ans == 'Y')
		{
			printf("���뿼����Ӣ��ɼ���");
			scanf("%f", &pupd->English);
		}
		printf("�����ɹ�������Ϊ%d��ѧ����Ϣ���³ɹ�\n", n);
	}
	else
	{
		printf("���޿���Ϊ%d��ѧ��\n", n);
	}
}

void Sort_Node(STU * phead, enum SORT_BY sort_by)
{
	float t;

	//ð������
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
				printf("�����ڴ�\n");
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
		printf("4����Ϣ�޸�\n");
		printf("5����Ϣ����\n");
		printf("0���˳�����\n");
		*/
		case 0:
			exit(0);
		case 1: //�ɼ�¼��
			if ((pn = (STU *)malloc(sizeof(STU))) == NULL)
			{
				printf("�����ڴ������꣡\n");
				exit(1);
			}
			Set_Node(pn);
			head = Insert_Node(head, pn);
			Show_List(head);
			break;
		case 2: //��Ϣ��ѯ
			Show_List(head);
			printf("����ѧ����\n");
			getchar();
			Sort_Node(head, MATH);
			Show_List(head);
			break;
		case 3: //��Ϣɾ��
			printf("��������Ҫɾ����ѧ����ѧ�ţ�");
			scanf("%d", &n);
			head=Delete_Node(head, n);
			break;
		case 4:
			printf("������Ҫ�޸�ѧ����ѧ�ţ�");
			scanf("%d", &n);
			Update_Node(head, n);
			break;
		default:
			printf("��������ȷ��ֵ(0-5)\n\n");
			break;
		}
		
		getchar(); //����س�
		Show_Menu();
		
	}
	
	return 0;
}