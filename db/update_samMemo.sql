
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
  boardStatus INT NULL
);

ALTER TABLE TAB_BOARD
ADD CONSTRAINT PK_BOARD PRIMARY KEY (tryID);
