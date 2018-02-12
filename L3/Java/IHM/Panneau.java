import javax.swing.JPanel;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import java.awt.*;

public class Panneau extends JPanel {

  private int posX = -50;
  private int posY = -50;


  public void paintComponent(Graphics g){

    g.setColor(Color.white);
    g.fillRect(0,0,this.getWidth(),this.getHeight());

    g.setColor(Color.red);
    g.fillOval(posX,posY,50,50);

    /* Dégradé de couleur (Graphics2D) */

/*
    Graphics2D g2d = (Graphics2D)g;
    GradientPaint gp, gp2, gp3, gp4, gp5, gp6;
    gp = new GradientPaint(0, 0, Color.RED, 20, 0, Color.magenta, true);
    gp2 = new GradientPaint(20, 0, Color.magenta, 40, 0, Color.blue, true);
    gp3 = new GradientPaint(40, 0, Color.blue, 60, 0, Color.green, true);
    gp4 = new GradientPaint(60, 0, Color.green, 80, 0, Color.yellow, true);
    gp5 = new GradientPaint(80, 0, Color.yellow, 100, 0, Color.orange, true);
    gp6 = new GradientPaint(100, 0, Color.orange, 120, 0, Color.red, true);

    g2d.setPaint(gp);
    g2d.fillRect(0, 0, 20, this.getHeight());
    g2d.setPaint(gp2);
    g2d.fillRect(20, 0, 20, this.getHeight());
    g2d.setPaint(gp3);
    g2d.fillRect(40, 0, 20, this.getHeight());
    g2d.setPaint(gp4);
    g2d.fillRect(60, 0, 20, this.getHeight());
    g2d.setPaint(gp5);
    g2d.fillRect(80, 0, 20, this.getHeight());
    g2d.setPaint(gp6);
    g2d.fillRect(100, 0, 40, this.getHeight());

*/

    /* Utilisations de Graphics */

/*
    int x1 = this.getWidth()/4;
    int y1 = this.getHeight()/4;
    int h1 = this.getWidth()/2;
    int l1 = this.getHeight()/2;
    int x[] = {x1,x1+h1/2,x1+h1};
    int y[] = {y1,y1/2,y1};
    String s = "Ceci est une maison";
    Font font = new Font("Comic Sans MS", Font.BOLD, 20);

    //.setColor(Color.red);
    //g.setFont(font);

    try{
      Image img = ImageIO.read(new File("image.jpg"));
      //g.drawImage(img, 0, 0, this);
      //Pour une image de fond
      g.drawImage(img, 0, 0, this.getWidth(), this.getHeight(), this);

    }catch (IOException e){
      e.printStackTrace();
    }

    g.fillOval(x1,y1,h1,l1);
    g.drawOval(x1,y1,h1,l1);
    g.drawRect(x1,y1,h1,l1);
    g.drawRoundRect(x1,y1,h1,l1,5,5);
    g.drawLine(x1,y1,h1+x1,y1+l1);
    g.drawLine(h1+x1,y1,x1,y1+l1);
    g.drawPolygon(x,y,3);
    g.drawString(s,x1,y1+l1+25);

  */

  }

  public int getPosX(){
    return posX;
  }

  public int getPosY(){
    return posY;
  }

  public void setPosX(int posX){
    this.posX = posX;
  }

  public void setPosY(int posY){
    this.posY = posY;
  }

}
