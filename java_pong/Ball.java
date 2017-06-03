package pong;

import java.awt.*;

public class Ball implements Runnable{

	private int xMin;
	private int xMax;
	private int yMin;
	private int yMax;
	private int dx;
	private int dy;
	private Color color=null;
	private Player player1=null;
	private Player player2=null;
	private Rectangle box=null;

	Ball(int x, int y, int d, Color color, int winW, int winH, Player player1, Player player2){
		this.xMin=0;
		this.xMax=winW-d;
		this.yMin=d;
		this.yMax=winH-d;
		dx=1;
		dy=1;
		this.color=color;
		this.player1=player1;
		this.player2=player2;
		box=new Rectangle(x,y,d,d);
	}

	public void draw(Graphics g){
		g.setColor(color);
		g.fillOval(box.x,box.y,box.width,box.height);
	}

	public void update(){
		if(box.intersects(player1.getPaddleRect())) dx=1;
		if(box.intersects(player2.getPaddleRect())) dx=-1;
		box.x+=dx;
		box.y+=dy;
		if(box.x<=xMin){
			dx=1;
			player2.incScore();
		}
		else if(box.x>=xMax){
			dx=-1;
			player1.incScore();
		}
		if(box.y<=yMin)
			dy=1;
		else if(box.y>=yMax)
			dy=-1;
	}

	@Override
	public void run(){
		try{
			while(true){
				update();
				Thread.sleep(6);
			}
		}
		catch(Exception e){
			System.err.println(e.getMessage());
		}
	}

}
