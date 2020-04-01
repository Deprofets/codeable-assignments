#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
} pair;

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
    for (int i = 0; i < candidate_count; i++)
    {
        // There's a candidate with that name
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {

        for (int j = i + 1; j < candidate_count; j++)
        {
            int preferred = ranks[i];
            int less_preferred = ranks[j];
            // global variables are set to 0 so we can just start adding
            preferences[preferred][less_preferred]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //
    for (int i = 0; i < candidate_count; i++)
    {

        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // Set pair winner and loser to candidate ids
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int diffs = 0;
    for (int i = 0; i < pair_count - 1; i++)
    {
        // compare strength of victory
        pair p1 = pairs[i];
        pair p2 = pairs[i + 1];

        if (preferences[p1.winner][p1.loser] < preferences[p2.winner][p2.loser])
        {
            diffs++;
            pairs[i] = p2;
            pairs[i + 1] = p1;
        }
    }
    if (diffs > 0)
    {
        sort_pairs();
    }
    return;
}

bool is_loop(int winner_id, int loser_id)
{
    /*
     * follow loser connections
     * if target is found return true
     * else false 
     */
    int root = loser_id;
    bool exhausted = false;
    while (!exhausted)
    {
        for (int i = 0; i < MAX; i++)
        {
            // loop found
            if (locked[root][i] && i == winner_id)
            {
                return true;
            }
            // follow next connection
            if (locked[root][i])
            {
                //set new root
                root = i;
                //reset
                break;
            }
            // not found or no more connections to follow
            if (i == MAX - 1)
            {
                exhausted = true;
            }
        }
    }
    return false;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        pair current = pairs[i];
        // check if loops
        if (is_loop(current.winner, current.loser))
        {
            continue;
        }
        else
        {
            locked[current.winner][current.loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // find the source
    bool skip = false;
    // loop over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //candidate is not the source
            if (locked[j][i])
            {
                skip = true;
                break;
            }
        }
        // this is not the source, check next candidate
        if (skip)
        {
            // reset skip so we don't skip everyone
            skip = false;
            continue;
        }
        else
        {
            // nobody was locked to candidate so he must be the source
            printf("%s\n", candidates[i]);
        }
        return;
    }
}
