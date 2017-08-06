//Joshua Sears
//CS362-400
//Su17
//Assignment 3 - Card Test for council room



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>


int testCouncilRoom(){
	int numPlayers = MAX_PLAYERS;
	int curHandCt[numPlayers];
	int curDiscardCt[numPlayers];
	int curDeckCt[numPlayers];
	int curPlayedCt, curBuyCt;
	int count;
	int test_status=0;
	int bonus=0;

//create gameState and decks
	int randomSeed = 2;
	struct gameState testState;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};
	
	initializeGame(numPlayers, k, randomSeed, &testState);

	int testHand[5] = {council_room, estate, estate, estate, estate};
	int testDeck[MAX_DECK];

	for (count = 0; count<MAX_DECK; count++){
		testDeck[count] = council_room;
	}

	//alter gameState for testing
	for(count = 0; count<numPlayers;count++){
		testState.handCount[count] = 5;
		testState.deckCount[count] = MAX_DECK;
		memcpy(testState.hand[count], testHand, 5*sizeof(int));
		memcpy(testState.deck[count], testDeck, MAX_DECK*sizeof(int));
	}
	printf("\n***Council Room Card Test***\n\n");
	
		
		for(count = 0; count<numPlayers; count++){
			curHandCt[count] = testState.handCount[count];
			curDiscardCt[count] = testState.discardCount[count];
			curDeckCt[count] = testState.deckCount[count];
		}
		curPlayedCt = testState.playedCardCount;
		curBuyCt = testState.numBuys;

		//Play card with cardEffect and subtract one action (other functions in playCard are not tested.)
		cardEffect(council_room, 1, 0, 0, &testState, 0, &bonus);
		testState.numActions--;

		printf("\nCURRENT PLAYER CARD PILES AND ACTIONS TEST:\n");
		if(testState.handCount[0] != curHandCt[0]+3 || testState.deckCount[0] != curDeckCt[0] - 4 || testState.discardCount[0] != curDiscardCt[0] 
			|| testState.playedCardCount != curPlayedCt+1 || testState.numBuys != curBuyCt+1){
			test_status = -1;
			printf("***PLAYER DECK, DISCARD, AND DECK TEST Failed.***\n");
			printf("Hand: Actual %i Expected %i\n", testState.handCount[0], curHandCt[0]+3);
			 printf("Deck: Actual %i Expected %i\n", testState.deckCount[0], curDeckCt[0]-4);
			 printf("Discard: Actual %i Expected %i\n", testState.discardCount[0], curDiscardCt[0]);
			 printf("Played: Actual %i Expected %i\n", testState.playedCardCount, curPlayedCt + 1);
			 printf("Buys: Actual %i Expected %i\n", testState.numBuys, curBuyCt + 1);
		}else{
			printf("Test Passed.\n");
		}

	//Ensure other players hand deck and discard count did not change.	
		printf("\nTESTING OTHER PLAYER HAND, DECK, AND DISCARD PILES:\n");
		for(count = 1; count<numPlayers; count++){
			printf("Player Position %i - ", count);
			if(testState.handCount[count] != curHandCt[count]+1 || testState.deckCount[count] != curDeckCt[count]-1 || testState.discardCount[count] != curDiscardCt[count]){
				test_status = -1;
				printf("Hand: Actual %i Expected %i\n", testState.handCount[count], curHandCt[count]+1);
			 	printf("Deck: Actual %i Expected %i\n", testState.deckCount[count], curDeckCt[count]-1);
			 	printf("Discard: Actual %i Expected %i\n", testState.discardCount[count], curDiscardCt[count]);
			}else{
				printf("Test Passed.\n");
			}
		}
	

	return test_status;
}


int main(){
printf("\n***TESTING COUNCIL ROOM CARD***\n\n");
 int result = testCouncilRoom();
 printf("\n***COUNCIL ROOM CARD TESTING COMPLETE***\n\n");
 	if(result == -1){
		printf("\n\n***Some Tests Failed.  Please Check Messages Above.***\n");
		return 0;
	}

	printf("\n\n***All Council Room Tests Passed.***\n");
	return 0;
}
