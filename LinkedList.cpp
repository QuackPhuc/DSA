#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next = NULL;
    
    Node() : data(NULL) {};
    Node(int data) :data(data) {};
};

struct LinkedList{
    Node* head;
    Node* tail;
    LinkedList() : head(nullptr),tail(nullptr) {};
    
    LinkedList(int array[], int size){
        head = new Node(array[0]);
        Node *node = head;
        for(int i = 1; i < size; i++){
            Node *newNode = new Node(array[i]);
            node -> next = newNode;
            node = newNode;
        }
        tail = node;
    }
    
    void add(Node *node){
        if(!head){
            head = node;
            tail = node;
            return;
        }
        node -> next = head;
        head = node;
    }
    
    void append(Node *node){
        if(!head){
            head = node;
            tail = node;
            return;
        }
        tail -> next = node;
        tail = node;
    }
    
    void addbeforeNode(Node *node, Node *newNode){
        Node *p = head;
        if(!node) return;
        while(p -> next && p -> next != node){
            p = p -> next;
        }
        if(!p) return;
        p -> next = newNode;
        newNode -> next = node;
    }
    
    void input(){
        bool conti = true;
        while(conti){
            conti = false;
            Node *node = new Node();
            cout<<"Data = ";
            cin>>node -> data;
            append(node);
            cout<<endl<<"Continue?(1/0)";
            cin>>conti;
        }
    }
    
    void output(){
        Node *node = head;
        while(node){
            cout<<node -> data<<" ";
            node = node -> next;
        }
    }
    
    Node *search(int key){
        Node *node = head;
        while(node && node -> data != key){
            node = node -> next;
        }
        if(!node) return nullptr;
        return node;
    }
    
    void removeEntry(int key){
        Node *node = head;
        if(head -> data == key){
            head = head -> next;
        }
        
        while(node -> next && node -> next -> data != key){
            node = node -> next;
        }
        
        if(!node -> next) return;
        node -> next = node -> next -> next;
    }
};

int main(){
    int array[5] = {1,2,4,5};
    int n = sizeof(array)/sizeof(int);
    LinkedList LL = LinkedList(array, n);    
    LL.output();
    LL.input();
    LL.add(new Node(100));
    LL.append(new Node(1000));
    LL.addbeforeNode(LL.search(3), new Node(300));
    LL.removeEntry(1000);
    LL.output();
}


