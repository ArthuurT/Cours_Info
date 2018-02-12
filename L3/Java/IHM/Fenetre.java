import java.awt.Color;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Fenetre extends JFrame {

  private Panneau pan = new Panneau();

  public Fenetre(){
    this.setTitle("Animation");
    this.setSize(300, 300);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.setLocationRelativeTo(null);
    this.setContentPane(pan);
    this.setVisible(true);
    go();

  }

  private void go(){
    boolean toucheV = false;
    boolean toucheH = false;
    int x = pan.getPosX(), y = pan.getPosY();
    while(true){

      if(y < 1) toucheV = false;
      if(y > pan.getHeight() - 50) toucheV = true;

      if(x < 1) toucheH = false;
      if(x > pan.getWidth() - 50) toucheH = true;


      if(!toucheV)y++;
      else y--;

      if(!toucheH)x++;
      else x++;


      pan.setPosX(x);
      pan.setPosY(y);
      pan.repaint();
      try {
        Thread.sleep(5);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }




}
