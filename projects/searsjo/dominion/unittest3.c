//Joshua Sears
//CS362-400
//Su17
//Assignment 3 - Unit Test for fullDeckCount()


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>


/*function will test various deck count sizes to ensure calculation
* - Empty deck, hand,or discard and combinations of each
* - Test all cards the same
* - Test No matching cards
* - Test mixed
*/
int testMatchingEstateDeck(int card){
	//create gameState
	int testHandCt, testDeckCt, testDiscardCt, count, actual, expected;
	int test_status = 0;
	struct gameState testState;
	int numPlayers = 3;
	int randomSeed = 2;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};

	int matchDeck[MAX_DECK];
	int matchHand[MAX_HAND];
	int matchDiscard[MAX_DECK];

	for(count=0; count<MAX_DECK; count++){
		matchDeck[count] = estate;
		matchDiscard[count] = estate;
	}

	for(count=0;count<MAX_HAND;count++){
		matchHand[count]=estate;
	}

	initializeGame(numPlayers, k, randomSeed, &testState);

	for(testDeckCt = MAX_DECK; testDeckCt >=0; testDeckCt--){
		testState.deckCount[0] = testDeckCt;

		memcpy(testState.deck[0], matchDeck, testDeckCt*sizeof(int));
		

		for(testHandCt = MAX_HAND - testDeckCt; testHandCt >= 0; testHandCt--){
			testState.handCount[0] = testHandCt;

			memcpy(testState.hand[0], matchHand, testHandCt*sizeof(int));
		
			testDiscardCt = MAX_DECK - testDeckCt - testHandCt;
			testState.discardCount[0] = testDiscardCt;
		
			memcpy(testState.discard[0], matchDiscard, testDiscardCt*sizeof(int));
				
			actual = fullDeckCount(0, card, &testState);
			
			if(card == 1){
				expected = testDeckCt + testHandCt + testDiscardCt;
			} else {
				expected = 0;
			}
			
			if(actual != expected){
				printf("\nMatched Deck Test: Deck: %i, Hand: %i, Discard: %i. Expected: %i Cards, Found: %i Cards - Test Failed.\n", testDeckCt, testHandCt, testDiscardCt, expected, actual);
				test_status = -1;
			} 


			
		}
	}

return test_status;

}

int testMixedEstateDeck(){
	//create gameState
	int testHandCt, testDeckCt, testDiscardCt, count, actual, expected;
	int test_status = 0;
	struct gameState testState;
	int numPlayers = 3;
	int randomSeed = 2;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};

	int matchDeck[MAX_DECK];
	int matchHand[MAX_HAND];
	int matchDiscard[MAX_DECK];

	for(count=0; count<MAX_DECK; count++){
		
			matchDeck[count] = estate;
			matchDiscard[count] = curse;
		

	}

	for(count=0;count<MAX_HAND;count++){
			matchHand[count]=curse;
	}
	

	initializeGame(numPlayers, k, randomSeed, &testState);

	for(testDeckCt = MAX_DECK; testDeckCt >=0; testDeckCt--){
		testState.deckCount[0] = testDeckCt;

		memcpy(testState.deck[0], matchDeck, testDeckCt*sizeof(int));
		

		for(testHandCt = MAX_HAND - testDeckCt; testHandCt >= 0; testHandCt--){
			testState.handCount[0] = testHandCt;

			memcpy(testState.hand[0], matchHand, testHandCt*sizeof(int));
		

			testDiscardCt = MAX_DECK - testDeckCt - testHandCt;
			testState.discardCount[0] = testDiscardCt;
	
			memcpy(testState.discard[0], matchDiscard, testDiscardCt*sizeof(int));
			
			actual = fullDeckCount(0, estate, &testState);
			
			expected = testDeckCt;

			if(actual != expected){
				printf("\nMixed Test (Deck Test): Deck: %i, Hand: %i, Discard: %i.  Expected: %i Cards, Found: %i Cards - Test Failed.\n", testDeckCt, testHandCt, testDiscardCt, expected, actual);
				test_status = -1;
			} 
		}
	}

	for(count=0; count<MAX_DECK; count++){
		
			matchDeck[count] = curse;
			matchDiscard[count] = estate;
		

	}

	for(count=0;count<MAX_HAND;count++){
			matchHand[count]=curse;
	}
	

	for(testDeckCt = MAX_DECK; testDeckCt >=0; testDeckCt--){
		testState.deckCount[0] = testDeckCt;

		memcpy(testState.deck[0], matchDeck, testDeckCt*sizeof(int));
		

		for(testHandCt = MAX_HAND - testDeckCt; testHandCt >= 0; testHandCt--){
			testState.handCount[0] = testHandCt;

			memcpy(testState.hand[0], matchHand, testHandCt*sizeof(int));
		

			testDiscardCt = MAX_DECK - testDeckCt - testHandCt;
			testState.discardCount[0] = testDiscardCt;
	
			memcpy(testState.discard[0], matchDiscard, testDiscardCt*sizeof(int));
			
			actual = fullDeckCount(0, estate, &testState);
			
			expected = testDiscardCt;

			if(actual != expected){
				printf("\nMixed Test (Discard Test): Deck: %i, Hand: %i, Discard: %i.  Expected: %i Cards, Found: %i Cards - Test Failed.\n", testDeckCt, testHandCt, testDiscardCt, expected, actual);
				test_status = -1;
			} 
		}
	}

		for(count=0; count<MAX_DECK; count++){
		
			matchDeck[count] = curse;
			matchDiscard[count] = curse;
		

	}

	for(count=0;count<MAX_HAND;count++){
			matchHand[count]=estate;
	}
	

	initializeGame(numPlayers, k, randomSeed, &testState);

	for(testDeckCt = MAX_DECK; testDeckCt >=0; testDeckCt--){
		testState.deckCount[0] = testDeckCt;

		memcpy(testState.deck[0], matchDeck, testDeckCt*sizeof(int));
		

		for(testHandCt = MAX_HAND - testDeckCt; testHandCt >= 0; testHandCt--){
			testState.handCount[0] = testHandCt;

			memcpy(testState.hand[0], matchHand, testHandCt*sizeof(int));
		

			testDiscardCt = MAX_DECK - testDeckCt - testHandCt;
			testState.discardCount[0] = testDiscardCt;
	
			memcpy(testState.discard[0], matchDiscard, testDiscardCt*sizeof(int));
			
			actual = fullDeckCount(0, estate, &testState);
			
			expected = testHandCt;



			if(actual != expected){
				printf("\nMixed Test (Hand Test): Deck: %i, Hand: %i, Discard: %i.  Expected: %i Cards, Found: %i Cards - Test Failed.\n", testDeckCt, testHandCt, testDiscardCt, expected, actual);
				test_status = -1;
			} 
		}
	}

return test_status;

}

//Calls tests for all cards match, and no matching cards
//Calls mixed deck, which find cards in either of discard, deck or hand
int testFullDeckCount(){

	int emptyResult, matchResult, mixedResult;
	int totalResult = 0;

	//Test a not matching card
	printf("\n***Checking For No Match.***\n");
	emptyResult = testMatchingEstateDeck(copper);
	if(emptyResult == 0) {printf("No Match Tests Passed.\n");}
	//Test the matching card
	printf("\n***Checking For All Match.***\n");
	matchResult = testMatchingEstateDeck(estate);
	if(matchResult == 0) {printf("All Match Tests Passed.\n");}
	//Test a mixed deck
	printf("\n***Checking For Mixed Matches.***\n");
	mixedResult = testMixedEstateDeck();
	if(mixedResult == 0) {printf("Mixed Tests Passed.\n");}

	
	if(emptyResult!=0 || matchResult != 0 || mixedResult !=0){
		totalResult = -1;
	}

	return totalResult;
}


int main(){
	int result;
	printf("\n***TESTING FULLDECKCOUNT()***\n\n");
	result = testFullDeckCount();
	printf("\n***FULLDECKCOUNT() TESTING COMPLETE***\n");
	if(result == -1){
		printf("\n\n***Some Tests Failed.  Please Check Messages Above.***\n");
		return 0;
	}

	printf("\n\n***All Tests Passed.***\n");

	return 0;
}