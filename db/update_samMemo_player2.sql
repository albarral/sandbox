
USE samMemo;


-- -----------------------------------------------------
-- Table TAB_VIRTUAL_BOARD
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_VIRTUAL_BOARD;

CREATE TABLE IF NOT EXISTS TAB_VIRTUAL_BOARD
(
  row_ID INT NOT NULL,
  cell0 INT default 0,
  cell1 INT default 0,
  cell2 INT default 0
);

ALTER TABLE TAB_VIRTUAL_BOARD ADD CONSTRAINT PK_VIRTUAL_BOARD PRIMARY KEY (row_ID);

-- fill tab with 3 empty rows
insert into TAB_VIRTUAL_BOARD values (0, 0, 0, 0);
insert into TAB_VIRTUAL_BOARD values (1, 0, 0, 0);
insert into TAB_VIRTUAL_BOARD values (2, 0, 0, 0);

