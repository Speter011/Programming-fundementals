all: partA partB 

partA:
	cl /EHsc symbol_table.cpp
	
partB: 
	cl /EHsc /c symbol_table2.cpp binary_search_tree.cpp
	lib /OUT:coursework.lib binary_search_tree.obj
	link symboltable2.obj coursework.lib
	link binary_search_tree.obj coursework.lib
clean:
	del *.txt
	del *.exe
	del *.lib
	del *.obj