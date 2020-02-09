import re

class Paper:
	#title: title of paper as string
	#authors: list of author names as strings
	#affiliation: list of author affiliations as strings

	def __init__(self):
		self.title = ''
		self.authors = []
		self.affiliation = []


	#buildPaper(entry) takes a .bib entry as a string and returns a Paper
	@staticmethod
	def buildPaper(entry):
		p = Paper()

		splitE = Paper.splitEntry(entry)

		p.title = p.retrieveTitle(splitE).strip()

		p.authors = re.split(' and ', p.retrieveAuthors(splitE))
		p.authors = Paper.stripWhitespace(p.authors)

		p.affiliation = p.retrieveAffiliations(splitE).split(';')
		p.affiliation = Paper.stripWhitespace(p.affiliation)

		return p

	#splits a .bib entry on '},' to break it into feilds
	@staticmethod
	def splitEntry(entry):
		splitE = re.split('},', entry)
		return splitE

	#stripWhitespace(L) takes a list of strings L and returns a new 
	#list of strings with trailing white space removed.
	@staticmethod
	def stripWhitespace(L):
		stripedL = []
		i = 0
		while(i < len(L)):
			stripedL.insert(i, L[i].strip())
			i = i + 1
		return stripedL

	#returns title of paper from .bib entry split on '},'
	def retrieveTitle(self, splitE):
		for e in splitE:
			if 'title=' in e:
				a = e.split('{')
				return a[len(a) - 1]

		return 'NO TITLE'

	#returns authors of paper from .bib entry split on '},'
	def retrieveAuthors(self, splitE):
		for e in splitE:
			if 'author=' in e:
				a = e.split('{')
				return a[len(a) - 1]
		return 'NO AUTHOR'

	#returns author affiliation of paper from .bib entry split on '},'
	def retrieveAffiliations(self, splitE):
		for e in splitE:
			if 'affiliation=' in e:
				a = e.split('{')
				return a[len(a) - 1]

		return 'NO AFFILIATION'


	#getAuthorAffiliation(self, authorName) returns the affiliation of the author
	#authorName in paper self. 
	#
	#REQUIRES canDeterminAffiliation() to return TRUE.
	def getAuthorAffiliation(self, authorName):
		numAuthors = len(self.authors)
		numAffiliations = len(self.affiliation)

		if(numAffiliations == 1):
			return self.affiliation[0]
		else:
			return self.affiliation[self.authors.index(authorName)]

	#returns a list of tuples of the form (authorName, authorAffiliation) 
	#obtained from paper self.
	#
	#REQUIRES canDetermineAffiliation() to be true.
	def getAuthorAndAffiliationList(self):
		authAfflList = []
		if(len(self.affiliation) == 1):
			affl = self.affiliation[0]
			for auth in self.authors:
				authAfflList.append((auth, affl))

		else:
			i = 0
			while(i < len(self.authors)):
				authAfflList.append((self.authors[i], self.affiliation[i]))
				i += 1

		return authAfflList

	#returns true if the afiliation all author of the paper self can be determined 
	def canDetermineAffiliation(self):
		numAuthors = len(self.authors)
		numAffiliations = len(self.affiliation)

		if(numAuthors == numAffiliations):
			return True
		elif(numAffiliations == 1):
			return True
		else:
			return False

	#returns true if all fields of the paper are defined and if author affiliations
	#can be determined.
	def isUseable(self):
		if 'NO TITLE' in self.title:
			return False
		else:
			for Auth in self.authors:
				if 'NO AUTHOR' in Auth:
					return False

			for Affl in self.affiliation:
				if 'NO AFFILIATION' in Affl:
					return False

			if(self.canDetermineAffiliation()):
				return True #this paper is useable
			else:
				return False 


	#atempts to clean affiliation. returns the cleaned affiliation or 
	#the affiliation unchanged if nothing can be done.
	@staticmethod
	def cleanAffiliation(affiliation):
		cleanAfflLower = affiliation.lower().split(',')
		cleanAffl = affiliation.split(',')

		matched = False

		i = 0
		while(i < len(cleanAfflLower)):
			if(cleanAfflLower[i] == ''):
				i = i #do nothing
			elif('university.' in cleanAfflLower[i]):
				clean = cleanAffl[i].strip()
				clean = clean.replace('University.', 'University')
				return clean
			elif('university' in cleanAfflLower[i]):
				return cleanAffl[i].strip()
			elif('unv.' in cleanAfflLower[i]):
				clean = cleanAffl[i].strip()
				clean = clean.replace('Unv.', 'University')
				return clean
			elif('univ.' in cleanAfflLower[i]):
				clean = cleanAffl[i].strip()
				clean = clean.replace('Univ.', 'University')
				return clean
			elif('univ' in cleanAfflLower[i]):
				clean = cleanAffl[i].strip()
				clean = clean.replace('Univ', 'University')
				return clean

			elif('institute' in cleanAfflLower[i]):
				return cleanAffl[i].strip()
			i = i + 1

		i = 0
		while(i < len(cleanAfflLower)):
			if(cleanAfflLower[i] == ''):
				i = i #do nothing
			elif('college' in cleanAfflLower[i]):
				return cleanAffl[i].strip()
			i = i + 1
		
		return affiliation #affiliation could not be simplified

	#replaces author affiliation field with cleaned version
	def cleanAffiliations(self):
		i = 0
		while(i < len(self.affiliation)):
			self.affiliation[i] = Paper.cleanAffiliation(self.affiliation[i])
			i = i + 1

	#returns coAuthor list for author named authorName in paper self.
	#REQUIRES canDeterminAffiliation to be TRUE.
	def buildCoAuthorList(self, authorName):
		numAuthors = len(self.authors)
		numAffiliations = len(self.affiliation)
		authorAffiliation = self.getAuthorAffiliation(authorName) #affiliation of author named authorName

		coAuthorList = []
		
		if(numAffiliations == 1):
			affl = self.affiliation[0]
			for auth in self.authors:
				if(auth != authorName): #prevent adding author under consideration as co-author with themselves
					coAuthorList.append((auth, affl, 1))

		else: #numAffiliation is equal to numAuthors
			i = 0
			while(i < numAuthors):
				#prevent having author underconsideration from being coauthor with themself
				if((self.authors[i] != authorName) and (self.affiliation[i] != authorAffiliation)):
					coAuthorList.append((self.authors[i], self.affiliation[i], 1))
				i = i + 1
		
		return coAuthorList

	#prints a paper
	def printPaper(self):
		print(self.title)
		print(self.authors)
		print(self.affiliation)

################## END CLASS ##########################
