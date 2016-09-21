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




ifeq ($(ccache),1)
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


OBJ +=                        \
  assvm_memory.o              \
  assvm_instruction.o         \
  assvm_instructionsource.o   \
  assvm_element.o             \
  assvm_block.o               \
  assvm_operand.o             \
  assvm_data.o                \
  assvm_program.o             \
  assvm_context.o             \


CMPLR_OBJ =                                      \
  libcmplr/expression_node.o                     \
  libcmplr/expression_operand.o                  \
  libcmplr/expression_operand__read_character.o  \
  libcmplr/expression_operand__read_integer.o    \
  libcmplr/expression_element.o                  \
  libcmplr/expression_operator.o                 \
  libcmplr/cmplr_type.o                          \
  libcmplr/cmplr_type__make.o                    \
  libcmplr/cmplr_type__is.o                      \
  libcmplr/cmplr_type__compile.o                 \
  libcmplr/cmplr_parameter.o                     \
  libcmplr/cmplr_signature.o                     \
  libcmplr/cmplr_function.o                      \
  libcmplr/cmplr_variable.o                      \
  libcmplr/cmplr_constant.o                      \
  libcmplr/cmplr_declaration.o                   \
  libcmplr/cmplr_declaration__read.o             \
  libcmplr/cmplr_foldcontext.o                   \
  libcmplr/cmplr_precontext.o                    \
  libcmplr/cmplr_context.o                       \
  libcmplr/cmplr_block.o                         \
  libcmplr/cmplr_branchnode.o                    \
  libcmplr/cmplr_globalscope.o                   \
  libcmplr/cmplr_statement.o                     \
  libcmplr/cmplr_statement__read.o               \
  libcmplr/cmplr_statement__read_ctrl.o          \


all: $(OBJ) assvm assvm_as


clean:
	rm -f $(OBJ) $(CMPLR_OBJ) assvm assvm_as


objects: $(OBJ) $(CMPLR_OBJ)




assvm: $(OBJ) $(CMPLR_OBJ) assvm.cpp
	$(CXX) -o $@ assvm.cpp $(OBJ) $(CMPLR_OBJ) ../*.o ../libpp/*.o $(CXXFLAGS) $(LDFLAGS)

assvm_as: $(OBJ) assvm_as.cpp
	$(CXX) -o $@ assvm_as.cpp $(OBJ) ../*.o ../libpp/*.o $(CXXFLAGS) $(LDFLAGS)




