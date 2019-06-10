#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define max_nodes 100

struct btree
{
	int data;
	struct btree *left,*right;
};

struct queue
{
	struct btree *nodes[max_nodes];
	int f,r;
};

void enque(struct queue *que, struct btree *root)
{
	que->nodes[++que->r] = root;
}

struct btree* deque(struct queue *que)
{
	return que->nodes[que->f++];
}

int is_empty(struct queue *que)
{
	if(que->r+1 == que->f || que->r==-1)
		return 0;
	else
		return 1;
}

struct queue * create_queue()
{
	struct queue *que = NULL;
	que = (struct queue*)malloc(sizeof(struct queue));
	que->r=-1;
	que->f=0;
	return que;
}

struct btree * create_node(int data)
{
	struct btree *root = (struct btree*)malloc(sizeof(struct btree*));
	root -> data = data;
	root -> left = NULL;
	root -> right = NULL;	
	return root;
}

struct btree* insert_node(struct btree* root,int data)
{
	struct btree *node = NULL; 
	struct btree *new_node = create_node(data);

	if(root == NULL)
	{
		root = new_node;
	}
	else
	{
		struct queue *que = create_queue();
		enque(que,root);
		while(is_empty(que))
		{
			node = deque(que);
			
			if(node->left)
				enque(que,node->left);

			if(node->right)
				enque(que,node->right);

			if(node->left == NULL){
				node->left = new_node;
				que->r=-1;
			}

			else if(node->right == NULL){
				node->right = new_node;
				que->r=-1;
			}
		}
	}
	return root;
}

void preorder_traversal(struct btree* root)
{
	if(root)
	{
		printf("%d -> ",root->data);
		preorder_traversal(root->left);
		preorder_traversal(root->right);	
	}
}

void inorder_traversal(struct btree* root)
{
	if(root)
	{
		inorder_traversal(root->left);
		printf("%d -> ",root->data);
		inorder_traversal(root->right);	
	}
}

void postorder_traversal(struct btree* root)
{
	if(root)
	{
		postorder_traversal(root->left);
		postorder_traversal(root->right);	
		printf("%d -> ",root->data);
	}
}

int find_max(struct btree* root)
{
	int max=INT_MIN,left,right,root_val;
	if(root)
	{
		root_val = root->data;
		left = find_max(root->left);
		right = find_max(root->right);

		if(left > right)
			max = left;
		else
			max = right;
		if(root_val > max)
			max = root_val;
	}
	return max;
}

int find_tree_size(struct btree *root)
{
	if(root == NULL)
		return 0;
	else
		return (find_tree_size(root->left) + 1 + find_tree_size(root->right));
}

int find_tree_height(struct btree* root)
{
	int left_len, right_len;

	if(root == NULL)
		return 0;
	else
	{
		left_len = find_tree_height(root->left);
		right_len = find_tree_height(root->right);

		if(left_len > right_len)
			return (left_len+1);
		else
			return (right_len+1);
	}
}

struct btree * delete_node(struct btree *root, int del_data)
{
	int save_data;
	struct btree *node = NULL; 
	struct btree *del_node = NULL; 
	struct btree *find_node = NULL; 
	struct queue *que = create_queue();

	if(root == NULL)
	{
		printf("%s\n","Tree is empty");
	}
	else if(root->left == NULL && root->right == NULL)
	{
		printf("%s %d\n","Element deleted = ",root->data);
		root = NULL;
	}	
	else
	{
		enque(que,root);
		while(is_empty(que))
		{
			node = deque(que);
			if(node->data == del_data)
			{
				find_node = node;
			}
			if(node->left)
				enque(que,node->left);

			if(node->right)
				enque(que,node->right);
		}
		save_data = node->data;
		//que -> r = -1;
		//que -> f = 0; 
		
		struct queue *que = create_queue();
		enque(que,root);
		while(is_empty(que))
		{
			del_node = deque(que);
			if(del_node == node)
			{
				del_node = NULL;
				que -> r = -1;
				free(del_node);
				break;
			}
			else if(del_node->left == node)
			{
				del_node -> left = NULL;
				que -> r = -1;
				free(del_node->left);
				break;
			}
			else if(del_node->right == node)
			{
				del_node -> right = NULL;
				que -> r = -1;
				free(del_node->right);
				break;
			}

			if(del_node->left)
				enque(que,del_node->left);

			if(del_node->right)
				enque(que,del_node->right);
		}

		if(find_node == NULL)
			printf("%s\n","Element not found");
		else
		{
			printf("%s %d\n","Element deleted = ",find_node->data);
			find_node->data = save_data;
		}
	}
	return root;
}

void print_path(int path[], int path_len)
{
	int i;
	for(i=0;i<path_len;i++)
		printf("%d ",path[i]);
	printf("\n");
}

void root_to_leaf_path(struct btree *root, int path[], int path_len)
{
	if(!root)
		return;
	path[path_len++] = root -> data;
	if(root->left == NULL && root->right == NULL)
		print_path(path,path_len);
	else
	{
		root_to_leaf_path(root->left, path, path_len);
		root_to_leaf_path(root->right, path, path_len);
	}

}


void display_nodes(struct btree* root)
{
	struct btree *node = NULL; 
	struct queue *que = create_queue();
	if(root == NULL)
	{
		printf("%s\n","Tree is empty");
	}
	else
	{	
		enque(que,root);
		while(is_empty(que))
		{
			node = deque(que);
			printf("%d\n",node->data);
			if(node->left)
				enque(que,node->left);

			if(node->right)
				enque(que,node->right);
		}
	}
}

int main()
{
	struct btree *root = NULL;
	int data, option, del_data;

	do
    {
    	printf("%s\n","enter an option 0.exit 1.insert_node 2.delete_node 3.preorder_traversal 4.inorder_traversal 5.postorder_traversal 6.find_max 7.find_tree_size 8.find_tree_height 9.root_to_leaf_path 10.display_nodes ");
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
                break;
            }

            case 3:
            {
                preorder_traversal(root);
                break;
            }

            case 4:
            {
                inorder_traversal(root);
                break;
            }

            case 5:
            {
                postorder_traversal(root);
                break;
            }

            case 6:
            {
                printf("max val = %d\n", find_max(root)); 
                break;
            }

            case 7:
            {
                printf("Binary tree size = %d\n", find_tree_size(root)); 
                break;
            }

            case 8:
            {
                printf("Height of Binary tree = %d\n", find_tree_height(root)); 
                break;
            }

            case 9:
            {
            	int path[max_nodes],path_len=0;
                root_to_leaf_path(root, path, path_len);
                break;
            }

            case 10:
            {
                display_nodes(root);
                break;
            }

        }
    }while(option!=0);
    
	return 0;
}
