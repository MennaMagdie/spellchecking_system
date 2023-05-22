#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    char data[100];
    struct node *left, *right;
}node;

node *newNode(char word[100])
{
    node *n = malloc(sizeof(node));
    strcpy(n->data,word);//n->data = word;
    n->left = n->right = NULL;
    return n;
}

node *insert(node *root, char x[100])
{
    if(root == NULL)
    {
        node *n = newNode(x);
        root = n;
    }
    else
    {
        if(strcasecmp(root->data,x) > 0)
            root->left = insert(root->left, x);
        else if(strcasecmp(root->data,x) < 0)
            root->right = insert(root->right, x);
    }
    return root; //eh lazmetha?
}

void display_inorder(node* root)
{
    if(root)
    {
        display_inorder(root->left);
        printf("%s  ",root->data);
        display_inorder(root->right);
    }
}


int main()
{
    int i=0;
    node *root=NULL;
    FILE *f;
    f = fopen("EN-US-Dictionary.txt","r");
    if(f!=NULL)
    {
        while(!feof(f))
        {
    char word[100];
    fscanf(f,"%s",word);
    root = insert(root,word);
    i++;
    //printf("%s  ",word);
        }
        printf("\n");
    fclose(f);
    }
    else
        printf("FILE NOT FOUND.");
        printf("number of nodes = %d\n",i);
        //printf("number of levels = %.0f\n",ceil(log2(i))+1);//ceil(log2(n+1))
    display_inorder(root);


    return 0;
}
