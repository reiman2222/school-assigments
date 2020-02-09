# Break LSFR

# time: 45 min

# plain text: HI! ISN’T THIS TOO EASY?

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

def fiveByteToChar(b):
    num = 1 * int(b[4]) + 2 * int(b[3]) + 4 * int(b[2]) + 8 * int(b[1]) + 16 * int(b[0])
    
    if(num < 26):
        return intToChar(num)
    else:
        if(num == 26):
            return ' '
        elif(num == 27):
            return '?'
        elif(num == 28):
            return '!'
        elif(num == 29):
            return  '.'
        elif(num == 30):
            return '’'
        else:
            return '$'

def bitStringToChars(bitStream):
    text = ''
    for i in range(0, len(bitStream), 5):
        charByte = bitStream[i:i+5]
        #print(charByte)
        c = fiveByteToChar(charByte)
        #print(c)
        text += c

    return text

def generateKeyStream(length, iv):
    #iv to bit str
    keystream = ''
    for b in iv:
        keystream += str(b)

    i = 4
    while(i < length - 1):
        nextBit = int(keystream[len(keystream) - 5]) ^ int(keystream[len(keystream) - 2])
        keystream += str(nextBit)
        i +=1

    return keystream

def xorKeystreamAndCipherStream(keystream, chipherStream):
    plainBits = ''
    i = 0
    while(i < len(keystream)):
        #print(keystream[i])
        #print(chipherStream[i])
        
        b = str(int(keystream[i]) ^ int(chipherStream[i]))
        #print('result = ' + b)
        plainBits += b
        i += 1
    return plainBits
#   MAIN    #

cipherBits = readCipherText('bits.txt')

print(bitStringToChars(cipherBits))

print('H')
print(characterToInt('H'))
print('I')
print(characterToInt('I'))

iv = [0,1,0,1,0]
coeffcientes = [1,0,0,1,0]
keystream = generateKeyStream(len(cipherBits), iv)
print('cipher bits')
print(cipherBits)
print('key stream')
print(keystream)
plainBits = xorKeystreamAndCipherStream(keystream, cipherBits)
print('plain bits')
print(plainBits)
print(bitStringToChars(plainBits))
