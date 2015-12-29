/* 
Table of Contents
0. Fundamentals
TODO:

*/
//-----------------------------------------------------------------------------------------------------------------------
// 0 Fundamentals
/*
Trie = Prefix Tree = Digital Tree
Trie != Radix Tree
Radix Tree = Space Compressed Trie
Trie != Suffix Tree
Suffix Tree uses Trie in its construction 
Trie comes from word re'Trie'val. 
It retrieves words given a prefix. 

It is the fastest way to look up strings and saves a tonne of space. 
Has at most 26 child nodes (if only English)
Can also prefix a permutation of digits (13476) (e.g. Phone numbers, ID number, binary values)

Worst Case Look Up time is better than Hash Table. (No collisions in Trie)
Worst Case Memory usage is worse than Hash Table. (Stores every single character in separate memory address)
 
Complexities: 
m = length of key
n = number of words in the Trie
Insert: T(m,n) = O(m), S(m,n) = O(n*m*AlphabetSize)
 
Applications:   
    1. Autocomplete
        - If user types half way, just jump around till reach an end node and give that as suggestion
    2. Autocorrect 
        - If user types wrongly, jump around from wrongly onwards till reach strings that match closely to after wrongly 
*/

#include <cstring> 
#include <cstdlib>
#include <string> 
#include <iostream> 
using namespace std; 

class Trie 
{
private:
    bool leaf; // indicate if end of any word
                // note: Just cause leaf is true doesn't mean this node has no child nodes. 
                //      It just means the current node marks an end of a word in the Trie
                //      but this word may still be a prefix of another word
    Trie* next[26]; // a pointer to all 26 characters
    // optionals: 
    // note: Total number of words in Tree is the value of prefix of the root node
    unsigned int prefixes; // number of words in Trie that has current node as a prefix
    
    // Only needed if Trie is allowed to contain duplicate words
    // unsigned int words is useful for determining which word is more popular than others in applications like auto correct and autocomplete 
    unsigned int words; //  number of same words that exist in Trie, if current leaf is a word. It is a counter on the current node
public:
    Trie()
    {
        words = 0;
        prefixes; 0;
        for (int i = 0; i < 26; i++)
        {
            next[i] = NULL;
        }
    }
    void addWord(string word);
    void deleteWord(string word);
    unsigned int countPrefix(string prefix); // counts number of words in Trie that has current node as a prefix
    unsigned int countWord(string word); // counts number of duplicate words with word in Trie
};

int main(void)
{
    return 0;
}
