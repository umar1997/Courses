import socket
import curses
import sys
import pickle
import threading 
import time
import os
from random import randint

player_number = -1
final_scores = []
board_data = (0,0,0,0,0,0,0)
init_pos = [(0,0),(0,0),(0,0),(0,0),(0,0)]
food_pos = (0,0)
total_score = 0

INIT_SNAKE_LEN = 3
snakes = []

win_status = ""
game_status= ""
food_status= ""
# up =259
# down = 258
# left = 260
# right = 261

#####################################CLASSES#############################################
class Snake(object):
	
    def __init__(self, x, y, symbol, window):
        self.symbol= symbol
        self.body_list = []
        self.total_score = 0
        self.timeout = 100
        self.eliminated = False

        for i in range(INIT_SNAKE_LEN, 0, -1):
            self.body_list.append(SnakeBod(x - i, y,symbol))			

        self.body_list.append(SnakeBod(x, y, '0'))				#head is at the end of body_list.
        self.window = window
        self.direction = curses.KEY_RIGHT
        self.last_head_pos = (x, y)
        self.direction_map = {
            259:  self.update1,
            258:  self.update2,
            260:  self.update3,
            261:  self.update4 
        }

    ForbiddenDir = {
        259: 258, 258: 259,
        260: 261, 261: 260,
    }		

    def update1(self):											#update head position coordinates
    	self.head.y -= 1

    def update2(self):
    	self.head.y += 1
    
    def update3(self):
    	self.head.x -= 1
    
    def update4(self):
    	self.head.x += 1
    
    @property
    def head(self):
    	return self.body_list[-1]

    @property
    def headPos(self):										#returns the position coordinates of head
    	return self.head.x, self.head.y

    def renderSnake(self):									#render snake on window
    	for part in self.body_list:
    		# print(part.x,part.y,part.symbol)
    		self.window.addstr(part.y, part.x, part.symbol)

    def redirect(self,new_direction): 						#change direction of snake 
    	if new_direction!=Snake.ForbiddenDir[self.direction]:
    		self.direction= new_direction

    @property    											#decorator
    def score(self):								        #returns the score 	
    	return 'Score: {}'.format(self.total_score) 			

    def add_body(self, body_list):							#add to the body of the snake
    	self.body_list.extend(body_list)

    def updatePos(self):									#update the position of the snake
    	tail = self.body_list[0]							#get the tail of the snake (first element of the body_list)
    	self.body_list.pop(0)								#remove the tail

    	tail.x = self.body_list[-1].x									######CHANGE TO HeadPos AFTER CHECKING######
    	tail.y = self.body_list[-1].y						
    	self.body_list.insert(-1, tail)						#the tail will move upfront right behind the head
    	self.last_head_pos = (self.head.x,self.head.y)					######MIGHT BE ABLE TO USE TAIL.X AND TAIL.Y HERE######
    	self.direction_map[self.direction]()				#update head pos coordinates

    @property
    def blist(self):
    	return self.body_list

    @property
    def collided(self):
        if any([(body.x, body.y) == self.headPos for body in self.body_list[:-1]]):
            return True
        else:
            return False

    @property
    def update_score(self):    	
        body =SnakeBod(self.last_head_pos[0],self.last_head_pos[1], self.symbol)
        self.body_list.insert(-1, body)
        self.total_score+=1
        return

    # def eliminate(self):
    # 	self.eliminated=True

    # @property
    # def get_elim(self):
    # 	return self.eliminated
    
class SnakeBod(object):
	def __init__(self,x,y, symbol = '#'):
		self.x =x
		self.y =y
		self.symbol = symbol

		@property
		def bodyPos(self):
			return self.x, self.y

def loadscreen():
	os.system('clear')
	print("	  YOU ARE PLAYER",player_number)
	print("	  YOUR GAME WILL BEGIN IN")
	time.sleep(1)
	os.system('clear')
	print("	  YOU ARE PLAYER",player_number)
	print("	  YOUR GAME WILL BEGIN IN","\n")
	print("          ##################")        
	print("          ##################")      
	print("                      ######")      
	print("                    ######")        
	print("                  ######")          
	print("               ######")             
	print("                 ######")           
	print("                   ######")         
	print("                      ######")     
	print("          ##################")      
	print("          ##################") 
	time.sleep(1)
	os.system('clear')
	print("	  YOU ARE PLAYER",player_number)
	print("	  YOUR GAME WILL BEGIN IN","\n")
	print("          ##################")
	print("          ##################")
	print("                       #####")
	print("                       #####")
	print("          ##################")
	print("          ##################")
	print("          ##################") 
	print("          #####")
	print("          #####")
	print("          ##################")
	print("          ##################") 
	time.sleep(1)
	os.system('clear')
	print("	  YOU ARE PLAYER",player_number)
	print("	  YOUR GAME WILL BEGIN IN","\n")
	print("              #########")
	print("              #########") 
	print("                   ####")
	print("                   ####")
	print("                   ####")
	print("                   ####")
	print("                   ####")
	print("                   ####")
	print("                   ####")
	print("          ##################")
	print("          ##################")
	time.sleep(1)
	os.system('clear')
#################################THREADED FUNCTIONS######################################
def ListenToPlayer(player, window): #THREADED FUNCTION THAT LISTENS FOR ANY USER INPUT
	while True:

		data=[player_number]		
		event = window.getch()
		if (event==261 or event==260 or event==259 or event==258):	#you changed your direction
			data.append("change_dir")
			data.append(event)
			data = pickle.dumps(data)
			player.send(data)

		elif food_status=="eaten":									#you ate the food
			data.append("food_alert")
			data.append(-1)
			data = pickle.dumps(data)
			player.send(data)

		elif game_status=="end"+str(player_number):					#your game ended
			data.append("end")
			data.append(total_score)
			data = pickle.dumps(data)
			player.send(data)
			break

def ListenToServer(screen,player,window): #THREADED FUNCTION THAT LISTENS FOR EVENTS FROM SERVER
	global snakes
	global food_status
	global food_pos
	global final_scores

	while True:
		new_event = player.recv(1024)
		new_event = pickle.loads(new_event)
		who_sent_update = new_event[0]
		what_happened = new_event[1]
		data = new_event[2]
		
		if what_happened == "change_dir":				#someone changed their direction
			snakes[who_sent_update-1].redirect(data)
			prev_dir = data 
		
		if what_happened == "food_alert":				#someone ate the food. New food was generated.
			food_pos  = data
			food_status = ""

		if what_happened == "end":						#your game ended
			if who_sent_update==player_number:
				break
	
#################################MAIN FUNCTION###############################################
def client(): 
	global board_data
	global player_number
	global init_pos
	global food_pos
	global snakes
	global game_status
	global win_status
	global food_status
	global final_scores
	global total_score

	ip_add = sys.argv[1]
	port = int(sys.argv[2])

	player=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	player.connect((ip_add,port))
	print("WAITING FOR OTHER PLAYERS TO JOIN...\n")
	board_data = player.recv(1024) #window x, window y, begin x, begin y, total#, your#, food_pos
	board_data = pickle.loads(board_data)

	total_players = board_data[4]
	player_number = board_data[5]
	food_pos = board_data[6]
	init_pos = [(INIT_SNAKE_LEN+1,2),(int(board_data[0]/2),2),(4,int(board_data[1]/2)), (INIT_SNAKE_LEN+1,board_data[1]-2), (int(board_data[0]/2), int(board_data[1]/2))]
	loadscreen()

	screen = curses.initscr()
	window = curses.newwin(board_data[1],board_data[0],board_data[3],board_data[2])
	window.timeout(100)
	window.keypad(True)
	curses.noecho()
	curses.curs_set(0)
	window.border(0)

	for i in range(total_players):
		snakes.append(Snake(init_pos[i][0], init_pos[i][1], str(i+1), window))

	PlayerThread = threading.Thread(target= ListenToPlayer, args = (player,window,))
	PlayerThread.setDaemon(True)
	ServerThread = threading.Thread(target = ListenToServer, args=(screen,player,window,))
	ServerThread.setDaemon(True)
	
	PlayerThread.start()
	ServerThread.start()

	x=1	
	while True:
		window.clear()
		window.border(0)
		window.addstr(0,5, 'player number '+ str(player_number) + ' ' + snakes[player_number-1].score)
		window.addstr(food_pos[1], food_pos[0], '*')

		for snake in snakes:
			if snake!=-1:						#render snakes that are still alive
				snake.renderSnake()

		time.sleep(0.3)							#to adjust speed of game
		for snake in snakes:
			if snake!=-1:	
				snake.updatePos()

		for i in range(len(snakes)):
			if snakes[i]!= -1:
				if snakes[i].headPos==food_pos:
					snakes[i].update_score
					food_status="eaten"
					if i == player_number-1:
						total_score+=1

		#CHECK IF SOMEONE COLLIDED WITH A WALL OR SOMEONE ELSE
		for i in range(len(snakes)):
			if snakes[i]!=-1:
				if i==player_number-1 and (snakes[i].headPos[0]==0 or snakes[i].headPos[0]==board_data[0]-1 or snakes[i].headPos[1]==0 or snakes[i].headPos[1]==board_data[1]-1 or snakes[i].collided): #you collide with a wall
					game_status="end"+str(player_number)
					x=0
					win_status="YOU LOSE"
					break

				if snakes[i].headPos[0]==0 or snakes[i].headPos[0]==board_data[0]-1 or snakes[i].headPos[1]==0 or snakes[i].headPos[1]==board_data[1]-1 or snakes[i].collided: #someone else collides with a wall
					snakes[i] = -1
					total_players -= 1
					# if total_players==1 and snakes[player_number-1]!=-1:
					# 	game_status="end"+str(player_number)
					# 	x=0
					# 	win_status="YOU WIN"
					# 	break

				for j in range(len(snakes)):
					if i!=j and snakes[j]!=-1 and snakes[i]!=-1:
						for k in range(len(snakes[j].blist)-1):
							if snakes[i]!=-1 and snakes[i].headPos == (snakes[j].blist[k].x , snakes[j].blist[k].y):
								if snakes[i]!=-1 and snakes[j].headPos == (snakes[i].blist[k].x, snakes[j].blist[k].y):
									#kill both
									if i==player_number-1 or j==player_number-1:								#you collide with someone's head
										game_status="end"+str(player_number)
										snakes[i]=-1
										snakes[j]=-1
										total_players-=2
										x=0
										if total_players==0:
											win_status="NO ONE WON"
										else:
											win_status="YOU LOSE"
										break		
									else:																		#someone collides with someone else's head
										snakes[i]=-1
										snakes[j]=-1
										total_players-=2

								if i==player_number-1:													#you collide with someone else
									game_status="end"+str(player_number)
									x=0
									win_status = "YOU LOSE"
									break
								else:																	#someone else collides into someone else
									snakes[i] = -1
									total_players -= 1
									# if total_players==1 and snakes[player_number-1]!=-1:
									# 	game_status="end"+str(player_number)
									# 	x=0
									# 	win_status="YOU WIN"
									# 	break

						if snakes[i]!=-1 and snakes[i].headPos==snakes[j].headPos:						
							if i==player_number-1 or j==player_number-1:								#you collide with someone's head
								game_status="end"+str(player_number)
								snakes[i]=-1
								snakes[j]=-1
								total_players-=2
								x=0
								if total_players==0:
									win_status="NO ONE WON"
								else:
									win_status="YOU LOSE"
								break		
							else:																		#someone collides with someone else's head
								snakes[i]=-1
								snakes[j]=-1
								total_players-=2
								# if total_players==1 and snakes[player_number-1]!=-1:
								# 	game_status="end"+str(player_number)
								# 	x=0
								# 	win_status="YOU WIN"
								break
			if x == 0:
				break											
		if x==0:
			break

	curses.endwin()
	os.system('clear')
	PlayerThread.join()
	ServerThread.join()

	#CALCULATE THE WINNER OF THE GAME	
	print("WAITING FOR OTHER PLAYERS TO FINISH...")
	final_scores = player.recv(1024)
	os.system('clear')
	final_scores = pickle.loads(final_scores)[2]
	print(final_scores)
	winner = []
	winner_score = -1
	for i in range(len(final_scores)):
		if final_scores[i]>winner_score:
			winner = [i+1]
			winner_score= final_scores[i]
		elif final_scores[i] == winner_score:
			winner.append(i+1)

	if len(winner)==1 and winner==[player_number]:
		print("PLAYER",player_number,": YOU WIN!!!		   \n")
		print("YOUR SCORE: ", winner_score)
	elif len(winner)>1 and player_number in winner:
		print("TIE BETWEEN PLAYERS ",winner)
		print("YOUR SCORE: ", winner_score)
	else:
		print("PLAYER",player_number,": YOU LOST :(        \n")		
	player.close()

if __name__ == '__main__':
	if len(sys.argv)!=3:
		print("Arguments Incorrect. Process Aborted")
	else:
		client()