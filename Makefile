PROJECT = WineLab
SOURCES = './dbconnect.cpp' './main.cpp' './wine.cpp'
EXECUTABLE_NAME = './winedb'

all: $(PROJECT)
clean: 
	$(RM) $(EXECUTABLE_NAME)
execute: 
	$(EXECUTABLE_NAME)
run: $(PROJECT)
	$(EXECUTABLE_NAME)

$(PROJECT):
	g++ -std=c++11 -I/usr/include/mysql $(SOURCES) -L/usr/lib/mysql -lmysqlclient -o $(EXECUTABLE_NAME)

