package tictactoe;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class GUI extends JFrame{

	private static final long serialVersionUID=1L;
	private static final int windowW=500;
	private static final int windowH=610;
	private static final int gameSize=12;

	private GamePanel game=null;
	private JButton btn=null;

	GUI(){
		super("Tic-Tac-Toe");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setSize(windowW,windowH);
		JPanel panel=new JPanel();
		panel.setBackground(new Color(49,54,59));
		btn=new JButton();
		btn.setFocusPainted(false);
		btn.setPreferredSize(new Dimension(130,30));
		btn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				remove(game);
				newGame();
			}
		});
		panel.add(btn);
		add(panel,"North");
		newGame();
		setResizable(false);
		setVisible(true);
	}

	public void newGame(){
		game=new GamePanel(gameSize);
		game.setGUI(this);
		add(game,"Center");
		game.revalidate();
		game.repaint();
		setStatus("NEW GAME",Color.BLACK);
	}

	public void setStatus(String str, Color c){
		btn.setText(str);
		btn.setForeground(c);
	}

}
