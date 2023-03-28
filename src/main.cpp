#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdlib>

bool fin(char mot[], char motT[], int len, int pts){
	if (pts == 12){
		std::cout << "Dommage, le petit bonome est mort ;( vous avez perdu!" << std::endl;
		return true;
	}

	for (int i=0; i<len; i++){
		if (mot[i] != motT[i]){
			return false;
		}
	}
	std::cout << "Bien joué vous avez trouver le mot." << std::endl;
	return true;
}

void afficherMot(char mot[], int l){
	std::cout << std::endl;
	for (int i=0; i<l; i++){
		if (mot[i] == ' '){
			std::cout << '_';
		}else{
			std::cout << mot[i];
		}
	}
	std::cout << '\n' << std::endl;
}

void afficherimg(char img[], int pts){
	std::string ligne;
	std::string filename = "/home/cptbb/dev/built/data/pendu/img/";
	filename += img;

	std::ifstream fic (filename);

	if (!fic.is_open()){
		std::cout << "Erreur : ne peut pas ouvrir le fichier img/$filename" << std::endl;
	}

	for (int i=0; i<pts*5; i++){
		getline(fic, ligne);
	}
	for (int i=0; i<5; i++){
		getline(fic, ligne);
		std::cout << ligne << std::endl;
	}
}

int main(int argc, char* argv[]){
	(void)argc;
	char lettre;
	char fausse[50];
	int nbFausse = 0;
	int pts = 0;
	bool trouve = false;
	char img[50];
	std::string motR;
	int nbMot = 0;

	if (argv[1] == NULL){
		strncpy(img, "default\0", 8);
	}else{
		strncpy(img, argv[1], (int)sizeof(argv[1]));
	}

	std::ifstream fic ("/home/cptbb/dev/built/data/pendu/dico.txt");
	if (!fic.is_open()){
		std::cout << "Erreur : ne peut pas ouvrir le fichier dico.txt" << std::endl;
		return -1;
	}
	while (fic.peek()!=EOF){
		getline(fic, motR);
		nbMot++;
	}
	fic.clear();
	fic.seekg(0);

	srand(time(0));
	int random = rand() % nbMot;
	for (int i=0; i<random; i++){
		getline(fic, motR);
	}

	char mot[motR.length()+1];
	int len = int(sizeof(mot))-1;
	for (int i=0; i<int(sizeof(motR)); i++){
		mot[i] = motR[size_t(i)];
	}
	char motT[sizeof(mot)];

	fic.close();


	for (int i=0; i<len; i++){ motT[i] = ' '; }

	afficherMot(motT, len);
	while (!fin(mot, motT, len, pts)){
		trouve = false;
		std::cout << "entrez une lettre : ";
		std::cin >> lettre;

		fausse[nbFausse] = lettre;
		nbFausse++;

		for (int i=0; i<len; i++){
			if (mot[i] == lettre){
				motT[i] = lettre;
				trouve = true;
			}
		}
		
		if (!trouve){ pts++; }

		afficherimg(img, pts);
		afficherMot(motT, len);
		std::cout << "lettre tenté : " << fausse << std::endl;
	}

	return 0;
}
