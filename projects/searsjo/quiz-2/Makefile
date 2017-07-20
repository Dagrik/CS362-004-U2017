CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c 
	gcc -o testme testme.c $(CFLAGS)

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme

