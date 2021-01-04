import socket
from _thread import *
import threading 
import hashlib
import time
import sys
import pickle
import os

IP_ADDRESS = "127.0.0.1"
M = 5
YourNode = None

class Node:
	def __init__(self, port):
		self.key = hash_func(port)
		self.port = port
		self.next = port
		self.prev = port
		self.ss = port
		self.leave = False
		self.fingerTable = []
		self.files = []

def hash_func(value):
	return value%8
################################################################## <Functions in Update Thread> #################################################

def updateSecSuccessor(port):
	global YourNode
	successorPort = YourNode.next
	try:
		nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		nextSoc.connect((IP_ADDRESS, successorPort))
		updatessmsg = ["UPDATES_SS", "", ""]
		nextSoc.send(pickle.dumps(updatessmsg))
		YourNode.ss = pickle.loads(nextSoc.recv(1024))
		nextSoc.close()
	except:
		pass
		# print("{-- Successor not available --}")

def pingSuccessor(port, successorPort):
	global YourNode
	offline = False
	count = 0
	if (port != successorPort):
		while True:
			try:
				nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
				nextSoc.connect((IP_ADDRESS, successorPort))
				pingmsg = ["PING", "" , ""]
				nextSoc.send(pickle.dumps(pingmsg))
				alive = pickle.loads(nextSoc.recv(1024))
				if alive == "ALIVE":
					break
			except:
				count+=1
				if count == 3:
					offline = True
					break
		if offline == True:
			YourNode.next = YourNode.ss
		nextSoc.close()


def knowPredecessor(port):
	global YourNode
	theNext = YourNode.next
	if YourNode.port==YourNode.ss and YourNode.port==YourNode.next:
		YourNode.prev = YourNode.port
	elif YourNode.port == YourNode.ss and YourNode!= YourNode.next:
		YourNode.prev = YourNode.next
	else:
		try:
			while True:
				nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
				nextSoc.connect((IP_ADDRESS, theNext ))
				predMsg = ["PREDECESSOR", port , ""]
				nextSoc.send(pickle.dumps(predMsg))
				pred = pickle.loads(nextSoc.recv(1024))
				if pred[0] != "Not_Predecessor":
					YourNode.prev = pred[1]
					break
				theNext = pred[1]
				nextSoc.close()
		except:
			pass


################################################################## <FINGER TABLE> ########################################################################
def viewFingerTable(port):
	global YourNode
	YourNode.fingerTable = []
	ftPort1 = port + (2**0)
	ftPort2 = port + (2**1)
	ftPort3 = port + (2**2)
	if port == YourNode.next and port == YourNode.prev and port == YourNode.ss: # For 1 node in the chord
		YourNode.fingerTable.append([ftPort1,port, hash_func(port)])
		YourNode.fingerTable.append([ftPort2,port, hash_func(port)])
		YourNode.fingerTable.append([ftPort3,port, hash_func(port)])
	elif port == YourNode.ss and YourNode.next==YourNode.prev and YourNode.next!=port:# For 2 nodes in the chord
 		YourNode.fingerTable.append([ftPort1,YourNode.next, hash_func(YourNode.next)])
 		YourNode.fingerTable.append([ftPort2,port, hash_func(port)])
 		YourNode.fingerTable.append([ftPort3,port, hash_func(port)])
	else:
		ftSucc1 = getFTSucc(ftPort1)
		ftSucc2 = getFTSucc(ftPort2)
		ftSucc3 = getFTSucc(ftPort3)
		YourNode.fingerTable.append([ftPort1,ftSucc1, hash_func(ftSucc1)])
		YourNode.fingerTable.append([ftPort2,ftSucc2, hash_func(ftSucc2)])
		YourNode.fingerTable.append([ftPort3,ftSucc3, hash_func(ftSucc3)])	
def getFTSucc(ftPort):
	CurrPort = YourNode.prev
	successorPort = YourNode.next
	while True:
		try: 
			if (ftPort > CurrPort and ftPort <= successorPort) or (CurrPort>successorPort and ftPort>=CurrPort) or (CurrPort>successorPort and ftPort<=successorPort):
				break
			nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			nextSoc.connect((IP_ADDRESS, successorPort))
			fwdmsg = ["FWD", CurrPort, ftPort]
			nextSoc.send(pickle.dumps(fwdmsg))
			retmsg = pickle.loads(nextSoc.recv(1024))
			CurrPort = retmsg[0]
			successorPort = retmsg[1]
			nextSoc.close()
		except:
			continue
	return successorPort

def getSuccWithFT(knownPort, JoinersNode, successorPort): # Join the node with Finger Table Approach
	CurrPort = knownPort
	pos = 2
	if JoinersNode.port < YourNode.fingerTable[pos][1]:
		successorPort = YourNode.fingerTable[pos][1]
	elif JoinersNode.port > YourNode.fingerTable[pos][1] and YourNode.fingerTable[pos][1] < YourNode.fingerTable[pos-1][1]:
		successorPort = YourNode.fingerTable[pos-1][1]
	elif JoinersNode.port > YourNode.fingerTable[pos][1] and YourNode.fingerTable[pos][1] < YourNode.fingerTable[pos-2][1]:
		successorPort = YourNode.fingerTable[pos-2][1]
	elif JoinersNode.port > YourNode.fingerTable[pos][1] and YourNode.fingerTable[pos][1] > YourNode.fingerTable[pos-2][1] and YourNode.fingerTable[pos][1] < YourNode.fingerTable[pos-2][1]:
		successorPort = YourNode.fingerTable[pos-2][1]
	while True: 
		if (JoinersNode.port > CurrPort and JoinersNode.port < successorPort) or (CurrPort>successorPort and JoinersNode.port>CurrPort) or (CurrPort>successorPort and JoinersNode.port<successorPort):
			break
		nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		nextSoc.connect((IP_ADDRESS, successorPort))
		fwdmsg = ["FINGER_TABLE_FWD", knownPort, JoinersNode]
		nextSoc.send(pickle.dumps(fwdmsg))
		retmsg = pickle.loads(nextSoc.recv(1024))
		CurrPort = retmsg[0]
		successorPort = retmsg[1]
		nextSoc.close()
	return successorPort, CurrPort

def getSuccFTPossible(knownPort, JoinersNode, successorPort):
	try:
		CurrPort = knownPort
		pos = 2
		if JoinersNode.port < YourNode.fingerTable[pos][1]:
			successorPort = YourNode.fingerTable[pos][1]
		elif JoinersNode.port > YourNode.fingerTable[pos][1] and YourNode.fingerTable[pos][1] < YourNode.fingerTable[pos-1][1]:
			successorPort = YourNode.fingerTable[pos-1][1]
		elif JoinersNode.port > YourNode.fingerTable[pos][1] and YourNode.fingerTable[pos][1] < YourNode.fingerTable[pos-2][1]:
			successorPort = YourNode.fingerTable[pos-2][1]
		elif JoinersNode.port > YourNode.fingerTable[pos][1] and YourNode.fingerTable[pos][1] > YourNode.fingerTable[pos-2][1] and YourNode.fingerTable[pos][1] < YourNode.fingerTable[pos-2][1]:
			successorPort = YourNode.fingerTable[pos-2][1]
		return True
	except:
		return False
################################################################## <THREADS> ########################################################################
def updateThread(port):
	global YourNode

	while YourNode.leave == False:
		time.sleep(0.2)
		updateSecSuccessor(port)
		pingSuccessor(YourNode.port, YourNode.next)
		knowPredecessor(YourNode.port)

def Listen(port, knownPort): # Think of this as the part that chooses what it can do after joining
	global YourNode
	print("I am Port ", port)
	print("I am Key", YourNode.key)

	if knownPort != 0:
		client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		client.connect((IP_ADDRESS,knownPort)) # This is the port you are connecting to
		if getSuccFTPossible(knownPort, YourNode, YourNode.next):
			message = ["JOIN_FINGER_TABLE", knownPort, YourNode] # Join me to my successor
		message = ["JOIN", knownPort, YourNode] # Join me to my successor
		client.send(pickle.dumps(message))
		JoinersNode = pickle.loads(client.recv(1024))
		YourNode = JoinersNode
		client.close()
	while True:
		print("\n")
		print("1 Print\n2 Upload File\n3 Download File\n4 Show List of Files\n5 View Finger Table\n6 Leave\n0 Leave Unxpectedly\n")
		print("Enter: \n")
		query = int(input(""))
		if query == 0:
			os._exit(0)
		elif query == 1:
			print("Your Port -- Successor Port -- Predesessor Port -- 2nd Successor")
			print(YourNode.port, YourNode.next, YourNode.prev, YourNode.ss)
		elif query == 2:
			fileKey, fname = ReadFile()
			if fileKey!=False and fname != False:
				successorPort  = getUploadSuccessor(YourNode, fileKey, YourNode.next)
				sendUploadedFile(successorPort, fname, fileKey)
		elif query == 3:
			fname, Key = requestFile()
			successorPort = getDownloadSuccessor(YourNode, Key, YourNode.next)
			DownloadFile(fname, YourNode, successorPort)
		elif query == 4:
			for each_file in YourNode.files:
				print(each_file)
		elif query == 5:
			viewFingerTable(YourNode.port)
			print("FINGER TABLE")
			print("Index--Port--Successor--Key\n")
			for i in range(3):
					print(i+1,". ", YourNode.fingerTable[i][0], " ", YourNode.fingerTable[i][1], " ", YourNode.fingerTable[i][2], " \n")
		elif query == 6:
			leaveTheChord()
			YourNode.files = []
			YourNode.leave = True
			print("{-- I AM LEAVING... --}")
			os._exit(0)

def Reply(port, machine): # Think of this as the part that will cater to the request of all the other machines
# machine is the machine that wants to connect with you
	global YourNode
	while True:
		try:
			message = pickle.loads(machine.recv(1024))
			if message[0] == "JOIN":
				JoinersNode = message[2]
				knownPort = message[1]
				if port == knownPort: # If you are the knownPort
					if YourNode.next == port and YourNode.prev == port and YourNode.port == knownPort: # You are the only node in the chord and someone wants to join
						JoinersNode.next = port
						JoinersNode.prev = port
						YourNode.next = JoinersNode.port
						YourNode.prev = JoinersNode.port
					else:
						succPort, prevPort =  getSuccessor(knownPort, JoinersNode, YourNode.next) # Finds you the Successor and Predecessor
						JoinersNode.next = succPort
						JoinersNode.prev = prevPort
						if succPort == port: # If you are the successor port
							tellAffectedPort(YourNode.prev, JoinersNode.port, "", "IamPrev")
							YourNode.prev = JoinersNode.port
						if prevPort == port: # If you are the predecessor port
							tellAffectedPort(YourNode.next, JoinersNode.port, "", "IamSucc")
							YourNode.next = JoinersNode.port
						if JoinersNode.port > prevPort and JoinersNode.port < succPort:
							tellAffectedPort( succPort, JoinersNode.port,"succ_1to2", "IamBtw") # If between ascending nodes
							tellAffectedPort( prevPort, JoinersNode.port, "prev_2to1", "IamBtw")
						if prevPort>succPort and JoinersNode.port>prevPort:
							tellAffectedPort( succPort, JoinersNode.port,"succ_4to0", "IamBtw") # if between the highest and the lowest node
							tellAffectedPort( prevPort, JoinersNode.port, "prev_0to4", "IamBtw")
					machine.send(pickle.dumps(JoinersNode)) # Send updated JoinerNode.next/prev back to the JoinerNode

			if message[0] == "JOIN_FINGER_TABLE":
				JoinersNode = message[2]
				knownPort = message[1]
				if port == knownPort: # If you are the knownPort
					if YourNode.next == port and YourNode.prev == port and YourNode.port == knownPort: # You are the only node in the chord and someone wants to join
						JoinersNode.next = port
						JoinersNode.prev = port
						YourNode.next = JoinersNode.port
						YourNode.prev = JoinersNode.port
					else:
						succPort, prevPort =  getSuccWithFT(knownPort, JoinersNode, YourNode.next) # Finds you the Successor and Predecessor
						JoinersNode.next = succPort
						JoinersNode.prev = prevPort
						if succPort == port: # If you are the successor port
							tellAffectedPort(YourNode.prev, JoinersNode.port, "", "IamPrev")
							YourNode.prev = JoinersNode.port
						if prevPort == port: # If you are the predecessor port
							tellAffectedPort(YourNode.next, JoinersNode.port, "", "IamSucc")
							YourNode.next = JoinersNode.port
						if JoinersNode.port > prevPort and JoinersNode.port < succPort:
							tellAffectedPort( succPort, JoinersNode.port,"succ_1to2", "IamBtw") # If between ascending nodes
							tellAffectedPort( prevPort, JoinersNode.port, "prev_2to1", "IamBtw")
						if prevPort>succPort and JoinersNode.port>prevPort:
							tellAffectedPort( succPort, JoinersNode.port,"succ_4to0", "IamBtw") # if between the highest and the lowest node
							tellAffectedPort( prevPort, JoinersNode.port, "prev_0to4", "IamBtw")
					machine.send(pickle.dumps(JoinersNode)) # Send updated JoinerNode.next/prev back to the JoinerNode

			elif message[0] == "FINGER_TABLE_FWD":
				fwdmsg = [YourNode.port,YourNode.next]
				##print("{-- I AM FWD GUY FOR FT", fwdmsg, " --}")	
				machine.send(pickle.dumps(fwdmsg))


			elif message[0] == "PREDECESSOR":
				port = message[1]
				if port == YourNode.next:
					machine.send(pickle.dumps(["Yes_Predecessor",YourNode.port]))
				else:
					machine.send(pickle.dumps(["Not_Predecessor",YourNode.next]))


			elif message[0] == "FWD": # This is the reply to all the Forwarding requests for e.g (Trying to find successor)
				fwdmsg = [YourNode.port,YourNode.next]
				##print("{-- I AM FWD GUY", fwdmsg, " --}")	
				machine.send(pickle.dumps(fwdmsg))

			elif message[0] == "AFFECTED": # Makes a socket with the directly Affected nodes and updates what need to be updated.
				now = message[1]
				if message[2] == "IamPrev":
					YourNode.next = now
				elif message[2] == "IamSucc":
					YourNode.prev = now
				elif message[2] == "succ_1to2":
					YourNode.prev = now
				elif message[2] == "prev_2to1":
					YourNode.next = now
				elif message[2] == "succ_4to0":
					YourNode.prev = now
				elif message[2] == "prev_0to4":
					YourNode.next = now

			elif message[0] == "UPDATES_SS":
				updatessmsg = YourNode.next
				machine.send(pickle.dumps(updatessmsg))

			elif message[0] == "UPLOAD":
				if message[1] == "First":
					fname = message[2]
					file = open(fname ,'wb')
					recvSize = 0
					
					while True:
						machine.send(pickle.dumps("ACK"))
						message = pickle.loads(machine.recv(1024))
						size = message[2]
						toWrite = message[1]
						file.write(toWrite)
						recvSize += len(toWrite)

						if recvSize >= size:
							break
					file.close()
					print("{-- ",fname," has been recieved. --}")
					YourNode.files.append(fname)

			elif message[0] == "DOWNLOAD":
				fname = message[1]
				try:
					file = open(fname, 'rb')
					size = str(os.path.getsize(fname))
					machine.send(pickle.dumps(size))
					size = int(size)
					sentSize = 0
					while sentSize < size:
						ack = pickle.loads(machine.recv(1024))
						toSend = file.read(1024)
						machine.send(pickle.dumps(toSend))
						sentSize += len(toSend)
					file.close()
				except OSError:
					exists = False
					machine.send(pickle.dumps(exists))

			elif message[0] == "PING":
				alive = "ALIVE"
				machine.send(pickle.dumps(alive))

			elif message[0] == "GIVE_SUCCESSOR":
				if message[1] == "First":
					fname = message[2]
					file = open(fname ,'wb')
					recvSize = 0
					while True:
						machine.send(pickle.dumps("ACK"))
						message = pickle.loads(machine.recv(1024))
						size = message[2]
						toWrite = message[1]
						file.write(toWrite)
						recvSize += len(toWrite)

						if recvSize >= size:
							break
					YourNode.files.append(fname)
					file.close() # After downloading give successor the files for failure resilience

			elif message[0] == "LEAVE_WITH_SUCCESSOR":
				if message[1] == "First":
					fname = message[2]
					file = open(fname ,'wb')
					recvSize = 0
					while True:
						machine.send(pickle.dumps("ACK"))
						message = pickle.loads(machine.recv(1024))
						size = message[2]
						toWrite = message[1]
						file.write(toWrite)
						recvSize += len(toWrite)

						if recvSize >= size:
							break
					file.close()
					YourNode.flies.append(fname)

			elif message[0] == "LEAVE_AFFECTED":
				if message[1] == "Successor": # If you are the successor then update your predecessor
					YourNode.prev = message[2]
					print("{-- Your new Predecessor has been updated. --}")
				elif message[1] == "Predecessor": # If you are the predecessor then update your successor
					YourNode.next = message[2]
					print("{-- Your new Successor has been updated. --}")
			break
		except:
			continue

################################################################## <LEAVE> #################################################################################
def leaveTheChord():
	pred = YourNode.prev
	succ = YourNode.next

	for each_file in YourNode.files:
		leaveWithSuccessor(succ, each_file)
	LeaveAffected(YourNode.next, "Successor", YourNode.prev)
	LeaveAffected(YourNode.prev, "Predecessor", YourNode.next)

def leaveWithSuccessor(successorPort, fname):
	nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	nextSoc.connect((IP_ADDRESS, successorPort))
	size = str(os.path.getsize(fname))
	file = open(fname, 'rb')
	downloadmsg2 = ["LEAVE_WITH_SUCCESSOR", "First", fname]
	nextSoc.send(pickle.dumps(downloadmsg2))
	size = int(size)
	sentSize = 0
	while sentSize < size:
		ack = pickle.loads(nextSoc.recv(1024))
		toSend = file.read(1024)
		uploadmsg = ["LEAVE_WITH_SUCCESSOR", toSend, size]
		nextSoc.send(pickle.dumps(uploadmsg))
		sentSize += len(toSend)
	file.close()
	nextSoc.close()
	print("{-- File transferred to Successor On Leaving... --}") # Sends file to the successor

def LeaveAffected(newport, portpos, toConnect):
	nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	nextSoc.connect((IP_ADDRESS, newport))
	leavemsg = ["LEAVE_AFFECTED", portpos, toConnect]
	nextSoc.send(pickle.dumps(leavemsg))
	nextSoc.close()

################################################################## <JOIN> #################################################################################

def tellAffectedPort(last, now, code, change): # Telling the an existing node that its previous or next might have changed 
# because of the addition of a new node in the chord
	if change != "IamBtw":
		nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		nextSoc.connect((IP_ADDRESS, last))
		changemsg = ["AFFECTED", now, change]
		nextSoc.send(pickle.dumps(changemsg))
		nextSoc.close()
	else:
		nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		nextSoc.connect((IP_ADDRESS, last))
		changemsg = ["AFFECTED", now, code]
		nextSoc.send(pickle.dumps(changemsg))
		nextSoc.close()
		nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		nextSoc.connect((IP_ADDRESS, last))
		changemsg = ["AFFECTED", now, code]
		nextSoc.send(pickle.dumps(changemsg))
		nextSoc.close()

def getSuccessor(knownPort, JoinersNode, successorPort): # Finds the successor of the Joiners Node and returns it to the known node.
	CurrPort = knownPort
	while True: 
		if (JoinersNode.port > CurrPort and JoinersNode.port < successorPort) or (CurrPort>successorPort and JoinersNode.port>CurrPort) or (CurrPort>successorPort and JoinersNode.port<successorPort):
			break
		nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		nextSoc.connect((IP_ADDRESS, successorPort))
		fwdmsg = ["FWD", knownPort, JoinersNode]
		nextSoc.send(pickle.dumps(fwdmsg))
		retmsg = pickle.loads(nextSoc.recv(1024))
		CurrPort = retmsg[0]
		successorPort = retmsg[1]
		nextSoc.close()
	return successorPort, CurrPort
################################################################## <DOWNLOAD> ##############################################################################
def requestFile():
	file = input("Enter name of file => ")
	fname = ' '.join(format(ord(x), 'b') for x in file)
	fname =  str(fname)
	fname = fname.replace(' ','')
	fileKey = int(fname,2)
	Key = hash_func(fileKey)
	return file, Key

def getDownloadSuccessor(DownloadersNode, fileKey, successorPort): # or (knownPort>successorPort and JoinersNode.port<successorPort)
	CurrPort = DownloadersNode.port
	while True: 
		CurrPortKey = hash_func(CurrPort)
		succPortKey = hash_func(successorPort)
		if (fileKey > CurrPortKey and fileKey <= succPortKey) or (CurrPortKey>succPortKey and fileKey>CurrPortKey) or (CurrPortKey>succPortKey and fileKey<=succPortKey):
			break
		nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		nextSoc.connect((IP_ADDRESS, successorPort))
		fwdmsg = ["FWD", fileKey, DownloadersNode] # Nothing of use is being sent except "FWD"
		nextSoc.send(pickle.dumps(fwdmsg))
		retmsg = pickle.loads(nextSoc.recv(1024))
		CurrPort = retmsg[0]
		successorPort = retmsg[1]
		nextSoc.close()
	return successorPort

def DownloadFile(fname, DownloadersNode, successorPort):
	nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	nextSoc.connect((IP_ADDRESS, successorPort))
	downloadmsg = ["DOWNLOAD", fname, ""] # #rd mein exists aasakta
	nextSoc.send(pickle.dumps(downloadmsg))
	exists = pickle.loads(nextSoc.recv(1024))
	size = int(exists)
	if exists != False:
		file = open(fname ,'wb')
		recvSize = 0
		while True:
			nextSoc.send(pickle.dumps("ACK"))
			toWrite  = pickle.loads(nextSoc.recv(1024))
			file.write(toWrite)
			recvSize += len(toWrite)
			if recvSize >= size:
				break
		file.close()
		print("{-- ",fname," has been downloaded. --}")
		YourNode.files.append(fname)
		giveDownloadedTOSucc(YourNode.next,fname)
	else:
		print("{-- ",fname, " does not exist. --}")
	nextSoc.close()
	return exists

def giveDownloadedTOSucc(successorPort, fname):
	nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	nextSoc.connect((IP_ADDRESS, successorPort))
	size = str(os.path.getsize(fname))
	file = open(fname, 'rb')
	downloadmsg2 = ["GIVE_SUCCESSOR", "First", fname]
	nextSoc.send(pickle.dumps(downloadmsg2))
	size = int(size)
	sentSize = 0
	while sentSize < size:
		ack = pickle.loads(nextSoc.recv(1024))
		toSend = file.read(1024)
		uploadmsg = ["GIVE_SUCCESSOR", toSend, size]
		nextSoc.send(pickle.dumps(uploadmsg))
		sentSize += len(toSend)
	file.close()
	nextSoc.close()
	print("{-- File transferred to Successor... --}")

################################################################## <UPLOAD> ##############################################################################

def ReadFile():
	filename = input("Enter name of file => ")
	try :
		file = open(filename, 'rb')
		file.close()
		fname = ' '.join(format(ord(x), 'b') for x in filename)
		fname =  str(fname)
		fname = fname.replace(' ','')
		fileKey = int(fname,2)
		Key = hash_func(fileKey)
		print("{-- Key: ", Key, " --}")
		return Key, filename
	except OSError:
		print("{-- File does not exit --}\n")
		return False, False


def getUploadSuccessor(UploadersNode, fileKey, successorPort):
	CurrPort = UploadersNode.port
	while True: 
		CurrPortKey = hash_func(CurrPort)
		succPortKey = hash_func(successorPort)
		if (fileKey > CurrPortKey and fileKey <= succPortKey) or (CurrPortKey>succPortKey and fileKey>CurrPortKey) or (CurrPortKey>succPortKey and fileKey<=succPortKey):
			break
		nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		nextSoc.connect((IP_ADDRESS, successorPort))
		fwdmsg = ["FWD", fileKey, UploadersNode] # Nothing of use is being sent except "FWD"
		nextSoc.send(pickle.dumps(fwdmsg))
		retmsg = pickle.loads(nextSoc.recv(1024))
		CurrPort = retmsg[0]
		successorPort = retmsg[1]
		nextSoc.close()
	return successorPort

def sendUploadedFile(successorPort, fname, fileKey):
	nextSoc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	nextSoc.connect((IP_ADDRESS, successorPort))
	size = str(os.path.getsize(fname))
	file = open(fname, 'rb')
	uploadmsg = ["UPLOAD", "First", fname]
	nextSoc.send(pickle.dumps(uploadmsg))
	size = int(size)
	sentSize = 0
	while sentSize < size:
		ack = pickle.loads(nextSoc.recv(1024))
		toSend = file.read(1024)
		uploadmsg = ["UPLOAD", toSend, size]
		nextSoc.send(pickle.dumps(uploadmsg))
		sentSize += len(toSend)
	file.close()
	nextSoc.close()
	print("{-- Completed... --}")

################################################################## <MAIN> ########################################################################

def Main(port):
	global YourNode
	port = int(port)
	YourNode = Node(port)
	knownPort = int(input("Enter port of a known node in chord, else enter 0: "))

	# Client just needs to connect with the known Port which ever one he knows
	listenToUser = threading.Thread(target = Listen, args = (port,knownPort,)) 
	listenToUser.start()

	update = threading.Thread(target = updateThread, args = (port,)) 
	update.start()

	# Now you open a socket of your port so that machines can connect to you
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind(("",port))
	s.listen(10)

	while True:
		# Whoever connects with you, you accept it and send that machine to the Replying(Server) thread
		machine, addr = s.accept()
		replyToPeers = threading.Thread(target = Reply, args = (port, machine,))
		replyToPeers.start()
if __name__ == '__main__':
	Main(sys.argv[1])