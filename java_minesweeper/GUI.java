package minesweeper;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class GUI extends JFrame{

	private static final long serialVersionUID=1L;
	private static final int windowW=500;
	private static final int windowH=610;
	private static final int numMines=20;
	private static final int gameSize=12;

	private GamePanel game=null;
	private JLabel lbMineCntr=null;
	private JLabel lbStepCntr=null;
	private JButton btn=null;

	GUI(){
		super("Minesweeper");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setSize(windowW,windowH);
		JPanel panel=new JPanel();
		panel.setBackground(new Color(49,54,59));
		lbMineCntr=new JLabel("",JLabel.CENTER);
		lbMineCntr.setPreferredSize(new Dimension(50,30));
		lbMineCntr.setForeground(new Color(121,211,255));
		panel.add(lbMineCntr);
		btn=new JButton();
		btn.setFocusPainted(false);
		btn.setPreferredSize(new Dimension(120,30));
		btn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				remove(game);
				newGame();
			}
		});
		panel.add(btn);
		lbStepCntr=new JLabel("",JLabel.CENTER);
		lbStepCntr.setPreferredSize(new Dimension(50,30));
		lbStepCntr.setForeground(new Color(121,211,255));
		panel.add(lbStepCntr);
		add(panel,"North");
		newGame();
		setResizable(false);
		setVisible(true);
	}

	public void newGame(){
		game=new GamePanel(gameSize,numMines);
		game.setGUI(this);
		add(game,"Center");
		game.revalidate();
		game.repaint();
		setStepCntr(0);
		setMineCntr(numMines);
		setStatus("NEW GAME",Color.BLACK);
	}

	public void setStepCntr(int n){
		lbStepCntr.setText(Integer.toString(n));
	}

	public void setMineCntr(int n){
		lbMineCntr.setText(Integer.toString(n));
	}

	public void setStatus(String str, Color c){
		btn.setText(str);
		btn.setForeground(c);
	}

}
