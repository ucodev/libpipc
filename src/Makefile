CC=`cat ../.compiler`
ECFLAGS=`cat ../.ecflags`
CCFLAGS=
LDFLAGS=`cat ../.libs`
ELFLAGS=`cat ../.elflags`
ARCHFLAGS=`cat ../.archflags`
INCLUDEDIRS=-I../include
OBJS=pipc.o
TARGET=libpipc.so
SYSLIBDIR=`cat ../.dirlib`

all:
	${CC} ${ECFLAGS} ${CCFLAGS} ${ARCHFLAGS} ${INCLUDEDIRS} -c pipc.c
	${CC} -shared -o ${TARGET} ${OBJS} ${LDFLAGS} ${ELFLAGS}

install:
	cp ${TARGET} ${SYSLIBDIR}/

clean:
	rm -f ${OBJS}
	rm -f ${TARGET}

