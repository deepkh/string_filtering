SHELL=/bin/sh


# Need GCC 5.2 above for <codecvt>

.DEFAULT_GOAL = all

CXXFLAGS = -I. -O2 -Wall -std=c++11 -g
LDFLAGS=

all: word_filter

word_filter: word_filter.o
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) *.o word_filter
