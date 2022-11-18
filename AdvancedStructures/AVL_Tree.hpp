#pragma once
#include <iostream>
#include <stack>

template <typename T>
class AVL_T{
private:

    struct Node{
        T value;
        Node* left;
        Node* right;
        int height;
        Node(const T& value) : value(value), left(nullptr), right(nullptr), height(0) {}
    };

    Node* _root;
    size_t _size;
    void (*_print)(const T&);
    bool (*_compare)(const T&,const T&);

private:

    void _leftRotation(Node*& node){
        Node* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        _setHeight(node);
        _setHeight(rightChild);
        node = rightChild;
    }

    void _rightRotation(Node*& node){
        Node* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        _setHeight(node);
        _setHeight(leftChild);
        node = leftChild;
    }

    void _setHeight(Node* node){
        node->height = std::max(_getHeight(node->left), _getHeight(node->right)) +1;
    }

    int _getHeight(Node* node){
        return (node)? node->height : -1;
    }

    void _balanceSubTree(Node*& node){

        int heightDifference = _getHeight(node->left) - _getHeight(node->right);

        if (heightDifference <= -2){ // unbalanced to the right
            if (node->right->right){
                _leftRotation(node);
            }

            else{
                _rightRotation(node->right);
                _leftRotation(node);
            }
        }
        else if (heightDifference >= 2){ // unbalanced to the left
            if (node->left->left){
                _rightRotation(node);
            }
            else{
                _leftRotation(node->left);
                _rightRotation(node);
            }
        }
    }
    

public:

    AVL_T(void (*print)(const T&), bool (*comparisonCriteria)(const T&,const T&)) : _root(nullptr), _size(0ll), _print(print), _compare(comparisonCriteria) {}

    ~AVL_T(){
        
        Node** temp_array = new Node*[_size];
        int current_index = 0;

        std::stack<Node*> aux;
        aux.push(_root);
        
        while(!aux.empty()){
            Node* node = aux.top();
            aux.pop();
            temp_array[current_index] = node;
            ++current_index;
            if (node->right)
                aux.push(node->right);
            if (node->left)
                aux.push(node->left);
        }

        for(int i = 0; i < current_index; i++){
            delete temp_array[i];
        }

        delete[] temp_array;
    }

    void PreOrder(){
        std::stack<Node*> aux;
        aux.push(_root);
        
        while(!aux.empty()){
            Node* node = aux.top();
            aux.pop();
            _print(node->value);
            if (node->right)
                aux.push(node->right);
            if (node->left)
                aux.push(node->left);
        }
    }

    void InOrder(){
        std::stack<Node*> stack;
        Node* current = _root;

        while (!stack.empty() || current != nullptr){
            
            while(current != nullptr){
                stack.push(current);
                current = current->left;
            }

            current = stack.top();
            stack.pop();

            _print(current->value);

            current = current->right;  
        }
    }

    void insert(const T& value){
        //When tree is empty
        if (!_root){
            _root = new Node(value);
            _size++;
            return;
        }
        
        std::stack<Node**> stack; //Here we are going to save teh path that we traverse to insert the node
        Node** aux = &_root;

        while (*aux != nullptr){

            if (_compare((*aux)->value, value)){
                stack.push(aux);
                aux = &((*aux)->left);
            }
            else{
                stack.push(aux);
                aux = &((*aux)->right);
            }
        }

        (*aux) = new Node(value);
        _size++;


        while(!stack.empty()){
            Node** lastNode = stack.top();
            stack.pop();
            _setHeight(*lastNode);
            _balanceSubTree(*lastNode);
        }
    }

    size_t Size(){
        return _size;
    }
    
    int TreeHeight(){
        return _getHeight(_root);
    }

    T getMin(){
        Node* aux = _root;
        while(aux->left){
            aux = aux->left;
        }
        return aux->value;
    }

    T getMax(){
        Node* aux = _root;
        while(aux->right){
            aux = aux->right;
        }
        return aux->value;
    }

};