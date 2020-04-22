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
public class AvailabilityServer {
    public AvailabilityServer() {}
    
    public static void main(String args[]) {
        //Initialize remote object invocation here
        if (args.length != 1){
            System.out.println("Need to especify registryPort: java availability.AvailabilityServer registryPort");
            System.exit(1);
        }
        
        try {
            int regPort = Integer.parseInt(args[0]);
            String host = "localhost";
            String db = "availdb";
            String user = "availserver";
            String pw = "password";
            
            Availability obj = new AvailabilityImpl(host, db, user, pw);
            
            java.rmi.registry.LocateRegistry.createRegistry(regPort);
            
            java.rmi.registry.Registry registry = java.rmi.registry.LocateRegistry.getRegistry(regPort);
            
            registry.rebind("availability", obj);
            
            System.out.println("Server ready!");
        }
        
        catch (Exception e) {
            e.printStackTrace();
        }
    }
            
}
