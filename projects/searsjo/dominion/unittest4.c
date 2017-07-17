//Joshua Sears
//CS362-400
//Su17
//Assignment 3 - Unit Test for scoreFor()

/* Errors found in dominion.c
* in scoreFor()
gardens addition uses fullDeckCount, but only calls to look for a specific card
deck addition uses limit for discardCount in for loop
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>


int testHelper(struct gameState *state, int hand[10], int expectedScore, char name[]){
	int result=0;
	int actualScore=0;
	int emptyHand[10]= {copper, copper, copper, copper, copper, copper, copper, copper, copper, copper};

	
//Test for cards in hand
	memcpy(state->hand[0], hand, 10*sizeof(int));
	memcpy(state->discard[0], emptyHand, 10*sizeof(int));
	memcpy(state->deck[0], emptyHand, 10*sizeof(int));

	actualScore = scoreFor(0, state);

	if(actualScore != expectedScore){
		printf("%s in Hand - Test Failed.  Actual: %i. Expected: %i.\n", name, actualScore, expectedScore);
		result= -1;
	}else{
		printf ("%s in Hand - Test Passed.\n", name);
	}

//Test for cards in discard
	memcpy(state->hand[0], emptyHand, 10*sizeof(int));
	memcpy(state->discard[0], hand, 10*sizeof(int));
	memcpy(state->deck[0], emptyHand, 10*sizeof(int));

	actualScore = scoreFor(0, state);

	if(actualScore != expectedScore){
		printf("%s in Discard - Test Failed.  Actual: %i. Expected: %i.\n", name, actualScore, expectedScore);
		result= -1;
	}else{
		printf ("%s in Discard - Test Passed.\n", name);
	}

//Test for cards in deck
	memcpy(state->hand[0], emptyHand, 10*sizeof(int));
	memcpy(state->discard[0], emptyHand, 10*sizeof(int));
	memcpy(state->deck[0], hand, 10*sizeof(int));

	actualScore = scoreFor(0, state);

	if(actualScore != expectedScore){
		printf("%s in Deck - Test Failed.  Actual: %i. Expected: %i.\n", name, actualScore, expectedScore);
		result= -1;
	}else{
		printf ("%s in Deck - Test Passed.\n", name);
	}

//Test for cards in hand and discard
	memcpy(state->hand[0], hand, 10*sizeof(int));
	memcpy(state->discard[0], hand, 10*sizeof(int));
	memcpy(state->deck[0], emptyHand, 10*sizeof(int));

	actualScore = scoreFor(0, state);

	if(actualScore != 2*expectedScore){
		printf("%s in Hand and Discard - Test Failed.  Actual: %i. Expected: %i.\n", name, actualScore, expectedScore);
		result= -1;
	}else{
		printf ("%s in Hand and Discard - Test Passed.\n", name);
	}

//Test for cards in hand and deck
	memcpy(state->hand[0], hand, 10*sizeof(int));
	memcpy(state->discard[0], emptyHand, 10*sizeof(int));
	memcpy(state->deck[0], hand, 10*sizeof(int));

	actualScore = scoreFor(0, state);

	if(actualScore != 2*expectedScore){
		printf("%s in Hand and Deck - Test Failed.  Actual: %i. Expected: %i.\n", name, actualScore, expectedScore);
		result= -1;
	}else{
		printf ("%s in Hand and Deck - Test Passed.\n", name);
	}

//Test for cards in deck and discard
	memcpy(state->hand[0], emptyHand, 10*sizeof(int));
	memcpy(state->discard[0], hand, 10*sizeof(int));
	memcpy(state->deck[0], hand, 10*sizeof(int));

	actualScore = scoreFor(0, state);

	if(actualScore != 2*expectedScore){
		printf("%s in Discard and Deck - Test Failed.  Actual: %i. Expected: %i.\n", name, actualScore, expectedScore);
		result= -1;
	}else{
		printf ("%s in Discard and Deck - Test Passed.\n", name);
	}

//Test for cards in all 3 piles
	memcpy(state->hand[0], hand, 10*sizeof(int));
	memcpy(state->discard[0], hand, 10*sizeof(int));
	memcpy(state->deck[0], hand, 10*sizeof(int));

	actualScore = scoreFor(0, state);

	if(actualScore != 3*expectedScore){
		printf("%s in All 3 - Test Failed.  Actual: %i. Expected: %i.\n", name, actualScore, expectedScore);
		result= -1;
	}else{
		printf ("%s in All 3 - Test Passed.\n", name);
	}

	return result;
}

//Test cost for each card.  Values retrieved from wiki.dominionstrategy.com


int testScoreFor(){
	int result = 0;

	int test_status = 0;
	struct gameState testState;
	int numPlayers = 3;
	int randomSeed = 2;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};

	initializeGame(numPlayers, k, randomSeed, &testState);

	testState.handCount[0]=10;
	testState.discardCount[0]=10;
	testState.deckCount[0]=10;


	//setup sample deck/hand/discards
	int emptyHand[10]= {copper, copper, copper, copper, copper, copper, copper, copper, copper, copper};
	int estateHand[10] = {estate, estate, estate, estate, estate, estate, estate, estate, estate, estate};
	int duchyHand[10] = {duchy, duchy, duchy, duchy, duchy, duchy, duchy, duchy, duchy, duchy};
	int provHand[10] = {province, province, province, province, province, province, province, province, province, province};
	int curseHand[10] = {curse, curse, curse, curse, curse, curse, curse, curse, curse, curse};
	int greatHallHand[10] = {great_hall, great_hall, great_hall, great_hall, great_hall, great_hall, great_hall, great_hall, great_hall, great_hall};
	int gardenHand[10] = {gardens, copper, copper, copper, copper, copper, copper, copper, copper, copper};
	int mixedHand[10] = {copper, estate, duchy, province, copper, great_hall, curse, curse, gardens, gold }; 

	//Tests
	test_status = testHelper(&testState, emptyHand, 0, "No-Point");
	if(test_status==-1){result = -1;}

	test_status = testHelper(&testState, estateHand, 10, "Estate Pile");
	if(test_status==-1){result = -1;}

	test_status = testHelper(&testState, duchyHand, 30, "Duchy Pile");
	if(test_status==-1){result = -1;}

	test_status = testHelper(&testState, provHand, 60, "Province Pile");
	if(test_status==-1){result = -1;}

	test_status = testHelper(&testState, curseHand, -10, "Curse Pile");
	if(test_status==-1){result = -1;}

	test_status = testHelper(&testState, greatHallHand, 10, "Great Hall Pile");
	if(test_status==-1){result = -1;}

	test_status = testHelper(&testState, gardenHand, 3, "Garden Pile");
	if(test_status==-1){result = -1;}

	test_status = testHelper(&testState, mixedHand, 12, "Mixed Pile");
	if(test_status==-1){result = -1;}

	return result;

}

int main(){
	int result=0;
	printf("\n***TESTING SCOREFOR()***\n\n");
	result = testScoreFor();
	printf("\n***SCOREFOR() TESTING COMPLETE***\n");
	if(result == -1){
		printf("\n\n***Some Tests Failed.  Please Check Messages Above.***\n");
		return 0;
	}

	printf("\n\n***All Tests Passed.***\n");

	return 0;
}