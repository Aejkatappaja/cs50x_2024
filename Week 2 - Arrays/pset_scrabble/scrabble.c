
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

#define PLAYER_1_WINS "Player 1 wins!"
#define PLAYER_2_WINS "Player 2 wins!"
#define TIE "Tie!"

int POINTS[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int str_len(string word);
int compute_score(string word, int len);
string players_result(int score1, int score2);

int main(void)
{
    string player_1_word = get_string("Player 1 :");
    string player_2_word = get_string("Player 2 :");

    int len1 = str_len(player_1_word);
    int len2 = str_len(player_2_word);

    int player_1_score = compute_score(player_1_word, len1);
    int player_2_score = compute_score(player_2_word, len2);

    printf("%s\n", players_result(player_1_score, player_2_score));
}

int str_len(string word)
{
    int n = 0;
    while (word[n] != '\0')
    {
        n++;
    }
    return n;
}

int compute_score(string word, int len)
{

    int score = 0;

    for (int i = 0; i < len; i++)
    {
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }
    }

    return score;
}

string players_result(int score1, int score2)
{

    if (score1 > score2)
    {
        return PLAYER_1_WINS;
    }
    else if (score1 < score2)
    {
        return PLAYER_2_WINS;
    }
    else
        return TIE;
}
