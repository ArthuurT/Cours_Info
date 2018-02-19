import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.io.IOException;

public class CloseSocket {

   public static void main(String[] args){
      Socket sock = null;
      try {
         //On se connecte à OpenClassrooms
         sock = new Socket("www.openclassrooms.com", 80);

         //...
      } catch (UnknownHostException e) {
         e.printStackTrace();
      } catch (IOException e) {
         e.printStackTrace();
      }
      finally{
         if(sock != null){
            try {
               sock.close();
            } catch (IOException e) {
               e.printStackTrace();
               sock = null;
            }
         }
      }
   }
}
