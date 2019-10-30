
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
        printf("打开数据库出错： %s",sqlite3_errmsg(db));
        exit(-1);
    }
    //创建表
    ret = sqlite3_exec(db,"create table if not exists stu(id int(10) PRIMARY Key not NULL,name char(20) NOT NULL,age int NOT NULL,Chinese int,Math int)",0,0,&errMsg);
    if(ret !=   SQLITE_OK)
    {
        sqlite3_close(db);
        printf("创建数据表出错：%s\n",errMsg);
        return ;
    }
}
void menu_main()
{
    printf("\n");
    printf("****************************************************\n");
    printf(" ***************** 学生信息管理系统  ****************** \n");
    printf("Note:\n");
    printf("     ---------------          ---------------   \n");
    printf("     ******************************************** \n");
    printf("     * 0.帮助                 **  1.排序查找信息 * \n" );
    printf("     * 2.查询学生信息         **  3.修改学生信息 * \n");
    printf("     * 4.添加学生信息         **  5.删除学生信息 * \n");
    printf("     * 6.显示所有信息         **  7.退出         * \n");
    printf("     ********************************************\n");
    printf("     ---------------          ---------------   \n");
    printf("请选择对应序号（0—7）:\n");
}
void menu_select()
{
    printf("\n");
    printf(" ***************** 查询学生信息界面*******************\n");
    printf("Note:\n");
    printf("     ---------------          ---------------   \n");
    printf("     ******************************************** \n");
    printf("     * 1.ID查询               **  2.成绩查询     * \n");
    printf("     * 3.返回主界面           **  4.退出         *\n");
    printf("     ********************************************\n");
    printf("     ---------------          ---------------   \n");
    printf("请选择对应序号（1-3）:\n");
}
void menu_help()
{
    printf("         ------------------------------\n");
    printf("         欢迎来到学生管理系统（数据库版）\n");
    printf("   此为完成版并非最终版，部分函数仍可继续拆分或整合\n");
    printf("   -------------------------------------------------\n");
    printf("\n\n\n\n\n请按任意键返回...\n");
    getchar();
    fflush(stdin);

}
void menu_selectByGrade()
{
    printf("1.已知语文成绩\n2.已知数学成绩\n3.返回\n");
    printf("请输入你的选择(1-3):\n");
}
void menu_updateStu(LNode *stu)
{
    printf("选择修改ID：%s学生的信息 :\n"
               "1.ID\n2.姓名\n3.年龄\n4.语文\n5.数学\n6.返回\n",stu->mID);
    printf("请选择修改内容(1-6):\n");
}
void menu_deleteStu()
{
    printf("1.By学生ID:\n2.By学生姓名\n3.返回\n");

    printf("请选择（1-3）:\n");
}
void menu_sortStu()
{
    printf("1.ID（升序）\n2.成绩（降序）\n3.返回\n");
    printf("请选择（1-3）:\n");
}
void menu_sortStuByGrade()
{
    printf("1.语文成绩（降序）\n2.数学成绩（降序）\n3.总成绩（降序）\n4.总成绩（升序）\n5.返回\n");
    printf("请选择(1-5)：\n");
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
                printf("请选择正确的序号输入（0-7）：\n");
            }
    }
}
void displayStu()
{
    const char *select_query="select * from stu";
    if(!selectGetTable(select_query))
        printf("显示完成\n");

    return;

}

void insertStu_ID(LNode *stu)
{
    do{
        printf("学生ID:\n");
        scanf("%s",stu->mID);
    }while(!isdigit(*stu->mID));

}
void insertStu_Name(LNode *stu)
{
    do{
        printf("姓名:\n");
        scanf("%s",stu->mName);
    }while(isdigit(*stu->mName));

}
void insertStu_Age(LNode *stu, LSTU *realStu)
{
    do{
        printf("年龄(0-100):\n");
        scanf("%s",&stu->mAge);
        realStu->mAge=atoi((const char *)&stu->mAge);
    }while(!isdigit(stu->mAge)||realStu->mAge<1||realStu->mAge>100);
}
void insertStu_Chinese(LNode *stu, LSTU *realStu)
{
    do{
        printf("语文(0-100):\n");
        scanf("%s",&stu->mChineseScore);
        realStu->mChineseScore=atof((const char *)&stu->mChineseScore);
    }while(!isdigit(stu->mChineseScore)||realStu->mChineseScore<0||realStu->mChineseScore>100);
}
void insertStu_Math(LNode *stu, LSTU *realStu)
{
    do{
        printf("数学成绩(0-100):\n");
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

        printf("请输入第%d名学生信息：\n",i);
        insertStu_All(&stu,&realStu);
        strcpy(insertStr,"insert into stu values(");
        sprintf(insertStr,"%s %s,'%s',%d,%lf,%lf);",insertStr,stu.mID,stu.mName,realStu.mAge,realStu.mChineseScore,realStu.mMathScore);
        printf("%s\n",insertStr);

        if(!selectGetTable(insertStr))
        printf("\n第%d名学生信息添加成功！\n",i);
        else
        printf("\n第%d名学生信息添加失败！\n请校验ID是否重复！\n",i);

        char choice='y';
        printf("\n");
        printf("\n是否继续添加?(y/n)\n");
        fflush(stdin);//清除缓存区
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
            printf("请选择正确的序号输入（1-3）：\n");
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
        printf("操作成功\n");
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
            printf("请选择正确的序号输入（1-3）：\n");
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
        printf("操作成功\n");

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
        printf("操作成功\n");
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
            printf("请选择正确的序号输入（1-6）：\n");
        }
    }

}
void updateID(LNode *stu)
{
    LNode newStu;
    char updateSql[100]="update stu set ";
    printf("修改ID为%s为新\n",stu->mID);
    insertStu_ID(&newStu);
    sprintf(updateSql,"%s id = %d where id = %d;",updateSql,atoi((const char*)newStu.mID),atoi((const char*)stu->mID));
    printf("%s\n",updateSql);
    if(!selectGetTable(updateSql))
        printf("修改成功！\n");
    else
        printf("修改ID失败，请校验ID是否重复\n");
    //strcpy(stu->mID,newID);

}
void updateName(LNode *stu)
{
    char updateSql[100]="update stu set ";

    printf("修改ID为%s学生姓名为新\n",stu->mID);
    insertStu_Name(stu);
    sprintf(updateSql,"%s name = '%s' where id = %d;",updateSql,stu->mName,atoi((const char*)stu->mID));

    printf("%s\n",updateSql);
    if(!selectGetTable(updateSql))
        printf("修改成功!\n");

}
void updateAge(LNode *stu)
{
    char updateSql[100]="update stu set ";
    LSTU realStu;
    printf("修改ID为%s学生年龄为新\n",stu->mID);
    insertStu_Age(stu,&realStu);

    sprintf(updateSql,"%s age = %d where id = %d;",updateSql,realStu.mAge,atoi((const char*)stu->mID));

    printf("%s\n",updateSql);
    if(!selectGetTable(updateSql))
        printf("修改成功!\n");
}
void updateChinese(LNode *stu)
{
    char updateSql[100]="update stu set ";
    LSTU realStu;
    printf("修改ID为%s学生语文成绩为新\n",stu->mID);
    insertStu_Chinese(stu,&realStu);

    sprintf(updateSql,"%s Chinese = %lf where id = %d;",updateSql,realStu.mChineseScore,atoi((const char*)stu->mID));
    printf("%s\n",updateSql);
    if(!selectGetTable(updateSql))
        printf("修改成功!\n");
}
void updateMath(LNode *stu)
{
    char updateSql[100]="update stu set ";
    LSTU realStu;
    printf("修改ID为%s学生数学成绩为新\n",stu->mID);
    insertStu_Math(stu,&realStu);

    sprintf(updateSql,"%s math = %lf where id = %d;",updateSql,realStu.mMathScore,atoi((const char*)stu->mID));

    printf("%s\n",updateSql);
    if(!selectGetTable(updateSql))
        printf("修改成功!\n");
}
void deleteStuByID()
{
    LNode stu;
    char deleteSql[100]="delete from stu where id = ";
    printf("请输入要删除的学生ID\n");
    insertStu_ID(&stu);

    sprintf(deleteSql,"%s%d;",deleteSql,atoi((const char*)stu.mID));

    if(!selectGetTable(deleteSql))
        printf("删除成功!\n");

}
void deleteStuByName()
{
    LNode stu;
    char deleteSql[100]="delete from stu where name =";
    printf("请输入要删除的学生姓名\n");
    insertStu_Name(&stu);
    sprintf(deleteSql,"%s'%s';",deleteSql,stu.mName);
    if(!selectGetTable(deleteSql))
        printf("删除成功\n");
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
            printf("请选择正确的序号输入（1-3）：\n");
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
                printf("请选择正确的序号输入（1-3）：\n");
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
                printf("请选择正确的序号输入（0-5）：\n");
        }
    }

}
void sortStuMethod(const char * method,const char *ascOr )
{
    char sortSql[100]="SELECT * FROM stu ORDER BY ";

    sprintf(sortSql,"%s %s %s;",sortSql,method,ascOr);
    printf("排序结果:\n");
    selectGetTable(sortSql);
    return;
}
void sortStuBySum(const char *stuColname,const char * method,const char *ascOr )
{

    char sortSql[100]="select";
    char *sortSql2=" FROM stu GROUP BY ";

    sprintf(sortSql,"%s %s %s %s %s;",sortSql,stuColname,sortSql2,method,ascOr);

    printf("%s\n",sortSql);
    printf("排序结果:\n");
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
        printf("数据库打开出错： %s\n",sqlite3_errmsg(db));
        exit(-1);
    }
    ret = sqlite3_exec(db,sql,callback,callStr,&errMsg);
    if(ret != SQLITE_OK)
    {
        sqlite3_close(db);
        db=NULL;
        printf("\n出错,错误码：%s\n",errMsg);
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
        printf("数据库打开出错：%s",sqlite3_errmsg(db));
        exit(-1);
    }
    ret = sqlite3_get_table(db,sql,&db_result,&nrow,&ncolumn,&errMsg);
    if(ret != SQLITE_OK)
    {
        printf("错误码：%s\n",errMsg);
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
    printf("\n\n请按任意键返回...");
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
    printf("\n\n请按任意键返回...");
    fflush(stdin);
    getchar();
    fflush(stdin);
    return 0;
}

