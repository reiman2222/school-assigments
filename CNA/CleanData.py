#Jack Edwards

#This program parses .bib files and constructs a co-authorship network. 
#The network is written to a file is .csv format for easy import into neo4j.

import re
import sys
import paper
import author


#cleans affiliations of all papers in paperList
def cleanAffiliationsOfPaperList(paperList):
	for p in paperList:
		p.cleanAffiliations()

#opens .bib file called filename and returns its contnets as a ist of entries.
def parseBibFileToList(filename):
	f = open(filename, 'r')
	data = f.read()

	entries = re.split('@', data)
	f.close()
	return entries

#bibListToPaperList(bibList) takes a list of .bib entries called bibList
#and returns a list of Papers.
def bibListToPaperList(bibList):
	plist = []
	i = 0
	while(i < len(entries)):
		p = paper.Paper.buildPaper(entries[i])
		#p.printPaper()
		plist.append(p)
		i = i + 1
	return plist

#removeNondeterminablePapers(paperList) returns a new list of papers containg only papers which are usable.
#paperList is the list of papers. 
def removeNonuseablePapers(paperList):
	determinablePList = []
	for p in paperList:
		if(p.isUseable()):
			determinablePList.append(p)

	return determinablePList

#writes all affiliations from pList to a text file named 'affiliations.txt'
def affiliationsToFile(pList):
	f = open('affiliations.txt', 'w+')

	for p in pList:
		affiliation = p.affiliation
		for A in affiliation:
			f.write(A + '\n')

	f.close()

def affiliationsToFileClean(pList):
	f = open('affiliationsClean.txt', 'w+')

	for p in pList:
		affiliation = p.affiliation
		for A in affiliation:
			cleanA = cleanAffiliation(A)
			f.write(cleanA + '\n')

	f.close()

#updataAuthorTable(paperList, authorTable) takes a list of Papers called paperList and
#adds the author and co author relationships to the author table.
def updateAuthorTable(paperList, authorTable):
	for p in paperList:
		for authAndAffl in p.getAuthorAndAffiliationList():
			auth = authAndAffl[0]
			afflOfAuth = authAndAffl[1]
			if auth in authorTable:
				authorsOfSameName = authorTable[auth]

				authorWasInTable = False
				for A in authorsOfSameName:
					if((auth == A.name) and (afflOfAuth == A.affiliation)):
						#A.printAuthor()
						A.expandCoAuthorList(p)
						authorWasInTable = True
						#A.printAuthor()
						break
				if(not authorWasInTable):
					newAuthor = author.Author.createAuthor(p, auth, afflOfAuth)
					authorTable[auth].insert(0, newAuthor)

			else:
				newAuthor = author.Author.createAuthor(p, auth, afflOfAuth)

				authorTable[auth] = []
				authorTable[auth].insert(0, newAuthor)
		

#hashTableValuesToList(table) converts hash table  to list of its values
#and returns the list.
def hashTableValuesToList(table):
	authTableValues = table.values()
	authorList = []
	for L in authTableValues:
		authorList.extend(L)
	return authorList


#authorListToFile(authorList, filename) writes the list of Authors authorList
#to a file called filename in the following format:
'''
@author
author1Name
author1Affiliation
<begin_coauthors>
coAuthor1Name; coAuthor1Affiliation; #timesCoauthoredTogether
coAuthor2Name; coAuthor2Affiliation; #timesCoauthoredTogether
.
.
coAuthorNName; coAuthorNAffiliation; #timesCoauthoredTogether
<end_coauthors>

@author
author2Name
author2Affiliation
<begin_coauthors>
coAuthor1Name; coAuthor1Affiliation; #timesCoauthoredTogether
coAuthor2Name; coAuthor2Affiliation; #timesCoauthoredTogether
.
.
coAuthorNName; coAuthorNAffiliation; #timesCoauthoredTogether
<end_coauthors>

.
.
.
'''	
def authorListToFile(authorList, filename):
	f = open(filename, 'w+')

	for author in authorList:
		f.write('@author\n')
		f.write(author.name + '\n')
		f.write(author.affiliation + '\n')
		f.write('<begin_coauthors>\n')
		for coAuth in author.coAuthors:
			#       coauthor name      coauthor affiliation
			f.write(coAuth[0] + '; ' + coAuth[1] + '; ' + str(coAuth[2]) + '\n')
		f.write('<end_coauthors>\n')
		f.write('.\n')

	f.close()


def authorListToCSVNodes(authorList, filename):
	f = open(filename, 'w+')

	f.write('authorId:ID,name,affiliation,:LABEL\n')
	#i = 0
	for A in authorList:
		f.write( '"' + A.getID() + '","' + A.name + '","' + A.affiliation + '",' + 'Author' + '\n')
		#i += 1

	f.close()
	print('File written: ' + filename)


def authorListToCSVRelationships(authorList, filename):
	f = open(filename, 'w+')

	f.write(':START_ID,weight:int,:END_ID,:TYPE\n')
	for A in authorList:
		for coA in A.coAuthors:
			f.write('"' + coA[0]+coA[1]  + '",' + str(coA[2]) + ',"' + A.getID() + '",' + 'COAUTHORED_WITH' + '\n')

	f.close()
	print('File written: ' + filename)

def authorListToAdjacencyListCSV(authorList, filename):
	f = open(filename, 'w+')

	for A in authorList:
		for coA in A.coAuthors:
			f.write('"' + coA[0]+coA[1] + '","' + A.getID() + '"\n')

	f.close()

def authorListToInstitutionNodes(authorList, filename):
	institutions = set()

	for A in authorList:
		 institutions.add(A.affiliation)

	institutionsL = list(institutions)

	f = open(filename, 'w+')

	f.write('affiliation:ID,:LABEL\n')
	#i = 0
	for I in institutionsL:
		f.write( '"' + I + '","'  + 'Institution' + '"\n')
		#i += 1

	f.close()
	print('File written: ' + filename)


def authorListToInstitutionRelationships(authorList, filename):
	institutions = {} #is a hash table on institution names that points to list of tuples of the form (inst 1, inst 2, weight)

	for A in authorList:
		for coA in A.coAuthors:
			ID = A.affiliation + ';'+ coA[1]
			if ID in institutions:
				inList = False
				i = 0

				for tup in institutions[ID]:	
					if(tup[0] == A.affiliation and tup[1] == coA[1]):
						L = institutions[ID]

						del L[i]
						L.insert(i, (tup[0], tup[1], tup[2] + 1))

						inList = True
						break

					i += 1
				if(not inList):
					institutions[ID].append((A.affiliation, coA[1], 1))
			else:
				institutions[ID] = []
				institutions[ID].append((A.affiliation, coA[1], 1))


	institutionsL = hashTableValuesToList(institutions)

	f = open(filename, 'w+')

	f.write(':START_ID,weight:int,:END_ID,:TYPE\n')
	for I in institutionsL:
		f.write('"' + I[0]  + '",' + str(I[2]) + ',"' + I[1] + '",' + 'COAUTHORED_WITH' + '\n')

	f.close()
	print('File written: ' + filename)


def authorListToInstitutionRelationshipsUnweighted(authorList, filename):
	institutions = {} #is a hash table on institution names that points to list of tuples of the form (inst 1, inst 2, weight)

	for A in authorList:
		for coA in A.coAuthors:
			ID = A.affiliation + ';'+ coA[1]
			if ID in institutions:
				institutions[ID].append((A.affiliation, coA[1]))

			else:
				institutions[ID] = []
				institutions[ID].append((A.affiliation, coA[1]))


	institutionsL = hashTableValuesToList(institutions)

	f = open(filename, 'w+')

	f.write(':START_ID,:END_ID,:TYPE\n')
	for I in institutionsL:
		f.write('"' + I[0]  + '","' + I[1] + '",' + 'COAUTHORED_WITH' + '\n')

	f.close()
	print('File written: ' + filename)



##################################################
#                    MAIN                        #
##################################################

args = sys.argv
numArgs = len(sys.argv)

#ensure that a file name is given
if(numArgs < 2):
	print('ERROR: no filenames given')
	sys.exit(2)

authorTable = {}


for filename in args[1:numArgs]:

	#convert .bib file to list of bib entries
	entries = parseBibFileToList(filename)
	print('Processing file: ' + filename)

	#remove first since it is always an empty string
	del entries[0]

	#convert list of entries to list of papers
	pList = bibListToPaperList(entries)
	entries = []

	#remove papers where atleast 1 feild is undertmined
	pList = removeNonuseablePapers(pList)

	#attempt to clean author afiliation for all paper in pList
	cleanAffiliationsOfPaperList(pList)

	#convert list of papers to list of authors
	updateAuthorTable(pList, authorTable)


authorList = hashTableValuesToList(authorTable)
print('Number of authors: ' + str(len(authorList)) + '\n')



#authorListToFile(authorList, 'DataOut/coauthors.txt')

authorListToCSVNodes(authorList, 'DataOut/authors-nodes.csv')

authorListToCSVRelationships(authorList, 'DataOut/authors-relationships.csv')

#authorListToAdjacencyListCSV(authorList, 'DataOut/adjacencylist.csv')

authorListToInstitutionNodes(authorList, 'DataOut/institution-nodes.csv')

#authorListToInstitutionRelationships(authorList, 'DataOut/instRelationships.csv')
authorListToInstitutionRelationshipsUnweighted(authorList, 'DataOut/institution-relationships.csv')



