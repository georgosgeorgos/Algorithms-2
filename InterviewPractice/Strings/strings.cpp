//----------------------------------------------------------------------------------------
/* //
Table of Contents
1. Reverse a string In-Place, T(n) = O(n), S(n) = O(1)
2. Determine if every ASCII character in a string is unique, T(n) = O(n), S(n) = O(1)
3. Determine if every ('a' to 'z') character in string is unique using Bit Manipulation, T(n) = O(n), S(n) = O(1)
4. Remove Duplicated characters of strings in place, T(n) = O(n^2), S(n) = O(1)
5. Implement Compression of a string (aabbbc->a2b3c1), T(n) = O(n), S(n) = O(n) (Amazon Round 1)
6. Longest Substring With Distinct Characters, T(n) = O(n) (single pass), S(n) = O(1)
7. Longest Substring With At Most K Distinct Characters, T(n) = O(n), S(n) = O(n)
8. Isomorphic Strings, T(n,m) = O(n), S(n,m) = O(n)
9. Exact Matching: Z-Algorithm, T(n,m) = O(n + m), Space Complexity, S(n,m) = O(n + m) TODO:INT
//-------------------------
TODO:
14. Reverse Words in a Sentence (Bloomberg Interview Round 1)
13. Finding longest palindromes substring 
    a) Hint: Manacher algorithm T(n) = O(n), S(n) = O(n) // fastest
    b) Dynamic Programming T(n) = O(n^2), S(n) = O(n^2)
    c) T(n) = O(n^2), S(n) = O(1) // least space, checking takes O(n), and (2n-1) centers
    d) Brute Force
Find all permutations of strings s in string b. 
    Easy: Just store all character of s in hashtable with count
    go to b, and reduce from hash table until not exist, then re-do
21. Longest Duplicated substring in a string.
30. Split a string by delimiter in  C++ using <string> 
31. Reading an input string of arbitrary size.
// Refer to hackerrank problem 6 "Alternating Characters" for solution. But code yourself first that was from online
32. A sentence has additional spaces between words, remove the additional spaces in place
eg: "hi  i     am paul" -> "hi i am paul"
Hint: 2 pointers, 1 to point to replace, one to search for more
33. Longest Common Substring Using Suffix Trees for > 2 strings
34. Exact Matching using Suffix Trees (location of each substring)
35. Exact Matching: Knuth Morris Pratt
35. Exact Matching: Rabin Karp
35. Exact Matching: Boyer-Moore
35. Dictionary (Check if a string is found in the dictionary)
36. Implement strspn function
37.Given an array of strings e.g. ["the", "quick", "brown", "fox", "quick"] and 2 strings, return minimum distance between 2 strings
"the", "fox" =>  3 
"quick", "fox" => 1
    Easy, 2 pointers, one to wordA, one to wordB, 
    move from left to right, each time find a new one, match with left. 
    "quick" (no match) => currMin = infinity
    "fox' (match with left 'quick') => currMin = 3
    "quick" (match with left 'fox') => currMin = 1 
    Done =) 

39. Minimum Window Substring: Find minimum window in S that contains all characters from T. 
    In other words, find minimum substring in S such that it contains all characters from T.  (From LeetCode)
    Return "" if none exist. 
    Assume only 1 minimum substring if multiple substrings exist.
    e.g. 
    S = abcdednfe , n = 8
    T = fdde, m = 4 
    => min. substring is dednf
    https://leetcode.com/problems/minimum-window-substring/
    Optimal Solution, T(n,m) = O(2n) time, O(n) space 

40.
//-------------------------
To work between <cstring> and <string> 
//-------------------------
    To convert from string to char *
        string bigString = "aabccccaaa";
        char* temp2; 
        cin >> bigString; // if needed
        const char* temp = bigString.c_str(); // must always be const char*
        // Copy it into normal char*
        strcpy(temp2, temp);
        // Now can use temp2 as usual. 
    To convert from char * to string
        char * haha = "abc";
        string newhaha = haha; // this works!
    // Must always malloc if changing an old cString
        char* compressed = (char *) malloc(strlen(inputStr));
        // Must also always null terminate the string! 

//-------------------------
<string> 
//-------------------------
char* cStr, cStr2;
string str, str2;

strlen(cStr); == str.length(); // returns length of string 
strcat(cStr,cStr2); == str.append(str2);
strcpy(cStr,cStr2); == str.assign(str2);
strcmp(cStr,cStr2); == str.compare(str2);
cStr[2] = 'k'; == str[2]  = 'k';

str.erase(startIndex,amountToErase); 
    // note: This inserts a string
str.insert(startIndex, str2); // insert str2 from startIndex position in str, if want to append in front, do str.insert(0,str2)
str.push_back(character1); // to insert 1 single character
//-------------------------
Common Hints
//-------------------------
- Reversing entire sentence, then reversing each word string => Reversing words in a sentence
- Assume ascii => char arr[256]; => Constant space, otherwise use Hash Table which is O(n)
- Loop through entire string with more than just 1 pointer, the first pointer moves faster, the 2nd pointer follows
//-------------------------
notes:
//-------------------------
"k" != 'k'
"k" is a char * whereas 'k' is a char
//-------------------------
Common Questions: 
//-------------------------
A-Z only or can have special characters?  ASCII or Unicode?
Does upper/lower cases matter ? 
What is a white space? How bout '\n' and '\t'
What is a word? 
ASCII only or A-Z, or entire character space (Mandarin, English etc.)? 
Does upper-case, lower-case matter? 
Is there trailing white space? 
Can there be multiple consecutive white spaces? 
Can there string have repeated characters or all distinct? 
Return position of string, or length or an entire new string itself? 
Can the original string be modified? 
What happens if string is empty "", or NULL, or contains 1 character only? 
//---------------------------------------------------------------------------------------------------
/* //
// Bloomberg Interview Round 1
Ahmed Bloomberg  (Indian??)
#include <string.h>  // for strlen(), strcpy()
#include <stdlib.h> //
#include <iostream>
using namespace std;
int main() {
    return 0;
}
Questions: 
Q: What constitutes a word?
A: A sequence of non-space characters constitutes a word.
Q: Does tab or newline character count as space characters?
A: Assume the input does not contain any tabs or newline characters.
Q: Could the input string contain leading or trailing spaces?
A: Yes. However, your reversed string should not contain leading or trailing spaces.
Q: How about multiple spaces between two words?
A: Reduce them to a single space in the reversed string.

// Returns number of words allocated
// Parameters:
//      @)
// Assume strArray is allocated
int seperateString(char* string, char** strArray)
{
    int n = strlen(string);
    // Allocating memory for strArray Maximum of n/2 words
    // Maximum number of words is n/2 " a b c "
    strArray = malloc(sizeof(char*) * (n/2)); // to point to each word
    int count = 0;  // number of words in string
    // To check for last word without spaces
    bool haveWord = false; // new character part of a word that is not saved yet
    int i = 0;
    // Get rid of initial spaces in beginning
    while(string[i] == ' ')
    {
        i++; // go to the first word and skip all the initial spaces
    }

    string = &string[i]; // repoint string to after spaces
    for( ; i < n; i++)
    {
        // " abc  "
        // one space
        if(string[i] == ' ')
        {
            string[i] = '/0'; // close this into a word

            // Get the length of the word just made
            int lenWord = strlen(string); // this will be a shorter length due to closing string

            strArray[count] = (char *)  malloc(sizeof(char) * lenWord);
            strcpy(strArray[count], string);
            string = &string[i+1]; // point it to the next word

            // "quick     brown"
            while(string[i] == ' ')
            {
                i++; // go to the next word and skip all the spaces
            }
            string = &string[i]; // repoint string to after spaces
            count++; // increment number of words
            haveWord = false;
        }
        // Case where it is not a space
        else
        {
            haveWord = true;

        }
    }
    // " hello   "
    // " hello'\0'    "
    // "  hello"

    // To handle case for final word " hello"
    if(haveWord) // string[n] will already be '\0' by definition of the string
    {
        int lenWord = strlen(string); // this will be a shorter length due to closing string
        strArray[count] = (char *)  malloc(sizeof(char) * lenWord);
        strcpy(strArray[count], string);
        count++;

    }
    return count;
}

void reverseSentence(char* string)
{
    char** strArray;


    // Returns number of words that was separated
    int n = seperateString(string, strArray);
    for(int i = 0; i < n/2; i++)
    {
        // Swap it
        swap(strArray[i], strArray[n-i-1]);
    }
    // It just basically merges all the array of strings
    // into a single string, separated by a " "
    mergeString(strArray, string);
    // Separate and swap
    // T(n) = O(n + k ) = O(n) , n = length of string
                                // k = number of words in string
    // merging takes
    // T(n) = O(n);
    // S(n) = O(n);

    // " a boy is good "
    // " " -> delimiter
    // "a" "boy" "is" "good"
    // "good"

}
//Examples
//" the quick      brown fox jumps over the lazy dog " becomes "dog lazy the over jumps fox brown quick the".
//"hello world" becomes "world hello".
//“ Hi! ” is trimmed to “Hi!”.
//“” stays as “”.
*/
//---------------------------------------------------------------------------------------------------
// 1 Reverse a string In-Place
// Time Complexity, T(n) = O(n) 
// Space Complexity, S(n) = O(1)
//-------------------------
/* //
#include <stdio.h>
#include <string.h>
void reverseStr(char* word);

int main(void)
{
    char word[80] = "abcdefg";
    printf("%s\n", word);
    reverseStr(word);
    printf("%s\n", word);
    return 0;
}

void reverseStr(char* word)
{
    int n = strlen(word) - 1;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        char temp = word[n];
        word[n] = word[i];
        word[i] = temp;
        n--;
    }
    return;
}

// Untested
void reverseStrMethod2(char* word)
{
    int n = strlen(word);
    int i = 0;
    for (i = 0; i < n/2; i++)
    {
    	// Swap
        char temp = word[n-1-i];
        word[n-1-i] = word[i];
        word[i] = temp;
    }
    return;
}
// */
//----------------------------------------------------------------------------------------
// 2 Determine if every ASCII character in a string is unique 
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//-------------------------
/*
Algorithm:
    Put into array, increment when found string, if that increment is > 1, that means string not unique.
    Constant size array since limited # of ASCII characters
    If can't use extra space, can
        1. Loop through one by one and compare => O(n^2)
        2. Destroy the string, sort it, and it takes O(nlgn + n) = O(nlgn)
           nlgn to sort, n to loop and compare
// */
//-------------------------
/* //
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define ASCII_LEN 128

bool uniqueStr(const char* word);

bool uniqueStr(const char* word)
{
    if (word == NULL)
        return true;
    int n = strlen(word);
    int table[ASCII_LEN];
    //int index[n];
    int i =  0;
    int j = 0;
    for (i = 0; i < ASCII_LEN; i++)
    {
        table[i] = 0;
    }
    for (j = 0; j < n; j++)
    {
        int value = word[j];
        table[value]++;
        if (table[value] > 1)
            return false;
    }
    return true;
}


int main(void)
{
    char* str1 = "abc";
    char* str2 = "abca";
    assert(uniqueStr(str1));
    assert(!uniqueStr(str2));
    return 0;
}

/* //
// Approach 2 using STL
#include <string>
#include <unordered_map>
#include <cstring>
#include <iostream>
using namespace std;
int main(void)
{
    string uniqueStr;
    cin >> uniqueStr;
    const char* temp = uniqueStr.c_str();
    unordered_map<char, int> table;
    int n = uniqueStr.size();
    for(int i = 0; i < n; i++)
    {
        table[temp[i]]++;
        if(table[temp[i]] > 1)
        {
            cout << " Not UNIQUE" << endl;
            return 0;
        }
    }
    cout << "UNIQUE" << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 3 Determine if every ('a' to 'z') character in string is unique using Bit Manipulation
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//-------------------------
/* 
Algorithm:
    Simplification: only characters 'a' to 'z'
    Takes O(n) time and saves a tonne of space but only works of from 'a' to 'z'
*/
//-------------------------
/* //
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
bool uniqueStr(const char* word);

int main(void)
{
    char* str1 = "abc";
    char* str2 = "abca";
  //  uniqueStr(str1);
  //  uniqueStr(str2);
    assert(uniqueStr(str1));
    assert(!uniqueStr(str2));
    return 0;
}

bool uniqueStr(const char* word)
{
    int n = strlen(word);
    unsigned int storage = 0;
    int i = 0;
    for (i = 0; i < n ; i++)
    {
        // Calculate the amount to shift by
        unsigned int shift = word[i] - 'a';
        unsigned int compare = 1 << shift; // initialize 1 bit and shift by the shift amount
        // If it existed, will and to a 1 here
        // Since compare will only have 1 bit set to 1
        if (storage&compare)
        {
            printf(" I am false\n");
            return false;
        }
        storage |= compare;
    }
    printf("TRUE\n");
    return true;
}
// */
//----------------------------------------------------------------------------------------
// 4. Remove Duplicated characters of strings in place
// Time Complexity, T(n) = O(n^2)
// Space Complexity, S(n) = O(1)
//-------------------------
/*
TestCase: 
    haakele => hakel
*/
//-------------------------
/*
#include <string>
#include <iostream>
using namespace std;
int main(void)
{
    string duplicatedString;
    cin >> duplicatedString;

    int tail = 1;
    for(int i = 1; i < duplicatedString.size(); i++)
    {
        bool exists = false;
        for(int j = 0; j < tail; j++)
        {
            if(duplicatedString[i] == duplicatedString[j])
            {
                exists = true;
                break;
            }
        }
        if(!exists)
        {
            duplicatedString[tail] = duplicatedString[i];
            tail++;
        }
    }
    duplicatedString = duplicatedString.substr(0,tail);
    cout << duplicatedString;
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 5 Implement Compression of a string (Amazon Round 1)
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(n)
//-------------------------
/* 
e.g. aabcccccaaa
With this function call 
char* compress(char* inputStr);
Note: You made the mistake of using arrays of characters and integers instead of outputting char *!!
should have done: a3b5c3d1e3f1a2b1c1 instead!
*/
//-------------------------
/* //
#include <iostream> 
#include <string> 
#include <cstring> 
#include <cstdio>
#include <cstdlib> // itoa(int, char*, baseForInt)
using namespace std; 

char* compress(char* inputStr);

int main(void) 
{
    string bigString = "aabccccaaa";
    const char* temp = bigString.c_str();
    char* compressed; 
    char* temp2; 
    strcpy(temp2, temp);
    compressed = compress(temp2);
    cout << bigString << endl;
    printf("%s\n",compressed);
}

char* compress(char* inputStr)
{
    if (strlen(inputStr) == 0) return inputStr;
    // Must malloc
    char* compressed = (char*) malloc(strlen(inputStr));
    compressed[strlen(inputStr)] = '\0';
    unsigned long long int index = 0;
    compressed[index] = inputStr[0];
    char* temp3 = (char*) malloc(strlen("haha")) ;
    int count = 1;
    for (int i = 1; i < strlen(inputStr); i++)
    {
        if (inputStr[i] == compressed[index]) 
        {
            count++;
        }
        else
        {
            itoa(count,temp3, 10);
            compressed[++index] = temp3[0];
            count = 1; // initialize count
            compressed[++index] = inputStr[i];
        }
    }
    // Set last integer for string
    itoa(count,temp3, 10);
    compressed[++index] = temp3[0];
    // Null terminate it
    compressed[++index] = '\0';
    return compressed; 
}
// */
//----------------------------------------------------------------------------------------
// 6 Longest Substring With Distinct Characters
// Time Complexity, T(n) = O(n) (single pass)
// Space Complexity, S(n) = O(1)
//-------------------------
/*
Questions: 
    1. Return length or position of substring or substring itself? 
    2. What can the string contain? ASCII only or a-z or? Does upper/lower cases matter?
Function Prototype:
    int LongestSubstringDistinctCharacters(string str); 
TestCase:
    "abcabcbb" => "abc"  = 3
    "bbbbb" => "b" = 1
    "abcdb" => "abcd" = 4
    "abcdbefg" => "cdbefg" = 6
Algorithm:
    Algorithm 1: 2 pointers, 1 ascii array, T(n) = O(2n), S(n) = O(256) = O(1)
        Loop from beginning to end in 1 pass, keeping track of number of characters, 
        whenever same character is met, move start point to 1 after same character. 
        Keep track of maximum everytime you have to move and at end of string 
        To know if detected same character, use bits (if < 64), or bool arr[256] if ASCII 
        Assume only ASCII 
            use bool arr[256] to store space => O(1) space 
            move start pointer until meet duplicate, and move 1 after duplicate
            => 2 passes since both pointers need move entire string in worst-case
    Algorithm 2: 2 pointers, 1 map of character to index array, T(n) = O(n), S(n) = O(256) = O(1)
        Here, instead of storing whether a character exist by count in the bool arr[256], 
        you store index of the character using int arr[256]
        therefore, if you meet it and the index != [-1] which is the initial value, 
        you know you found a duplicate, then you just jump your first pointer to that index, and update the index to be the later position
        Thus, first pointer jumps around, whereas 2nd pointer moves to end
        Therefore, only 1 pass needed
Implement!
*/
//-------------------------
/* //
#include <cstring>
#include <string> 
#include <vector>
#include <iostream> 
using namespace std;
int LongestSubstringDistinctCharacters(string str)
{
    const char * newStr = str.c_str();
    int n = strlen(newStr);
    vector<int> arr(256, -1);
    // Initialize pointers to loop
    int i = 0;
    int j = 0;
    int longestSub = 0;
    while (j < n)
    {
        if(arr[newStr[j]] == -1)
        {
            arr[newStr[j]] = j;  // initialize the first index
        }
        else
        {
            // Update longest Substring
            if (longestSub < (j-i)) longestSub = (j-i);
            i = arr[newStr[j]] + 1;  // move i to 1 after old index 
            arr[newStr[j]]  = j;  // update index for this character
        }
        j++; // MISTAKE: Forget to increment j!
    }
    // Handle end of string case
    if (longestSub < (j-i)) longestSub = (j-i);
    return longestSub;
}

int main(void)
{
    string a = "abcabcbb"; 
    string b = "bbbbb"; 
    string c = "abcdb"; 
    string d = "abcdbefg"; 
    string e = "a"; 
    int answer = LongestSubstringDistinctCharacters(a);
    cout << a << " " << answer << endl;
    answer = LongestSubstringDistinctCharacters(b);
    cout << b << " " << answer << endl;
    answer = LongestSubstringDistinctCharacters(c);
    cout << c << " " << answer << endl;
    answer = LongestSubstringDistinctCharacters(d);
    cout << d << " " << answer << endl;
    answer = LongestSubstringDistinctCharacters(e);
    cout << e << " " << answer << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 7 Longest Substring With At Most K Distinct Characters 
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(n)
//-------------------------
/*
Questions: 
    1. Does upper/lower cases matter? 
    2. What if string is empty "", or NULL?
    3. Return length or substring itself? Can original string be modified? 
FunctionPrototype:
    int LongestSubstringAtMostKDistinct(string str, int k);
TestCases:
    "eceba", k = 2 => "ece" = 3
    "a", k >= 1 => "a" = 1 
Algorithm:
*/
//-------------------------
/* //
#include <unordered_map> // C++ 11 Feature: Mistake: Included <map> instead of <unordered_map>, only multimap<int,int> requires <map> instead of <multimap>
#include <cstring>
#include <string>
#include <iostream> 
using namespace std;

int LongestSubstringAtMostKDistinct(string str, int k)
{
    const char * newStr = str.c_str();
    int n = strlen(newStr);
    if (n <= 0 || k < 1) return 0;
    int longestSub = 0;
    // Create hashtable to store count
    unordered_map <char, int> m; // note: Replace with vector<int> arr[256] if ASCII only
    // To keep track of number of distinct characters
    int numDistinct = 0;
    int j = 0;
    for(int i = 0; i < n; i++)
    {
        // If character doesn't exist, initialize it and increment numDistinct
        if(!m.count(newStr[i]))
        {
            m[newStr[i]] = 1; 
            numDistinct++;
        }
        // If character exist, add to it
        else
        {
            m[newStr[i]] += 1;
        }
        while(numDistinct > k)
        {
            m[newStr[j]] -= 1;

            if (m[newStr[j]] == 0)
            {
                // erase this from hashTable
                m.erase(newStr[j]);
                numDistinct--; // Decrement numDistinct
            }
            j++;
        }
        // Only calculate accounting for no new characters
        longestSub = max(longestSub, i - j + 1);
    }
    return longestSub;
}

int main(void)
{
    string a = "eceba"; 
    int k = 2;
    int result = LongestSubstringAtMostKDistinct(a,k); // 5
    cout << a << " " << result << endl;
    string b = "a"; 
    result = LongestSubstringAtMostKDistinct(b, k); // 1
    cout << b << " " << result << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 8 Isomorphic Strings
// Time Complexity, T(n,m) = O(n)
// Space Complexity, S(n,m) = O(n)
//-------------------------
/* Given 2 words, return if they are isomorphic. Isomorphic means one word can map to the other by assigning each of its alphabet to another alphabet. 
However, no 2 alphabet can map to the same alphabet. An alphabet can map to itself. Ordering of letters must remain the same

TestCases:
    foo, app => true cause f=a, o->p
    bat, loo => false since  b=l, a=o, but t!=o since a=o already 
    ab, ca => true since a=c, b=a
Algorithms:
    Will only take O(n) complexity as length of strings needs to be the same
    
*/
//-------------------------
/* //
#include <unordered_map> // C++ 11 feature
#include <string>
#include <iostream> 
using namespace std; 

bool isIsomorphic(string str1, string str2)
{
    if(str1.length() != str2.length()) return false;
    unordered_map<char, int> hashStr1, hashStr2;
    int n = str1.length();
    for(int i = 0; i < n; i++)
    {
        // assign hashes if not yet already
        if(!hashStr1.count(str1[i]))
           hashStr1[str1[i]] = i; 
        if(!hashStr2.count(str2[i]))
           hashStr2[str2[i]] = i; 
        if(hashStr1[str1[i]] != hashStr2[str2[i]]) return false;
    }
    return true;
}

int main(void)
{
    string str1 = "foo";
    string str2 = "app";
    if (isIsomorphic(str1, str2)) cout << str1 << " and " << str2 << " are isomorphic" << endl;
    else cout << str1 << " and " << str2 << " NOT isomorphic" << endl;
    str1.assign("bat"); str2.assign("loo");
    if (isIsomorphic(str1, str2)) cout << str1 << " and " << str2 << " are isomorphic" << endl;
    else cout << str1 << " and " << str2 << " NOT isomorphic" << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 9 Exact Matching: Z-Algorithm
// Time Complexity, T(n,m) = O(n + m)
// Space Complexity, S(n,m) = O(n + m)
//-------------------------
/*
Algorithm: 
    Z-array = number of exact matching of a string with its own prefix 
    Z[0] = strlen(str), redundant case 
    Then, let newStr = strcat(pattern,text) 
    After computing Z[i], 
    T(n,m)  = O(m+n) => To find indices of exact matching
    For every Z[i] >= strlen(pattern), there is an exact matching at that location, i >= strlen(pattern)
    S(n,m) = O(m+n) => To hold the z-array
    Computing Z[i] also takes T(n,m) = O(m+n)
    Let R[i] = the furthest Z[j] can reach from j = 2,...,i
    Let L[i] be the corresponding j for R[i] where L[i] can be any of them if multiple Z[j]'s reachest the same furthest
    Z[1] is basically all m comparisons., start computing from Z[2] since needed for Case 2 below
    Assuming computed R[i-1], L[i-1] and Z[i-1] properly, 
    Case 1: i > R[i-1]
        Z[i] = compute from scratch again  as well as R[i] and L[i]
    Case 2: i <= R[i-1]
        // note: +1 cause inclusive deduction
        Calculate a = Z[i - L[i-1] + 1], b = R[i-1] - i 
        case (A):
            if a < b, Z[i] = Z[i - L[i-1] + 1, L[i] = L[i-1], R[i] = R[i-1] 
        case {B}: 
            else (a >= b), 
                start comparing from str[R[i-1]+1] with str[i - L[i-1] + 1 + b]
                and compute from scratch again for Z[i]. R[i], and L[i]
    TODO: Implement and check corner cases above (-1 or +1 etc.)
*/
//-------------------------
/* //
#include <string> 
#include <vector> 
#include <iostream> 
using namespace std; 

vector<int> zAlgorithm(string text, string pattern)
{
    vector<int> solution;  
    string concat = "";
    concat.assign(pattern);
    concat.append(text);
    vector<int> zArray (concat.length(), 0); // MISTAKE: initialize as (0, length) instead of (length, 0)

    int left = 0;  // Since only depend on L[i-1], can just use left, will be initialize to 1 at first iteration
    int right = 0; // Since only depend on R[i-1], can just use right
    // note: Base case is already handled since R[0] = 0, and i = 1 at first iteration
    for(int i = 1; i < zArray.size(); i++)
    {
        // Re-count everything since passed the last matched character 
        if(i > right)
        {
            left = i; 
            int matchLength = 0; 
            while(((i + matchLength) < zArray.size()) && (concat[i + matchLength] == concat[matchLength]))
            {
                matchLength++;
            }
            zArray[i] = matchLength; // number of index that match for Z[i]
            right = i + matchLength - 1; // Since 0 indexing, need  to - 1
        }
        // This is part of an exact matching position 
        else
        {
            // Check if string at position of i - L[i-1] is more than or less than R[i-1]
            if( zArray[i - left] < right - left)
            {
                zArray[i] = zArray[i-left];
                // right and left remains the same
            }
            // Otherwise, begin matching from (right-left) onwards
            else
            {
                // new maximum is found (may maintain same right) 
                left = i; 
                int matchLength = right - i + 1; // skip to compare from right+1 onwards
                while(((i + matchLength) < zArray.size()) && (concat[i + matchLength] == concat[matchLength]))
                {
                    matchLength++;
                }
                // update right and zArray[i]
                zArray[i] = matchLength; // number of index that match for Z[i], MISTAKE: FORGOT TO UPDATE zArray[i]
                right = i + matchLength - 1; // Since 0 indexing, need  to - 1
            }
        }
        // Check if current i matches the pattern completely
        if ((zArray[i] >= pattern.length()) && (i >= pattern.length())) // MISTAKE: Forgot to make sure i is out of pattern's indices
        {
            solution.push_back(i-pattern.length()); // Mistake: Forgot to deduct the original pattern.length() to get position in original text
        }
    }
    cout << endl;
    return solution;
}

int main(void)
{
    string text = "I am a boy amto bilamd"; 
    string pattern = "am";
    vector<int> solution = zAlgorithm(text, pattern); // 2, 11, 19
    for(int i = 0; i < solution.size(); i++)
    {
        cout << solution[i] << " ";
    }
    cout << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------
