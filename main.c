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

long height(node* root) {
    if (root == NULL) {
        return -1;
    } else {
        int left_height = height(root->left);
        int right_height = height(root->right);
        return 1+(left_height > right_height ? left_height : right_height);
    }
}

node *search(node *root, char value[100])
{
    if(root)
    {
        if(strcasecmp(root->data,value) == 0)
            return root;
        else if(strcasecmp(root->data,value) > 0)
            return search(root->left, value);
        else
            return search(root->right, value);
    }
    else
        return NULL;
}



int main()
{
    int nodes_num=0;
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
    nodes_num++;
    //printf("%s  ",word);
        }
        printf("Dictionary loaded successfully!\n");
    fclose(f);
    }
    else
        printf("FILE NOT FOUND.");
        printf("number of nodes = %d\n",nodes_num);
        printf("number of levels = %d\n",height(root));
    //display_inorder(root);

    printf("\nword = %s",search(root,"torpedo")->data);


    return 0;
}
