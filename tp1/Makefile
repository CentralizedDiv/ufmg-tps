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
	${C} -c ${SRC_DIR}/models/Models.c -o ${BUILD_DIR}/Models.o

FileReader.o: ${SRC_DIR}/utility/FileReader.h ${SRC_DIR}/utility/FileReader.c
	${C} -c ${SRC_DIR}/utility/FileReader.c -o ${BUILD_DIR}/FileReader.o

####################################################
#                                                  #
#                     MAIN                         #
#                                                  #
####################################################

tp1.o: ${SRC_DIR}/models/Models.h ${SRC_DIR}/utility/FileReader.h ${SRC_DIR}/tp1.h
	${C} -c ${SRC_DIR}/tp1.c -o ${BUILD_DIR}/tp1.o

main: Models.o FileReader.o tp1.o
	${C} -g -o ${BUILD_DIR}/tp1 main.c ${BUILD_DIR}/*.o
 
# Rule for cleaning files generated during compilation. 
# Call 'make clean' to use it 
clean: 
	rm -rf ${BUILD_DIR}/*.o    

clean_windows:
	del /S "%dir%\build\*.o"    

run:
	./build/tp1 ${universitiesFile} ${applicantsFile}

run_windows:
	./build/tp1.exe

