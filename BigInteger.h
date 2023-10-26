#ifndef BigInteger_H
#define BigInteger_H
struct BigInteger {
    struct node *l;
    int length;
    //int sign;
};

struct node {
    int data;
    struct node *next;
};

struct BigInteger initialize(char *s);
void display(struct BigInteger a);
struct node* reverse(struct node* head);
void insertNode(struct node **head, int val);
int compare(struct BigInteger *num1, struct BigInteger *num2);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);

#endif