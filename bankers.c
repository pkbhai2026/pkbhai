#define true 1
#define false 0
#include <ctype.h>
#include <stdio.h>
int avail[4], work[10];
int max[5][4];
int alloc[5][4];
int need[5][4], finish[10], req[10];
int safeseq[10], ssi = -1;
int m = 3;
int n = 5;
int i, j;
void get_alloc_state();
void print_safess();
void get_alloc_request();
void main()
{
    get_alloc_state();
}
void get_alloc_state()
{
    printf("\n Total number of resource type: %d", m);
    printf("\n Total number of processes: %d", n);
    int choice = 0;
    while (choice != 8)
    {
printf("\n1. Accept available\n2. Display allocation and 
max\n3. Display the contents of need matrix\n4. Display available\n5. 
Accept request for a process\n6. Safety algorithm\n7. Resources request 
algorithm\n8. Exit\nEnter choice : ");
scanf("%d", &choice);
switch(choice) {
        case 1:
            printf("\n Enter available:");
            for (j = 0; j < m; j++)
            {
                scanf("%d", &avail[j]);
            }
printf("\n Enter maximun demand by each 
proces\n");
for(i=0;i<n;i++)
{
                printf("Process %d: ", i);
                for (j = 0; j < m; j++)
                    scanf("%d", &max[i][j]);
}
printf("\n\n Enter allocation by each process\n");
for(i=0;i<n;i++)
{
                printf("Process %d: ", i);
                for (j = 0; j < m; j++)
                    scanf("%d", &alloc[i][j]);
}
break;
case 2 :
printf("\n Maximum demand by each process\n");
for(i=0;i<n;i++)
{
                printf("Process %d: ", i);
                for (j = 0; j < m; j++)
                    printf("%d\t", max[i][j]);
                printf("\n");
}
printf("\n\n Allocation by each process\n");
for(i=0;i<n;i++)
{
                printf("Process %d: ", i);
                for (j = 0; j < m; j++)
                    printf("%d\t", alloc[i][j]);
                printf("\n");
}
break;
case 3 :
printf("\n\n Need by each process\n");
for(i=0;i<n; i++)
{
                printf("Process %d: ", i);
                for (j = 0; j < m; j++)
                {
                    need[i][j] = max[i][j] - alloc[i][j];
                    printf("%4d", need[i][j]);
                }
                printf("\n");
}
break;
case 4 :
printf("\nAvailable: ");
for(j=0; j<m;j++)
{
                printf("%d\t", avail[j]);
}
break;
case 5 :
printf("\n\nRequest of Process number ? "); 
scanf("%d", &i);
printf("\n Enter Request : ");
for(j=0; j<m; j++)
scanf ("%d",&req[j]);
break;
case 7 :
if(safe_state()) {
printf("\n Given system is in safe 
state...");
ssi = ssi / 2;
print_safess();
} else {
printf("\n Given system is not in safe 
state...");
get_alloc_request();
ssi=-1;
if(safe_state())
{
printf("\n system will be in safe state 
after request...");
print_safess();
}
else
{
printf("\n System will not be in safe 
state after request...");
printf("\n Allocation state is 
undone... ");
printf("\n Process requesting should 
wait ...");
}
}
break;
case 6 :
if(safe_state()) {
printf("\n Given system is in safe 
state...");
print_safess();
}
break;
case 8 :
choice = 8;
break;
default :
printf("Enter valid choice!");
}
    }
}
safe_state() // safety algo
{
    int found;
    for (j = 0; j < m; j++)
        work[j] = avail[j];
    for (i = 0; i < n; i++)
        finish[i] = false;
    printf("\n\n Check of safe state...");
    do
    {
        found = false;
        for (i = 0; i < n; i++)
        {
            if (finish[i] == false && need_lte_work(i))
            {
                printf("\n Selected process %d", i);
                finish[i] = true;
                for (j = 0; j < m; j++)
                    work[j] = work[j] + alloc[i][j];
                safeseq[++ssi] = i;
                found = true;
            }
        }
        if (found == false)
        {
            for (i = 0; i < n; i++)
                if (finish[i] == false)
                    return (false);
            return (true);
        }
    } while (1);
}
need_lte_work(int i)
{
    for (j = 0; j < m; j++)
    {
        if (need[i][j] > work[j])
            return (false);
    }
    return (true);
}
void print_safess()
{
    printf("\n\n Safe sequence : ");
    for (i = 0; i <= ssi; i++)
        printf("%4d ", safeseq[i]);
}
void get_alloc_request() // resource request algo
{
    if (!req_lte_need(i))
    {
        printf("\n Process requested more than its max claim..");
    }
    if (!req_lte_avail(i))
    {
printf("\n Resources are not available.Process %d should 
wait..",i);
    }
    for (j = 0; j < m; j++)
    {
        alloc[i][j] += req[j];
        need[i][j] -= req[j];
        avail[j] -= req[j];
    }
}
req_lte_need(int i)
{
    for (j = 0; j < m; j++)
    {
        if (req[j] > need[i][j])
            return 0;
    }
    return 1;
}
req_lte_avail()
{
    for (j = 0; j < m; j++)
    {
        if (req[j] > avail[j])
            return 0;
    }
    return 1;
}