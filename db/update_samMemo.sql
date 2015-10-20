
USE samMemo;

-- -----------------------------------------------------
-- Table TAB_BOARD
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_BOARD;

CREATE TABLE IF NOT EXISTS TAB_BOARD
(
  tryID INT NOT NULL AUTO_INCREMENT,
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
  player VARCHAR(30) NULL,
  PRIMARY KEY (tryID)
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
  reward FLOAT NULL
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
  Q FLOAT NULL
);

ALTER TABLE TAB_TRANSITIONS
ADD CONSTRAINT PK_TRANSITIONS PRIMARY KEY (taskID, stateID, transID);

--- -----------------------------------------------------
--- Table `samMemo`.`TAB_STATES_PLAYER`
--- -----------------------------------------------------

DROP TABLE IF EXISTS TAB_STATES_PLAYER;

CREATE TABLE IF NOT EXISTS TAB_STATES_PLAYER 
(
  taskID INT NOT NULL,
  stateID INT NOT NULL,
  cell0 INT NULL,
  cell1 INT NULL,
  cell2 INT NULL,
  numMines INT NULL,
  numOthers INT NULL
);

ALTER TABLE TAB_STATES_PLAYER
ADD CONSTRAINT PK_STATES_PLAYER PRIMARY KEY (taskID, stateID);

--- -----------------------------------------------------
--- Table `samMemo`.`TAB_GAME_STATES`
--- -----------------------------------------------------

DROP TABLE IF EXISTS TAB_GAME_STATES;

CREATE TABLE IF NOT EXISTS TAB_GAME_STATES
(
  taskID INT NOT NULL,
  stateID INT NOT NULL,
  description VARCHAR(30) NULL,
  reward FLOAT NULL,
  cell0 INT NULL,
  cell1 INT NULL,
  cell2 INT NULL,
  numMines INT NULL,
  numOthers INT NULL
);

ALTER TABLE TAB_GAME_STATES
ADD CONSTRAINT PK_GAME_STATES PRIMARY KEY (taskID, stateID);



