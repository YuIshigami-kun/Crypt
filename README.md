# Crypt
Crypt is a project for encrypting an decrypting data using a custom algorithm (don't use in serious projects, I've made it just for practise).

It takes two keys to encrypt: the complement which is a temporal key and the main key that is used to decrypt the text. The key is 208 characters long and the complement is 100 (the only characters you can use are ```ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz```).

View the usage.cpp if you want documentation.

## How it works?

### Encrypt.h

1. First we pick an input like "abcdefghijk".

2. The program will break it in blocks of 8 chars ("abcdefgh", "ijk").

3. Then it will swap the blocks if it's possible ("ijk", "abcdefgh").

4. Now it will iterate the blocks and do the next algorithm:
    - Using the complement, if the char c is found in the complement replace the char in the complement       with the index of c in the string.
    - If the char isn't found it's appended to a string (end) and then the index in the string is             appended ("o" in the string "hello" would end like "o4").
    - Append the string end with all the chars and index to the modified complement.
    - Adds the result to another string and goes on with the next block.

5. Add the complement at the start of the result string.
6. Now using the key it breaks the key in groups of 4 chars and assing a character to it.
7. Replace the characters with the 4 characters long blocks of the key.

### Decrypt.h

1. Having the key gets the blocks of 4 chars (you obviously need the key).

2. Decrypts the text using the blocks, gets the complement and gets the text.

3. Using the complement gets the text before the complement algorithm.

4. Breaks the text in blocks of 8 chars and swap them.

5. Converts the text to a unique string.

## Contact
[Telegram](http://t.me/Yulshigami)

## Donations
BTC --> bc1q4g6h98z72dr65qnyuw44979jelk077mmc3xucl

ETH --> 0x30fd7278c10Ea6B82982a4f2717fB6dC6C238886

LTC --> LV5Y591opDFw5zBto7zCWGgxHiF66SyvbW

DOGE --> DQbK8DSG8JNmLpz7hjToHwTnpNwzXiXehn
