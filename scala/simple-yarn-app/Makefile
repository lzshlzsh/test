
SCALAC := scalac #fsc
JAR := jar

CLASS_DIR := class
__mkdir := $(shell for i in ${CLASS_DIR}; do [ -d $$i ] || mkdir -p $$i; done)

HADOOP_HOME := ${HOME}/spark/hadoop-2.2.0
LIBS := $(wildcard ${HADOOP_HOME}/share/hadoop/common/hadoop-common-2.2.0.jar \
	${HADOOP_HOME}/share/hadoop/yarn/*.jar)
LIBS := $(shell echo ${LIBS} | tr -s ' ' ':')

SCALA_FLAGS := -cp ${LIBS} -d ${CLASS_DIR} #-verbose
JAR_FLAGS := -C ${CLASS_DIR}

SRC := $(wildcard *.scala)
TARGET := simple_yarn_app.jar

.PHONY: all clean

all: ${TARGET}

${TARGET}: ${SRC}
	${SCALAC} ${SCALA_FLAGS} $^
	${JAR} cf $@ ${JAR_FLAGS} .

clean:
	${RM} -r ${TARGET} ${CLASS_DIR}
