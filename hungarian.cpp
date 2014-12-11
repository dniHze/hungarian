#include "hungarian.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdlib.h>

using namespace std;

hungarian::hungarian() {
    ans_i=0;
    result=0;
}

hungarian::~hungarian() {
    for (int count = 0; count < size; count++)
            delete []array[count];
    for (int count = 0; count < size; count++)
            delete []initarray[count];
    delete []A;
    delete []B;
    delete []C;
}

void hungarian::input_size() {
    cout<<"Enter number of rows:";
    vertification(rows);
    cout<<"Enter number of columns:";
    vertification(columns);
    if (rows==columns) {
        square_flag=true;
        size=rows;
        return;
    }
    if (rows>columns) {
        square_flag=false;
        size=rows;
    } else {
        square_flag=false;
        size=columns;
    }
}

void hungarian::create_array()
{
    array = new int* [size];

    for (int count = 0; count < size; count++)
            array[count] = new int [size];
    initarray=new int* [size];

    for (int count = 0; count < size; count++)
            initarray[count] = new int [size];
    answer=new int* [2];

    for (int count = 0; count < size; count++)
            answer[count] = new int [size];

    A=new int[size];
    for(int i=0;i<size;i++)
        A[i]=0;

    B=new int[size];
    for(int i=0;i<size;i++)
        B[i]=0;

    C=new int[size*2];
    for(int i=0;i<size*2;i++)
        C[i]=0;
}

void hungarian::input_elements() {
    for(int i=0;i<rows;i++)
        for(int j=0;j<columns;j++) {
            cout<<"Enter ("<<i+1<<","<<j+1<<") element:";
            vertificatione(array[i][j]);
        }
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            initarray[i][j]=array[i][j];

    if(square_flag==true)
        return;

    if((size-rows)>0)
        for( int i=rows;i<size;i++)
            for(int j=0;j<columns;j++)
                array[i][j]=0;

    if((size-columns)>0)
        for(int i=0;i<rows;i++)
            for(int j=columns;j<size;j++)
                array[i][j]=0;

    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            initarray[i][j]=array[i][j];

}

int hungarian::min_row(int row) {
    int min=array[row][0];
    for(int i=0;i<size;i++)
        if(array[row][i]<min)
            min=array[row][i];

    return min;
}


int hungarian::min_col(int column) {
    int min=array[0][column];
    for(int i=0;i<size;i++)
        if(array[i][column]<min)
            min=array[i][column];

    return min;
}

void hungarian::search()
{
    int minimal=0;
    for(int j=0;j<size;j++) {
        minimal=min_row(j);
        for(int l=0;l<size;l++)
            array[j][l]-=minimal;
    }

    for(int j=0;j<size;j++) {
        minimal=min_col(j);
        for(int l=0;l<size;l++)
            array[l][j]-=minimal;
    }
}

bool hungarian::check()
{
    int t;
    int count;
    bool flag=false;
    bool flag_result=true;
    do {
        flag=false;
        for (int i=0;i<size;i++,t=0,count=0){
            for (int j=0;j<size;j++)
                if (array[i][j]==0&&B[j]==0) {
                    count++;
                    t=j;
                }

            if (count==1) {
                A[i]=1;
                B[t]=1;
                flag=true;
                answer[0][ans_i]=i;
                answer[1][ans_i]=t;
                ans_i++;
                if(ans_i==size)
                    break;
            }
        }
    } while(flag==true);

    for(int i=0;i<size;i++)
        if(A[i]==0)
            flag_result=false;

    for(int i=0;i<size;i++)
        if(B[i]==0)
            flag_result=false;

    for(int i=0;i<size;i++) {
        A[i]=0;
        B[i]=0;
    }

    return flag_result;
}

void hungarian::clear_result() {
    result=0;
    ans_i=0;
    for(int i=0;i<size;i++) {
      A[i]=0;
      B[i]=0;
    }
}

void hungarian::answer_output() {
    for(int i=0;i<size;i++)
        result+=initarray[answer[0][i]][answer[1][i]];

    cout<<"result=";

    for(int i=0;i<size;i++) {
        if((i+1)>=size)
            cout<<initarray[answer[0][i]][answer[1][i]];
        else
            cout<<initarray[answer[0][i]][answer[1][i]]<<"+";
    }

    cout<<"="<<result<<endl;
}

void hungarian::max_nulls()
{
    int counter=0;

    for(int i=0;i<size;i++,counter=0) {
        do{
            if(A[i]==1) {
                C[i]=0;
                i++;
            }

            if(i==size)
                break;

        } while(A[i]==1);

        if(i==size)
            break;

        for(int j=0;j<size;j++)
            if(array[i][j]==0&&B[j]==0)
                counter++;

        C[i]=counter;
    }

    counter=0;

    for(int i=0;i<size;i++,counter=0)
    {
        do{
            if(B[i]==1) {
                C[i+size]=0;
                i++;
            }

            if(i==size)
                break;
        } while(B[i]==1);

        for(int j=0;j<size;j++)
            if(array[j][i]==0&&A[j]==0)
                counter++;

        C[size+i]=counter;
    }
}

void hungarian::cross_min() {
    bool flag;
    int max;
    int t=0;
    do{
        max_nulls();
        max=0;
        flag=true;
        for(int i=0;i<size*2;i++)
            if(max<C[i]) {
                max=C[i];
                t=i;
            }

        if(t<size)
            A[t]=1;

        if(t>=size)
            B[t-size]=1;

        C[t]=0;
        max_nulls();

        for(int i=0;i<size*2;i++)
            if(C[i]!=0)
                flag=false;

    } while (flag==false);
}

void hungarian::processing() {
    int min=0;

    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(min<array[i][j]&&B[j]==0)
                min=array[i][j];

    for(int i=0;i<size;i++)
    {
        do{
            if(A[i]==1)
                i++;

            if(i==size)
                break;
        }while(A[i]==1);

        if(i==size)
            break;

        for(int j=0;j<size;j++)
            if(min>array[i][j]&&B[j]==0)
                min=array[i][j];

    }

    for(int i=0;i<size;i++) {
        do{
            if(A[i]==1)
                i++;
            if(i==size)
                break;
        } while(A[i]==1);

        if(i==size)
            break;

        for(int j=0;j<size;j++)
            if(B[j]==0)
                array[i][j]-=min;

    }

    output_array(size,size);

    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(A[i]==1&&B[j]==1)
                array[i][j]+=min;

    output_array(size,size);
}

void hungarian::max_min() {
    return;
}


void hungarian::output_array(int k, int n) {
    cout<<"Current array:"<<endl;
    for(int i=0;i<k;i++,cout<<endl)
        for(int j=0;j<n;j++)
            cout<<setw(4)<<left<<array[i][j]<<"   ";
}

void hungarian::vertificatione(int& number) {
    while ((cin >> number).fail() || cin.get() != '\n'||number<=0) {
        cin.clear();
        cin.sync();
        cout << "Error!!!Enter integer >0:";
    }
}

void hungarian::vertification(int& number){
    while ((cin >> number).fail() || cin.get() != '\n'||number<2) {
        cin.clear();
        cin.sync();
        cout << "Error!!!Enter integer>2:";
    }
}
