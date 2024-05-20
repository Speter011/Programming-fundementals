all: create

create: 
	cl /c jdoc.c i-o.c
	lib /OUT:coursework.lib i-o.obj
	link jdoc.obj coursework.lib

	
clean:
	del *.txt
	del *.lib
	del *.exe
	del *.obj