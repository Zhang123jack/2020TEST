#include<stdio.h> 
#include<stdlib.h>
#include<conio.h> 
#include<string.h> 
struct bank
 { 
 char name[20];
 char password[7];
 int account;
 double money;
    }kehu;
struct bank t;
FILE *fp;
int find,dfind;
void inputpassword(char mima[]);
void regist();
void chaxun();
void cunkuan();
void qukuan();
void zhuanzhang();
void xiugai();
int zhuxiao(int zx);
void quit();
void tuichu();
void service();
void login();

//主函数 
int main()
{
	int i,j,m;
	char xz;
	for(i=1;i<=100;i++)
	{
		printf("\n\n\n\n\n\t\t\t\t\t欢迎使用金三银行ATM系统\n");//输出1
		printf("\n\n\n\t\t\t\t\t正在进入，请稍等\n");//输出2
		printf("\t\t\t\t\t");
		for(j=0;j<=10;j++)
		{
			for(m=0;m<=5000000;m++);//延迟
			printf(".");//输出.
		}
		printf("\t\t%d%%",i);//输出百分比
		for(m=0;m<=5000000;m++);//延迟
		system("cls");//清屏
	}
 while (1)
 {
  printf("\n\n\n\t\t\t\t\t欢迎使用金三银行ATM系统");
  printf("\n\n\n\t\t\t\t\t【A】：用户注册");
  printf("\n\n\n\t\t\t\t\t【B】：用户登录");
  printf("\n\n\n\t\t\t\t\t【C】：退出登录");
  printf("\n\n\n\t\t\t\t\t请输入选择：");
   fflush(stdin);
   scanf("%c",&xz);
   fflush(stdin);
   if(xz=='A'||xz=='a')
   {
     system("cls");
	 regist();
	 for(m=0;m<=999999999;m++);
	 system("cls");
   }
   else  if(xz=='B'||xz=='b')
   {
     system("cls");
	 login();
	 for(m=0;m<=999999999;m++);
	 system("cls");
   }
   else  if(xz=='C'||xz=='c')
   {
    system("cls");
	quit();
	for(m=0;m<=999999999;m++);
	system("cls");
   }
   else 
        {   
    printf("\n\t\t\t\t\t输入有误，请重新输入：");
           }
   system("cls");
      printf("\n\t\t\t\t\t请摁任意键继续......");
   getch();
     system("cls");
 }

return 0;
}
 //密码函数
void inputpassword(char mima[])
{ 
   int i=0;
   char ch; 
while(1)
{
    ch=getch();
    if(ch!='\r')
     {
       if(ch!='\b')
       {
          mima[i]=ch;
		  i++;
      printf("*");
    }
    else 
    {
     if(i>0)
     {
     i--;
     printf("\b \b"); 
     }
    }
     }
     else break;
  }
mima[i]='\0';
printf("\n");
}

//注册函数
void regist()
{ 
 char password1[7];
fp=fopen("atm.txt","ab+");
if(fp==NULL)
{
	printf("打开文件失败！");
	return ;
}
printf("\n\t\t\t\t\t请输入名字："); 
 gets(kehu.name);
 fflush(stdin);
 printf("\n\t\t\t\t\t用户名为：%s",kehu.name);
    while (1)
   {
		  while(1)
		  {
				  printf("\n\t\t\t\t\t请输入密码：");
					fflush(stdin);
					inputpassword(kehu.password);
				  int length=strlen(kehu.password);
				  if(length==6)break;
				  else printf("\n\t\t\t\t\t用户密码长度必须为六位。");    
			} 
		  printf("\n\t\t\t\t\t请再次输入密码：");
		  fflush(stdin);
		  inputpassword(password1);
		  
		  if(strcmp(kehu.password,password1)==0)break;
		  else printf("\n\t\t\t\t\t两次密码不一致，请重新输入："); 
   }
   kehu.money=0;
   rewind(fp);
   if(fread(&t,sizeof(t),1,fp)==1)
   {
		fseek(fp,-sizeof(kehu),2);
		fread(&t,sizeof(t),1,fp);
		kehu.account=t.account+1;
   }
   else kehu.account=20170001;
   fseek(fp,0,2);
	fwrite(&kehu,sizeof(struct bank),1,fp);
	fclose(fp);
   printf("\n\t\t\t\t\t注册成功！");
   printf("\n\t\t\t\t\t您的账号为%d",kehu.account);
}

//查询函数
void chaxun()
{
 system("cls");
 printf("\n\n\n\n\n\t\t\t\t\t您现在正在使用的是查询功能");
 printf("\n\t\t\t\t\t您的账户余额为：%.2lf",t.money); 
}

//存款函数
void cunkuan()
{
 system("cls");
 int qian; 
 printf("\n\n\n\n\n\t\t\t\t\t您现在正在使用的是存款服务");
 printf("\n\t\t\t\t\t请输入存款金额:");
 scanf("%d",&qian);
 t.money=t.money+qian;
 fseek(fp,-sizeof(t),1);
 fwrite(&t,sizeof(t),1,fp);
 printf("\n\t\t\t\t\t存款成功！"); 
} 
 
//取款函数 
void qukuan()
{
  system("cls");
 printf("\n\t\t\t\t\t您现在正在使用的是取款服务");
 int qian; 
 printf("\n\t\t\t\t\t请输入取款金额");
 scanf("%d",&qian);
 if(t.money>=qian)
 {
t.money=t.money-qian;
    fseek(fp,-sizeof(t),1);
    fwrite(&t,sizeof(t),1,fp);
  printf("\n\t\t\t\t\t取款成功！");
 } 
 else
 {
  printf("\n\t\t\t\t\t余额不足！");
   
 }
}

//转账函数

void zhuanzhang()
{
 system("cls");
 int zhanghao,qian,f=0;
 int n=ftell(fp);
 struct bank temp;
 printf("\n\n\n\n\n\t\t\t\t\t您正在执行转账服务：");
 printf("\n\n\t\t\t\t\t请输入对方账号:");
 scanf("%d",&zhanghao);
 rewind(fp);
 while(fread(&temp,sizeof(temp),1,fp)==1)
 {
  if(zhanghao==temp.account)
  {
   f=1;
   break;
  }
 }
 if(f==1)
 {
   printf("\n\t\t\t\t\t请输入转账金额：");
   scanf("%d",&qian);
   if(t.money>=qian)
   {
    t.money=t.money-qian;
	temp.money=temp.money+qian;
	   //修改文件数据
	   fseek(fp,-sizeof(t),1);
	   fwrite(&temp,sizeof(t),1,fp);
	   fseek(fp,n-sizeof(t),0);
	   fwrite(&t,sizeof(t),1,fp);
    printf("\n\t\t\t\t\t转账成功！"); 
   } 
 }
 else
 {
  printf("\n\t\t\t\t\t目标账号不存在！");
 }
} 
//修改密码函数 '

void xiugai()
{
 system("cls");
 int i;
 char password1[20],password2[20],password3[20];
 printf("\n\n\t\t\t\t\t您正在执行修改密码服务");
 for(i=1;i<=3;i++)
 { 
  printf("\n\n\t\t\t\t\t请输入旧密码："); 
  inputpassword(password1);
  if(strcmp(password1,t.password)==0)
  {
    
    break;
  }
   else
  {
    printf("\n\n\t\t\t\t\t旧密码输入有误，请重新输入：");
  }
    }
  if(i<3)
  {
   while(1) 
   {
	   while(1)
	   {
			printf("\n\n\t\t\t\t\t请输入新密码：");
			inputpassword(password2);
			int length=strlen(password2);
			 if(length==6)
			 {
			 break;
			 }
			 else printf("\n\t\t\t\t\t用户密码长度必须为六位。");    
	   }
	printf("\n\n\t\t\t\t\t请输入确认新密码：");
    inputpassword(password3);
    if(strcmp(password2,password3)==0)
     {
      strcpy(t.password,password2);
	  fseek(fp,-sizeof(t),1);
	  fwrite(&t,sizeof(t),1,fp);
      printf("\n\n\t\t\t\t\t密码修改成功！");
      break; 
     } 
    else
        {
      printf("\n\n\t\t\t\t\t两次密码输入不一致，请重新输入：");
        }
   }

  }
     else
     {
   printf("\n\n\t\t\t\t\t三次旧密码输入有误，吞卡中......");
     }
}

//注销函数 
int zhuxiao(int zx)
{
 zx=0;
 char sf; 
 system("cls"); 
 printf("\n\n\t\t\t\t\t您正在执行注销服务");
 printf("\n\n\t\t\t\t\t您正要注销的客户账号是：%d",t.account);
 printf("\n\n\t\t\t\t\t您是否要注销此账号？\n");
 printf("\n\n\t\t\t\t\t注销【Y】\t\t取消【N】");
 printf("\n\n\t\t\t\t\t请输入：\t");
    fflush(stdin);
    scanf("%c",&sf);
    if(sf=='Y'||sf=='y')
 {
  printf("\n\t\t\t\t\t正在对账号%d进行注销，即将返回服务器",t.account);
  zx=1;   

 }
 else if(sf=='N'||sf=='n')
 {
  printf("\n\t\t\t\t\t不对账号%d进行注销，即将返回",t.account);
 }
 else printf("\n\t\t\t\t\t只可以输入“Y”或者“N”！");
   return zx;

}
//退出函数
void quit()
{
 system("cls");
 printf("\n\n\n\n\n\n\n\t\t\t\t\t您正在退出ATM服务界面......");
 printf("\n\t\t\t\t\t正在退出，请稍后.......\n\n");
exit(0);
}
//退出服务函数
void tuichu()
{
 system("cls");
 printf("\n\n\n\n\n\n\n\t\t\t\t\t您正在退出ATM服务界面......");
 printf("\n\t\t\t\t\t正在退出，请稍后.......\n\n");
}
//服务页面函数
void service()
{
 char xz;
 while(1)
 {
  system("cls");
  printf("\n\t\t\t\t\t您正在使用服务功能页面：");
  printf("\n\t\t\t\t\t【a】：查询余额");
  printf("\n\t\t\t\t\t【b】：存款");
  printf("\n\t\t\t\t\t【c】：取款");
  printf("\n\t\t\t\t\t【d】：转账");
  printf("\n\t\t\t\t\t【e】：修改密码");
  printf("\n\t\t\t\t\t【f】：注销");
  printf("\n\t\t\t\t\t【g】：退出系统"); 
  printf("\n\t\t\t\t\t请选择服务种类 ： ");
  fflush(stdin);
  scanf("%c",&xz); 
 switch(xz)
 {
  case 'a':
  case 'A':chaxun();break;
  case 'b':
  case 'B':cunkuan();break;
  case 'c':
  case 'C':qukuan();break;
  case 'd':
  case 'D':zhuanzhang();break;
  case 'e':
  case 'E':xiugai();break;
  case 'f':
  case 'F':int zx;zx=zhuxiao(zx);if(zx==1)return;break;
  case 'g':
  case 'G': tuichu();return; 
  default: printf("\n\t\t\t\t\t输入有误，请重新选择："); 
 }
 printf("\n\n\t\t\t\t\t摁任意键继续......");
 getch(); 
 }
 
} 

//登录函数
void login()
{

	fp=fopen("atm.txt","rb+");
	if(fp==NULL)
	{
		printf("\n\t\t\t\t\t打开失败！\n");
	return;
	}
printf("\n\t\t\t\t\t您正在执行登录函数");
int zhanghao,f=0;
char password1[10];

printf("\n\t\t\t\t\t请输入您的账号：");
scanf("%d",&zhanghao);
while(fread(&t,sizeof(t),1,fp)==1)
{
 if(zhanghao==t.account)
	{
	 f=1;
	 break;
    }
}
if(f==1)
{
 int j;
 for(j=1;j<=3;j++) 
 {
      printf("\n\t\t\t\t\t请输入密码:");
      inputpassword(password1);
      if(strcmp(password1,t.password)==0)
          {
          printf("\n\t\t\t\t\t密码正确！登录成功！");
          getch(); 
          service();//服务页面 
			break;
          }
	  else
	  {
		  printf("\n\t\t\t\t\t密码错误，请重新输入：");

	  }
     if(j==3)
   {
     
    printf("\n\t\t\t\t\t今日密码错误次数已达上限，吞卡中......"); 
   getch();
   }
   }
  
}
else printf("\n\t\t\t\t\t账号不存在！"); 
fclose(fp);
}


