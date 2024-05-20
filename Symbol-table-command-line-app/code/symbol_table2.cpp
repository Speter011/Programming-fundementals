//Author: Peter Stefan
//This program does the same thing as symbol_table.cpp the difference is it uses a binary tree instead of a vector, so it has some additional methods in place
//Last modified :08/05/21

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "binary_search_tree.h"

using namespace std;

int main(int argc, char **argv)
{	
    ifstream file(argv[1]);
    string line;
    string token;
    int line_counter = 0;
    int num_functions = 0;
    int num_variables = 0;
	int num_ifs = 0;
	int num_for = 0;
	int num_while = 0;
	int reference_times = 0;

	//we create a instance for the binary search tree
	Node *tree = nullptr;
	//iterate through the lines of the file
    while(getline(file, line))
    {
        stringstream stream(line);
        line_counter++;
		
		//iterate through the tokens
        while(stream >> token)
        {
			//we search for the different identifiers
            if(token.compare("char") == 0 || token.compare("short") == 0 || token.compare("int") == 0 || token.compare("long") == 0
			||token.compare("float") == 0 || token.compare("double") == 0|| token.compare("char*") ==0 || token.compare("short*") == 0
			||token.compare("int*") == 0 || token.compare("long*") == 0 || token.compare("float*") == 0 || token.compare("double*") == 0)
            {
				
				symbol_info new_struct = symbol_info(); //we create an instance of our struct
				new_struct.type = token;
					
					//special case for long long because it is two words and doesn't fit in one token, so we need to look at the next token as well
					new_struct.name = token;
					stream >> token;
					if(token.compare("long") == 0)
					{
						new_struct.type = "long long"; 
						stream >> token;
						new_struct.name = token;
					}

                //The next token is the name
				new_struct.line_number = line_counter;
           
				
				if(new_struct.type.compare("long") != 0 || new_struct.type.compare("long long") != 0)
				{
					new_struct.name = token;
				}
				
				new_struct.reference_number = 0;
				
                stream >> token; //Get the next token
                if(token.compare("(") == 0)
                {
                    //We have a function
                    num_functions++;
					new_struct.identifier = "function";
                }
                else
                {
                    //We have a variable
                    num_variables++;
					new_struct.identifier = "variable";
                }
				//we put the struct in to the tree
				tree.update(new_struct);
            }
			//we check for if statements, and for and while loops
			if(token.compare("if") == 0)
			{
				//We have an if statement
				num_ifs++;
			}
			else if(token.compare("for") == 0)
			{
				//We have a for loop
				num_for++;
			}
			else if(token.compare("while") == 0)
			{
				//We have a while loop
				num_while++;
			}
        }
    }
	//we go to the front our file
	file.clear();
    file.seekg(0, ios::beg);				
	
	//we close the file and output the other requiered data to the console
    file.close();
	
	//print to the console the required information(number of variables, functions, if statements, for and while loops)
    cout << "The number of variables is: " << num_variables << endl;
    cout << "The number of functions is: " << num_functions << endl;
	cout << "The number of if statements is: " << num_ifs << endl;
	cout << "The number of for loops is: " << num_for << endl;
	cout << "The number of while loops is: " << num_while << endl;
	//we free the allocated memory by deleting the tree
	tree.delete_tree();
    return 0; //Program ended succesfully
}