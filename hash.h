/*HEADER FILE FOR HASH TABLE IMPLEMENTATION*/

typedef struct wordNode
{
    char* word;
    int count;

} wordNode;

typedef struct Hash
{
    struct wordNode* hash;
    int maxSize;
    int curSize;
} Hash;

int hashCode(char* word);
Hash createHashTable(int size);
void add(Hash* curHash, char* string, int countNum);
void rehash(Hash* curHash);
wordNode* getImportantValues(Hash* curHash);
void freeEverything(Hash* curHash, wordNode* iValues);
