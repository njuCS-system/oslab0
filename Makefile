NAME := plane
SRCS := $(shell find ./src -name "*.c")
LIBS += klib
include $(AM_HOME)/Makefile.app
