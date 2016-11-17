#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int coinExperiment();
int trumpExperiment();
int processCoinExperiment();
int processDetistan();
int main()
{
    char experimentType[80] = "0";
    int outcome;
    int advantage = 0;
    srand (time(NULL));
    while (experimentType[0] != '6')
    {
        printf("\n\n\nFor the coin simulation, enter 1.\nFor a simulated re-do of election night assuming the 538 model is correct, enter 2.\nTo run a poll on the population of Detistan, press 3.\nTo run a fair Detistan elections, press 4.\nTo run a rigged Detistan elections, press 5.\nTo exit, enter 6.\n");
        scanf("%s", &experimentType);
        if (experimentType[0] == '1')
        {
            outcome = coinExperiment(0);
        }
        else if (experimentType[0] == '2')
        {
            outcome = trumpExperiment(0);
        }
        else if (experimentType[0] == '3')
        {
            outcome = coinExperiment(2);
        }
        else if (experimentType[0] == '4')
        {
            outcome = coinExperiment(1);
        }
        else if (experimentType[0] == '5')
        {
            outcome = coinExperiment(3);
        }
    }
    return 0;
}

int coinExperiment(int input)
{
    int flip = rand();
    int maxAcceptableResult = RAND_MAX/20000;
    int experimentCount = 0;
    int headCount = 0;
    int tailCount = 0;
    int sideCount = 0;
    int headPollCount = 0;
    int tailPollCount = 0;
    int sidePollCount = 0;
    int foundSuccess = 0;
    int i = 0;
    int polled = 0;
    int totalPolled = 0;
    double rangeChecker = 0;
    while (foundSuccess == 0)
    {
        headCount = 0;
        tailCount = 0;
        sideCount = 0;
        for (i = 0; i < 100000; i++)
        {
            flip = rand();
            rangeChecker = ((double)flip)/20000; //suppose our RAND_MAX = 32767. We want to discard results between 20000 and 32767, because they make 0~12767 appear more often in our 0~20000 generator.
            while (rangeChecker>=((double)maxAcceptableResult)) //make sure 0 doesn't appear too often
            {
                flip = rand();
                rangeChecker = ((double)flip)/20000;
            }
            flip = flip%20000;
            polled = rand()%100;
            //19998~19999 = landing on the side, 0~9998 = landing heads, 9999~19997 = landing tails
            if (flip <=9998 )
            {
                headCount++;

                if (polled == 1)
                {
                    headPollCount++;
                }
            }
            else if (flip <= 19997)
            {
                tailCount++;
                if (polled == 1)
                {
                    tailPollCount++;
                }
            }
            else
            {
                sideCount++;
                if (polled == 1)
                {
                    sidePollCount++;
                }
            }
        }

        experimentCount++;

        if (input == 0)
        {
            foundSuccess = processCoinExperiment(headCount);
            if (foundSuccess != 0)
            {
                printf("\nExperiment became out of range after %d tries with %d heads.", experimentCount, headCount);
            }
        }
        else if (input == 1)
        {
            foundSuccess = processDetistan(headCount, tailCount, sideCount);
            if (foundSuccess == 0)
            {
                printf("\nThe results look bad...The king hereby decrees population will be cut by spending. A total of %f was spent.", (tailCount + sideCount)*0.25 );
                return 0;
            }
            else if (foundSuccess == 1)
            {
                printf("\nThe results have vindicated the king! The king celebrates by spending %f on celebrations.", headCount * 0.25);
                return 1;
            }
            else
            {
                printf("\nThe king recognizes the coming of a new age by this new, unprecedented outcome. All 100000$ are hereby freed from my rule to rule the lands of Wall Street.");
                return 0;
            }
        }
        else if (input == 2)
        {
            totalPolled = (headPollCount+tailPollCount+sidePollCount);
            foundSuccess = processDetistan(headPollCount, tailPollCount, sidePollCount);
            if (foundSuccess == 0)
            {
                printf("\nThe polls look bad...a total of %f percent of citizen don't like the king!\nA total of %d citizens were polled.", ((double)(tailPollCount + sidePollCount)/totalPolled), totalPolled );
                return 0;
            }
            else if (foundSuccess == 1)
            {
                printf("\nThe polls have vindicated the king! He enjoys a support from %f percent of citizens.\nA total of %d citizens were polled.", ((double)(headPollCount))/totalPolled, totalPolled);
                return 1;
            }
            else
            {
                printf("\nThe king did not see this coming! The reports indicate some strange results, the king is demanding more polls!");
                return 0;
            }
        }
        else if (input == 3)
        {
            int dice = (rand()%6)+1;
            printf("\n\n\nThe dice has been rolled! The result is...%d!\n", dice);
            foundSuccess = processDetistan(headCount*dice, tailCount, sideCount);
            if (foundSuccess == 0)
            {
                printf("\nA rare loss, the King is shocked by these results! How does one lose a rigged election!?");
                return 0;
            }
            else if (foundSuccess == 1)
            {
                printf("\nThe king humbly accepts the victory and dedicates the speech to Emperor Palpatine.");
                return 1;
            }
            else
            {
                printf("\nThe king has been removed from the throne while he was shouting that it was all rigged. Nobody knew what he was talking about.");
                return 0;
            }
        }
    }
    return 0;
}



int processDetistan(int heads, int tails, int sides)
{
    int headTailDifference = heads - tails;
    int tailSideDifference = tails - sides;
    int headSideDifference = heads - sides;
    //handle equals
    if (headTailDifference == 0)
    {
        printf("\nTie detected! What will happen...!!!???");
        return 2;
    }
    else if (tailSideDifference == 0)
    {
        if (headTailDifference > 0)
        {
            return 1;
        }
    }
    else
    {
        if (heads > tails && heads > sides)
        {
            return 1;
        }
        if (tails > heads && tails > sides)
        {
            return 0;
        }
        if (sides > heads && sides > tails)
        {
            return 2;
        }
    }
}

int processCoinExperiment(int heads)
{
    if (heads < 49685 || heads > 50305)
    {
        return 1;
    }
    return 0;
}

int trumpExperiment()
{
    int flip = rand();
    int maxAcceptableResult = RAND_MAX/1000;
    double rangeChecker = ((double)flip)/100;
    while (rangeChecker>=((double)maxAcceptableResult))
    {
        flip = rand();
        rangeChecker = ((double)flip)/1000;
    }
    if ((flip%1000)<1) //0~2 = trump win
    {
        printf("\nJill stein has won...? How many times have you ran this thing?");
    }
    else if (flip%1000 < 6)
    {
        printf("\nGary Johnson has won! Congrats, you found the rare outcome!");
    }
    else if (flip%1000 < 306)
    {
        printf("\nTrump has won! If you got this on the first try consider it a re-enactment of that fateful night...with less excitement and crying.");
    }
    else
    {
        printf("\nHillary has won! Not that this changes anything - remember, simulations is just yet another type of prediction method that get trumped by ACTUAL OUTCOMES(tm) too.");
    }
    return 0;
}
