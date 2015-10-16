
package tictactoe2;

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;


public class DB {
    
    private static Connection conn = null;
    private static Statement statement;
    private static final String username = "sam";
    private static final String password = "sam";      
    private static final String url = "jdbc:mysql://localhost:3306/samMemo";    
    private static PreparedStatement preparedStatement = null;
    private static ResultSet resultSet = null;
    
    public void loadFromMemo()
    {
        //get the values from the database
        try{
            String sql= "SELECT * FROM TAB_BOARD";
            statement.executeQuery(sql);
            resultSet = statement.getResultSet();
            
            if (resultSet != null)
            {
                while (resultSet.next())
                {
//                    InteractiveGUI.cell1 = resultSet.getInt("cell00");
//                    InteractiveGUI.cell2 = resultSet.getInt("cell01");
//                    InteractiveGUI.cell3 = resultSet.getInt("cell02");
//                    InteractiveGUI.cell4 = resultSet.getInt("cell10");
//                    InteractiveGUI.cell5 = resultSet.getInt("cell11");
//                    InteractiveGUI.cell6 = resultSet.getInt("cell12");
//                    InteractiveGUI.cell7 = resultSet.getInt("cell20");
//                    InteractiveGUI.cell8 = resultSet.getInt("cell21");
//                    InteractiveGUI.cell9 = resultSet.getInt("cell22");
//                    InteractiveGUI.bStatus = resultSet.getInt("boardStatus");   
//                    InteractiveGUI.turn = resultSet.getInt("turn");
                }
            }
        } catch(SQLException e){
            System.err.println("Error Code: " + ((SQLException)e).getErrorCode());
            System.err.println("Message: " + e.getMessage());
        }
        
    }
    
    public void storeInMemo()
    {
        try{
            String sql = "INSERT INTO TAB_BOARD (tryID, Cell00, Cell01, Cell02, Cell10, Cell11, Cell12, "
                    + "Cell20, Cell21, Cell22, boardStatus, turn) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
            preparedStatement = conn.prepareStatement(sql);
//            preparedStatement.setInt(1, InteractiveGUI.tryID);
//            preparedStatement.setInt(2, InteractiveGUI.cell1);
//            preparedStatement.setInt(3, InteractiveGUI.cell2);
//            preparedStatement.setInt(4, InteractiveGUI.cell3);
//            preparedStatement.setInt(5, InteractiveGUI.cell4);
//            preparedStatement.setInt(6, InteractiveGUI.cell5);
//            preparedStatement.setInt(7, InteractiveGUI.cell6);
//            preparedStatement.setInt(8, InteractiveGUI.cell7);
//            preparedStatement.setInt(9, InteractiveGUI.cell8);
//            preparedStatement.setInt(10, InteractiveGUI.cell9);
//            preparedStatement.setInt(11, 1);           
//            preparedStatement.setInt(12, InteractiveGUI.chooseTurn);
            preparedStatement.executeUpdate();
                      
        } catch(SQLException e){
            System.err.println("Error Code: " + ((SQLException)e).getErrorCode());
            System.err.println("Message: " + e.getMessage());
        } 
        
    }
    
    public void connectDB()
    {
        try{
            conn = DriverManager.getConnection(url, username, password);
            statement = conn.createStatement();
                      
        } catch (SQLException e) {
            System.err.println("Error Code: " + ((SQLException)e).getErrorCode());
            System.err.println("Message: " + e.getMessage());
        }
    }
    
    public void closeDB()
    {
        try{
            statement.close();
            conn.close();
    
        } catch(SQLException e){
            System.err.println("Error Code: " + ((SQLException)e).getErrorCode());
            System.err.println("Message: " + e.getMessage());
        }
    }
    
}
