#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
typedef struct binary_tree* link;

typedef struct binary_tree
{
    char data;
    link left;
    link right;
}node;

link create_tree(char *order,int oder_len,int idx);

link NODE(char item,link left,link right);

int get_length(char *filename);

void readfile(char *filename);

void sequence_init(int length,char *a);

void tree_print(link root);

int height_of_tree(link root);

int count_of_node(link root);

bool isBalanced(link root);

bool is_complete(link root);

void output_file(link root,char *filename);

void output_file_1(char *filename);

void output_file_2(char *filename);

char o_order[100];

char b_order[100];

int main()
{
    int length = get_length("input_tree.txt");
    if(length == 0) //the tree is empty
    {
        output_file_1("tree_properties.txt");
    }
    if(length == 1)//tree only has a root
    {
        output_file_2("tree_properties.txt");
    }
    sequence_init(length,b_order);
    readfile("input_tree.txt");
    /*for(int i = 0; i < strlen(b_order);i++)
    {
        printf("%c",b_order[i]);
    }
    printf("\n");*/
    link b_tree=create_tree(b_order,length,0);
    //tree_print(b_tree); // pre_order
    output_file(b_tree,"tree_properties.txt");
}

void readfile(char *filename)
{
    FILE *fp;
    int a_1;
    char p='A';
    char p_1 ='B';
    if((fp=fopen(filename,"r+")) == NULL)
    {
        printf("Error\n");
        exit(0);
    }
    while(fgets(o_order,10,fp)!=NULL)
    {
        a_1 = atoi(&o_order[1]);
        int a_2 = atoi(&o_order[4]);
        if(a_1==0)
        {
            printf("Please input correct root\n");
            exit(0);
        }
        if(a_1==1&&a_2==1)//case start from(1, 1)
        {
            b_order[a_2-1] =p;
            p++;
        }
        else  //case start not from (1, 1)
        {
            b_order[0]='A';
            b_order[a_2-1]=p_1;
            p_1++;
        }

    }
}

int get_length(char *filename)
{
    int a_1=0;
    FILE *fp;
    if((fp=fopen(filename,"r+")) == NULL)
    {
        printf("Error\n");
        exit(0);
    }
    while(fgets(o_order,10,fp)!=NULL)
    {
        a_1 = atoi(&o_order[4]);
    }
    return a_1;
}

void sequence_init(int length,char *a)
{
    for(int i=0; i <length;i++)
    {
        a[i]='#';
    }
}

link NODE(char item,link left,link right)
{
    link born=malloc(sizeof(node));
    born->data=item;
    born->left=left;
    born->right=right;
    return born;
}

link create_tree(char *order,int oder_len,int idx)
{
    if(order[idx] =='#' || idx>=oder_len)
    {
        return NULL;
    }
    link root = NODE(order[idx],NULL,NULL);
    root->left= create_tree(order,oder_len,idx*2+1);
    root->right= create_tree(order,oder_len,idx*2+2);
    return root;
}

void tree_print(link root)
{
    if(root!=NULL)
    {
        printf("%c",root->data);
        tree_print(root->left);
        tree_print(root->right);
    }
}

int height_of_tree(link root)
{
    int l,r;
    if(root!=NULL)
    {
        l= height_of_tree(root->left)+1;
        r= height_of_tree(root->right)+1;
        return l>r?l:r;
    }
    else
    {
        return 0;
    }
}

int count_of_node(link root)
{
    if(root == NULL)
    {
        return 0;
    }
    else
    {
        return count_of_node(root->right)+ count_of_node(root->left)+1;
    }
}

bool isBalanced(link root)
{
    if(root == NULL)
    {
        return true;
    }
    int l = height_of_tree(root->left);
    int r = height_of_tree(root->right);
    if(abs(l-r)>1)
    {
        return false;
    }
    else
    {
        return isBalanced(root->left)&& isBalanced(root->right);
    }
}

bool is_complete(link root)
{
    int h = height_of_tree(root);
    int sum = count_of_node(root);
    if(sum == (pow(2,h)-1))
        return true;
    else
        return false;
}

void output_file(link root,char *filename)
{
    FILE *fp=fopen(filename,"w");
    if (fp == NULL)
    {
        printf("Error\n");
        return;
    }
    int height= height_of_tree(root);
    bool flag= isBalanced(root);
    bool flag_2 = is_complete(root);
    if(flag_2)
    {
        fprintf(fp,"Is the tree complete? Yes\n");
    }
    else
    {
        fprintf(fp,"Is the tree complete? No\n");
    }
    fprintf(fp,"What's the height of the tree? %d\n",height-1);
    if(flag)
    {
        fprintf(fp,"Is it balanced? Yes");
    }
    else
    {
        fprintf(fp,"Is it balanced? No");
    }
}

void output_file_1(char *filename)
{
    FILE *fp=fopen(filename,"w");
    if (fp == NULL)
    {
        printf("Error\n");
        return;
    }
    fprintf(fp,"Is the tree complete? Yes\n");
    fprintf(fp,"What's the height of the tree? 0\n");
    fprintf(fp,"Is it balanced? Yes");
    exit(0);
}

void output_file_2(char *filename)
{
    FILE *fp=fopen(filename,"w");
    if (fp == NULL)
    {
        printf("Error\n");
        return;
    }
    fprintf(fp,"Is the tree complete? Yes\n");
    fprintf(fp,"What's the height of the tree? 0\n");
    fprintf(fp,"Is it balanced? Yes");
    exit(0);
}