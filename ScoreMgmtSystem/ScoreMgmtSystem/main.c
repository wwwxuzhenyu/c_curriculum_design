#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


void Show_Menu()
{
	printf("========================================\n");
	printf("ѧ���ɼ�����ϵͳ\n");
	printf("========================================\n");
	printf("������0-9���ܼ���\n");

	printf("1���ɼ�¼��\n");
	printf("2����Ϣ��ѯ\n");
	printf("3����Ϣɾ��\n");
	printf("4����Ϣ�޸�\n");
	printf("5������ѧ�ɼ�����\n");
	printf("6����Ӣ��ɼ�����\n");
	printf("7����ƽ���ɼ�����\n");
	printf("8����ѧ������\n");
	printf("9����Ϣ����\n");
	printf("0���˳�����\n");
	printf("���루0-9����");
}

STU * Create_List(STU * phead)
{
	char ans;
	STU * pnew;
	//STU * pend;
	phead = NULL;
	FILE * fp;
	
	printf("�Ƿ�����е��ļ��ж�ȡ��Ϣ��y/n����");
	scanf(" %c", &ans);
	if (ans == 'y' || ans == 'Y')
	{
		if ((fp = fopen(FILENAME, "r")) == NULL)
		{
			printf("δ�ҵ��ѱ�����ļ���\n");
		}
		else
		{
			do
			{
				if ((pnew = (STU *)malloc(sizeof(STU))) == NULL)
				{
					printf("�����ڴ������꣡\n");
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
		printf("Ŀǰ��û��¼��ѧ����Ϣ\n");
		return;
	}
	printf("ѧ��\t����\t�Ա�\t��ѧ�ɼ�\tӢ��ɼ�\tƽ����\n");
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
	printf("ѧ������%d\t��ѧƽ���֣�%3.1f\tӢ��ƽ���֣�%3.1f", listcount, mathavg, engavg);
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
		printf("ѧ���Ѵ��ڣ��ѽ���Ϣ�滻Ϊ���������Ϣ��\n");
		pnew->next = phead->next;
		free(phead);
		return pnew;
	}
	for (pcur = phead; pcur->next != NULL; pcur = pcur->next)
	{
		if (pcur->next->num == pnew->num)
		{
			printf("ѧ���Ѵ��ڣ��ѽ���Ϣ�滻Ϊ���������Ϣ��\n");
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
		printf("û�п�ɾ��������Ѽ (>_<) \n");
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
		printf("û�п��޸ĵ�����Ѽ (>_<) \n");
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
			pupd->average = (pupd->math + pupd->English) / 2;
		}


		printf("���뿼����Ӣ��ɼ���%3.1f���Ƿ��޸ģ�y/n����", pupd->English);
		scanf(" %c", &ans);
		if (ans == 'y' || ans == 'Y')
		{
			printf("���뿼����Ӣ��ɼ���");
			scanf("%f", &pupd->English);
			pupd->average = (pupd->math + pupd->English) / 2;
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
	STU * pfirst = NULL, * pend = NULL;

	void * pdata;
	int data_size = sizeof(STU) - sizeof(STU *);

	if ((pdata = malloc(data_size)) == NULL)
	{
		printf("�����ڴ������꣡\n");
		exit(1);
	}

	//ð������
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
		printf("Ŀǰ��û��¼��ѧ����Ϣ\n");
		return 1;
	}
	if ((fp = fopen(filename, "w+")) == NULL)
	{
		printf("���ܴ��ļ�\n");
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
			break;
		case 3: //��Ϣɾ��
			printf("��������Ҫɾ����ѧ����ѧ�ţ�");
			scanf("%d", &n);
			head=Delete_Node(head, n);
			break;
		case 4: //��Ϣ�޸�
			printf("������Ҫ�޸�ѧ����ѧ�ţ�");
			scanf("%d", &n);
			Update_Node(head, n);
			break;
		case 5: //����ѧ�ɼ�����
			Sort_Node(head, MATH);
			Show_List(head);
			break;
		case 6: //��Ӣ��ɼ�����
			Sort_Node(head, ENGLISH);
			Show_List(head);
			break;
		case 7: //��ƽ���ɼ�����
			Sort_Node(head, AVERAGE);
			Show_List(head);
			break;
		case 8: //��ѧ������
			Sort_Node(head, NUM);
			Show_List(head);
			break;
		case 9: //��Ϣ����
			result=Save_List2File(head, FILENAME);
			if (result == 0) printf("��Ϣ����ɹ�\n");
			else printf("��Ϣ����ʧ�ܣ�\n");
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