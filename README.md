anagram
=======

This library is meant to provide an efficient mechanism for finding
anagrams (full, partial or both) of an input string efficiently.

My initial tests have centered around an english dictionary of about
80k words, and to find all the anagrams (and partial anagrams) for 
all the words in the dictionary takes about 10 seconds.

Bindings
========

I was initially most interested in having anagram functionality from
`node.js` and python, and so I wrote the library itself in C, and have
an initial C++ extension for `node` in the corresponding subdirectory.

These are simply the two languages with which I have the most familiarity
when it comes to writing extensions, but if you have other languages
you'd like supported, I welcome your contributions!