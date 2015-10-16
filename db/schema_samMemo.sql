
DROP DATABASE IF EXISTS samMemo;
CREATE DATABASE IF NOT EXISTS samMemo;
USE samMemo;

-- -----------------------------------------------------
-- Table TAB_ENVIRONMENTS
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_ENVIRONMENTS;

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
DROP TABLE IF EXISTS TAB_PLACES;

CREATE TABLE TAB_PLACES 
(
  envID INT NOT NULL,
  placeID INT NOT NULL,
  description VARCHAR(30) default NULL,
  reward FLOAT NULL
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
  abruptness INT default NULL,
  Q FLOAT NULL
);

ALTER TABLE TAB_CONNECTIONS 
ADD CONSTRAINT PK_CONNECTIONS PRIMARY KEY (envID, placeID, connID);


-- -----------------------------------------------------
-- Table TAB_TASKS
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_TASKS ;

CREATE TABLE IF NOT EXISTS TAB_TASKS 
(
  taskID INT NOT NULL,
  description VARCHAR(30) NULL,
  `type` INT NULL
);


-- -----------------------------------------------------
-- Table TAB_STATES
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_STATES ;

CREATE TABLE IF NOT EXISTS `TAB_STATES` 
(
  taskID INT NOT NULL,
  stateID INT NOT NULL,
  description VARCHAR(30) NULL,
  reward FLOAT NULL,
  rewardDefense FLOAT NULL
);

ALTER TABLE TAB_STATES
ADD CONSTRAINT PK_STATES PRIMARY KEY (taskID, stateID);

-- -----------------------------------------------------
-- Table TAB_TRANSITIONS
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_TRANSITIONS;

CREATE TABLE IF NOT EXISTS TAB_TRANSITIONS 
(
  taskID INT NOT NULL,
  stateID INT NOT NULL,
  transID INT NOT NULL,
  description VARCHAR(30) NULL,
  nextState INT NULL,
  cost FLOAT NULL,
  Q FLOAT NULL,
  QDefend FLOAT NULL
);

ALTER TABLE TAB_STATES
ADD CONSTRAINT PK_TRANSITIONS PRIMARY KEY (taskID, stateID, transID);


-- -----------------------------------------------------
-- Table TAB_BOARD
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_BOARD;

CREATE TABLE IF NOT EXISTS TAB_BOARD
(
  tryID INT NOT NULL,
  cell00 INT NULL,
  cell01 INT NULL,
  cell02 INT NULL,
  cell10 INT NULL,
  cell11 INT NULL,
  cell12 INT NULL,
  cell20 INT NULL,
  cell21 INT NULL,
  cell22 INT NULL,
  boardStatus INT NULL,
  turn INT NULL
);

ALTER TABLE TAB_BOARD
ADD CONSTRAINT PK_BOARD PRIMARY KEY (tryID);

