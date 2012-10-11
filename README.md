Metta Transliterator
====================

This is a simple program to convert Tipitaka file written in metta font in to
unicode. Tipitaka text can be found at [metta.lk](http://metta.lk/tipitaka/index.html)

I collaborated with venerable Mettavihari to write this program. It's in working 
state but according to bhikku there are some little fixes to be done all 
over the place. Tipitaka is serious business :).

Anguttara Nikaya text should be transliterated without a problem. At the time I 
dropped the ball on this project we were woking on Diga Nikaya. 
Then we both got busy :(

You can compile the program with
`$ gcc -o mettatr.out mettatr.c`

Then run
`$ ./mettatr.out <input file> <output file>`

The resources directory includes what I worked with. You'd need Bhashitha font to view
touching letters (bandi akuru) properly.

I was provided with a file which I later found out to be in ISO-8859 encoding.
(use 'file' command for this). This file is found in resources directory as
Anguttara_Nikaya_1_ISO8859.txt

I used following command to convert it to utf-8.

`$ iconv -f iso-8859-15 -t utf-8 file > output.file`

The converted file is found as Anguttara_Nikaya_1_UTF8.txt

The program can now convert the utf8 text to sinhala unicode (mettatr only works on utf-8 text).
`$ ./mettatr.out Anguttara_Nikaya_1_UTF8.txt Anguttara_Nikaya_1_UTF8_sinhala.txt`
