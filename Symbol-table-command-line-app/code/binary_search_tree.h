//Author: Peter Stefan
//Header file for the binary_search_tree.cpp file
//Last modified :08/05/21

#pragma once
#include <iostream>
#include <string>

//struct for the info about the different symbols we are reading in from the file
struct symbol_info
{
	std::string name = ""; //name of the variable/function/array
	std::string type; //type of the variable/function/array
	std::string identifier; //is it a variable/function/ or array
	int line_number; //the line the variable/f./a. is on
	int reference_number; //the times it was referenced in the file
	
};	

//Node class for our binary search tree
class Node
{
	private:
			Node *left; //pointer to left child
			Node *right; //pointer to right child
			Node *root; //pointer ot root
			symbol_info data; //stores the identifier struct 
	public:
			void delete_tree(); //method to delete the tree
			void update(symbol_info data); //method to insert data into the tree
			void print_tree(); //method to print out the data from the tree in order (left branch lesser, right branch greater, than root, and so forth)
}