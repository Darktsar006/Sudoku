# Makefile SUDOKU SOLVER
# TRAORE Oumar
#L2-Informatique Groupe 2.2

# Le compilateur
CC=gcc
# Les options de compilation
CFLAGS=-Wall
# La liste des fichiers source du repertoire courant
SRC=$(wildcard *.c) 
# La liste des fichiers objet correspondant
OBJ=$(SRC:.c=.o)

# La compilation finale
Sudoku_Solver_TRAORE&MOREAU: $(OBJ)
	@$(CC) $^ -o $@

%.o : %.c
	@$(CC) -o $@ -c $^ $(CFLAGS) # La compilation separee de chaque .c

# Pour nettoyer le repertoire courant. Utilisation : make clean
clean:
	@rm -f *.o # Suppression de tous les fichiers objets
	@rm -f *~ # et tous les fichiers temporaires
	
#$@: Le nom de la cible
#$^: La liste des dependances
#@commande : Permet de desactiver l'echo de la commande
