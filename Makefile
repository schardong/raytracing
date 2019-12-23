ifneq ($(MAKECMDGOALS), release)
	CONFIG := debug
	CXXFLAGS += -g3 -O0 -D_DEBUG
else
	CONFIG := release
	CXXFLAGS += -g0 -O2 -DNDEBUG
endif

CXXFLAGS += -std=c++17 -Iext -Isrc

OBJS := $(shell find src -name *.cpp | sed "s/^src\///")
OBJS := $(foreach obj, $(OBJS:.cpp=.o), $(obj))

.PHONY: all release clean test

all: rt

release: all
	strip rt

clean:
	rm -Rf *.o rt

rt: $(OBJS)
	$(CXX) -o $@ $^

%.o: src/%.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

test: rt
	./rt 600 300 10 > image.ppm
