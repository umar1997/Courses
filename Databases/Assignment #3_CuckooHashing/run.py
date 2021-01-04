import math
from prettytable import PrettyTable
from os import system

def hash_1(k,m):
	return k % m
def hash_2(k, m):
	return  int((k/m)%m)
	# return math.floor(m*(k*0.67 % 1))
def printer(dictionary):
	t = PrettyTable(['key', 'value'])
	for key, val in dictionary.items():
   		t.add_row([key, val])
	print(t)
def inserter(key, tableSize):
	global hashTable_1
	global hashTable_2
	global insertBool

	counter = 0
	while True:
		
		
		h1 = hash_1(key,tableSize)
		if hashTable_1.get(h1,False) == False:
			hashTable_1[h1] = key
			counter = 0
			break
		else:
			swap = hashTable_1[h1]
			hashTable_1[h1] = key
			key = swap
			counter+=1
		h2 = hash_2(key,tableSize)
		if hashTable_2.get(h2,False) == False:
			hashTable_2[h2] = key
			counter = 0
			break
		else:
			swap = hashTable_2[h2]
			hashTable_2[h2] = key
			key = swap
			counter+=1

		if counter >= tableSize:
			insertBool = True
			break

def searcher(value):
	global hashTable_1
	global hashTable_2

	try:
		x = hashTable_1[hash_1(int(value),tSize)]
		return (1,hash_1(int(value)))
	except:
		try:
			x = hashTable_2[hash_2(int(value),tSize)]
			return (2,hash_2(int(value)))
		except:
			print('No Such Element Exists')

hashTable_1 = {}
hashTable_2 = {}
tSize = 11
insertBool = False

while True:
	system('cls')
	print( 'CUCKOO HASHING\n')
	print('1. Search')
	print('2. Insert')
	print('3. Delete')
	print('4. Print Tables')
	print('5. Exit')
	z = input('Select(1-5): ')
	if z == '1': # SEARCH
		search_key = input('Enter Search Element: ')
		x = searcher(search_key)
		if x == None:
			print('There is no such Element')
		elif x[0] == 1:
			print(search_key, 'is in Hash Table 1, Key', x[1])
		elif x[0] == 2:
			print(search_key, 'is in Hash Table 2, Key', x[1])
	elif z == '2': # INSERT
		keys = input('Enter key(s) you wish to insert: ')
		keys = keys.split(',')
		for i in keys:
			print(i)
			inserter(int(i),int(tSize))
			if insertBool:
				keyList = []
				for idx, key in enumerate(hashTable_1):
					keyList.append(hashTable_1[key])
				for idx, key in enumerate(hashTable_2):
					keyList.append(hashTable_2[key])
				keyList.append(int(i))
				hashTable_1.clear()
				hashTable_2.clear()
				tSize *= 2
				for key in keyList:
					inserter(int(key),int(tSize))
				insertBool = False
	elif z == '3': # DELETE
		deleteKey = input('Enter Element To Delete: ')
		hashTable_1.pop(hash_1(int(deleteKey),tSize),None)
		hashTable_2.pop(hash_2(int(deleteKey),tSize),None)
	elif z == '4': # PRINT
		print('Hash Table 1')
		printer(hashTable_1)
		print('Hash Table 2')
		printer(hashTable_2)
	elif z == '5': # EXIT
		exit()	
	input('')