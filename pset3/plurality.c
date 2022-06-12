#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Inspiration from https://gist.github.com/deeunix/d9523f86b7499ba880055f836b48ba6d

// I don't know if invalid entries are handled correctly.
// The check50 function is returning good results, but when I try an invalid name
//      I notice that it counts as a vote. It isn't added to the list of candidates,
//      but I don't get an extra vote tally to accomodate the invalid vote.

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Loops through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Comparison between user vote and existing candidate
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Increate the vote tally for that candidate
            candidates[i].votes++;
            return true;
        }
    }
    // else return false. Will print "Invalid Vote" to terminal
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Variable to track max vote
    int highest_tally = 0;

    // Go through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highest_tally)
        {
            highest_tally = candidates[i].votes;
        }
    }

    // Again go through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // For all candidate vote totals equal to the highest vote tally, print
        if (candidates[i].votes == highest_tally)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}