test_executable : anagrams
	./anagrams

anagrams : AllTests.o test_anagrams.o anagrams.o
	gcc -o $@ AllTests.o test_anagrams.o anagrams.o -L$(CPPUTEST_LIB) -lCppUTest -lstdc++

AllTests.o : AllTests.cpp
	gcc -o $@ -c AllTests.cpp -I$(CPPUTEST_INCLUDE)

test_anagrams.o : test_anagrams.cpp
	gcc -o $@ -c test_anagrams.cpp -I$(CPPUTEST_INCLUDE)

anagrams.o : anagrams.c
	gcc -o $@ -c anagrams.c -std=c99

clean : 
	-rm -f *.o anagrams
