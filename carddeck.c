/**
 * @file carddeck.c
 * @brief Implementation of dynamic deck operations
 * @details This fiiles contains functions to create, manipulate, and delete 
 * suffle sort and print of the card deck to be used in main
 * @author Cormac
 * @date 19-11-2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"
#include "carddeck.h"

 /**
  * @brief Swap two cards in memory 
  * @details Helper function to be used later to make the code neater and 
  * easier for me to code
  * @param a Pointer to the first card
  * @param b Pointer to the second card
  * @return void
  */
static void swapCards(Card* a, Card* b)
{
    //saves it into temp so we can swap
    Card temp;
    temp.rank = a->rank;
    temp.suit = a->suit;

    //copys a into b
    a->rank = b->rank;
    a->suit = b->suit;
    //copys b into temp
    b->rank = temp.rank;
    b->suit = temp.suit;
}

/**
 * @brief Compare two cards using rank-major ordering
 * @details We first compare the ranks of the two cards then
 * if they are equal we compare the suits
 * @param lleft is the first card to copmpare
 * @param  right is the second card to compare
 * @return  -1,0 or 1 if left is less than equal to or greater than right
 */
static int compareRankMajor(Card left, Card right)
{// get the rank of both cards
    int leftRank = (int)left.rank;
    int rightRank = (int)right.rank;

	// if the rank of card is difrrent return -1 or 1
    if (leftRank < rightRank) {
        return -1;
    }
    if (leftRank > rightRank) {
        return 1;
    }

	// if ranks are equal compare suits
    int leftSuit = (int)left.suit;
    int rightSuit = (int)right.suit;
	// if the suits are diffrent then return -1 or 1
    if (leftSuit < rightSuit) {
        return -1;
    }
    if (leftSuit > rightSuit) {
        return 1;
    }

    //if both rank and suit are equal we can go ahead and return 0
    return 0;
}
/**
 * @brief Create a new deck with a specified number of packs
 * @details Each pack is a full set of 52 cards in rank-major order
 * eg 2C,2D,2H, AC,AH,AD etc 
 * @param numPacks is the number of packs to include in the deck
 * @return pointer to the newly created deck
 */
CardDeck* createDeck(int numPacks)
{
    // make sure numPacks is positve
    if (numPacks <= 0) {
        return NULL;
    }

	//make space for the deck 
    CardDeck* deck = (CardDeck*)malloc(sizeof(CardDeck));
    if (deck == NULL) {
		return NULL;// check if malloc actually even worked
    }

    // cacluate total number of cards 
    int cardsPerPack = 52;
    int totalCards = numPacks * cardsPerPack;
	// set the size of the deck
    deck->size = totalCards;

	/// Allocate memory for all cards in the deck
    deck->cards = (Card*)malloc((size_t)totalCards * sizeof(Card));
    if (deck->cards == NULL) {
		free(deck);// free the deck if malloc fails to do its job
        return NULL;
    }

  
    int i = 0;

    for (int p = 0; p < numPacks; p++) {
        // loop over all ranks from TWO all the way up to ACE
        for (int r = (int)TWO; r <= (int)ACE; r++) {
         //inner loop covers all suits from CLUB to DIAMOND
            for (int s = (int)CLUB; s <= (int)DIAMOND; s++) {
				// Create a new card with the current rank and suit
                Card newCard;
                // change int to enum types 
                newCard.rank = (Rank)r;
                newCard.suit = (Suit)s;
                // place the new card into the deck at the current number i
                deck->cards[i] = newCard;

				//move to the next position in the deck
                i++;
            }
        }
    }
    // return the new deck
    return deck;
}
/**
 * @brief Add a new card to the end of the deck
 * @details the card is added to the end of the deck 
 * @param deck Pointer to the deck we need to add a card to
 * @param c the Card to add.
 */
void addCard(CardDeck* deck, Card c)
{//check if the deck is NULL to make sure we dont have any issues
    if (deck == NULL) {
        return;
    }
	//check if the cards array is NULL
    if (deck->cards == NULL) {
        return;
    }
	//store the old size and calculate the new size
    int oldSize = deck->size;
    int newSize = oldSize + 1;

    //rezize the 
    Card* resized = (Card*)realloc(deck->cards,
        (size_t)newSize * sizeof(Card));
    if (resized == NULL) {
        //if the realloc fails we just return
        return;
    }

    //update the deck to use the new array and size
    deck->cards = resized;
    deck->size = newSize;

    //add the new card to the end of the deck
    deck->cards[newSize - 1] = c;
}
/**
 * @brief Remove the card form the deck at the given number
 *
 * @details the card at the given number is removedfrom the deck
 * and all cards are shifted down to fill the gap and the size is 
 * shrunk using realloc.
 * @param deck  Pointer to the deck
 * @param The number of the card to remove
 * @return the removed card 
 */
Card removeCard(CardDeck* deck, int index)
{
    // card to return if somthing goes wrong
    Card defaultCard;
    defaultCard.rank =TWO;
    defaultCard.suit =CLUB;
	// check the deck pointer is valid
    if (deck==NULL) {
        return defaultCard;
    }
	// check for vaild intenal array
    if (deck->cards== NULL) {
        return defaultCard;
    }
	//may of done this check above but better safe than sorry change to and || function?
    // Check that deck actually has cards
    if (deck->size <=0) {
        return defaultCard;
    }
    // Check index bounds last
    if (index < 0 || index >= deck->size) {
        return defaultCard;
    }
    //store the card to be removed 
    Card removed = deck->cards[index];

	//shift all the cards after the card to be removed down by one
    for (int i = index; i < deck->size - 1; i++) {
        deck->cards[i] = deck->cards[i + 1];
    }

	//decrease the size of the deck by one
    int newSize = deck->size - 1;
    deck->size = newSize;

	// if the new size is zero free the array and set pointer to NULL
    if (newSize==0) {
		free(deck->cards);// free the array
		deck->cards = NULL;// set pointer to NULL
		return removed;// return the removed card
    }

	//shrink the array using realloc
    Card* shrunk = (Card*)realloc(deck->cards,
		(size_t)newSize * sizeof(Card));// resize the array
	if (shrunk != NULL) {// check if realloc worked
        deck->cards = shrunk;
    }

	return removed;// return the removed card
}
/**
 * @brief Shuffle the deck using the Fisher–Yates shuffle algorithm.
 * @details start from end of deck each card is swapped with another 
 * randomly selected card before its postion or at 
 * @param deck Pointer to the deck to shuffle
 */
void shuffleDeck(CardDeck* deck)
{
    if (deck==NULL) {
        return;
    }else if (deck->cards== NULL) {
        return;
    } else if (deck->size < 2) {
        return;
    }
    int lastposition = deck->size - 1;

    while (lastposition > 0) {

        int range = lastposition + 1;
        int rnd = rand();
        int j = rnd % range;
       
        swapCards(&deck->cards[lastposition], &deck->cards[j]);

		lastposition--;// move to the next position
    }
}

/**
 * @brief Sort using bubble sort in rank-major order
 * @details scans through the deck multiple times swapping coparing ajacent cards 
 * if they are out of order accorting to rank-major order until a full pass is 
 * made with no swaps
 * @param deck ponter to the deck to start
 */
void sortDeck(CardDeck* deck)
{
    if (deck==NULL) {
        return;
    }else if (deck->cards== NULL) {
        return;
    }else if (deck->size < 2) {
        return;
    }
    int last = deck->size - 1;
    int sorted = 0; 

    while (last > 0 && sorted == 0) {

        sorted = 1; 

        for (int j = 1; j <= last; j++) {
            Card left = deck->cards[j - 1];
            Card right = deck->cards[j];
            int crm = compareRankMajor(left, right);
            if (crm > 0){
                swapCards(&deck->cards[j - 1], &deck->cards[j]);
                sorted = 0;
            }
        }

        
        last--;
    }
}
/**
 * @brief Print all the cards in the deck
 * @details this shall print each card on its own line with its number for clarity
 * @param deck Pointer to the deck to print
 */
void printDeck(const CardDeck* deck)
{
    if (deck ==NULL) {
        printf("EMEPTY DECK\n");
        return;
    }else if (deck->cards==NULL) {
        printf("EMEPTY DECK\n");
        return;
    }

    int i = 0;  // start at the first card

    while (i <deck->size) {
        printf("%3d: ", i);
        printCard(&deck->cards[i]); 
        i++; 
    }
}
/**
 * @brief Free all memory associated with the deck
 * @details frees the dynamically allocated array of cards first then frees the deck itself
 * @param deck Pointer to the deck to free
 */
void freeDeck(CardDeck* deck)
{//if the deck is NULL we have nothing to free
    if (deck == NULL) {
        return;
    }

	// First free the dynamically allocated array of cards
    free(deck->cards);
    deck->cards = NULL;
    deck->size = 0;

	// Now free the deck structure itself
    free(deck);
}


//all of it should work now i treid to run it but i need the main to 
// run it and test it properly soz if it actually donst work
//i also dont know if this is fully right due to not having the card.h
// also need to add more comments later on sorry about that

//also need to clean up my comments later sorry about that too
