// Author: Jack Edwards
// Date:   9/1/17
// Tabs:   4

import java.util.*;

public class ArithmeticTest
{

	public static void main(String[] args)
	{
		byte[] A;
		byte[] B;
		
		Scanner input = new Scanner(System.in);
/*
		byte[] norm = {1,0};
		printByteArray(norm);
		norm = Arithmetic.normalize(norm);
		System.out.println("test normalize");
		printByteArray(norm);
*/
/*
		byte[] test4 = {1,1,1,1,1,1,1,1};
		byte[] test5 = {1};
		printByteArrayBackwards(Arithmetic.sum(test4,test5));

		byte[] test6 = {1,1,1,1,1,1,1,1,1,1,1,1};
		byte[] test7 = {1,1,1,1,1,1};
		printByteArrayBackwards(Arithmetic.product(test6,test7));
*/	
/*
		byte[] pad = {1,1,0,0,1};
		byte[] padded = Arithmetic.padByteArray(pad, 3);
		printByteArray(pad);
		printByteAsInt(padded);
*/		
/*
		byte[] t1 = {0,0,0,0,0};
		byte[] t2 = {1,1,1};
		byte[] a1 = Arithmetic.product(t1, t2);
		printByteArray(a1);
		printByteAsInt(a1);
*/
/*
		//byte[] test1 = {0,0,0,1,1,0,0,0};
		//byte[] test2 = {1,1};
		//printByteAsInt(Arithmetic.sum(test1, test2));	
*/		
		System.out.println("enter: add, mutiply, inc, or exit");
		String choice = input.nextLine();

		while(!choice.equals("exit")){

			if(choice.equals("add")){
				System.out.println("enter 2 numbers to add.");
				A = readByteArray();
				B = readByteArray();
				
				byte[] C = Arithmetic.sum(A, B);
				printByteAsInt(C);

			}else if(choice.equals("multiply")){
				System.out.println("enter 2 numbers to multiply.");
				A = readByteArray();
				B = readByteArray();
				
				byte[] D = Arithmetic.product(A, B);
				printByteAsInt(D);	
			}else if(choice.equals("inc")){
				System.out.println("enter number to increment.");
				A = readByteArray();	

				byte[] E = Arithmetic.inc(A);
				printByteAsInt(E);
			}else{
				System.out.println("unrecognized input");
			}
			choice = input.nextLine();
		}
		System.out.println("exiting");
	}
	
	//readByteArray() reads and integer from the user and returns a byte
	//array with the least significant bit at index 0.
	public static byte[] readByteArray(){
		Scanner read = new Scanner(System.in);
		//System.out.println("enter integer");
		int num;
		num = read.nextInt();
		String number = Integer.toBinaryString(num);
		byte[] bNumber = new byte[number.length()];
		
		int j = number.length() - 1;
		for(int i = 0; i < number.length(); i++){ 			
			String currBit = Character.toString(number.charAt(j));
			bNumber[i] = (byte)Integer.parseInt(currBit);
			j--;
		}
		return bNumber;
	}
	
	//printByteArray(A) prints byte array A. A is the byte array to print.
	public static void printByteArray(byte[] A){
		if(A.length == 0)
		{
			System.out.println("the value is 0");
		}
		else
		{
			for(int i = 0; i < A.length; i++){
				System.out.print(A[i]);		
			}
			System.out.println();
		}	
	}
	
	//printByteArrayBackwards(A) prints byte array A backwards(LSB last). 
	//A is the byte array to print.
	public static void printByteArrayBackwards(byte[] A){
		if(A.length == 0)
		{
			System.out.println("the value is 0");
		}
		else
		{
			for(int i = A.length - 1; i >= 0; i--){
				System.out.print(A[i]);		
			}
			System.out.println();
		}	
	}
	
	//printByteArrayAsInt(A) prints byte array A as an integer. A is the byte
	//aray to print.
	public static void printByteAsInt(byte[] A){
		long number = 0;
		for(int i = 0; i < A.length; i++){
			if(A[i] == 1){
				number += Math.pow(2, i);
			}
		}
		System.out.println("the number is: " + number);
	}
}
