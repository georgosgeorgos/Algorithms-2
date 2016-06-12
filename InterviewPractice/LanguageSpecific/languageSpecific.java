/* 
//-------------------------
// Strings
//-------------------------
1. Never concatenate strings in a Loop
2. Compare string using .equals NOT ==
3. Compare string from constant to variable

*/
//----------------------------------------------------------------------------------------------------------------------------------
// Strings
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Never concatenate strings in a Loop
//---------------------------------
Never concatenate strings in a loop like that
String s = "";
for (int i = 0; i < 100; i++) {
        s += ", " + i;
}
Use StringBuilder as more efficient instead 
StringBuilder builder = new StringBuilder();
for (int i = 0; i < 100; i++) {
       builder.append(Integer.toString(i));
}
String s = builder.toString();

However, it is fine if you use it in a line as it is turned into StringBuilder by compiler automatically 
String s = "1, " + "2, " + "3, " + "4";
//----------------------------------------------------------------------------------------------------------------------------------
// 2 Compare string using .equals NOT ==
//---------------------------------
String a = "hello";
String b = "hello";
assertFalse(a == b); // not same object
assertTrue(a.equals(b));
//----------------------------------------------------------------------------------------------------------------------------------
// 3 Compare string from constant to variable
//---------------------------------
from:
    if(b.equals("hello")) // a runtime exception if b == NULL
to:
    if("hello".equals(b)) // handles if b == NULL case
//----------------------------------------------------------------------------------------------------------------------------------
