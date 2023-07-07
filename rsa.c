#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "rsa.h"

/*void main()
{
    printf("\nENTER FIRST PRIME NUMBER\n");
    scanf("%d",&p);
    flag=prime(p);
    if(flag==0)
    {
        printf("\nWRONG INPUT\n");
        exit(1);
    }
    printf("\nENTER ANOTHER PRIME NUMBER\n");
    scanf("%d",&q);
    flag=prime(q);
    if(flag==0||p==q)
    {
        printf("\nWRONG INPUT\n");
        exit(1);
    }
    printf("\nENTER MESSAGE\n");
    fflush(stdin);
    scanf("%s",msg);
    for(i=0;msg[i]!=NULL;i++)
        m[i]=msg[i];
    n=p*q;
    t=(p-1)*(q-1);
    ce();
    printf("\nPOSSIBLE VALUES OF e AND d ARE\n");
    for(i=0;i<j-1;i++)
        printf("\n%ld\t%ld",e[i],d[i]);
    encrypt();
    decrypt();
}*/
int prime(long int pr)
{
    int i;
    j=sqrt((double)pr);
    for(i=2;i<=j;i++)
    {
        if(pr%i==0)
            return 0;
    }
    return 1;
}
void ce()
{
    int k;
    k=0;
    for(i=2;i<t;i++)
    {
        if(t%i==0)
            continue;
        flag=prime(i);
        if(flag==1&&i!=p&&i!=q)
        {
            e[k]=i;
            flag=cd(e[k]);
            if(flag>0)
            {
                d[k]=flag;
                k++;
            }
            if(k==99)
                break;
        }
    }
}

long int cd(long int x)
{
    long int k=1;
    while(1)
    {
        k=k+t;
        if(k%x==0)
            return(k/x);
    }
}

void encrypt()
{
    long int plain_text, cipher_text, key=e[0], k;
    srand(time(NULL)); // Seed the random number generator
    for (int idx = 0; idx != MSG_SIZE; idx++)
    {
        plain_text = msg[idx];
        plain_text = plain_text - 96;
        plain_text &= 0xff;
        //printf("pt %d \n", plain_text);
        //long int random_value = rand();
        //random_value = random_value << 0x10;
        //printf("rand %d \n", random_value);
        //plain_text += random_value;

        //printf("pt2 %d \n", plain_text);

        k = 1;
        for(j=0;j<key;j++)
        {
            k=k * plain_text;
            k=k % n;
        }
        temp[idx] = k;
        cipher_text = k + 96;
        en[idx] = cipher_text;

    }
}

void decrypt()
{
    long int plain_text, cipher_text, key=d[0], k;
    
    for (int idx = 0; idx != MSG_SIZE; idx++)
    {
        cipher_text=temp[idx];
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*cipher_text;
            k=k%n;
        }
        plain_text = k;
        plain_text &= 0xff;
        plain_text += 96;
        m[idx] = plain_text;
    }
}