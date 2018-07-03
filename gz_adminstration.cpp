/*******************************************************************************************************************************
Copyright (C), 2018/06/18--2018/06/29 ,���������ѧ. Co.,Ltd.
FileName: gz_adminstration.cpp
Description:  //ģ������
Version:      gz_adminstration 0.1  //�汾��Ϣ
Function List:     //��Ҫ�������书��
1.read()   �������ܣ��������ļ��ж�ȡְ���������ݡ���ʼ��ְ�����ʽṹ�����鲢ͳ�Ƶ�ǰ�����ļ���ְ������������ְ����������ȫ�ֱ���n�У��Ա���������ʹ�á� 
2.write()  �������ܣ���zggz�ṹ�������еļ�¼���浽gz.dat�����ļ��С�
3.find()   �������ܣ����ݹ��Ų�ѯ��Ӧְ���Ĺ��ʼ�¼��
4.list()   �������ܣ���ʾ����ְ���ļ�¼��
5.modify() �������ܣ�ָ�����ţ��޸ĸ�ְ���Ĺ��ʼ�¼
6.del()    �������ܣ�ɾ��ָ������ְ���ļ�¼
7.add()    �������ܣ���ӹ��ʼ�¼���ṹ������zggzĩβ
8.grsds()  �������ܣ������������˰��
9.main()   �������ܣ�������ʵ����ϵͳ�������棬�û����ڴ˽��������ѯ�������ɾ�������

History:              //��ʷ�޸ļ�¼
<author>          <time>            <Version>          <desc>
�����          2018/06/22            0.1             write  entirely  nine functions    
�����          2018/06/29            0.11            write  read()
*******************************************************************************************************************************/


#include <iostream>
#include <fstream>
#include "string.h"
#include <stdlib.h>
#include <cstdio>  
#include <conio.h>
#include <iomanip>
using namespace std;
int i;      //����i��������forѭ�������ʹ�á�
int n;      //����ְ������nΪȫ�ֱ���
int grsds(float yfsalary);     
struct gz
{
    char te_number[10]; //ְ������
	char name[10];    //ְ������
	float salary;     //��λ����
	float xj_salary;    //н������
	float jt_salary;    //ְ�����
	float jx_salary;    //��Ч����
	float yf_salary;    //Ӧ������
	float gr;         //��������˰
	float sf_salary;    // ʵ������	
	gz *prev;       //˫�������ǰָ�룬һ��ָ��ֱ��ǰ����ָ��
	gz *next;      //˫������ĺ�ָ�룬һ��ָ��ֱ�Ӻ�̵�ָ��
};


/*************************************************************************************************
Function:    read()         
Description: �������ļ��ж�ȡְ���������ݡ���ʼ��ְ�����ʽṹ�����鲢ͳ�Ƶ�ǰ�����ļ���ְ������������ְ����������ȫ�ֱ���n�У��Ա���������ʹ�á�
Calls:    eof() , close()
Called By :   main()����
Input :  �β�struct gz *zggz��ָ��ṹ���ָ�룬�β�t��main()�н������ݵĽṹ��������±�t������
Output:   
Return:  ����ְ������n��ֵ
others:  
*************************************************************************************************/
int read(struct gz *zggz,int &t)    //������ִ��ʱҪ���úͱ�����õĵ�һ������ :read()����
{ 	                              
  	int n=0;             //n������¼ְ��������һ��ʼ��ʼ��Ϊ0
    FILE *fp;
	gz *p;
	p=zggz;

    if((fp=fopen("gz.dat","rb"))==NULL)
	{
		printf("Can not open file strike any key exit !");
		getch();
		exit(-1);
	}

	for(i=0;!feof(fp);i++,p++)
	{
       fread(p,sizeof(struct gz),1,fp);
	   n++;
	}

	printf("�ɹ���ȡ�ļ��е�����\n");
	printf("���ļ��е�ְ�������ǣ�");
    printf("%d\n",n-1);

    fclose(fp); 
return n-1;                     //����ְ������n��ֵ
}


/*************************************************************************************************
Function:    write()         
Description: ��zggz�ṹ�������еļ�¼���浽gz.dat�����ļ��С�
Calls:   fopen() ,fwrite() 
Called By :   main()����
Input :  �β�struct gz *zggz��ָ��ṹ���ָ�룬�β�n ��main������n������
Output:   
Return:  ����return=0
others:  
*************************************************************************************************/
int write(struct gz *zggz,int &n)       //����ְ���������ݺ��� write()
{                                   
	FILE *fp;                 //�����ļ�ָ��
    struct gz *p;             //����ṹ��ָ��
	p=zggz;
	                               
    if(n>0) 
	{   
		if((fp=fopen("gz.dat","wb+"))==NULL)   
		{
			printf("Can not open file strike any key exit!\n");
			getch();
			exit(1);
		}

		fwrite(p,sizeof(struct gz),n,fp);     //fwrite()�ǡ�д���ݿ麯����   
       
	}

	else      
	{ 
		printf("��ΪNΪ0��С��0�����Գ����ˡ� \n");  
		return 1;
	}
    fclose(fp);
	printf("�ɹ����ṹ����������ݴ����ļ�gz.dat��.\n");
return 0;
}

/*************************************************************************************************
Function:    find()         
Description: ���ݹ��Ų�ѯ��Ӧְ���Ĺ��ʼ�¼��
Calls:   strcmp(), setw()
Called By :   main()����
Input :  �β�struct gz *zggz��ָ��ṹ���ָ�룬�β�n1 ��main������n������
Output:   
Return:  ����return=0
others:  
*************************************************************************************************/
int find(struct gz *zggz,int &n1)        
{                                        
	
	char gonghao[10];
    int k;

	printf("�����빤�ţ� \n");
	scanf("%s",gonghao);
	
    gz *p=&zggz[0]; 
	gz *head;          //����head ͷָ��
	zggz[0].prev=head;
    for(i=0;i<n1;i++)
	{    
		 
	     k=strcmp(p->te_number,gonghao);  //k=0,�����빤��number=zggz[i].te_number
	     if(k==0)
		 {  
		    printf("����  ����  ��λ���� н������ ְ�����  ");   
			printf("��Ч����  Ӧ������ ��������˰ ʵ������\n");
			printf("%s %s   ",p->te_number,p->name);
			printf("%.1f\t%.1f\t%.1f\t",p->salary,p->xj_salary,p->jt_salary);
			printf("%.1f\t  %.1f\t%.1f\t",p->jx_salary,p->yf_salary,p->gr);
		    printf("%.1f\n",p->sf_salary);     
		    printf("ֹͣ���ң����ص����˵���\n");
		 }

	     p=p->next;    //ʹpָ����һ���ڵ� 
	}

  return 0;
}


/*************************************************************************************************
Function:    list()         
Description: ��ʾ����ְ���ļ�¼��
Calls:    setw()
Called By :   main()����
Input :  �β�struct gz *zggz��ָ��ṹ���ָ�룬�β�n ��main������n������
Output:   
Return:  ����return=0
others:  
*************************************************************************************************/
int list(struct gz *zggz,int &n)     
{   
	gz *p=&zggz[0];                                 
	for(i=0;i<n;i++)      //�ڽṹ�������д�zggz[0] ��ʼ����n+1����¼����
	{       
		    printf("����  ����  ��λ���� н������ ְ�����  ");   
			printf("��Ч����  Ӧ������ ��������˰ ʵ������\n");
			printf("%s %s   ",p->te_number,p->name);
			printf("%.1f\t%.1f\t%.1f\t",p->salary,p->xj_salary,p->jt_salary);
			printf("%.1f\t  %.1f\t%.1f\t",p->jx_salary,p->yf_salary,p->gr);
		    printf("%.1f\n",p->sf_salary);    
			p=p->next;       //ʹpָ����һ���ڵ�   
	}

    printf("��ǰְ�����ʹ���ϵͳ���� ");
	printf("  %d",n);
	printf("λְ��������. \n");
return 0;
}

/*************************************************************************************************
Function:    modify()         
Description: ָ�����ţ��޸ĸ�ְ���Ĺ��ʼ�¼������Ҫ����grsds()���������������˰��
Calls:    strcmp(), grsds()
Called By :   main()����
Input :  �β�struct gz *zggz��ָ��ṹ���ָ�룬�β�n1 ��main������n������
Output:   
Return:  ��
others:  
*************************************************************************************************/
void modify(struct gz *zggz,int &n1)  
{                                    
	int k;              //k���ڼ�¼strcmp������ֵ��k=0���ҵ�������ͬ
	
	char gonghao[10];
	printf(" �����빤�ţ� \n");
	scanf("%s",&gonghao);

	gz *p=&zggz[0];
	gz *head;        //����һ��head ͷָ��
	zggz[0].prev=head;   //��һ���ڵ��ǰ��ָ��ָ�� head

    for(i=0;i<n1;i++,p=p->next)
	{ 
	     k=strcmp(p->te_number,gonghao);  //k=0,�����빤��number=zggz[i].te_number
	     if(k==0)
		 {
	       printf(" ����¼�������Ϣ:\n");
		   printf("����:");
		   scanf("%s",&(p->te_number));
           printf("\n");

		   printf("����:");
		   cscanf("%s",&(p->name));
           printf("\n");

		   printf("��λ����:");
		   scanf("%f",&(p->salary));
           printf("\n");

		   printf("н������:");
		   scanf("%f",&(p->xj_salary));
           printf("\n");

		   printf("ְ�����:");
		   scanf("%f",&(p->jt_salary));
		   printf("\n");

		   printf("��Ч����:");
		   scanf("%f",&(p->jx_salary));
		   printf("\n");

		   p->yf_salary=(p->salary+p->xj_salary+p->jt_salary+p->jx_salary);   //����Ӧ������
		                                               	                                        
           p->gr=grsds(p->yf_salary);               //�����������˰
		
		   p->sf_salary=(p->yf_salary-p->gr);   //����ʵ������

		   printf("�޸ĸ�ְ���Ĺ�����Ϣ���. \n");
		}
	}

    printf("�޸ĸ�ְ���Ĺ��ʼ�¼����ɡ� \n"); 
}

/*************************************************************************************************
Function:    del()         
Description: ɾ��ָ������ְ���ļ�¼
Calls:    strcmp(), 
Called By :   main()����
Input :  �β�struct gz *zggz��ָ��ṹ���ָ�룬�β�t������¼main()�н������ݵĽṹ��������±������,n�������ж����ְ������n ������
Output:   
Return:  return 0
others:  
*************************************************************************************************/
int del(struct gz *zggz,int &t,int &n)      
{                                    
	int mubi, k;                
    char number[10];        //number�������������빤��

    printf(" �����빤�ţ� \n");
	
	scanf("%s",&number);

	int flag=0;
   	gz *p=&zggz[0];
	gz *head;        //����һ��head ͷָ��
	zggz[0].prev=head;   //��һ���ڵ��ǰ��ָ��ָ�� head

	for(i=0;i<t;i++,p=p->next)
	{  
	
	   k=strcmp(p->te_number,number);  //k=0,�����빤��number=zggz[i].te_number
	   if(k==0)
	   {
		  flag=1;
		  mubi=i;
		  printf("�������в鵽��Ҫɾ��������λ�ڣ���zggz[");
		  printf("%d",i);
		  printf("]\n");
		  break; 
	   }

	   if(n==i) 
	   {      
			   if(!flag)
			   {
			   printf("�����е�n+1��¼û��,����\n ");  
			   return 1;
			   }
	   }
	 
	}

	printf("ȷ��ɾ��������11ȷ�ϣ�����22����ɾ����\n");

	int s;             //s������¼�����������11��22��
	scanf("%d",&s);

	if(s==11)       //ɾ���ü�¼
	{  
		printf("��ɾ���ü�¼������ \n");
	
		if(mubi==0)
		{    
				 zggz[mubi]=zggz[mubi+1];
				 zggz[mubi].next=&zggz[mubi+2];
				 zggz[mubi+2].prev=&zggz[mubi];	
		}

		else
		{
			  for(int j=mubi;j<n;j++)  
				 {   
				  zggz[j-1].next=&zggz[j+1];
				  zggz[j+1].prev=&zggz[j-1];
				 }
		}
		 
	    n=n-1;
	}
		   
	else if(s==22)
	{   
		printf("�ѷ���ɾ��������������\n");
		return 1;
	}

    printf("ֹͣ���ҡ����� \n");
return 0;
}

/*************************************************************************************************
Function:    add()         
Description: ��������:��ӹ��ʼ�¼���ṹ������zggzĩβ
Calls:    setw()
Called By :   main()����
Input :  �β�struct gz *zggz��ָ��ṹ���ָ�룬�β�n1 ��main������n������
Output:   
Return:  return 0
others:  
*************************************************************************************************/
int add(struct gz *zggz,int &n1)     
{   
	gz *p;

	if(n1==0)    //���ļ���һ�����ݶ�û�У�n1Ϊ��ʱ
	{
		p=&zggz[0];
		gz *head;        //����һ��head ͷָ��
	    zggz[0].prev=head;   //��һ���ڵ��ǰ��ָ��ָ�� head
	}

	else        //�ļ���������ʱ
	{
       p=zggz[n1-1].next;
	}

                                  
    printf("��������ְ��������Ϣ:\n");
	printf("����:");
	scanf("%s",&(p->te_number));
	printf("\n");

	printf("����:");
	scanf("%s",&(p->name));
	printf("\n");

	printf("��λ����:");
	scanf("%f",&(p->salary));
    printf("\n");

	printf("н������:");
    scanf("%f",&(p->xj_salary));
    printf("\n");

    printf("ְ�����:");
	scanf("%f",&(p->jt_salary));
	printf("\n");

	printf("��Ч����:");
	scanf("%f",&(p->jx_salary));
    printf("\n");

    p->yf_salary=(p->salary+p->xj_salary+p->jt_salary+p->jx_salary);  //����Ӧ������
                                      
    p->gr=grsds(p->yf_salary);               //�����������˰
	
	p->sf_salary=(p->yf_salary-p->gr);   //����ʵ������
   
    printf("����  ����  ��λ���� н������ ְ�����  ");   
	printf("��Ч����  Ӧ������ ��������˰ ʵ������\n");
    printf("%s %s",p->te_number,p->name);
	printf("  %.1f    %.1f   %.1f   ",p->salary,p->xj_salary,p->jt_salary);
	printf("%.1f     %.1f    %.1f",p->jx_salary,p->yf_salary,p->gr);
    printf("    %.1f\n",p->sf_salary);     
			
	n1=n1+1;
	printf("ְ����������1��Ϊ�� ");
	printf("%d",n1);
	printf("��\n");
return 0;
}

/*************************************************************************************************
Function:    grsds()       
Description: ��������:�����������˰�����ո�������˰˰�ʱ�������.
Calls:    
Called By :   main()����
Input :  �β���yfsalary������Ӧ������yf_salary��������ֵ
Output:   
Return:  ���ظ�������˰gr��ֵ
others:  
*************************************************************************************************/
int grsds(float yfsalary)   
{  
	float gr=0.0;       

	if(yfsalary<500)    //������500Ԫ�Ĳ���
	{
		gr=yfsalary*0.05;     
	}

	else if(yfsalary>500&&yfsalary<2000)   //����500Ԫ��2000Ԫ�Ĳ���
	{
		gr=yfsalary*0.10;
	}

	else if(yfsalary>2000&&yfsalary<5000)   //����2000Ԫ��5000Ԫ�Ĳ���
	{	
		gr=yfsalary*0.15;
	}

	else if(yfsalary>5000&&yfsalary<20000)  //����5000Ԫ��20000Ԫ�Ĳ���
	{
		gr=yfsalary*0.20;
	}

	else if(yfsalary>20000&&yfsalary<40000)  //����20000Ԫ��40000Ԫ�Ĳ���
	{
	     gr=yfsalary*0.25;
	}

	else if(yfsalary>40000&&yfsalary<60000)  //����40000Ԫ��60000Ԫ�Ĳ���
	{
		gr=yfsalary*0.30;
	} 

	else if(yfsalary>60000&&yfsalary<80000)  //����60000Ԫ��80000Ԫ�Ĳ���
	{
		gr=yfsalary*0.35;
	}
	
	else if(yfsalary>80000&&yfsalary<100000)  //����80000Ԫ��100000Ԫ�Ĳ���
	{
		gr=yfsalary*0.40;
	}

    else if(yfsalary>100000)    //����100000Ԫ�Ĳ���
	{
		gr=yfsalary*0.45;
	}

return gr;         //���ظ�������˰gr��ֵ
}


/*************************************************************************************************
Function:    main()����       
Description: ��������:������ʵ����ϵͳ�������棬�û����ڴ˽��������ѯ�������ɾ�������
Calls:    read(),write(), find(), list(), modify(), del(), add(), grsds()
Called By :   
Input :  
Output:   
Return:  return 0
others:  
*************************************************************************************************/
int main()      
{    
    gz zggz1[60];
    int t=60;     //��¼�ṹ������zggz1���±�
	gz *head;        //����һ��head ͷָ��
	zggz1[0].prev=head;   //��һ���ڵ��ǰ��ָ��ָ�� head


	for(i=0;i<59;i++)
	{ 
		zggz1[i].next=&zggz1[i+1];
        zggz1[i+1].prev=&zggz1[i];
	}

    zggz1[59].next=NULL;


    n=read(zggz1,t);
    printf("ְ������Ϊ�� ");
	printf("%d\n",n);
	 
	
    int cm;  //��¼�������ֵ�ֵ
	    printf("       ###  ��ӭʹ�ù��������ѧ�������Ϣ��ȫѧԺְ�����ʹ���ϵͳ  ###\n");
	    printf("\n");
	
	
	while(cm)
	{   
		printf("       ��ѡ��1 �� 7����\n");
		printf("       ================================================================\n");
        printf("       |        1.��ѯְ�����ʼ�¼                                    |\n");
		printf("       |        2.�޸�ְ�����ʼ�¼                                    |\n");
        printf("       |        3.���ְ�����ʼ�¼                                    |\n");
		printf("       |        4.ɾ��ְ�����ʼ�¼                                    |\n");
		printf("       |        5.�������ݵ��ļ�                                      |\n");
		printf("       |        6.���ְ����¼                                        |\n");
		printf("       |        7.�˳�ϵͳ                                            |\n");
		printf("       ================================================================\n");
		printf("\n");
		printf("      ���ѡ���ǣ�\n");

		scanf("%d",&cm);

	    switch(cm)         //ʹ��switch���ʵ�ֶ��֧ѡ�񣬼�ִ�������벻ͬ��������
		{ 
		   case 1:
			  {
                find(zggz1,n);
				break;
			  }

		   case 2:
			  {
				modify(zggz1,n);
				break;
			  }

		   case 3:
			  {
				add(zggz1,n);
				break;
			  }

		   case 4:
			  {
				del(zggz1,t,n);
				break;
			  }

		   case 5:
			  {
				write(zggz1,n);
				break;
			  }

		   case 6:
			  {
				list(zggz1,n); 
				break;
			  }

		   case 7:
			  {
				 printf("���������������˳���\n ");
				 return 0;
			  }

           default:
			  {
				  printf("�û��������������������1��7��������֣��������˳�������7\n");
			  }
		}

	}

return 0;
}