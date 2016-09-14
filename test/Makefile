BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -I.. -Werror -Wno-unused-result


ifeq ($(opt),1)
  CXXFLAGS += -Os -march=i686 -fomit-frame-pointer
  LDFLAGS  += -s
else
  CXXFLAGS += -g
endif


COMMON_LDFLAGS = -lstdc++


ifeq ($(mingw),1)
  EXE_EXT = .exe
  DIR_PREFIX = i686-w64-mingw32
  CMD_PREFIX = $(DIR_PREFIX)-
  LDFLAGS = $(COMMON_LDFLAGS) -lmingw32 -static
else
  LDFLAGS = $(COMMON_LDFLAGS)
endif




ifeq ($(emcc),1)
  CXX      = CCACHE_DIR=/tmp/ccachedir ccache emcc
  CXXFLAGS = -std=gnu++11 -I. -Werror -Wno-unused-result -Os -s USE_SDL=2
  EXE_EXT  = .html
  LDFLAGS  = 
else ifeq ($(ccache),1)
  CXX = CCACHE_DIR=/tmp/ccachedir ccache $(CMD_PREFIX)g++
else
  CXX = $(CMD_PREFIX)g++
endif



STRIP = $(CMD_PREFIX)strip
AR    = $(CMD_PREFIX)ar

CXXFLAGS += -I$(BASE_DIR)/$(DIR_PREFIX)/include
LDFLAGS  += -L$(BASE_DIR)/$(DIR_PREFIX)/lib


ifeq ($(delay),1)
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS)  $< -o $@
	sleep 1
endif


all: test_mkf$(EXE_EXT) randjson$(EXE_EXT) test_mkfjson$(EXE_EXT)


clean:
	rm -f test_mkf$(EXE_EXT)     \
       randjson$(EXE_EXT)     \
       test_mkfjson$(EXE_EXT) \


test_mkf$(EXE_EXT):
	$(CXX) test_mkf.cpp -o $@ ../*.o ../libpp/*.o $(CXXFLAGS) $(LDFLAGS)

randjson$(EXE_EXT):
	$(CXX) randjson.cpp -o $@ ../*.o ../libpp/*.o $(CXXFLAGS) $(LDFLAGS)

test_mkfjson$(EXE_EXT):
	$(CXX) test_mkfjson.cpp -o $@ ../*.o ../libpp/*.o $(CXXFLAGS) $(LDFLAGS)




