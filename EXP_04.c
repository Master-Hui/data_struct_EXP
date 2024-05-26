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
void sort(STUDENT *student_data,int student_num,int Priority[5])
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
}
void merge(unsigned long arr[], unsigned long temp[], int left, int mid, int right) {
    int i = left;    // 左半部分的起始索引
    int j = mid + 1; // 右半部分的起始索引
    int k = left;    // 用于临时数组的起始索引

    // 合并两个子数组到临时数组中
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // 如果左边的子数组还有剩余的元素，直接复制到临时数组中
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // 如果右边的子数组还有剩余的元素，直接复制到临时数组中
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // 将排序后的元素复制回原数组
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}
void mergeSort(unsigned long arr[],unsigned long temp[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2; // 找到中点

        // 分别对左右半部分进行归并排序
        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid + 1, right);

        // 合并两个排序好的部分
        merge(arr, temp, left, mid, right);
    }
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
     sort(student_data,student_num,Priority);
    int rank;
    for(i=0;i<student_num;i++)
    {
        if(!(i>=1&&(student_data[i].aver_grade==student_data[i-1].aver_grade)))
            rank = i+1;
        printf("%d %d\n",rank,student_data[i].code);
    }
    /*********** TASK 1 **********/


    int num;//输入的正整数个数
    unsigned long Inve_group[N]={0},temp[N]={0};//存储正整数序列
    /*********** TASK 2 **********/
    scanf("%d",&num);
    for(i=0;i<num;i++)//储存序列
    {
        scanf("%lu", &Inve_group[i]);
    }
    mergeSort(Inve_group,temp,0,num);
    unsigned long invr=0;
    unsigned long loop;
    for(i=0;i<num;i++)
    {
        loop=num-i-1;
        for(j=i+1;j<num;j++)
        {
            if(Inve_group[i]==Inve_group[j])
            {
                loop--;
            }
            invr += loop;
        }
    }
    printf("%lu",loop);
    return 0;
}

