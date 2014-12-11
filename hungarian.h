#ifndef HUNGARIAN_H
#define HUNGARIAN_H

class hungarian
{
public:
    hungarian();
    ~hungarian();
    int rows;
    int columns;
    int size;
    void input_size();
    void input_elements();
    void create_array();
    void output_array(int,int);
    void search();
    bool check();
    void clear_result();
    void answer_output();
    void next_step();
    void max_nulls();
    void cross_min();
    void processing();
    void max_min();
    void vertificationtrig(int &number);
private:
    void all_nulls();
    void vertification(int& number);
    void vertificatione(int &number);
    bool square_flag;
    int **array;
    int **initarray;
    int **answer;
    int ans_i;
    int result;
    int *A;
    int *B;
    int *C;
    int min_row(int);
    int min_col(int);

};

#endif // HUNGARIAN_H
