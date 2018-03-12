import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.*;

public class Serveur{

	private ServerSocket s = null;
	private String IP = "127.0.0.1";
	private boolean isRunning = true;
	private int port = 5896;
	private List<Socket> lSock = null;
	private List<String> uNames = null;

	public Serveur(){
		try{
            s = new ServerSocket(port,100,InetAddress.getByName(IP));
            lSock = new ArrayList<Socket>();
            uNames = new ArrayList<String>();
        }catch (UnknownHostException e){
         	e.printStackTrace();
        }catch (IOException e){
            System.err.println("Le port est déjà utilisé ! ");
        }
	}

	public void open(){
      
     	Thread t = new Thread(new Runnable(){
         	public void run(){
            	while(isRunning == true){

               
               		try{
                  
                  		Socket client = s.accept();
                  		System.out.println("Connexion cliente reçue.");                  
                  		Thread t = new Thread(new ReponseServeur(client,lSock,uNames));
                  		t.start();
                  
               		}catch (IOException e){
                  		e.printStackTrace();
               		}
            	}
            
	            try{
	              	s.close();
	            }catch (IOException e){
	               	e.printStackTrace();
	              	s = null;
	            }
        	}

    	});
      
      	t.start();

   }

   public void close(){
		isRunning = false;
   } 

}