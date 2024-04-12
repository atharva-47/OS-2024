#include<stdio.h>
#include<math.h>

void current_differences(int request[],int n,int head, int diff[][2])
{
    int i;
    for(i=0;i<n;i++)
        diff[i][0] = abs(request[i] - head);
}

int min_difference(int diff[][2],int n)
{
    int i,loc = -1;
    int min = 9999;

    for(i=0;i<n;i++)
        {
            if(diff[i][0]<=min && diff[i][1]!=1)
                {
                    min = diff[i][0];
                    loc = i;
                }
        }
    return loc;
}

int sstf(int request[],int n,int head,int sequence[])
{
    int diff[100][2] = {0};
    int i,cnt = 0,loc;
    
    for(i=0;i<n;i++)
        {
            sequence[i] = head;

            current_differences(request,n,head,diff);
            loc = min_difference(diff,n);
            diff[loc][1] = 1;

            cnt += diff[loc][0];

            head = request[loc];
        }
    sequence[n] = head; 

    return cnt;
}


int main()
{
    int i,n,request[100],head,sequence[100]={0},seek_cnt;

    printf("\nEnter number of disk blocks:");
    scanf("%d",&n);

    printf("\nEnter disk request string:");
    for(i=0;i<n;i++)
        scanf("%d",&request[i]);

    printf("\nEnter current head position:");
    scanf("%d",&head);

    seek_cnt = sstf(request,n,head,sequence);

    printf("\nSeek Sequence\n");
    for(i=0;i<=n;i++)
        printf("%d ",sequence[i]);

    printf("\nTotal Number of head movement : %d",seek_cnt);

    return 0;
}