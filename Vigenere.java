import java.util.Scanner;

public class Vigenere {

	public static char[][] table = new char[96][96];
	Scanner in = new Scanner(System.in);
	String message;
	String key;

	public static void main(String[] args) {
		Vigenere vig = new Vigenere();
		vig.initTable();
		System.out.println("Enter message");
		vig.message = vig.in.next();
		System.out.println("Enter key");
		vig.key = vig.in.next();

		System.out.println(vig.encipher());
	}

	public void initTable(){

		for(int i = 0; i < 96; i++){
			for(int j = 0; j < 95; j++){
				table[i][j] = (char)((j+32+i)%96);
			}
		}
	}

	public String encipher(){
		String cipher = "";
		for(int i = 0; i < message.length(); i++){
			int row = (int)(message.charAt(i))-32;
			int col = (int)(key.charAt(i%key.length()))-32;

			cipher += table[row][col];
		}
		return cipher;
	}
}