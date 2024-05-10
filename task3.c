#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARDS 5

typedef struct
{
    int rank;
    int suit;
} Card;

typedef struct
{
    Card cards[MAX_CARDS];
} Hand;

// Function to compare two cards based on rank
int compare(const void *a, const void *b)
{
    Card *cardA = (Card *)a;
    Card *cardB = (Card *)b;
    return cardB->rank - cardA->rank;
}

// Function to check if all cards in a hand have the same suit
int isFlush(Hand *hand)
{
    for (int i = 0; i < MAX_CARDS - 1; i++)
    {
        if (hand->cards[i].suit != hand->cards[i + 1].suit)
        {
            return 0;
        }
    }
    return 1;
}

// Function to check if all cards in a hand form a straight sequence
int isStraight(Hand *hand)
{
    for (int i = 0; i < MAX_CARDS - 1; i++)
    {
        if (hand->cards[i].rank != hand->cards[i + 1].rank + 1)
        {
            return 0;
        }
    }
    return 1;
}

// Function to evaluate the hand and determine its score
int evaluateHand(Hand *hand)
{
    qsort(hand->cards, MAX_CARDS, sizeof(Card), compare);

    int pairs = 0;
    int threeOfAKind = 0;
    int fourOfAKind = 0;
    for (int i = 0; i < MAX_CARDS - 1; i++)
    {
        if (hand->cards[i].rank == hand->cards[i + 1].rank)
        {
            pairs++;
            if (i < MAX_CARDS - 2 && hand->cards[i].rank == hand->cards[i + 2].rank)
            {
                threeOfAKind++;
                if (i < MAX_CARDS - 3 && hand->cards[i].rank == hand->cards[i + 3].rank)
                {
                    fourOfAKind++;
                }
            }
        }
    }

    if (isFlush(hand) && isStraight(hand))
    {
        return 8; // Straight Flush
    }
    else if (fourOfAKind)
    {
        return 7; // Four of a Kind
    }
    else if (threeOfAKind && pairs > 1)
    {
        return 6; // Full House
    }
    else if (isFlush(hand))
    {
        return 5; // Flush
    }
    else if (isStraight(hand))
    {
        return 4; // Straight
    }
    else if (threeOfAKind)
    {
        return 3; // Three of a Kind
    }
    else if (pairs == 2)
    {
        return 2; // Two Pairs
    }
    else if (pairs == 1)
    {
        return 1; // One Pair
    }
    else
    {
        return 0; // High Card
    }
}

int main()
{
    // Get cards for player 1 and player 2
    Hand player1, player2;

    printf("Enter player 1 cards:\n");
    for (int i = 0; i < MAX_CARDS; i++)
    {
        printf("Enter rank and suit for card %d: ", i + 1);
        scanf("%d %d", &player1.cards[i].rank, &player1.cards[i].suit);
    }

    printf("Enter player 2 cards:\n");
    for (int i = 0; i < MAX_CARDS; i++)
    {
        printf("Enter rank and suit for card %d: ", i + 1);
        scanf("%d %d", &player2.cards[i].rank, &player2.cards[i].suit);
    }

    int score1 = evaluateHand(&player1);
    int score2 = evaluateHand(&player2);

    if (score1 > score2)
    {
        printf("Player 1 wins.\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins.\n");
    }
    else
    {
        printf("It's a tie.\n");
    }

    return 0;
}