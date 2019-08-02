package model;

import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Classe de conexão com o banco de dados
 * @author daniel
 */
public class ConnectionDb {

    private Connection con;

    /**
     * Realiza conexão com o banco de dados utilizando o driver jdbc
     */
    public void connectDb() {
        String myUrl = "jdbc:mysql://localhost:3306/freelance";
        
        try {
            con = DriverManager.getConnection(myUrl, "freelanceAdm", "Freelance!123");
        } catch (SQLException ex) {
            Logger.getLogger(ConnectionDb.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    /**
     * Getter da conexão atual
     * @return conexão atual
     */
    public Connection getCon() {
        return con;
    }

    /**
     * Realiza uma query de SELCT no banco de dados e retorna o ResultSet
     * @param query query a ser feita
     * @return ResultSet rs resultdados da query
     */
    public ResultSet selectQuery(String query) {
        ResultSet rs = null;
        try {
            connectDb();
            Statement st = con.createStatement();
            rs = st.executeQuery(query);
        } catch (SQLException ex) {
            Logger.getLogger(LoginModel.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
        return rs;
    }
    
    /**
     * Realiza uma query de insert ou update no banco de dados
     * @param query query a ser feita
     */
    public void insertQuery(String query){
        try {
            connectDb();
            Statement st = con.createStatement();
            st.execute(query);
        } catch (SQLException ex) {
            Logger.getLogger(ConnectionDb.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }

}
