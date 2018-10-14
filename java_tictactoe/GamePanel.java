package tictactoe;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;

public class GamePanel extends JPanel{

	private static final long serialVersionUID=1L;
	private static final int[] scoresPlayer={0,2,49,199,5999};
	private static final int[] scoresComputer={0,3,50,200,6000};

	private GUI gui;
	private int gameSize;
	private int status;
	private int[][] table=null;
	private int[] winPos=new int[5];

	GamePanel(int gameSize){
		this.gameSize=gameSize;
		status=0;
		table=new int[gameSize][gameSize];
		for(int i=0;i<gameSize;i++) for(int j=0;j<gameSize;j++) table[i][j]=0;
		setLayout(new GridLayout(gameSize,gameSize,1,1));
		setBackground(new Color(49,54,59));
		for(int i=0;i<gameSize;i++){
			for(int j=0;j<gameSize;j++){
				JButton btn=new JButton();
				add(btn);
				btn.setBackground(new Color(121,211,255));
				btn.setMargin(new Insets(0,0,0,0));
				btn.setFont(new Font("Monospace",Font.BOLD,30));
				btn.setFocusPainted(false);
				btn.addMouseListener(new MouseAdapter(){
					@Override
					public void mousePressed(MouseEvent e){
						if((e.getModifiers()&MouseEvent.BUTTON1_MASK)!=0){
							if(status!=0 || !(btn.getText().equals(""))) return;
							btn.setForeground(Color.RED);
							btn.setText("X");
							int pos;
							for(pos=0;pos<getComponentCount();pos++) if(getComponent(pos)==btn) break;
							int x=pos%gameSize;
							int y=pos/gameSize;
							table[x][y]=1;
							pos=computerPick();
							((JButton)getComponent(pos)).setForeground(Color.ORANGE);
							((JButton)getComponent(pos)).setText("O");
							status=checkWin();
							if(status==0) return;
							if(status==1)
								gui.setStatus("You Win!", Color.GREEN);
							else if(status==2)
								gui.setStatus("Computer Wins!", Color.RED);
							for(pos=0;pos<getComponentCount();pos++)
								if((pos!=winPos[0])&&(pos!=winPos[1])&&(pos!=winPos[2])&&(pos!=winPos[3])&&(pos!=winPos[4]))
										((JButton)getComponent(pos)).setForeground(Color.GRAY);
						}
					}
				});
			}
		}
	}

	public void setGUI(GUI gui){
		this.gui=gui;
	}

	private int computerPick(){
		/* az egyes mezok hasznossaganak kiszamitasa */
		int[][] score=new int[gameSize][gameSize];
		int player, computer, s;
		for(int y=0;y<gameSize;y++)
			for(int x=0;x<gameSize;x++){
				score[x][y]=0;
			}		
		for(int y=0;y<gameSize;y++) //vizszintesen
			for(int x=0;x<gameSize-4;x++){
				player=computer=s=0;
				for(int i=0;i<=4;i++){
					if(table[x+i][y]==1)
						player++;
					else if(table[x+i][y]==2)
						computer++;
				}
				if(computer==0) s=scoresPlayer[player];
				if(player==0) s=scoresComputer[computer];
				for(int i=0;i<=4;i++) if(table[x+i][y]==0) score[x+i][y]+=s;
			}
		for(int y=0;y<gameSize-4;y++) //fuggolegesen
			for(int x=0;x<gameSize;x++){
				player=computer=s=0;
				for(int i=0;i<=4;i++){
					if(table[x][y+i]==1)
						player++;
					else if(table[x][y+i]==2)
						computer++;
				}
				if(computer==0) s=scoresPlayer[player];
				if(player==0) s=scoresComputer[computer];
				for(int i=0;i<=4;i++) if(table[x][y+i]==0) score[x][y+i]+=s;
			}
		for(int y=0;y<gameSize-4;y++) //mellekatloban
			for(int x=4;x<gameSize;x++){
				player=computer=s=0;
				for(int i=0;i<=4;i++){
					if(table[x-i][y+i]==1)
						player++;
					else if(table[x-i][y+i]==2)
						computer++;
				}
				if(computer==0) s=scoresPlayer[player];
				if(player==0) s=scoresComputer[computer];
				for(int i=0;i<=4;i++) if(table[x-i][y+i]==0) score[x-i][y+i]+=s;
			}
		for(int y=0;y<gameSize-4;y++) //foatloban
			for(int x=0;x<gameSize-4;x++){
				player=computer=s=0;
				for(int i=0;i<=4;i++){
					if(table[x+i][y+i]==1)
						player++;
					else if(table[x+i][y+i]==2)
						computer++;
				}
				if(computer==0) s=scoresPlayer[player];
				if(player==0) s=scoresComputer[computer];
				for(int i=0;i<=4;i++) if(table[x+i][y+i]==0) score[x+i][y+i]+=s;
			}
		/* a maximalis hasznossagu mezok kozul veletlenszeruen valasztunk */
		int max=0, maxcnt=0;
		for(int y=0;y<gameSize;y++)
			for(int x=0;x<gameSize;x++)
				if(table[x][y]==0){
					if(score[x][y]==max)
						maxcnt++;
					else if(score[x][y]>max){
						max=score[x][y];
						maxcnt=1;
					}
				}
		Random rand=new Random();
		maxcnt=rand.nextInt(maxcnt);
		int x=0, y=0;
		boolean found=false;
		for(y=0;y<gameSize;y++){
			for(x=0;x<gameSize;x++){
				if(score[x][y]==max){
					if(maxcnt==0){
						found=true;
						break;
					}
					maxcnt--;
				}
			}
			if(found) break;
		}
		/* a valasztott mezobe lepunk */
		table[x][y]=2;
		return y*gameSize+x;
	}

	private int checkWin(){
		for(int y=0;y<gameSize;y++) //vizszintesen
			for(int x=0;x<gameSize-4;x++)				
				if((table[x][y]==1 && table[x+1][y]==1 && table[x+2][y]==1 && table[x+3][y]==1 && table[x+4][y]==1)||(table[x][y]==2 && table[x+1][y]==2 && table[x+2][y]==2 && table[x+3][y]==2 && table[x+4][y]==2)){
					winPos[0]=y*gameSize+x; winPos[1]=y*gameSize+x+1; winPos[2]=y*gameSize+x+2; winPos[3]=y*gameSize+x+3; winPos[4]=y*gameSize+x+4;
					return table[x][y];
				}
		for(int y=0;y<gameSize-4;y++) //fuggolegesen
			for(int x=0;x<gameSize;x++)
				if((table[x][y]==1 && table[x][y+1]==1 && table[x][y+2]==1 && table[x][y+3]==1 && table[x][y+4]==1)||(table[x][y]==2 && table[x][y+1]==2 && table[x][y+2]==2 && table[x][y+3]==2 && table[x][y+4]==2)){
					winPos[0]=y*gameSize+x; winPos[1]=(y+1)*gameSize+x; winPos[2]=(y+2)*gameSize+x; winPos[3]=(y+3)*gameSize+x; winPos[4]=(y+4)*gameSize+x; 
					return table[x][y];
				}
		for(int y=0;y<gameSize-4;y++) //mellekatloban
			for(int x=4;x<gameSize;x++)
				if((table[x][y]==1 && table[x-1][y+1]==1 && table[x-2][y+2]==1 && table[x-3][y+3]==1 && table[x-4][y+4]==1)||(table[x][y]==2 && table[x-1][y+1]==2 && table[x-2][y+2]==2 && table[x-3][y+3]==2 && table[x-4][y+4]==2)){
					winPos[0]=y*gameSize+x; winPos[1]=(y+1)*gameSize+x-1; winPos[2]=(y+2)*gameSize+x-2; winPos[3]=(y+3)*gameSize+x-3; winPos[4]=(y+4)*gameSize+x-4; 
					return table[x][y];
				}
		for(int y=0;y<gameSize-4;y++) //foatloban
			for(int x=0;x<gameSize-4;x++)
				if((table[x][y]==1 && table[x+1][y+1]==1 && table[x+2][y+2]==1 && table[x+3][y+3]==1 && table[x+4][y+4]==1)||(table[x][y]==2 && table[x+1][y+1]==2 && table[x+2][y+2]==2 && table[x+3][y+3]==2 && table[x+4][y+4]==2)){
					winPos[0]=y*gameSize+x; winPos[1]=(y+1)*gameSize+x+1; winPos[2]=(y+2)*gameSize+x+2; winPos[3]=(y+3)*gameSize+x+3; winPos[4]=(y+4)*gameSize+x+4;
					return table[x][y];
				}
		return 0;
	}
	
}
