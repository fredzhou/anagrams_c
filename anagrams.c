#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "anagrams.h"

struct anagrams_s {
    char *output;
    char *current;
    int length;
    int amount;
};

anagrams_t anagrams;

unsigned int __factorial(unsigned int n)
{
    int result = 0;
    if (0 == n) {
        result = 1;
    } else {
        result = n*__factorial(n-1);
    }

    return result;
}

void __append(char *dest, char c)
{
    if (dest[strlen(dest)] == 0)
        dest[strlen(dest)] = c;
}

void __remove_a_char(char *src, int index)
{
    for (int i = index; i < strlen(src); i++)
        src[i] = src[i+1];
}

void __allocate_new_carried_and_remainder(
     char **new_carried, 
     char **new_remainder, 
     const char *orig_carried, 
     const char *orig_remainder)
{
        *new_carried = (char *)malloc(anagrams.length + 1);
        *new_remainder = (char *)malloc(anagrams.length + 1);

        memset(*new_carried, 0, anagrams.length + 1);
        memset(*new_remainder, 0, anagrams.length + 1);
        
        strcpy(*new_carried, orig_carried);
        strcpy(*new_remainder, orig_remainder);
}

void __free_carried_and_remainder(char *carried, char *remainder)
{
    free(carried);
    free(remainder);
}

void __gen_anagram_words(const char * carried, const char *remainder)
{
    
    char *new_carried = NULL;
    char *new_remainder = NULL;
     
    for (int i = 0; i < strlen(remainder); i++) {
         __allocate_new_carried_and_remainder(&new_carried, &new_remainder, carried, remainder);

        __append(new_carried, remainder[i]);
        __remove_a_char(new_remainder, i);
         
        if (strlen(new_remainder) == 0) {
            strncpy(anagrams.current, new_carried, strlen(new_carried));
            anagrams.current += anagrams.length + 1;
            return;
        }
        else {
            __gen_anagram_words(new_carried, new_remainder);
        }

        __free_carried_and_remainder(new_carried, new_remainder);
     } 
}


anagrams_t *anagrams_create(const char *src)
{
    anagrams.amount = __factorial(strlen(src));
    anagrams.length = strlen(src);

    anagrams.output = (char *)malloc((anagrams.length + 1)*anagrams.amount);
    memset(anagrams.output, 0, sizeof(anagrams.output));
    anagrams.current = anagrams.output;
    
    __gen_anagram_words("", src);
    return &anagrams;
}
 
char *anagrams_get_item(anagrams_t *self, unsigned int i)
{
    return self->output + i*(self->length + 1);
}

void anagrams_destroy(anagrams_t *self)
{
    free(self->output);
    self->amount = 0;
    self->length = 0;
    anagrams.current = NULL;
}

unsigned int anagrams_get_amount(anagrams_t *self)
{
	return self->amount;
}

unsigned int anagrams_get_length(anagrams_t *self)
{
	return self->length;
}
