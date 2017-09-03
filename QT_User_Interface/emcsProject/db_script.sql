DROP DATABASE IF EXISTS db_emcs;

CREATE DATABASE db_emcs;

USE db_emcs;

CREATE TABLE tab_parameter
(
	id_Parameter INT UNSIGNED AUTO_INCREMENT,
	CO2_Limit FLOAT NOT NULL, 
	Upper_Temperature FLOAT NOT NULL, 
	Lower_Temperature FLOAT NOT NULL, 
	Upper_Humidity FLOAT NOT NULL, 
	Lower_Humidity FLOAT NOT NULL, 	
	Phone_Number INT NOT NULL,
	date_parameter DATE,
	time_parameter TIME,
	
	CONSTRAINT Primary_key_parameter
		PRIMARY KEY(id_Parameter)
);

CREATE TABLE tab_read
(
	id_read INT UNSIGNED AUTO_INCREMENT,
	id_Parameter INT UNSIGNED,
	hum FLOAT NOT NULL,
	tem FLOAT NOT NULL,
	co2 FLOAT NOT NULL,
	date_read DATE,
	time_read TIME,
	
	CONSTRAINT Primary_key_read
		PRIMARY KEY (id_read),
		
	CONSTRAINT Foreign_key_parameter
		FOREIGN KEY (id_Parameter) REFERENCES tab_parameter (id_Parameter)
		ON UPDATE CASCADE
		ON DELETE CASCADE
);

INSERT INTO tab_parameter (CO2_Limit,Upper_Temperature,Lower_Temperature,
						   Upper_Humidity,Lower_Humidity,
						   Phone_number,date_parameter,time_parameter)
VALUES (1500,30,15,80,20,915900217,'2017-02-04','03:41:15');
