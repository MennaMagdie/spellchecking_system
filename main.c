#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node
{
    char data[100];
    struct node *left, *right;
} node;

node *newNode(char word[100])
{
    node *n = malloc(sizeof(node));
    strcpy(n->data,word);
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
    return root;
}

void displayTree(node* root)
{
    if(root)
    {
        displayTree(root->left);
        printf("%s  ",root->data);
        displayTree(root->right);
    }
}

int getHeight(node* root)
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        int left_height = getHeight(root->left);
        int right_height = getHeight(root->right);
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

node* getSuggestions(node *root, char *str)
{

    if(root)
    {
        if((strcasecmp(root->left->data,str) > 0)&&(strcasecmp(root->right->data,str) > 0))
            return root;
        else if((strcasecmp(root->left->data,str) < 0)&&(strcasecmp(root->right->data,str) < 0))
            return root;
        else if(strcasecmp(root->data,str) > 0)
            return getSuggestions(root->left, str);
        else
            return getSuggestions(root->right, str);
    }
    else
        return NULL;
}

void wordCheck(node *root,char *str)
{
    node *n = search(root,str);
    if(strcasecmp(n->data,str) == 0)
        printf("%s - CORRECT\n",str);
    else
    {
        n = getSuggestions(root,str);
        printf("INCORRECT WORD\n");
        printf("Suggestion: %s",n->data);
        //       inorderPredecessor(root,n), inorderSuccessor(root,n));
    }
}

int main()
{
    int nodes_num=0;
    node *root=NULL;
    FILE *f;
    f = fopen("EN-US-Dictionary.txt","r");

    if(f)
    {
        while(!feof(f))
        {
            char word[100];
            fscanf(f,"%s",word);
            root = insert(root,word);
            nodes_num++;
            //printf("%s  ",word);
        }
        printf(" Dictionary loaded successfully!\n\n");
        fclose(f);
    }
    else
        printf("FILE NOT FOUND.");
    printf(" Size (nodes) = %d\n",nodes_num);
    printf(" Height (levels) = %d\n",getHeight(root));
    printf("-------------------------------------\n");

    displayTree(root);
    wordCheck(root,"wrot");
    //printf("\nword = %s",search(root,"torpedo")->data);


    return 0;
}
