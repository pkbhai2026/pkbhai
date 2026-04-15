#include <stdio.h>
#include <stdlib.h>

int main()
{
    int RQ[100], i, j, n, TotalHeadMoment = 0, initial, move;

    printf("Enter the number of Requests\n");
    scanf("%d", &n);

    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
        scanf("%d", &RQ[i]);

    printf("Enter initial head position\n");
    scanf("%d", &initial);

    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move);

    // Sort the request array
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (RQ[j] > RQ[j + 1])
            {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index;
    for (i = 0; i < n; i++)
    {
        if (initial < RQ[i])
        {
            index = i;
            break;
        }
    }

    // Move towards high
    if (move == 1)
    {
        for (i = index; i < n; i++)
        {
            TotalHeadMoment += abs(RQ[i] - initial);
            initial = RQ[i];
        }

        // Jump to lowest request
        if (index > 0)
        {
            TotalHeadMoment += abs(RQ[0] - initial);
            initial = RQ[0];

            for (i = 1; i < index; i++)
            {
                TotalHeadMoment += abs(RQ[i] - initial);
                initial = RQ[i];
            }
        }
    }
    // Move towards low
    else
    {
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment += abs(RQ[i] - initial);
            initial = RQ[i];
        }

        // Jump to highest request
        if (index < n)
        {
            TotalHeadMoment += abs(RQ[n - 1] - initial);
            initial = RQ[n - 1];

            for (i = n - 2; i >= index; i--)
            {
                TotalHeadMoment += abs(RQ[i] - initial);
                initial = RQ[i];
            }
        }
    }

    printf("Total head movement is %d", TotalHeadMoment);

    return 0;
}