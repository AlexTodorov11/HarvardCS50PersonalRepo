#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to get the score of a letter
int get_letter_score(char letter)
{
    int scores[ALPHABET_SIZE] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                                 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    if (isalpha(letter))
    {
        return scores[toupper(letter) - 'A'];
    }
    return 0;
}

// Function to calculate the total score of a word
int calculate_score(const char *word)
{
    int score = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        score += get_letter_score(word[i]);
    }
    return score;
}

int main(void)
{
    // Prompt for Player 1's word
    string word1 = get_string("Player 1: ");

    // Prompt for Player 2's word
    string word2 = get_string("Player 2: ");

    // Calculate scores
    int score1 = calculate_score(word1);
    int score2 = calculate_score(word2);

    // Determine the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}
