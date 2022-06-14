#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Takes inspiration from: https://joseph28robinson.medium.com/cs50-pset3-tideman-87f22f0f0bc3
// string.h header added to allow for strcmp function

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Iterates through all of the possible candidates to check that their name exists
    for (int k = 0; k < candidate_count; k++)
    {
        // If there is a candidate by this name, add the provided name. A value of zero means it is the same.
        if (strcmp(name, candidates[k]) == 0)
        {
            // Set the user's preference rank (in the ranks array) equal to the name of the valid candidate name.
            ranks[rank] = k;
            return true;
        }
    }
    // False is returned if the provided name was not found in the list
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update the preferences array. For 9 candidates, this would be a 9x9 array or table.
    // This will ultimately record who prefers candidate A to candidate B.
    for (int i = 0; i < candidate_count; i++)
    {
        // Nested loop must start from i + 1. Thus, we only modify the preferences
        //      array when j comes after i in ranks array
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Changes the preferences array for each pair of i and j. Add to counter for pair.
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Up to (n^2)-n pairs
    // Nested loop will iterate through all possible candidate pairs
    for (int i = 0; i < candidate_count; i++)
    {
        // Will add to pair counter for each newly found preference.
        // Since updates are side effect of the void return prototype, no else condition needed.
        // Essentially, this means you can skip pairs for which there is no preference.
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences [j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble sort. Increments down, as there are fewer things to sort as the algorithm progresses
    for (int i = pair_count - 1; i >= 0; i--)
    {
        for (int j = 0; j <= i - 1; j++)
        {
            // Checks if preference is stronger for candidate pair j + 1 than for j
            if ((preferences[pairs[j].winner][pairs[j].loser]) < (preferences[pairs[j + 1].winner][pairs[j + 1].loser]))
            {
                // Temporary variable for swapping
                pair foo = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = foo;
            }
        }
    }
    return;
}

//
bool recursion_check(int last, int first)
{
    // Returns true if a cycle is made
    if (last == first)
    {
        return true;
    }

    // Iterate through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If a combination involving the last-ranked candidate is found...
        if (locked[last][i])
        {
            // Calls function within itself recursively. If true, there is a recursive graph of candidates.
            if (recursion_check(i, first))
            {
                return true;
            }
        }
    }
    // Default is to return false. Just in case.
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Iterate through all pairs
    for (int i = 0; i < pair_count; i++)
    {
        // If there is no recursion escape clause, lock the candidate winner/loser pair.
        if (!recursion_check(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Iterates through candidates and will count number of 'missing arrows' pointed towards them in the graph
    for (int i = 0; i < candidate_count; i++)
    {
        int false_number = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_number++;
                // Returns true for the winner because no arrows point towards them in the graph. Prints the winner name.
                if (false_number == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}