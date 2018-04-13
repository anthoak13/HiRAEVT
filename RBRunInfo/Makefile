CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(RIBbitSRC)/
INCLUDES  += -I$(RIBbitSRC)/RBRunInfo
INCLUDES  += -I$(RIBbitSRC)/electronics

RLIBS     := -L$(RIBbitLIB) -lRBElectronics

CXXFLAGS  += -g $(INCLUDES) -fPIC

RBRUNINFO_LIB := libRBRunInfo.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

$(RBRUNINFO_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^"

$(OBJS): $(SRCS)
	@$(CXX) $(CXXFLAGS) -c $^ $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $^ $(CFLAGS)"

install:
	@cp $(RBRUNINFO_LIB) $(RIBbitLIB)/.

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
