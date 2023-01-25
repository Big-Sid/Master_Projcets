#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct element
{
    char data[20]; // up to 20 words
    int  number; //count
    struct element *next;
};

struct element* head =NULL;

struct element *readfile(char *data);


void printf_List(struct  element *p);
void change_list_2(struct element *p);
void change_list(struct element *p);
void output_file(struct element *p, char *filename);

int main() {
    head= readfile("input_text.txt");
    change_list(head);
    change_list_2(head);
    printf_List(head);
    output_file(head,"output_text.txt");

}

void printf_List(struct element *p)
{
    int i =1;
    while(p!=NULL)
    {
        printf("%s %d\n",p->data,p->number);
        p=p->next;
        i++;
    }
}

void change_list(struct element *p)
{
    while(p!=NULL)  //initialize the frequency
    {
        p->number =1;
        p=p->next;
    }
}

void change_list_2(struct element *p)
{
    struct element *tmp_node; //
    struct element *tmp_node1; //
    struct element *pre_temp;
    tmp_node=p;
    while(tmp_node!=NULL)
    {
        pre_temp=tmp_node;
        while(pre_temp->next!=NULL)
        {
            tmp_node1=pre_temp->next;
            if(!strcmp(tmp_node->data,tmp_node1->data))
            {
                tmp_node->number++;
                pre_temp->next = tmp_node1->next;
                tmp_node1=pre_temp->next;
            }
            else
            {
                pre_temp=tmp_node1;
                tmp_node1=tmp_node1->next;
            }
        }
        tmp_node=tmp_node->next;
    }
}

void output_file(struct element *p, char *filename)
{
    FILE *fp=fopen(filename,"w");
    if (fp == NULL)
    {
        printf("Error\n");
        return;
    }
    while(p!=NULL)
    {
        fprintf(fp,"%s %d\n",p->data,p->number);
        p=p->next;
    }
    fclose(fp);
}

struct element *readfile(char *filename)
{
    FILE *fp;
    if((fp=fopen(filename,"r+")) == NULL)
    {
        printf("Error\n");
        exit(0);
    }
    struct element *head=NULL,*node=NULL,*end=NULL;
    node =(struct element*)malloc(sizeof(struct element));
    end=node;
    int n = 0;
    while(fscanf(fp,"%s",node->data)!=EOF)
    {
        n++;
        if(n==1)
        {
            head=node;
        }
        else
        {
            end->next=node;
        }
        end=node;
        node =(struct element*)malloc(sizeof(struct element));
    }
    end->next = NULL;
    return head;
}

