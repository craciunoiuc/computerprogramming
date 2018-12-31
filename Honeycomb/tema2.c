//Craciunoiu Cezar 314CA

#include <stdio.h>

//se construieste o functie similara 'atoi' pentru a se evita includerea intregii biblioteci stdlib.h
int atoi(char *str)
{
    int numar = 0;
    while((*str >= '0') && (*str <= '9'))
    {
        numar = (numar * 10) + (*str - '0');
        str++;
    }

    return numar;
}

//se construieste o functie similara 'strlen' pentru a se evita includerea intregii biblioteci string.h
int lungime_sir(char *x){
	int i = 0;
	while(x[i] != '\0'){
		i++;
	}
	return i;
}

//functie care aseaza caracterele '_' din primele 2 linii ale fagurelui
void inceput_fagure(int pozitie, int numar_coloane, char fagure[][1000]){
	int i;
	if(pozitie == 'R'){
		for(i = 1; i <= 2*numar_coloane; i = i + 4) 
			fagure[0][i] = '_';
		for(i = 3; i <= 2*numar_coloane; i = i + 4)
			fagure[1][i] = '_';
	}
	else{
		for(i = 1; i <= 2*numar_coloane; i = i + 4)
			fagure[1][i] = '_';
		for(i = 3; i <= 2*numar_coloane; i = i + 4)
			fagure[0][i] = '_';
		}
}

//functie care construieste fagurele
void construire_fagure(int i, int k, int j, int numar_matci, char fagure[][1000], int pozitii_matci[][152]){
	int l;

	//patru if-uri care construiesc fagurele in functie de pozitia precedenta
	if(fagure[k-1][j+1] == '_' || fagure[k-1][j] == '\\')
		fagure[k][j] = '/';
	if(fagure[k-1][j-1] == '_' || fagure[k-1][j] == '/')
		fagure[k][j] = '\\';
	if(fagure[k][j-1] == '/')
		fagure[k][j] = ' ';
	if(fagure[k][j-1] == '\\')
		fagure[k][j] = '_';

	//if care verifica daca pozitia actuala este cea pe care se pot aseza matci
	if(fagure[k][j-1] == '/' && fagure[k-1][j] == '_'){

		//for care trece prin fiecare element din matricea in care sunt pastrate pozitiile matcilor si verifica daca exista acea pozitie
		for(l = 0; l < numar_matci; l++){
			if(i == pozitii_matci[0][l] -1){

				//daca coloana este egala cu i, iar linia este egala cu de 2 ori -1(pentru coloanele ridicare)
				//sau de 2 ori (pentru cele coborate), atunci se pune Q in acea casuta.
				if(2*pozitii_matci[1][l]-1 == k || 2*pozitii_matci[1][l] == k)
					fagure[k][j] = 'Q';
			}
		}
	}

}

//functie care verifica daca coloana actuala este ridicata sau coborata pentru ca stii pana unde sa lucreze
int pana_unde_merge(int i, char pozitie){
	if(i % 2 == 0){
		if(pozitie == 'R')
			return 0;
		else
			return 1;
	}
	else{
		if(pozitie == 'R')
			return 1;
		else
			return 0;
	}
}

//functie care afiseaza fagurele
void afisare(int lungime, int numar_coloane, char fagure[][1000]){
	int i, j;
	for(i = 0; i < lungime; i++){
		for(j = 0; j < 2*numar_coloane+1; j++)
			printf("%c", fagure[i][j]);
		if(i < lungime)
			printf("\n");
	}
}
int main(){
	int marimi_coloane[52], i, j, numar_coloane, numar_matci, pozitii_matci[2][152], k, contor, lungime_maxima, maxip, pas, ok, coloana_tablou_matci, linie_tablou_matci, lungime;
	char pozitie, t[252], fagure[1000][1000], temp[5];


	while(fgets(t, 251 , stdin)){

		//toate variabilele si toate tablourile sunt reinitializate
		for(i = 0; i < 51; i++)
				marimi_coloane[i] = 0;
		for(i = 0; i < 151; i++){
				pozitii_matci[0][i] = 0;
				pozitii_matci[1][i] = 0;
		}

		pozitie = '0';
		ok = 0;
		coloana_tablou_matci = 0;
		linie_tablou_matci = 1;
		contor = 0;
		pas = 0;
		maxip = 0;
		lungime_maxima = 0;
		
		for ( i = 0; i < 1000; i++)
			for ( j = 0; j < 1000; j++)
				fagure[i][j] = ' ';

		//se incepe construirea tablourilor marimi_coloane, pozitii_matci, precum si identificarea variabilei pozitie ce pastreaza tipul primei coloane
		lungime = lungime_sir(t);
		for(i = 0; i < lungime; i++){
			if(ok){
				//cat timp se afla intre 2 spatii se salveaza numarul dintre ele
				if(t[i] != ' '){
						temp[contor] = t[i];
						contor++;
					}
					else{
						//daca se ajunge la spatiu se pune NULL pe pozitia urmatoare
						temp[contor] = '\0';
						//contorul linie_tablou_matci verifica pe ce linie trebuie pus numarul obtinut
						if(linie_tablou_matci){
							pozitii_matci[0][coloana_tablou_matci] = atoi(temp);
							linie_tablou_matci = 0;
						}
						else{
							//coloana este incrementata doar atunci cand s-a asezat pe a doua linie un numar
							pozitii_matci[1][coloana_tablou_matci] = atoi(temp);
							coloana_tablou_matci++;
							linie_tablou_matci = 1;
						}
						contor = 0;
					}
			}
			else{
				//daca intalneste caracterul R sau C, acesta este salvat in variabila pozitie, se trece la pasul urmator, iar ok devine 1 pentru a se putea procesa reginele
				if(t[i] == 'R' || t[i] == 'C'){
					pozitie = t[i];
					ok = 1;
					contor = 0;
					i++;
				}
				else{
					//cat timp se afla intre 2 spatii acesta salveaza cifrele intr-un vector auxiliar si se mareste un contor
					if(t[i] != ' '){
						temp[contor] = t[i];
						contor++;
					}
					else{
						//cand se ajunge la un spatiu, se pune NULL, iar numarul salvat in vectorul de char auxiliar este transformat in int, contorul fiind adus la loc la 0
						temp[contor] = '\0';
						marimi_coloane[pas] = atoi(temp);
						pas++;
						contor = 0;
					}
				}
			}
		}
		//ultimul element este asezat pe a lui pozitie
		temp[contor] = '\0';
		pozitii_matci[1][coloana_tablou_matci] = atoi(temp);
		numar_coloane = pas;
		if(coloana_tablou_matci != 0)
			numar_matci = coloana_tablou_matci+1;

		inceput_fagure(pozitie, numar_coloane, fagure);

		for(i = 0; i < numar_coloane; i++){
			for(j = 2*i; j < 2*i+3; j++){

				contor = pana_unde_merge(i, pozitie);

				for(k = 0; k < 2 * marimi_coloane[i]+1+contor; k++){
					construire_fagure(i, k, j, numar_matci, fagure, pozitii_matci);
				}
			}
		}

		//for care calculeaza lungimea coloanei maxime
		for(i = 0; i < numar_coloane; i++){
			
			contor = pana_unde_merge(i, pozitie);

			if(lungime_maxima < marimi_coloane[i]){
				lungime_maxima = marimi_coloane[i];
				maxip = contor;
			}
		}
		//daca prima coloana este ridicata, si toate coloanele sunt de lungime 1, atunci se creste cu 1 lungimea ce trebuie afisata
		if(pozitie == 'R'){
			for(i = 0; i < numar_coloane; i++){
				if(marimi_coloane[i] != 1){
					break;
				}
				else{
					if(i == numar_coloane-1)
						maxip++;
				}
			}
		}

		lungime = 2*lungime_maxima+1+maxip;
		afisare(lungime, numar_coloane, fagure);
	}
	return 0;
}