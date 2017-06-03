package pong;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class GUI extends JFrame{

	private static final long serialVersionUID=1L;
	private int winW;
	private Color strColor=null;
	private Player player1=null;
	private Player player2=null;
	private Ball ball=null;

	GUI(int winW, int winH, Color bgColor, Color strColor, Ball ball, Player player1, Player player2){
		super("Pong Game");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(winW,winH);
		setLocationRelativeTo(null);
		setBackground(bgColor);
		setResizable(false);
		setVisible(true);
		addKeyListener(new KeyAdapter(){
			@Override
			public void keyPressed(KeyEvent e){
				switch(e.getKeyCode()){
					case KeyEvent.VK_W:    player1.setSpeed(-1); break;
					case KeyEvent.VK_S:    player1.setSpeed(1);  break;
					case KeyEvent.VK_UP:   player2.setSpeed(-1); break;
					case KeyEvent.VK_DOWN: player2.setSpeed(1);  break;
				}
			}
			@Override
			public void keyReleased(KeyEvent e){
				switch(e.getKeyCode()){
					case KeyEvent.VK_W:    player1.setSpeed(0); break;
					case KeyEvent.VK_S:    player1.setSpeed(0); break;
					case KeyEvent.VK_UP:   player2.setSpeed(0); break;
					case KeyEvent.VK_DOWN: player2.setSpeed(0); break;
				}
			}
		});
		this.winW=winW;
		this.strColor=strColor;
		this.player1=player1;
		this.player2=player2;
		this.ball=ball;
	}

	@Override
	public void paint(Graphics g){
		Image img=createImage(getWidth(),getHeight());
		Graphics g2=img.getGraphics();
		ball.draw(g2);
		player1.draw(g2);
		player2.draw(g2);
		g2.setColor(strColor);
		g2.setFont(new Font("Arial",Font.BOLD,20));
		g2.drawString(Integer.toString(player1.getScore()),50,50);
		g2.drawString(Integer.toString(player2.getScore()),winW-50,50);
		repaint();
		g.drawImage(img,0,0,this);
	}

}
