OBJS = obtenerSetEntrenamiento.o SetEntrenamiento.o ProcesadorSetEntrenamiento.o UtilesTexto.o ProcesadorReviews.o Puntuacion.o \
EliminadorSufijos.o ProcesadorSufijos.o Tags.o ProcesadorStopWords.o
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

UtilesTexto.o : UtilesTexto.h UtilesTexto.cpp Puntuacion.h 
	$(CC) $(CFLAGS) UtilesTexto.cpp

ProcesadorReviews.o : ProcesadorReviews.h ProcesadorReviews.cpp UtilesTexto.h EliminadorSufijos.h ProcesadorStopWords.h Tags.h
	$(CC) $(CFLAGS) ProcesadorReviews.cpp

Puntuacion.o : Puntuacion.h Puntuacion.cpp
	$(CC) $(CFLAGS) Puntuacion.cpp

EliminadorSufijos.o : EliminadorSufijos.h EliminadorSufijos.cpp ProcesadorSufijos.h UtilesTexto.h
	$(CC) $(CFLAGS) EliminadorSufijos.cpp

ProcesadorSufijos.o : ProcesadorSufijos.h ProcesadorSufijos.cpp UtilesTexto.h
	$(CC) $(CFLAGS) ProcesadorSufijos.cpp

Tags.o : Tags.h Tags.cpp
	$(CC) $(CFLAGS) Tags.cpp

ProcesadorStopWords.o : ProcesadorStopWords.h ProcesadorStopWords.cpp
	$(CC) $(CFLAGS) ProcesadorStopWords.cpp

clean:
	\rm *.o *~ test

