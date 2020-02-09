#break hill chipher

#2 hrs

def readCipherText(filename):
    with open(filename, 'r') as f:
        ciphertext = f.read().strip()

    return ciphertext

def charToInt(char):
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
#k = [[a, b], [c, d]]
#expects k to be 2 by 2 list of ints
def det2by2(k):
    return (((k[0][0] * k[1][1]) % 26) - ((k[0][1] * k[1][0]) % 26)) % 26 

#returns None if inv does not exist
def inv2by2(k):
    invDet = modInverse(det2by2(k))
    if(invDet == None):
        return None
    else:
        sk = [[k[1][1], (-1 * k[0][1]) % 26], [(-1 * k[1][0]) % 26, k[0][0]]]
        
        invK = [[sk[0][0] * invDet % 26, sk[0][1] * invDet % 26], 
            [sk[1][0] * invDet % 26, sk[1][1] * invDet % 26]]
        return invK

def print2by2(k):
    print('key = [ ' + str(k[0][0]) + ' ' + str(k[0][1]) + ']')
    print('      [ ' + str(k[1][0]) + ' ' + str(k[1][1]) + ']')

#returns a * b mod 26
def multpilyModMatrix(a, b):
    result = []
    for i in range(len(a)):
       result.append([0] * len(b[i]))
    #result = [[0, 0], [0, 0]]
    for i in range(len(a)):
        for j in range(len(b[0])):
            for k in range(len(a[0])):
                result[i][j] += a[i][k] * b[k][j] % 26

    for i in range(len(result)):
        for j in range(len(result[0])):
            result[i][j] = result[i][j] % 26

    return result

def computePossibleKey(cipherBi1, cipherBi2, plainBi1, plainBi2):
    leftM = [[charToInt(plainBi1[0]), charToInt(plainBi1[1])],
                [charToInt(plainBi2[0]), charToInt(plainBi2[1])]]
    rightM = [[charToInt(cipherBi1[0]), charToInt(cipherBi1[1])],
                [charToInt(cipherBi2[0]), charToInt(cipherBi2[1])]]

    invL = inv2by2(leftM)

    if(invL == None):
        return None
    else:
        return multpilyModMatrix(invL, rightM)

def decipherBi(cipherBi, invKey):
    cipherM = [[charToInt(cipherBi[0]), charToInt(cipherBi[1])]]
    plainBiM = multpilyModMatrix(cipherM, invKey)[0]

    return intToChar(plainBiM[0]) + intToChar(plainBiM[1])

def decipherString(cipherText, key):
    plainText = ""

    invKey = inv2by2(key)
    if(invKey == None):
        return None

    for i in range(0, len(cipherText), 2):
        plainText += decipherBi(cipherText[i:i+2], invKey)
    return plainText

#print(computePossibleKey('BR', 'XG', 'TH', 'IN'))

biOrder = ['TH', 'HE', 'IN', 'ER', 'AN', 'RE', 'ON',  'AT', 'EN', 'ND','TI', 'ES', 'OR', 'TE', 'OF', 
            'ED', 'IS', 'IT', 'AL', 'AR', 'ST', 'TO', 'NT', 'NG', 'SE', 'HA', 'AS', 'OU', 'IO', 
            'LE', 'VE', 'CO', 'ME', 'DE', 'HI', 'RI', 'RO', 'IC', 'NE', 'EA', 'RA', 'CE', 'LI', 
            'CH', 'LL', 'BE', 'MA','SI', 'OM', 'UR'] 


cipherText = readCipherText('hill-cipher.txt')

biFreq = calcNgramFreq(cipherText, 2)

sortedFreqTuples = sortFreq(biFreq)

i = 0
while(i < len(biOrder)):
    j = 0
    
    while(j < len(biOrder)):
        if(i != j):
            plainBi1 = biOrder[0]
            cipherBi1 = sortedFreqTuples[i][0]
            plainBi2 = biOrder[1]
            cipherBi2 = sortedFreqTuples[j][0]

            key = computePossibleKey(cipherBi1, cipherBi2, plainBi1, plainBi2)
            print('Trying: ' + cipherBi1 + ' -> ' + plainBi1 + ', ' +  cipherBi2 + ' -> ' + plainBi2)


            if(key != None):
                print2by2(key)

                plainText = decipherString(cipherText, key)
                if(plainText == None):
                    print('Cannot dechipher key has no inverse\n')
                else:
                    print(plainText + '\n')

                    usrInput = input()

                    if(usrInput == 'stop'):
                        exit()
            else:
                print("Invalid Possibility")
        j += 1
    i += 1









