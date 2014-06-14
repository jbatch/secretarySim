#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_APPLICANTS 100
#define MAX_SCORE 1000000

int is_int(char const* p)
{
        char *buffer = malloc(10 * sizeof(char));
        sprintf(buffer, "%d", atoi(p));
        return strcmp(buffer, p) == 0;
}

int randInRange(int min, int max)
{
        return (rand() % (max+1-min))+min;
}

int main(int argc, char* argv[])
{
        const double e = 2.7182818284590452353602874;
        double percent = 0.0;
        srand(time(NULL));
        int numSimulations = 0, i = 0, highestScore = 0,
                bestApplicant =-1, currApplicant = 0, currScore = 0,
                numBestPicks = 0, simulationCount = 0;
        int *applicantScores;
        printf("Secretary Problem Simulator\n");

        /*This block gets the number of simulations through cmd line
         or through scanf.*/
        if(argc == 1)
        {
                printf("How many simulations?: ");
                scanf("%d", &numSimulations);
        }
        else
        {
                if(is_int(argv[1]))
                {
                        numSimulations = atoi(argv[1]);
                }
                else
                {
                        printf("Invalid argument passed from cmd line"
                               "\nHow many simulations?: ");
                        scanf("%d", &numSimulations);
                }
        }

        /*Allocate memory for array of applicant scores*/
        applicantScores = calloc(sizeof(int), NUM_APPLICANTS);

        for(simulationCount = 0;
            simulationCount < numSimulations;
            simulationCount++)
        {
                currApplicant = 0;
                currScore = 0;
                highestScore = 0;
                bestApplicant = -1;
                /*Give each applicant a random score*/
                for(i = 0; i < NUM_APPLICANTS; i++)
                {
                        applicantScores[i] = randInRange(1, MAX_SCORE);
                }

                /*Interview the first 1/e applicants and identify the best*/
                for(i = 0; i < 1 + (int)(NUM_APPLICANTS*(1/e)); i++)
                {
                        if(applicantScores[i] > highestScore)
                        {
                                highestScore = applicantScores[i];
                                bestApplicant = i;
                        }
                }

                currApplicant = 1 + (int)(NUM_APPLICANTS*(1/e));
                currScore = applicantScores[currApplicant];;
                while(currScore < highestScore && currApplicant < NUM_APPLICANTS - 1)
                {
                        currApplicant++;
                        currScore = applicantScores[currApplicant];
                }

                /*Find highest in the group*/
                highestScore = 0;
                bestApplicant = -1;
                for(i = 0; i < NUM_APPLICANTS; i++)
                {
                        if(applicantScores[i] > highestScore)
                        {
                                bestApplicant = i;
                                highestScore = applicantScores[i];
                        }
                }

                if(applicantScores[currApplicant] == highestScore)
                {
                        numBestPicks++;
                }
        }

        percent = 100*((double)numBestPicks / numSimulations);
        printf("Num best picks %d/%d %.2lf%%\n",
               numBestPicks,
               (int)numSimulations,
               percent);

        return 0;
}
