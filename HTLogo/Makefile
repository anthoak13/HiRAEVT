CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(HiRAEVTSRC)/
INCLUDES  := -I$(HiRAEVTSRC)/logo

RLIBS     := -L$(HiRAEVTLIB)

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

HTLOGO_LIB := libHTLogo.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(HTLOGO_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

$(HTLOGO_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

install:
	@cp $(HTLOGO_LIB) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(HTLOGO_LIB)
	@rm -f $(HiRAEVTLIB)/$(HTLOGO_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
