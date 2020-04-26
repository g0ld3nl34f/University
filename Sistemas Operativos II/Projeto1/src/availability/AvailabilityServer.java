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
    
    public static void main(String args[]) {
        //Initialize remote object invocation here
        if (args.length != 2){
            System.out.println("Need to especify registryPort and serverPort: java availability.AvailabilityServer registryPort serverPort");
            System.exit(1);
        }
        
        try {
            int regPort = Integer.parseInt(args[0]);
            int serverPort = Integer.parseInt(args[1]);
            
            PropertyValues pv = new PropertyValues("server_database.properties");
            Properties info = pv.getPropertiesValues();
            
            String host = info.getProperty("host");
            String db = info.getProperty("db");
            String user = info.getProperty("user");
            String pw = info.getProperty("pw");
            
            Availability obj = new AvailabilityImpl(host, db, user, pw);
            
            java.rmi.registry.LocateRegistry.createRegistry(regPort);
            
            java.rmi.registry.Registry registry = java.rmi.registry.LocateRegistry.getRegistry(regPort);
            
            registry.rebind("availability", obj);
            
            System.out.println("Remote object ready!"); 
            
            obj.initializeAvailabilityDataBase();
            obj.initializeRequestsDataBase();
            
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

class PropertyValues {
    String filename;
    
    public PropertyValues(String filename) {
        this.filename = filename;
    }
    
    public Properties getPropertiesValues() {
        try {
            Properties prop = new Properties();
            
            InputStream is = getClass().getClassLoader().getResourceAsStream(filename);
            
            if (is != null) {
                prop.load(is);
                System.out.println("Properties file loaded.");
                return prop;
            }
            
            else {
                System.out.println("Properties file not found.");
                return null;
            }
        }
        
        catch (IOException e) {
            e.printStackTrace();
        }
        
        return null;
    }
}
