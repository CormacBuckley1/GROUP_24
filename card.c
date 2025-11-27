/**
 * @file card.c
 * @brief Implementation of functions used for handling Card objects.
 *
 * This file contains the logic for:
 *  - Converting suit and rank values to readable strings.
 *  - Printing cards using printCard().
 *  - Checking if two cards match using cardMatches().
 *
 * All functionality in this file supports the Card ADT defined in card.h.
 *
 * @author Jusmir
 * @date 26/111/25
 */

#include <stdio.h>
#include "card.h"

/**
 * @brief Converts a Suit enum to a string.
 *
 * @param s The Suit value.
 * @return A string such as "Hearts" or "Spades".
 */

static const char *suitToString(Suit s)
{
    switch (s) {
    case CLUB:    return "Clubs";
    case SPADE:   return "Spades";
    case HEART:   return "Hearts";
    case DIAMOND: return "Diamonds";
    default:      return "UnknownSuit";
    }
}

/**
 * @brief Converts a Rank enum to a string.
 *
 * @param r The Rank value.
 * @return A string such as "King" or "Two".
 */

static const char *rankToString(Rank r)
{
    switch (r) {
    case TWO:   return "Two";
    case THREE: return "Three";
    case FOUR:  return "Four";
    case FIVE:  return "Five";
    case SIX:   return "Six";
    case SEVEN: return "Seven";
    case EIGHT: return "Eight";
    case NINE:  return "Nine";
    case TEN:   return "Ten";
    case JACK:  return "Jack";
    case QUEEN: return "Queen";
    case KING:  return "King";
    case ACE:   return "Ace";
    default:    return "UnknownRank";
    }
}

/**
 * @brief Prints a card using "Rank of Suit" format.
 *
 * Example:
 * @code
 * Card c = {HEART, FIVE};
 * printCard(&c);   // Output: Five of Hearts
 * @endcode
 *
 * @param c Pointer to a valid Card structure. If NULL → prints "NULL card".
 */

void printCard(const Card *c)
{
    if (c == NULL) {
        printf("NULL card");
        return;
    }


    printf("%s of %s", rankToString(c->rank), suitToString(c->suit));
}

/**
 * @brief Checks whether two cards match by suit or rank.
 *
 * Matching rules:
 *  - Same rank  → match (e.g. Five of Hearts & Five of Diamonds)
 *  - Same suit  → match (e.g. King of Hearts & Two of Hearts)
 *
 * @param c   Card being tested.
 * @param top Top card on the played deck.
 * @return 1 if cards match, otherwise 0.
 */

int cardMatches(const Card *c, const Card *top)
{
    if (c == NULL || top == NULL) {
        return 0;
    }

    if (c->suit == top->suit) {
        return 1;
    }

    if (c->rank == top->rank) {
        return 1;
    }

    return 0;
}

