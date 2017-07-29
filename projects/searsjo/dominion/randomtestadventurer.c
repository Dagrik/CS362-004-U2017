//Joshua Sears
//CS362-400
//Su17
//Assignment 4 - Random Tester for Adventurer Card

//Research on no cards https://www.boardgamegeeks.com/thread/376877/what-happens-when-you-have-no-deck-and-no-discard


//Error where does not check drawcard for errors...if so could not pull non-drawn cards and could exit loop.
//If no treasure cards, then infinite loop occurs in the writing.  If no treasures, seg fault happens upon running program

//Adventurer Card
//Card Text: Reveal cards from your deck until you reveal 2 Treasure cards. Put those Treasure cards into your hand and discard the other revealed cards.
//Special conditions to test: empty deck and discard, deck runs out before pulling 2 treasures, only 1 treasure in deck and discard
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
  /* SORT CARDS IN DECK TO ENSURE DETERMINISM! */

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
	int count, innercount;
	int k[16] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy, copper, silver, gold, estate, duchy, province};
	
	state->numPlayers = rand()%2+2;
	state->playedCardCount = 0;
	int selector=0;//rand()%100;
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
				state->discardCount[count] = (rand()%MAX_DECK)+1;
				break;

			case 2:
				state->deckCount[count] = (rand()%MAX_DECK)+1;
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
				state->hand[count][0] = adventurer;
			} else{
				state->hand[count][innercount] = k[rand()%16];
			}
		}

		if (selector == 4){  //no treasure cards
			for(innercount = 0; innercount < state->deckCount[count]; innercount++){
				state->deck[count][innercount] = k[rand()%10];
			}
			for(innercount = 0; innercount < state->discardCount[count]; innercount++){
				state->discard[count][innercount] = k[rand()%10];
			}
		}

		else if (selector == 5){  //one treasure card
			for(innercount = 0; innercount < state->deckCount[count]; innercount++){
				if(innercount == 0){
					state->deck[count][innercount] = k[10];
				} else {
				state->deck[count][innercount] = k[rand()%10];
				}
			}
			for(innercount = 0; innercount < state->discardCount[count]; innercount++){
				state->discard[count][innercount] = k[rand()%10];
			}
		} else {

			for(innercount = 0; innercount < state->deckCount[count]; innercount++){
				state->deck[count][innercount] = k[rand()%16];
			}
			for(innercount = 0; innercount < state->discardCount[count]; innercount++){
				state->discard[count][innercount] = k[rand()%16];
			}
		}
	}
	
	return;
}

int testAdventurer(){
	int test_result = 0;
	int count, card, testloop;
	
	struct gameState preState, postState;


for(testloop=0; testloop<500; testloop++){
	int keptTreasures = 0;
	int shuffle_flag = 0;

	
	
	//copy gameState over to pre
	setupState(&postState);
	memcpy(&preState, &postState, sizeof(struct gameState));
	
	if(LONG_ERRORS){
		printf("\nTest %i\n", testloop+1);
		printf("\nInitial Setup:\nPRE: Hand %i, Deck %i and Discard %i\n", preState.handCount[preState.whoseTurn],  preState.deckCount[preState.whoseTurn], preState.discardCount[preState.whoseTurn]);
		printf("\nPOST: Hand %i, Deck %i and Discard %i\n", postState.handCount[preState.whoseTurn], postState.deckCount[preState.whoseTurn], postState.discardCount[preState.whoseTurn]);
	}
	//run cardEffect on postState
	//random setup always has adventurer card in handpos 0
	cardEffect(adventurer, 1, 0, 0, &postState, 0, 0);
	

	//manually change preState
	int curPlayer = preState.whoseTurn;
	
	if(!(preState.deckCount[curPlayer] == 0 && preState.discardCount[curPlayer] == 0)){	
		while(keptTreasures < 2 && !shuffle_flag){  //until two treasures are drawn or until discard shuffled and deck is at 0 again
			//draw a card from the deck, test if treasure.  keep if so, discard otherwise
		
			if(preState.deckCount[curPlayer] < 1){
				
					for(count = 0; count < preState.discardCount[curPlayer]; count++){
						preState.deck[curPlayer][count] = preState.discard[curPlayer][count];
						preState.discard[curPlayer][count] = -1;
						preState.deckCount[curPlayer]++;
					}
					preState.discardCount[curPlayer] = 0;
					shuffler(curPlayer, &preState);
					shuffle_flag=1;
			}
			card = preState.deck[curPlayer][preState.deckCount[curPlayer]-1];
			
			preState.deckCount[curPlayer]--;
			if(card == copper || card == silver || card == gold){
				preState.hand[curPlayer][preState.handCount[curPlayer]] = card;
				preState.handCount[curPlayer]++;
				keptTreasures++;
				
			} else {
				preState.discard[curPlayer][preState.discardCount[curPlayer]] = card;
				preState.discardCount[curPlayer]++;
			}

		}
	
		//move adventurer card to playedHand
		preState.playedCards[preState.playedCardCount] = preState.hand[curPlayer][0];
		preState.playedCardCount++;

		preState.hand[curPlayer][0] = -1;
		if(preState.handCount[curPlayer] == 1){
			preState.handCount[curPlayer]--;
		} else {
			preState.hand[curPlayer][0] = preState.hand[curPlayer][preState.handCount[curPlayer]-1];
			preState.hand[curPlayer][preState.handCount[curPlayer]-1] = -1;
			preState.handCount[curPlayer]--;
		}
}
	if(LONG_ERRORS){
		printf("\nAfter Adventurer:\nPRE: Hand %i, Deck %i and Discard %i\n", preState.handCount[preState.whoseTurn],  preState.deckCount[preState.whoseTurn], preState.discardCount[preState.whoseTurn]);
		printf("\nPOST: Hand %i, Deck %i and Discard %i\n", postState.handCount[preState.whoseTurn], postState.deckCount[preState.whoseTurn], postState.discardCount[preState.whoseTurn]);
	}

	//test and compare values
	if(preState.handCount[curPlayer] != postState.handCount[curPlayer]){
		test_result = -1;
			printf("\nTest %i\n", testloop+1);
			printf ("HandCount Mismatch.  Expected: %i, Actual: %i\n", preState.handCount[curPlayer], postState.handCount[curPlayer]);
			if(LONG_ERRORS){
			printf("\nExpected Hand:");
			for(count = 0; count < preState.handCount[curPlayer]; count++){
				printf("%i, ", preState.hand[curPlayer][count]);
			}
			printf("\n\nActual Hand: ");
			for(count = 0; count < postState.handCount[curPlayer]; count++){
				printf("%i, ", postState.hand[curPlayer][count]);
			}
			printf("\nExpected Discard:");
			for(count = 0; count < preState.discardCount[curPlayer]; count++){
				printf("%i, ", preState.discard[curPlayer][count]);
			}
			
			printf("\n\nActual Discard: ");
			for(count = 0; count < postState.discardCount[curPlayer]; count++){
				printf("%i, ", postState.discard[curPlayer][count]);
			}
			printf("\n");
		}

	}
	if(keptTreasures == 2){
		if((postState.hand[curPlayer][0] != copper && postState.hand[curPlayer][0] != silver &&
	   		postState.hand[curPlayer][0] != gold) || (postState.hand[curPlayer][postState.handCount[curPlayer]-1] != copper && 
	   		postState.hand[curPlayer][postState.handCount[curPlayer]-1] != silver && postState.hand[curPlayer][postState.handCount[curPlayer]-1] != gold)) {
				test_result = -1;
				if(LONG_ERRORS)
					printf ("Draw Error - Not Treasures.\n");
		}
	}

	if(keptTreasures == 1){
		if(postState.hand[curPlayer][0] != copper && postState.hand[curPlayer][0] != silver && postState.hand[curPlayer][0] != gold) {
				test_result = -1;
				if(LONG_ERRORS)
					printf ("Draw Error - Not Treasures.\n");
		}
	}

	if(postState.hand[curPlayer][0] == adventurer && preState.hand[curPlayer][0] != adventurer){
		test_result = -1;
		if(LONG_ERRORS)
			printf ("Adventurer Card Still in Hand.\n");
	}


	for(count = 0; count < preState.numPlayers; count++){
		if(count!=curPlayer){
			if(preState.handCount[count] != postState.handCount[count] || preState.deckCount[count] != postState.deckCount[count] || 
				preState.discardCount[count] != postState.discardCount[count]){
				test_result = -1;
				if(LONG_ERRORS)
					printf ("Affected Other Players.  Expected (Deck, Hand, Discard): %i, %i, %i Actual (Deck, Hand, Discard): %i, %i, %i\n", 
						preState.deckCount[count], preState.handCount[count], preState.discardCount[count], postState.deckCount[count], postState.handCount[count], postState.discardCount[count]);
			}
		}
	}

}
	return test_result;
}


int main(){
	srand(time(NULL));
	printf("*** Adventurer Card Random Testing ***\n");
	int result = testAdventurer();
	if(result == -1){
		printf("\nTest Failed.  Please see above errors for details.\n");
	} else {
		printf("All Tests Passed\n");
	}
	return 0;
}