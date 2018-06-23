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

*******************************************************************************************************************************/
#include <iostream>
#include <fstream>
#include "string.h"
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
using namespace std;
int i; 
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
};

int read(struct gz *zggz,int &t)    //主函数执行时要调用和必须调用的第一个函数 :read()函数
{ 	                              //形参struct gz *zggz是指向结构体的指针，形参t是main()中接受数据的结构体数组的下标t的引用
	int n=0;             //n用来记录职工人数，一开始初始化为0

	ifstream in("gz.dat",ios::in|ios::binary);
	if(!in)
	{ cout<<"Can not open input file.\n";
	  exit(1);
	}

    for(int i=0;!in.eof();i++)                 //用eof()函数判断文件指针是否到文件尾，即是否读完文件中的数据
	{  
	    in.read((char*)&zggz[i],sizeof(zggz[i]));
		n++;                                         //记录职工人数   		                   
	}
	
	in.close();
	cout<<n-1<<endl;
	cout<<"成功读取文件中的数据."<<endl;
return n-1;                     //返回职工人数n
}

int write(struct gz *zggz,int &n)   //保存职工工资数据函数 write()
{                                   // 形参struct gz *zggz是指向结构体的指针，形参n 是main函数中n的引用
	FILE *fp;                 //定义文件指针
    struct gz *p;             //定义结构体指针
	p=zggz;
	                               
    if(n>0) 
	{   
		if((fp=fopen("gz.dat","wb+"))==NULL)   
		{
			cout<<"Can not open file strike any key exit!";
			getch();
			exit(1);
		}

		fwrite(p,sizeof(struct gz),n,fp);     //fwrite()是“写数据块函数”   
       
	}
	else      
	{ 
		cout<<"因为N为0或小于0，所以出错了。 "<<endl;  
		return 1;
	}
	cout<<"成功将结构体数组的数据存入文件gz.dat中."<<endl;
return 0;
}

int find(struct gz *zggz,int &n1)         //find()函数， 根据工号查询相应职工的工资记录
{                                        // 形参struct gz *zggz是指向结构体的指针，形参n1 是main函数中n的引用
	
	char gonghao[10];
    int k;

	cout<<"请输入工号： "<<endl;
	cin>>gonghao; 

    for(i=0;i<n1;i++)
	{ 
	     k=strcmp(zggz[i].te_number,gonghao);  //k=0,即输入工号number=zggz[i].te_number
	     if(k==0)
		 {
            cout<<"工号"<<setw(7)<<"姓名"<<setw(9)<<"岗位工资"<<setw(9)<<"薪级工资"<<setw(9)<<"职务津贴"<<setw(9);   //使用setw()函数，设定下次输出宽度，让输出的数据右对齐
	        cout<<"绩效工资"<<setw(9)<<"应发工资"<<setw(12)<<"个人所得税"<<setw(9)<<"实发工资"<<endl;
			cout<<zggz[i].te_number<<setw(7)<<zggz[i].name<<setw(9);
			cout<<zggz[i].salary<<setw(9)<<zggz[i].xj_salary<<setw(9)<<zggz[i].jt_salary<<setw(9);
			cout<<zggz[i].jx_salary<<setw(9)<<zggz[i].yf_salary<<setw(12);
			cout<<zggz[i].gr<<setw(9)<<zggz[i].sf_salary<<endl;     
		    cout<<"停止查找，将回到主菜单。"<<endl;
		 }
	}

  return 0;
}

int list(struct gz *zggz,int &n)     //list() 显示所用职工的记录
{                                    //形参struct gz *zggz是指向结构体的指针，形参n 是main函数中n的引用
	for(i=0;i<n;i++)      //在结构体数组中从zggz[0] 开始，到n+1条记录结束
	{       
		    cout<<"工号"<<setw(7)<<"姓名"<<setw(9)<<"岗位工资"<<setw(9)<<"薪级工资"<<setw(9)<<"职务津贴"<<setw(9);   //使用setw()函数，设定下次输出宽度，让输出的数据右对齐
	        cout<<"绩效工资"<<setw(9)<<"应发工资"<<setw(12)<<"个人所得税"<<setw(9)<<"实发工资"<<endl;
			cout<<zggz[i].te_number<<setw(7)<<zggz[i].name<<setw(9);
			cout<<zggz[i].salary<<setw(9)<<zggz[i].xj_salary<<setw(9)<<zggz[i].jt_salary<<setw(9);
			cout<<zggz[i].jx_salary<<setw(9)<<zggz[i].yf_salary<<setw(12);
			cout<<zggz[i].gr<<setw(9)<<zggz[i].sf_salary<<endl; 
			
		  /*cout<<"工号"<<"  "<<"姓名"<<"     "<<"岗位工资"<<" "<<"薪级工资"<<" "<<"职务津贴"<<" ";          //使用在双引号中加空格的方式间隔数据，再输出
	        cout<<"绩效工资"<<" "<<"应发工资"<<" "<<"个人所得税"<<" "<<"实发工资"<<endl;
			cout<<zggz[i].te_number<<"  "<<zggz[i].name<<"    ";
			cout<<zggz[i].salary<<"     "<<zggz[i].xj_salary<<"     "<<zggz[i].jt_salary<<"       ";
			cout<<zggz[i].jx_salary<<"       "<<zggz[i].yf_salary<<"  ";
			cout<<zggz[i].gr<<"     "<<zggz[i].sf_salary<<endl;                                  */
	}

    cout<<"当前职工工资管理系统中有 "<<n<<"位职工的数据. "<<endl;
return 0;
}

void modify(struct gz *zggz,int &n1)   //modify()指定工号，修改该职工的工资记录。
{                                     // n1是职工人数n的引用
	int k;                            //k用于记录strcmp函数的值，k=0即找到工号相同
	gz xigz;                         //定义结构体变量xigz

	char gonghao[10];
	cout<<"请输入工号： "<<endl;
	cin>>gonghao;
	
    for(i=0;i<n1;i++)
	{ 
	     k=strcmp(zggz[i].te_number,gonghao);  //k=0,即输入工号number=zggz[i].te_number
	     if(k==0)
		 {
	     cout<<"重新录入基本信息:"<<endl;
		 cout<<"工号"<<" ";
		 cin>>xigz.te_number;
		 cout<<"姓名"<<" ";
		 cin>>xigz.name;
		 cout<<"岗位工资"<<" ";
		 cin>>xigz.salary;
		 cout<<"薪级工资"<<" ";
		 cin>>xigz.xj_salary;
		 cout<<"职务津贴"<<" ";
		 cin>>xigz.jt_salary;
		 cout<<"绩效工资"<<"  ";
		 cin>>xigz.jx_salary;

		 xigz.yf_salary=(xigz.salary+xigz.xj_salary+xigz.jt_salary+xigz.jx_salary);   //计算应发工资
		                                               	                                        
         xigz.gr=grsds(xigz.yf_salary);               //计算个人所得税
		
		 xigz.sf_salary=(xigz.yf_salary-xigz.gr);   //计算实发工资
		
		 zggz[i]=xigz;              //将结构体变量xigz的值给zggz[i],完成修改

		 cout<<"修改该职工的工资信息完成. "<<endl;
		}
	}

   cout<<"修改该职工的工资记录已完成。 "<<endl; 
}

int del(struct gz *zggz,int &t,int &n)      // del()函数作用：删除指定工号职工的记录
{                                    //形参struct gz *zggz是指向结构体的指针，形参t用来记录main()中接受数据的结构体数组的下标的引用,n主函数中定义的职工人数n 的引用
	int mubi, k;                
    char number[10];        //number用来接受所输入工号

	cout<<"请输入工号："<<endl;
	cin>>number;

	int flag=0;

	for(i=0;i<t;i++)
	{  
	
	   k=strcmp(zggz[i].te_number,number);  //k=0,即输入工号number=zggz[i].te_number
	   if(k==0)
	   {
		  flag=1;
		  mubi=i;
		  cout<<"在数组中查到，要删除的数据位于，是zggz["<<i<<"] "<<endl;
		  break; 
	   }

	   if(n==i) 
	   {      
			   if(!flag)
			   {
			   cout<<"数组中的n+1记录没有,错误。 "<<endl;  
			   return 1;
			   }
	   }
	 
	}

	cout<<"确认删除否？输入11确认，输入22放弃删除。"<<endl;

	int s;             //s用来记录输入整数命令（11或22）
	cin>>s;

	if(s==11)       //删除该记录
	{  
		cout<<"将删除该记录··· "<<endl; 
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
		cout<<"已放弃删除······"<<endl;
		return 1;
	}

     cout<<"停止查找··· "<<endl;
return 0;
}

int add(struct gz *zggz,int &n1)     //函数作用:添加工资记录到结构体数组zggz末尾
{                                    //形参struct gz *zggz是指向结构体的指针，n1是职工人数n的引用
    cout<<"依次输入职工基本信息:"<<endl;
	cout<<"工号"<<" ";
	cin>>zggz[n1].te_number;
	cout<<"姓名"<<" ";
	cin>>zggz[n1].name;
	cout<<"岗位工资"<<" ";
	cin>>zggz[n1].salary;
	cout<<"薪级工资"<<" ";
    cin>>zggz[n1].xj_salary;
    cout<<"职务津贴"<<" ";
	cin>>zggz[n1].jt_salary;
	cout<<"绩效工资"<<"  ";
	cin>>zggz[n1].jx_salary;

    zggz[n1].yf_salary=(zggz[n1].salary+zggz[n1].xj_salary+zggz[n1].jt_salary+zggz[n1].jx_salary);  //计算应发工资
                                      
    zggz[n1].gr=grsds(zggz[n1].yf_salary);               //计算个人所得税
	
	zggz[n1].sf_salary=(zggz[n1].yf_salary-zggz[n1].gr);   //计算实发工资

    cout<<"此职工的全部信息为 :"<<endl;
	cout<<"工号"<<setw(7)<<"姓名"<<setw(9)<<"岗位工资"<<setw(9)<<"薪级工资"<<setw(9)<<"职务津贴"<<setw(9);   //使用setw()函数，设定下次输出宽度，让输出的数据右对齐
	cout<<"绩效工资"<<setw(9)<<"应发工资"<<setw(12)<<"个人所得税"<<setw(9)<<"实发工资"<<endl;
    cout<<zggz[n1].te_number<<setw(7)<<zggz[n1].name<<setw(9);
	cout<<zggz[n1].salary<<setw(9)<<zggz[n1].xj_salary<<setw(9)<<zggz[n1].jt_salary<<setw(9);
	cout<<zggz[n1].jx_salary<<setw(9)<<zggz[n1].yf_salary<<setw(12);
	cout<<zggz[n1].gr<<setw(9)<<zggz[n1].sf_salary<<endl;    
	n1=n1+1;
	cout<<"职工人数增加1后为： "<<n1<<endl;
return 0;
}

int grsds(float yfsalary)   //grsds()函数作用：计算个人所得税，按照个人所得税税率表来计算
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

int main()       //main()函数功能: 主函数实现了系统的主界面，用户可在此界面输入查询、浏览、删除等命令。
{    
    gz zggz1[50];
    int t=50;     //记录结构体数组zggz1的下标

    n=read(zggz1,t);
    cout<<"职工人数为： "<<n<<endl;
	 
	
    int cm;                 //记录命令数字的值
	cout<<"                     欢迎使用职工工资管理系统！"<<endl;
	
	
	while(cm)
	{ 
		cout<<"                           功能菜单:"<<endl;
		cout<<"                     1.查询 2.修改 3.添加 "<<endl;
		cout<<"                     4.删除 5.保存 6.浏览 "<<endl;
		cout<<"                            7.退出"<<endl;
	    cout<<"请输入命令："<<endl;
        cin>>cm;

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
				 cout<<"操作结束，立即退出： "<<endl;
				 return 0;
			  }

           default:
			  {
				  cout<<"用户您输入命令错误（输入了1至7以外的数字），如需退出请输入7"<<endl;
			  }
		}

	}

return 0;
}