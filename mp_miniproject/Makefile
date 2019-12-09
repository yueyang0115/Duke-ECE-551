SOURCES=ffosh.cpp  shell.cpp function.cpp
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98

ffosh: $(OBJS)
	g++ $(CPPFLAGS) -o ffosh $(OBJS)
%.o: %.cpp shell.h function.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm ffosh *~ *.o
