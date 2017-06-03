package minesweeper;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class GamePanel extends JPanel{

	private static final long serialVersionUID=1L;
	private GUI gui;
	private int gameSize;
	private int numMines;
	private int numSteps;
	private int mineCntr;
	private int[] mines=null;
	private int revealed;

	GamePanel(int gameSize, int numMines){
		this.gameSize=gameSize;
		this.numMines=this.mineCntr=numMines;
		this.numSteps=0;
		this.revealed=0;
		/* aknak elhelyezese veletlenszeruen */
		mines=new int[numMines];
		for(int i=0;i<numMines;i++){
			int mine;
			while(true){
				mine=(int)(Math.random()*gameSize*gameSize);
				int j;
				for(j=0;j<i;j++) if(mines[j]==mine) break;
				if(j==i) break;
			}
			mines[i]=mine;
		}
		/* gombok generalasa */
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
						if(!btn.isEnabled()) return;
						if((e.getModifiers()&MouseEvent.BUTTON1_MASK)!=0){ //bal egergomb
							if(!(btn.getText().equals(""))) return;
							gui.setStepCntr(++numSteps);
							int pos;
							for(pos=0;pos<getComponentCount();pos++) if(getComponent(pos)==btn) break;
							int n;
							for(n=0;n<numMines;n++) if(mines[n]==pos) break;
							if(n<numMines){ //aknara leptunk
								gameOver(pos);
							}
							else{
								reveal(pos);
								if(revealed==gameSize*gameSize-numMines) playerWins();
							}
						}
						else if((e.getModifiers()&MouseEvent.BUTTON3_MASK)!=0){ //jobb egergomb
							if(btn.getText().equals("")){
								btn.setForeground(Color.RED);
								btn.setText("!");
								gui.setMineCntr(--mineCntr);
							}
							else if(btn.getText().equals("!")){
								btn.setForeground(Color.BLUE);
								btn.setText("?");
								gui.setMineCntr(++mineCntr);
							}
							else if(btn.getText().equals("?")){
								btn.setText("");
							}
						}
					}
				});
			}
		}
	}

	public void setGUI(GUI gui){
		this.gui=gui;
	}

	public void reveal(int pos){
		/* osszeszamoljuk a szomszedos aknakat */
		int adjacent=0;
		for(int i=0;i<numMines;i++){
			if(pos-gameSize==mines[i]) //fel
				adjacent++;
			else if(pos+gameSize==mines[i]) //le
				adjacent++;
			else if((pos+1==mines[i])&&((pos+1)%gameSize!=0)&&((pos-gameSize+1)%gameSize!=0)) //jobbra
				adjacent++;
			else if((pos-1==mines[i])&&(pos%gameSize!=0)) //balra
				adjacent++;
			else if((pos-gameSize+1==mines[i])&&((pos+1)%gameSize!=0)&&((pos-gameSize+1)%gameSize!=0)) //jobbra fel
				adjacent++;
			else if((pos-gameSize-1==mines[i])&&(pos%gameSize!=0)) //balra fel
				adjacent++;
			else if((pos+gameSize+1==mines[i])&&((pos+1)%gameSize!=0)&&((pos-gameSize+1)%gameSize!=0)) //jobbra le
				adjacent++;
			else if((pos+gameSize-1==mines[i])&&(pos%gameSize!=0)) //balra le
				adjacent++;
		}
		/* beirjuk a szomszedok szamat; ha 0, akkor rekurzivan vegignezzuk a szomszedos cellakat */
		JLabel label=new JLabel("",JLabel.CENTER);
		label.setFont(new Font("Monospace",Font.BOLD,30));
		switch(adjacent){
			case 0:
				if(getComponent(pos) instanceof JButton){
					revealed++;
					remove(getComponent(pos));
					add(label,pos);
					int next;
					next=pos-gameSize; //fel
					if((next>=0)&&(next<gameSize*gameSize)) reveal(next);	
					next=pos+gameSize; //le
					if((next>=0)&&(next<gameSize*gameSize)) reveal(next);
					next=pos+1; //jobbra
					if((next>=0)&&(next<gameSize*gameSize)&&(next%gameSize!=0)) reveal(next);
					next=pos-1; //balra
					if((next>=0)&&(next<gameSize*gameSize)&&((next+1)%gameSize!=0)&&((next-gameSize+1)%gameSize!=0)) reveal(next);
					next=pos-gameSize+1; //jobbra fel
					if((next>=0)&&(next<gameSize*gameSize)&&(next%gameSize!=0)) reveal(next);
					next=pos-gameSize-1; //balra fel
					if((next>=0)&&(next<gameSize*gameSize)&&((next+1)%gameSize!=0)&&((next-gameSize+1)%gameSize!=0)) reveal(next);
					next=pos+gameSize+1; //jobbra le
					if((next>=0)&&(next<gameSize*gameSize)&&(next%gameSize!=0)) reveal(next);
					next=pos+gameSize-1; //balra le
					if((next>=0)&&(next<gameSize*gameSize)&&((next+1)%gameSize!=0)&&((next-gameSize+1)%gameSize!=0)) reveal(next);
				}
				break;
			case 1: label.setForeground(new Color(73,201,228)); break;
			case 2: label.setForeground(new Color(127,149,74)); break;
			case 3: label.setForeground(new Color(212,75,129)); break;
			case 4: label.setForeground(new Color(0,0,128)); break;
			case 5: label.setForeground(new Color(255,127,80)); break;
			case 6: label.setForeground(new Color(128,0,0)); break;
			case 7: label.setForeground(new Color(0,128,0)); break;
			case 8: label.setForeground(new Color(255,0,255)); break;
		}
		label.setBackground(new Color(240,240,240));
		label.setOpaque(true);
		if(getComponent(pos) instanceof JButton){
			revealed++;
			label.setText(Integer.toString(adjacent));
			remove(getComponent(pos));
			add(label,pos);
		}
	}

	public void gameOver(int pos){
		for(int i=0;i<numMines;i++){
			JLabel label=new JLabel("X",JLabel.CENTER);
			label.setFont(new Font("Monospace",Font.BOLD,20));
			label.setForeground(Color.BLACK);
			label.setBackground(new Color(240,240,240));
			getComponent(pos).setBackground(Color.RED);
			label.setOpaque(true);
			remove(getComponent(mines[i]));
			add(label,mines[i]);
			for(int j=0;j<getComponentCount();j++) if(getComponent(j) instanceof JButton) getComponent(j).setEnabled(false);
			gui.setStatus("GAME OVER",Color.RED);
		}
	}

	public void playerWins(){
		gui.setStatus("YOU WIN",new Color(0,204,0));
		gui.setMineCntr(0);
		for(int j=0;j<gameSize*gameSize;j++){
			Component comp=getComponent(j);
			if(comp instanceof JButton){
				((JButton)comp).setText("!");
				comp.setEnabled(false);
			}
		}
	}

}
