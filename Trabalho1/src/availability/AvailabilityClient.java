/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package availability;

import java.util.Vector;

/**
 *
 * @author l40011
 */
public class AvailabilityClient {
    public AvailabilityClient() {}
    
    private static void getAvailableProducts(Availability availability) throws java.rmi.RemoteException{
        Vector<String> request = availability.checkAvailability();
        
        for (int i = 0; i < request.size(); i++){
            System.out.println(request.get(i));
        }
    }
    
    public static void main(String args[]){
        if (args.length != 2){
            System.out.println("Need to especify registryPort and registryHost: java availability.AvailabilityClient registryPort registryHost");
            System.exit(1);
        }
        
        String regPort = args[0];
        String regHost = args[1];
        
        try {
            Availability availability = (Availability) java.rmi.Naming.lookup("rmi://" + regHost + ":" + regPort + "/availability");
            
            getAvailableProducts(availability);        
        }
        
        catch (Exception e){
            e.printStackTrace();
        }
    }
    
}
