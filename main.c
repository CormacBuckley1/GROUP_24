/**
 * @file main.c
 * @brief Main program for the card deck assignment.
 *
 * This program demonstrates creation, shuffling, dealing,
 * sorting, and printing of card decks. 
 *
 * @author Niamh O'Dowd
 * @date 17/11/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "carddeck.h"

 /**
  * @brief Check if a deck is empty.
  *
  * @param deck Pointer to the deck to check.
  * @return int Returns 1 if the deck has no cards, 0 otherwise.
  */
int isEmpty(const CardDeck* deck)
{
    if (deck == NULL) {
        return 1;   // A NULL deck is considered empty.
    }
    return (deck->size == 0);
}

int main(void)
{
    int packs;

    // Asks the user how many packs to use and saves in 'packs'
    printf("Enter number of packs of cards: ");
    scanf("%d", &packs);

    // Create the hidden deck
    CardDeck* hiddenDeck = createDeck(packs);
    if (hiddenDeck == NULL) {
        printf("Error creating deck.\n");
        return 1;
    }
    //shuffles hidden deck
    shuffleDeck(hiddenDeck);

    // Create empty working decks
    CardDeck* player1 = createEmptyDeck(); //function to createEmptyDeck does not exist yet (card.c)
    CardDeck* player2 = createEmptyDeck();
    CardDeck* playedDeck = createEmptyDeck();

    /* Deal 8 cards to each player */
    for (int i = 0; i < 8; i++) {
        addCard(player1, drawCard(hiddenDeck)); //function drawCard does not exist (card.c)
        addCard(player2, drawCard(hiddenDeck));
    }

    // Sort both decks for display for the user 
    sortDeck(player1);
    sortDeck(player2);

    // prints both decs for each player
    printf("\nInitial hands:\n");
    printf("\nPlayer 1:\n");
    printDeck(player1);

    printf("\nPlayer 2:\n");
    printDeck(player2);

    // Adds the first card to the played deck
    Card firstCard = drawCard(hiddenDeck); //function doesnt exist
    addCard(playedDeck, firstCard);

    //Prints the first card
    printf("\nFirst card on table: ");
    printCard(&firstCard);//function doesnt exist
    printf("\n");

    // game loop
    while (!isEmpty(player1) && !isEmpty(player2)) { //loops only while both players have cards

        //Player 1
        playTurn(player1, hiddenDeck, playedDeck, 1);//Playturn doesnt exist yet
        //parameters: CardDeck *player, CardDeck *hiddenDeck, CardDeck *playedDeck, int playerNum 
        //if a players card matches, add it to the played pile, if not they draw a card, if that matches add to 
        //the played pile if not, next players turn
        if (isEmpty(player1)) break;// stops the game if someone has no cards left

        //Player 2
        playTurn(player2, hiddenDeck, playedDeck, 2);
        if (isEmpty(player2)) break;

        /* If hidden deck is empty, recycle played pile */
        if (isEmpty(hiddenDeck)) {
            recycleDeck(playedDeck, hiddenDeck); //recycleDeck doesntexist yet
            //moves all cards except last played card to the hidden deck

            //shuffles hidden deck
            shuffleDeck(hiddenDeck);
        }
    }

    // prints out the winner - the player left with no cards
    if (isEmpty(player1)) {
        printf("\nPlayer 1 wins!\n");
    } else {
        printf("\nPlayer 2 wins!\n");
    }

    // frees memory of all decks
    freeDeck(hiddenDeck);
    freeDeck(playedDeck);
    freeDeck(player1);
    freeDeck(player2);

    return 0;
}

//Assumed what functions will be in card.c but will fix it when i know the real functions
// I'm pretty sure I labelled all of the functions that dont exist yet but there might be one that i missed - i will fix that
//comments a bit all over the place, I need to fix them as well as doxygen comments
