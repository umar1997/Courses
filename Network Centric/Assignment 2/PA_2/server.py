# wlps1 192.168.100.3
import socket
import sys
import curses
import pickle
from _thread import *
import threading 
from random import randint
import time

WIDTH = 60
HEIGHT = 19
INIT_SIZE = 3
INIT_POSX= 0
INIT_POSY= 0
food_pos = (randint(1,WIDTH-2),randint(1,HEIGHT-2))
final_scores = []
thread_number = 0

players=[]
players2= []
p_threads=[]
max_players = 0

def sendToClient(player, data): 			#SEND TO A SPECIFIC CLIENT
	data = pickle.dumps(data)
	player.send(data)

def broadcastMessage(data):					#SEND TO ALL CLIENTS
	data= pickle.dumps(data)
	for each in players:
		if each!=-1:
			each.send(data)

def talkToClient(player):					#MAIN THREADED FUNCTION
	global max_players
	global food_pos
	global final_scores
	global thread_number


	i=0
	while (len(players)<max_players):
		i+=1

	player_num = 0
	for i in range(len(players)):
		if player == players[i]:
			player_num=i+1
			break
	
	board_data = (WIDTH,HEIGHT, INIT_POSX,INIT_POSY, len(players), player_num, food_pos)
	sendToClient(player, board_data)

	while True:
		move = player.recv(1024) #[player_num, what_happened, data]
		try:
			move = pickle.loads(move)
			who_sent_update = move[0]
			what_happened = move[1]
			data = move[2]

			if what_happened=="food_alert":
				move[2] = (randint(1,WIDTH-2) , randint(1,HEIGHT-2))

			print("Player" , who_sent_update," triggered event:", what_happened,"  with data:", data)
			broadcastMessage(move)

			if what_happened=="end":
				max_players-=1
				players[who_sent_update-1]=-1
				final_scores[who_sent_update-1] = data
				thread_number-=1
				break
			
		except EOFError:
			thread_number-=1
			break

	status="end"

def main():
	global players
	global p_threads
	global max_players
	global final_scores
	global thread_number

	ip_add = sys.argv[1]
	port = int(sys.argv[2])
	max_players = int(sys.argv[3]) 
		
	server= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	server.bind(("",port))
	server.listen(max_players)
	
	while len(players)<max_players:
		player, addr = server.accept()
		players.append(player)
		players2.append(player)
		final_scores.append(-1)
		
		print ("connection by: ",addr)
		print(len(players), "player(s) are connected")

	for each_player in players:
		newThread= threading.Thread(target = talkToClient, args = (each_player,))
		# newThread.setDaemon(True)
		p_threads.append(newThread)
		thread_number+=1
		newThread.start() 	

	# for each_thread in p_threads:
 # 		each_thread.join()
	itr = 0
	while thread_number!=0:
 		itr+=1


	final_scores = [-1,"final_scores",final_scores]
	final_scores = pickle.dumps(final_scores)
	for each_player in players2:
		each_player.send(final_scores)

	print ("SENT TO ALL: ", pickle.loads(final_scores))

	time.sleep(2)
	server.close()

if __name__ == '__main__':	
	if len(sys.argv)!=4:
		print("Arguments Incorrect. Process Aborted")
	else:
		main()