
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "sqlite3.h"

#define DBNAME "data.db"
typedef unsigned char unchar;
typedef unsigned char unint;

typedef struct LNode
{
    unchar mID[20];
    unchar mName[20];
    unchar mAge;
    unchar mChineseScore;
    unchar mMathScore;
    struct LNode *next;

}LNode;

typedef struct LSTU
{
    unint mID;
    unchar mName[20];
    unint mAge;
    double mChineseScore;
    double mMathScore;
    struct LNode *next;

}LSTU;

void createStuTable();
void displayMenu();
void choice_menu_Main();
void menu_main();
void menu_select();
void menu_help();
void menu_selectByGrade();
void menu_sortStuByGrade();
void displayStu();
int selectGetTable(const char *sql);
void insertStu_ID(LNode *stu);
void insertStu_Name(LNode *stu);
void insertStu_Age(LNode *stu, LSTU *realStu);
void insertStu_Chinese(LNode *stu, LSTU *realStu);
void insertStu_Math(LNode *stu, LSTU *realStu);
void insertStu_All(LNode *stu, LSTU *realStu);
void insertStu();
void selectByID();
void selectStu();
void selectByGrade();
void selectByChinese();
void selectByMath();
void updateID(LNode *stu);
void updateName(LNode *stu);
void updateAge(LNode *stu);
void updateChinese(LNode *stu);
void updateMath(LNode *stu);
void deleteStuByID();
void deleteStuByName();
void deleteStu();
void updateStu();
void sortStu();
void sortStuByGrade();
void sortStuMethod(const char * method,const char *ascOr );
void sortStuBySum(const char *stuColname,const char * method,const char *ascOr );
static int callback(void *data, int argc, char **argv, char **stuColName);

int main()
{
    createStuTable();
    choice_menu_Main();
    return 0;
}
void createStuTable()
{
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    int ret=sqlite3_open(DBNAME,&db);
    if(ret != SQLITE_OK)
    {
        printf("�����ݿ���� %s",sqlite3_errmsg(db));
        exit(-1);
    }
    //������
    ret = sqlite3_exec(db,"create table if not exists stu(id int(10) PRIMARY Key not NULL,name char(20) NOT NULL,age int NOT NULL,Chinese int,Math int)",0,0,&errMsg);
    if(ret !=   SQLITE_OK)
    {
        sqlite3_close(db);
        printf("�������ݱ����%s\n",errMsg);
        return ;
    }
}
void menu_main()
{
    printf("\n");
    printf("****************************************************\n");
    printf(" ***************** ѧ����Ϣ����ϵͳ  ****************** \n");
    printf("Note:\n");
    printf("     ---------------          ---------------   \n");
    printf("     ******************************************** \n");
    printf("     * 0.����                 **  1.���������Ϣ * \n" );
    printf("     * 2.��ѯѧ����Ϣ         **  3.�޸�ѧ����Ϣ * \n");
    printf("     * 4.���ѧ����Ϣ         **  5.ɾ��ѧ����Ϣ * \n");
    printf("     * 6.��ʾ������Ϣ         **  7.�˳�         * \n");
    printf("     ********************************************\n");
    printf("     ---------------          ---------------   \n");
    printf("��ѡ���Ӧ��ţ�0��7��:\n");
}
void menu_select()
{
    printf("\n");
    printf(" ***************** ��ѯѧ����Ϣ����*******************\n");
    printf("Note:\n");
    printf("     ---------------          ---------------   \n");
    printf("     ******************************************** \n");
    printf("     * 1.ID��ѯ               **  2.�ɼ���ѯ     * \n");
    printf("     * 3.����������           **  4.�˳�         *\n");
    printf("     ********************************************\n");
    printf("     ---------------          ---------------   \n");
    printf("��ѡ���Ӧ��ţ�1-3��:\n");
}
void menu_help()
{
    printf("         ------------------------------\n");
    printf("         ��ӭ����ѧ������ϵͳ�����ݿ�棩\n");
    printf("   ��Ϊ��ɰ沢�����հ棬���ֺ����Կɼ�����ֻ�����\n");
    printf("   -------------------------------------------------\n");
    printf("\n\n\n\n\n�밴���������...\n");
    getchar();
    fflush(stdin);

}
void menu_selectByGrade()
{
    printf("1.��֪���ĳɼ�\n2.��֪��ѧ�ɼ�\n3.����\n");
    printf("���������ѡ��(1-3):\n");
}
void menu_updateStu(LNode *stu)
{
    printf("ѡ���޸�ID��%sѧ������Ϣ :\n"
               "1.ID\n2.����\n3.����\n4.����\n5.��ѧ\n6.����\n",stu->mID);
    printf("��ѡ���޸�����(1-6):\n");
}
void menu_deleteStu()
{
    printf("1.Byѧ��ID:\n2.Byѧ������\n3.����\n");

    printf("��ѡ��1-3��:\n");
}
void menu_sortStu()
{
    printf("1.ID������\n2.�ɼ�������\n3.����\n");
    printf("��ѡ��1-3��:\n");
}
void menu_sortStuByGrade()
{
    printf("1.���ĳɼ�������\n2.��ѧ�ɼ�������\n3.�ܳɼ�������\n4.�ܳɼ�������\n5.����\n");
    printf("��ѡ��(1-5)��\n");
}
void choice_menu_Main()
{
    int choice=8;
    menu_main();
    while (1) {
        scanf("%d",&choice);
        getchar();
        switch (choice) {
            case 0:menu_help();menu_main();
                break;
            case 1:sortStu();menu_main();
                break;
            case 2:selectStu();menu_main();
                break;
            case 3:updateStu();menu_main();
                break;
            case 4:insertStu();menu_main();
                break;
            case 5:deleteStu();menu_main();
                break;
            case 6:displayStu();menu_main();
                break;
            case 7:exit(0);
                break;
            default:
                printf("��ѡ����ȷ��������루0-7����\n");
            }
    }
}
void displayStu()
{
    const char *select_query="select * from stu";
    if(!selectGetTable(select_query))
        printf("��ʾ���\n");

    return;

}

void insertStu_ID(LNode *stu)
{
    do{
        printf("ѧ��ID:\n");
        scanf("%s",stu->mID);
    }while(!isdigit(*stu->mID));

}
void insertStu_Name(LNode *stu)
{
    do{
        printf("����:\n");
        scanf("%s",stu->mName);
    }while(isdigit(*stu->mName));

}
void insertStu_Age(LNode *stu, LSTU *realStu)
{
    do{
        printf("����(0-100):\n");
        scanf("%s",&stu->mAge);
        realStu->mAge=atoi((const char *)&stu->mAge);
    }while(!isdigit(stu->mAge)||realStu->mAge<1||realStu->mAge>100);
}
void insertStu_Chinese(LNode *stu, LSTU *realStu)
{
    do{
        printf("����(0-100):\n");
        scanf("%s",&stu->mChineseScore);
        realStu->mChineseScore=atof((const char *)&stu->mChineseScore);
    }while(!isdigit(stu->mChineseScore)||realStu->mChineseScore<0||realStu->mChineseScore>100);
}
void insertStu_Math(LNode *stu, LSTU *realStu)
{
    do{
        printf("��ѧ�ɼ�(0-100):\n");
        scanf("%s",&stu->mMathScore);
        realStu->mMathScore=atof((const char *)&stu->mMathScore);
    }while(!isdigit(stu->mMathScore)||realStu->mMathScore<0||realStu->mMathScore>100);
}
void insertStu_All(LNode *stu, LSTU *realStu)
{
    insertStu_ID(stu);
    insertStu_Name(stu);
    insertStu_Age(stu,realStu);
    insertStu_Chinese(stu,realStu);
    insertStu_Math(stu,realStu);
}
void insertStu()
{
    LNode stu;
    LSTU realStu;
    char insertStr[100] = "insert into stu values(";
    int i=1;

    while(1){

        printf("�������%d��ѧ����Ϣ��\n",i);
        insertStu_All(&stu,&realStu);
        strcpy(insertStr,"insert into stu values(");
        sprintf(insertStr,"%s %s,'%s',%d,%lf,%lf);",insertStr,stu.mID,stu.mName,realStu.mAge,realStu.mChineseScore,realStu.mMathScore);
        printf("%s\n",insertStr);

        if(!selectGetTable(insertStr))
        printf("\n��%d��ѧ����Ϣ��ӳɹ���\n",i);
        else
        printf("\n��%d��ѧ����Ϣ���ʧ�ܣ�\n��У��ID�Ƿ��ظ���\n",i);

        char choice='y';
        printf("\n");
        printf("\n�Ƿ�������?(y/n)\n");
        fflush(stdin);//���������
        choice=getchar();
        getchar();
        if(choice!='y')
        {
            return;
        }
        ++i;
    }

}

void selectStu()
{
    int choice=0;
    menu_select();
    while (1) {
        scanf("%d",&choice);
        getchar();

        switch (choice) {
        case 1:selectByID();menu_select();
            break;
        case 2:selectByGrade();menu_select();
            break;
        case 3:return;
        default:
            printf("��ѡ����ȷ��������루1-3����\n");
        }
    }
}

void selectByID()
{
    LNode stu;
    char selectSql[100]="select * from stu where id = ";

    insertStu_ID(&stu);

    sprintf(selectSql,"%s%s;",selectSql,stu.mID);
    printf("%s\n",selectSql);
    if(!selectGetTable(selectSql))
        printf("�����ɹ�\n");
}

void selectByGrade()
{ 
    int choice;
        menu_selectByGrade();
        while(1){
        scanf("%d",&choice);
        getchar();

        switch (choice) {
        case 1:selectByChinese();menu_selectByGrade();
            break;
        case 2:selectByMath();menu_selectByGrade();
            break;
        case 3:return;
        default:
            printf("��ѡ����ȷ��������루1-3����\n");
        }
    }

}
void selectByChinese()
{
    LNode stu;
    LSTU realStu;
    char selectSql[100]="select * from stu where Chinese = ";

    insertStu_Chinese(&stu, &realStu);

    sprintf(selectSql,"%s%lf;",selectSql,realStu.mChineseScore);
    printf("%s\n",selectSql);
    if(!selectGetTable(selectSql))
        printf("�����ɹ�\n");

}

void selectByMath()
{
    LNode stu;
    LSTU realStu;
    char selectSql[100]="select * from stu where math = ";

    insertStu_Math(&stu, &realStu);

    sprintf(selectSql,"%s%lf;",selectSql,realStu.mMathScore);
    printf("%s\n",selectSql);
    if(!selectGetTable(selectSql))
        printf("�����ɹ�\n");
    //select_exec(selectSql);
}



void updateStu()
{
    LNode stu;
    int choice;
    insertStu_ID(&stu);
    menu_updateStu(&stu);
    while (1){
        scanf("%d",&choice);
        getchar();
        switch (choice) {
        case 1:updateID(&stu);menu_updateStu(&stu);
            break;
        case 2:updateName(&stu);menu_updateStu(&stu);
            break;
        case 3:updateAge(&stu);menu_updateStu(&stu);
            break;
        case 4:updateChinese(&stu);menu_updateStu(&stu);
            break;
        case 5:updateMath(&stu);menu_updateStu(&stu);
            break;
        case 6:return;
        default:
            printf("��ѡ����ȷ��������루1-6����\n");
        }
    }

}
void updateID(LNode *stu)
{
    LNode newStu;
    char updateSql[100]="update stu set ";
    printf("�޸�IDΪ%sΪ��\n",stu->mID);
    insertStu_ID(&newStu);
    sprintf(updateSql,"%s id = %d where id = %d;",updateSql,atoi((const char*)newStu.mID),atoi((const char*)stu->mID));
    printf("%s\n",updateSql);
    if(!selectGetTable(updateSql))
        printf("�޸ĳɹ���\n");
    else
        printf("�޸�IDʧ�ܣ���У��ID�Ƿ��ظ�\n");
    //strcpy(stu->mID,newID);

}
void updateName(LNode *stu)
{
    char updateSql[100]="update stu set ";

    printf("�޸�IDΪ%sѧ������Ϊ��\n",stu->mID);
    insertStu_Name(stu);
    sprintf(updateSql,"%s name = '%s' where id = %d;",updateSql,stu->mName,atoi((const char*)stu->mID));

    printf("%s\n",updateSql);
    if(!selectGetTable(updateSql))
        printf("�޸ĳɹ�!\n");

}
void updateAge(LNode *stu)
{
    char updateSql[100]="update stu set ";
    LSTU realStu;
    printf("�޸�IDΪ%sѧ������Ϊ��\n",stu->mID);
    insertStu_Age(stu,&realStu);

    sprintf(updateSql,"%s age = %d where id = %d;",updateSql,realStu.mAge,atoi((const char*)stu->mID));

    printf("%s\n",updateSql);
    if(!selectGetTable(updateSql))
        printf("�޸ĳɹ�!\n");
}
void updateChinese(LNode *stu)
{
    char updateSql[100]="update stu set ";
    LSTU realStu;
    printf("�޸�IDΪ%sѧ�����ĳɼ�Ϊ��\n",stu->mID);
    insertStu_Chinese(stu,&realStu);

    sprintf(updateSql,"%s Chinese = %lf where id = %d;",updateSql,realStu.mChineseScore,atoi((const char*)stu->mID));
    printf("%s\n",updateSql);
    if(!selectGetTable(updateSql))
        printf("�޸ĳɹ�!\n");
}
void updateMath(LNode *stu)
{
    char updateSql[100]="update stu set ";
    LSTU realStu;
    printf("�޸�IDΪ%sѧ����ѧ�ɼ�Ϊ��\n",stu->mID);
    insertStu_Math(stu,&realStu);

    sprintf(updateSql,"%s math = %lf where id = %d;",updateSql,realStu.mMathScore,atoi((const char*)stu->mID));

    printf("%s\n",updateSql);
    if(!selectGetTable(updateSql))
        printf("�޸ĳɹ�!\n");
}
void deleteStuByID()
{
    LNode stu;
    char deleteSql[100]="delete from stu where id = ";
    printf("������Ҫɾ����ѧ��ID\n");
    insertStu_ID(&stu);

    sprintf(deleteSql,"%s%d;",deleteSql,atoi((const char*)stu.mID));

    if(!selectGetTable(deleteSql))
        printf("ɾ���ɹ�!\n");

}
void deleteStuByName()
{
    LNode stu;
    char deleteSql[100]="delete from stu where name =";
    printf("������Ҫɾ����ѧ������\n");
    insertStu_Name(&stu);
    sprintf(deleteSql,"%s'%s';",deleteSql,stu.mName);
    if(!selectGetTable(deleteSql))
        printf("ɾ���ɹ�\n");
    return;
}

void deleteStu()
{
    int choice;
    menu_deleteStu();
    while (1){
        scanf("%d",&choice);
        getchar();

        switch(choice){
        case 1 : deleteStuByID();menu_deleteStu();
            break;
        case 2 : deleteStuByName();menu_deleteStu();
            break;
        case 3 : return;
        default:
            printf("��ѡ����ȷ��������루1-3����\n");
        }
    }

}

void sortStu()
{
    int choice;
    menu_sortStu();
    while (1){
        scanf("%d",&choice);
        getchar();

        switch (choice) {
            case 1:sortStuMethod("id","ASC");menu_sortStu();
                break;
            case 2:sortStuByGrade();menu_sortStu();
                break;
            case 3:return;
            default:
                printf("��ѡ����ȷ��������루1-3����\n");
        }
    }

}


void sortStuByGrade()
{
    int choice;
    menu_sortStuByGrade();
    while (1){
        scanf("%d",&choice);
        getchar();

        switch (choice) {
            case 1:sortStuMethod("Chinese","DESC");menu_sortStuByGrade();
                break;
            case 2:sortStuMethod("math","DESC");menu_sortStuByGrade();
                break;
            case 3:sortStuBySum("id,name,sum(Chinese+math)","id","order by sum(Chinese+math) DESC");menu_sortStuByGrade();
                break;
            case 4:sortStuBySum("id,name,sum(Chinese+math)","id","order by sum(Chinese+math) ASC");menu_sortStuByGrade();
                break;
            case 5:return;
                break;
            default:
                printf("��ѡ����ȷ��������루0-5����\n");
        }
    }

}
void sortStuMethod(const char * method,const char *ascOr )
{
    char sortSql[100]="SELECT * FROM stu ORDER BY ";

    sprintf(sortSql,"%s %s %s;",sortSql,method,ascOr);
    printf("������:\n");
    selectGetTable(sortSql);
    return;
}
void sortStuBySum(const char *stuColname,const char * method,const char *ascOr )
{

    char sortSql[100]="select";
    char *sortSql2=" FROM stu GROUP BY ";

    sprintf(sortSql,"%s %s %s %s %s;",sortSql,stuColname,sortSql2,method,ascOr);

    printf("%s\n",sortSql);
    printf("������:\n");
    selectGetTable(sortSql);
    return;
}
void select_exec(const char* sql,char* callStr)
{
    sqlite3 *db = NULL;
    char *errMsg = NULL;

    int ret=sqlite3_open(DBNAME,&db);
    if(ret != SQLITE_OK)
    {
        printf("���ݿ�򿪳��� %s\n",sqlite3_errmsg(db));
        exit(-1);
    }
    ret = sqlite3_exec(db,sql,callback,callStr,&errMsg);
    if(ret != SQLITE_OK)
    {
        sqlite3_close(db);
        db=NULL;
        printf("\n����,�����룺%s\n",errMsg);
        return ;
    }
    sqlite3_close(db);
    db=NULL;
    return;
}
int selectGetTable(const char *sql)
{
    sqlite3 *db;
    int nrow,ncolumn;
    char ** db_result;
    char *errMsg = NULL;
    int ret=sqlite3_open(DBNAME,&db);

    if(ret != SQLITE_OK)
    {
        printf("���ݿ�򿪳���%s",sqlite3_errmsg(db));
        exit(-1);
    }
    ret = sqlite3_get_table(db,sql,&db_result,&nrow,&ncolumn,&errMsg);
    if(ret != SQLITE_OK)
    {
        printf("�����룺%s\n",errMsg);
        sqlite3_close(db);
        return 1 ;
    }
    for(int i=0;i<(nrow+1)*ncolumn;i+=ncolumn)
    {
        for(int j=0;j<ncolumn;j++)
        {
            printf("|");
            printf(" %s   ",db_result[i+j]);
        }
        printf("| \n");
    }

    sqlite3_close(db);
    db=NULL;
    printf("\n\n�밴���������...");
    fflush(stdin);
    getchar();
    fflush(stdin);
    return 0;
}
static int callback(void *data, int argc,char **argv,char **stuColName)
{
    static int num=1;
    printf("(%d).",num);
    ++num;
    fprintf(stderr,"%s", (const char* )data);
    for (int i=0;i<argc;i++)
    {
        printf("%s : %s\n",stuColName[i],argv[i]?argv[i]:"NULL");
    }
    printf("\n\n�밴���������...");
    fflush(stdin);
    getchar();
    fflush(stdin);
    return 0;
}

