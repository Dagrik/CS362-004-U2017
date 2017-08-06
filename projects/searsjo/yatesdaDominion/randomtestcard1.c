//Joshua Sears
//CS362-400
//Su17
//Assignment 4 - Random Tester for Village Card

//Research on no cards https://www.boardgamegeeks.com/thread/376877/what-happens-when-you-have-no-deck-and-no-discard

//Village card gives +1 Card (draw one card from deck) and +2 Actions (but costs one to use)

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define LONG_ERRORS 1

int comparer(const void* a, const void* b) {
  if (*(int*)a > *(int*)b)
    return 1;
  if (*(int*)a < *(int*)b)
    return -1;
  return 0;
}

int shuffler(int player, struct gameState *state) {
 

  int newDeck[MAX_DECK];
  int newDeckPos = 0;
  int card;
  int i;

  if (state->deckCount[player] < 1)
    return -1;
  qsort ((void*)(state->deck[player]), state->deckCount[player], sizeof(int), comparer); 

  while (state->deckCount[player] > 0) {
    card = floor(Random() * state->deckCount[player]);
    newDeck[newDeckPos] = state->deck[player][card];
    newDeckPos++;
    for (i = card; i < state->deckCount[player]-1; i++) {
      state->deck[player][i] = state->deck[player][i+1];
    }
    state->deckCount[player]--;
  }
  for (i = 0; i < newDeckPos; i++) {
    state->deck[player][i] = newDeck[i];
    state->deckCount[player]++;
  }

  return 0;
}

void setupState(struct gameState *state){
	int count, innercount, selector;
	int k[16] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy, copper, silver, gold, estate, duchy, province};
	
	selector=rand()%100;
	state->numPlayers = rand()%2+2;
	state->playedCardCount = 0;
	state->numActions = rand()%20 + 1;
	state->whoseTurn = rand()%state->numPlayers;
	for(count = 0; count <  state->numPlayers; count++){

		state->handCount[count] = rand()%(MAX_HAND) + 1;
		
		switch(selector){

			case 0:
				state->deckCount[count] = 0;
				state->discardCount[count] = 0;
				break;

			case 1:
				state->deckCount[count] = 0;
				state->discardCount[count] = rand()%(MAX_DECK)+1;
				break;

			case 2:
				state->deckCount[count] = rand()%(MAX_DECK)+1;
				state->discardCount[count] = 0;
				break;

			case 3:
				state->deckCount[count] = MAX_DECK;
				state->discardCount[count] = MAX_DECK;	
				state->handCount[count] = MAX_HAND;
				break;
			
			default:
				state->deckCount[count] = (rand()%MAX_DECK)+1;
				state->discardCount[count] = (rand()%MAX_DECK)+1;
		}
		for(innercount = 0; innercount < state->handCount[count]; innercount++){
			if(innercount ==0){
				state->hand[count][0] = village;
			} else{
				state->hand[count][innercount] = k[rand()%16];
			}
		}
		for(innercount = 0; innercount < state->deckCount[count]; innercount++){
			state->deck[count][innercount] = k[rand()%16];
		}
		for(innercount = 0; innercount < state->discardCount[count]; innercount++){
			state->discard[count][innercount] = k[rand()%16];
		}
	}

	
	return;
}

int testVillage(){

	int test_status = 0;
	int count, testloop;
	
	struct gameState preState, postState;


	for(testloop = 0; testloop<MAX_DECK*10; testloop++){
		//copy gameState over to pre
		setupState(&postState);
		memcpy(&preState, &postState, sizeof(struct gameState));
		int player = preState.whoseTurn;

		if(LONG_ERRORS){
			printf("\nTest %i\n", testloop+1);
			printf("\nInitial Setup:\nExpected: Hand %i, Deck %i Discard %i and Actions %i\n", preState.handCount[preState.whoseTurn],  preState.deckCount[preState.whoseTurn], preState.discardCount[preState.whoseTurn], preState.numActions);
			printf("\nActual: Hand %i, Deck %i Discard %i and Actions %i\n", postState.handCount[preState.whoseTurn], postState.deckCount[preState.whoseTurn], postState.discardCount[preState.whoseTurn], postState.numActions);
		}
		//run cardEffect on postState
		//random setup always has village card in handpos 0
		cardEffect(village, 1, 0, 0, &postState, 0, 0);

		//manually do the same thing to the preState

		//if deck is empty

		if(preState.deckCount[player] < 1){	
			for(count = 0; count < preState.discardCount[player]; count++){
				preState.deck[player][count] = preState.discard[player][count];
				preState.discard[player][count] = -1;
				preState.deckCount[player]++;
			}
			preState.discardCount[player] = 0;
			shuffler(player, &preState);
		}

		//Subtract one action for using card
		//preState.numActions--;

		//+1 Card
		if(preState.deckCount[player] > 0){
			preState.hand[player][preState.handCount[player]] = preState.deck[player][preState.deckCount[player] -1];
			preState.handCount[player]++;
			preState.deckCount[player]--;
		}
		//+2 Actions
		preState.numActions = preState.numActions + 2;

		//Move village card to played
		preState.playedCards[preState.playedCardCount] = preState.hand[player][0];
		preState.playedCardCount++;

		preState.hand[player][0] = -1;
		if(preState.handCount[player] == 1){
			preState.handCount[player]--;
		} else {
			preState.hand[player][0] = preState.hand[player][preState.handCount[player]-1];
			preState.hand[player][preState.handCount[player]-1] = -1;
			preState.handCount[player]--;
		}

		if(LONG_ERRORS){
			
			printf("\nAfter Village:\nExpected: Hand %i, Deck %i Discard %i and Actions %i\n", preState.handCount[preState.whoseTurn],  preState.deckCount[preState.whoseTurn], preState.discardCount[preState.whoseTurn], preState.numActions);
			printf("\nActual: Hand %i, Deck %i Discard %i and Actions %i\n", postState.handCount[preState.whoseTurn], postState.deckCount[preState.whoseTurn], postState.discardCount[preState.whoseTurn], postState.numActions);
		}

		//test card change
		if(preState.deckCount[player] != postState.deckCount[player]){
			test_status = -1;
			printf("\nTest %i\n", testloop+1);
			printf("Deck Counts Do Not Match - Expected: %i, Actual: %i\n", preState.deckCount[player], postState.deckCount[player]);
		}
		if(preState.handCount[player] != postState.handCount[player]){
			test_status = -1;
			printf("\nTest %i\n", testloop+1);
			printf("Hand Counts Do Not Match - Expected: %i, Actual: %i\n", preState.handCount[player], postState.handCount[player]);
		}
		if(preState.discardCount[player] != postState.discardCount[player]){
			test_status = -1;
			printf("\nTest %i\n", testloop+1);
			printf("Discard Counts Do Not Match - Expected: %i, Actual: %i\n", preState.discardCount[player], postState.discardCount[player]);
		}
		for(count=0; count<preState.numPlayers; count++){
			if(count != player){
				if((preState.deckCount[count] != postState.deckCount[count]) || (preState.handCount[count] != postState.handCount[count]) || (preState.discardCount[count] != postState.discardCount[count])){
					test_status = -1;
					printf("\nTest %i\n", testloop+1);
					printf("Player %i Values Changed.\n", count);
				}
			}
		}

		//test for actions
		if(preState.numActions != postState.numActions){
			test_status = -1;
			printf("\nTest %i\n", testloop+1);
			printf("Action Count Error - Expected: %i, Actual: %i\n", preState.numActions, postState.numActions);
		}
	}
	return test_status;
}

int main(){
	srand(time(NULL));
	printf("*** Village Card Random Testing ***\n");
	int result = testVillage();
	if(result == -1){
		printf("\nTest Failed.  Please see above errors for details.\n");
	} else {
		printf("All Tests Passed\n");
	}
	return 0;
}