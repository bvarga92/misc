package pong;

import java.awt.Color;

public class Main{

	private static final int   winW=500;
	private static final int   winH=300;
	private static final Color bgColor=new Color(22,40,40);
	private static final Color strColor=new Color(0,235,238);
	private static final int   playerW=8;
	private static final int   playerH=60;
	private static final Color player1Color=new Color(0,235,238);
	private static final Color player2Color=new Color(0,235,238);
	private static final int   ballD=12;
	private static final Color ballColor=new Color(0,235,238);

	public static void main(String[] args){
		Player player1=new Player(10,(winH-playerH)/2,playerW,playerH,winH,player1Color);
		Player player2=new Player(winW-10-playerW,(winH-playerH)/2,playerW,playerH,winH,player2Color);
		Ball ball=new Ball((winW-ballD)/2,(winH-ballD)/2,ballD,ballColor,winW,winH,player1,player2);
		new GUI(winW,winH,bgColor,strColor,ball,player1,player2);
		new Thread(ball).start();
		new Thread(player1).start();
		new Thread(player2).start();
	}

}
