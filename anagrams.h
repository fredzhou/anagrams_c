typedef struct anagrams_s anagrams_t;

anagrams_t *anagrams_create(const char *src);
void anagrams_destroy(anagrams_t *self);
char *anagrams_get_item(anagrams_t * self, unsigned int i);
unsigned int anagrams_get_amount(anagrams_t *self);
unsigned int anagrams_get_length(anagrams_t *self);
