//Tema 3 - Craciunoiu Cezar 314CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	char oras[30];
	char jucarie[30];
	int numar_jucarii;
	char directie[2];
	int mosul_e_aici;
	int cadouri_adunate;
}structura_laponia;

typedef struct{
	char nume[100];
	int numar;
}jucarie;

typedef struct{
	char oras[100];
	int numar_feluri;
	jucarie tip[100];
}structura_rezultat;

void swapint(int *a, int *b){
	int t = *a;
	*a = *b;
	*b = t;
}

void swapstr(char *a, char *b){
	char *t = (char*) malloc((strlen(a) + 1) * sizeof(char));
	strcpy(t, a);
	strcpy(a, b);
	strcpy(b, t);
	free(t);
}

int main (){
	int N, M, numar_pasi_total, pozitie_start[2], numar_pasi = 0, nr_cadouri = 0, nr_unice = 1, inceput_tip_jucarie, sfarsit_tip_jucarie, iesit_afara = 1;
	int i = 0, j = 0, k, l, cnt, ok1, ok2;
	char temp1[100], *p, temp2[100];
	structura_rezultat rezultat[100]; 
	char directii[] = { 'U', 'D', 'L', 'R' };
	int di[] = { -1, 1, 0, 0 };
	int dj[] = { 0, 0, -1, 1 };
	
	//Se citesc dimensiunile matricei de structuri
	scanf("%d %d", &N, &M);
	structura_laponia laponia[N][M];

	//Se citeste pozitia de pozitie_start
	scanf("%d %d", &pozitie_start[0], &pozitie_start[1]);

	//Se citeste numarul de pasi de efectuat
	scanf("%d\n", &numar_pasi_total);

	for(i = 0; i < N; i++)
		for(j = 0; j < M; j++){

			//Se citeste structura unui camp din matrice
			fgets(temp1, 100, stdin);

			//Se inregistreaza care e pozitia de pozitie_start
			if(pozitie_start[0] == i && pozitie_start[1] == j)
				laponia[i][j].mosul_e_aici = 1;
			else
				laponia[i][j].mosul_e_aici = 0;

			//Se completeaza orasul
			p = strtok(temp1, " \n");
			cnt = 1;
			strcpy(laponia[i][j].oras, temp1);

			while(p != NULL){

				//Se completeaza tipul de jucarie
				if(cnt == 2)
					strcpy(laponia[i][j].jucarie, p);

				//Se completeaza numarul de jucarii disponibile
				if(cnt == 3){
					strcpy(temp2, p);
					laponia[i][j].numar_jucarii = atoi(temp2);
				}

				//Se completeaza directia
				if(cnt == 4){
					strcpy(laponia[i][j].directie, p);
				}

				p = strtok(NULL, " \n");
				cnt++;
			}

			//Se pune 0 pentru numarul de jucarii adunate
			laponia[i][j].cadouri_adunate = 0;
		}

	//Cat timp nu s-au executat toti pasii
	while(numar_pasi <= numar_pasi_total){
		for(i = 0; i < N; i++){
			for(j = 0; j < M; j++){
				ok1 = 0;

				//Daca se gaseste o pozitie in matrice in care se afla mosul se realizeaza urmatoarele
				if(laponia[i][j].mosul_e_aici){

					//Daca mai sunt jucarii in fabrica se ia o jucarie
					if(laponia[i][j].numar_jucarii != 0){
						laponia[i][j].numar_jucarii--;
						laponia[i][j].cadouri_adunate++;
					}
					laponia[i][j].mosul_e_aici = 0;

					//In functie de directia in care trebuie sa mearga mosul se pune 1 in pozitia in care trebuie sa mearga in campul "mosul_e_aici"
					//daca se poate iesi din matrice se afiseaza mesajul "TOO MUCH SNOW !"
					//daca se iese din matrice ok1 ia valoarea 1, daca se mai poate merge, acesta ia valoarea 2
					//In functie de ok1 se iese decat din for-uri sau din toate structurile repetitive
					for (k = 0; k < 4; ++k){
						if (directii[k] == laponia[i][j].directie[0]){
							if (0 <= i + di[k] && i + di[k] < N && 0 <= j + dj[k] && j + dj[k] < M){
								ok1 = 2;
								laponia[i + di[k]][j + dj[k]].mosul_e_aici = 1;
							}
							else{
								if(numar_pasi < numar_pasi_total){
									ok1 = 1;
									printf("TOO MUCH SNOW !");
								}
							}
						}
					}
				}
				if(ok1 == 1 || ok1 == 2)
					break;
			}
			if(ok1 == 1 || ok1 == 2)
				break;
		}

		//Daca s-a iesit din matrice se iese si din while, daca nu, se continua mai departe
		if(ok1 == 1)
			break;
		else
			numar_pasi++;
	}

	//Daca s-a iesit din matrice si s-a facut macar un pas valoarea numarului de pasi se decrementeaza
	if(numar_pasi > 0 && ok1 != 1)
		numar_pasi--;

	//Daca nu s-a iesit din matrice nu se mai afiseaza \n la inceput 
	if(ok1 == 1)
		iesit_afara = 0;

	//Se calculeaza numarul de cadouri cadouri_adunate
	for(i = 0; i < N; i++)
		for(j = 0; j < M; j++)
			nr_cadouri += laponia[i][j].cadouri_adunate;

	//Se pune 0 pe campul numarului de feluri
	for(i = 0; i < 100; i++)
		rezultat[i].numar_feluri = 0;

	//Se muta rezultatele din structura laponia in structura rezultat
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			if(laponia[i][j].cadouri_adunate){
				ok1 = 1;
				for(k = 0; k < nr_unice; k++){

					//Daca deja se gaseste orasul trecut in rezultat
					if(strcmp(laponia[i][j].oras, rezultat[k].oras) == 0){
						ok1 = 0;
						for(l = 0; l < rezultat[k].numar_feluri; l++){
							ok2 = 1;

							//Daca jucaria se afla deja in structura tip din structura rezultat
							if(strcmp(laponia[i][j].jucarie, rezultat[k].tip[l].nume) == 0){
								ok2 = 0;
								rezultat[k].tip[l].numar += laponia[i][j].cadouri_adunate;
							}
						}

						// Daca o jucarie nu se afla in structura rezultat in acel oras se adauga jucaria
						if(ok2){
							strcpy(rezultat[k].tip[rezultat[k].numar_feluri].nume, laponia[i][j].jucarie);
							rezultat[k].tip[rezultat[k].numar_feluri].numar = laponia[i][j].cadouri_adunate;
							rezultat[k].numar_feluri++;
						}
					}
				}
				//Daca orasul este nou, se adauga in structura rezultat si se aduaga si prima jucarie
				if(ok1){
					strcpy(rezultat[nr_unice].oras, laponia[i][j].oras);
					rezultat[nr_unice].tip[0].numar = laponia[i][j].cadouri_adunate;
					rezultat[nr_unice].numar_feluri++;
					strcpy(rezultat[nr_unice].tip[0].nume, laponia[i][j].jucarie);
					nr_unice++;
				}
			}
		}
	}

	//Se sorteaza lexicografic dupa numele oraselor
	for(i = 0; i < nr_unice; i++){
		for(j = i; j < nr_unice; j++){
			//Daca 2 orase nu sunt aranjate bine se interschimba toate campurile dintre ele, in functie de cel cu mai multe elemente
			if(strcmp(rezultat[i].oras, rezultat[j].oras) > 0){
				swapstr(rezultat[i].oras, rezultat[j].oras);
				if(rezultat[i].numar_feluri >= rezultat[j].numar_feluri){
					for(k = 0; k < rezultat[i].numar_feluri; k++){
						swapint(&rezultat[i].tip[k].numar, &rezultat[j].tip[k].numar);
						swapstr(rezultat[i].tip[k].nume, rezultat[j].tip[k].nume);
					}
				}
				else{
					for(k = 0; k < rezultat[j].numar_feluri; k++){
						swapint(&rezultat[i].tip[k].numar, &rezultat[j].tip[k].numar);
						swapstr(rezultat[i].tip[k].nume, rezultat[j].tip[k].nume);
					}
				}
				swapint(&rezultat[i].numar_feluri, &rezultat[j].numar_feluri);
			}

		}
	}

	//Sortare dupa numarul de jucarii din fiecare oras
	for(i = 0; i < nr_unice; i++){

		//Pentru fiecare oras se foloseste Bubble Sort pentru a se sorta elementele
		for(j = 0; j < rezultat[i].numar_feluri; j++){
			for(k = j; k < rezultat[i].numar_feluri; k++){
				if(rezultat[i].tip[j].numar < rezultat[i].tip[k].numar){
					swapint(&rezultat[i].tip[j].numar, &rezultat[i].tip[k].numar);
					swapstr(rezultat[i].tip[j].nume, rezultat[i].tip[k].nume);
				}
			}
		}
	}

	//Sortare dupa nume unde numarul de jucarii este egal
	for(i = 1; i < nr_unice; i++){
		inceput_tip_jucarie = 0;

		while(inceput_tip_jucarie != rezultat[i].numar_feluri){
			sfarsit_tip_jucarie = rezultat[i].numar_feluri;

			//Initial se pleaca de la inceput si se verifica pana unde numarul de jucarii este egal
			for(k = inceput_tip_jucarie; k < sfarsit_tip_jucarie; k++){
				if(rezultat[i].tip[k].numar != rezultat[i].tip[k+1].numar){
					sfarsit_tip_jucarie = k+1;
					break;
				}
			}

			//Se interschimba jucariile cu scopul de a se sorta
			for(j = inceput_tip_jucarie; j < sfarsit_tip_jucarie; j++){
				for(k = j; k < sfarsit_tip_jucarie; k++){
					if(strcmp(rezultat[i].tip[j].nume, rezultat[i].tip[k].nume) > 0){
						swapstr(rezultat[i].tip[j].nume, rezultat[i].tip[k].nume);
					}
				}
			}

			//Pentru urmatorul set de jucarii se porneste de la sfarsitul primului set
			inceput_tip_jucarie = sfarsit_tip_jucarie;
		}	
	}

	//In fiecare oras, daca se gasesc doua inregistrari ale aceleiasi jucarii se pune 0 pe cea cu mai putine elemente,
	//deoarece deja au fost adunate in aceasta toate jucariile de acest tip
	for(i = 1; i < nr_unice; i++){
		for(j = 0; j < rezultat[i].numar_feluri; j++){
			for(k = j+1; k < rezultat[i].numar_feluri; k++){
				if(strcmp(rezultat[i].tip[j].nume, rezultat[i].tip[k].nume) == 0){
					if(rezultat[i].tip[j].numar <= rezultat[i].tip[k].numar){
						rezultat[i].tip[j].numar = 0;
					}
					else
						rezultat[i].tip[k].numar = 0;
				}
			}
		}
	}

	//Se afiseaza rezultatele, respectandu-se structura ceruta
	if(iesit_afara == 0)
		printf("\n%d\n", numar_pasi);
	else
		printf("%d\n", numar_pasi);
	printf("%d\n", nr_cadouri);
	for(i = 1; i < nr_unice; i++){
		printf("%s:\n", rezultat[i].oras);
		for(j = 0; j < rezultat[i].numar_feluri; j++){
			if(rezultat[i].tip[j].numar > 0)
				printf("  %d %s\n", rezultat[i].tip[j].numar, rezultat[i].tip[j].nume);
		}
	}

	return 0;
}