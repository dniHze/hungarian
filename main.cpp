#include"hungarian.h"
#include<iostream>

using namespace std;

int main() {
    int i=0;

    hungarian task;

    task.input_size();
    task.create_array();
    task.input_elements();
    task.output_array(task.size,task.size);
    task.max_min();
    task.search();
    task.output_array(task.size,task.size);

    if (task.check()==true)
        task.answer_output();
    else {
        do{
            task.cross_min();
            task.processing();
            task.clear_result();
            i++;
        } while (task.check()==false&&i<10);

        task.answer_output();
    }

    return 0;
}

