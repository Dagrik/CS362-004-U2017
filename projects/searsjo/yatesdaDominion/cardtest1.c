//Joshua Sears
//CS362-400
//Su17
//Assignment 3 - Card Test for altered Smithy



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>


int testSmithy(){
	int numPlayers = MAX_PLAYERS;
	int curHandCt[numPlayers];
	int curDiscardCt[numPlayers];
	int curDeckCt[numPlayers];
	int count;

	int randomSeed = 2;
	struct gameState testState;
	int bonus = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};
	int test_status=0;
	initializeGame(numPlayers, k, randomSeed, &testState);

	int testHand[5] = {smithy, copper, copper, copper, copper};
	int testDeck[MAX_DECK];

	for (count = 0; count<MAX_DECK; count++){
		testDeck[count] = copper;
	}

	testState.handCount[0] = 5;
	testState.deckCount[0] = MAX_DECK;
	memcpy(testState.hand[0], testHand, 5*sizeof(int));
	memcpy(testState.deck[0], testDeck, MAX_DECK*sizeof(int));


		//save current counts for all players
		for(count = 0; count<numPlayers; count++){
			curHandCt[count] = testState.handCount[count];
			curDiscardCt[count] = testState.discardCount[count];
			curDeckCt[count] = testState.deckCount[count];
		}
		int curPlayedCt = testState.playedCardCount;

		cardEffect(smithy, 1, 0, 0, &testState, 0, &bonus);

		printf("\nCURRENT PLAYER DECK, DISCARD, AND DECK TEST:\n");
	//smithy card discarded, add three new cards.
		if(testState.handCount[0] != curHandCt[0]+2 || testState.deckCount[0] != curDeckCt[0] - 3 || testState.discardCount[0] != curDiscardCt[count] || testState.playedCardCount != curPlayedCt+1){
			test_status = -1;
			printf("***PLAYER DECK, DISCARD, AND DECK TEST Failed.***\n");
			printf("Hand: Actual %i Expected %i\n", testState.handCount[0], curHandCt[0]+2);
			 printf("Deck: Actual %i Expected %i\n", testState.deckCount[0], curDeckCt[0]-3);
			 printf("Discard: Actual %i Expected %i\n", testState.discardCount[0], curDiscardCt[0]);
			 printf("Played: Actual %i Expected %i\n", testState.playedCardCount, curPlayedCt + 1);
		}else{
			printf("Test Passed.\n");
		}

	//Ensure other players hand deck and discard count did not change.	
		printf("\nTESTING OTHER PLAYER HAND, DECK, AND DISCARD PILES:\n");
		for(count = 1; count<numPlayers; count++){
			printf("Player Position %i - ", count);
			if(testState.handCount[count] != curHandCt[count] || testState.deckCount[count] != curDeckCt[count] || testState.discardCount[count] != curDiscardCt[count]){
				test_status = -1;
				printf("Test Failed. Hand: %i, Deck: %i, Discard:%i \n", testState.handCount[0], testState.deckCount[0], testState.discardCount[0]);
			}else{
				printf("Test Passed.\n");
			}
		}
		
return test_status;

}

int main(){
printf("\n***TESTING SMITHY CARD***\n\n");
 int result = testSmithy();
 printf("\n***SMITHY CARD TESTING COMPLETE***\n");
 	if(result == -1){
		printf("\n\n***Some Tests Failed.  Please Check Messages Above.***\n");
		return 0;
	}

	printf("\n\n***All Tests Passed.***\n");
	return 0;
}
