#include <stdio.h>

#define MAX 1000000

int collatzLength[MAX];

int calculateCollatzLength(int n)
{
    if (n < MAX && collatzLength[n] != -1)
    {
        return collatzLength[n];
    }

    int length;
    if (n % 2 == 0)
    {
        length = 1 + calculateCollatzLength(n / 2);
    }
    else
    {
        length = 2 + calculateCollatzLength((3 * n + 1) / 2);
    }

    if (n < MAX)
    {
        collatzLength[n] = length;
    }

    return length;
}

int main()
{
    for (int i = 0; i < MAX; i++)
    {
        collatzLength[i] = -1;
    }
    collatzLength[1] = 1;

    int n;
    do
    {
        printf("Enter the upper limit for finding the longest Collatz sequence: ");
        scanf("%d", &n);
    } while (n < 0);

    int maxLength = 0;
    int maxNumber = 0;

    for (int i = 1; i <= n; ++i)
    {
        int length = calculateCollatzLength(i);
        if (length > maxLength)
        {
            maxLength = length;
            maxNumber = i;
        }
    }

    printf("Number with the longest Collatz sequence: %d, Length: %d\n", maxNumber, maxLength);

    return 0;
}