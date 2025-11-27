/**
 * @file card.h
 * @brief This file defines the data types and function prototypes used to show
 *        a single playing card in a standard 52-card deck.
 *
 * The Card data type consists of:
 *  - A suit (Club, Spade, Heart, Diamond)
 *  - A rank (Two all the way to Ace eg. Ace is the highest King is the second highest and 2 is the lowest)
 *
 * This header also declares two functions:
 *  - printCard():  shows a card in human-readable format.
 *  - cardMatches(): Determines whether two cards match (same suit or same rank).
 *
 * The types in this file are designed to be general and reused in any card-based game.
 *
 * @author YOUR NAME
 * @date 2025-11-26
 */


#ifndef CARD_H
#define CARD_H

/**
 * @enum Suit
 * @brief Enum representing the four suits of a standard card deck.
 *
 * These are used in the @ref Card struct to show the suit of a card.
 * They cover all standard playing card suits.
 */
typedef enum {
    CLUB,     /**< Clubs       */
    SPADE,    /**< Spades      */
    HEART,    /**< Hearts      */
    DIAMOND   /**< Diamonds    */
} Suit;


/**
 * @enum Rank
 * @brief Enumeration representing all valid card ranks.
 *
 * Values start at TWO (index 0) and go up to ACE.
 * These values are used inside the @ref Card struct.
 */

typedef enum {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
} Rank;

/**
 * @struct Card
 * @brief Represents a single card with a suit and rank.
 *
 * A card consists of:
 *  - A suit (Club, Spade, Heart, Diamond)
 *  - A rank (Two to Ace)
 */

typedef struct {
    Suit suit;
    Rank rank;
} Card;

/**
 * @brief Prints a card in human-readable form.
 *
 * Example output: "Five of Hearts"
 *
 * @param c Pointer to a valid @ref Card structure.
 *          If NULL is passed, the function prints "NULL card".
 */

void printCard(const Card *c);

/**
 * @brief Checks whether a card matches another card.
 *
 * Two cards are considered a match if:
 *  - They have the same suit, OR
 *  - They have the same rank.
 *
 * @param c   Pointer to the card from the player's hand.
 * @param top Pointer to the top card of the played deck.
 * @return 1 if cards match, 0 otherwise.
 */

int cardMatches(const Card *c, const Card *top);

#endif /* CARD_H */
