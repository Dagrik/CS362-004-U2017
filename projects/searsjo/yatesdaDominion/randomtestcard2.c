//Joshua Sears
//CS362-400
//Su17
//Assignment 4 - Random Tester for Council Room Card



//Card definition
//Council Room - +4 Cards (from deck), +1 Buy (ability to purchase additional card), all other players +1 Card

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
	council_room, tribute, smithy, copper, silver, gold, estate, duchy, province};
	
	selector = rand()%100; //chooses from special conditions or general random values

	state->numPlayers = rand()%2+2;
	state->playedCardCount = 0;
	state->numBuys = rand()%10 + 1;
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
				state->hand[count][0] = council_room;
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


int testCouncilRoom(){

	int test_status = 0;
	int count, testloop, innercount;
	
	struct gameState preState, postState;


	for(testloop = 0; testloop<10*MAX_DECK; testloop++){
		//copy gameState over to pre
		setupState(&postState);
		memcpy(&preState, &postState, sizeof(struct gameState));
		int player = preState.whoseTurn;

		if(LONG_ERRORS){
			printf("\nTest %i\n", testloop+1);
			printf("\nInitial Setup:\nExpected: Hand %i, Deck %i Discard %i and Buys %i\n", preState.handCount[preState.whoseTurn],  preState.deckCount[preState.whoseTurn], preState.discardCount[preState.whoseTurn], preState.numBuys);
			printf("Actual: Hand %i, Deck %i Discard %i and Buys %i\n", postState.handCount[preState.whoseTurn], postState.deckCount[preState.whoseTurn], postState.discardCount[preState.whoseTurn], postState.numBuys);
			for(count = 0; count< preState.numPlayers; count++){
				if(count != player){
					printf("Player %i:\n Expected: Hand %i, Deck %i Discard %i\nActual: Hand %i, Deck %i Discard %i\n", count, preState.handCount[count],  preState.deckCount[count], preState.discardCount[count], postState.handCount[count], postState.deckCount[count], postState.discardCount[count]);
				}
			}
		}
		//run cardEffect on postState
		//random setup always has village card in handpos 0
		cardEffect(council_room, 1, 0, 0, &postState, 0, 0);

		//Play card manually in preState

		//+4 Cards for current player
		for(count=0; count<4; count++){
			if(preState.deckCount[player] < 1){	
				for(innercount = 0; innercount < preState.discardCount[player]; innercount++){
					preState.deck[player][innercount] = preState.discard[player][innercount];
					preState.discard[player][innercount] = -1;
					preState.deckCount[player]++;
				}
				preState.discardCount[player] = 0;
				shuffler(player, &preState);
			}
			if(preState.deckCount[player] > 0){
				preState.hand[player][preState.handCount[player]] = preState.deck[player][preState.deckCount[player]-1];
				preState.deck[player][preState.deckCount[player]-1] = -1;
				preState.deckCount[player]--;
				preState.handCount[player]++;
			}
		}

		//+1 Buy
		preState.numBuys++;

		//Each other player draws one card
		for(count=0; count<preState.numPlayers; count++){
			if(count!=player){
				if(preState.deckCount[count] < 1){	
					for(innercount = 0; innercount < preState.discardCount[count]; innercount++){
						preState.deck[count][innercount] = preState.discard[count][innercount];
						preState.discard[count][innercount] = -1;
						preState.deckCount[count]++;
					}
					preState.discardCount[count] = 0;
					shuffler(count, &preState);
				}
				
				if(preState.deckCount[count] > 0){
					preState.hand[count][preState.handCount[count]] = preState.deck[count][preState.deckCount[count]-1];
					preState.deck[count][preState.deckCount[count]-1] = -1;
					preState.deckCount[count]--;
					preState.handCount[count]++;
				}
			}
		}

		//Move council room card to playedCard stack
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

		//Test by comparison

		if(LONG_ERRORS){
			
			printf("\nAfter Council Room:\nExpected: Hand %i, Deck %i Discard %i and Buys %i\n", preState.handCount[preState.whoseTurn],  preState.deckCount[preState.whoseTurn], preState.discardCount[preState.whoseTurn], preState.numBuys);
			printf("Actual: Hand %i, Deck %i Discard %i and Buys %i\n", postState.handCount[preState.whoseTurn], postState.deckCount[preState.whoseTurn], postState.discardCount[preState.whoseTurn], postState.numBuys);
			for(count = 0; count< preState.numPlayers; count++){
				if(count != player){
					printf("Player %i:\n Expected: Hand %i, Deck %i Discard %i\nActual: Hand %i, Deck %i Discard %i\n", count, preState.handCount[count],  preState.deckCount[count], preState.discardCount[count], postState.handCount[count], postState.deckCount[count], postState.discardCount[count]);
				}
			}
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
		//test for actions
		if(preState.numBuys != postState.numBuys){
			test_status = -1;
			printf("\nTest %i\n", testloop+1);
			printf("Buy Count Error - Expected: %i, Actual: %i\n", preState.numBuys, postState.numBuys);
		}
		for(count=0; count<preState.numPlayers; count++){
			if(count != player){
				if((preState.deckCount[count] != postState.deckCount[count]) || (preState.handCount[count] != postState.handCount[count]) || (preState.discardCount[count] != postState.discardCount[count])){
					test_status = -1;
					printf("\nTest %i\n", testloop+1);
					printf("Player %i Values Incorrect.\n", count);
				}
			}
		}
	}

	return test_status;
}



int main(){
	srand(time(NULL));
	printf("*** Council Room Card Random Testing ***\n");
	int result = testCouncilRoom();
	if(result == -1){
		printf("\nTest Failed.  Please see above errors for details.\n");
	} else {
		printf("\nAll Tests Passed\n");
	}
	return 0;
}