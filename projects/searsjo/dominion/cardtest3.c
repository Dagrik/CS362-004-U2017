//Joshua Sears
//CS362-400
//Su17
//Assignment 3 - Card Test for Village



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>

//Check to see if player drew a card and if players actions went down by 1 (played Village card), then up by 2 (from the card itself)
//Check decks discards and handcounts for other players.
int testVillage(){


	int numPlayers = MAX_PLAYERS;
	int curHandCt[numPlayers];
	int curDiscardCt[numPlayers];
	int curDeckCt[numPlayers];
	int curPlayedCt, curActionCt;
	int count, loopcounter;
	int test_status=0;
	int bonus=0;

//create gameState and decks
	int randomSeed = 2;
	struct gameState testState;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};
	
	initializeGame(numPlayers, k, randomSeed, &testState);

	int testHand[5] = {village, village, village, village, village};
	int testDeck[MAX_DECK];

	for (count = 0; count<MAX_DECK; count++){
		testDeck[count] = village;
	}

//alter gameState for testing
	testState.handCount[0] = 5;
	testState.deckCount[0] = MAX_DECK;
	memcpy(testState.hand[0], testHand, 5*sizeof(int));
	memcpy(testState.deck[0], testDeck, MAX_DECK*sizeof(int));


	printf("\n***Village Card Test***\n\n");
	printf("Single Village Iteration Test\n");
	for(loopcounter=1; loopcounter <=20; loopcounter++){
		printf("\nITERATION %i\n", loopcounter);
		for(count = 0; count<numPlayers; count++){
			curHandCt[count] = testState.handCount[count];
			curDiscardCt[count] = testState.discardCount[count];
			curDeckCt[count] = testState.deckCount[count];
		}
		curPlayedCt = testState.playedCardCount;
		curActionCt = testState.numActions;

		//Play card with cardEffect and subtract one action (other functions in playCard are not tested.)
		cardEffect(village, 1, 0, 0, &testState, 0, &bonus);
		testState.numActions--;

		printf("\nCURRENT PLAYER CARD PILES AND ACTIONS TEST:\n");
		if(testState.handCount[0] != curHandCt[0] || testState.deckCount[0] != curDeckCt[0] - 1 || testState.discardCount[0] != curDiscardCt[0] 
			|| testState.playedCardCount != curPlayedCt+1 || testState.numActions != curActionCt+1){
			test_status = -1;
			printf("***PLAYER DECK, DISCARD, AND DECK TEST Failed.***\n");
			printf("Hand: Actual %i Expected %i\n", testState.handCount[0], curHandCt[0]);
			 printf("Deck: Actual %i Expected %i\n", testState.deckCount[0], curDeckCt[0]-1);
			 printf("Discard: Actual %i Expected %i\n", testState.discardCount[0], curDiscardCt[0]);
			 printf("Played: Actual %i Expected %i\n", testState.playedCardCount, curPlayedCt + 1);
			 printf("Actions: Actual %i Expected %i\n", testState.numActions, curActionCt + 1);
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
	}

//Test for multiple plays of the village card
	for(count = 0; count<numPlayers; count++){
			curHandCt[count] = testState.handCount[count];
			curDiscardCt[count] = testState.discardCount[count];
			curDeckCt[count] = testState.deckCount[count];
		}
		curPlayedCt = testState.playedCardCount;
		curActionCt = testState.numActions;

		//Play card with cardEffect and subtract one action (other functions in playCard are not tested.)
		for(count=0;count<5;count++){
			cardEffect(village, 1, 0, 0, &testState, 0, &bonus);
			testState.numActions--;
		}

		printf("\nMULTIPLE VILLAGE CARDS (5 PLAYS) - Player 0:\n");
		if(testState.handCount[0] != curHandCt[0] || testState.deckCount[0] != curDeckCt[0] - 5 || testState.discardCount[0] != curDiscardCt[0] 
			|| testState.playedCardCount != curPlayedCt+5 || testState.numActions != curActionCt+5){
			test_status = -1;
			printf("***PLAYER DECK, DISCARD, AND DECK TEST Failed.***\n");
			printf("Hand: Actual %i Expected %i\n", testState.handCount[0], curHandCt[0]);
			 printf("Deck: Actual %i Expected %i\n", testState.deckCount[0], curDeckCt[0]-5);
			 printf("Discard: Actual %i Expected %i\n", testState.discardCount[0], curDiscardCt[0]);
			 printf("Played: Actual %i Expected %i\n", testState.playedCardCount, curPlayedCt + 5);
			 printf("Actions: Actual %i Expected %i\n", testState.numActions, curActionCt + 5);
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
	return test_status;
}


int main(){
printf("\n***TESTING VILLAGE CARD***\n\n");
 int result = testVillage();
 printf("\n***VILLAGE CARD TESTING COMPLETE***\n");
 	if(result == -1){
		printf("\n\n***Some Tests Failed.  Please Check Messages Above.***\n");
		return 0;
	}

	printf("\n\n***All Tests Passed.***\n");
	return 0;
}