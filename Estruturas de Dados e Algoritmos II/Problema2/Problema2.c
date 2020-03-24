#include <stdio.h>

int alexPoints = 0, belaPoints = 0, i, j, *begin, *end, minMax = 0;

int alexTurn(int arr[])
{
    if (arr[i]>arr[j]){
        alexPoints += *begin;
        begin = &arr[i+1];
        return i++;
    }
    else{
        alexPoints += *end;
        end = &arr[j-1];
        return j--;
    }
}

int belaTurn(int arr[])
{
    if (minMax==0) {
        if (arr[i] < arr[j]) {
            belaPoints += *begin;
            begin = &arr[i + 1];
            minMax = 1;
            return i++;
        }

        else {
            belaPoints += *end;
            end = &arr[j - 1];
            minMax = 1;
            return j--;
        }
    }
    else{
        if (arr[i]>arr[j])
        {
            belaPoints += *begin;
            begin = &arr[i+1];
            minMax = 0;
            return i++;
        }

        else{
            belaPoints += *end;
            end = &arr[j-1];
            minMax = 0;
            return j--;
        }
    }
}

int main()
{
    int beanPiles, numPile = 0, counter = 0;
    char help;

    scanf("%d", &beanPiles);

    int array[beanPiles];

    while(help != '\n') {                       //
        scanf("%d%c",&array[numPile],&help);
        numPile++;
    }

    i = 0, j = beanPiles-1;
    begin = &array[i];
    end = &array[j];

    while (i<=j)
    {
        if(counter % 2 == 0){
            alexTurn(array);
            counter++;
        }
        else{
            belaTurn(array);
            counter++;
        }

    }

    if (alexPoints > belaPoints)
    {
        printf("Alex ganha com %d contra %d\n",alexPoints,belaPoints);
    }
    else if(belaPoints > alexPoints)
    {
        printf("Bela ganha com %d contra %d\n",belaPoints,alexPoints);
    }
    else{
        printf("Alex e Bela empatam a %d\n",alexPoints);
    }


    return 0;
}