
DROP DATABASE IF EXISTS samMemo;
CREATE DATABASE IF NOT EXISTS samMemo;
USE samMemo;

-- -----------------------------------------------------
-- Table TAB_ENVIRONMENTS
-- -----------------------------------------------------
DROP TABLE  IF EXISTS TAB_ENVIRONMENTS;

CREATE TABLE TAB_ENVIRONMENTS 
(
  envID INT NOT NULL,
  description VARCHAR(30) default NULL,
  `type` INT default NULL
);

ALTER TABLE TAB_ENVIRONMENTS 
ADD CONSTRAINT PK_ENVIRONMENTS PRIMARY KEY (envID);


-- -----------------------------------------------------
-- Table TAB_PLACES
-- -----------------------------------------------------
DROP TABLE  IF EXISTS TAB_PLACES;

CREATE TABLE TAB_PLACES 
(
  envID INT NOT NULL,
  placeID INT NOT NULL,
  description VARCHAR(30) default NULL
);

ALTER TABLE TAB_PLACES
ADD CONSTRAINT PK_PLACES PRIMARY KEY (envID, placeID);


-- -----------------------------------------------------
-- Table TAB_CONNECTIONS
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_CONNECTIONS;

CREATE TABLE TAB_CONNECTIONS 
(
  envID INT NOT NULL,
  placeID INT NOT NULL,
  connID INT NOT NULL,
  description VARCHAR(30) default NULL,
  nextPlace INT default NULL,
  length INT default NULL,
  slope INT default NULL,
  abruptness INT default NULL
);

ALTER TABLE TAB_CONNECTIONS 
ADD CONSTRAINT PK_CONNECTIONS PRIMARY KEY (envID, placeID, connID);


