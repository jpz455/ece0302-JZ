
#include "binary_search_tree.hpp"

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& rhs)
{
    root = 0;
    Node<KeyType, ItemType>** lhs = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.rhs = rhs.root;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ItemType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        temp->left = 0;
        temp->right = 0;
        *curr_lhs = temp;

        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}


template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(BinarySearchTree<KeyType, ItemType> rhs)
{
    swap(rhs);
    return *this;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::swap(BinarySearchTree<KeyType, ItemType>& rhs)
{
    std::swap(root, rhs.root);
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}


template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != 0) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = 0;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item)
{
    
    //check that tree is empty and make a root node if so
     if (isEmpty()) {

        root = new Node<KeyType, ItemType>;
        root->key = key;
        root->data = item;
        return true;

    }
    //otherwise we have to search for the spot to insert the new item
    else{

    Node<KeyType, ItemType>* node1;          
    Node<KeyType, ItemType>* node2;   
    search(key, node1, node2);   //using the search method   

    //this will return if the node already exists within the tree therefore it will not add the new one
    if (node1->key == key) { 
        node1=nullptr;
        node2=nullptr; //have to deallocate the memory to avoid leaks            
        return false;                     

    } 
    //if the tree isnt empty, doesnt already contain the item, we have to perform the insertion at the right spot
    else { 
        //create a node to add the item to the tree and provide the given information                         
        Node<KeyType, ItemType>* tempNode = new Node<KeyType, ItemType>;
        
        tempNode->key = key;                
        tempNode->data = item;              

        //perform insertion
        if (key < node1->key) {             
            node1->left = tempNode;           
        } else {                          
            node1->right = tempNode;          
        }
        }

    return true; //success!
    }
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == 0);
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item)
{
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    if (curr == 0)
        return false;

    if (curr->key == key) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{   
    //check that tree is empty/cannot remove from an empty tree
      if (isEmpty())
        return false;

    //otherwise search for where the removal will take place
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* parent;
    search(key, curr, parent);

    //key was not found therefore cannot remove the key
    if (curr == nullptr)  
        return false;


    // Case 1: Node has no children
    if (curr->left == nullptr && curr->right == nullptr) {
        if (parent == nullptr) {//remove a root
            delete root;
            root = nullptr;
        } else if (parent->left == curr) {//remove left child of parent
            delete parent->left;
            parent->left = nullptr;
        } else {
            delete parent->right;//remove right child of parent
            parent->right = nullptr;
        }
        return true;
    }

    // Case 2: Node has one child have to check left and right children
    if (curr->left == nullptr || curr->right == nullptr) {
        Node<KeyType, ItemType>* child = nullptr;
        if (curr->left != nullptr) { //determining which child exists
          child = curr->left;
        } else {
          child = curr->right;
        }
        if (parent == nullptr) { //node to remove is root 
            root = child;
        } else if (parent->left == curr) {//node to remove is left child
            parent->left = child;
        } else {
            parent->right = child; //node to remove is right child
        }
        delete curr; //deallocate
        return true;
    }

    // Case 3: Node has two children
    Node<KeyType, ItemType>* successorParent = curr;
    Node<KeyType, ItemType>* successor = curr->right; //initialize as right child
    inorder(successor, successor, successorParent);  // find inorder successor

    // copying data for current node
    curr->key = successor->key;
    curr->data = successor->data;

    // Remove the successor node from position 
    if (successorParent->left == successor) {
        successorParent->left = successor->right; //successor right subtree added to parent
    } else {
        successorParent->right = successor->right; //successor left subtree added to parent
    }
    delete successor; //deallocate
    return true;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
    Node<KeyType, ItemType>*& in, Node<KeyType, ItemType>*& parent)
{
   //find leftmost node
    while (curr->left != nullptr) {
        //assign to parent
        parent = curr;
        //move to left child
        curr = curr->left;
    }
    //inorder successor will now point to the leftmost node
    in = curr;

}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::search(KeyType key,
    Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& parent)
{
    curr = root;
    parent = 0;

    if (isEmpty())
        return;

    while (true) {
        if (key == curr->key) {
            break;
        } else if (key < curr->key) {
            if (curr->left != 0) {
                parent = curr;
                curr = curr->left;
            } else
                break;
        } else {
            if (curr->right != 0) {
                parent = curr;
                curr = curr->right;
            } else
                break;
        }
    }
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(KeyType arr[], int size) {
    // TODO: check for duplicate items in the input array

    // TODO: use the tree to sort the array items

    // TODO: overwrite input array values with sorted values
}