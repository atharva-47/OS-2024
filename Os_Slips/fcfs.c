#include<stdio.h>
#include<math.h>

int fcfs(int request[],int n, int head)
{
    int i,cnt=0;

    for(i=0;i<n;i++)
        {
           int moves = abs(head - request[i]);

            cnt += moves;

            head = request[i];
        }
    return cnt;
}


int main()
{
    int i,n,request[100],head,seek_cnt;

    printf("\nEnter number of disk blocks:");
    scanf("%d",&n);

    printf("\nEnter disk request string:");
    for(i=0;i<n;i++)
        scanf("%d",&request[i]);

    printf("\nEnter current head position:");
    scanf("%d",&head);

    printf("\nSeek Sequence in FCFS would be the same as requested array");
    printf("%d ",head);
    for(i=0;i<n;i++)
        printf("%d ",request[i]);

    seek_cnt = fcfs(request,n,head);
    
    printf("\nTotal number of head movement : %d",seek_cnt);

    return 0;
}