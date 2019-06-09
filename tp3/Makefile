C=gcc

BUILD_DIR = ./build
SRC_DIR = ./src
 
all: main 

####################################################
#                                                  #
#                  Header Files                    #
#                                                  #
####################################################

Models.o: ${SRC_DIR}/models/Models.h ${SRC_DIR}/models/Models.c
	${C} -c ${SRC_DIR}/models/Models.c -g -o ${BUILD_DIR}/Models.o

GraphUtilities.o: ${SRC_DIR}/utility/GraphUtilities.h ${SRC_DIR}/utility/GraphUtilities.c
	${C} -c ${SRC_DIR}/utility/GraphUtilities.c -g -o ${BUILD_DIR}/GraphUtilities.o

####################################################
#                                                  #
#                     MAIN                         #
#                                                  #
####################################################

tp3.o: ${SRC_DIR}/models/Models.h ${SRC_DIR}/utility/GraphUtilities.h ${SRC_DIR}/tp3.h
	${C} -c ${SRC_DIR}/tp3.c -g -o ${BUILD_DIR}/tp3.o

main: Models.o GraphUtilities.o tp3.o
	${C} -g -o ${BUILD_DIR}/tp3 -lm main.c ${BUILD_DIR}/*.o
 
# Rule for cleaning files generated during compilation. 
# Call 'make clean' to use it 
clean: 
	rm -rf ${BUILD_DIR}/*.o    

clean_windows:
	del /S "%dir%\build\*.o"    

run:
	./build/tp3 ${citiesFile}

run_windows:
	./build/tp3.exe

