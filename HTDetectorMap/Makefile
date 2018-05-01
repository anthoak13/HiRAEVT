CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(HiRAEVTSRC)/
INCLUDES  := -I$(HiRAEVTSRC)/shared
INCLUDES  += -I$(HiRAEVTSRC)/HTDetectorMap

RLIBS     := -L$(HiRAEVTLIB) -lHTShared

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

HTDETECTORMAP_LIB := libHTDetectorMap.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(HTDETECTORMAP_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

$(HTDETECTORMAP_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

install:
	@cp $(HTDETECTORMAP_LIB) $(HiRAEVTLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(HTDETECTORMAP_LIB)
	@rm -f $(HiRAEVTLIB)/$(HTDETECTORMAP_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
