Goal: To write functions to determine the winner of a tideman election and to print the name of the winner. Before reading further it is important to understand how a tideman voting system works, which is explained in the [problem description](https://cs50.harvard.edu/x/2020/psets/3/tideman/#:~:text=wget%20https://cdn.cs50.net/2019/fall/psets/3/tideman/tideman.c).

The **vote** function must take arguments **rank**, **name**, and **ranks**. If **name** is a match for the name of a valid candidate, then the **ranks** array should be updated to indicate that the voter has the candidate as their **rank** preference (where 0 is the first preference, 1 is the second preference, etc.) The function should return true if the rank was successfully recorded, and false otherwise (if, for instance, **name** is not the name of one of the candidates).

The **record_preferences** function is called once for each voter, and takes as argument the **ranks** array. The function should update the global **preferences** array to add the current voter’s preferences.

The **add_pairs** function should add all pairs of candidates where one candidate is preferred to the **pairs** array. A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.  
The function should update the global variable **pair_count** to be the number of pairs of candidates.

The **sort_pairs** function should sort the **pairs** array in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate. If multiple pairs have the same strength of victory, you may assume that the order does not matter.

The **lock_pairs** function should create the **locked** graph, adding all edges in decreasing order of victory strength so long as the edge would not create a cycle.

The **print_winner** function should print out the name of the candidate who is the source of the graph. You may assume there will not be more than one source.

Just like with plurality, the **main** function is already written for us, and our objective is to populate the functions called within **main**. The correct behaviour of the program is shown below, taking as command line arguments the names of the candidates in the election before prompting the user for number of voters followed by each voter’s ranking of the candidates. Finally the winner of the election is printed.

./tideman Alice Bob Charlie  
Number of voters: 5  
Rank 1: Alice  
Rank 2: Charlie  
Rank 3: Bob  
  
Rank 1: Alice  
Rank 2: Charlie  
Rank 3: Bob  
  
Rank 1: Bob  
Rank 2: Charlie  
Rank 3: Alice  
  
Rank 1: Bob  
Rank 2: Charlie  
Rank 3: Alice  
  
Rank 1: Charlie  
Rank 2: Alice  
Rank 3: Bob  
  
Charlie

# **vote**

The **vote** function is called once for every voter (**i**) and ranking (**j**) in a nested loop within the **main** function. For example, if there were three candidates the function would be called three times per voter to check each voter’s first, second and third ranking candidate choices. Just like in plurality, if it returns **false** then “Invalid vote.” is printed and the program ends.

    // Query for votes  
    for (int i = 0; i < voter_count; i++)  
    {  
        // ranks[i] is voter's ith preference  
        int ranks[candidate_count];        // Query for each rank  
        for (int j = 0; j < candidate_count; j++)  
        {  
            string name = get_string("Rank %i: ", j + 1);            if (!vote(j, name, ranks))  
            {  
                printf("Invalid vote.\n");  
                return 3;  
            }  
        }

The goal of the function is thus to first determine if the candidate name in each ranking position is valid and secondly to update each voter’s **ranks** array with that voter’s rank preferences.

The **ranks** array is a 1D array which defines the ranking order of the candidates for each voter. The candidate index integer (the order in which they were defined in the command line arguments) is what is stored in the **ranks** array. For example, if there are three candidates Alice, Bob and Charlie, then Alice will be [0], Bob will be [1] and Charlie will be [2]. If the voter votes for Bob in rank 1, Charlie in rank 2 and Alice in rank 3 then the outputted **ranks** array will be **[1, 2, 0]** for that voter.

The function itself is similar to the **vote** function in the plurality problem. It should loop through each candidate, checking using **strcmp** each time if the candidate name matches the **name** argument. If it does, add that candidate’s index to the current position of the **ranks** array and return **true** since the **name** is valid. If this condition isn’t met after checking all candidates against the **name** argument, return **false**.

// Update ranks given a new vote  
bool vote(int rank, string name, int ranks[])  
{  
    // Loop through candidates  
    for (int i = 0; i < candidate_count; i++)  
    {  
        // Check name is valid  
        if (strcmp(candidates[i], name) == 0)  
        {  
            // Update ranks array with rank preference  
            ranks[rank] = i;  
            return true;  
        }  
    }  
    return false;  
}

# **record_preferences**

This function is also called once for each voter, inside the same loop as the **vote** function. It takes one argument, the **ranks** array that was populated in the **vote** function. The objective here is to update the **preferences** array, which is a 2D array that indicates the number of voters who prefer candidate **i** to candidate **j**. In other words, if there are three candidates, **preferences** is a 3x3 table.

The code for this one is short, but the logic can be challenging. A nested loop must be used, with both the inner and outer loops looping up to the number of candidates. The inner loop however should start from **i + 1**, as we only want to add to the **preferences** array when **_j comes after i_** in the **ranks** array. Once this condition is included, the **preferences** count can be increased by 1 at the position where the candidate in **ranks[i]** is being compared to the candidate in **ranks[j]**.

// Update preferences given one voter's ranksvoid record_preferences(int ranks[])  
{  
    // Assess voter ranks  
    for (int i = 0; i < candidate_count; i++)  
    {  
        for (int j = i + 1; j < candidate_count; j++)  
        {  
            // Update number of voters who prefer [i] to [j]  
            // in ranks array  
            // E.g. [0, 3, 2, 1, 4]  
            preferences[ranks[i]][ranks[j]]++;        }  
    }return;  
}

# **add_pairs**

This function must add every pair of candidates where one is preferred over the other to the **pairs** array. This is a 1D array of **pair** structs, which have both a winner and loser integer value. The global variable **pair_count** must also be incremented for every pair added.

Once again this can be achieved using a nested loop up to the amount of candidates, with the inner loop incrementally increasing from **i + 1**. This is done to prevent repeat checks of the **preferences** array. Again taking the example of three candidates, candidate [0] will be checked against [1] and [2], then candidate [1] will be checked against candidate [2] only. This fulfils every combination exactly once, as candidates should not be checked against themselves.

Within the inner loop, each combination can be checked to see if candidate **i** or candidate **j** is the winner using separate conditional statements. To check if **i** is the winner, we check if the number of people who prefer candidate **i** to candidate **j** is greater than the number of people who prefer **j** to **i,** reversing this to check if **j** is the winner. If there is a draw, both conditions pass and the loop continues.

With a winner determined, the **pair** struct in the **pair_count** position of the **pairs** array can be updated with a winner and loser. Recall that **pair_count** is initially equal to zero, as defined within the **main** function. **pair_count** should then be incremented, which allows the next pair to be inserted at the next position in the array.

// Record pairs of candidates where one is preferred over the othervoid add_pairs(void)  
{  
    for (int i = 0; i < candidate_count; i++)  
    {  
        for (int j = i + 1; j < candidate_count; j++)  
        {  
            if (preferences[i][j] > preferences[j][i])  
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

# **sort_pairs**

With the **pairs** array defined, the purpose of this function is to sort them in order of decreasing strength of victory, where the strength of victory is defined to be the number of voters who prefer the preferred candidate. In terms of our program, it is equal to position **[pairs.winner][pairs.loser]** of the **preferences** array, which gives the number of people who prefer the winner to the loser.

Any sorting algorithm, as taught in the week 3 lecture, can be used for this function however I have opted for [bubble sort](https://www.geeksforgeeks.org/bubble-sort/). To do this I have once again used, yep you guessed it, a nested loop. An important thing to note here is that **i** is incremented downwards. This is because each pass of the loop will require less elements to be sorted as those to the right of **i** will already be sorted.

For each adjacent couple of **pair** structs in the **pairs** array, the strength of victory is compared. If the **pair** at position **j + 1** has a greater strength of victory than the **pair** at position **j**, then they are swapped using a temporary variable.

// Sort pairs in decreasing order by strength of victoryvoid sort_pairs(void)  
{  
    for (int i = pair_count - 1; i >= 0 ; i--)  
    {  
        for (int j = 0; j <= i - 1; j++)  
        {  
            if ((preferences[pairs[j].winner][pairs[j].loser]) < (preferences[pairs[j + 1].winner][pairs[j + 1].loser]))  
            {  
                pair temp = pairs[j];  
                pairs[j] = pairs[j + 1];  
                pairs[j + 1] = temp;  
            }  
        }  
    }return;  
}

# **lock_pairs**

The purpose of this function is to populate the **locked** 2D array, which is composed of boolean values and is initially set to all **false**. A pair can be ‘locked’ and the value set to **true** if locking that pair does not create a cycle back to the winning candidate. This is shown graphically in the below image. In this example Alice was preferred to Bob, and Charlie was preferred to Alice. If Bob was preferred to Charlie in one of the sorted **pairs** then a cycle would be created and there would not be a winner of the election. In this case however, Charlie can be declared the winner as he has no arrows pointing to him. In terms of the array, all values are **false** pointing towards him (more on that later).

![](https://miro.medium.com/v2/resize:fit:700/1*aYd6VdF-6BYk0P7b9nqPTA.jpeg)

It’s important that you fully understand what you want the function to do before starting with the syntax, as it can take a bit of time to get your head around. Personally I found it really clicked after reading [this post](https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9). It’s important to realise that the sole purpose of the function is to populate the **locked** array based on the information given in the **pairs** array, nothing more nothing less.

Now on to the syntax itself. There are many ways to approach this with some using recursion, some not. My approach was to define a separate **cycle** function that takes as argument two candidates and checks if a cycle is created.

This is a recursive function, so a base case must first be defined that will exit the function if a cycle is created. This occurs when the function is being called for two identical candidate values, meaning a candidate points at themselves, thus creating a cycle.

The recursive case loops through each candidate and performs two checks. This is perhaps easier to understand with the knowledge that when this function is being called, **end** will initially be the loser and **cycle_start** will be the winner of each **pair** being checked. Firstly, if there is an arrow going from **end** to another candidate then there is a potential for a cycle. If not, there cannot be a cycle and the function returns **false**. If the first check returns **true** then **cycle** is called again, this time using the current candidate as the **end** argument. This process repeats until **false** is returned, meaning the chain ends and there is no cycle, or the base case is triggered as the chain has looped back round to the start, thus creating a cycle and returning **true**.

// Test for cycle by checking arrow coming into each candidatebool cycle(int end, int cycle_start)  
{  
    // Return true if there is a cycle created (Recursion base case)  
    if (end == cycle_start)  
    {  
        return true;  
    }    // Loop through candidates (Recursive case)  
    for (int i = 0; i < candidate_count; i++)  
    {  
        if (locked[end][i])  
        {  
            if (cycle(i, cycle_start))  
            {  
                return true;  
            }  
        }  
    }  
    return false;  
}

Within the **lock_pairs** function, I have looped through each pair and called the **cycle** function for each loser and winner. If **cycle** returns **false**, then the **locked** array can be set to **true** for the **pair**.

// Lock pairs into the candidate graph in order, without creating cyclesvoid lock_pairs(void)  
{  
    // Loop through pairs  
    for (int i = 0; i < pair_count; i++)  
    {  
        // If cycle function returns false, lock the pair  
        if (!cycle(pairs[i].loser, pairs[i].winner))  
        {  
            locked[pairs[i].winner][pairs[i].loser] = true;  
        }  
    }  
    return;  
}

If this is still not making sense I recommend sitting down with a sheet of paper and walking through a few example **pairs** arrays. This was definitely the most challenging problem in CS50 thus far and it took me a while to get my head around.

# **print_winner**

The final function must print the winner of the election, given the information defined in the **locked** array. In terms of the array, the winner is the candidate with no **true** values in their column. In graphical terms, this means there are no arrows pointing towards them.

To determine this, we can loop through each candidate, declaring an integer to count the number of false values in that candidate’s column within **locked**. We then iterate through each candidate’s column, iterating **false_count** if a **false** value is found. If **false_count** is equal to **candidate_count** then the entire column is **false** and that candidate can be declared as a source of the graph and their name printed.

// Print the winner of the election  
void print_winner(void)  
{  
    // Winner is the candidate with no arrows pointing to them  
    for (int i = 0; i < candidate_count; i++)  
    {  
        int false_count = 0;        for (int j = 0; j < candidate_count; j++)  
        {  
            if (locked[j][i] == false)  
            {  
                false_count++;  
                if (false_count == candidate_count)  
                {  
                    printf("%s\n", candidates[i]);  
                }  
            }  
        }  
    }  
    return;  
}

# **Conclusion**

The difficulty definitely escalated significantly for this PSet as we had our first taste of recursion and sorting algorithms. Very satisfying to finally see a successful check50 for this one.