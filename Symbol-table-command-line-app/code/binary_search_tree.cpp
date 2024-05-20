//Author: Peter Stefan
//file declaring the methods of the Node class
//Last modified :08/05/21

#include <iostream>
#include <string>
#include "binary_search_tree.h"

//method to free up memory/ to delete existing binary search tree
void Node::delete_tree()
{
	if(this == nullptr)
	{
		return;
	}
	Node::left.delete_tree();
	delete this;
	Node::right.delete_tree();
	delete this;
	return;
}

//method to insert a new node into a binary search tree
void Node::update (symbol_info data)
{
	if(Node::data.name.compare("") == 0)
	{
		//if the node is empty we input the data, and set the left and right nodes to nullpointers
		Node::data = data;
		Node::left = nullptr;
		Node::right = nullptr;
	}
	//we check where the data should be put
	//if it is less than this node then we go left
	if(Node::data.name.compare(Node::data.name) < 0)
	{
		Node::left.update(data);
	}
	//if it is greater than this node then we go right
	if(Node::data.name.compare(Node::data.name) > 0)
	{
		Node::right.update(data);
	}
	//if it is equal then we add one to the current number of references
	if(Node::data.name.compare(Node::data.name) == 0)
	{
		Node::data.reference_number++;
	}	
}

//prints the tree in order
void Node::print_tree()
{
	//first we need to check if the tree is empty
	if(this != nullptr)
	{
		//we recursively print out the left and right branches, and the current tree
		Node::left.print_tree();
		std::cout << Node::data.name << ", line " << Node::data.line_number << ", "<< Node::data.identifier << ", " << Node::data.type << ", referenced " << Node::data.reference_number << std::endl;
		Node::right.print_tree();
	}
}