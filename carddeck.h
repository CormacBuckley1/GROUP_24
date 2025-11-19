#ifndef CARDDECK_H
#define CARDDECK_H

#include "card.h"


typedef struct {
    Card* cards; 
    int size;   
} CardDeck;

CardDeck* createDeck(int numPacks);
void addCard(CardDeck* deck, Card c);
Card removeCard(CardDeck* deck, int index);
void shuffleDeck(CardDeck* deck);
void sortDeck(CardDeck* deck);
void printDeck(const CardDeck* deck);
void freeDeck(CardDeck* deck);

#endif

