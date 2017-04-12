#include "TreeNode.h"
#include "Student.h"
#include "Faculty.h"

using namespace std;

template <class T>
class BST
{
    private:
        TreeNode<T> *root;
        int size;

    public:
        BST()
        {
            root = NULL;
            size = 0;
        }

        ~BST(){};

        void insert(TreeNode<T> *node)
        {
            //TreeNode<T> *node = new TreeNode<T>(data);

            // TREE IS EMPTY
            if (root == NULL)
            {
                root = node;
            }

            else
            {
                TreeNode<T> *current = root; // STARTING POINT
                TreeNode<T> *parent; // FOR KEEPING TRACK OF WHO THE NEW PARENT WILL BE

                while (true)
                {
                    parent = current;

                    // GOING LEFT
                    if (node->key < current->key)
                    {
                        current = current->left;

                        // FOUND A LEAF
                        if (current == NULL)
                        {
                            parent->left = node;
                            break;
                        }
                    }

                    // GOING RIGHT
                    else
                    {
                        current = current->right;

                        // FOUND A LEAF
                        if (current == NULL)
                        {
                            parent->right = node;
                            break;
                        }
                    }
                }
            }

            size++;
        }

        bool isInTree(int k)
        {
            // EMPTY TREE
            if (root == NULL)
            {
                return false;
            }

            TreeNode<T> *current = root;

            // LOOK FOR NODE
            while (current->key != k)
            {
                // GOING LEFT
                if (k < current->key)
                {
                    current = current->left;
                }

                // GOING RIGHT
                else
                {
                    current = current->right;
                }

                // NODE NOT FOUND
                if (current == NULL)
                {
                    return false;
                }
            }

            return true;
        }

        T* search(int k)
        {
            if (isInTree(k))
            {
                TreeNode<T> *current = root;

                // LOOK FOR NODE
                while (current->key != k)
                {
                    // GOING LEFT
                    if (k < current->key)
                    {
                        current = current->left;
                    }

                    // GOING RIGHT
                    else
                    {
                        current = current->right;
                    }
                }

                return current->data;
            }

            else
            {
                return NULL;
            }
        }

        TreeNode<T>* getSuccessor(TreeNode<T> *n)
        {
            TreeNode<T> *successorParent = n;
            TreeNode<T> *successor = n;
            TreeNode<T> *current = n->right;

            while (current != NULL)
            {
                successorParent = successor;
                successor = current;
                current = current->left;
            }

            if (successor != n->right)
            {
                successorParent->left = successor->right;
                successor->right = n->right;
            }

            return successor;
        }

        bool deleteNode(int k)
        {
            // EMPTY TREE
            if (root == NULL)
            {
                return false;
            }

            TreeNode<T> *parent = root;
            TreeNode<T> *current = root;
            bool isLeft = true;

            // LOOK FOR NODE TO DELETE
            while (current->key != k)
            {
                parent = current;

                // GOING LEFT
                if (k < current->key)
                {
                    isLeft = true;

                    current = current->left;
                }

                // GOING RIGHT
                else
                {
                    isLeft = false;

                    current = current->right;
                }

                // NODE NOT FOUND
                if (current == NULL)
                {
                    return false;
                }
            }

            // IF WE GET HERE, WE FOUND NODE TO BE DELETED;
            // NOW WE CHECK OUR CASES

            // NO CHILDREN
            if (current->left == NULL && current->right == NULL)
            {
                // DELETING THE ROOT
                if (current == root)
                {
                    root = NULL;
                }

                else if (isLeft)
                {
                    parent->left = NULL;
                }

                else
                {
                    parent->right = NULL;
                }
            }

            // ONE CHILD, LEFT CHILD
            else if (current->right == NULL)
            {
                if (current == root)
                {
                    root = current->left;
                }

                else if (isLeft)
                {
                    parent->left = current->left;
                }

                else
                {
                    parent->right = current->left;
                }
            }

            // ONE CHILD, RIGHT CHILD
            else if (current->right == NULL)
            {
                if (current == root)
                {
                    root = current->right;
                }

                else if (isLeft)
                {
                    parent->left = current->right;
                }

                else
                {
                    parent->right = current->right;
                }
            }

            // TWO CHILDREN
            else
            {
                TreeNode<T> *successor = getSuccessor(current);

                if (current == root)
                {
                    root = successor;
                }

                else if (isLeft)
                {
                    parent->left = successor;
                }

                else
                {
                    parent->right = successor;
                }

                // LINK SUCCESSOR TO CURRENT'S LEFT CHILD
                successor->left = current->left;
            }

            size--;
            return true;
        }

        void print(TreeNode<T> *node)
        {
            if (node == NULL)
            {
                return;
            }

            print(node->left);
            cout << node->data << " | ";
            print(node->right);
        }

        void printTree()
        {
            print(root);
        }

        TreeNode<T>* getRoot()
        {
            return root;
        }

        int getSize()
        {
            return size;
        }

        bool isEmpty()
        {
            return (size == 0);
        }
};
