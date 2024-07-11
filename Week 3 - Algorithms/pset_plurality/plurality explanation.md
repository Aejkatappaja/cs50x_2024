### vote function implementation

- We loop over the candidates array to compare the name given to the function with some of candidate's name present in the candidates array,
  - if name exists -> increment candidates.votes
  - else return false

```c
// Update vote totals given a new vote
bool vote(string name)
{

    for (int i = 0; i < candidate_count; i++)
    {

        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}
```

### print_winner function implementation

- We init a variable called max_votes to 0.
- We loops through candidates array and verify if candidates.votes > max_count,
  - if true -> max_votes = candidate.votes
- Second loop is to print winner(s), if candidate.votes == max_votes then he is a winner.

```c
// Print the winner (or winners) of the election
void print_winner(void)
{

    int max_votes = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
            max_votes = candidates[i].votes;
    }

    for (int i = 0; i < candidate_count; i++)
        candidates[i].votes == max_votes &&printf("%s\n", candidates[i].name);

    return;
}
```
