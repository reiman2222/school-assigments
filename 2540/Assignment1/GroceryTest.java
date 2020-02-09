//Jack Edwards
//CSCI 2540
//Assignment 1

import java.io.*;
import java.util.*;

public class GroceryTest
{

	public static final int MAX_GROCERY_LIST_SIZE = 100;
	public static final double FOOD_TAX = 0.02;
	public static final double NONFOOD_TAX = 0.07;

	public static void main(String[] args){
		GroceryItem[] list = new GroceryItem[MAX_GROCERY_LIST_SIZE];
		int numItems = 0;
			
    	Scanner fileInput;  // inventory file
    	File inFile = new File("inventory.dat");
		
		int currentCustomer = 1; //current customer in customer simuation
		Scanner customer = new Scanner(System.in); //customer input
		
    	try {
			fileInput = new Scanner(inFile);  // open inventory file and read
			
			
    		while (fileInput.hasNext() && numItems < MAX_GROCERY_LIST_SIZE){
				GroceryItem item = new GroceryItem();
				item.readItem(fileInput);
							
				//adds item to inventory if it was not previously entered
				if((GroceryItem.itemSearch(list, numItems, item.getNumber()) == -1) || numItems == 0){
					list[numItems] = item;
				
					numItems++;
				
				}else{
					System.out.println("*** ERROR duplicate item " + item.getNumber() + " "
									   + item.getName() + " ignored.");
				}
				
    		}
      	
    	}catch(FileNotFoundException e){
      		System.out.println(e); 
			System.exit(0);
    
    	}
		
		System.out.println("INITIAL INVENTORY\n");
		GroceryItem.printInventory(list, numItems);
		System.out.println("\nPURCHASE SIMULATION\n");
		
		//coustomer simulation
		while(customer.hasNext()){
			System.out.println("CUSTOMER " + currentCustomer);
			
			simulateCustomer(customer, currentCustomer, list, numItems);
			currentCustomer++;
			
			
		}
		
		System.out.println("FINAL INVENTORY\n");
		GroceryItem.printInventory(list, numItems);

	}
	
	//simulateCustomer(customerInput, currentCustomer, list, numItems) simulates 1 customer making purchases until they
	//enter -1 -1. simulateCustomer then prints the total cost of the transaction to the standard out put.
	//customerInput is the input to read from. currentCustomer is the customer currently doing a transaction.
	//list is the grocery list. numItems is the number of items in the grocery list.
	public static void simulateCustomer(Scanner customerInput, int currentCustomer, GroceryItem[] list, int numItems){		
		int productNum;
		int quantity;
		double totalTax = 0.0;
		double totalCost = 0.0;
		double currentTax;
		double currentPrice;
		
		productNum = customerInput.nextInt(); //get product number
		quantity = customerInput.nextInt(); //get quantity
					
		while((productNum != -1) && (quantity != -1)){
			int index = GroceryItem.itemSearch(list, numItems, productNum);

			if(index != -1){
				//calculate tax for item
				currentTax = calcTax(list[index].getPrice(), quantity, list[index].getTaxCode());
				totalTax += currentTax; //keep track of total tax
				currentPrice = list[index].getPrice() * quantity; //calculate price of item
				totalCost += currentPrice; //keep track of total cost of transaction
				
				//prints item transaction
				System.out.printf("%12s %d@%.2f, Cost = %6.2f %s\n", 
								  list[index].getName(), quantity, list[index].getPrice(), 
								  currentPrice, list[index].getTaxCode());
				
				//reduce quantity
				list[index].setQuantity(list[index].getQuantity() - quantity);
				
				
			}else{
				System.out.println("*** item " + productNum + " not in inventory ***");
				
			}
			
			productNum = customerInput.nextInt(); //get product number
			quantity = customerInput.nextInt(); //get quantity
		}
		
		//print final cost and tax
		System.out.printf("\nTotal Cost  = $%7.2f\n", totalCost);
		System.out.printf("Total Tax   = $%7.2f\n", totalTax);
		System.out.printf("Grand Total = $%7.2f\n\n", totalCost + totalTax);
			
	}
	
	//calcTax(price, quantity, taxCode) returns the tax for the purchase.
	//price is the price of the item. quantity is the number of items.
	//taxCode is the tax code of the item.
	public static double calcTax(double price, int quantity, String taxCode){
		
		if(taxCode.equals("F")){
			return ((price * quantity) * FOOD_TAX);
		}else{
			return ((price * quantity) * NONFOOD_TAX);
		}
	}
	
	
	

}
