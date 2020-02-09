// Author: Jack Edwards
// Date:   9/1/17
// Tabs:   4  (indicate the separation between tab stops)

//==============================================================
// These functions work on arrays that represent binary numbers.
// Each value in the arrays is either 0 or 1, and the low order
// bit is at index 0.  For example, if array A contains binary
// number 14 (1110 in standard binary notation), then it might be
// that
//    A[0] = 0
//    A[1] = 1
//    A[2] = 1
//    A[3] = 1
//
// Say that a binary number is *normalized* if its highest order
// bit is 1.  (As a special case, 0 is normalized if it is
// represented by an array of length 0.)
//
// All results of these functions are normalized.  But the
// parameters are not required to be normalized.  For example,
// if array A holds
//    A[0] = 0
//    A[1] = 1
//    A[2] = 1
//    A[3] = 1
//    A[4] = 0
//    A[5] = 0
// then A is a non-normalized representation of 14.
//==============================================================

import java.util.*;

public class Arithmetic
{
	
	//normalize(A) normalizes the byte array A.
	//Ex: A = 10110000, normalize(A) = 1011
	private static byte[] normalize(byte[] A)
	{  //!!!!!! change back to private;
		byte[] normalizedArray;
		int newLength; //holds the index where the first 1 occurs
		newLength = A.length;

		while(newLength > 0 && (A[newLength - 1] != 1))
		{
			newLength--;	
		}
		
		if(newLength == 0)
		{
			normalizedArray = new byte[0];
		}
		else if(newLength == A.length)
		{
			normalizedArray = A;
		}
		else
		{
			normalizedArray = new byte[newLength];
			for(int i = 0; i < normalizedArray.length; i++)
			{
				normalizedArray[i] = A[i];			
			}		
		}
		return normalizedArray;
	}
	
	//copyBitArray(A, sizeOfNewArray) returns a copy of A with size 
	//sizeOfNewArray. sizeOfNewArray must be <= A.length. A is array
	//to copy. sizeOfNewArray is the size of the new array.
	private static byte[] copyBitArray(byte[] A, int sizeOfNewArray)
	{
		byte[] newArray = new byte[sizeOfNewArray];
		for(int i = 0; i < A.length; i++)
		{
			newArray[i] = A[i];
		}
		return newArray;
	}	

 	//=================================================================
	// inc(A) returns an array of bits representing A+1.
	//=================================================================

	public static byte[] inc(byte[] A)
	{
		byte[] one = {1};
		return sum(A, one);
	}

	//=================================================================
	// sum(A,B) returns an array of bits representing A+B.
	//=================================================================

	public static byte[] sum(byte[] A, byte[] B)
	{
		byte[] answer = new byte[Math.max(A.length, B.length) + 1];
		byte carry = 0;
		byte[] newA;
		byte[] newB;

		//A is 0
		if(A.length == 0)
		{
			return normalize(B);
		}
		
		//B is 0
		if(B.length == 0)
		{
			return normalize(A);
		}
	
		//make A and B equal length
		if(A.length > B.length)
		{
			newB = copyBitArray(B, A.length); //make new variables
			newA = A;
		}
		else if(B.length > A.length)
		{
			newA = copyBitArray(A, B.length);
			newB = B;		
		}
		else
		{
			newA = A;
			newB = B;
		}
		
		//perform addition
		for(int i = 0; i < answer.length - 1; i++)
		{
			answer[i] = (byte)(newA[i] ^ newB[i] ^ carry); 
			carry = (byte)((newA[i] & newB[i]) | (carry & (newA[i] ^ newB[i])));
		}

		answer[answer.length - 1] = carry;
		
    	return normalize(answer);
	}

	//=================================================================
	// product(A,B) returns an array of bits representing A*B.
	//=================================================================

	public static byte[] product(byte[] A, byte[] B)
	{
		byte[] answer = new byte[0];
		byte[] larger;
		byte[] smaller;
		byte[] partialSum;
		
		//find which array is smallest
		if(A.length > B.length)
		{
			larger = A;
			smaller = B;
		}
		else
		{
			larger = B;
			smaller = A;		
		}

		for(int i = 0; i < smaller.length; i++)
		{
			if(smaller[i] == 1)
			{
				partialSum = padByteArray(larger, i);
				answer = sum(answer, partialSum);
			}
		}
		
    	return normalize(answer);
	}

	//padByteArray(A, numberToPad) pads a with amountToPad zeros. 
	//A is the byte array to pad. amountToPad is the amount of zeroes to pad.
	//padByteArray requires numberToPad <= A.length
	//A = 1101, padByteArray(A, 3) = 0001101
	public static byte[] padByteArray(byte[] A, int amountToPad)
	{
		byte[] paddedArray = new byte[A.length + amountToPad];
		
		int i = amountToPad;
		
		//copy A 
		for(int j = 0; j < A.length; j++)
		{
			paddedArray[i] = A[j];
			i++;
		}

		return paddedArray;
	}
}
