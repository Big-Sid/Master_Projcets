#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void rand_fill (int *array, unsigned int length);
void bubble_sort(int *array,int length);
void selection_sort(int *array,int length);
void insertion_sort(int *array,int length);
void quicksort(int *array, int left, int right);
void binary_quicksort(int *array,int l,int r,int k);
void decreasing_array(int *array,int length);
void ascending_array(int *array, int length);
void time_measure(int *array,int *array_1,int *array_2,int length);
void time_measure_2(int *array,int *array_1,int *array_2,int length);
void swap(int a[], int b, int c);
int digit_comp(int a,int b);
void heap_build(int *array,int length);
void heap_build_again(int *array,int start,int length);
void heap_sort(int *array,int length);




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
    //time_measure(a,b,c,length);
    time_measure_2(a,b,c,length);
    printf("\n");
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

void quicksort(int *array, int left, int right)
{
    {
        if(left<right)
        {
            int l =left;
            int r =right;
            int p = rand()%(right-left)+left;
            swap(array,l,p);
            int pivot = array[left];
            while(l<r)
            {
                while(l<r&&array[r]>=pivot)
                {
                    r--;
                }
                if(l<r)
                {
                    array[l++]=array[r];
                }
                while(l<r&&array[l]<pivot)
                {
                    l++;
                }
                if(l<r)
                {
                    array[r--]=array[l];
                }
            }
            array[l]=pivot;
            quicksort(array,left,l-1);
            quicksort(array,l+1,right);
        }
    }
}

void binary_quicksort(int *array,int l,int r,int k)
{
    int i;
    int j;
    if(l<r && k>=0)
    {
        i = l;
        j = r;
        while(i< j)
        {
            while(digit_comp(array[i],k) == 0 && i< r)
            {
                i++;
            }
            while(digit_comp(array[j],k) == 1 && j>l)
            {
                j--;
            }
            if(i<j)swap(array,i,j);
        }
        binary_quicksort(array,l,j,k-1);
        binary_quicksort(array,i,r,k-1);
    }
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

    start = clock ();
    selection_sort(array_2,length);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("selection_sort for ascending order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");


}

void time_measure_2(int *array,int *array_1,int *array_2,int length)
{
    int *a = malloc(sizeof(int)*length);
    int *a_1 = malloc(sizeof(int)*length);
    int *a_2 = malloc(sizeof(int)*length);
    for(int i = 0 ; i < length; i++)
    {
        a[i]=array[i];
    }
    for(int i = 0 ; i < length; i++)
    {
        a_1[i]=array_1[i];
    }
    for(int i = 0 ; i < length; i++)
    {
        a_2[i]=array_2[i];
    }
    int n = length /10;
    int avg = n *2;
    long double avg_time;
    long double time;
    clock_t start, end;
    //printf("Here is the result of bubble sorting for random order array:  ");
    start = clock ();
    quicksort(a,0,length-1);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("quick_sort for random order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");


    start = clock ();
    quicksort(a_1,0,length-1);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("quick_sort for decreasing order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    start = clock ();
    quicksort(a_2,0,length-1);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("quick_sort for ascending order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    int *b = malloc(sizeof(int)*length);
    int *b_1 = malloc(sizeof(int)*length);
    int *b_2 = malloc(sizeof(int)*length);
    for(int i = 0 ; i < length; i++)
    {
        b[i]=array[i];
    }
    for(int i = 0 ; i < length; i++)
    {
        b_1[i]=array_1[i];
    }
    for(int i = 0 ; i < length; i++)
    {
        b_2[i]=array_2[i];
    }
    start = clock ();
    binary_quicksort(b,0,length-1,6);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("binary_quick_sort for random order order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    start = clock ();
    binary_quicksort(b_1,0,length-1,6);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("binary_quick_sort for decreasing order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    start = clock ();
    binary_quicksort(b_2,0,length-1,6);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("binary_quick_sort for ascending order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    int *c = malloc(sizeof(int)*length);
    int *c_1 = malloc(sizeof(int)*length);
    int *c_2 = malloc(sizeof(int)*length);
    for(int i = 0 ; i < length; i++)
    {
        c[i]=array[i];
    }
    for(int i = 0 ; i < length; i++)
    {
        c_1[i]=array_1[i];
    }
    for(int i = 0 ; i < length; i++)
    {
        c_2[i]=array_2[i];
    }
    start = clock ();
    heap_sort(c,length);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("heap_sort for random order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    start = clock ();
    heap_sort(c_1,length);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("heap_sort for decreasing order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");

    start = clock ();
    heap_sort(c_2,length);
    end = clock();
    time = (long double)(end - start) / CLOCKS_PER_SEC;
    time *= 10e3;
    avg_time=time/avg;
    printf ("heap_sort for ascending order array runs in %LFms\n", time);
    printf ("average time runs in %LFms\n", avg_time);
    printf("\n");
    free(a);
    free(a_1);
    free(a_2);
    free(b);
    free(b_1);
    free(b_2);
    free(c);
    free(c_1);
    free(c_2);
}

void swap(int a[], int b, int c)
{
    int temp = a[b];
    a[b]=a[c];
    a[c]=temp;
}

int digit_comp(int a,int b)
{
    if((1<< b) & a)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void heap_build(int *array,int length)
{
    for(int i = 0 ; i < length ; i++)
    {
        int current = i;
        int father = (current-1)/2;
        while(array[current]>array[father])
        {
            swap(array,current,father);
            current=father;
            father =(current-1)/2;
        }
    }
}

void heap_build_again(int *array,int start,int length)
{
    int left_child=start*2+1;
    int right_child=start*2+2;
    while(left_child<length)
    {
        int bigger;
        if(array[left_child]<array[right_child]&&right_child<length)
        {
            bigger=right_child;
        }
        else
        {
            bigger=left_child;
        }
        if(array[start]>array[bigger])
        {
            bigger=start;
        }
        if(start==bigger)
        {
            break;
        }
        swap(array,bigger,start);
        start=bigger;
        left_child=start*2+1;
        right_child=start*2+2;
    }
}

void heap_sort(int *array,int length)
{
    heap_build(array,length);
    int length_h = length;
    while(length_h>1)
    {
        swap(array,0,length_h-1);
        length_h--;
        heap_build_again(array,0,length_h);
    }
}