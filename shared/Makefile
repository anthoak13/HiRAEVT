CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(RIBbitSRC)/

RLIBS     := -L$(RIBbitLIB)

CXXFLAGS  += -g $(INCLUDES) -std=c++11 -fPIC -O2 -Wall -Wpedantic

RBRUNINFO_LIB := libRBShared.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

all: $(RBRUNINFO_LIB)

$(RBRUNINFO_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

$(OBJS): $(SRCS)
	@$(CXX) $(CXXFLAGS) -c $^ $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $^ $(CFLAGS)"

install:
	@cp $(RBRUNINFO_LIB) $(RIBbitLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(RBRUNINFO_LIB)
	@rm -f $(RIBbitLIB)/$(RBRUNINFO_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
