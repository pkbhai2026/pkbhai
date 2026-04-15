#include <stdio.h>
#include <stdlib.h>

int main()
{
    int RQ[100], i, j, n, TotalHeadMovement = 0, initial;
    int visited[100] = {0};
    int min, index, distance;

    printf("Enter the number of Requests\n");
    scanf("%d", &n);

    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
        scanf("%d", &RQ[i]);

    printf("Enter initial head position\n");
    scanf("%d", &initial);

    // Logic for SSTF Disk Scheduling

    for (i = 0; i < n; i++)
    {
        min = 9999;

        for (j = 0; j < n; j++)
        {
            if (visited[j] == 0)
            {
                distance = abs(RQ[j] - initial);
                if (distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
        }

        TotalHeadMovement = TotalHeadMovement + min;
        initial = RQ[index];
        visited[index] = 1;
    }

    printf("Total head movement is %d", TotalHeadMovement);

    return 0;
}