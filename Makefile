CC = g++
LFLAGS = -m64 -ltbb -std=c++11 -Wall
RFLAGS = src/Simulation.cpp src/Vecteur.cpp src/ObjetCeleste.cpp
EXEC =  SimTests SimMesures SimSystemeSolaire
FILES = data/simSystemeSolaireSeq.dat data/simSystemeSolairePar.dat data/simSystemeSolaireSeq.png data/simSystemeSolairePar.png data/mesures.dat data/temps.png data/accelerations.png

.PHONY: all clean

all: $(EXEC)

SimTests:
	$(CC) $(LFLAGS) -o SimTests src/SimTests.cpp $(RFLAGS)

SimMesures:
	$(CC) $(LFLAGS) -o SimMesures src/SimMesures.cpp $(RFLAGS) 

SimSystemeSolaire:
	$(CC) $(LFLAGS) -o SimSystemeSolaire src/SimSystemeSolaire.cpp $(RFLAGS)

tests:
	make SimTests; 
	./SimTests

mesures:
	make SimMesures; 
	./SimMesures;
	gnuplot src/gnuplotMesures.gpi;
	@echo "Graphes produits aux emplacements data/temps.png et data/accelerations.png"

orbites: 
	make SimSystemeSolaire; 
	./SimSystemeSolaire; 
	gnuplot src/gnuplotSimSystemeSolaire.gpi;
	@echo "Images produites aux emplacements data/simSystemeSolaireSeq.png et data/simSystemeSolairePar.png" 

clean:
	rm -f $(EXEC) $(FILES)
