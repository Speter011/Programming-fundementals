//Author: Peter Stefan
//A program which analyses a input file and identifiers in a .c file
//Last modified :08/05/21

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//struct for the info about the different symbols we are reading in from the file
struct symbol_info
{
	string name; //name of the variable/function/array
	string type; //type of the variable/function/array
	string identifier; //is it a variable/function/ or array
	int line_number; //the line the variable/f./a. is on
	int reference_number; //the times it was referenced in the file
	
};
//writefile method to write the outputs into the output file
void writefile (string &filename ,vector <symbol_info> &symbol_list)
	{
		ofstream file(filename);
		//iterate through the vector containing each symbol, and write out the name, line number, the identifier and the reference times into a file
		for (int i = symbol_list.size() - 1; i >= 0; i--)
			file << symbol_list[i].name << ", line " << symbol_list[i].line_number << ", "<< symbol_list[i].identifier << ", " << symbol_list[i].type << ", referenced " << symbol_list[i].reference_number << endl;
		//close the file after use
		file.close();
	}
	
//method to remove duplicates from the vector
void duplicate_remove (vector <symbol_info> &symbol_list)
	{
		//iterate through the vector twice and erase the duplicates
		for(symbol_info s: symbol_list)
		{
			int counter = 0;
			for(symbol_info s2 :symbol_list)
			{
				//we detect a duplicate if the two symbols have the same name and line number
				if(s.name.compare(s2.name) && s.line_number == s2.line_number)
				{
					symbol_list.erase(symbol_list.begin() + counter);
				}
				counter++;
			}
		}
	}
	

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
	vector<symbol_info> symbol_list; //vector in which we store all the info about the functions and variables found in the file
	
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
				//we add the line number to our struct
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
				//we put the struct in our vector
				symbol_list.push_back(new_struct);
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
	
	//we call the duplicate remover method to only have the correct number of identifier information in the vector
	duplicate_remove(symbol_list);
	
	//we find the number of times an identifier was referenced
	while(getline(file, line))
    {
        stringstream stream(line);
        while(stream >> token)
		{
			for(int i = 0; i <= symbol_list.size() -1; i++)
			{
				//we check if the token is the current element of the vector
				if(symbol_list[i].name.compare(token) == 0)
				{
					//if it is the we add one to the times it was referenced
					symbol_list[i].reference_number = symbol_list[i].reference_number + 1;
				}
			}		
		}
	}
	
	for(int i = 0; i <= symbol_list.size() -1; i++)
	{
		//we need to remove one from the reference times because our original number includes the declaration as well
		symbol_list[i].reference_number = symbol_list[i].reference_number - 1;
	}
			
	//we output our vector into the output file
	writefile (string ("identifiers.txt") ,symbol_list ) ;
	
	//we close the file and output the other requiered data to the console
    file.close();
	
	//print to the console the required information(number of variables, functions, if statements, for and while loops)
    cout << "The number of variables is: " << num_variables << endl;
    cout << "The number of functions is: " << num_functions << endl;
	cout << "The number of if statements is: " << num_ifs << endl;
	cout << "The number of for loops is: " << num_for << endl;
	cout << "The number of while loops is: " << num_while << endl;
    return 0; //Program ended succesfully
}