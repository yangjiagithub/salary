/*******************************************************************************************************************************
Copyright (C), 2018/06/18--2018/06/29 ,广西民族大学. Co.,Ltd.
FileName: gz_adminstration.cpp
Description:  //模块描述
Version:      gz_adminstration 0.1  //版本信息
Function List:     //主要函数及其功能
1.read()   函数功能：从数据文件中读取职工工资数据、初始化职工工资结构体数组并统计当前数据文件中职工人数，并将职工人数存在全局变量n中，以备其他函数使用。 
2.write()  函数功能：将zggz结构体数组中的记录保存到gz.dat数据文件中。
3.find()   函数功能：根据工号查询相应职工的工资记录。
4.list()   函数功能：显示所有职工的记录。
5.modify() 函数功能：指定工号，修改该职工的工资记录
6.del()    函数功能：删除指定工号职工的记录
7.add()    函数功能：添加工资记录到结构体数组zggz末尾
8.grsds()  函数功能：计算个人所得税，
9.main()   函数功能：主函数实现了系统的主界面，用户可在此界面输入查询、浏览、删除等命令。

History:              //历史修改记录
<author>          <time>            <Version>          <desc>
杨家雄          2018/06/22            0.1             write  entirely  nine functions    
杨家雄          2018/06/29            0.11            write  read()
*******************************************************************************************************************************/


#include <iostream>
#include <fstream>
#include "string.h"
#include <stdlib.h>
#include <cstdio>  
#include <conio.h>
#include <iomanip>
using namespace std;
int i;      //定义i，用于在for循环语句中使用。
int n;      //定义职工人数n为全局变量
int grsds(float yfsalary);     
struct gz
{
    char te_number[10]; //职工工号
	char name[10];    //职工姓名
	float salary;     //岗位工资
	float xj_salary;    //薪级工资
	float jt_salary;    //职务津贴
	float jx_salary;    //绩效工资
	float yf_salary;    //应发工资
	float gr;         //个人所得税
	float sf_salary;    // 实发工资	
	gz *prev;       //双向链表的前指针，一个指向直接前驱的指针
	gz *next;      //双向链表的后指针，一个指向直接后继的指针
};


/*************************************************************************************************
Function:    read()         
Description: 从数据文件中读取职工工资数据、初始化职工工资结构体数组并统计当前数据文件中职工人数，并将职工人数存在全局变量n中，以备其他函数使用。
Calls:    eof() , close()
Called By :   main()函数
Input :  形参struct gz *zggz是指向结构体的指针，形参t是main()中接受数据的结构体数组的下标t的引用
Output:   
Return:  返回职工人数n的值
others:  
*************************************************************************************************/
int read(struct gz *zggz,int &t)    //主函数执行时要调用和必须调用的第一个函数 :read()函数
{ 	                              
  	int n=0;             //n用来记录职工人数，一开始初始化为0
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

	printf("成功读取文件中的数据\n");
	printf("该文件中的职工人数是：");
    printf("%d\n",n-1);

    fclose(fp); 
return n-1;                     //返回职工人数n的值
}


/*************************************************************************************************
Function:    write()         
Description: 将zggz结构体数组中的记录保存到gz.dat数据文件中。
Calls:   fopen() ,fwrite() 
Called By :   main()函数
Input :  形参struct gz *zggz是指向结构体的指针，形参n 是main函数中n的引用
Output:   
Return:  返回return=0
others:  
*************************************************************************************************/
int write(struct gz *zggz,int &n)       //保存职工工资数据函数 write()
{                                   
	FILE *fp;                 //定义文件指针
    struct gz *p;             //定义结构体指针
	p=zggz;
	                               
    if(n>0) 
	{   
		if((fp=fopen("gz.dat","wb+"))==NULL)   
		{
			printf("Can not open file strike any key exit!\n");
			getch();
			exit(1);
		}

		fwrite(p,sizeof(struct gz),n,fp);     //fwrite()是“写数据块函数”   
       
	}

	else      
	{ 
		printf("因为N为0或小于0，所以出错了。 \n");  
		return 1;
	}
    fclose(fp);
	printf("成功将结构体数组的数据存入文件gz.dat中.\n");
return 0;
}

/*************************************************************************************************
Function:    find()         
Description: 根据工号查询相应职工的工资记录。
Calls:   strcmp(), setw()
Called By :   main()函数
Input :  形参struct gz *zggz是指向结构体的指针，形参n1 是main函数中n的引用
Output:   
Return:  返回return=0
others:  
*************************************************************************************************/
int find(struct gz *zggz,int &n1)        
{                                        
	
	char gonghao[10];
    int k;

	printf("请输入工号： \n");
	scanf("%s",gonghao);
	
    gz *p=&zggz[0]; 
	gz *head;          //定义head 头指针
	zggz[0].prev=head;
    for(i=0;i<n1;i++)
	{    
		 
	     k=strcmp(p->te_number,gonghao);  //k=0,即输入工号number=zggz[i].te_number
	     if(k==0)
		 {  
		    printf("工号  姓名  岗位工资 薪级工资 职务津贴  ");   
			printf("绩效工资  应发工资 个人所得税 实发工资\n");
			printf("%s %s   ",p->te_number,p->name);
			printf("%.1f\t%.1f\t%.1f\t",p->salary,p->xj_salary,p->jt_salary);
			printf("%.1f\t  %.1f\t%.1f\t",p->jx_salary,p->yf_salary,p->gr);
		    printf("%.1f\n",p->sf_salary);     
		    printf("停止查找，将回到主菜单。\n");
		 }

	     p=p->next;    //使p指向下一个节点 
	}

  return 0;
}


/*************************************************************************************************
Function:    list()         
Description: 显示所有职工的记录。
Calls:    setw()
Called By :   main()函数
Input :  形参struct gz *zggz是指向结构体的指针，形参n 是main函数中n的引用
Output:   
Return:  返回return=0
others:  
*************************************************************************************************/
int list(struct gz *zggz,int &n)     
{   
	gz *p=&zggz[0];                                 
	for(i=0;i<n;i++)      //在结构体数组中从zggz[0] 开始，到n+1条记录结束
	{       
		    printf("工号  姓名  岗位工资 薪级工资 职务津贴  ");   
			printf("绩效工资  应发工资 个人所得税 实发工资\n");
			printf("%s %s   ",p->te_number,p->name);
			printf("%.1f\t%.1f\t%.1f\t",p->salary,p->xj_salary,p->jt_salary);
			printf("%.1f\t  %.1f\t%.1f\t",p->jx_salary,p->yf_salary,p->gr);
		    printf("%.1f\n",p->sf_salary);    
			p=p->next;       //使p指向下一个节点   
	}

    printf("当前职工工资管理系统中有 ");
	printf("  %d",n);
	printf("位职工的数据. \n");
return 0;
}

/*************************************************************************************************
Function:    modify()         
Description: 指定工号，修改该职工的工资记录，其中要调用grsds()函数计算个人所得税。
Calls:    strcmp(), grsds()
Called By :   main()函数
Input :  形参struct gz *zggz是指向结构体的指针，形参n1 是main函数中n的引用
Output:   
Return:  无
others:  
*************************************************************************************************/
void modify(struct gz *zggz,int &n1)  
{                                    
	int k;              //k用于记录strcmp函数的值，k=0即找到工号相同
	
	char gonghao[10];
	printf(" 请输入工号： \n");
	scanf("%s",&gonghao);

	gz *p=&zggz[0];
	gz *head;        //定义一个head 头指针
	zggz[0].prev=head;   //第一个节点的前驱指针指向 head

    for(i=0;i<n1;i++,p=p->next)
	{ 
	     k=strcmp(p->te_number,gonghao);  //k=0,即输入工号number=zggz[i].te_number
	     if(k==0)
		 {
	       printf(" 重新录入基本信息:\n");
		   printf("工号:");
		   scanf("%s",&(p->te_number));
           printf("\n");

		   printf("姓名:");
		   cscanf("%s",&(p->name));
           printf("\n");

		   printf("岗位工资:");
		   scanf("%f",&(p->salary));
           printf("\n");

		   printf("薪级工资:");
		   scanf("%f",&(p->xj_salary));
           printf("\n");

		   printf("职务津贴:");
		   scanf("%f",&(p->jt_salary));
		   printf("\n");

		   printf("绩效工资:");
		   scanf("%f",&(p->jx_salary));
		   printf("\n");

		   p->yf_salary=(p->salary+p->xj_salary+p->jt_salary+p->jx_salary);   //计算应发工资
		                                               	                                        
           p->gr=grsds(p->yf_salary);               //计算个人所得税
		
		   p->sf_salary=(p->yf_salary-p->gr);   //计算实发工资

		   printf("修改该职工的工资信息完成. \n");
		}
	}

    printf("修改该职工的工资记录已完成。 \n"); 
}

/*************************************************************************************************
Function:    del()         
Description: 删除指定工号职工的记录
Calls:    strcmp(), 
Called By :   main()函数
Input :  形参struct gz *zggz是指向结构体的指针，形参t用来记录main()中接受数据的结构体数组的下标的引用,n主函数中定义的职工人数n 的引用
Output:   
Return:  return 0
others:  
*************************************************************************************************/
int del(struct gz *zggz,int &t,int &n)      
{                                    
	int mubi, k;                
    char number[10];        //number用来接受所输入工号

    printf(" 请输入工号： \n");
	
	scanf("%s",&number);

	int flag=0;
   	gz *p=&zggz[0];
	gz *head;        //定义一个head 头指针
	zggz[0].prev=head;   //第一个节点的前驱指针指向 head

	for(i=0;i<t;i++,p=p->next)
	{  
	
	   k=strcmp(p->te_number,number);  //k=0,即输入工号number=zggz[i].te_number
	   if(k==0)
	   {
		  flag=1;
		  mubi=i;
		  printf("在数组中查到，要删除的数据位于，是zggz[");
		  printf("%d",i);
		  printf("]\n");
		  break; 
	   }

	   if(n==i) 
	   {      
			   if(!flag)
			   {
			   printf("数组中的n+1记录没有,错误。\n ");  
			   return 1;
			   }
	   }
	 
	}

	printf("确认删除否？输入11确认，输入22放弃删除。\n");

	int s;             //s用来记录输入整数命令（11或22）
	scanf("%d",&s);

	if(s==11)       //删除该记录
	{  
		printf("将删除该记录··· \n");
	
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
		printf("已放弃删除······\n");
		return 1;
	}

    printf("停止查找··· \n");
return 0;
}

/*************************************************************************************************
Function:    add()         
Description: 函数作用:添加工资记录到结构体数组zggz末尾
Calls:    setw()
Called By :   main()函数
Input :  形参struct gz *zggz是指向结构体的指针，形参n1 是main函数中n的引用
Output:   
Return:  return 0
others:  
*************************************************************************************************/
int add(struct gz *zggz,int &n1)     
{   
	gz *p;

	if(n1==0)    //当文件中一个数据都没有，n1为零时
	{
		p=&zggz[0];
		gz *head;        //定义一个head 头指针
	    zggz[0].prev=head;   //第一个节点的前驱指针指向 head
	}

	else        //文件中有数据时
	{
       p=zggz[n1-1].next;
	}

                                  
    printf("依次输入职工基本信息:\n");
	printf("工号:");
	scanf("%s",&(p->te_number));
	printf("\n");

	printf("姓名:");
	scanf("%s",&(p->name));
	printf("\n");

	printf("岗位工资:");
	scanf("%f",&(p->salary));
    printf("\n");

	printf("薪级工资:");
    scanf("%f",&(p->xj_salary));
    printf("\n");

    printf("职务津贴:");
	scanf("%f",&(p->jt_salary));
	printf("\n");

	printf("绩效工资:");
	scanf("%f",&(p->jx_salary));
    printf("\n");

    p->yf_salary=(p->salary+p->xj_salary+p->jt_salary+p->jx_salary);  //计算应发工资
                                      
    p->gr=grsds(p->yf_salary);               //计算个人所得税
	
	p->sf_salary=(p->yf_salary-p->gr);   //计算实发工资
   
    printf("工号  姓名  岗位工资 薪级工资 职务津贴  ");   
	printf("绩效工资  应发工资 个人所得税 实发工资\n");
    printf("%s %s",p->te_number,p->name);
	printf("  %.1f    %.1f   %.1f   ",p->salary,p->xj_salary,p->jt_salary);
	printf("%.1f     %.1f    %.1f",p->jx_salary,p->yf_salary,p->gr);
    printf("    %.1f\n",p->sf_salary);     
			
	n1=n1+1;
	printf("职工人数增加1后为： ");
	printf("%d",n1);
	printf("人\n");
return 0;
}

/*************************************************************************************************
Function:    grsds()       
Description: 函数作用:计算个人所得税，按照个人所得税税率表来计算.
Calls:    
Called By :   main()函数
Input :  形参是yfsalary，接收应发工资yf_salary传过来的值
Output:   
Return:  返回个人所得税gr的值
others:  
*************************************************************************************************/
int grsds(float yfsalary)   
{  
	float gr=0.0;       

	if(yfsalary<500)    //不超过500元的部分
	{
		gr=yfsalary*0.05;     
	}

	else if(yfsalary>500&&yfsalary<2000)   //超过500元到2000元的部分
	{
		gr=yfsalary*0.10;
	}

	else if(yfsalary>2000&&yfsalary<5000)   //超过2000元到5000元的部分
	{	
		gr=yfsalary*0.15;
	}

	else if(yfsalary>5000&&yfsalary<20000)  //超过5000元到20000元的部分
	{
		gr=yfsalary*0.20;
	}

	else if(yfsalary>20000&&yfsalary<40000)  //超过20000元到40000元的部分
	{
	     gr=yfsalary*0.25;
	}

	else if(yfsalary>40000&&yfsalary<60000)  //超过40000元到60000元的部分
	{
		gr=yfsalary*0.30;
	} 

	else if(yfsalary>60000&&yfsalary<80000)  //超过60000元到80000元的部分
	{
		gr=yfsalary*0.35;
	}
	
	else if(yfsalary>80000&&yfsalary<100000)  //超过80000元到100000元的部分
	{
		gr=yfsalary*0.40;
	}

    else if(yfsalary>100000)    //超过100000元的部分
	{
		gr=yfsalary*0.45;
	}

return gr;         //返回个人所得税gr的值
}


/*************************************************************************************************
Function:    main()函数       
Description: 函数作用:主函数实现了系统的主界面，用户可在此界面输入查询、浏览、删除等命令。
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
    int t=60;     //记录结构体数组zggz1的下标
	gz *head;        //定义一个head 头指针
	zggz1[0].prev=head;   //第一个节点的前驱指针指向 head


	for(i=0;i<59;i++)
	{ 
		zggz1[i].next=&zggz1[i+1];
        zggz1[i+1].prev=&zggz1[i];
	}

    zggz1[59].next=NULL;


    n=read(zggz1,t);
    printf("职工人数为： ");
	printf("%d\n",n);
	 
	
    int cm;  //记录命令数字的值
	    printf("       ###  欢迎使用广西民族大学软件与信息安全学院职工工资管理系统  ###\n");
	    printf("\n");
	
	
	while(cm)
	{   
		printf("       请选择（1 — 7）：\n");
		printf("       ================================================================\n");
        printf("       |        1.查询职工工资记录                                    |\n");
		printf("       |        2.修改职工工资记录                                    |\n");
        printf("       |        3.添加职工工资记录                                    |\n");
		printf("       |        4.删除职工工资记录                                    |\n");
		printf("       |        5.保存数据到文件                                      |\n");
		printf("       |        6.浏览职工记录                                        |\n");
		printf("       |        7.退出系统                                            |\n");
		printf("       ================================================================\n");
		printf("\n");
		printf("      你的选择是：\n");

		scanf("%d",&cm);

	    switch(cm)         //使用switch语句实现多分支选择，即执行所输入不同数字命令
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
				 printf("操作结束，立即退出：\n ");
				 return 0;
			  }

           default:
			  {
				  printf("用户您输入命令错误（输入了1至7以外的数字），如需退出请输入7\n");
			  }
		}

	}

return 0;
}