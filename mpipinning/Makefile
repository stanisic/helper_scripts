EXE=mpipinning
SRC=mpipinning.c
MPICC?=mpicc

CFLAGS += $(shell pkg-config --cflags hwloc)
LDLIBS += $(shell pkg-config --libs hwloc)

all: clean ${EXE}

${EXE}: ${SRC}
        ${MPICC} -o ${EXE} ${SRC} -lhwloc

clean:
        rm -f ${EXE}
