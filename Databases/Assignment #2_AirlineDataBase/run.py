import mysql.connector
from mysql.connector import errorcode
from os import system
from prettytable import PrettyTable
from prettytable import from_db_cursor
from time import sleep
from getpass import getpass
import sys

try:
  db = mysql.connector.connect(
  host = '127.0.0.1',
	user = 'root',
  port = '3306',
	password = '*********',
  #	auth_plugin='mysql_native_password'
)

# CREATE DATABASE AIRLINE DEFAULT CHARACTER SET utf8;

  if db.is_connected():
        db_Info = db.get_server_info()
        print('Connected to MySQL Server version ', db_Info)
        cursor = db.cursor()
        cursor.execute('USE AIRLINE;')
        database_name = cursor.fetchone()
        print("YOU'RE CONNECTED TO DATABASE: ", database_name)
        system('cls')

        ######################################################## WELCOME PAGE ########################################################

        print(' /$$      /$$ /$$$$$$$$ /$$        /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$ ')                                      
        print('| $$  /$ | $$| $$_____/| $$       /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/ ')                                       
        print('| $$ /$$$| $$| $$      | $$      | $$  \__/| $$  \ $$| $$$$  /$$$$| $$       ')                                             
        print('| $$/$$ $$ $$| $$$$$   | $$      | $$      | $$  | $$| $$ $$/$$ $$| $$$$$    ')                                      
        print('| $$$$_  $$$$| $$__/   | $$      | $$      | $$  | $$| $$  $$$| $$| $$__/    ')                                     
        print('| $$$/ \  $$$| $$      | $$      | $$    $$| $$  | $$| $$\  $ | $$| $$       ')                                      
        print('| $$/   \  $$| $$$$$$$$| $$$$$$$$|  $$$$$$/|  $$$$$$/| $$ \/  | $$| $$$$$$$$ ')                                     
        print('|__/     \__/|________/|________/ \______/  \______/ |__/     |__/|________/ ')                                      
        print(' ')                                                                                                                  
        print(' ')                                                                                                                  
        print(' ')                                                                                                                  
        print(' /$$$$$$$$ /$$$$$$    ')                                                                                             
        print('|__  $$__//$$__  $$   ')                                                                                             
        print('   | $$  | $$  \ $$   ')                                                                                             
        print('   | $$  | $$  | $$   ')                                                                                             
        print('   | $$  | $$  | $$   ')                                                                                             
        print('   | $$  | $$  | $$   ')                                                                                             
        print('   | $$  |  $$$$$$/   ')                                                                                             
        print('   |__/   \______/    ')                                                                                             
        print(' ')                                                                                                                  
        print(' ')                                                                                                                  
        print(' ')                                                                                                                              
        print('  /$$$$$$  /$$$$$$ /$$$$$$$  /$$       /$$$$$$ /$$   /$$ /$$$$$$$$       /$$$$$$$  /$$$$$$$  /$$      /$$  /$$$$$$   ')
        print(' /$$__  $$|_  $$_/| $$__  $$| $$      |_  $$_/| $$$ | $$| $$_____/      | $$__  $$| $$__  $$| $$$    /$$$ /$$__  $$  ')
        print('| $$  \ $$  | $$  | $$  \ $$| $$        | $$  | $$$$| $$| $$            | $$  \ $$| $$  \ $$| $$$$  /$$$$| $$  \__/  ')
        print('| $$$$$$$$  | $$  | $$$$$$$/| $$        | $$  | $$ $$ $$| $$$$$         | $$  | $$| $$$$$$$ | $$ $$/$$ $$|  $$$$$$   ')
        print('| $$__  $$  | $$  | $$__  $$| $$        | $$  | $$  $$$$| $$__/         | $$  | $$| $$__  $$| $$  $$$| $$ \____  $$  ')
        print('| $$  | $$  | $$  | $$  \ $$| $$        | $$  | $$\  $$$| $$            | $$  | $$| $$  \ $$| $$\  $ | $$ /$$  \ $$  ')
        print('| $$  | $$ /$$$$$$| $$  | $$| $$$$$$$$ /$$$$$$| $$ \  $$| $$$$$$$$      | $$$$$$$/| $$$$$$$/| $$ \/  | $$|  $$$$$$/  ')
        print('|__/  |__/|______/|__/  |__/|________/|______/|__/  \__/|________/      |_______/ |_______/ |__/     |__/ \______/   ')
                                                                                                                   
                                                                                                                   
        input('')                                                                                                          
        system('cls')


        ######################################################## CREATE TABLES ########################################################
        ############## CREDENTIALS
        Table_Info = ''' CREATE TABLE Credentials (
          UserName VARCHAR(20) NOT NULL,
          Password VARCHAR(20) NOT NULL,
          AR_Binary INTEGER(1) NOT NULL
        )'''


        ############## PASSENGERS
        Table_Passenger = ''' CREATE TABLE Passengers (
          Passenger_ID INTEGER NOT NULL AUTO_INCREMENT,
          Full_Name VARCHAR(50) NOT NULL,
          Phone VARCHAR(11) NOT NULL,
          CNIC VARCHAR(13) NOT NULL,
          Address VARCHAR(50),
          Nationality VARCHAR(50),
          PRIMARY KEY(Passenger_ID)
          )'''
          # CONSTRAINT valid_phone_number CHECK (REGEXP_LIKE(Phone, '^0\d{10}$')),
          # CONSTRAINT valid_cnic CHECK (REGEXP_LIKE(CNIC, '^\d{13}$'))

        ############## FLIGHTS
        Table_Flights = ''' CREATE TABLE Flights (
          Flight_ID INTEGER NOT NULL AUTO_INCREMENT,
          toAirport_ID INTEGER NOT NULL,
          fromAirport_ID INTEGER NOT NULL,
          Dates DATE NOT NULL,
          departureTime INTEGER NOT NULL,
          arrivalTime INTEGER NOT NULL,
          fare INTEGER NOT NULL,
          Airplane_ID INTEGER NOT NULL, 
          PRIMARY KEY(Flight_ID),
          CONSTRAINT FOREIGN KEY(Airplane_ID) REFERENCES Airplanes(Airplane_ID) ON DELETE CASCADE ON UPDATE CASCADE,
          CONSTRAINT FOREIGN KEY(toAirport_ID) REFERENCES Airports(Airport_ID) ON DELETE CASCADE ON UPDATE CASCADE,
          CONSTRAINT FOREIGN KEY(fromAirport_ID) REFERENCES Airports(Airport_ID) ON DELETE CASCADE ON UPDATE CASCADE
          )'''
          #Time constraint for only between 0 and 24 ^[0-2][0-9]:[0-9][0-9]$

        ############## AIRPORTS
        Table_Airports = ''' CREATE TABLE Airports (
          Airport_ID INTEGER NOT NULL AUTO_INCREMENT,
          Airport_Name VARCHAR(50) NOT NULL,
          PRIMARY KEY(Airport_ID)
          )'''

        ############## AIRPLANE
        Table_Airplane = ''' CREATE TABLE Airplanes (
          Airplane_ID INTEGER NOT NULL AUTO_INCREMENT,
          Airline VARCHAR(50) NOT NULL,
          PRIMARY KEY(Airplane_ID)
          )'''

        ############## TICKETS
        Table_Tickets = ''' CREATE TABLE Tickets (
          Ticket_ID INTEGER NOT NULL AUTO_INCREMENT,
          Passenger_ID INTEGER NOT NULL,
          Flight_ID INTEGER NOT NULL,
          PRIMARY KEY(Ticket_ID),
          CONSTRAINT FOREIGN KEY(Flight_ID) REFERENCES Flights(Flight_ID) ON DELETE CASCADE ON UPDATE CASCADE,
          CONSTRAINT FOREIGN KEY(Passenger_ID) REFERENCES Passengers(Passenger_ID) ON DELETE CASCADE ON UPDATE CASCADE
          )'''


        tables = [Table_Info,Table_Passenger,Table_Airplane,Table_Airports,Table_Flights,Table_Tickets]
        for t in tables:
          try:  
            cursor.execute(t)
          except:
            continue
        
        ######################################################## LOGIN ########################################################
        while True:
          print('   __   ____  __________  __ ')
          print('  / /  / __ \/ ___/  _/ |/ / ')
          print(' / /__/ /_/ / (_ // //    /  ')
          print('/____/\____/\___/___/_/|_/   ')
          print(' ')
          print(' ')

          qst = input('Have an account? (Y|N): ')
          print('\n')
          Job = 2
          #################################################### ALREADY HAVE AN ACCOUNT
          if qst == 'Y' or  qst == 'y':
            while True:  
              system('cls')
              un = input('ENTER USERNAME: ')
              pwd = getpass('ENTER PASSWORD:')
              cursor.execute('SELECT Password FROM Credentials WHERE UserName = \''+un+'\';')
              dbpwd = cursor.fetchall()
              if dbpwd == []:
                print('\nERROR: Invalid UserName or Password.')
                input('')
                system('cls')
              elif dbpwd[0][0] == pwd:
                print('\nLogin Successful')
                cursor.execute('SELECT AR_Binary FROM Credentials WHERE UserName = \''+un+'\';')
                Job = cursor.fetchall()
                Job = Job[0][0]
                input('')                 
                break
              else:
                print('Incorrect Password')
                input('')
                system('cls')
            system('cls')                  
          #################################################### Dont HAVE AN ACCOUNT
          elif qst == 'N' or qst == 'n':
            system('cls')
            while True:
              Job = input('ENTER 1 FOR ADMINISTRATION, 0 FOR RECEPTIONIST: ')
              un = input('ENTER USERNAME: ')
              pwd = input('ENTER PASSWORD: ')
              cfrmpwd = input('CONFIRM PASSWORD: ')

              if pwd == cfrmpwd:
                try:
                  cursor.execute('INSERT INTO Credentials(UserName, Password, AR_Binary) VALUES (\''+un+'\',\''+pwd+'\','+Job+')')
                  db.commit()
                  print('\nAccount Created Successfully.')
                  Job = int(Job)
                  break
                except:
                  print('\nInvalid Entry.')
                  input('')
                  system('cls')
              else:
                print('\nERROR: Passwords Dont Match')
                sinput('')
                system('cls')
            system('cls')
          ####################################################### QUESTIONS ADMIN ########################################################
          if Job == 1:
            while True:
              system('cls')  
              print('ADMINISTRATOR PAGE\n')
              print('1. Add a new flight record.')
              print('2. Update existing flight record.')
              print('3. Cancel a particular flight record.')
              print('4. View all flights landing and taking off for a particular airport on that day.')
              print('5. View every table of the database in tabular form.')
              print('6. Log Out')
              n = input('#####################################  Enter Field Number (1-6): ')
              

              ######################################################## ADMIN 1
              if n == '1':
                while True:
                  system('cls')
                  datex = input('Enter Date(YYYY-MM-DD): ')
                  toAirport = input('Enter Airport City To Go To: ')
                  fromAirport = input('Enter Airport City To Go From: ')
                  departureTime = input('Enter Departure Time(XXXX): ')
                  arrivalTime = input('Enter Arrival Time(XXXX): ')
                  airlineName = input('Enter Airline: ')
                  fare = input('Enter Fare($): ')


                  cursor.execute('SELECT Airport_ID FROM Airports WHERE Airport_Name = \''+toAirport+'\'')
                  toAP = cursor.fetchall()
                  if toAP == []:
                    cursor.execute('INSERT INTO Airports(Airport_Name) VALUES (\''+toAirport+'\')')
                    db.commit()
                    cursor.execute('SELECT Airport_ID FROM Airports WHERE Airport_Name = \''+toAirport+'\'')
                    toAP = cursor.fetchall()
                  cursor.execute('SELECT Airport_ID FROM Airports WHERE Airport_Name = \''+fromAirport+'\'')
                  fromAP = cursor.fetchall()
                  if fromAP == []:
                    cursor.execute('INSERT INTO Airports(Airport_Name) VALUES (\''+fromAirport+'\')')
                    db.commit()
                    cursor.execute('SELECT Airport_ID FROM Airports WHERE Airport_Name = \''+fromAirport+'\'')
                    fromAP = cursor.fetchall()
                  cursor.execute('SELECT Airplane_ID FROM Airplanes WHERE Airline = \''+airlineName+'\'')
                  airlineID = cursor.fetchall()
                  if  airlineID == []:
                    cursor.execute('INSERT INTO Airplanes(Airline) VALUES (\''+airlineName+'\')')
                    db.commit()
                    cursor.execute('SELECT Airplane_ID FROM Airplanes WHERE Airline = \''+airlineName+'\'')
                    airlineID = cursor.fetchall()
                  try:
                    cursor.execute('INSERT INTO Flights(toAirport_ID,fromAirport_ID,Dates,departureTime,arrivalTime, fare,Airplane_ID) VALUES ('+str(toAP[0][0])+', '+str(fromAP[0][0])+', \''+datex+'\', '+departureTime+', '+arrivalTime+', '+fare+', '+str(airlineID[0][0])+')')
                    db.commit()
                  except Exception as e: 
                    print(e)
                  t = PrettyTable(['To','From','Date','Departure Time', 'Arrival Time','Airline','Fare($)'])
                  t.add_row([toAirport, fromAirport, datex, departureTime, arrivalTime, airlineName, fare])
                  print('Flight Has Been Added Successfully \n')
                  print(t)
                  input('')
              ######################################################## ADMIN 2
              elif n == '2':                                              # Departure     # Arrival
                cursor.execute('SELECT Flights.Flight_ID, Flights.Dates,  S.Airport_Name, T.Airport_Name, Flights.fare FROM Flights JOIN Airports as T JOIN Airports as S ON Flights.toAirport_ID = T.Airport_ID AND Flights.fromAirport_ID = S.Airport_ID')
                result = cursor.fetchall()
                t = PrettyTable(['FLight ID','Date','Departure Airport','Arrival Airport', 'Fare($)'])
                for i in range(len(result)):
                  t.add_row([result[i][0], result[i][1], result[i][2], result[i][3], result[i][4]])
                print(t)
                x = input('\nEnter Flight_ID To Update: ')
                print('FIELDS')
                print('1. Departure Airport')
                print('2. Arrival Airport')
                print('3. Departure Time')
                print('4. Arrival Time')
                print('5. Date')
                print('6. Fare')
                z = input('Enter Field To Update(1-6): ')
                if z == '1':
                  New = input('Enter New Departure Airport: ')
                  cursor.execute('SELECT Airport_ID FROM Airports WHERE Airport_Name = \''+New+'\'')
                  the_id = cursor.fetchall()
                  if the_id == []:
                    cursor.execute('INSERT INTO Airports(Airport_Name) VALUES(\''+New+'\')')
                    db.commit()
                    cursor.execute('SELECT Airport_ID FROM Airports WHERE Airport_Name = \''+New+'\'')
                    the_id = cursor.fetchall()
                    cursor.execute('UPDATE Flights SET fromAirport_ID = '+str(the_id[0][0])+' WHERE Flight_ID = '+x+'')
                    db.commit()
                  else:
                    cursor.execute('UPDATE Flights SET fromAirport_ID = '+str(the_id[0][0])+' WHERE Flight_ID = '+x+'')
                    db.commit()
                  print('Updated Successfully')
                elif z == '2':
                  New = input('Enter New Arrival Airport: ')
                  cursor.execute('SELECT Airport_ID FROM Airports WHERE Airport_Name = \''+New+'\'')
                  the_id = cursor.fetchall()
                  if the_id == []:
                    cursor.execute('INSERT INTO Airports(Airport_Name) VALUES(\''+New+'\')')
                    db.commit()
                    cursor.execute('SELECT Airport_ID FROM Airports WHERE Airport_Name = \''+New+'\'')
                    the_id = cursor.fetchall()
                    cursor.execute('UPDATE Flights SET toAirport_ID = '+str(the_id[0][0])+' WHERE Flight_ID = '+x+'')
                    db.commit()
                  else:
                    cursor.execute('UPDATE Flights SET toAirport_ID = '+str(the_id[0][0])+' WHERE Flight_ID = '+x+'')
                    db.commit()
                  print('Updated Successfully')
                elif z == '3':
                  New = input('Enter New Departure Time(XXXX): ')
                  cursor.execute('UPDATE Flights SET departureTime = '+New+' WHERE Flight_ID = '+x+'')
                  db.commit()
                  print('Updated Successfully')
                elif z == '4':
                  New = input('Enter New Departure Time(XXXX): ')
                  cursor.execute('UPDATE Flights SET arrivalTime = '+New+' WHERE Flight_ID = '+x+'')
                  db.commit()
                  print('Updated Successfully')
                elif z == '5':
                  New = input('Enter New Date(YYYY-MM-DD): ')
                  cursor.execute('UPDATE Flights SET Dates = \''+New+'\' WHERE Flight_ID = '+x+'')
                  db.commit()
                  print('Updated Successfully')
                elif z == '6':
                  New = input('Enter New Fare($): ')
                  cursor.execute('UPDATE Flights SET fare = '+New+' WHERE Flight_ID = '+x+'')
                  db.commit()
                  print('Updated Successfully')
                input('')
              ######################################################## ADMIN 3
              elif n == '3': 
                cursor.execute('SELECT Flights.Flight_ID, Flights.Dates,  S.Airport_Name, T.Airport_Name, Flights.fare FROM Flights JOIN Airports as T JOIN Airports as S ON Flights.toAirport_ID = T.Airport_ID AND Flights.fromAirport_ID = S.Airport_ID')
                result = cursor.fetchall()
                t = PrettyTable(['FLight ID','Date','Departure Airport','Arrival Airport', 'Fare($)'])
                for i in range(len(result)):
                  t.add_row([result[i][0], result[i][1], result[i][2], result[i][3], result[i][4]])
                print(t)
                x = input('\nEnter Flight_ID To Cancel: ')
                cursor.execute('DELETE FROM Flights WHERE Flight_ID = '+x+'')
                db.commit()
                print('Flight Has Been Canceled Successfully.')
                input('')
              ######################################################## ADMIN 4
              elif n == '4':
                dt = input('Enter Date To View Flights(YYYY-MM-DD): ')
                ap = input('Enter Airport You Wish To View: ')
                cursor.execute('SELECT Airport_ID FROM Airports WHERE Airport_Name = \''+ap+'\'')
                apid = cursor.fetchall()
                if apid == []:
                  print('No Flight Records For This Airport')
                else:
                  cursor.execute('SELECT Flights.Dates, D.Airport_Name, A.Airport_Name, Flights.departureTime, Flights.arrivalTime, Flights.fare  FROM Flights JOIN Airports AS D JOIN Airports as A ON Flights.toAirport_ID = A.Airport_ID AND Flights.fromAirport_ID = D.Airport_ID WHERE Dates = \''+dt+'\' AND toAirport_ID = '+str(apid[0][0])+' OR fromAirport_ID = '+str(apid[0][0])+'')
                  result = cursor.fetchall()
                  if result == []:
                    print('No Flight Records For This Airport On This Date.')
                  else:
                    t = PrettyTable(['Date','Departure Airport','Arrival Airport','Departure Time', 'Arrival Time','Fare($)'])
                    for i in range(len(result)):
                      t.add_row([result[i][0], result[i][1], result[i][2], result[i][3], result[i][4], result[i][4]])
                    print(t)
                input('')
              ######################################################## ADMIN 5
              elif n == '5':
                tables = ['Credentials','Passengers','Airplanes','Airports','Flights','Tickets']
                for t in tables:
                  print('\n<<<<<<< '+t+' >>>>>>>')
                  cursor.execute('SELECT * FROM '+t+'')
                  table = from_db_cursor(cursor)
                  print(table)
                input('')
              ######################################################## ADMIN 6
              elif n == '6':
                system('cls')
                break
              input('')
          ####################################################### QUESTIONS RECEPTIONIST ########################################################    
          elif Job == 0:
            while True:
              system('cls')
              print('RECEPTIONIST PAGE\n')
              print('1. Create a new passenger record.')
              print('2. Update existing passenger record.')
              print('3. Generate ticket record for a particular passenger for a particular flight.')
              print('4. Using departure airport IATA code and arrival airport IATA code, view all available flights in a particular time period')
              print('5. Using departure airport IATA code and arrival airport IATA code, view the cheapest flight.')
              print('6. View flight history of a particular passenger.')
              print('7. Cancel a particular ticket record')
              print('8. Log Out')
              n = input('Enter Field Number (1-8): ')
              ######################################################## RECEP 1
              if n == '1':
                while True:
                  system('cls')
                  name = input('Enter Full Name: ')
                  phone = input('Enter Phone #: ')
                  cnic = input('Enter CNIC: ')
                  addr = input ('Enter Address: ')
                  nation = input('Enter Nationality: ')
                  if phone.isnumeric() and cnic.isnumeric() and len(phone) == 11 and len(cnic) == 13:
                    try:
                      cursor.execute('INSERT INTO Passengers(Full_Name, Phone, CNIC, Address, Nationality) VALUES(\''+name+'\',\''+phone+'\',\''+cnic+'\', \''+addr+'\', \''+nation+'\')')
                      db.commit()
                      cursor.execute('SELECT * FROM Passengers WHERE CNIC = \''+cnic+'\' AND Full_Name = \''+name+'\'')
                      result = cursor.fetchall()
                      print('Passenger Created Successfully.')
                      t = PrettyTable(['Full Name','Phone #','CNIC','Address', 'Nationality'])
                      for i in range(len(result)):
                        t.add_row([result[i][0], result[i][1], result[i][2], result[i][3], result[i][4]])
                      print(t)
                      break
                    except:
                      print('Phone must be an 11 digit number. CNIC must be a 13 digit number.')
                      print('Inalid Entry. Please Try Again.')
                      input('')
                      continue
                  else:
                    print('Phone must be an 11 digit number. CNIC must be a 13 digit number.')
                    input('')
                    continue
                input('')
              ######################################################## RECEP 2    
              elif n == '2':
                cursor.execute('SELECT * FROM PASSENGERS')
                t = from_db_cursor(cursor)
                print(t)
                x = input('\nEnter Passenger_ID To Update: ')
                print('FIELDS')
                print('1. Full Name')
                print('2. Phone #')
                print('3. CNIC')
                print('4. Address')
                print('5. Nationality')
                z = input('Enter Field To Update(1-5): ')
                if z == '1':
                  New  = input('Enter New Full Name: ')
                  cursor.execute('UPDATE Passengers SET Full_Name = \''+New+'\' WHERE Passenger_ID = '+x+'')
                  db.commit()
                  print('Updated Successfully.')
                  input('')
                elif z == '2':
                  while True:
                    New  = input('Enter New Phone #: ')
                    if len(New) == 11 and New.isnumeric()==True:
                      cursor.execute('UPDATE Passengers SET Phone = \''+New+'\' WHERE Passenger_ID = '+x+'')
                      db.commit()
                      print('Updated Successfully.')
                      input('')
                      break
                    else:
                      print('Error: Phone must be an 11 digit number.')
                      input('')

                elif z == '3':
                  while True:
                    New  = input('Enter New CNIC: ')
                    if len(New) == 13 and New.isnumeric():
                      cursor.execute('UPDATE Passengers SET CNIC = \''+New+'\' WHERE Passenger_ID = '+x+'')
                      db.commit()
                      print('Updated Successfully.')
                      input('')
                      break
                    else:
                      print('Error: CNIC must be an 13 digit number.')
                      input('')
                
                elif z == '4':
                  New  = input('Enter New Address: ')
                  cursor.execute('UPDATE Passengers SET Address = \''+New+'\' WHERE Passenger_ID = '+x+'')
                  db.commit()
                  print('Updated Successfully.')
                  input('')

                elif z == '5':
                  New  = input('Enter New Nationality: ')
                  cursor.execute('UPDATE Passengers SET Nationality = \''+New+'\' WHERE Passenger_ID = '+x+'')
                  db.commit()
                  print('Updated Successfully.')
                  input('')
              ######################################################## RECEP 3
              elif n == '3':
                cursor.execute('SELECT * FROM Passengers')
                t = from_db_cursor(cursor)
                print(t)
                pid = input('\nSelect Passenger_ID: ')
                cursor.execute('SELECT Flights.Flight_ID, Flights.Dates,  S.Airport_Name, T.Airport_Name, Flights.fare FROM Flights JOIN Airports as T JOIN Airports as S ON Flights.toAirport_ID = T.Airport_ID AND Flights.fromAirport_ID = S.Airport_ID')
                result = cursor.fetchall()
                t = PrettyTable(['FLight ID','Date','Departure Airport','Arrival Airport', 'Fare($)'])
                for i in range(len(result)):
                  t.add_row([result[i][0], result[i][1], result[i][2], result[i][3], result[i][4]])
                print(t)
                fid = input('\nSelect FLight_ID: ')
                cursor.execute('INSERT INTO Tickets(Passenger_ID, Flight_ID) VALUES('+pid+','+fid+')')
                db.commit()
                cursor.execute('SELECT fromAirport_ID, toAirport_ID, Airplane_ID FROM Flights WHERE Flight_ID = '+fid+'')
                row = cursor.fetchall()
                col = []
                cursor.execute('SELECT Airport_Name FROM Airports WHERE Airport_ID = '+str(row[0][0])+'')
                c = cursor.fetchall()
                col.append(c[0][0])
                cursor.execute('SELECT Airport_Name FROM Airports WHERE Airport_ID = '+str(row[0][1])+'')
                c = cursor.fetchall()
                col.append(c[0][0])
                cursor.execute('SELECT Airline FROM Airplanes WHERE Airplane_ID = '+str(row[0][2])+'')
                c = cursor.fetchall()
                col.append(c[0][0])
                cursor.execute('SELECT Passengers.Full_Name, Passengers.CNIC, Flights.Dates, Flights.Fare FROM Tickets JOIN Passengers JOIN Flights ON Passengers.Passenger_ID = Tickets.Passenger_ID AND Flights.Flight_ID = Tickets.Flight_ID WHERE Passengers.Passenger_ID = '+pid+' AND Flights.Flight_ID = '+fid+'')
                result = cursor.fetchall()
                t = PrettyTable(['Full Name','CNIC','Departure Airport','Arrival Airport','Airline','Date','Fare($)'])
                for i in range(len(result)):
                  t.add_row([result[i][0], result[i][1],col[0],col[1],col[2], result[i][2], result[i][3]])
                print(t)
                input('')
              ######################################################## RECEP 4
              elif n == '4':
                cursor.execute('SELECT * FROM Airports')
                t = from_db_cursor(cursor)
                print(t)
                apid = input('Choose IATA Code(Airport_ID): ')
                lt = input('Minimum Time(XXXX): ')
                ut = input('Maximum Time(XXXX): ')
                cursor.execute('SELECT * FROM (SELECT * FROM Flights WHERE toAirport_ID = '+apid+' OR fromAirport_ID = '+apid+') AS T WHERE departureTime  BETWEEN '+lt+' and '+ut+' AND arrivalTime  BETWEEN '+lt+' and '+ut+'')
                t = from_db_cursor(cursor)
                print(t)
                input('')
                ######################################################## RECEP 5
              elif n == '5':
                cursor.execute('SELECT * FROM Airports')
                t = from_db_cursor(cursor)
                print(t)
                apid = input('Choose IATA Code(Airport_ID): ')
                cursor.execute('SELECT MIN(fare) as min_fare FROM Flights WHERE  fromAirport_ID = '+apid+' LIMIT 1')
                mini1 = cursor.fetchall()
                cursor.execute('SELECT MIN(fare) as min_fare FROM Flights WHERE  toAirport_ID = '+apid+' LIMIT 1')
                mini2 = cursor.fetchall()
                if mini2[0][0] == None:
                  cursor.execute('SELECT * FROM Flights WHERE fare = '+str(mini1[0][0])+' AND fromAirport_ID = '+apid+'')
                  t = from_db_cursor(cursor)
                  print(t)
                elif mini1[0][0] == None:
                  cursor.execute('SELECT * FROM Flights WHERE fare = '+str(mini2[0][0])+' AND toAirport_ID = '+apid+'')
                  t = from_db_cursor(cursor)
                  print(t)
                elif mini2[0][0] <= mini1[0][0]: 
                  cursor.execute('SELECT * FROM Flights WHERE fare = '+str(mini2[0][0])+' AND toAirport_ID = '+apid+'')
                  t = from_db_cursor(cursor)
                  print(t)
                elif mini1[0][0] <= mini2[0][0]:
                  cursor.execute('SELECT * FROM Flights WHERE fare = '+str(mini1[0][0])+' AND fromAirport_ID = '+apid+'')
                  t = from_db_cursor(cursor)
                  print(t)
                input('')
              ######################################################## RECEP 6
              elif n == '6':
                cursor.execute('SELECT * FROM Passengers')
                t = from_db_cursor(cursor)
                print(t)
                pid = input('Choose Passenger_ID: ')
                cursor.execute('SELECT Flight_ID FROM Tickets WHERE Passenger_ID = '+pid+'' )
                f = cursor.fetchall()
                fls = []
                for i in range(len(f)):
                  cursor.execute('SELECT fromAirport_ID, toAirport_ID, Airplane_ID FROM Flights WHERE Flight_ID = '+str(f[i][0])+'')
                  row = cursor.fetchall()
                  col = []
                  cursor.execute('SELECT Airport_Name FROM Airports WHERE Airport_ID = '+str(row[0][0])+'')
                  c = cursor.fetchall()
                  col.append(c[0][0])
                  cursor.execute('SELECT Airport_Name FROM Airports WHERE Airport_ID = '+str(row[0][1])+'')
                  c = cursor.fetchall()
                  col.append(c[0][0])
                  cursor.execute('SELECT Airline FROM Airplanes WHERE Airplane_ID = '+str(row[0][2])+'')
                  c = cursor.fetchall()
                  col.append(c[0][0])
                  cursor.execute('SELECT Passengers.Full_Name, Passengers.CNIC, Flights.Dates, Flights.Fare FROM Tickets JOIN Passengers JOIN Flights ON Passengers.Passenger_ID = Tickets.Passenger_ID AND Flights.Flight_ID = Tickets.Flight_ID WHERE Passengers.Passenger_ID = '+pid+' AND Flights.Flight_ID = '+str(f[i][0])+'')
                  result = cursor.fetchall()
                  
                  for i in range(len(result)):
                    fls.append([result[i][0], result[i][1],col[0],col[1],col[2], result[i][2], result[i][3]])
                t = PrettyTable(['Full Name','CNIC','Departure Airport','Arrival Airport','Airline','Date','Fare($)'])
                for row in fls:
                  t.add_row(row)
                print(t)
                input('')
              ######################################################## RECEP 7
              elif n == '7':
                cursor.execute('SELECT * FROM Passengers')
                t = from_db_cursor(cursor)
                print(t)
                pid = input('\nSelect Passenger_ID: ')
                cursor.execute('SELECT Flights.Flight_ID, Flights.Dates,  S.Airport_Name, T.Airport_Name, Flights.fare FROM Flights JOIN Airports as T JOIN Airports as S ON Flights.toAirport_ID = T.Airport_ID AND Flights.fromAirport_ID = S.Airport_ID')
                result = cursor.fetchall()
                t = PrettyTable(['FLight ID','Date','Departure Airport','Arrival Airport', 'Fare($)'])
                for i in range(len(result)):
                  t.add_row([result[i][0], result[i][1], result[i][2], result[i][3], result[i][4]])
                print(t)
                fid = input('\nSelect FLight_ID: ')
                cursor.execute('DELETE FROM Tickets WHERE Passenger_ID = '+pid+' AND Flight_ID = '+fid+'')
                print('Ticket Record Canceled Successfully.')
                input('')
              ######################################################## RECEP 8
              elif n == '8':
                system('cls')
                break
          else:
            print('Enter Y or N')
            input('')
        

##############################################################<===========>############################################################
except mysql.connector.Error as err:
  if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
    print("Something is wrong with your USERNAME or PASSWORD")
  elif err.errno == errorcode.ER_BAD_DB_ERROR:
    print("Database Does Not Exist")
  else:
    print("Error while connecting to MySQL",err)

finally:
    if (db.is_connected()):
        cursor.close()
        db.close()
        print("MySQL connection is closed")
print(db) # <mysql.connector.connection.MySQLConnection object at 0x00000201F1B66278>


