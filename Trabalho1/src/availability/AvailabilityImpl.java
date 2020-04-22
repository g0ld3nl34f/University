/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package availability;

/**
 *
 * @author l40011
 */
import java.util.Vector;
import java.rmi.server.UnicastRemoteObject;
import java.sql.*;

public class AvailabilityImpl extends UnicastRemoteObject implements Availability, java.io.Serializable {
    String db_name;
    DatabaseConnector db;
    
    public AvailabilityImpl(String host, String db, String user, String pw) throws java.rmi.RemoteException {
        super();
        db_name = db;
        this.db = new DatabaseConnector(host, db, user, pw);
    }
    
    /**
     * Returns available products
     * 
     * @return
     * @throws java.rmi.RemoteException
     */
    public Vector<String> checkAvailability() throws java.rmi.RemoteException {
        Vector<String> request = new Vector();
        
        try {
            db.connect();
            Statement stmt = db.getStatement();
            ResultSet rs = stmt.executeQuery("select shop, product from " + db_name + " where available = 1");
            
            while (rs.next()){
                String shop = rs.getString("shop");
                String product = rs.getString("product");
                    
                request.add("Shop: " + shop + ", Product: " + product + ".");
            }
            
            db.disconnect();
            
            return request;
        }
        
        catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problems retrieving available products from database");
        }
        
        return null;
    }
    
    /**
     * Returns current product necessities
     * 
     * @return
     * @throws java.rmi.RemoteException
     */
    public Vector<String> checkNecessities() throws java.rmi.RemoteException {
        Vector<String> request = new Vector();
        
        try {
            db.connect();
            Statement stmt = db.getStatement();
            ResultSet rs = stmt.executeQuery("select product from " + db_name + " where available = 0");
            
            while (rs.next()) {
                String product = rs.getString("product");
                
                request.add("Product needed: " + product + ".");
            }
            
            db.disconnect();
            
            return request;
        }
        
        catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problems retrieving product necessities from database");
        }
        
        return null;
    }
    
    /**
     * Updates the database with the given product necessity if it isn't already in the database
     * 
     * @param product
     * @throws java.rmi.RemoteException
    */
    public void requestAvailability(String product) throws java.rmi.RemoteException {
        
    }
    
    /**
     * Updates the database with the given product to a given shop if it isn't already in the database
     * 
     * @param product
     * @param shop
     * @throws java.rmi.RemoteException 
     */
    public void confirmAvailability(String product, String shop) throws java.rmi.RemoteException {
        
    }
    
}
