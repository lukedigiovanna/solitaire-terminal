VPATH = src

# Specify the object files
OBJS = main.o Game.o Card.o Deck.o termutils.o
# Directory for object files
OBJDIR = src

CXXFLAGS := -std=c++17 -I/opt/homebrew/Cellar/ncurses/6.4/include -D_XOPEN_SOURCE_EXTENDED
LDFLAGS := -L/opt/homebrew/Cellar/ncurses/6.4/lib -lncursesw

main: main.cpp $(OBJS)
	g++ $(CXXFLAGS) $(addprefix $(OBJDIR)/,$(OBJS)) $(LDFLAGS) -o solitaire

# Rule for making object files
%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

# Clean target
clean:
	rm -f $(OBJDIR)/*.o
	# rm -f solitaire
