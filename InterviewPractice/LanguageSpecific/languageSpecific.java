//---------------------------------------------
// Concatenate Strings in loops
//---------------------------------------------
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

