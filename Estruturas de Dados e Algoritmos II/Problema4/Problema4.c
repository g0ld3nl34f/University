#include <stdio.h>
#define MAXCHAR 1101

void decipher(char input[])
{
    char compare[MAXCHAR];
    int  begin = 0, temp = 0, end = 1;

    for (int k = 0; k < MAXCHAR; ++k) {
        compare[k] = '\0';
    }

    while (input[end - 1] != '\0')
    {
        for (int i = begin; i < end; ++i) {
            compare[temp] = input[i];
            temp++;
        }

        for (int j = 0; j < temp; ++j) {
            if (compare[j] == input[end]){
                printf("%c", input[end]);
                begin = end + 1;
                end = begin;
                for (int i = 0; i < temp; ++i) {
                    compare[i] = '\0';
                }
                break;
            }
        }
        temp = 0;
        end++;
    }
}

int main()
{
    char input[MAXCHAR];

    while(scanf("%s",input) != EOF)
    {
        decipher(input);
        printf("\n");
    }

    return 0;
}