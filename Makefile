BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -Werror -Wno-unused-result


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


OBJ +=                   \
  mkf_file.o             \
  mkf_charptr.o          \
  mkf_discontinue.o      \
  mkf_print.o            \
  mkf_element.o          \
  mkf_element_compare.o  \
  mkf_group.o            \
  mkf_group_scan.o       \
  mkf_group_compare.o    \
  mkf_definition.o       \
  mkf_node.o             \
  mkf_cursor.o           \
  mkf_ctype.o            \
  mkf_unicode.o          \
  mkf_book.o             \
  mkf_parsecontext.o     \
  json.o                 \
  json_random.o          \
  json_read.o            \


all: objects test_mkf$(EXE_EXT) randjson$(EXE_EXT) test_mkfjson$(EXE_EXT)


clean:
	rm -f $(OBJ) test_mkf$(EXE_EXT)         test_mkf.o  \
              randjson$(EXE_EXT)         randjson.o  \
              test_mkfjson$(EXE_EXT) test_mkfjson.o  \


objects: $(OBJ)


test_mkf$(EXE_EXT): $(OBJ) test_mkf.o
	$(CXX) -o $@ $(OBJ) test_mkf.o $(LDFLAGS)

randjson$(EXE_EXT): $(OBJ) randjson.o
	$(CXX) -o $@ $(OBJ) randjson.o $(LDFLAGS)

test_mkfjson$(EXE_EXT): $(OBJ) test_mkfjson.o
	$(CXX) -o $@ $(OBJ) test_mkfjson.o $(LDFLAGS)




