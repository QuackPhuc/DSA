#include<iostream>
using namespace std;

struct Node
{
    int value = 0;
    Node * next = NULL;
};


//h(k) = ((a*k+b)%p)%m ; a,b in (0;p-1)
struct Hash
{
    Node *Table;
    int a = 100;
    int b = 0;
    int p = 97;
    int m = 0;

    void build(int a = 100, int b = 0, int p = 97, int m = 0)
    {
        Hash::a = a;
        Hash::b = b;
        Hash::p = p;
        Hash::m = m;
        set_default();
        if(m != 0)
            Table = new Node[m];
    }
    void set_default()
    {
        if(a == 0)
            a = 100;
        if(p == 0)
            p = 97;
        Table = new Node[p];
    }
    void info()
    {
        cout<<"(("<<a<<"k + "<<b<<") % "<<p<<" ) % "<<m<<endl;
    }
    bool isEmpty(int index)
    {
        return Table[index].value == 0;
    }
    
    void add(int k)
    {
        int index = 0;
        if(m != 0)
        {
            index = ((a*k + b) % p) % m;
        }
        else
        {
            index = (a*k + b) % p;
        }
        if (isEmpty(index))
        {
            Table[index].value = k;
            return;
        }
        Node *Next = &Table[index];
        while(Next -> next != nullptr)
        {
            Next = Next -> next;
        };
        Node *node = new Node;
        node -> value = k;
        Next -> next = node;
    }

    void printShell(int index)
    {
        if(isEmpty(index))
        {
            cout<<"None";
            return;
        }
        Node *Next = Table[index].next;
        cout<<Table[index].value;
        while(Next != NULL)
        {
            cout<<" -> "<<Next->value;
            Next = Next -> next;
        }
    }
};

int main()
{
    struct Hash cc;
    cc.build(11,4,9,0);
    cc.info();
    //int array[7] = {67, 13, 49, 24, 40, 33, 58};
    /*for(int i = 0; i < 9; i++)
    {
        cc.add(array[i]);
    }*/
    cc.add(67);
    cc.add(13);
    cc.add(49);
    cc.add(24);
    cc.add(40);
    cc.add(33);
    cc.add(58);
    for(int i = 0; i < cc.p; i++)
    {
        cc.printShell(i);
        cout<<endl;
    }
    return 0;
}