// #include<iostream>
// #include<functional>

// template <typename T>
// using funcAdd = std::function<T(T L, T R)>;

// template <typename T>
// T func(funcAdd<T> add,T a,T b)
// {
//     return add(a,b);
// }

// int ADD(int a,int b)
// {
//     return a + b;
// }

// int main(){

//     std::cout << (func<int>(ADD,1,2 ))<< std::endl;
//     return 0;
// };

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

Node *start()

{
    int x;
    Node *one = (Node *)malloc(sizeof(Node)), *p, *wei;
    one->next = NULL;
    wei = one;
    scanf("%d", &x);
    while (x != 0)
    {
        p = (Node *)malloc(sizeof(Node));
        wei->next = p;
        p->next = NULL;
        wei = p;
        scanf("%d", &x);
    }
    return one;
}

Node *search(Node *L, int i)
{
    Node *p = L;
    int x = 1;
    while (p->next != NULL && x < i)
    {
        p = p->next;
        x++;
    }
    return p;
}
int main()
{
    int x;
    Node *p = start(), *b;
    scanf("%d", &x);
    b = search(p, x);
    printf("%d", b->data);
}