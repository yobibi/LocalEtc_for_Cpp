TARGET    = ExampleLocalEtc
SRCS      = ExampleLocalEtc.cpp LocalEtc.cpp
OBJS      = $(SRCS:.cpp=.o)
CXX       = g++
#CXX       = clang++
CXXFLAGS  = -Wall -std=gnu++17
LIBS      = -static-libgcc -static-libstdc++ -static


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) -c $^


.PHONY: all
all: clean $(OBJS) $(TARGET)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)
