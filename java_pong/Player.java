package pong;

import java.awt.*;

public class Player implements Runnable{

	private int yMin;
	private int yMax;
	private int dy;
	private int score;
	private Color color=null;
	private Rectangle paddle=null;

	Player(int x, int y, int w, int h, int winH, Color color){
		this.yMin=10;
		this.yMax=winH-h-10;
		this.dy=0;
		this.score=0;
		this.color=color;
		paddle=new Rectangle(x,y,w,h);
	}

	public void incScore(){
		score++;
	}

	public int getScore(){
		return score;
	}

	public Rectangle getPaddleRect(){
		return paddle;
	}

	public void setSpeed(int dy){
		this.dy=dy;
	}

	public void draw(Graphics g){
		g.setColor(color);
		g.fillRect(paddle.x,paddle.y,paddle.width,paddle.height);
	}

	public void update(){
		paddle.y+=dy;
		if(paddle.y<yMin)
			paddle.y=yMin;
		else if(paddle.y>yMax)
			paddle.y=yMax;
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
