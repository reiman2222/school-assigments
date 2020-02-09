# Brute Foraces a shift cipher

#spent 30 min


def readCipherText(filename):
    with open(filename, 'r') as f:
        ciphertext = f.read().strip()

    return ciphertext

def characterToInt(char):
    return ord(char) - 65

def intToChar(num):
    return chr(num + 65)

def decipherChar(key, character):
    return intToChar((characterToInt(character) - key) % 26)

def dechipherString(key, ciphertext):
    plaintext = ""
    for char in ciphertext:
        plaintext = plaintext + decipherChar(key, char)

    return plaintext


#       MAIN        #


ciphertext = readCipherText('shift-cipher.txt')

key = 0
while(key < 26):
    print('\nKey=' + str(key))
    print(dechipherString(key, ciphertext))
    

    key += 1


#Answer

#Key=10
#CRYPTOGRAPHY CERTAINLY HAS COME ALONG WAY SINCE THE FIRST CENTURY WHEN JULIUS CAESAR REPORTEDLY USED A NAIVELY SIMPLE CIPHER