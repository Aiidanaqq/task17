In this code I used the technique Run-Length Encoding (RLE).
I used the Fleet compiler in my work. To test my code in this compiler, you need to add the 'run.json' file to the library, which I attached to my GITHUB. 
When you press 'RUN' the code automatically produces the files 'compressed.txt' and 'decompressed.txt' which contain ready-made text.

1.Compression Function ('compress'):
-This function takes a string 'inputText' as input and compresses it using Run-Length Encoding.
-It iterates through each character of the input text.
-For each character, it counts the consecutive occurrences of that character.
-When it encounters a different character or reaches the end of the input text, it appends the count followed by the character to the 'compressedStream'.
-Finally, it returns the compressed string.

2.Decompression Function ('decompress'):
-This function takes a compressed string 'compressedText' as input and decompresses it back to the original text.
-It iterates through pairs of characters in the compressed text, where the first character represents the count and the second character represents the repeated character.
-It constructs the decompressed string by repeating each character according to its count.
-Finally, it returns the decompressed string.

3.Main Function:
-The main function is where the compression and decompression processes are orchestrated.
-It opens three files: 'input.txt' for reading, 'compressed.txt' for writing compressed data, and 'decompressed.txt' for writing decompressed data.
-If any of the file operations fail, it prints an error message and exits with a non-zero status.
-It reads the content of 'input.txt' into a string using a 'stringstream'.
-It compresses the input text using the compress function and writes the compressed data to 'compressed.txt'.
-It decompresses the compressed text using the 'decompress' function and writes the decompressed data to 'decompressed.txt'.
-Finally, it prints a message indicating that the compression and decompression processes are complete.
