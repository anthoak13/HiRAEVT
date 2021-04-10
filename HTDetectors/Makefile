#Get the list of subdirectories

DIRS := $(dir $(wildcard $(PWD)/../*/))
INCLS := $(sort $(patsubst %, "\n%", ${DIRS}))

test:
	@echo ${DIRS}
	@echo ${INCLS}
