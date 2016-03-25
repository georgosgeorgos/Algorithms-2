/* //
Table Of Contents
    Goals
// */

//-------------------------------------------------------------------------------------------
// Goals
//-------------------------------------------------------------------------------------------
Refactoring = A change made to internal structure of software so that it is easier to understand, modify, and debug without changing any observable behavior.

//----------------------------
Remove any unnecessary variables with the function calls that gave them directly 
    from: 
        int lala = getLala();
        doBaba(lala);
        doCaca(lala);
    to:
        doBaba(getLala());
        doCaca(getLala());
//----------------------------
Replace a single variable that gets re-assigned many times to what it represents
    from: 
        int a = scoreX + scoreY; 
        ...
        a /= (maxScoreX + maxScoreY); 
    to:
        int sumScore = scoreX + scoreY; 
        ...
        int normalizedSumScore = sumScore/(maxScoreX + maxScoreY);
    to: 
        getSumScore();
        ...
        getNormalizedSumScore(); 
//----------------------------
Move responsibilities from a class to a new class, and make the original class contain that new class as a member variable. 
