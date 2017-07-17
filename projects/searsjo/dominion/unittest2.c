//Joshua Sears
//CS362-400
//Su17
//Assignment 3 - Unit Test for updateCoins


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdbool.h>


/*Testing updateCoins by checking to see the following:
* - No coin cards, all coppers, all silvers, all golds, and random mix (to include no cards in hand)
* - Add negative, 0 and positive bonuses
* - mix of both
*/
int testUpdateCoins(){
	int test_status = 0;
	int handCount = 0;
	int bonusCount = 0;

	//initialize gameState
	struct gameState testState;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};

	//No-coin hand and full set treasure hands
	int noCoinHand[MAX_HAND];
	int copperHand[MAX_HAND];
	int silverHand[MAX_HAND];
	int goldHand[MAX_HAND];
	int mixedHand[MAX_HAND];

	//fill test treasure hands
	int count = 0;
	for(count = 0; count < MAX_HAND; count++){
		noCoinHand[count] = estate;
		copperHand[count] = copper;
		silverHand[count] = silver;
		goldHand[count] = gold;

		if(count%4 == 3){
			mixedHand[count] = gold;
		}else if (count%4 == 2){
			mixedHand[count] = silver;
		} else if (count%4 == 1){
			mixedHand[count] = copper;
		} else {
			mixedHand[count] = estate;
		}
	}

	
	//initial setup
	int numPlayers = 3;
	int randomSeed = 2;
	int maxHandCount = 10;
	initializeGame(numPlayers, k, randomSeed, &testState);


	//Test empty, all copper, silver or gold hands, and mixed.  No bonus coins.
	printf("\nTesting updateCoin() With Various Hands.\n");
	for(handCount = 0; handCount <= maxHandCount; handCount++){

		testState.handCount[0] = handCount;

		//set current player hand to noCoinHand
		memcpy(testState.hand[0], noCoinHand, handCount*sizeof(int));
		updateCoins(0, &testState, 0);

		if(testState.coins != 0){
			printf("No Coin Hand Test - HandCount: %i - Actual Coin: %i - Test FAILED.\n", handCount, testState.coins);
			test_status = -1;
		}

		memcpy(testState.hand[0], copperHand, handCount*sizeof(int));
		updateCoins(0, &testState, 0);

		if(testState.coins != handCount){
			printf("Copper Hand Test - HandCount: %i - Actual Coin: %i - Test FAILED.\n", handCount, testState.coins);
			test_status = -1;
		}

		memcpy(testState.hand[0], silverHand, handCount*sizeof(int));
		updateCoins(0, &testState, 0);

		if(testState.coins != 2*handCount){
			printf("Silver Hand Test - HandCount: %i - Actual Coin: %i - Test FAILED.\n", handCount, testState.coins);
			test_status = -1;
		}

		memcpy(testState.hand[0], goldHand, handCount*sizeof(int));
		updateCoins(0, &testState, 0);

		if(testState.coins != 3*handCount){
			printf("Gold Hand Test - HandCount: %i - Actual Coin: %i - Test FAILED.\n", handCount, testState.coins);
			test_status = -1;
		}

		memcpy(testState.hand[0], mixedHand, handCount*sizeof(int));
		updateCoins(0, &testState, 0);

		//Calculate total coin count of mixedHand
		int partTotal = 0;
		if(handCount % 4 == 2){
			partTotal = 1;
		} else if (handCount%4 == 3){
			partTotal = 3;
		}
		int total = 6*(handCount/4) + partTotal;

		if(testState.coins != total){
			printf("Mixed Hand Test - HandCount: %i - Actual Coin: %i - Tested: %i - Test FAILED.\n", handCount, testState.coins, total);
			test_status = -1;
		}

	}	
	if(test_status == 0){
		printf("\nTesting Various Hands - Tests Passed.\n");
	}


	//Test bonus adds
	printf("\nTesting Bonus Coins.\n");
	memcpy(testState.hand[0], noCoinHand, 5*sizeof(int));
	testState.handCount[0] = 5;
	for(bonusCount = -5; bonusCount <= 20; bonusCount++){
		updateCoins(0, &testState, bonusCount);
		if(testState.coins != bonusCount){
			printf("Bonus Test - bonusCount: %i - Actual Coin: %i - Test FAILED.\n", bonusCount, testState.coins);
			test_status = -1;
		}
	}
	if(test_status == 0){
		printf("\nTesting Bonus Coins - Tests Passed.\n");
	}

	printf("\nTesting Mix of Hands and Bonuses.\n");
	//Mixed hand and bonus testing
	for(handCount = 0; handCount <= maxHandCount; handCount++){
		for(bonusCount = -5; bonusCount <= 20; bonusCount++){
			memcpy(testState.hand[0], noCoinHand, handCount*sizeof(int));
			testState.handCount[0] = handCount;
			updateCoins(0, &testState, bonusCount);

			if(testState.coins != bonusCount){
				printf("Combined No Coin Hand Test - HandCount: %i - Bonus: %i - Actual Coin: %i - Test FAILED.\n", handCount, bonusCount, testState.coins);
				test_status = -1;
			}

			memcpy(testState.hand[0], copperHand, handCount*sizeof(int));
			updateCoins(0, &testState, bonusCount);

			if(testState.coins != (handCount + bonusCount)){
				printf("Combined Copper Hand Test - HandCount: %i - Bonus: %i - Actual Coin: %i - Test FAILED.\n", handCount, bonusCount, testState.coins);
				test_status = -1;
			}

			memcpy(testState.hand[0], silverHand, handCount*sizeof(int));
			updateCoins(0, &testState, bonusCount);

			if(testState.coins != (2*handCount + bonusCount)){
				printf("Combined Silver Hand Test - HandCount: %i - Bonus: %i - Actual Coin: %i - Test FAILED.\n", handCount, bonusCount, testState.coins);
				test_status = -1;
			}

			memcpy(testState.hand[0], goldHand, handCount*sizeof(int));
			updateCoins(0, &testState, bonusCount);

			if(testState.coins != (3*handCount + bonusCount)){
				printf("Combined Gold Hand Test - HandCount: %i - Bonus: %i - Actual Coin: %i - Test FAILED.\n", handCount, bonusCount, testState.coins);
				test_status = -1;
			}

			memcpy(testState.hand[0], mixedHand, handCount*sizeof(int));
			updateCoins(0, &testState, bonusCount);

			//Calculate total coin count of mixedHand
			int partTotal = 0;
			if(handCount % 4 == 2){
				partTotal = 1;
			} else if (handCount%4 == 3){
				partTotal = 3;
			}
			int total = 6*(handCount/4) + partTotal;

			if(testState.coins != (total+bonusCount)){
				printf("Combined Mixed Hand Test - HandCount: %i - Bonus: %i - Actual Coin: %i - Test FAILED.\n", handCount, bonusCount, testState.coins);
				test_status = -1;
			}


		}

	}

	if(test_status == 0){
		printf("\nTesting Hands with Bonuses - Tests Passed.\n");
	}
	return test_status;
	
}


int main(){
	int result;
	result = testUpdateCoins();
	if(result == -1){
		printf("\n\n***Some Tests Failed.  Please Check Messages Above.***\n");
		return 0;
	}

	printf("\n\n***All Tests Passed.***\n");
	return 0;
}