/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package availability;

import java.util.*;

/**
 *
 * @author l40011
 */
public interface Availability extends java.rmi.Remote{
    public Vector<String> checkAvailability() throws java.rmi.RemoteException;
    
    public Vector<String> checkNecessities() throws java.rmi.RemoteException;
    
    public boolean confirmAvailability(String product, String shop) throws java.rmi.RemoteException;
    
    public boolean requestAvailability(String product) throws java.rmi.RemoteException;
    
    public Vector<String> getShops(String product) throws java.rmi.RemoteException;
    
    public void updateRequests(String requestId) throws java.rmi.RemoteException;
    
    public Vector<String> getRequests(String product) throws java.rmi.RemoteException;
}
