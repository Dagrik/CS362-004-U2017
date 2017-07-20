#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    int newValue = rand()%95+32;
    char newChar =(char)newValue;
    return newChar;
}

void inputString(char *newString)
{
    int count, newVal, chooser;
    char newChar;
    char* testString = "abcdeeefghijklmnopqrrrssstttuvwxyzERST!1 \n";
    chooser = rand()%100;
    if(chooser>2){
	    for(count=0; count<5; count++){
	    	newVal=rand()%42;
	   		newChar = testString[newVal];
	    	newString[count] = newChar;
	    }
	    newString[5] = '\0';
	} else {
		if(chooser>1){
			newString[0] = 'r';
			newString[1] = 'e';
			newString[2] = 's';
			newString[3] = 'e';
			newString[4] = 't';
			newString[5] = inputChar();
		} else if(chooser>0){
			newString[0] = 'R';
			newString[1] = 'E';
			newString[2] = 'S';
			newString[3] = 'E';
			newString[4] = 'T';
			newString[5] = '\0';
		}else{
			newString[0] = 't';
			newString[1] = 'r';
			newString[2] = 'e';
			newString[3] = 'e';
			newString[4] = 's';
			newString[5] = '\0';
		}
	}   
    
   
    return;
}

void testme()
{
  int tcCount = 0;
  char *s = malloc(6*sizeof(char));
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    inputString(s);
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      free(s);
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
