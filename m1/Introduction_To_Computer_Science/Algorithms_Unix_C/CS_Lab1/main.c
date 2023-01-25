#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void rand_fill (int *array, unsigned int length);
void bubble_sort(int *array,int length);
void selection_sort(int *array,int length);
void insertion_sort(int *array,int length);
void decreasing_array(int *array,int length);
void ascending_array(int *array, int length);
void time_measure(int *array,int *array_1,int *array_2,int length);


int main()
{
    int length=0;
    printf("please input the length of the array: ");
    scanf ( " %d", &length);
    int *a = malloc(sizeof(int)*length);
    rand_fill(a,length);
    int *b = malloc(sizeof(int)*length);
    int *c = malloc(sizeof(int)*length);
    decreasing_array(b,length);
    ascending_array(c,length);
    time_measure(a,b,c,length);
    free(a);
    free(b);
    free(c);
}

void rand_fill (int* array, unsigned int length)
{
    time_t time_seed;
    srand((unsigned) time(&time_seed));
    for ( int j = 0 ; j <length; j ++)
    {
        array[j] =rand()%100;
    }
}

void bubble_sort(int* array,int length)
{
    int *b_array = malloc(sizeof(int)*length);
    for(int i = 0 ; i < length; i++)
    {
        b_array[i]=array[i];
    }
    for (int i = 0 ; i < length-1; i++)
    {
        int flag = 1;
        for(int j = 0 ; j < length-1-i; j++)
        {
            if(b_array[j]>b_array[j+1])
            {
                int temp = b_array[j];
                b_array[j] = b_array[j+1];
                b_array[j+1]=temp;
                flag = 0;
            }
        }
        if(flag ==1)
        {
            return;
        }
    }
    //for (int i = 0 ; i < length ; i ++)
    //{
    //    printf("%d ",b_array[i]);
    //}
    //printf("\n");
    free(b_array);
}

void selection_sort(int *array,int length)
{

    int *s_array = malloc(sizeof(int)*length);
    for(int i = 0 ; i < length; i++)
    {
        s_array[i]=array[i];
    }
    for(int i = 0 ; i < length-1; i++)
    {
        int min = s_array[i];
        int pos = i ;
        for(int j = i+1 ; j < length ; j++)
        {
            if(s_array[j] <= min)
            {
                pos = j ;
                min = s_array[j];
            }
            int temp = min;
            s_array[i] = s_array[j];
            s_array[pos] = temp;
        }
    }
    //for (int i = 0 ; i < length ; i ++)
    //{
    //    printf("%d ",s_array[i]);
    //}
    //printf("\n");
    free(s_array);
}

void insertion_sort(int *array, int length)
{
    int *i_array = malloc(sizeof(int)*length);
    for(int i = 0 ; i < length ; i++)
    {
        i_array[i]=array[i];
    }
    for(int i = 0 ; i < length ; i++)
    {
        if(i_array[i-1]>i_array[i])
        {
            int j = i-1;
            while(j>=0 && i_array[j]>i_array[j+1])
            {
                int temp;
                temp = i_array[j];
                i_array[j] = i_array[j+1];
                i_array[j+1]=temp;
                j--;
            }
        }
    }
    //for (int i = 0 ; i < length ; i ++)
    //{
    //    printf("%d ",i_array[i]);
    //}
    //printf("\n");
    free(i_array);
}

void decreasing_array(int* array,int length)
{
    int n  = length -1 ;
    for(int i = 0; i < length ; i++)
    {
        array[i] = n ;
        n--;
    }
}

void ascending_array(int *array,int length)
{
    int count = 0 ;
    for(int i = 0 ; i < length; i++)
    {
        array[i] = count;
        count ++;
    }
}


void time_measure(int *array,int *array_1,int *array_2,int length)
{
    int n = length /10;
    int avg = n *2;
    long double avg_time;
    long double time;
    clock_t start, end;
    //printf("Here is the result of bubble sorting for random order array:  ");
    start = clock ();
    bubble_sort(array,length);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("bubble_sort for random order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    //printf("Here is the result of selection sorting for random order array:  ");
    start = clock();
    selection_sort(array,length);
    end = clock();
    time = (long double)(end - start)/CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("selection_sort for random order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");


    //printf("Here is the result of insertion sorting for random order array:  ");
    start = clock();
    insertion_sort(array,length);
    end = clock();
    time = (long double)(end - start)/CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("insertion_sort for random order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    //printf("Here is the result of bubble sorting for decreasing order array:  ");
    start = clock ();
    bubble_sort(array_1,length);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("bubble_sort for decreasing order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    //printf("Here is the result of selection sorting for decreasing order array:  ");
    start = clock ();
    selection_sort(array_1,length);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("selection_sort for decreasing order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    //printf("Here is the result of insertion sorting for decreasing order array:  ");
    start = clock ();
    insertion_sort(array_1,length);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("insertion_sort for decreasing order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    start = clock ();
    bubble_sort(array_2,length);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("bubble_sort for ascending order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    start = clock ();
    selection_sort(array_2,length);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("selection_sort for ascending order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    start = clock ();
    insertion_sort(array_2,length);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("insertion_sort for ascending order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");
}