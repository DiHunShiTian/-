#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include<conio.h>

typedef struct words
{
    char words[20];
    struct words *next;
} words;

void readfile(char *route,words *head)//��ȡ����
{
    char ch;
    int i=0;
    words* xia1=(words*)malloc(sizeof(words));
    words* xia2;
    head->next=xia1;
    FILE *wz=fopen(route,"rt");
    if(wz==NULL)
    {
        printf("���¶�ȡʧ�ܣ�");
        return 0;
    }
    else
    {
        printf("���¶�ȡ�ɹ����������ԭ����(������ܻ�������룬��ʵ���ļ�����Ϊ׼)��\n");
    }
    while((ch=fgetc(wz))!=EOF)//ÿһ������Ϊһ������
    {
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))//����ĸ������ʱ������һ������
        {
            xia1->words[i++]=ch;
        }
        else//����������������������ĸ��������
        {
            xia2=(words*)malloc(sizeof(words));
            memset(xia2->words,0,sizeof(xia2->words));//��ֹĩβ���
            xia2->words[0]=ch;
            xia1->next=xia2;
            xia1=(words*)malloc(sizeof(words));
            xia2->next=xia1;
            memset(xia1->words,0,sizeof(xia1->words));//��ֹĩβ���
            i=0;
        }
    }
    xia1->next=NULL;//ĩβ�ÿ�
    printwz(head->next);
    putchar('\n');
    return 0;
}

void writefile(char *route,words *head,char *qian,char *hou)//д������
{
    int k=0;
    char ch;
    words *xia=head->next;//ͷ���Ϊ��
    while(xia!=NULL)
    {
        if(strcmp(xia->words,qian)==0)//������ĸ�ȶ�
        {
            strcpy(xia->words,hou);
            k=1;//������Ҫ�޸ĵĵ���
        }
        xia=xia->next;
    }
    if(k==0)
    {
        printf("δ�ҵ��õ���!\n");
        return 0;
    }
    xia=head->next;
    FILE *wz=fopen(route,"wt");//����д�����
    if(wz==NULL)
    {
        printf("�޸�����ʱʧ�ܣ�");
        return 0;
    }
    printf("�޸ĺ������(������ܻ�������룬��ʵ���ļ�����Ϊ׼):\n");
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

void printwz(words *head) //�������
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
    char before[20]= {0}; //��Ҫ�޸�ǰ�ĵ���
    char after[20]= {0}; //��Ҫ�޸ĺ�ĵ���
    char route[100]="D:\\english.txt";
    int i=0;
    printf("�ļ�·����Ĭ�ϻ���ָ��(0��Ĭ�ϣ�1��ָ��)\n");
    scanf("%d",&i);
    putchar('\n');
    if(i==1)
    {
        printf("����������·��\n");
        memset(route,0,sizeof(route));
        getchar();//��ȡ���з�
        gets(route);
    }
    readfile(route,&head);
again:
    printf("��������Ҫ�޸ĵĵ���(���ִ�Сд���س���������)��\n");
    getchar();//��ȡ���з�
    gets(before);
    printf("�������޸ĺ�ĵ���(�س���������)��\n");
    gets(after);
    writefile(route,&head,before,after);
    printf("\n�Ƿ���Ҫ�ٴ��޸�?(0������Ҫ��1����Ҫ)\n");
    scanf("%d",&i);
    if(i==1)
        goto again;//ѭ���޸ĵ���
    else
        printf("��л����ʹ��!");
    printf("��������˳�...\n");
    getch();//��������
    return 0;
}
