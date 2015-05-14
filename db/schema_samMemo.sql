
DROP DATABASE IF EXISTS samMemo;
CREATE DATABASE IF NOT EXISTS samMemo;
USE samMemo;

-- -----------------------------------------------------
-- Table TAB_ENVIRONMENTS
-- -----------------------------------------------------
DROP TABLE  IF EXISTS TAB_ENVIRONMENTS;

CREATE TABLE TAB_ENVIRONMENTS 
(
  ID INT NOT NULL,
  description VARCHAR(30) default NULL,
  `type` INT default NULL
);

ALTER TABLE TAB_ENVIRONMENTS 
ADD CONSTRAINT PK_ENVIRONMENTS PRIMARY KEY (ID);


-- -----------------------------------------------------
-- Table TAB_PLACES
-- -----------------------------------------------------
DROP TABLE  IF EXISTS TAB_PLACES;

CREATE TABLE TAB_PLACES 
(
  ID INT NOT NULL,
  description VARCHAR(30) default NULL,
  environmentID INT NOT NULL
);

ALTER TABLE TAB_PLACES
ADD CONSTRAINT PK_PLACES PRIMARY KEY (ID, environmentID);


-- -----------------------------------------------------
-- Table TAB_CONNECTIONS
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_CONNECTIONS;

CREATE TABLE TAB_CONNECTIONS 
(
  ID INT NOT NULL,
  description VARCHAR(30) default NULL,
  environmentID INT NOT NULL,
  placeID INT NOT NULL,
  nextPlace INT default NULL,
  length INT default NULL,
  slope INT default NULL,
  abruptness INT default NULL
);

ALTER TABLE TAB_CONNECTIONS 
ADD CONSTRAINT PK_CONNECTIONS PRIMARY KEY (ID, environmentID, placeID);


