//Jack Edwards
//CSCI 2540
//Assignment 1

import java.io.*;
import java.util.*;

public class GroceryItem{
	private int productNumber; //the product number of the item
	private String description; //the description of the item
	private int quantity; //the number of items
	private double price; //the price of the item
	private String tax; //change to string
	
	public GroceryItem(){
		productNumber = 0;
		description = "";
		quantity = 0;
		price = 0.0;
		tax = "";
	
	}
	
	public String getName(){ return description;} //returns name of item
	public int getNumber(){ return productNumber;} //returns product number of item
	public int getQuantity(){ return quantity;} //returns quantity of item
	public double getPrice(){ return price;} //returns price of item
	public String getTaxCode(){ return tax;} //ruturns tax code of item
	
	public void setQuantity(int itemQuantity){ quantity = itemQuantity;} //sets quantity of item to itemQuantity
	
	//readitem(input) reads a new grocery item in the following format:
	//<productNumber> <description> <quantity> <price> <tax>
	//input is scanner to read from. 
	public void readItem(Scanner input){
		productNumber = input.nextInt();
		description = input.next();
		quantity = input.nextInt();
		price = input.nextDouble();
		tax = input.next();
		
	}
	
	//printInventory(items, numItems) prints a list of grocery items in the following format:
	//<productNumber> <description> <quantity> <price> <tax>
	//items is the grocery list to print. numItems is the number of items in the grocery list items.
	public static void  printInventory(GroceryItem[] items, int numItems){
		for(int i = 0; i < numItems; i++){
			System.out.printf("%5d %12s %4d %7.2f %s\n", items[i].getNumber(), 
							  items[i].getName(), items[i].getQuantity(), items[i].getPrice(), items[i].getTaxCode());
			
		}
	}
	
	//itemSearch(items, numItems, productID) searches the grocery list items for an item
	//with a product identification number productID, if a match is found the index of the item is returned,
	//else -1 is returned.
	//items is the grocery list to search. numItems is the number of items in the grocery list.
	//productID is the product identification number to search for.
	public static int itemSearch(GroceryItem[] items, int numItems, int productID){
		
		for(int i = 0; i < numItems; i++){
			if(items[i].getNumber() == productID){
				return i; //item found
			}
		}
		
		return -1; //item was not found
	}
	
}