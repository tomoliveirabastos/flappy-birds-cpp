TARGET=a.out
CXX=g++
CXXFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
LD=g++
OBJS=main.o 
all: $(OBJS) 
	$(LD) $(OBJS) -o $(TARGET)  $(CXXFLAGS) 
	@rm *.o 
	@./$(TARGET)

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o