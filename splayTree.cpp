#include<stdio.h>
#include<stdlib.h>

// Tree node
typedef struct node No;
struct node
{
	int value;
	No *left, *right;
};

/* Helper function that allocates a new node with the given x. */
No* newNode(int x)
{
	No* node = new No();
	node->value = x;
	node->left = node->right = NULL;
	return (node);
}

// A utility function to right rotate subtree rooted with y
// Here, y shall emerge as root of the tree, while x (former root) becomes y's right child

No *zig(No *x)
{
	No *y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

// A utility function to left rotate subtree rooted with x
// Here, y shall emerge as root of the tree, while x (former root) becomes y's left child
No *zag(No *x)
{
	No *y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

// This function brings the value at root if value is present in tree.
// If value is not present, then it brings the last accessed item at
// root. This function modifies the tree and returns the new root
No *splay(No *root, int x)
{
	// Base cases: root is NULL or x is present at root
	if (root == NULL || root->value == x)
		return root;

	// X lies in left subtree
	if (root->value > x)
	{
		// X is not in tree, we are done
		if (root->left == NULL) return root;

		// Zig-Zig (Left Left)
		if (root->left->value > x)
		{
			// First recursively bring the x as root of left-left
			root->left->left = splay(root->left->left, x);

			// Do first rotation for root, second rotation is done after else
			root = zig(root);
		}
		else if (root->left->value < x) // Zig-Zag (Left Right)
		{
			// First recursively bring the x as root of left-right
			root->left->right = splay(root->left->right, x);

			// Do first rotation for root->left
			if (root->left->right != NULL)
				root->left = zag(root->left);
		}

		// Do second rotation for root
		return (root->left == NULL)? root: zig(root);
	}
	else // X lies in right subtree
	{
		// X is not in tree, we are done
		if (root->right == NULL) return root;

		// Zig-Zag (Right Left)
		if (root->right->value > x)
		{
			// Bring the x as root of right-left
			root->right->left = splay(root->right->left, x);

			// Do first rotation for root->right
			if (root->right->left != NULL)
				root->right = zig(root->right);
		}
		else if (root->right->value < x)// Zag-Zag (Right Right)
		{
			// Bring the x as root of right-right and do first rotation
			root->right->right = splay(root->right->right, x);
			root = zag(root);
		}

		// Do second rotation for root
		return (root->right == NULL)? root: zag(root);
	}
}

// Function to insert a new x k in splay tree with given root
No *insert(No *root, int x)
{
	// Simple Case: If tree is empty
	if (root == NULL) return newNode(x);

	// Bring the closest leaf node to root
	root = splay(root, x);

	// If x is already present, then return
	if (root->value == x) return root;

	// Otherwise allocate memory for new node
	No *newnode = newNode(x);

	// If root's x is greater, make root as right child
	// of newnode and copy the left child of root to newnode
	if (root->value > x)
	{
		newnode->right = root;
		newnode->left = root->left;
		root->left = NULL;
	}

	// If root's x is smaller, make root as left child
	// of newnode and copy the right child of root to newnode
	else
	{
		newnode->left = root;
		newnode->right = root->right;
		root->right = NULL;
	}

	return newnode; // newnode becomes new root
}



// The search function for Splay tree.  Note that this function
// returns the new root of Splay Tree.  If x is present in tree
// then, it is moved to root.
No *search(struct node *root, int x)
{
    root = splay(root, x);
    if (root->value == x){
    	printf("\n %d found at %p\n", root->value, root);
	}
	else{
		printf("\n %d not found\n", x);
	}
		return root;
}

// The delete function for Splay tree. Note that this
// function returns the new root of Splay Tree after
// removing the key
No* delete_x(No* root, int x)
{
    No* temp;
    if (root == NULL){
    	printf("\nRoot is empty.\n");
    	return NULL;
	}
    // Splay the given key
    root = splay(root, x);
  
    // If key is not present, then
    // return root
    if (x != root->value){
    	printf("\n%d isn't part of the tree.\n", x);
        return root;
	}   	 
    // If key is present
    // If left child of root does not exist
    // make root->right as root
    if (root->left == NULL) {
        temp = root;
        root = root->right;
    }
    // Else if left child exits
    else {
        temp = root;
        /*Note: Since key == root->key,
        so after Splay(key, root->lchild),
        the tree we get will have no right child tree
        and maximum node in left subtree will get splayed*/
        // New root
        root = splay(root->left, x);
  
        // Make right child of previous root as
        // new root's right child
        root->right = temp->right;
    }
    // free the previous root node, that is,
    // the node containing the key
    printf("\n%d deleted.\n", x);
    free(temp);
    // return root of the new Splay Tree
    return root;
}

// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(No *root)
{
	if (root != NULL)
	{
		printf("%d ", root->value);
		preOrder(root->left);
		preOrder(root->right);	
	}
}

/* Driver program to test above function*/
int main()
{
	No *root = NULL;
	
	root = insert(root, 20);
	root = insert(root, 13);
	root = insert(root, 14);
	root = insert(root, 22);
	
	printf("\nPreorder traversal of the modified Splay tree is \n");
	preOrder(root);
	printf("\n");
	
	root = search(root, 20);	//x will be found
	
	
	printf("\nPreorder traversal of the modified Splay tree is \n");
	preOrder(root);
	printf("\n");
	
	root = search(root, 40);	//x will not be found

	printf("\nPreorder traversal of the modified Splay tree is \n");
	preOrder(root);
	printf("\n");
	
	root = delete_x(root, 13);
	
	printf("\nPreorder traversal of the modified Splay tree is \n");
	preOrder(root);
	printf("\n");
	
	return 0;
}

