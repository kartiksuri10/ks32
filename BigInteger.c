#include "BigInteger.h"
struct BigInteger initialize(char *s)
{
    struct BigInteger num;
    num.l=NULL;
    num.length=0;
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]<'0'||s[i]>'9')
        {
            printf("INVALID INPUT");
            exit(1);
        }
        int digit=s[i]-'0';
        struct node *temp=(struct node*)malloc(sizeof(struct node));
        temp->data=digit;
        temp->next=num.l;
        num.l=temp;
        num.length++;
    }
    return num;
}

void display(struct BigInteger a)
{
    struct node *temp=a.l;
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        temp=temp->next;
    }
}

struct node* reverse(struct node*head)
{
    struct node*back=NULL,*front=NULL,*current=head;
    while(current!=NULL)
    {
        front=current->next;
        current->next=back;
        back=current;
        current=front;
    }
    return back;
}

void insertNode(struct node **head, int val) 
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode) 
    {
        printf("Memory Allocation Failed!!!");
        exit(1);
    }
    newNode->data = val;
    newNode->next = *head;
    *head = newNode;
}

int compare(struct BigInteger *num1,struct BigInteger *num2)
{
   
    //it would return 1 if n2 is greater otherwise 0
    if(num2->length>num1->length)
    {
        return 1;
    }
    else if(num2->length==num1->length)
    {
        int return_val=0;
        num1->l= reverse(num1->l);
        num2->l= reverse(num2->l);
        struct node*l1=num1->l,*l2=num2->l;
        while(l1!=NULL && l2!=NULL)
        {
            if(l2->data>l1->data)
            {
                return_val= 1;
                break;
            }
            else if(l1->data<l2->data)
            {
                return_val= 0;
                break;
            }
            l1=l1->next;
            l2=l2->next;
        }
        num1->l= reverse(num1->l);
        num2->l= reverse(num2->l);
        return return_val;
    }
    return 0;
}

struct BigInteger add(struct BigInteger a,struct BigInteger b)
{
    if(!a.l)
    return b;
    if(!b.l)
    return a;

    struct BigInteger result;
    result.l=NULL;
    result.length=0;

    int carry=0;
    struct node *ia=a.l,*ib=b.l;
    while(ia!=NULL || ib!=NULL || carry!=0)
    {
        int sum=carry;
        if(ia!=NULL)
        {
            sum+=ia->data;
            ia=ia->next;
        }
        if(ib!=NULL)
        {
            sum+=ib->data;
            ib=ib->next;
        }

        carry=sum/10;
        sum=sum%10;

        struct node *temp=(struct node*)malloc(sizeof(struct node));
        temp->data=sum;
        temp->next=result.l;
        result.l=temp;
        result.length++;
    }
    return result;
}

struct BigInteger sub(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger result;
    result.l = NULL;
    result.length = 0;
    int borrow=0;
    int flag=0;
    if(compare(&a,&b))
    {
        flag=1;
        struct BigInteger temp=a;
        a=b;
        b=temp;
    }
    struct node *ia=a.l,*ib=b.l;
    while(ia || ib)
    {
        int na=(ia!=NULL)?ia->data:0;
        int nb=(ib!=NULL)?ib->data:0;
        int diff=na - nb - borrow;
        if(diff<0)
        {
            diff+=10;
            borrow=1;
        }
        else
            borrow=0;
        struct node *temp=(struct node*)malloc(sizeof(struct node));
        if(!temp)
        {
            printf("Memory Allocation Failed!!!");
            exit(1);
        }
        temp->data=diff;
        temp->next=result.l;
        result.l=temp;
        result.length++;

        if(ia) ia=ia->next;
        if(ib) ib=ib->next;
    }
    if(flag)
    {
        struct node *itr=result.l;
        itr->data=(-1)*(itr->data);
    }
    return result;
}

struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{
//     if(!a.l || !b.l)return NULL;
    struct BigInteger res;
    res.l=NULL;
    res.length=0;
    struct node *ia=a.l,*ib=b.l;
    int carry=0,i=0;
    while(ib!=NULL){
        ia=a.l;
        struct BigInteger p;
        p.l=NULL;
        p.length=0;
        carry=0;
        for(int j=0;j<i;j++){
            insertNode(&p.l,0); //adding zeroes
            p.length++;
        }
        while(ia!=NULL){
            int product=(ia->data)*(ib->data)+carry;
            carry=product/10;
            insertNode(&p.l, product%10 );
            ia=ia->next;
            p.length++;   // printf("test: %d\n",product%10);
        }
        if(carry>0){
            insertNode(&p.l,carry);
            p.length++;
        }
        i++;
        p.l = reverse(p.l);
        if(i>2){
            res.l = reverse(res.l);
            
        }res=add(res,p);
        ib=ib->next;
    }
    return res;
}

struct BigInteger div1(struct BigInteger a, struct BigInteger b) 
{
    
}