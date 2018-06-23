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

*******************************************************************************************************************************/
#include <iostream>
#include <fstream>
#include "string.h"
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
using namespace std;
int i; 
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
};

int read(struct gz *zggz,int &t)    //������ִ��ʱҪ���úͱ�����õĵ�һ������ :read()����
{ 	                              //�β�struct gz *zggz��ָ��ṹ���ָ�룬�β�t��main()�н������ݵĽṹ��������±�t������
	int n=0;             //n������¼ְ��������һ��ʼ��ʼ��Ϊ0

	ifstream in("gz.dat",ios::in|ios::binary);
	if(!in)
	{ cout<<"Can not open input file.\n";
	  exit(1);
	}

    for(int i=0;!in.eof();i++)                 //��eof()�����ж��ļ�ָ���Ƿ��ļ�β�����Ƿ�����ļ��е�����
	{  
	    in.read((char*)&zggz[i],sizeof(zggz[i]));
		n++;                                         //��¼ְ������   		                   
	}
	
	in.close();
	cout<<n-1<<endl;
	cout<<"�ɹ���ȡ�ļ��е�����."<<endl;
return n-1;                     //����ְ������n
}

int write(struct gz *zggz,int &n)   //����ְ���������ݺ��� write()
{                                   // �β�struct gz *zggz��ָ��ṹ���ָ�룬�β�n ��main������n������
	FILE *fp;                 //�����ļ�ָ��
    struct gz *p;             //����ṹ��ָ��
	p=zggz;
	                               
    if(n>0) 
	{   
		if((fp=fopen("gz.dat","wb+"))==NULL)   
		{
			cout<<"Can not open file strike any key exit!";
			getch();
			exit(1);
		}

		fwrite(p,sizeof(struct gz),n,fp);     //fwrite()�ǡ�д���ݿ麯����   
       
	}
	else      
	{ 
		cout<<"��ΪNΪ0��С��0�����Գ����ˡ� "<<endl;  
		return 1;
	}
	cout<<"�ɹ����ṹ����������ݴ����ļ�gz.dat��."<<endl;
return 0;
}

int find(struct gz *zggz,int &n1)         //find()������ ���ݹ��Ų�ѯ��Ӧְ���Ĺ��ʼ�¼
{                                        // �β�struct gz *zggz��ָ��ṹ���ָ�룬�β�n1 ��main������n������
	
	char gonghao[10];
    int k;

	cout<<"�����빤�ţ� "<<endl;
	cin>>gonghao; 

    for(i=0;i<n1;i++)
	{ 
	     k=strcmp(zggz[i].te_number,gonghao);  //k=0,�����빤��number=zggz[i].te_number
	     if(k==0)
		 {
            cout<<"����"<<setw(7)<<"����"<<setw(9)<<"��λ����"<<setw(9)<<"н������"<<setw(9)<<"ְ�����"<<setw(9);   //ʹ��setw()�������趨�´������ȣ�������������Ҷ���
	        cout<<"��Ч����"<<setw(9)<<"Ӧ������"<<setw(12)<<"��������˰"<<setw(9)<<"ʵ������"<<endl;
			cout<<zggz[i].te_number<<setw(7)<<zggz[i].name<<setw(9);
			cout<<zggz[i].salary<<setw(9)<<zggz[i].xj_salary<<setw(9)<<zggz[i].jt_salary<<setw(9);
			cout<<zggz[i].jx_salary<<setw(9)<<zggz[i].yf_salary<<setw(12);
			cout<<zggz[i].gr<<setw(9)<<zggz[i].sf_salary<<endl;     
		    cout<<"ֹͣ���ң����ص����˵���"<<endl;
		 }
	}

  return 0;
}

int list(struct gz *zggz,int &n)     //list() ��ʾ����ְ���ļ�¼
{                                    //�β�struct gz *zggz��ָ��ṹ���ָ�룬�β�n ��main������n������
	for(i=0;i<n;i++)      //�ڽṹ�������д�zggz[0] ��ʼ����n+1����¼����
	{       
		    cout<<"����"<<setw(7)<<"����"<<setw(9)<<"��λ����"<<setw(9)<<"н������"<<setw(9)<<"ְ�����"<<setw(9);   //ʹ��setw()�������趨�´������ȣ�������������Ҷ���
	        cout<<"��Ч����"<<setw(9)<<"Ӧ������"<<setw(12)<<"��������˰"<<setw(9)<<"ʵ������"<<endl;
			cout<<zggz[i].te_number<<setw(7)<<zggz[i].name<<setw(9);
			cout<<zggz[i].salary<<setw(9)<<zggz[i].xj_salary<<setw(9)<<zggz[i].jt_salary<<setw(9);
			cout<<zggz[i].jx_salary<<setw(9)<<zggz[i].yf_salary<<setw(12);
			cout<<zggz[i].gr<<setw(9)<<zggz[i].sf_salary<<endl; 
			
		  /*cout<<"����"<<"  "<<"����"<<"     "<<"��λ����"<<" "<<"н������"<<" "<<"ְ�����"<<" ";          //ʹ����˫�����мӿո�ķ�ʽ������ݣ������
	        cout<<"��Ч����"<<" "<<"Ӧ������"<<" "<<"��������˰"<<" "<<"ʵ������"<<endl;
			cout<<zggz[i].te_number<<"  "<<zggz[i].name<<"    ";
			cout<<zggz[i].salary<<"     "<<zggz[i].xj_salary<<"     "<<zggz[i].jt_salary<<"       ";
			cout<<zggz[i].jx_salary<<"       "<<zggz[i].yf_salary<<"  ";
			cout<<zggz[i].gr<<"     "<<zggz[i].sf_salary<<endl;                                  */
	}

    cout<<"��ǰְ�����ʹ���ϵͳ���� "<<n<<"λְ��������. "<<endl;
return 0;
}

void modify(struct gz *zggz,int &n1)   //modify()ָ�����ţ��޸ĸ�ְ���Ĺ��ʼ�¼��
{                                     // n1��ְ������n������
	int k;                            //k���ڼ�¼strcmp������ֵ��k=0���ҵ�������ͬ
	gz xigz;                         //����ṹ�����xigz

	char gonghao[10];
	cout<<"�����빤�ţ� "<<endl;
	cin>>gonghao;
	
    for(i=0;i<n1;i++)
	{ 
	     k=strcmp(zggz[i].te_number,gonghao);  //k=0,�����빤��number=zggz[i].te_number
	     if(k==0)
		 {
	     cout<<"����¼�������Ϣ:"<<endl;
		 cout<<"����"<<" ";
		 cin>>xigz.te_number;
		 cout<<"����"<<" ";
		 cin>>xigz.name;
		 cout<<"��λ����"<<" ";
		 cin>>xigz.salary;
		 cout<<"н������"<<" ";
		 cin>>xigz.xj_salary;
		 cout<<"ְ�����"<<" ";
		 cin>>xigz.jt_salary;
		 cout<<"��Ч����"<<"  ";
		 cin>>xigz.jx_salary;

		 xigz.yf_salary=(xigz.salary+xigz.xj_salary+xigz.jt_salary+xigz.jx_salary);   //����Ӧ������
		                                               	                                        
         xigz.gr=grsds(xigz.yf_salary);               //�����������˰
		
		 xigz.sf_salary=(xigz.yf_salary-xigz.gr);   //����ʵ������
		
		 zggz[i]=xigz;              //���ṹ�����xigz��ֵ��zggz[i],����޸�

		 cout<<"�޸ĸ�ְ���Ĺ�����Ϣ���. "<<endl;
		}
	}

   cout<<"�޸ĸ�ְ���Ĺ��ʼ�¼����ɡ� "<<endl; 
}

int del(struct gz *zggz,int &t,int &n)      // del()�������ã�ɾ��ָ������ְ���ļ�¼
{                                    //�β�struct gz *zggz��ָ��ṹ���ָ�룬�β�t������¼main()�н������ݵĽṹ��������±������,n�������ж����ְ������n ������
	int mubi, k;                
    char number[10];        //number�������������빤��

	cout<<"�����빤�ţ�"<<endl;
	cin>>number;

	int flag=0;

	for(i=0;i<t;i++)
	{  
	
	   k=strcmp(zggz[i].te_number,number);  //k=0,�����빤��number=zggz[i].te_number
	   if(k==0)
	   {
		  flag=1;
		  mubi=i;
		  cout<<"�������в鵽��Ҫɾ��������λ�ڣ���zggz["<<i<<"] "<<endl;
		  break; 
	   }

	   if(n==i) 
	   {      
			   if(!flag)
			   {
			   cout<<"�����е�n+1��¼û��,���� "<<endl;  
			   return 1;
			   }
	   }
	 
	}

	cout<<"ȷ��ɾ��������11ȷ�ϣ�����22����ɾ����"<<endl;

	int s;             //s������¼�����������11��22��
	cin>>s;

	if(s==11)       //ɾ���ü�¼
	{  
		cout<<"��ɾ���ü�¼������ "<<endl; 
		if(mubi<n)
		{
			 for(int j=mubi;j<n;j++)  
			 {
                zggz[j]=zggz[j+1];
			 }
		 
		} 
		n=n-1;
	}
		   
	else if(s==22)
	{   
		cout<<"�ѷ���ɾ��������������"<<endl;
		return 1;
	}

     cout<<"ֹͣ���ҡ����� "<<endl;
return 0;
}

int add(struct gz *zggz,int &n1)     //��������:��ӹ��ʼ�¼���ṹ������zggzĩβ
{                                    //�β�struct gz *zggz��ָ��ṹ���ָ�룬n1��ְ������n������
    cout<<"��������ְ��������Ϣ:"<<endl;
	cout<<"����"<<" ";
	cin>>zggz[n1].te_number;
	cout<<"����"<<" ";
	cin>>zggz[n1].name;
	cout<<"��λ����"<<" ";
	cin>>zggz[n1].salary;
	cout<<"н������"<<" ";
    cin>>zggz[n1].xj_salary;
    cout<<"ְ�����"<<" ";
	cin>>zggz[n1].jt_salary;
	cout<<"��Ч����"<<"  ";
	cin>>zggz[n1].jx_salary;

    zggz[n1].yf_salary=(zggz[n1].salary+zggz[n1].xj_salary+zggz[n1].jt_salary+zggz[n1].jx_salary);  //����Ӧ������
                                      
    zggz[n1].gr=grsds(zggz[n1].yf_salary);               //�����������˰
	
	zggz[n1].sf_salary=(zggz[n1].yf_salary-zggz[n1].gr);   //����ʵ������

    cout<<"��ְ����ȫ����ϢΪ :"<<endl;
	cout<<"����"<<setw(7)<<"����"<<setw(9)<<"��λ����"<<setw(9)<<"н������"<<setw(9)<<"ְ�����"<<setw(9);   //ʹ��setw()�������趨�´������ȣ�������������Ҷ���
	cout<<"��Ч����"<<setw(9)<<"Ӧ������"<<setw(12)<<"��������˰"<<setw(9)<<"ʵ������"<<endl;
    cout<<zggz[n1].te_number<<setw(7)<<zggz[n1].name<<setw(9);
	cout<<zggz[n1].salary<<setw(9)<<zggz[n1].xj_salary<<setw(9)<<zggz[n1].jt_salary<<setw(9);
	cout<<zggz[n1].jx_salary<<setw(9)<<zggz[n1].yf_salary<<setw(12);
	cout<<zggz[n1].gr<<setw(9)<<zggz[n1].sf_salary<<endl;    
	n1=n1+1;
	cout<<"ְ����������1��Ϊ�� "<<n1<<endl;
return 0;
}

int grsds(float yfsalary)   //grsds()�������ã������������˰�����ո�������˰˰�ʱ�������
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

int main()       //main()��������: ������ʵ����ϵͳ�������棬�û����ڴ˽��������ѯ�������ɾ�������
{    
    gz zggz1[50];
    int t=50;     //��¼�ṹ������zggz1���±�

    n=read(zggz1,t);
    cout<<"ְ������Ϊ�� "<<n<<endl;
	 
	
    int cm;                 //��¼�������ֵ�ֵ
	cout<<"                     ��ӭʹ��ְ�����ʹ���ϵͳ��"<<endl;
	
	
	while(cm)
	{ 
		cout<<"                           ���ܲ˵�:"<<endl;
		cout<<"                     1.��ѯ 2.�޸� 3.��� "<<endl;
		cout<<"                     4.ɾ�� 5.���� 6.��� "<<endl;
		cout<<"                            7.�˳�"<<endl;
	    cout<<"���������"<<endl;
        cin>>cm;

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
				 cout<<"���������������˳��� "<<endl;
				 return 0;
			  }

           default:
			  {
				  cout<<"�û��������������������1��7��������֣��������˳�������7"<<endl;
			  }
		}

	}

return 0;
}