#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define max_nodes 100

struct bstree
{
	int data;
	struct bstree *left,*right;
};

struct bstree * create_node(int data)
{
	struct bstree *root = (struct bstree*)malloc(sizeof(struct bstree*));
	root -> data = data;
	root -> left = NULL;
	root -> right = NULL;	
	return root;
}

struct bstree* insert_node(struct bstree *root, int data)
{
	if(root == NULL)
	{
		root = create_node(data);
	}
	else
	{
		if(data < root -> data)
			root -> left = insert_node(root->left, data);
		else if(data > root -> data)
			root -> right = insert_node(root->right, data);
	}
	return root;
}

struct bstree* find_min(struct bstree *root)
{
	if(root == NULL)
		return NULL;
	else if(root->left == NULL)
		return root;
	else
		return(find_min(root->left));
}

struct bstree* find_max(struct bstree *root)
{
	if(root == NULL)
		return NULL;
	else if(root->right == NULL)
		return root;
	else
		return(find_max(root->right));
}

struct bstree* delete_node(struct bstree *root, int del_data)
{
	struct bstree * temp = NULL;

	if(root == NULL)
	{
		printf("%s\n","Tree is empty");
	}
	else if(del_data < root->data)
	{
		root->left = delete_node(root->left, del_data);
	}
	else if(del_data > root->data)
	{
		root->right = delete_node(root->right, del_data);
	}
	else
	{
		if(root->left && root->right)
		{
			temp = find_max(root->left);
			root->data = temp->data;
			root->left = delete_node(root->left,root->data);
		}
		else
		{
			temp = root;
			if(root->left == NULL)
				root = root->right;
			else if(root->right == NULL)
				root = root->left;
			free(temp);
		}
	}
	return root;
} 

void display_nodes(struct bstree* root)
{
	if(root)
	{
		display_nodes(root->left);
		printf("%d -> ",root->data);
		display_nodes(root->right);	
	}
}

int main()
{
	struct bstree *root = NULL;
	struct bstree *min_max = NULL;
	int data, option, del_data;

	do
    {
    	printf("%s\n","enter an option 0.exit 1.insert_node 2.delete_node 3.find_min 4.find_max 5.display_nodes ");
        scanf("%d",&option);

        switch(option)
        {
            case 1:
            {
            	printf("%s\n","enter a data element" );
                scanf("%d",&data);
                root = insert_node(root,data);
                break;
            }
            
            case 2:
            {
            	printf("%s\n","enter a data element to delete" );
                scanf("%d",&del_data);
                root = delete_node(root,del_data);
                printf("deleted_node = %d\n",del_data);
                break;
            }

            case 3:
            {
                min_max = find_max(root);
                printf("max data = %d\n", min_max->data);
                break;
            }

            case 4:
            {
                min_max = find_min(root);
                printf("min data = %d\n", min_max->data);
                break;
            }

            case 5:
            {
                display_nodes(root);
                break;
            }
        }
    }while(option!=0);
    
	return 0;
}
