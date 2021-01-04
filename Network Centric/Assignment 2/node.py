import socket
import thread
import sys
import hashlib
import os
import time

ip = "localhost"
m = 100
joined = False

class Node:
	def __init__(self, port):
		self.key = hash_func(ip + str(port))
		self.port = port
		self.successor = port
		self.secSuccessor = port
		self.predeccessor = port
		self.state = True
		self.files = []

def hash_func(value):
	hash_object = hashlib.sha1(value)
	return int(hash_object.hexdigest(), 16)%30

def fix_links(serverNode, some_port):
	newSoc = socket.socket()
	newSoc.connect((ip, serverNode.predeccessor))
	newSoc.send("__FIX_LINKS__")
	ack = newSoc.recv(1024)
	newSoc.send(str(serverNode.port))
	ack = newSoc.recv(1024)
	newSoc.send(str(some_port))
	serverNode.predeccessor = some_port
	newSoc.close()

def server_fix_links(clientSoc, serverNode):
	clientSoc.send("ack")
	newSuccessor = int(clientSoc.recv(1024))
	serverNode.successor = newSuccessor

# telling predeccessor to update sec successor
def update_sec_successor(serverNode): 
	newSoc = socket.socket()
	newSoc.connect((ip, serverNode.predeccessor))
	newSoc.send("__UPDATE_SS__")
	ack = newSoc.recv(1024)
	newSoc.send(str(serverNode.port))
	ack = newSoc.recv(1024)
	newSoc.send(str(serverNode.successor))
	newSoc.close()

def client_join(node, some_port):
	if some_port:
		soc = socket.socket()
		soc.connect((ip, some_port))
		soc.send("__JOIN__")
		ack = soc.recv(1024)
		soc.send(str(node.port))

		some_key = (soc.recv(1024))
		if some_key=="ONE_P":
			node.successor = some_port
			node.predeccessor = some_port
		else:
			soc.send("ACK")
			predeccessor_port = int(soc.recv(1024))
			predeccessor_key = hash_func(ip+str(predeccessor_port))
			some_key = int(some_key)
			if (node.key < some_key) and (((node.key > predeccessor_key) and (some_key > predeccessor_key)) or ((node.key < predeccessor_key) and (some_key < predeccessor_key))) :
				soc.send("0")
				node.successor = some_port
				node.predeccessor = predeccessor_port
			elif (node.key > some_key) and (predeccessor_key > some_key) and (node.key > predeccessor_key):
				soc.send("0")
				node.successor = some_port
				node.predeccessor = predeccessor_port
			else :
				# print node.key, " ",some_key, " ", predeccessor_key
				soc.send("1")
				new_port = int(soc.recv(1024))
				client_join(node, new_port)

		soc.close()

		
	return
	
def server_join(clientSoc, serverNode, clientPort):
	if serverNode.port==serverNode.successor and serverNode.port==serverNode.predeccessor:
		clientSoc.send("ONE_P")
		serverNode.predeccessor = clientPort
		serverNode.successor = clientPort
	else:
		clientSoc.send(str(serverNode.key))
		ack = clientSoc.recv(1024)
		clientSoc.send(str(serverNode.predeccessor))
		query = clientSoc.recv(1024)
		if query == "0":
			fix_links(serverNode, clientPort)
			set_second_successor(serverNode)
			send_files_pred(serverNode)
		elif query == "1":
			clientSoc.send(str(serverNode.successor))

def set_second_successor(serverNode):
	newSoc = socket.socket()
	newSoc.connect((ip, serverNode.successor))
	newSoc.send("__SEND_SUCC__")
	ack = newSoc.recv(1024)
	newSoc.send(str(serverNode.port))
	serverNode.secSuccessor = int(newSoc.recv(1024))
	newSoc.close()

def client_leaving(node):
	node.state = False
	if (node.successor == node.port) and (node.predeccessor == node.port):
		return

	newSoc1 = socket.socket()
	# Informing Successor
	newSoc1.connect((ip,node.successor))
	newSoc1.send("__LEAVING_P__")
	ack = newSoc1.recv(1024)
	newSoc1.send(str(node.port))
	if node.successor == node.predeccessor:
		return
	ack = newSoc1.recv(1024)
	newSoc1.send(str(node.predeccessor))
	# newSoc1.shutdown(0)
	newSoc1.close()
	# Informing Predeccessor
	newSoc2 = socket.socket()
	newSoc2.connect((ip,node.predeccessor))
	newSoc2.send("__LEAVING_S__")
	ack = newSoc2.recv(1024)
	newSoc2.send(str(node.port))
	ack = newSoc2.recv(1024)
	newSoc2.send(str(node.successor))
	newSoc2.close()


def send_files_pred(serverNode):
	for fname in serverNode.files:
		hash_fname = hash_func(fname)
		pred = hash_func(ip + str(serverNode.predeccessor))
		if (hash_fname<pred):
			put_helper(serverNode, fname, serverNode.predeccessor)
			serverNode.files.remove(fname)

def server_side(clientSoc, serverNode):
	query = clientSoc.recv(1024)
	clientSoc.send("ack")
	clientPort = int(clientSoc.recv(1024))

	if query == "__JOIN__": 
		server_join(clientSoc, serverNode, clientPort)
	elif query == "__FIX_LINKS__": 
		server_fix_links(clientSoc, serverNode)
		set_second_successor(serverNode)
		update_sec_successor(serverNode)
	elif query == "__UPDATE_SS__":
		clientSoc.send("ack")
		serverNode.secSuccessor = int(clientSoc.recv(1024))
	elif query == "__SEND_SUCC__":
		clientSoc.send(str(serverNode.successor))
	elif query == "__LEAVING_P__":
		if (serverNode.successor == serverNode.predeccessor) and (serverNode.successor == clientPort):
			serverNode.successor = serverNode.port
			serverNode.predeccessor = serverNode.port
		else:
			clientSoc.send("ack")
			serverNode.predeccessor = int(clientSoc.recv(1024))
			set_second_successor(serverNode)
			update_sec_successor(serverNode)
	elif query == "__LEAVING_S__":
		clientSoc.send("ack")
		serverNode.successor = int(clientSoc.recv(1024))
	elif query == "__UPDATE_P__":
		serverNode.predeccessor = clientPort
	elif query == "find_successor_put":
		put_server(serverNode, clientSoc)
	elif query == "find_successor_get":
		get_server(serverNode, clientSoc)
	clientSoc.close()

def check_successor(node):
	count = 0
	while True:
		time.sleep(10)
		if node.port == node.successor and node.port == node.predeccessor:
			count = 0
		else:
			soc = socket.socket()
			try :
				soc.connect((ip,node.successor))
			  	soc.send("__PING__")
			  	ack = soc.recv(1024)
			  	soc.send(str(node.port))
			  	soc.close()
			except socket.error : 
				count = count+1

			if count == 3:
				newSoc = socket.socket()
				newSoc.connect((ip,node.secSuccessor))
				newSoc.send("__UPDATE_P__")
				ack = newSoc.recv(1024)
				newSoc.send(str(node.port))
				newSoc.close()
				node.successor = node.secSuccessor
				set_second_successor(node)
				update_sec_successor(node)
				count = 0

def put_server(serverNode, clientSoc):
	clientSoc.send("ack")
	fname = clientSoc.recv(1024)
	hash_fname = hash_func(fname)
	pred = hash_func(ip + str(serverNode.predeccessor))
	if ( (hash_fname<serverNode.key) and ((hash_fname>pred and serverNode.key>pred) or (hash_fname<pred and serverNode.key<pred))) or (hash_fname>serverNode.key and pred>serverNode.key and hash_fname>pred):
		clientSoc.send("send_file")
		fsize = long(clientSoc.recv(1024))
		file = open(fname,'wb')
		toWrite = clientSoc.recv(1024)
		file.write(toWrite)
		recvSize = len(toWrite)
		while recvSize < fsize:
			toWrite = clientSoc.recv(1024)
			recvSize += len(toWrite)
			file.write(toWrite)
		file.close()
		serverNode.files.append(fname)
	else:
		clientSoc.send(str(serverNode.successor))

def put_helper(node, fname, tempPort=None):
	if tempPort == None:
		tempPort = node.successor
	while True:
		newSoc = socket.socket()
		newSoc.connect((ip, tempPort))
		newSoc.send("find_successor_put")
		ack = newSoc.recv(1024)
		newSoc.send(str(node.port))
		ack = newSoc.recv(1024)
		newSoc.send(fname)
		check = newSoc.recv(1024)
		if check == "send_file":
			size = os.path.getsize(fname)
			newSoc.send(str(size))
			file = open(fname, 'rb')
			toSend = file.read(1024)
			newSoc.send(toSend)
			while toSend != "":
				toSend = file.read(1024)
				newSoc.send(toSend)
			file.close()
			return
		else:
			tempPort = int(check)

def put(node):
	fname = raw_input("Enter name of file=> ")
	try :
		with open(fname, 'rb') as file:
			print "File has been stored in DHT\n"
		h = hash_func(fname)
		print h
		pred = hash_func(ip + str(node.predeccessor))
		if ( (h<node.key) and ((h>pred and node.key>pred) or (h<pred and node.key<pred))) or (h>node.key and pred>node.key and h>pred):
			node.files.append(fname)
			return
		else:
			thread.start_new_thread(put_helper,(node, fname))
	except OSError:
		print "File does not exit\n"

def get_server(serverNode, clientSoc):
	clientSoc.send("ack")
	fname = clientSoc.recv(1024)
	hash_fname = hash_func(fname)
	pred = hash_func(ip + str(serverNode.predeccessor))
	if ( (hash_fname<serverNode.key) and ((hash_fname>pred and serverNode.key>pred) or (hash_fname<pred and serverNode.key<pred))) or (hash_fname>serverNode.key and pred>serverNode.key and hash_fname>pred) :
		if fname in serverNode.files:
			clientSoc.send("recv_file")
			ack = clientSoc.recv(1024)
			size = os.path.getsize(fname)
			clientSoc.send(str(size))
			file = open(fname, 'rb')
			toSend = file.read(1024)
			clientSoc.send(toSend)
			while toSend != "":
				toSend = file.read(1024)
				clientSoc.send(toSend)
			file.close()
			return
		else:
			clientSoc.send("No_file")
	else:
		clientSoc.send(str(serverNode.successor))	

def get_helper(node, fname):
	tempPort = node.successor
	while True:
		newSoc = socket.socket()
		newSoc.connect((ip,tempPort))
		newSoc.send("find_successor_get")
		ack = newSoc.recv(1024)
		newSoc.send(str(node.port))
		ack = newSoc.recv(1024)
		newSoc.send(fname)
		check = newSoc.recv(1024)
		if check == "recv_file":
			newSoc.send("ack")
			fsize = long(newSoc.recv(1024))
			file = open(fname,'wb')
			toWrite = newSoc.recv(1024)
			file.write(toWrite)
			recvSize = len(toWrite)
			while recvSize < fsize:
				toWrite = newSoc.recv(1024)
				recvSize += len(toWrite)
				file.write(toWrite)
			file.close()
			print "File has been retrieved\n"
			return
		elif check == "No_file":
			print "File is not in DHT\n"
			return
		else:
			tempPort = int(check)

def get(node):
	fname = raw_input("Enter name of file => ")
	if fname in node.files:
		print "File has been retrieved\n"
	else:
		get_helper(node, fname)

def client_side(node):
	thread.start_new_thread(check_successor, (node, ))
	while True:
		query = raw_input("enter 1 to print links\nenter 2 to put a file\nenter 3 to get a file\notherwise 0 to exit: ")
		if query == "0":
			client_leaving(node)
			for f in node.files:
				put_helper(node, f)
			os._exit(0)
		elif query =="1":
			print "Links:\n"
			print_links(node)
		elif query == "2":
			put(node)
			# print "put not done\n"
		elif query == "3":
			get(node)
			# print "get not done yet\n"
		else :
			print "Invalid input given\n"

def print_links(node):
	print "Key of your node is ", node.key, "with port: ", node.port
	print "Key of your successor is ", hash_func(ip + str(node.successor)), "with port: ", node.successor
	print "Key of your predeccessor is ", hash_func(ip + str(node.predeccessor)), "with port: ", node.predeccessor
	print "Key of your secSuccessor is ", hash_func(ip + str(node.secSuccessor)), "with port: ", node.secSuccessor

def Main(argv):
	myport = int(argv[0])
	some_port = int(raw_input("Enter port of a known node in chord, else enter 0: "))
	node = Node(myport)
	if some_port:
		client_join(node, some_port)
		set_second_successor(node)
	thread.start_new_thread(client_side,(node,))
	s = socket.socket()
	s.bind((ip,myport)) 
	s.listen(100) # max number of connections
	while True :
		client, addr = s.accept()
		thread.start_new_thread(server_side,(client, node))		
	s.close()

if __name__ == '__main__':
	Main(sys.argv[1:])