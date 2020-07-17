VERPAPI=5_7
EXE=papi-test-${VERPAPI}
SRC=papi-test-${VERPAPI}.c
CC?=gcc

FLAGS=-O0
INC=-I${EBROOTPAPI}/include
LIB=${EBROOTPAPI}/lib/libpapi.a

all: clean ${EXE} run
${EXE}: ${SRC}
        ${CC} ${FLAGS} ${INC} -o ${EXE} ${SRC} ${LIB}

run:
        ./${EXE}

clean:
        rm -f ${EXE}
