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
import java.util.*;
import java.rmi.server.UnicastRemoteObject;
import java.sql.*;

public class AvailabilityImpl extends UnicastRemoteObject implements Availability, java.io.Serializable {
    DatabaseConnector db;
    
    public AvailabilityImpl(String host, String db, String user, String pw) throws java.rmi.RemoteException {
        super();
        this.db = new DatabaseConnector(host, db, user, pw);
    }
    
    /**
     * Initialize availability database
     * 
     * @throws java.rmi.RemoteException
     */
    @Override
    public void initializeAvailabilityDataBase() throws java.rmi.RemoteException{
        try {
            db.connect();
            Statement stmt = db.getStatement();
            
            stmt.execute("create table availability(product varchar(50), shop varchar(50))");
            
            db.disconnect();
        }
        
        catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problem initializing availability database");
        }
    }
    
    /**
     * Initialize requests database
     * 
     * @throws java.rmi.RemoteException
     */
    @Override
    public void initializeRequestsDataBase() throws java.rmi.RemoteException {
        try {
            db.connect();
            Statement stmt = db.getStatement();
            
            stmt.execute("create table requests(requestid varchar(50), product varchar(50))");
            
            db.disconnect();
        }
        
        catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problem initializing requests database");
        }
    }
    
    /*************************************************************************************************/
    
    /**
     * Returns available products
     * 
     * @return
     * @throws java.rmi.RemoteException
     */
    @Override
    public Vector<String> checkAvailability() throws java.rmi.RemoteException {
        Vector<String> request = new Vector();
        
        try {
            db.connect();
            Statement stmt = db.getStatement();
            ResultSet rs = stmt.executeQuery("select shop, product from availability");
            
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
    
    /*************************************************************************************************/
    
    /**
     * Returns current product necessities
     * 
     * @return
     * @throws java.rmi.RemoteException
     */
    @Override
    public Vector<String> checkNecessities() throws java.rmi.RemoteException {
        Vector<String> request = new Vector();
        
        try {
            db.connect();
            Statement stmt = db.getStatement();
            ResultSet rs = stmt.executeQuery("select product from requests");
            
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
    
    /*************************************************************************************************/
    
    /**
     * Updates the database with the given product to a given shop if it isn't already in the database
     * 
     * @param product
     * @param shop
     * @return
     * @throws java.rmi.RemoteException 
     */
    @Override
    public boolean confirmAvailability(String product, String shop) throws java.rmi.RemoteException {
        try {
            db.connect();
            Statement stmt = db.getStatement();
            ResultSet rs = stmt.executeQuery("select * from availability where product = '" + product + "'");
            
            if (!rs.isClosed() && rs.next()) {
                db.disconnect();
                
                return false;
            }
            
            stmt.executeUpdate("insert into availability values('" + product +"', '" + shop + "')");
            
            db.disconnect();
            
            return true;
        }
        
        catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problem updating or adding the given product");
        }
        
        return false;
    }
    
    /**
     * Check if given product is available
     * 
     * @param product
     * @return
     * @throws java.rmi.RemoteException
     */
    @Override
    public boolean requestAvailability(String product) throws java.rmi.RemoteException {
        try {
            db.connect();
            Statement stmt = db.getStatement();
            ResultSet rs = stmt.executeQuery("select * from availability where product = '" + product +"'");
            
            if (!rs.next()){
                db.disconnect();
                return false;
            }
            
            db.disconnect();
            return true;
        }
        
        catch (Exception e) {
            e.printStackTrace();
        }
        
        return false;
    }
    
    /**
     * Returns shops where a given product is available
     * 
     * @param product
     * @return
     * @throws java.rmi.Remoteexception
     */
    public Vector<String> getShops(String product) throws java.rmi.RemoteException {
        Vector<String> request = new Vector<String>();
        
        try {
            db.connect();
            Statement stmt = db.getStatement();
            ResultSet rs = stmt.executeQuery("select shop from availability where product = '" + product + "'");
            
            if (!rs.isClosed() && rs.next()) {
                String shop = rs.getString("shop");
                request.add(shop);
                
                while (rs.next()) {
                    request.add(shop);
                }

                db.disconnect();

                return request;
            }
            
            db.disconnect();
            return null;
            
        }
        
        catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problems retrieving shops where the given product is available from database");
        }
        
        return null;
    }
    
    /**
     * Update requests table with new request
     * 
     * @param requestID
     * @throws java.rmi.RemoteException
     */
    @Override
    public void updateRequests(String requestID) throws java.rmi.RemoteException{
        try {
            db.connect();
            Statement stmt = db.getStatement();
            
            String[] request = requestID.split(",");
            
            stmt.executeUpdate("insert into requests values('" + requestID + "', '" + request[1] + "')");
        }
        
        catch (Exception e) {
            e.printStackTrace();
            System.err.println("Could't set request");
        }
    }
    
    /**
     * Return all requests in requests table
     * 
     * @param product
     * @return
     * @throws java.rmi.RemoteException
     */
    @Override
    public Vector<String> getRequests(String product) throws java.rmi.RemoteException{
        Vector<String> requests = new Vector<String>();
        
        try {
            db.connect();
            Statement stmt = db.getStatement();
            ResultSet rs = stmt.executeQuery("select requestid from requests where product = '" + product + "'");
            
            while (!rs.isClosed() && rs.next()) {
                String requestid = rs.getString("requestid");
                
                requests.add(requestid);
                
                stmt.executeUpdate("delete from requests where requestid = '" + requestid + "'");
            }
            
            db.disconnect();
            
            return requests;
        }
        
        catch (Exception e) {
            e.printStackTrace();
            System.err.println("Could't get requests");
        }
        
        return null;
    }
}
