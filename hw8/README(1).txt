Lukas Griffin & Thomas Nemeh
Encode: Constructs a Huffman tree based on the frequency of letters in a file.
Decode: Reads a file generated by encode and write a decoded version of that file to a specified output file. Constructs a Huffman tree based on the frequency of letters in a file.
No none bugs
Took us 20 hours.
None.
Valgrind showed that there were bytes that were still reachable within encode.c. However, there were no errors are lost memory. 
