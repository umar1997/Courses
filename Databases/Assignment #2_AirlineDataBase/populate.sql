CREATE DATABASE AIRLINE DEFAULT CHARACTER SET utf8;
Use AIRLINE;

# Populate Airports
INSERT INTO Airports(Airport_Name) VALUES ('Karachi');
INSERT INTO Airports(Airport_Name) VALUES ('London');
INSERT INTO Airports(Airport_Name) VALUES ('New York');
INSERT INTO Airports(Airport_Name) VALUES ('Dubai');
INSERT INTO Airports(Airport_Name) VALUES ('San Francisco');
INSERT INTO Airports(Airport_Name) VALUES ('Paris');
INSERT INTO Airports(Airport_Name) VALUES ('Hong Kong');
INSERT INTO Airports(Airport_Name) VALUES ('Madrid');
INSERT INTO Airports(Airport_Name) VALUES ('Tokyo');
INSERT INTO Airports(Airport_Name) VALUES ('Istanbul');


# Populate Airplanes
INSERT INTO Airplanes(Airline) VALUES ('ETIHAD');
INSERT INTO Airplanes(Airline) VALUES ('AMERICAN AIRLINES');
INSERT INTO Airplanes(Airline) VALUES ('BRITISH AIRWAYS');
INSERT INTO Airplanes(Airline) VALUES ('PIA');
INSERT INTO Airplanes(Airline) VALUES ('EMIRATES');
INSERT INTO Airplanes(Airline) VALUES ('TURKISH AIRLINES');
INSERT INTO Airplanes(Airline) VALUES ('THAI AIRWAYS');
INSERT INTO Airplanes(Airline) VALUES ('QATAR AIRLINES');
INSERT INTO Airplanes(Airline) VALUES ('AIR PACIFIC');


INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('Ali','03214402159','3520613256668','36-B Gulberg','Pakistani');
INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('Imran','03214402159','3520613256668','72-A Valencia','Pakistani');
INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('Usman','03214402159','3520613256668','90-k Valencia','Pakistani');
INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('Javed','03214402159','3520613256668','71 A Askari 11','Pakistani');
INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('kamran','03214402159','3520613256668','78-p Bahria','Pakistani');
INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('Farhan','03214402159','3520613256668','Gujarawala','Pakistani');
INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('Haaris','03214402159','3520613256668','faisalabad','Pakistani');
INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('Omar','03214402159','3520613256668','67-H Iqbal Town','Pakistani');
INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('Atif','03214402159','3520613256668','Sibi','Pakistani');
INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('Mannan','03214402159','3520613256668','101-F DHA','Pakistani');
INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('Humayun','03214402159','3520613256668','Near Airport','Pakistani');
INSERT INTO Passengers(Full_Name,Phone,CNIC,Address, Nationality) VALUES('Hamza','03214402159','3520613256668','221 B Baker Street','Pakistani');
