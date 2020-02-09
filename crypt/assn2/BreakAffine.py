#break affine chipher
#spent 1hr 30 min

def readCipherText(filename):
    with open(filename, 'r') as f:
        ciphertext = f.read().strip()

    return ciphertext

def characterToInt(char):
    return ord(char) - 65

def intToChar(num):
    return chr(num + 65)

def sortFreq(frequencyDict):
	tuples = list(frequencyDict.items())
	sortedGrams = sorted(tuples, key=lambda k: k[1], reverse=True)
	return sortedGrams

def calcNgramFreq(cipherText, n):
	freqDict = {}

	for i in range(len(cipherText) - n + 1):
		nGram = cipherText[i:i+n]
		if nGram in freqDict:
			freqDict[nGram] += 1
		else:
			freqDict[nGram] = 1
	return freqDict

def exgcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = exgcd(b % a, a)
        return (g, x - (b // a) * y, y)

#returns none if a is not invertable mod 26
def modInverse(a):
    gf, x, y = exgcd(a, 26)
    if(gf == 1):
        return x % 26
    else:
        return None

def computePossibleKey(cipherChar1, cipherChar2, plainChar1, plainChar2):
    cipherInt1 = characterToInt(cipherChar1)
    cipherInt2 = characterToInt(cipherChar2)
    plainInt1 = characterToInt(plainChar1)
    plainInt2 = characterToInt(plainChar2)

    aFactor = (plainInt1 - plainInt2) % 26
    bFactor = (cipherInt1 - cipherInt2) % 26


    aFactorInv = modInverse(aFactor)

    if(aFactorInv == None):
        return None, None
    else:
        a = (aFactorInv * bFactor) % 26
        b =  (cipherInt1 - ((plainInt1 * a) % 26)) % 26
        return a, b


def dechipherChar(c, aInv, b):
    cint = characterToInt(c)

    plainChar = intToChar((aInv * (cint - b)) % 26)

    return plainChar 

def decipherString(a, b, cipherText):
    aInv = modInverse(a)
    if(aInv == None):
        return None
    plainText = ""

    for c in cipherText:
        plainText += dechipherChar(c, aInv, b)
    
    return plainText

cipherText = readCipherText('affine-cipher.txt')

uniFreq = calcNgramFreq(cipherText, 1)

sortedFreqTuples = sortFreq(uniFreq)

charOrder = ['e', 't', 'a', 'o', 'i', 'n', 's', 'r', 'h', 'l', 'd', 'c', 'u', 'm', 'f', 'p', 'g', 'w', 'y', 'b', 'v', 'k', 'x', 'j', 'q', 'z']

print("press enter to try to decrypt again stop to stop")

i = 0
while(i < len(sortedFreqTuples)):
    j = 0
    
    while(j < len(sortedFreqTuples)):
        if(i != j):
            plainChar1 = charOrder[i].upper()
            cipherChar1 = sortedFreqTuples[i][0]
            plainChar2 = charOrder[j].upper()
            cipherChar2 = sortedFreqTuples[j][0]

            a, b = computePossibleKey(cipherChar1, cipherChar2, plainChar1, plainChar2)
            print('Trying: ' + cipherChar1 + ' -> ' + plainChar1 + ', ' +  cipherChar2 + ' -> ' + plainChar2)


            if(a != None):
                print('a = ' + str(a) + ', b = ' + str(b))

                plainText = decipherString(a, b, cipherText)
                if(plainText == None):
                    print('Cannot dechipher a has no inverse\n')
                else:
                    print(plainText + '\n')

                    usrInput = input()

                    if(usrInput == 'stop'):
                        exit()
            else:
                print("Invalid Possibility")
        j += 1
    i += 1