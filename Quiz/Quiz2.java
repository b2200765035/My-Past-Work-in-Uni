import java.util.*;
import java.io.*;

public class Quiz2 {
    public static void main(String[] args) throws IOException {
        
        // TODO: Use the first command line argument (args[0]) as the file to read the input from
    	File file = new File(args[0]);
        Scanner sc = new Scanner(file);
        
        int maxMass = Integer.valueOf(sc.next());
        int maxItem = Integer.valueOf(sc.next());
        int[] items = new int[maxItem + 1];
        for(int i=0; i < maxItem + 1; i++) {
        	if(i == 0) {
        		items[i] = 0;
        	} 
        	else {
            	items[i] = Integer.valueOf(sc.next());       		
        	}
        	
        	}
        
        // TODO: Your code goes here
        int maxMassArr = maxMass + 1;
        int maxItemArr = maxItem + 1;
        boolean[][] result = new boolean[maxMassArr][maxItemArr];
        
        for(int y = 0; y < maxMassArr; y++){
        	for(int x = 0; x < maxItemArr; x++) {
        		if(x==0 && y==0) {
        			result[y][x] = true;
        		} 
        		else if(x==0 && y>0) {
        			result[y][x] = false;
        		} 
        		else if(x>1 && y<items[x-1]) {
        			result[y][x] = result[y][x-1];
        		} 
        		else {
        			int newMass = y - items[x-1];
        			result[y][x] = (result[y][x-1] || result[newMass][x-1]);
        		}
        	}
        }
        // TODO: Print the solution to STDOUT
        int posTrue = 0;
        for(int y = 0; y < maxMassArr; y++){
        	for(int x = 0; x < maxItemArr; x++) {
        		if(result[y][x] == true) {
        			posTrue = y;
        			}
        		}
        	}
        System.out.println(posTrue);
        for (int i = 0; i < result.length; i++) { //this equals to the row in our matrix.
            for (int j = 0; j < result[i].length; j++) { //this equals to the column in each row.
            	if(result[i][j]==true) {
            		System.out.print(1);
            	}
            	else {
            		System.out.print(0);
            	}
            }
            System.out.println(); //change line on console as row comes to end in the matrix.
         }
    }
}
