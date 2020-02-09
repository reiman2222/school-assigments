//Jack Edwards
//CSCI 2540
//Assignment 2
//DiskSim.java

//This program simulates a file manager. the user can create files, delete files,
//prints the sector usage of files and print the list of free sectors.
//user input is expected in the following format
//<code> <fileNumber> <numCharacters>
//code c creates a file with file number fileNumber and size numCharacters.
//code d deletes a file fileNumber.
//code p prints a file fileNumber.
//code p with file number -1 prints the list of free sectors.
//code x exits the prgram.
//printing the number of files and used sectors to the standard output.
//if a field is not needed to perfrom a certain operation then 0 should 
//be entered.
//ex:	p 2 0 	prints the sectors used by file 2.
//		x 0 0 	exits the program.
//this program requires DiskParam.java

import java.util.*;
import java.lang.Math;

public class DiskSim{
	
	public static final int NUM_SECTORS = DiskParam.NUM_SECTORS;
	public static final int NUM_FILES = DiskParam.NUM_FILES;
	public static final int MAX_SIZE = DiskParam.MAX_SIZE;
	public static final int SECTOR_SIZE = DiskParam.SECTOR_SIZE;
	
	public static void main(String args[]){
		
		SectorUsage empty = new SectorUsage(0, NUM_SECTORS - 1);
		
		List<SectorUsage> freeSpace = new List<SectorUsage>(); //free space list
		freeSpace.add(1, empty);
		
		FileInfo[] filesOnDisk = new FileInfo[NUM_FILES - 1]; //file info array
		
		Scanner input = new Scanner(System.in);
		char code; //determines operstion to perform on simulated disk
		int fileID; //file to perfrom operation on
		int size; //size of file
		
		boolean exit = false; //if true program exits
		
		initFileInfoArray(filesOnDisk); //initalize filesOnDisk
		
		//continue until user enters exit command
		while(!exit){
			
			//get user input
			code = input.next().charAt(0);
			fileID = input.nextInt();
			size = input.nextInt();
			
			//create file
			if(code == 'c'){
				writeFile(freeSpace, filesOnDisk, size, fileID);
				
			//delete file
			}else if(code == 'd'){
				deleteFile(freeSpace, filesOnDisk, fileID);
			
			//print
			}else if(code == 'p'){
				
				//print free sectors list
				if(fileID == -1){ 
					System.out.println("Contents of Sector List");
					printSectors(freeSpace);
				
				//print sectors used by file at index fileID
				}else{
					printFileSectorList(filesOnDisk, fileID);
				}
			
			//exit
			}else{
				exitSimulation(filesOnDisk); //print output for exit
				exit = true;
			}
		}
	}
	
	
	//pritnSectors(sectorList) prints a sectorList in the following format
	//	<start>		<end>
	//	<start>		<end>
	//	...			...
	//sectorList is the sector list to print
	public static void printSectors(List<SectorUsage> sectorList){
		int i = 1;
		
		System.out.println("Start Sector    End Sector");
		while(i <= sectorList.size()){
			SectorUsage curr = sectorList.get(i);
			System.out.println("      " + curr.getStart() + "           "
				+ curr.getEnd());
			i++;
		}
		System.out.println();
	}
	
	//printFileSectorList(files, fileID) prints the file sector usage list at
	//files[fileID]. if the file exists printFileSectorUsageList prints information
	//about the file and the sector usage list. if the file does not exist an error 
	//message is printed. files is the array of files. fileID is the index in the 
	//files array to print from.
	public static void printFileSectorList(FileInfo[] files, int fileID){
		if(files[fileID] != null){
			System.out.println("Sector usage for file " + fileID + " --- size = " 
						+ files[fileID].numchars + " character");
			printSectors(files[fileID].file_usage);
			
		}else{
			System.out.println("ERROR on print command: file " 
				+ fileID + " does not exist.\n");
		}
	}
	
	//writeFile(freeSpace, files, numCharacters, fileID) allocates a file with 
	//enough sectors to hold numCharacter characters, from the freeSpace list. 
	//If there are not enough free sectors avalible writeFile prints an error 
	//message to the stanard output,
	//else writeFile creates the file and prints information about that file
	//to the standard output.
	//freeSpace is the list to allocate memory from.
	//files is the file info array to store the new file in.
	//numCharacters is the number of characters that need to be stored.
	//fileID is the position to store the new file in the file info array files
	public static void writeFile(List<SectorUsage> freeSpace, FileInfo[] files, int numCharacters, int fileID){
		List<SectorUsage> used = new List<SectorUsage>();
		FileInfo file = new FileInfo();
		int currFS = 1; //current index of freeSpace list
		int neededSec = sectorsNeeded(numCharacters); //sectors needed to hold file
		int sectorsFilled = 0; 
		int currUsed = 1; //current index of used
		SectorUsage newSector;
		
		if(files[fileID] == null){
			if(neededSec <= sectorsInList(freeSpace)){
				//while more sectors need to be allocated
				while(sectorsFilled != neededSec){ 
		
					//chunk is larger than sectors needed
					if(numSectors(freeSpace.get(currFS)) > neededSec){ 
						//System.out.println("Part of chunk");
						newSector = new SectorUsage(freeSpace.get(currFS).getStart(), 
							(neededSec - sectorsFilled)+ freeSpace.get(currFS).getStart() - 1);
					
						used.add(currUsed, newSector); //allocate sector
						sectorsFilled += numSectors(newSector); //update sectors filled
				
						//update freeSpace list
						freeSpace.get(currFS).setStart(newSector.getEnd() + 1);
			
					//chunk is smaller that sectors needed
					}else{
						//System.out.println("Whole chunk");
						newSector = new SectorUsage(freeSpace.get(currFS).getStart(), 
							freeSpace.get(currFS).getEnd());
					
						used.add(currUsed, newSector); //allocate sector
						sectorsFilled += numSectors(newSector); //update sectors filled
				 
						//update freeSpace list
						freeSpace.remove(currFS);
						currFS--;
				
					}
					currFS++;
					currUsed++;
				}	
				file.numchars = numCharacters; 
				file.file_usage = used;
				files[fileID] = file;
				
				System.out.println("File " + fileID + " created, size = " + numCharacters);

			}else{
				System.out.println("ERROR on create command: insufficient space for file "
					+ fileID + "\n");
			}
		}else{
			System.out.println("ERROR on create command: file " +
						fileID + " already exists\n");
		}
	}
	
	//numSectors(currentSectors) returns the number of sectors in a 
	//chunk of memory currentSectors. currentSectors is the chunk of memory.
	public static int numSectors(SectorUsage currentSector){
		return currentSector.getEnd() - currentSector.getStart() + 1;
	}
	
	//sectorsNeeded(numCharacter) returns the sectors needed to hold an ammount of
	//characters numCharacters. numCharacters is the number of characters that 
	//need to be storred. 
	public static int sectorsNeeded(int numCharacters){
		double neededSec = numCharacters / (double)SECTOR_SIZE;
		return (int)Math.ceil(neededSec);
	}
	
	//deleteFile(freeSpace, files, fileID) returns all sectors used by files[fileID] to
	//freeSpace, then prints the number of sectors freed to the standard output.
	//if the file to delete does not exist the deleteFile just prints an error message.
	//freeSpace is the list of free sectors, files is the file info array to delete from.
	//fileID is the index in files to delete.
	public static void deleteFile(List<SectorUsage> freeSpace, FileInfo[] files, int fileID){
		int currFile = 1;
		int sectorsFreed;
		List<SectorUsage> fileList;
		
		if(files[fileID] != null){
			fileList = files[fileID].file_usage;
			
			//while there are still SectorUsage nodes to delete
			while(currFile <= fileList.size()){ //could maybe do a remove for file at each interation to make more efficent
				freeSpace.add(1, fileList.get(currFile)); //return used sector to free space list
				currFile++;
			
			}
		
			sectorsFreed = sectorsNeeded(files[fileID].numchars); //number of sectors contained in file
			files[fileID] = null; //delete file
			
			System.out.println("File " + fileID + " deleted, " + 
					sectorsFreed + " sectors freed");
			
		}else{
			System.out.println("ERROR on delete command: file " + fileID
				+ " does not exist\n");
		}
		
	}
	
	//initFileInfoArray(files) initalizes all indecies in files to null.
	//files is the file info array to initalize.
	public static void initFileInfoArray(FileInfo[] files){
		for(int i = 0; i < files.length; i++){
			files[i] = null;
		}
	}
	
	//sectorsInList(list) returns the number of sectors in a sector usage list.
	//list is the Sector Usage list to evaluate.
	public static int sectorsInList(List<SectorUsage> list){
		int totalSectors = 0;
		for(int i = 1; i <= list.size(); i++){
			totalSectors += numSectors(list.get(i));
		}
		return totalSectors;
	}
	
	
	//exitSimulation(files) prints the number of files and sectors being used by the files 
	//in the file info array files.
	//files is the file info array to examine.
	public static void exitSimulation(FileInfo[] files){
		int numFiles = 0;
		int totalSectors = 0;
		
		for(int i = 0; i < files.length; i++){
			if(files[i] != null){
				numFiles++;
				totalSectors += sectorsNeeded(files[i].numchars);
			}
		}
		
		System.out.println("SIMULATOR EXIT: " + numFiles + 
					" files exist, occupying " + totalSectors + " sectors.");
	}
}
