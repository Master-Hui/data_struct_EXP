#include <stdio.h>
#include <stdlib.h>
#define NUM_MAX 1000
#define N 100000
typedef struct student{
    int code;
    int grades[5];
    double aver_grade;
}STUDENT;

double get_Wei_Aver_Score(int grades[5],double weight[5])//计算加权平均分
{
    double Aver;
    for(int i =0;i<5;i++)
    {
        Aver+=grades[i]*weight[i];
    }
    return Aver;
}
int find_priority(int Priority[5],int pri)//寻找不同学科所对应的优先级
{
    if(pri>5||pri<=0)
        return -1;
    for(int i=0;i<5;i++)
    {
        if(Priority[i] == pri)
        {
            return i;
        }
    }
    return -1;
}
STUDENT* Change_by_Priority(STUDENT *student_data,int Priority[5],int i,int j)//加权分数相同时，判断是否需要交换位置
{
    int grade_num;
    STUDENT temp;
    for(int i =1;i<=5;i++)
    {
        grade_num=find_priority(Priority,i);
        if(student_data[i].grades[grade_num]<student_data[j].grades[grade_num])
        {
            temp=student_data[i];
            student_data[i]=student_data[j];
            student_data[j]=temp;
            return student_data;
        }
    }
    if(student_data[i].code<student_data[j].code)
    {
        temp=student_data[i];
            student_data[i]=student_data[j];
            student_data[j]=temp;
            return student_data;
    }
    return student_data;
}
STUDENT* sort(STUDENT *student_data,int student_num,int Priority[5])
{
    STUDENT temp;
    int i,j;
    for( i=0;i<student_num;i++)
    {
        for( j=i+1;j<student_num;j++)
        {
            if(student_data[i].aver_grade<student_data[j].aver_grade)
                {
                    temp=student_data[i];
                    student_data[i]=student_data[j];
                    student_data[j]=temp;
                }
        }
    }
    for(i=0;i<student_num;i++)
    {
        for(j=i+1;j<student_num;j++)
        {
            if(student_data[i].aver_grade==student_data[j].aver_grade)//两个学习成绩一致
            {
                student_data = Change_by_Priority(student_data,Priority,i,j);
            }
        }
    }
    return student_data;
}
int main()
{
    int student_num,i,j;
    STUDENT student_data[NUM_MAX]={0};
    double weight[5];
    int Priority[5];
    scanf("%d",&student_num);//获取学生人数
    for(i=0;i<5;i++)//获取优先级
    {
        scanf("%d",&Priority[i]);
    }
    for(i=0;i<5;i++)//获取权重
    {
        scanf("%lf",&weight[i]);
    }
    for(j=0;j<student_num;j++)//学生信息存储
    {
        scanf("%d",&student_data[j].code);
        for(int k=0;k<5;k++)
        {
            scanf("%d",&student_data[j].grades[k]);
        }
    }

    /*********** TASK 1 **********/
    for(i=0;i<student_num;i++)//计算每个学生的加权平均分
    {
        student_data[i].aver_grade=get_Wei_Aver_Score(student_data[i].grades,weight);

    }
    student_data = sort(student_data,student_num,Priority);
    int rank;
    for(i=0;i<student_num;i++)
    {
        if(!(i>=1&&(student_data[i]==student_data[i-1])))
            rank = i+1;
        printf("%d %d\n",rank,student_data[i].code);
    }
    /*********** TASK 1 **********/
    int num;
    
    /*********** TASK 2 **********/
    
    return 0;
}
