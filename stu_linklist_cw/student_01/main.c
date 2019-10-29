#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME "students.txt"


typedef struct LNode
{
    int mID;
    char mName[20];
    int mAge;
    double mChineseScore;
    double mMathScore;
    struct LNode *next;

}LNode,*LinkList;
LinkList L = NULL;


void displayMenu();
void displayStu();
void refreshStu();
void saveStu();
void insertStu();
void findID();
void findChinese();
void findMath();
void findGrade();
void findStu();
void deleteStuByID();
void deleteStuByName();
void deleteStu();
void changeStu();
void swaps(LNode *temp,LNode *p1);
void swap(LNode* p1,LNode * p2);
void sortStu();


int main()
{

    refreshStu();
    while(1)
        displayMenu();
    return 0;
}



void displayMenu()
{
    int num;
    printf("\n");
    printf("****************************************************************************\n");
    printf(" **************** student information management system *************** \n");
    printf("Note:\n");
    printf("     --------------------------         ----------------------------   \n");
    printf("     *************************************************************** \n");
    printf("     * 0.Help                     ** 1.Refresh Student Information * \n" );
    printf("     * 2.Query Student Information** 3.Change Student Information  * \n");
    printf("     * 4.Add Student Information  ** 5.Delet Student Information   * \n");
    printf("     * 6.Show                     ** 7.Save                        * \n");
    printf("     * 8.Sort                     ** 9.Exit                        * \n");
    printf("     ***************************************************************\n");
    printf("     --------------------------         ----------------------------   \n");
    printf("Please enter your choice:\n");

    scanf("%d",&num);
    getchar();
    switch (num) {
    case 0:
        printf("           -----------------------------------------------\n");
        printf("           there are students information management system!\n");
        printf("           -----------------------------------------------\n");
        break;
    case 1:refreshStu();
        break;
    case 2:findStu();
        break;
    case 3:changeStu();
        break;
    case 4:insertStu();
        break;
    case 5:deleteStu();
        break;
    case 6:displayStu();
        break;
    case 7:saveStu();
        break;
    case 8:sortStu();
        break;
    case 9:exit(0);
        break;
    default:
        printf("Please enter right choice:\n");
    }
}

void displayStu()
{
    printf("\n student management system \n");
    printf("|   | ID | Name | Age | ChineseScore | MathScore\n");
    printf(" ----------------------------------------\n");
    LinkList p=L;
    int n=1;
    if(L==NULL) printf("No such message\n");
    else
    while(p)
    {
    printf("| %d | %d |",n,p->mID);
    printf(" %s | %d | %lf | %lf |\n",p->mName,p->mAge,p->mChineseScore,p->mMathScore);
    p=p->next;
    n++;
    }
    printf(" ----------------------------------------\n");
    return ;
}

void refreshStu()
{
    FILE *fp;
    LNode stu,*p;
    char chioce='y';
    static bool refreshflag=0;

    if(refreshflag!=0)
    {
        printf("Unsaved data will be lost!\n");
        printf("You are sure that re-read the data from file? (y/n)\n");
        scanf("%s",&chioce);
        getchar();
        if(chioce!='y')
            return;
    }
    refreshflag=1;
    if((fp=fopen(FILENAME,"rb"))==NULL)
    {
        printf("open failed!\n");
        return;
    }
    fseek(fp, 0, SEEK_SET);
    L=NULL;
    while (fread(&stu,sizeof(LNode),1,fp))
    {
       p=(LNode*)malloc(sizeof(LNode));
       swaps(p,&stu);
       p->next=L;
       L=p;
    };
    fclose(fp);
}

void saveStu()
{
    FILE *fp;
    LNode *p=L;
    int n=0;
    if((fp=fopen(FILENAME,"wb"))==NULL)
    {
        printf("open failed!\n");
        return;
    }
    while(p)
    {
        fwrite(p,sizeof(LNode),1,fp);
        p=p->next;
        n++;
    }
    printf("%d information have be writed",n);
    fclose(fp);

}

void insertStu()
{
    FILE *fp;
    LNode *stu1,*p;
    int i=0;
    char choice='y';
    do
    {
        i++;
        stu1=(LNode*)malloc(sizeof(LNode));
        if(stu1==NULL)
        {
            printf("malloc failed!\n");
            return;
        }
        printf("\n\tplease enter %d student information\n",i);
        //bound('_',40);
        printf("ID:  ");
        scanf("%d",&stu1->mID);
        getchar();
        p=L;
        int flag1=1;
        while (p) {
            while(p->mID==stu1->mID)
            {
                printf("Error! the id already exist!\n");
                printf("ID:  ");
                scanf("%d",&stu1->mID);
                getchar();
                flag1=0;
            }
            if(!flag1)
                break;
            p=p->next;
        }
        printf("Name:  ");
        scanf("%s",&stu1->mName);
        getchar();
        printf("Age:  ");
        scanf("%d",&stu1->mAge);
        getchar();
        while(stu1->mAge<0||stu1->mAge>100)
        {
            printf("please enter the Age about 0~150\n");
            scanf("%d",&stu1->mAge);
            getchar();
        }
        printf("ChineseScore:  ");
        scanf("%lf",&stu1->mChineseScore);
        getchar();
        while(stu1->mChineseScore<0||stu1->mChineseScore>100)
        {
            printf("please enter the Score about 0~100\n");
            scanf("%lf",&stu1->mChineseScore);
            getchar();
        }
        printf("MathScore:  ");
        scanf("%lf",&stu1->mMathScore);
        getchar();
        while(stu1->mMathScore<0||stu1->mMathScore>100)
        {
            printf("please enter the Score about 0~100\n");
            scanf("%lf",&stu1->mMathScore);
            getchar();
        }
        stu1->next=NULL;
        //fwrite(stu1,sizeof(LNode),1,fp);
        if(L!=NULL)
        {
            stu1->next = L;
            L=stu1;
        }
        if(L==NULL)
        {
            L=stu1;
            L->next=NULL;
        }
        printf("\n");
        printf("\nContinue?(y/n)");
        fflush(stdin);//清除缓存区
        choice=getchar();
        getchar();
        if(choice!='y')
        {
            //fclose(fp);
            return;
            }
    }while(1);
fclose(fp);

}

void findID()
{
    int id;
    printf("enter student id:\n");
    scanf("%d",&id);
    getchar();
    LNode *p=L;
    while(p!= NULL)
    {
        if(p->mID==id)
        {
            printf("ID: %d\n",p->mID);
            printf("Name: %s\n",p->mName);
            printf("Age: %d\n",p->mAge);
            printf("Chinese: %lf\n",p->mChineseScore);
            printf("Math: %lf\n",p->mMathScore);
            return;
        }
        p=p->next;
    }
    printf("not find!");

}

void findChinese()
{
    LNode *p=L;
    int grade,n=0;
    printf("please enter the Chinese score");
    scanf("%d",&grade);
    getchar();
    while(p!= NULL)
    {
        if(p->mChineseScore==grade)
        {
            n++;
            printf("The %d students information",n);
            printf("ID: %d\n",p->mID);
            printf("Name: %s\n",p->mName);
            printf("Age: %d\n",p->mAge);
            printf("Chinese: %lf\n",p->mChineseScore);
            printf("Math: %lf\n",p->mMathScore);

        }
        p=p->next;
    }
    if(n==0)
    {
        printf("not found!");
    }
    return;
}

void findMath()
{
    LNode *p=L;
    int grade,n=0;
    printf("please enter the Math score");
    scanf("%d",&grade);
    getchar();
    while(p!= NULL)
    {
        if(p->mMathScore==grade)
        {
            n++;
            printf("The %d students information\n",n);
            printf("ID: %d\n",p->mID);
            printf("Name: %s\n",p->mName);
            printf("Age: %d\n",p->mAge);
            printf("Chinese: %lf\n",p->mChineseScore);
            printf("Math: %lf\n",p->mMathScore);

        }
        p=p->next;
    }
    if(n==0)
    {
        printf("not found!");
    }
    return;
}

void findGrade()
{
    int id;
    printf("Select the subject:\n");
    printf("1.Chinese\n");
    printf("2.Math\n");
    scanf("%d",&id);
    getchar();
    switch (id) {
    case 1:findChinese();
        break;
    case 2:findMath();
        break;
    default:
        break;
    }


}

void findStu()
{
    int choice;
    printf("1.By ID\n");
    printf("2.By Grade\n");
    printf("3.Return\n");
    printf("please enter a number of method:\n");
    choice=getchar();
    getchar();
    while (choice>'3'||choice<'1')
    {
        printf("please enter a right number!\n");//为什么会出现两次？已解决
        getchar();
        choice=getchar();

    }
    switch (choice) {
    case '1':findID();
        break;
    case '2':findGrade();
        break;
    case '3':return;
    default:
        break;
    }

}
void deleteStuByID()
{
    int id;
    LNode *p=L;
    LNode *p2;
    printf("please enter student id:\n");
    scanf("%d",&id);
    getchar();
    if(L==NULL)
    {
        printf("Empty!");
        return;

    }
    if(L->mID==id)
    {
        L=L->next;
        free(p);
        return;

    }
    while(p->next!=NULL)
    {
        p2=p->next;
        if(p2->mID==id)
        {
            p->next=p2->next;
            p2->next=NULL;
            free(p2);
            return;
        }
        p=p->next;
    }
    printf("not found!");
    return;
}
void deleteStuByName()
{
    char name[20];
    printf("please enter student's name:\n");
    scanf("%s",name);
    getchar();
    if(L==NULL)
        return;
    if(L->mName==name)
                L=NULL;
    LNode *p=L;
    LNode *p2=L;
    while(p!=NULL)
    {
        if(strcmp(p->mName,name)==0)
        {
            p2->next=p->next;
            p->next=NULL;
            free(p);
            printf("delete succeed!");
            return;//可能出现重名
        }
        p2=p;
        p=p->next;
    }
    return;
}
void deleteStu()
{
    int choice;
    deleteStuStart:
    printf("1.By ID\n");
    printf("2.By Name\n");
    printf("3.Return\n");
    printf("please enter a number of method:\n");
    scanf("%d",&choice);
    getchar();
    switch (choice) {
    case 1:deleteStuByID();
        break;
    case 2:deleteStuByName();
        break;
    case 3:return;
    default:
        printf("please enter right choice!\n");
        goto deleteStuStart;
    }
}

void changeStu()
{
    int id;
    printf("please enter the student's id:\n");
    scanf("%d",&id);
    getchar();
    //if(L==NULL)
    //    return;
    LNode *p=L;
    while(p!=NULL)
    {
        if(p->mID==id)
        {
            printf("please enter what you want to modify\n ");
            printf("ID:  ");
            scanf("%d",&p->mID);
            getchar();
            printf("Name:  ");
            scanf("%s",&p->mName);
            getchar();
            printf("Age:  ");
            scanf("%d",&p->mAge);
            getchar();
            printf("ChineseScore:  ");
            scanf("%lf",&p->mChineseScore);
            getchar();
            printf("mMathScore:  ");
            scanf("%lf",&p->mMathScore);
            getchar();
            return;
        }
        p=p->next;
    }
    printf("not found!\n");
    return;
}
void swaps(LNode *temp,LNode *p1)
{
    temp->mID=p1->mID;
    temp->mAge=p1->mAge;
    strcpy(temp->mName,p1->mName);
    temp->mChineseScore=p1->mChineseScore;
    temp->mMathScore=p1->mMathScore;
    return;
}
void swap(LNode* p1,LNode * p2)
{
    LNode temp;
    swaps(&temp,p1);
    swaps(p1,p2);
    swaps(p2,&temp);
    return;

}
void sortStu()
{
    if(L==NULL)
    {
        printf("Empty!");
        return;
    }
    LNode *p=L;
    while(p)
    {
        LNode *p2=p->next;
        while(p2)
        {
            if(p->mID>p2->mID)
            {
               printf("re-sorting...");
               swap(p,p2);
            }
            p2=p2->next;
        }

        p=p->next;
    }

}
