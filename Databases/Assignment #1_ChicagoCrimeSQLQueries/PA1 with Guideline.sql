-- source \Users\Acer\Desktop\Codes\Data Bases\Assignment #1\CS340_20100120_A1.sql
CREATE DATABASE Chicago DEFAULT CHARACTER SET utf8;

USE Chicago;

-- SHOW VARIABLES LIKE "secure_file_priv";

CREATE TABLE CRIME (
	ID INTEGER,
	Primary_Type VARCHAR(50),
	Description VARCHAR(50),
	Location_Description VARCHAR(50),
	Arrest VARCHAR(20),
	Domestic VARCHAR(20),
	Community_Area_Number INTEGER,
	Year INTEGER
) Engine= InnoDB;

LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/Chicago_Crime_Data-v2.csv' 
INTO TABLE CRIME 
FIELDS TERMINATED BY ',' 
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;


CREATE TABLE SCHOOLS (
	School_ID INTEGER,
	Name_Of_School VARCHAR(255),
	City VARCHAR(50),
	Healthy_School_Certified VARCHAR(3),
	Safety_Score INTEGER,
	College_Enrollment INTEGER,
	Community_Area_No INTEGER,
	Community_Area_Name VARCHAR(50)
) Engine=InnoDB;


LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/Chicago_Public_Schools.csv' 
INTO TABLE SCHOOLS 
FIELDS TERMINATED BY ',' 
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;


CREATE TABLE CENSUS_DATA (
	Community_Area_No INTEGER,
	Community_Area_Name VARCHAR(50),
	Per_Capita_Income INTEGER,
	Hardship_Index INTEGER
) Engine=InnoDB;

LOAD DATA INFILE 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/Census_Data_-_Selected_socioeconomic_indicators_in_Chicago__2008___2012-v2.csv' 
INTO TABLE CENSUS_DATA 
FIELDS TERMINATED BY ',' 
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;


-- a)Find the total number of crimes recorded in the CRIME table. (5) 
SELECT COUNT(*) FROM CRIME;
-- b) Retrieve first 10 rows from the CRIME table. (5)
SELECT * FROM CRIME LIMIT 10;
-- c) How many crimes involve an arrest? (5)
SELECT COUNT(*) FROM CRIME WHERE Arrest = 'TRUE';
-- f) Which unique types of crimes have been recorded at GAS STATION locations? (5)
SELECT DISTINCT Primary_Type FROM CRIME WHERE Location_Description = 'GAS STATION';
-----------------------------------------------------------------------------------
-- Changing all empty values of Safety_Score to Null and then changing column type to int

-- SELECT NULLIF(Safety_Score, '') FROM SCHOOLS;
-- SELECT CAST(Safety_Score AS UNSIGNED) FROM SCHOOLS;
-- SELECT NULLIF(Safety_Score, 0) FROM SCHOOLS;
-----------------------------------------------------------------------------------
-- d) What is the average school Safety Score? (5)
SELECT AVG(Safety_Score) FROM SCHOOLS;
-- g) Which schools in Community Areas 10 to 15 are healthy school certified? (5)
SELECT Name_Of_School,Community_Area_No,Community_Area_Name FROM SCHOOLS WHERE Community_Area_No BETWEEN 10 and 15 AND Healthy_School_Certified = 'Yes';
-- h) List the top 5 Community Areas by average College Enrollment [number of students] (10) 
SELECT Community_Area_Name, AVG(College_Enrollment) FROM SCHOOLS GROUP BY Community_Area_Name ORDER BY AVG(College_Enrollment) DESC LIMIT 5;
-- i) Use a sub-query to determine which Community Area has the least value for school Safety Score? (10)
SELECT Community_Area_Name, Min_Safety_Score FROM (SELECT Community_Area_Name, min(Safety_Score) as Min_Safety_Score FROM SCHOOLS GROUP BY Community_Area_Name) AS SUBTABLE ORDER BY Min_Safety_Score;
-- k) Find the School ID, Name of School and City of all the schools with a lower than average safety score. (10) 
SELECT School_ID, Name_Of_School, City, Safety_Score FROM SCHOOLS WHERE Safety_Score < (SELECT avg(Safety_Score) FROM SCHOOLS);
-----------------------------------------------------------------------------------
-- e) In the CENUS_DATA table list all Community Areas whose names start with the letter ‘B’. (5)
SELECT Community_Area_Name FROM CENSUS_DATA WHERE Community_Area_Name LIKE 'B%';
-----------------------------------------------------------------------------------
-- j)Find the name of the community area and the Per Capita Income of the Community Area which has a school Safety Score of 1.  [Without using an explicit JOIN operator] (15) 
SELECT CD.Community_Area_Name, Per_Capita_Income 
FROM CENSUS_DATA AS CD, SCHOOLS AS S
WHERE CD.Community_Area_Name = S.Community_Area_Name AND S.Safety_Score = 1;
-- l) Find the name of the community area and the Per Capita Income of the Community Area which has School Safety Score of 1, using a JOIN operator. (20)
SELECT CENSUS_DATA.Community_Area_Name, CENSUS_DATA.Per_Capita_Income FROM CENSUS_DATA JOIN SCHOOLS ON CENSUS_DATA.Community_Area_No = SCHOOLS.Community_Area_No WHERE SCHOOLS.Safety_Score = 1; 
-----------------------------------------------------------------------------------