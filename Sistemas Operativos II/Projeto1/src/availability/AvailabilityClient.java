/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package availability;

import java.util.*;
import java.io.*;
import java.net.*;

/**
 *
 * @author l40011
 */
public class AvailabilityClient {
    public AvailabilityClient() {}
    
    private static File resumePreviousSession(Availability availability) {
        File data = new File("session.txt");
        
        try {
            if (data.createNewFile()) {
                return data;
            }
            
            FileReader fr = new FileReader(data);
            BufferedReader br = new BufferedReader(fr);
            String lineRead;
            
            while ((lineRead = br.readLine()) != null){
                if (lineRead.equals("4")) {
                    System.out.println(lineRead);
                    if((lineRead = br.readLine()) != null) {
                        System.out.println(lineRead);
                        
                        if ((lineRead = br.readLine()) != null) {
                            System.out.println(lineRead);
                            
                            if((lineRead = br.readLine()) != null) {
                                System.out.println(lineRead);
                                System.out.println("> Checking if the product you requested is available...");
                            
                                String[] checkProduct = lineRead.split(" ");

                                if (availability.requestAvailability(checkProduct[1])) {
                                    Vector<String> shopsAvailableAt = availability.getShops(checkProduct[1]);

                                    System.out.print("> Product available at these shops: " + shopsAvailableAt.get(0));

                                    for (int i = 1; i < shopsAvailableAt.size(); i++) {
                                        System.out.print(", " + shopsAvailableAt.get(i));
                                    }

                                    System.out.println(".");
                                }
                                
                                else {
                                    System.out.println("> " + checkProduct[1] + " still not available.");
                                }
                            }
                            
                        }
                        
                        else {
                            break;
                        }
                    }
                    
                    else {
                        break;
                    }
                }
                
                else {
                    System.out.println(lineRead);
                }
            }
            
            br.close();
            fr.close();
            
            return data;
        }
        
        catch (IOException e) {
            e.printStackTrace();
        }
        
        return null;
    }
    
    private static void deleteFile(File session) {
        session.delete();
    }
    
    private static void getAvailableProducts(Availability availability, DataOutputStream fw) throws java.rmi.RemoteException {
        try {
            Vector<String> request = availability.checkAvailability();
            String prompt = "> Products available:\n\n";

            System.out.print(prompt);
            fw.write(prompt.getBytes());

            if (request != null) {
                for (int i = 0; i < request.size(); i++) {
                    System.out.println("> " + request.get(i));
                    fw.write(("> " + request.get(i) + "\n").getBytes());
                }
            }
            
            System.out.println();
        }
        
        catch (IOException e) {
            e.printStackTrace();
        }
        
    }
    
    private static void getRequestedProducts(Availability availability, DataOutputStream fw) throws java.rmi.RemoteException {
        try{
            Vector<String> request = availability.checkNecessities();
            String prompt = "> Products requested:\n\n";

            System.out.print(prompt);
            fw.write(prompt.getBytes());

            if (request != null) {
                for (int i = 0; i < request.size(); i++) {
                    System.out.println("> " + request.get(i));
                    fw.write(("> " + request.get(i) + "\n").getBytes());
                }
            }
            
            System.out.println();
        }
        
        catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    private static void getProductAvailability(Availability availability, DataOutputStream fw) throws java.rmi.RemoteException {
        try {
            String prompt = "> What product are you looking for?";
            System.out.println(prompt);
            fw.write((prompt + "\n").getBytes());
            
            Scanner scan = new Scanner(System.in);
            prompt = ">> ";
            System.out.print(prompt);
            String product = scan.nextLine();
            fw.write((prompt + product + "\n").getBytes());
            
            if (availability.requestAvailability(product)) {
                Vector<String> shopsAvailableAt = availability.getShops(product);
                prompt = "> Product available at these shops: ";
                
                System.out.print(prompt + shopsAvailableAt.get(0));
                fw.write((prompt + shopsAvailableAt.get(0)).getBytes());
                
                for (int i = 1; i < shopsAvailableAt.size(); i++) {
                    System.out.print(", " + shopsAvailableAt.get(i));
                    fw.write((", " + shopsAvailableAt.get(i)).getBytes());
                }

                System.out.println(".\n");
                fw.write((".\n\n").getBytes());
            }
            
            else {
                prompt = "> " + product + " not found at any shop.\n";
                System.out.println(prompt);
                fw.write((prompt).getBytes());
            }
        }
        
        catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    private static void setProductRequest(Availability availability, String host, String serverPort, String username, DataOutputStream fw) throws java.rmi.RemoteException {
        try {
            Scanner scan = new Scanner(System.in);
            String prompt = "> What product do you need?";

            System.out.println(prompt);
            fw.write((prompt + "\n").getBytes());

            prompt = ">> ";
            System.out.print(prompt);
            String product = scan.nextLine();
            fw.write((prompt + product + "\n").getBytes());

            boolean anwser = availability.requestAvailability(product);

            if (anwser) {
                prompt = "> " + product + " already available.\n";
                System.out.println(prompt);
                fw.write((prompt + "\n").getBytes());

                return;
            }

            AvailabilityNotification an = new AvailabilityNotification(host, serverPort, username, product);
            an.start();

            prompt = "> " + product + " requested.\n";
            System.out.println(prompt);
            fw.write((prompt + "\n").getBytes());
        }
        
        catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    private static void setAvailableProduct(Availability availability, String host, String serverPort, DataOutputStream fw) throws java.rmi.RemoteException {
        try {
            Scanner scan = new Scanner(System.in);
            String prompt = "> What product are you reporting availability for?";

            System.out.println(prompt);
            fw.write((prompt + "\n").getBytes());

            prompt = ">> ";
            System.out.print(prompt);
            String product = scan.nextLine();
            fw.write((prompt + product + "\n").getBytes());

            prompt = "> What shop is this product available in?";
            System.out.println(prompt);
            fw.write((prompt + "\n").getBytes());

            prompt = ">> ";
            System.out.print(prompt);
            String shop = scan.nextLine();
            fw.write((prompt + shop + "\n").getBytes());

            boolean anwser = availability.confirmAvailability(product, shop);

            if (anwser) {
                prompt = "> " + product + " was succesfuly confirmed available at " + shop + ".";
                System.out.println(prompt);
                fw.write((prompt + "\n").getBytes());

                prompt = "> Thank you for your cooperation.\n";
                System.out.println(prompt);
                fw.write((prompt + "\n").getBytes());

                try{
                    Socket notifyServer = new Socket(host, Integer.parseInt(serverPort));
                    DataOutputStream dos = new DataOutputStream(notifyServer.getOutputStream());

                    String msg = product + " available\n";
                    dos.write(msg.getBytes());
                    dos.flush();

                    notifyServer.close();
                }

                catch (Exception e) {
                    e.printStackTrace();
                    System.out.println("> Cound't notify server about availability\n");
                }
            }

            else {
                prompt = "> " +product + " already available or something went wrong.\n";
                System.out.println(prompt);
                fw.write((prompt + "\n").getBytes());
            }
        }
        
        catch (IOException e){
            e.printStackTrace();
        }
        
        
    }
    
    public static void listCommands() {
        System.out.println("> MENU:");
        System.out.println("> '1' - List available products and their locations.");
        System.out.println("> '2' - List products requested by users.");
        System.out.println("> '3' - List shops where the product you're looking for is available.");
        System.out.println("> '4' - Request a product you need.");
        System.out.println("> '5' - Inform other users where you found a product.");
        System.out.println("> 'q' - Quit programm.");
    }
    
    //Add option to add more products or more shops where the product is available
    public static void menu(Availability availability, String host, String serverPort, String username, File session) throws java.rmi.RemoteException {
        try{
            DataOutputStream fw = new DataOutputStream(new FileOutputStream(session));
            Scanner scan = new Scanner(System.in);
            String command, prompt = ">> ";
            
            listCommands();

            while (true) {
                System.out.print(prompt);
                fw.write((prompt + "\n").getBytes());
                command = scan.nextLine();
                fw.write((command + "\n").getBytes());

                switch (command){
                    case "1":
                        getAvailableProducts(availability, fw);
                        System.out.println("> To show commands enter list.");
                        break;

                    case "2":
                        getRequestedProducts(availability, fw);
                        System.out.println("> To show commands enter list.");
                        break;
                    
                    case "3":
                        getProductAvailability(availability, fw);
                        System.out.println("> To show commands enter list.");
                        break;
                        
                    case "4":
                        setProductRequest(availability, host, serverPort, username, fw);
                        System.out.println("> To show commands enter list.");
                        break;

                    case "5":
                        setAvailableProduct(availability, host, serverPort, fw);
                        System.out.println("> To show commands enter list.");
                        break;

                    case "list":
                        listCommands();
                        break;
                        
                    case "q":
                        System.out.println("> Stay safe!");
                        fw.close();
                        deleteFile(session);
                        System.exit(0);
                }
            }
        }
        
        catch (IOException e) {
            e.printStackTrace();
        }
        
    }
    
    public static void main(String args[]){
        if (args.length != 3) {
            System.out.println("> Need to especify registryPort and registryHost: java availability.AvailabilityClient registryPort registryHost serverPort");
            System.exit(1);
        }
        
        String regPort = args[0];
        String host = args[1];
        String serverPort = args[2];
        
        try {
            Scanner scanLogin = new Scanner(System.in);
            
            System.out.println("> Insert username for validation: ");
            System.out.print(">> ");
            String username = scanLogin.nextLine();
            
            while (username.equals("")){
                System.out.println();
                System.out.println("> Insert username for validation:");
                System.out.print(">> ");
                username = scanLogin.nextLine();
            }
            
            Availability availability = (Availability) java.rmi.Naming.lookup("rmi://" + host + ":" + regPort + "/availability");
            
            File session = resumePreviousSession(availability);
            
            menu(availability, host, serverPort, username, session);
            
        }
        
        catch (Exception e){
            e.printStackTrace();
        }
    }
    
}

class AvailabilityNotification extends Thread {
    String host, serverPort, username, product;
    
    public AvailabilityNotification(String host, String serverPort, String username, String product){
        this.host = host;
        this.serverPort = serverPort;
        this.username = username;
        this.product = product;
    }
    
    public void run(){
        try{
            Socket sock = new Socket(host, Integer.parseInt(serverPort));
            OutputStream os = sock.getOutputStream();
            InputStream is = sock.getInputStream();
            
            String msg = username + "," + product + " request\n";
            
            os.write(msg.getBytes());
            os.flush();
        
            byte[] b = new byte[256];
        
            int readBytes = is.read(b);
            
            String anwser = new String(b, 0, readBytes);
            
            System.out.println(anwser);
            
            sock.close();
        }
        
        catch (IOException e) {
            e.printStackTrace();
        }  
    }
}
