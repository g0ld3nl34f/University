#include <stdio.h>
#include <string.h>
#define MAXCHAR 21

void readResults(int N, int J, int data[N][6], char names[N][MAXCHAR])
{
    //to store the goals scored by each team;
    int homeTeamScore, awayTeamScore; 
    
    //to store each team name;
    char homeTeam[MAXCHAR], awayTeam[MAXCHAR];

    for (int i = 0; i < J; ++i)
    {
        //reads each game result;
        scanf("%s %d - %s %d", homeTeam, &homeTeamScore, awayTeam, &awayTeamScore);

        if (homeTeamScore > awayTeamScore)
        {
            //if the home team won, a victory, goals scored, goals conceded and points won are stored in data[N], being N the number associated to the team; 
            for (int j = 0; j < N; ++j)
            {
                if (strcmp(names[j],homeTeam)==0)
                {
                    data[j][0] += 1;
                    data[j][3] += homeTeamScore;    
                    data[j][4] += awayTeamScore;
                    data[j][5] += 3;
                    break;
                }
            }
            //the same has the home team, but instead of a victory, a loss is stored and no points are stored;
            for (int k = 0; k < N; ++k)
            {
                if (strcmp(names[k],awayTeam)==0)
                {
                    data[k][2] += 1;
                    data[k][3] += awayTeamScore;
                    data[k][4] += homeTeamScore;
                    break;
                }
            }
        }

        else if (awayTeamScore > homeTeamScore)
        {   
            //the same if the home team won, but reversed;
            for (int j = 0; j < N; ++j)
            {
                if (strcmp(names[j],awayTeam)==0)
                {
                    data[j][0] += 1;
                    data[j][3] += awayTeamScore;
                    data[j][4] += homeTeamScore;
                    data[j][5] += 3;
                    break;
                }
            }

            for (int k = 0; k < N; ++k)
            {
                if (strcmp(names[k],homeTeam)==0)
                {
                    data[k][2] += 1;
                    data[k][3] += homeTeamScore;
                    data[k][4] += awayTeamScore;
                    break;
                }
            }
        }

        else{

            //for each team a draw, goals scored, goals conceded and a point are stored in their respective array;
            for (int j = 0; j < N; ++j)
            {
                if (strcmp(names[j],homeTeam)==0)
                {
                    data[j][1] += 1;
                    data[j][3] += homeTeamScore;
                    data[j][4] += awayTeamScore;
                    data[j][5] += 1;
                    break;
                }
            }

            for (int k = 0; k < N; ++k)
            {
                if (strcmp(names[k],awayTeam)==0)
                {
                    data[k][1] += 1;
                    data[k][3] += awayTeamScore;
                    data[k][4] += homeTeamScore;
                    data[k][5] += 1;
                    break;
                }
            }
        }
    }
}


int main() {
    int N, J, points = 0, winner = 0;

     //Takes N -> number of teams and J -> number of games played as inputs;
    scanf("%d %d",&N,&J);  

     //names[N] -> team name;
    char names[N][MAXCHAR];
    
    //data[N][0] -> victories, data[N][1] -> draws, data[N][2] -> defeats, data[N][3] -> goals scored, data[N][4] -> goals conceded, data[N][5] = accumulated points;
    int data[N][6];        

    //This cycle is for setting every position of the 2D array data in an initial state;
    for (int j = 0; j < N; ++j)
    {
        for (int i = 0; i < 6; ++i)
        {
            data[j][i] = 0;
        }
    }

    //Stores each team name in names[i];
    for (int i = 0; i < N; ++i)
    {
        scanf("%s", names[i]);
    }

    readResults(N,J,data,names);

    for (int k = 0; k < N; ++k)
    {   
        //The current max points found and the index of the current winning team are stored;
        if (data[k][5] > points)
        {
            points = data[k][5];
            winner = k;
        }
    }

    //Searchs for a team with the same amount os points as the winner, if one is found, the tournament as no winner;
    for (int l = 0; l < N; ++l) {
        
        if (l == winner)
        {
            ++l;
        }
        
        if (data[l][5] == points)
        {
            printf("torneio sem vencedora\n");
            return 0;
        }
    }

    printf("a vencedora foi %s, com %d ponto(s)\n", names[winner], points);
    printf("ganhou %d jogo(s), empatou %d jogo(s) e perdeu %d jogo(s)\n", data[winner][0], data[winner][1], data[winner][2]);
    printf("marcou %d golo(s) e sofreu %d golo(s)\n", data[winner][3], data[winner][4]);

    return 0;
}