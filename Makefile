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
  mkf_book.o             \
  mkf_parsecontext.o     \
  mkf__read.o            \
  json.o                 \
  json_random.o          \
  json_read.o            \


all: assvm_program test_program


clean:
	make -C libpp clean
	make -C assvm clean
	make -C test  clean
	rm -f $(OBJ)


objects: $(OBJ)
	make -C libpp objects
	make -C assvm objects


archive: clean
	tar -cJ ../libmkf-git > ../libmkf-git.tar.xz


assvm_program: $(OBJ)
	rm -f assvm/assvm
	rm -f assvm/assvm_as
	make -C libpp objects
	make -C assvm

test_program: $(OBJ)
	make -C libpp objects
	make -C test




