//Joshua Sears
//CS362-400
//Su17
//Assignment 3 - Card Test for Adventurer



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>

//Adventurer card is supposed to allow a player to add 2 treasures to their hand by
//continuing to draw until two are found, then discarding others that were drawn (dominion wiki)
int testAdv(){
	int numPlayers = MAX_PLAYERS;
	int curHandCt[numPlayers];
	int curDiscardCt[numPlayers];
	int curDeckCt[numPlayers];
	int curPlayedCt;
	int count;
	int test_status=0;
	int bonus=0;

//create gameState and decks
	int randomSeed = 2;
	struct gameState testState;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};
	
	initializeGame(numPlayers, k, randomSeed, &testState);

	int testHand[5] = {adventurer, copper, copper, copper, copper};
	int testDeck[MAX_DECK];

//init testDeck with 1 treasure and 2 non-treasures
//assign all types of treasure cards 
	for (count = 0; count<MAX_DECK; count++){
		if((count+1)%5==0){
			if((count+1)%15 == 0){
				testDeck[count] = gold;
			} else if((count+1)% 10 == 0){
				testDeck[count] = silver;
			} else {
				testDeck[count] = copper;
			}
		} else {
			testDeck[count] = estate;
		}
	}

//alter gameState for testing
	testState.handCount[0] = 5;
	testState.deckCount[0] = MAX_DECK;
	memcpy(testState.hand[0], testHand, 5*sizeof(int));
	memcpy(testState.deck[0], testDeck, MAX_DECK*sizeof(int));
	printf("\n***Adventurer Card Test***\n***Every 5th Card in Deck is a Treasure***\n\n");

//first iteration test
	for(count = 0; count<numPlayers; count++){
				curHandCt[count] = testState.handCount[count];
				curDiscardCt[count] = testState.discardCount[count];
				curDeckCt[count] = testState.deckCount[count];
		}
		curPlayedCt = testState.playedCardCount;

		//play the adventurer card
		cardEffect(adventurer, 1, 0, 0, &testState, 0, &bonus);


	printf("\nCURRENT PLAYER DECK, DISCARD, AND DECK TEST:\n");
		if(testState.handCount[0] != curHandCt[0]+1 || testState.deckCount[0] != curDeckCt[0] - 6 || testState.discardCount[0] != curDiscardCt[0]+4 || testState.playedCardCount != curPlayedCt+1){
			test_status = -1;
			printf("***PLAYER DECK, DISCARD, AND DECK TEST Failed.***\n");
			printf("Hand: Actual %i Expected %i\n", testState.handCount[0], curHandCt[0]+1);
			 printf("Deck: Actual %i Expected %i\n", testState.deckCount[0], curDeckCt[0]-6);
			 printf("Discard: Actual %i Expected %i\n", testState.discardCount[0], curDiscardCt[0]+4);
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
				printf("Hand: Actual %i Expected %i\n", testState.handCount[count], curHandCt[count]);
			 	printf("Deck: Actual %i Expected %i\n", testState.deckCount[count], curDeckCt[count]);
			 	printf("Discard: Actual %i Expected %i\n", testState.discardCount[count], curDiscardCt[count]);
			}else{
				printf("Test Passed.\n");
			}
		}


	//get current card counts for later testing
		
		
		for(count = 0; count<numPlayers; count++){
				curHandCt[count] = testState.handCount[count];
				curDiscardCt[count] = testState.discardCount[count];
				curDeckCt[count] = testState.deckCount[count];
		}
		curPlayedCt = testState.playedCardCount;

		//play the adventurer card
		cardEffect(adventurer, 1, 0, 0, &testState, 0, &bonus);


	printf("\nCURRENT PLAYER DECK, DISCARD, AND DECK TEST:\n");
		if(testState.handCount[0] != curHandCt[0]+1 || testState.deckCount[0] != curDeckCt[0] - 10 || testState.discardCount[0] != curDiscardCt[0]+8 || testState.playedCardCount != curPlayedCt+1){
			test_status = -1;
			printf("***PLAYER DECK, DISCARD, AND DECK TEST Failed.***\n");
			printf("Hand: Actual %i Expected %i\n", testState.handCount[0], curHandCt[0]+1);
			 printf("Deck: Actual %i Expected %i\n", testState.deckCount[0], curDeckCt[0]-10);
			 printf("Discard: Actual %i Expected %i\n", testState.discardCount[0], curDiscardCt[0]+8);
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
printf("\n***TESTING ADVENTURER CARD***\n\n");
 int result = testAdv();
 printf("\n***ADVENTURER CARD TESTING COMPLETE***\n");
 	if(result == -1){
		printf("\n\n***Some Tests Failed.  Please Check Messages Above.***\n");
		return 0;
	}

	printf("\n\n***All Tests Passed.***\n");
	return 0;
}
