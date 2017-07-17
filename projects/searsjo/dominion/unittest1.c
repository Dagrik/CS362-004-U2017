//Joshua Sears
//CS362-400
//Su17
//Assignment 3 - Unit Test for initializeGame()


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>

/*  Test initializeGame
*	The purpose of this unit test is to ensure the original setup of the game is to standard.
*   Initializing the game requires different levels of setup
*  x 1.  Check for player count
*	x2.  Choose 10 different kingdom cards
*	x3.  Set curse card count per player count
*	x4.  Set victory card count per player count
*   x5.  Set treasure card count
*   x6.  Set kingdom card count
*   7.  Set player decks
*   8.  Shuffle decks
*   9.  Initialize first player's turn
*   10.  Update coin count for first player
*/

//To check player count for init.  Cannot be <2 or >4.
//Check outside limits, check boundaries, check acceptable
int testPlayerCount(){
	bool failed = false;
	struct gameState state;
	int playerCount, result;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};

	printf("TESTING PLAYER COUNT:\n");

	//Check below range
	playerCount = 1;
	result = initializeGame(playerCount, k, 2, &state);
	if(result == -1){
		printf("Player Count Too Low - Test Passed.\n");
	} else {
		printf("Player Count Too Low - Test Failed.\n");
		failed = true;
	}

	//Check above range
	playerCount = 5;
	result = initializeGame(playerCount, k, 2, &state);
	if(result == -1){
		printf("Player Count Too High - Test Passed.\n");
	} else {
		printf("Player Count Too High - Test Failed.\n");
		failed = true;
	}

	

	//Check boundary conditions and middle
	for(playerCount = 2; playerCount <= MAX_PLAYERS; playerCount++){
		result = initializeGame(playerCount, k, 2, &state);
		if(result == 0){
			printf("Player Count %i - Test Passed.\n", playerCount);
		} else {
			printf("Player Count %i - Test Failed.\n", playerCount);
			failed = true;
		}
	}
	
	printf("PLAYER COUNT TESTS COMPLETE.\n");

	if(failed){
		return -1;
	}
	return 0;
}

//Test to ensure multiple of same kingdom cards can be found
int testKingdomCardVariation(){
	bool failed = false;
	int playerCount = 2;
	struct gameState state;
	int result;

	printf("TESTING KINGDOM CARD VARIATION:\n");

	//set cards to have one set of doubles in first and second spot
	int i[10] = {adventurer, adventurer, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};

	result = initializeGame(playerCount, i, 2, &state);
	if(result == -1){
		printf("First Two Kingdom Cards The Same - Test Passed.\n");
	} else {
		printf("First Two Kingdom Cards The Same - Test Failed.\n");
		failed = true;
	}

	//set cards to have one set of doubles which are separated
	int j[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, adventurer, smithy};

	result = initializeGame(playerCount, j, 2, &state);
	if(result == -1){
		printf("Separated Two Kingdom Cards The Same - Test Passed.\n");
	} else {
		printf("Separated Two Kingdom Cards The Same - Test Failed.\n");
		failed = true;
	}

	//set cards to good set
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};

	result = initializeGame(playerCount, k, 2, &state);
	if(result == 0){
		printf("All Kingdom Cards Different - Test Passed.\n");
	} else {
		printf("All Kingdom Cards Different - Test Failed.\n");
		failed = true;
	}

	printf("KINGDOM CARD VARIATION COMPLETE.\n");
	if(failed){
		return -1;
	}
	return 0;
}

//tests the amount of curse cards set by initializer
//Curse rules: 2 Players = 10 curses, 3P = 20 curses, 4P= 30 curses
//Victory rules: 8 of each in 2 player, 12 each in 3-4 players
//Treasure Card rules: Copper: 60 - (7 per player), Silver: 40, Gold: 30
//Kingdom Card rules: All assigned cards get 10, gardens and great_hall get 8 for 2 player, 12 for others
int testCardCount(const struct gameState *state, int kingdomCards[10]){
	bool failed = false;
	int counter = 0;
	int playerCount = state->numPlayers;
	int curseCount = state->supplyCount[curse];
	
	int estateCount = state->supplyCount[estate];
	int duchyCount = state->supplyCount[duchy];
	int provinceCount = state->supplyCount[province];

	int copperCount = state->supplyCount[copper];
	int silverCount = state->supplyCount[silver];
	int goldCount = state->supplyCount[gold];

	int totalCardCount;

	//Test card for two players
	
	if(playerCount == 2){
		printf("Curse Card Count");
		if(curseCount != 10){
			printf(" - Test Failed.\n");
			failed = true;
		} else {printf(" - Test Passed.\n");}

		printf("Victory Card Count");
		if(estateCount != 8 || duchyCount != 8 || provinceCount != 8){
			printf(" - Test Failed.\n");
			failed = true;
		} else { printf(" - Test Passed.\n");}

		printf("Treasure Card Count");
		if(copperCount != 46 || silverCount != 40 || goldCount != 30){
			printf(" - Test Failed.\n");
			failed = true;
		} else { printf(" - Test Passed.\n");}

		printf("Kingdom Card Count");
		for(counter = 0; counter < 10; counter++){
			totalCardCount += state->supplyCount[kingdomCards[counter]];
		}
		if(totalCardCount != 98){
			printf(" - Test Failed.\n");
			failed = true;
		} else { printf(" - Test Passed.\n");}



	} else if (playerCount == 3){
		printf("Curse Card Count");
		if(curseCount != 20){
			printf(" - Test Failed.\n");
			failed = true;
		} else {printf(" - Test Passed.\n");}

		printf("Victory Card Count");
		if(estateCount != 12 || duchyCount != 12 || provinceCount != 12){
			printf(" - Test Failed.\n");
			failed = true;
		} else { printf(" - Test Passed.\n");}
	
		printf("Treasure Card Count");
		if(copperCount != 39 || silverCount != 40 || goldCount != 30){
			printf(" - Test Failed.\n");
			failed = true;
		} else { printf(" - Test Passed.\n");}

		printf("Kingdom Card Count");
		for(counter = 0; counter < 10; counter++){
			totalCardCount += state->supplyCount[kingdomCards[counter]];
		}
		if(totalCardCount != 102){
			printf(" - Test Failed.\n");
			failed = true;
		} else { printf(" - Test Passed.\n");}




	} else {
		printf("Curse Card Count");
		if(curseCount != 30){
			
			printf(" - Test Failed.\n");
			failed = true;
		}else {printf(" - Test Passed.\n");}

		printf("Victory Card Count");
		if(estateCount != 12 || duchyCount != 12 || provinceCount != 12){
			printf(" - Test Failed.\n");
			failed = true;
		} else { printf(" - Test Passed.\n");}
	
		printf("Treasure Card Count");
		if(copperCount != 32 || silverCount != 40 || goldCount != 30){
			printf(" - Test Failed.\n");
			failed = true;
		} else { printf(" - Test Passed.\n");}

		printf("Kingdom Card Count");
		for(counter = 0; counter < 10; counter++){
			totalCardCount += state->supplyCount[kingdomCards[counter]];
		}
		if(totalCardCount != 102){
			printf(" - Test Failed.\n");
			failed = true;
		} else { printf(" - Test Passed.\n");}
	}
	


	if(failed){
		return -1;
	}
	return 0;
}

//Tests to see if 5 cards are in deck and 5 in hand for player 1, 10 in deck for all others
int testPlayerDeckHandCount(const struct gameState *state){
	int counter = 0;
	
	if(!(state->handCount[counter] == 5 && state->deckCount[counter] == 5)){
		printf(" - Test Failed.\n");
		return -1;
	}
	
	for(counter = 1; counter < state->numPlayers; counter++){
		if(!(state->deckCount[counter] == 10)){
			printf(" - Test Failed.\n");
			return -1;
		}
	}

	printf(" - Test Passed.\n");
	return 0;
}

int testBeginningState(const struct gameState *state){

	if(state->outpostPlayed == 0 && state->phase == 0 && state->numActions == 1 && state->numBuys == 1 &&
		state->playedCardCount == 0 && state->whoseTurn == 0 && state->handCount[state->whoseTurn] == 5){
		printf(" - Test Passed.\n");
		return 0;
	} else {
		printf(" - Test Failed.\n");
		return -1;
	}
}


int main(){
	int test_status = 0;
	int loopCount = 0;

	for(loopCount=0; loopCount<10; loopCount++){
		test_status=testPlayerCount();
		if(test_status == -1) return 0;
	}

	for(loopCount=0; loopCount<10; loopCount++){
		test_status = testKingdomCardVariation();
		if(test_status == -1) return 0;
	}
	


	//create three gameStates, with 2, 3 and 4 players for card count testing
	//Use good player counts and Kingdom Card variation
	struct gameState twoPlayerGame;
	struct gameState threePlayerGame;
	struct gameState fourPlayerGame;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};

	for(loopCount=0; loopCount<10; loopCount++){
		printf("\n\n***Test Attempt %i***\n\n", loopCount+1);
		//initialize the three gameStates
		initializeGame(2, k, 2, &twoPlayerGame);
		initializeGame(3, k, 2, &threePlayerGame);
		initializeGame(4, k, 2, &fourPlayerGame);

		printf("\nCARD COUNT TESTS:\n");

		printf("\nCard Count - Two Player Game:\n");
		test_status = testCardCount(&twoPlayerGame, k);
		if(test_status == -1) return 0;
		
		printf("\nCard Count - Three Player Game:\n");
		test_status = testCardCount(&threePlayerGame, k);
		if(test_status == -1) return 0;
		
		printf("\nCard Count - Four Player Game:\n");
		test_status = testCardCount(&fourPlayerGame, k);
		if(test_status == -1) return 0;

		printf("CARD COUNT TEST COMPLETE\n");

		//test Player Deck and Hand size for all players
		printf("\nDECK/HAND COUNT TESTS:\n");

		printf("Player Deck and Hand Count - Two Player Game");
		test_status = testPlayerDeckHandCount(&twoPlayerGame);
		if(test_status == -1) return 0;
		
		printf("Player Deck and Hand Count - Three Player Game");
		test_status = testPlayerDeckHandCount(&threePlayerGame);
		if(test_status == -1) return 0;
		
		printf("Player Deck and Hand Count - Four Player Game");
		test_status = testPlayerDeckHandCount(&fourPlayerGame);
		if(test_status == -1) return 0;

		printf("DECK/HAND COUNT TEST COMPLETE\n");

		printf("\nTESTING BEGINNING STATE:\n");

		printf("Beginning State Status - Two Player Game");
		test_status = testBeginningState(&twoPlayerGame);
		if(test_status == -1){ return 0;}

		printf("Beginning State Status - Three Player Game");
		test_status = testBeginningState(&threePlayerGame);
		if(test_status == -1){ return 0;}

		printf("Beginning State Status - Four Player Game");
		test_status = testBeginningState(&fourPlayerGame);
		if(test_status == -1){ return 0;}
	}

	printf("\n\nALL initializeGame() TESTS PASSED SUCCESSFULLY.\n");

	return 0;
}