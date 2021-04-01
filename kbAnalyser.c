#include <stdio.h>
#include <stdlib.h>

unsigned int **tri(unsigned int *record, unsigned int size);



int main(int argc, char *argv[]) {

	 if (argc < 2)
			return 1;

	 unsigned int nbCaracteresASCII = 256;
	 unsigned int *record = calloc(nbCaracteresASCII, sizeof(unsigned int));


	 // Analyse autant de fois qu'il y a de fichiers passés en argv
	 for (int numArgc = 1 ; numArgc < argc ; numArgc++) {
			FILE *f = fopen(argv[numArgc], "r");
			if (!f) {
				 printf("No such file : %s\n", argv[numArgc]);
				 return 1;
			}

			unsigned char buffer;
			while (!feof(f)) {
				 fread(&buffer, 1, 1, f);
				 record[(unsigned int)buffer]++;
			}
	 }

	 // Fin de l'analyse, tri des résultats par ordre décroissant
	 unsigned int **recordTries = tri(record, nbCaracteresASCII);

	 // Fin du tri, affichage des résultats
	 for (long unsigned int i = 0 ; i < nbCaracteresASCII ; i++) {
			if (recordTries[i][1] == 0)
				 continue;

			switch (recordTries[i][0]) {
				 case 32: 
						printf("espace"); 
						break;
				 case 9: 
						printf("tabulation"); 
						break;
				 default:
						printf("%c", (unsigned char)recordTries[i][0]);
						break;
			}
			printf(" : %u occurence", recordTries[i][1]);
			if (recordTries[i][1] > 1)
				 printf("s");

			printf(" (ASCII : %u)\n", recordTries[i][0]);
	 }

	 return 0;
}



unsigned int **tri(unsigned int *record, unsigned int size) {


	 // Initialise le tableau ** qui contient la valeur int du caractère et son nom d'apparitions

	 unsigned int **tri = malloc(size * 8);
	 for (long unsigned int i = 0 ; i < size ; i++)
			tri[i] = calloc(2, sizeof(unsigned int));


	 unsigned int indexDuMax = 0, max = record[indexDuMax];

	 for (long unsigned int i = 0 ; i < size ; i++) {
			for (long unsigned int j = 0 ; j < size ; j++) {
				 if (record[j] > max) {
						indexDuMax = j;
						max = record[j];
				 }
			}
			tri[i][0] = indexDuMax;
			tri[i][1] = max;
			max = 0;
			record[indexDuMax] = 0;
	 }

	 return tri;
}
