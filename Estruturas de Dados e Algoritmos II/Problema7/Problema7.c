#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME "base"
#define MAXCHAR 56
#define MAXPEOPLE 1000000

struct person{
    int id, phone_1, phone_2, income;
    char politic_orientation[MAXCHAR], consuming_habits[MAXCHAR];
};

struct person *person_new(int id, int phone_1, int phone_2, int income, char p_o[], char c_h[]){
    struct person *new = malloc(sizeof(struct person));

    new -> id = id; new -> phone_1 = phone_1; new -> phone_2 = phone_2; new -> income = income;

    strcpy(new -> politic_orientation, p_o);
    strcpy(new -> consuming_habits, c_h);

    return new;
}

//opens file in read/write mode if it exists, or else creates a new file and initializes it;
FILE *open()
{
    FILE *data_base = fopen(NAME, "r+");

    if (data_base == NULL)
    {
        data_base = fopen(NAME, "w+");

        struct person *temp = person_new(-1, 0, 0, 0, "", "");

        for (int i = 0; i < MAXPEOPLE; ++i)
        {
            fwrite(temp, sizeof(struct person), 1, data_base);
        }

        free(temp);
    }

    return data_base;
}

//writes the given node in a position given by the node id in the file;
void file_write(FILE *data_base, struct person *write){
    int id = write->id;

    fseek(data_base, id * sizeof(struct person), SEEK_SET);

    fwrite(write, sizeof(struct person), 1, data_base);
}

//reads the given position of the file and returns the corresponding node;
struct person *file_read(FILE *data_base, int id)
{
    fseek(data_base, id * sizeof(struct person), SEEK_SET);
    struct person *temp = malloc(sizeof(struct person));

    fread(temp, sizeof(struct person), 1, data_base);

    return temp;
}

//overwrites the given position in the file, "deleting" it;
void file_delete(FILE *data_base, int id)
{
    fseek(data_base, id * sizeof(struct person), SEEK_SET);

    struct person *temp = person_new(-1, 0, 0, 0, "", "");

    fwrite(temp, sizeof(struct person), 1, data_base);

    free(temp);
}

//reads the input and returns the resulting struct;
struct person *get_person()
{
    int id, phone_1, phone_2, rendimento;
    char p_o[MAXCHAR], c_h[MAXCHAR];

    scanf("%d", &id);
    scanf("%d %d", &phone_1, &phone_2);
    scanf("%d", &rendimento);
    scanf(" %[^\n]s", p_o);
    scanf(" %[^\n]s", c_h);

    struct person *temp = person_new(id, phone_1, phone_2, rendimento, p_o, c_h);

    return temp;
}

int main() {
    FILE *data_base = open();
    int id;
    char instruction;
    struct person *temp;

    while (scanf("%c", &instruction) != EOF) {
        switch (instruction) {
            case '+':
                temp = get_person();

                file_write(data_base, temp);

                free(temp);
                break;

            case '-':
                scanf("%d", &id);
                temp = file_read(data_base, id);
                
                if (temp -> id == -1)
                {
                    printf("+ SUJEITO %06d desconhecido\n", id);
                } 
                else
                {
                    file_delete(data_base, id);
                }

                free(temp);
                break;

            case '?':
                scanf("%d", &id);
                temp = file_read(data_base, id);

                if (temp -> id == -1)
                {
                    printf("+ SUJEITO %06d desconhecido\n", id);
                }

                else{
                    printf("+ SUJEITO %06d\n", temp -> id);
                    printf("%d %d\n", temp -> phone_1, temp -> phone_2);
                    printf("%d\n", temp -> income);
                    printf("%s\n", temp -> politic_orientation);
                    printf("%s\n", temp -> consuming_habits);
                }

                free(temp);
                break;

            default :
                break;

        }
    }

    fclose(data_base);

    return 0;
}