# BREAK VIGENERE CIPHER

#time: 
import itertools

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

def dechipherStringShift(ciphertext):
    cFreq = calcNgramFreq(ciphertext, 1)

    sFreq = sortFreq(cFreq)
    key = (characterToInt(sFreq[0][0]) - characterToInt('E')) % 26
    plaintext = ""
    for char in ciphertext:
        plaintext = plaintext + decipherChar(key, char)

    return key, plaintext

def dechipherString(k, ciphertext):
    plaintext = ""
    for char in ciphertext:
        plaintext = plaintext + decipherChar(k, char)

    return plaintext

def iC(text):
    freqDict = calcNgramFreq(text, 1)
    N = 0.0
    sumI = 0.0

    for freq in freqDict.values():
        i = freq
        sumI += i * (i - 1)
        N += i
    
    if(N == 0.0):
        return 0.0

    return sumI / (N * (N - 1))

def compteIcForValuesOfM(cipherText, m):
    cArray = [""] * m

    #split string in to m strings
    i = 0
    for c in cipherText:
        index = i % m
        cArray[index] += c
        i += 1
    
    icArray = [0] * m
    i = 0
    for s in cArray:
        icArray[i] = iC(cArray[i])
        i += 1

    return icArray

def avg(doubleL):
    return sum(doubleL) / len(doubleL)

def pArrayToString(pA):
    m = len(pA)
    plaintextL = [''] * (m * len(pA[0]))
    
    #totalChar = m * len(pA[0])

    
    i = 0
    j = 0
    pos = 0
    for i in range(0, len(pA[0])):
        for j in range(0, len(pA)):
            if(i < len(pA[j])):
                plaintextL[pos] = pA[j][i]
                pos += 1
    
    plaintext = ''
    for ch in plaintextL:
        plaintext += ch
    return plaintext


def cipherTextToMlists(cipherText, m):
    cArray = [""] * m

    #split string in to m strings
    i = 0
    for c in cipherText:
        index = i % m
        cArray[index] += c
        i += 1
    return cArray
    

def computePossibleKey(m, cipherText):
    cArray = [""] * m
    
    #split string in to m strings
    i = 0
    for c in cipherText:
        index = i % m
        cArray[index] += c
        i += 1

    key = [''] * m

    pArray = [''] * m

    clearText = ''
    i = 0
    for j in cArray:
        key[i], pArray[i] = dechipherStringShift(j) 

        i += 1

    return key, pArray

def keyToString(key):
    k = ''
    for c in key:
        k += intToChar(c)
    return k

def stringToKey(s):
    key = []
    for c in s:
        key.append(characterToInt(c)) 

def decipherVWithChosenKey(key, cipherText):
    cA = cipherTextToMlists(cipherText, len(key))
    pA = [''] * len(key)

    i = 0
    for k in key:
        
        pA[i] = dechipherString(characterToInt(k), cA[i])
        i += 1
    
    return pArrayToString(pA)

def generateProbableKeys(m, cipherText):
    keysM = []

    cA = cipherTextToMlists(cipherText, m)
    i = 0
    for l in cA:
        
        cFreq = calcNgramFreq(l, 1)
        sFreq = sortFreq(cFreq)
        mostFreq = sFreq[0][1]
        curFreq = mostFreq

        j = 0
        kI = []
        top5 = l[0:5]

        for t in top5:
            kI.append(intToChar((characterToInt(sFreq[j][0]) - characterToInt('E')) % 26))
            curFreq = sFreq[j][1]

            j += 1       
        keysM.append(kI)

        i += 1
    return keysM

def keyMatrixToStrings(keys):
    keyL = list(itertools.product(*keys))

    kS = []
    for l in keyL:
        k = ''
        for c in l:
            k += c
        kS.append(k)
    return kS
        

#      MAIN        #

cipherText = readCipherText('vigenere-cipher.txt')

icE = 0.065

for i in range(2, 25):
    icI = compteIcForValuesOfM(cipherText, i)
    print('m = ' + str(i))
    print('avg = ' + str(avg(icI)))



pM = [3, 6, 12, 24]
'''
for m in pM:
    print('m = ' + str(m))
    key, pA = computePossibleKey(m, cipherText)
    print(keyToString(key))
    print(pArrayToString(pA))
    print('')
'''

keys = generateProbableKeys(6, cipherText)
keysS = keyMatrixToStrings(keys)

possible = []
for k in keysS:
    text = decipherVWithChosenKey(k, cipherText)
    if('THE' in text):
        possible.append((k,text))
    
uInput = input('press enter to continue stop to stop')
i = 0
while(uInput != 'stop'):
    tup = possible[i]
    print('k = ' + tup[0])
    print(tup[1])
    uInput = input()
    i += 1



#decipherVWithChosenKey(key, cipherText)
