SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

DROP SCHEMA IF EXISTS `samMemo` ;
CREATE SCHEMA IF NOT EXISTS `samMemo` DEFAULT CHARACTER SET latin1 COLLATE latin1_spanish_ci ;
USE `samMemo` ;

-- -----------------------------------------------------
-- Table `samMemo`.`TAB_ENVIRONMENTS`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `samMemo`.`TAB_ENVIRONMENTS` ;

CREATE TABLE IF NOT EXISTS `samMemo`.`TAB_ENVIRONMENTS` (
  `envID` INT NOT NULL,
  `description` VARCHAR(30) NULL,
  `type` INT NULL,
  PRIMARY KEY (`envID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `samMemo`.`TAB_PLACES`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `samMemo`.`TAB_PLACES` ;

CREATE TABLE IF NOT EXISTS `samMemo`.`TAB_PLACES` (
  `envID` INT NOT NULL,
  `placeID` INT NOT NULL,
  `description` VARCHAR(30) NULL,
  `reward` FLOAT NULL,
  PRIMARY KEY (`envID`, `placeID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `samMemo`.`TAB_CONNECTIONS`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `samMemo`.`TAB_CONNECTIONS` ;

CREATE TABLE IF NOT EXISTS `samMemo`.`TAB_CONNECTIONS` (
  `envID` INT NOT NULL,
  `placeID` INT NOT NULL,
  `connID` INT NOT NULL,
  `description` VARCHAR(30) NULL,
  `nextPlace` INT NULL,
  `length` INT NULL,
  `slope` INT NULL,
  `abruptness` INT NULL,
  `Q` FLOAT NULL,
  PRIMARY KEY (`envID`, `connID`, `placeID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `samMemo`.`TAB_TASKS`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `samMemo`.`TAB_TASKS` ;

CREATE TABLE IF NOT EXISTS `samMemo`.`TAB_TASKS` (
  `taskID` INT NOT NULL,
  `description` VARCHAR(30) NULL,
  `type` INT NULL,
  PRIMARY KEY (`taskID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `samMemo`.`TAB_STATES`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `samMemo`.`TAB_STATES` ;

CREATE TABLE IF NOT EXISTS `samMemo`.`TAB_STATES` (
  `taskID` INT NOT NULL,
  `stateID` INT NOT NULL,
  `description` VARCHAR(30) NULL,
  `reward` FLOAT NULL,
  `rewardDefense` FLOAT NULL,
  PRIMARY KEY (`stateID`, `taskID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `samMemo`.`TAB_TRANSITIONS`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `samMemo`.`TAB_TRANSITIONS` ;

CREATE TABLE IF NOT EXISTS `samMemo`.`TAB_TRANSITIONS` (
  `taskID` INT NOT NULL,
  `stateID` INT NOT NULL,
  `transID` INT NOT NULL,
  `description` VARCHAR(30) NULL,
  `nextState` INT NULL,
  `cost` FLOAT NULL,
  `Q` FLOAT NULL,
  `QDefend` FLOAT NULL,
  PRIMARY KEY (`taskID`, `transID`, `stateID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `samMemo`.`TAB_BOARD`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `samMemo`.`TAB_BOARD` ;

CREATE TABLE IF NOT EXISTS `samMemo`.`TAB_BOARD` (
  `tryID` INT NOT NULL,
  `Cell00` INT NULL,
  `Cell01` INT NULL,
  `Cell02` INT NULL,
  `Cell10` INT NULL,
  `Cell11` INT NULL,
  `Cell12` INT NULL,
  `Cell20` INT NULL,
  `Cell21` INT NULL,
  `Cell22` INT NULL,
  `boardStatus` INT NULL,
  PRIMARY KEY (`tryID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `samMemo`.`TAB_STATES_PLAYER`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `samMemo`.`TAB_STATES_PLAYER` ;

CREATE TABLE IF NOT EXISTS `samMemo`.`TAB_STATES_PLAYER` (
  `taskID` INT NOT NULL,
  `stateID` INT NOT NULL,
  `cell0` INT NULL,
  `cell1` INT NULL,
  `cell2` INT NULL,
  `numMines` INT NULL,
  `numOthers` INT NULL,
  `dVictory` INT NULL,
  `dDefeat` INT NULL,
  PRIMARY KEY (`taskID`, `stateID`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;