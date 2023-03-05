#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include<conio.h>

typedef struct words
{
    char words[20];
    struct words *next;
} words;

void readfile(char *route,words *head)//读取文章
{
    char ch;
    int i=0;
    words* xia1=(words*)malloc(sizeof(words));
    words* xia2;
    head->next=xia1;
    FILE *wz=fopen(route,"rt");
    if(wz==NULL)
    {
        printf("文章读取失败！");
        return 0;
    }
    else
    {
        printf("文章读取成功，下面输出原文章(输出可能会产生乱码，以实际文件内容为准)：\n");
    }
    while((ch=fgetc(wz))!=EOF)//每一个单词为一个链表
    {
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))//非字母或数字时进入下一段链表
        {
            xia1->words[i++]=ch;
        }
        else//创建符号内容链表，并与字母链表相连
        {
            xia2=(words*)malloc(sizeof(words));
            memset(xia2->words,0,sizeof(xia2->words));//防止末尾多出
            xia2->words[0]=ch;
            xia1->next=xia2;
            xia1=(words*)malloc(sizeof(words));
            xia2->next=xia1;
            memset(xia1->words,0,sizeof(xia1->words));//防止末尾多出
            i=0;
        }
    }
    xia1->next=NULL;//末尾置空
    printwz(head->next);
    putchar('\n');
    return 0;
}

void writefile(char *route,words *head,char *qian,char *hou)//写入文章
{
    int k=0;
    char ch;
    words *xia=head->next;//头结点为空
    while(xia!=NULL)
    {
        if(strcmp(xia->words,qian)==0)//进行字母比对
        {
            strcpy(xia->words,hou);
            k=1;//存在需要修改的单词
        }
        xia=xia->next;
    }
    if(k==0)
    {
        printf("未找到该单词!\n");
        return 0;
    }
    xia=head->next;
    FILE *wz=fopen(route,"wt");//进行写入操作
    if(wz==NULL)
    {
        printf("修改文章时失败！");
        return 0;
    }
    printf("修改后的文章(输出可能会产生乱码，以实际文件内容为准):\n");
    printwz(xia);
    while(xia!=NULL)
    {
        int l=strlen(xia->words);
        int i=0;
        char ch;
        while(l--)
        {
            ch=xia->words[i++];
            if((ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
                fputc(ch,wz);
            else if(ch==' '||ch=='\n'||ch==','||ch==';'||ch=='.')
            {
                fputc(ch,wz);
                break;
            }

            else
                continue;
        }
        xia=xia->next;
    }
    fclose(wz);
    return 0;
}

void printwz(words *head) //输出文章
{
    while(head!=NULL)
    {
        int l=strlen(head->words);
        for(int i=0; i<l; i++)
        {
            char ch=head->words[i];
            if((ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'||(ch>='0'&&ch<='9')))
                printf("%c",ch);
            else if(ch==' '||ch=='\n'||ch==','||ch==';'||ch=='.')
            {
                printf("%c",ch);
                break;
            }
            else
                continue;
        }
        head=head->next;
    }
    putchar('\n');
    return 0;
}

int main(void)
{
    words head;
    char before[20]= {0}; //需要修改前的单词
    char after[20]= {0}; //需要修改后的单词
    char route[100]="D:\\english.txt";
    int i=0;
    printf("文件路径是默认还是指定(0是默认，1是指定)\n");
    scanf("%d",&i);
    putchar('\n');
    if(i==1)
    {
        printf("请输入完整路径\n");
        memset(route,0,sizeof(route));
        getchar();//读取换行符
        gets(route);
    }
    readfile(route,&head);
again:
    printf("请输入需要修改的单词(区分大小写，回车结束输入)：\n");
    getchar();//读取换行符
    gets(before);
    printf("请输入修改后的单词(回车结束输入)：\n");
    gets(after);
    writefile(route,&head,before,after);
    printf("\n是否需要再次修改?(0：不需要，1：需要)\n");
    scanf("%d",&i);
    if(i==1)
        goto again;//循环修改单词
    else
        printf("感谢您的使用!");
    printf("按任意键退出...\n");
    getch();//暂留窗口
    return 0;
}
