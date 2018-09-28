# Morse-Code-Translator
Morse Code encoder/decoder written in C++

I wrote this last year for fun and figured I might as well upload it.
The program has 2 options: encode or decode

Encode: the program takes the text in alphabet.txt and translates it into Morse
Code, and writes it to encoded.txt. Characters without Morse Code equivalents are
held over (ex: punctuation) and appear in the encoded message.

Decode: the program takes the Morse Code in encoded.txt and translates it into
English, writing the translation to alphabet.txt. 

Format: though there is some leeway with the input format, the program generally
expects the following format, which is the output format - 
-  a space between the set of dots and dashes representing each letter/number
-  a forward slash between words
-  punctuation as expected in regular writing (although ., and ? can be encoded)
