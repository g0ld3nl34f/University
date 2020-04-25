/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package availability;

import java.io.*;
import java.net.*;
import java.util.*;

/**
 *
 * @author l40011
 */
public class AvailabilityServer {
    public AvailabilityServer() {}
    
    private static HashMap<String, Socket> getUserData() {
        File data = new File("userdata");
        
        try {
            if (data.createNewFile()) {
                System.out.println("User data file created.");
            
                return null;
            }
        }
        
        catch (IOException e) {
            e.printStackTrace();
        }
        
        try {
            FileInputStream fis = new FileInputStream(data);
            ObjectInputStream ois = new ObjectInputStream(fis);
        
            HashMap<String, Socket> users = (HashMap<String, Socket>) ois.readObject();
            
            System.out.println("User data retrieved.");
            
            ois.close();
            fis.close();
            
            return users;
        }
        
        catch (IOException e) {
            e.printStackTrace();
        }
        
        catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        
        return null;
    }
    
    
    //method for concurrent request notification
    
    public static void main(String args[]) {
        //Initialize remote object invocation here
        /*if (args.length != 1){
            System.out.println("Need to especify registryPort: java availability.AvailabilityServer registryPort");
            System.exit(1);
        }*/
        
        try {
            int regPort = 9000;//Integer.parseInt(args[0]);
            int serverPort = 8000;
            
            String host = "localhost";
            String db = "availbd";
            String user = "availserver";
            String pw = "password";
            
            Availability obj = new AvailabilityImpl(host, db, user, pw);
            
            java.rmi.registry.LocateRegistry.createRegistry(regPort);
            
            java.rmi.registry.Registry registry = java.rmi.registry.LocateRegistry.getRegistry(regPort);
            
            registry.rebind("availability", obj);
            
            System.out.println("Remote object ready!"); 
            
            HashMap<String, Socket> userData = new HashMap<String, Socket>();
            System.out.println("Userdata ready");
            
            try {
                ServerSocket server = new ServerSocket(serverPort);
                
                while (true) {
                    Socket data = server.accept();
                    BufferedReader br = new BufferedReader(new InputStreamReader(data.getInputStream()));
                    
                    String message = br.readLine();
                    
                    String[] toProcess = message.split(" ");
                    
                    if (toProcess[1].equals("request")) {
                        obj.updateRequests(toProcess[0]);
                        
                        userData.put(toProcess[0], data);
                    }
                    
                    if (toProcess[1].equals("available")){
                        String productToNotify = toProcess[0];
                        Vector<String> requests = obj.getRequests(productToNotify);
                        
                        if (requests != null) {
                            DataOutputStream dos;
                            String userRequest;
                            String[] ur;
                            
                            for (int j = 0; j < requests.size(); j++) {
                                userRequest = requests.get(j);
                                ur = userRequest.split(",");
                                
                                dos = new DataOutputStream(userData.get(userRequest).getOutputStream());
                                
                                String msg = toProcess[0] + " available.";
                                
                                dos.writeUTF(msg);
                            }
                        }
                    }
                    
                }
            }
            
            catch (Exception e) {
                e.printStackTrace();
                System.err.println("Dont work");
            }
        }
        
        catch (Exception e) {
            e.printStackTrace();
        }
    }
            
}
