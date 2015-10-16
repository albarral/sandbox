
USE samMemo;

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
