OBJS = prueba.o ProcesadorSet.o ProcesadorSetEntrenamiento.o SetReviews.o SetEntrenamiento.o UtilesTexto.o ProcesadorReviews.o Arbol.o RandomForest.o \
EliminadorSufijos.o ProcesadorSufijos.o ProcesadorStopWords.o
CC = g++
OFLAGS = -o
CFLAGS = -c

test.exe : $(OBJS)
	$(CC) $(OBJS) $(OFLAGS) test

prueba.o : prueba.cpp SetEntrenamiento.h ProcesadorSetEntrenamiento.h ProcesadorSet.h RandomForest.h 
	$(CC) $(CFLAGS) prueba.cpp

ProcesadorSet.o : ProcesadorSet.h ProcesadorSet.cpp SetReviews.h UtilesTexto.h ProcesadorReviews.h
	$(CC) $(CFLAGS) ProcesadorSet.cpp
	
ProcesadorSetEntrenamiento.o : ProcesadorSetEntrenamiento.h ProcesadorSetEntrenamiento.cpp ProcesadorReviews.h SetEntrenamiento.h UtilesTexto.h ProcesadorSet.h SetReviews.h
	$(CC) $(CFLAGS) ProcesadorSetEntrenamiento.cpp

SetReviews.o : SetReviews.h SetReviews.cpp
	$(CC) $(CFLAGS) SetReviews.cpp
	
SetEntrenamiento.o : SetEntrenamiento.h SetEntrenamiento.cpp SetReviews.h
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

Arbol.o : Arbol.h Arbol.cpp
	$(CC) $(CFLAGS) Arbol.cpp

RandomForest.o : RandomForest.h RandomForest.cpp Arbol.h
	$(CC) $(CFLAGS) RandomForest.cpp

clean:
	\rm *.o *~ test

