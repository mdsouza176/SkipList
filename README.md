# SkipList

This SkipList project creates a skiplist data structure from the skiplist.cpp and .h files and then in the Main.cpp, calls the structure
and adds integer input to it.

The skipList takes a depth integer to start. It then puts numbers inputted in sorted order of least to greatest. This is depth 1. If depth
is greater than one, it will flip a coin and if heads, add that integer at a higher level depth, it will flip again until it either fails
or the depth is less than the level. It does this for all integers.
