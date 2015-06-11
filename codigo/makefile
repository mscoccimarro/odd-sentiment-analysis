OBJS = obtenerSetEntrenamiento.o SetEntrenamiento.o ProcesadorSetEntrenamiento.o UtilesTexto.o ProcesadorReviews.o \
EliminadorSufijos.o ProcesadorSufijos.o ProcesadorStopWords.o
CC = g++
OFLAGS = -o
CFLAGS = -c

test.exe : $(OBJS)
	$(CC) $(OBJS) $(OFLAGS) test

obtenerSetEntrenamiento.o : obtenerSetEntrenamiento.cpp ProcesadorSetEntrenamiento.h SetEntrenamiento.h
	$(CC) $(CFLAGS) obtenerSetEntrenamiento.cpp

ProcesadorSetEntrenamiento.o : ProcesadorSetEntrenamiento.h ProcesadorSetEntrenamiento.cpp ProcesadorReviews.h SetEntrenamiento.h UtilesTexto.h
	$(CC) $(CFLAGS) ProcesadorSetEntrenamiento.cpp

SetEntrenamiento.o : SetEntrenamiento.h SetEntrenamiento.cpp
	$(CC) $(CFLAGS) SetEntrenamiento.cpp

UtilesTexto.o : UtilesTexto.h UtilesTexto.cpp 
	$(CC) $(CFLAGS) UtilesTexto.cpp

ProcesadorReviews.o : ProcesadorReviews.h ProcesadorReviews.cpp UtilesTexto.h EliminadorSufijos.h ProcesadorStopWords.h 
	$(CC) $(CFLAGS) ProcesadorReviews.cpp

EliminadorSufijos.o : EliminadorSufijos.h EliminadorSufijos.cpp ProcesadorSufijos.h UtilesTexto.h
	$(CC) $(CFLAGS) EliminadorSufijos.cpp

ProcesadorSufijos.o : ProcesadorSufijos.h ProcesadorSufijos.cpp UtilesTexto.h
	$(CC) $(CFLAGS) ProcesadorSufijos.cpp

ProcesadorStopWords.o : ProcesadorStopWords.h ProcesadorStopWords.cpp
	$(CC) $(CFLAGS) ProcesadorStopWords.cpp

clean:
	\rm *.o *~ test

