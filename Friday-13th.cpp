#define _CRT_SECURE_NO_WARNINGS 0
#include<iostream>
#include<stdio.h>
#include<time.h>	
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define max_row_size 500
#define max_liczba_cyfr 3
#define max_dl_koloru 10
#define max_kolorow 8
#define PLIK_TALIA "talia.txt"
#define PLIK_STANGRY "stan_gry.txt"
#define PLIK_ZRODLO "stan_gry.txt"
#define ilosc_losowan 100
using namespace std;
enum kolory_t {
	green, blue, red, violet, yellow, white, black
};
typedef struct {
	int l_kociolkow;
	int l_zielonych;
	int w_zielonych;
	int l_kart;
}wejscie;
typedef struct {
	int kolor;
	int wartosc;
}karty;
typedef struct {
	int id;
	karty* reka;
	int handsize;
	karty* deck;
	int decksize;
	int punkty;
}gracz;
typedef struct {
	int id;
	karty* stos_kart;
	int ilosc_kart;
	int kolor_kociolka;
	int suma_wartosci_na_kociolku;
}kociolek;
void zamien_karty(karty* talia, int indeks1, int indeks2) {
	karty pomoc = talia[indeks1];
	talia[indeks1] = talia[indeks2];
	talia[indeks2] = pomoc;
}
void tasuj_talie(karty* talia, int liczba_kart) {
	srand(time(NULL));
	for (int i = 0; i < ilosc_losowan; i++) {
		zamien_karty(talia, rand() % liczba_kart, rand() % liczba_kart);
	}
}
void generuj_talie(karty* talia, wejscie wejscie, int* tab_wartosci)
{
	int i = 0;
	for (i; i < wejscie.l_zielonych; i++)
	{
		talia[i].kolor = 0;
		talia[i].wartosc = wejscie.w_zielonych;
	}
	for (int k = 0; k < wejscie.l_kociolkow; k++)
	{
		for (int o = 0; o < wejscie.l_kart; o++)
		{
			talia[i].kolor = k + 1;
			talia[i].wartosc = tab_wartosci[o];
			i++;
		}
	}
}
void zwroc_kolor(int k)
{
	kolory_t kolor;
	kolor = green;
	if (kolor == k) cout << "green" << " ";
	kolor = blue;
	if (kolor == k) cout << "blue" << " ";
	kolor = red;
	if (kolor == k) cout << "red" << " ";
	kolor = violet;
	if (kolor == k) cout << "violet" << " ";
	kolor = yellow;
	if (kolor == k) cout << "yellow" << " ";
	kolor = white;
	if (kolor == k) cout << "white" << " ";
	kolor = black;
	if (kolor == k) cout << "black" << " ";
}
void zwroc_kolor_plik(int k,FILE* talia_file)
{
	kolory_t kolor;
	kolor = green;
	if (kolor == k) fprintf(talia_file, "%s ", "green");
	kolor = blue;
	if (kolor == k) fprintf(talia_file, "%s ", "blue");
	kolor = red;
	if (kolor == k) fprintf(talia_file, "%s ", "red");
	kolor = violet;
	if (kolor == k) fprintf(talia_file, "%s ", "violet");
	kolor = yellow;
	if (kolor == k) fprintf(talia_file, "%s ", "yellow");
	kolor = white;
	if (kolor == k) fprintf(talia_file, "%s ", "white");
	kolor = black;
	if (kolor == k) fprintf(talia_file, "%s ", "black");
}
int znajdz_najw(int* tablica, int size) {
	int max = tablica[0];
	for (int i = 0; i < size; i++) {
		if (max < tablica[i]) max = tablica[i];
	}
	return max;
}
int zwroc_indeks_najmn(int* tablica, int size, int start) {
	int min = tablica[start], indeks = start;
	for (int i = start; i < size; i++) {
		if (min > tablica[i]) {
			min = tablica[i];
			indeks = i;
		}
	}
	return indeks;
}
void zamien(int* tablica, int indeks1, int indeks2) {
	int pomoc = tablica[indeks1];
	tablica[indeks1] = tablica[indeks2];
	tablica[indeks2] = pomoc;
}
void posortuj_tablice(int* tablica, int size) {
	int indeks;
	for (int i = 0; i < size; i++) {
		indeks = zwroc_indeks_najmn(tablica, size, i);
		zamien(tablica, indeks, i);
	}
}
void wypisz_talie(karty* talia, int liczba_kart)
{
	FILE* talia_file;
	talia_file = fopen(PLIK_TALIA, "w");
	if (talia_file != NULL){
	for (int i = 0; i < liczba_kart; i++) {
		fprintf(talia_file, "%d ", talia[i].wartosc);
		//cout << talia[i].wartosc << " ";
		zwroc_kolor_plik(talia[i].kolor,talia_file);
		//fprintf(talia_file,"%s",zwroc_kolor(talia[i].kolor);)
	}
	fclose(talia_file);
	}
	else cout << "Blad pliku";
	
}
void przypisz_wartosci_kociolkom(kociolek* kociolki, int k) {
	for (int i = 0; i < k; i++) {
		kociolki[i].id = i + 1;
		kociolki[i].ilosc_kart = 0;
		kociolki[i].kolor_kociolka = 0;
		kociolki[i].suma_wartosci_na_kociolku = 0;
	}
}
void przypisz_wartosci_kociolkom2(kociolek* kociolki, int k,int liczba_kart) {
	karty* karty_kotla = (karty*)malloc(sizeof(karty) * liczba_kart);
	for (int i = 0; i < k; i++) {
		kociolki[i].id = i + 1;
		kociolki[i].ilosc_kart = 0;
		kociolki[i].kolor_kociolka = 0;
		kociolki[i].suma_wartosci_na_kociolku = 0;
		kociolki[i].stos_kart = karty_kotla;
	}
	free(karty_kotla);
}
void rozdaj_karty(gracz* gracze, karty* talia, int n, int liczba_kart)
{
	karty** reka = (karty**)malloc(sizeof(karty*) * n); // alokacja pamieci
	for (int i = 0; i < n; i++) {
		reka[i] = (karty*)malloc(sizeof(karty) * (liczba_kart / n) + 1);
	} //reka[n][liczba_kart/n+1]
	for (int i = 0; i < liczba_kart; i++) {
		reka[i % n][gracze[i % n].handsize] = talia[i];
		gracze[i % n].handsize++;
	}
	for (int i = 0; i < n; i++) {
		gracze[i].reka = reka[i];
	}
	free(reka);
}
void wypisz_reke_plik(gracz* gracze, int numer,FILE* plik)
{
	for (int j = 0; j < gracze[numer].handsize; j++)
	{
		//cout << gracze[numer].reka[j].wartosc << " ";
		fprintf(plik, "%d ", gracze[numer].reka[j].wartosc);
		zwroc_kolor_plik(gracze[numer].reka[j].kolor,plik);
	}
}

void wypisz_deck_plik(gracz* gracze, int numer,FILE* file) {
	for (int j = 0; j < gracze[numer].decksize; j++)
	{
		//cout << gracze[numer].deck[j].wartosc << " ";
		fprintf(file, "%d ", gracze[numer].deck[j].wartosc);
		zwroc_kolor_plik(gracze[numer].deck[j].kolor,file);
	}
}

void wypisz_kociolek_plik(kociolek* kociolki, int numer,FILE* file) {
	for (int j = 0; j < kociolki[numer].ilosc_kart; j++)
	{
		//cout << kociolki[numer].stos_kart[j].wartosc << " ";
		fprintf(file, "%d ", kociolki[numer].stos_kart[j].wartosc);
		zwroc_kolor_plik(kociolki[numer].stos_kart[j].kolor,file);
	}
}


int znajdz_dwukropek(char* string) {
	for (size_t i = 0; i < strlen(string); i++)
	{
		if (string[i] == ':') return i;
	}
	return -1;
}
int znajdz_indeksgracza(char* string) {
	char id[max_liczba_cyfr];
	int licznik = 0;
	for (size_t i = 0; i < strlen(string); i++) {
		if (licznik != 0 && string[i] == ' ') {
			break;
		}
		if (isdigit(string[i]))
		{
			id[licznik] = string[i];
			licznik++;
		}
	}
	return atoi(id) - 1;
}
int wartosc_koloru(char* kolor) {
	if (strcmp(kolor, "green") == 0) return 0;
	if (strcmp(kolor, "blue") == 0) return 1;
if (strcmp(kolor, "red") == 0) return 2;
if (strcmp(kolor, "violet") == 0) return 3;
if (strcmp(kolor, "yellow") == 0) return 4;
if (strcmp(kolor, "white") == 0) return 5;
if (strcmp(kolor, "black") == 0) return 6;
return -1;
}
int czy_brak_w_tablicy(int szukana, int* tablica, int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		if (tablica[i] == szukana) return 0;
	}
	return 1;
}
void przetworz_linie(gracz* gracze, int nr_wiersza, char* string) {
	int za_dwukropkiem = znajdz_dwukropek(string) + 1;
	int indeks_gracza = znajdz_indeksgracza(string);
	int licznik_kart = 0, indeksl = 0, indeksk = 0;
	char* kolor;
	kolor = (char*)malloc(sizeof(char) * max_dl_koloru);
	char* wartosc;
	wartosc = (char*)malloc(sizeof(char) * max_liczba_cyfr);
	karty* hand = (karty*)malloc(sizeof(karty) * strlen(string));
	for (size_t i = za_dwukropkiem; i < strlen(string); i++)
	{
		if (string[i] == ' ' || string[i] == '\0' || i + 1 == strlen(string))
		{
			if (indeksl != 0)
			{
				hand[licznik_kart].wartosc = atoi(wartosc);
				indeksl = 0;
				//cout << "wartosc karty " << hand[licznik_kart].wartosc << " = " << atoi(wartosc) << endl;
				wartosc = (char*)malloc(sizeof(char) * max_liczba_cyfr);
			}
			else if (indeksk != 0)
			{
				kolor[indeksk] = '\0';
				hand[licznik_kart].kolor = wartosc_koloru(kolor);
				//cout << "kolor karty " << licznik_kart << " = " << kolor << " = " << wartosc_koloru(kolor) << endl;
				indeksk = 0;
				kolor = (char*)malloc(sizeof(char) * max_dl_koloru);
				licznik_kart++;
			}
		}
		else if (isdigit(string[i]))
		{
			wartosc[indeksl] = string[i];
			indeksl++;
		}
		else if (string[i] != ' ')
		{
			kolor[indeksk] = string[i];
			indeksk++;
		}
	}
	if (nr_wiersza % 2 == 0)
	{
		gracze[indeks_gracza].handsize = licznik_kart;
		gracze[indeks_gracza].reka = hand;
	}
	else
	{
		gracze[indeks_gracza].decksize = licznik_kart;
		gracze[indeks_gracza].deck = hand;
	}
	free(kolor);
	free(wartosc);
}
void przypisz_wartosci_graczom(gracz* gracze, int n) {
	for (int i = 0; i < n; i++) {
		gracze[i].id = i + 1;
		gracze[i].handsize = 0;
		gracze[i].decksize = 0;
		gracze[i].punkty = 0;
	}
}
void przypisz_wartosci_graczom2(gracz* gracze, int n, int liczba_kart) {
	karty* deckkarty = (karty*)malloc(sizeof(karty) * liczba_kart);
	for (int i = 0; i < n; i++) {
		gracze[i].id = i + 1;
		gracze[i].handsize = 0;
		gracze[i].decksize = 0;
		gracze[i].punkty = 0;
		gracze[i].deck = deckkarty;
	}
	free(deckkarty);
}
int sprawdz_ilosc_kolorow(gracz* gracze, int n) {
	int kolor;
	int tablica_kolorow[max_kolorow];
	int kolory_size = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < gracze[i].handsize; j++) {
			kolor = gracze[i].reka[j].kolor;
			if (czy_brak_w_tablicy(kolor, tablica_kolorow, kolory_size)) {
				tablica_kolorow[kolory_size] = kolor;
				kolory_size++;
			}
		}
		for (int j = 0; j < gracze[i].decksize; j++) {
			kolor = gracze[i].deck[j].kolor;
			if (czy_brak_w_tablicy(kolor, tablica_kolorow, kolory_size)) {
				tablica_kolorow[kolory_size] = kolor;
				kolory_size++;
			}
		}
	}
	return kolory_size;
}
void przetworz_linie2(kociolek* kociolki, char* string) {
	int za_dwukropkiem = znajdz_dwukropek(string) + 1;
	int indeks_gracza = znajdz_indeksgracza(string);
	int licznik_kart = 0, indeksl = 0, indeksk = 0;
	char* kolor;
	kolor = (char*)malloc(sizeof(char) * max_dl_koloru);
	char* wartosc;
	wartosc = (char*)malloc(sizeof(char) * max_liczba_cyfr);
	karty* hand = (karty*)malloc(sizeof(karty) * strlen(string));
	for (size_t i = za_dwukropkiem; i < strlen(string); i++)
	{
		if (string[i] == ' ' || string[i] == '\0' || i + 1 == strlen(string))
		{
			if (indeksl != 0)
			{
				hand[licznik_kart].wartosc = atoi(wartosc);
				indeksl = 0;
				//cout << "wartosc karty " << licznik_kart << " = " << atoi(wartosc) << endl;
				wartosc = (char*)malloc(sizeof(char) * max_liczba_cyfr);
			}
			else if (indeksk != 0)
			{
				kolor[indeksk] = '\0';
				hand[licznik_kart].kolor = wartosc_koloru(kolor);
				//cout << "kolor karty " << licznik_kart << " = " << kolor << " = " << wartosc_koloru(kolor) << endl;
				indeksk = 0;
				kolor = (char*)malloc(sizeof(char) * max_dl_koloru);
				licznik_kart++;
			}
		}
		else if (isdigit(string[i]))
		{
				wartosc[indeksl] = string[i];
				indeksl++;
		}
		else if (string[i] != ' ')
		{
			kolor[indeksk] = string[i];
			indeksk++;
		}
	}
	kociolki[indeks_gracza].id = indeks_gracza + 1;
	kociolki[indeks_gracza].stos_kart = hand;
	kociolki[indeks_gracza].ilosc_kart = licznik_kart;
	kociolki[indeks_gracza].kolor_kociolka = 0;
	free(kolor);
	free(wartosc);
}
void wypisz_graczy(gracz* gracze, int n)
{
	for (int i = 0; i < n; i++) {
		cout << i + 1 << " player has " << gracze[i].handsize << " cards on hand" << endl;
		cout << i + 1 << " player has " << gracze[i].decksize << " cards in front of him" << endl;
	}
}
void wypisz_kociolki(kociolek* kociolki, int k)
{
	for (int i = 0; i < k; i++) {
		cout << "there are " << kociolki[i].ilosc_kart << " cards on " << kociolki[i].id << " pile" << endl;
	}
}
int ile_koloru(gracz* gracze, int n, int kolor)
{
	int licznik_ziel = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < gracze[i].decksize; j++)
		{
			if (gracze[i].deck[j].kolor == kolor) licznik_ziel++;
		}
		for (int j = 0; j < gracze[i].handsize; j++)
		{
			if (gracze[i].reka[j].kolor == kolor) licznik_ziel++;
		}
	}
	return licznik_ziel;
}
int ile_koloru2(kociolek* kociolki, int k, int kolor)
{
	int licznik_ziel = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kociolki[i].ilosc_kart; j++)
		{
			if (kociolki[i].stos_kart[j].kolor == kolor) licznik_ziel++;
		}
	}
	return licznik_ziel;
}
void uzupelnij_wartosci(int* tab_wartosci, gracz* gracze, int n, kociolek* kociolki, int k, int kolor) {
	int licznik = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < gracze[i].decksize; j++)
		{
			if (gracze[i].deck[j].kolor == kolor)
			{
				tab_wartosci[licznik] = gracze[i].deck[j].wartosc;
				licznik++;
			}
		}
		for (int j = 0; j < gracze[i].handsize; j++)
		{
			if (gracze[i].reka[j].kolor == kolor)
			{
				tab_wartosci[licznik] = gracze[i].reka[j].wartosc;
				licznik++;
			}
		}
	}
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kociolki[i].ilosc_kart; j++)
		{
			if (kociolki[i].stos_kart[j].kolor == kolor)
			{
				tab_wartosci[licznik] = kociolki[i].stos_kart[j].wartosc;
				licznik++;
			}
		}
	}

}
void uzupelnij_zielone(karty* zielone, gracz* gracze, int n, kociolek* kociolki, int k, int kolor)
{
	int licznik = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < gracze[i].decksize; j++)
		{
			if (gracze[i].deck[j].kolor == kolor)
			{
				zielone[licznik] = gracze[i].deck[j];
				licznik++;
			}
		}
		for (int j = 0; j < gracze[i].handsize; j++)
		{
			if (gracze[i].reka[j].kolor == kolor)
			{
				zielone[licznik] = gracze[i].reka[j];
				licznik++;
			}
		}
	}
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < kociolki[i].ilosc_kart; j++)
		{
			if (kociolki[i].stos_kart[j].kolor == 0)
			{
				zielone[licznik] = kociolki[i].stos_kart[j];
				licznik++;
			}
		}
	}
}
int sprawdz_wartosci(karty* zielone, int liczba_zielonych) {
	int wartosc = zielone[0].wartosc;
	for (int i = 0; i < liczba_zielonych; i++) {
		if (zielone[i].wartosc != wartosc) return -1;
	}
	return wartosc;
}
int sprawdz_ilosci_kart_koloru(int* kolorki, int k) {
	int wartosc = kolorki[0];
	for (int i = 0; i < k; i++) {
		if (kolorki[i] != wartosc) return -1;
	}
	return wartosc;
}
void sprawdzanie_zielonych_kart(gracz* gracze, kociolek* kociolki, int n, int k) {
	int g1 = 0, g2 = 0, suma_zielonych = 0;
	g1 = ile_koloru(gracze, n, 0);
	g2 = ile_koloru2(kociolki, k, 0);
	suma_zielonych = g1 + g2;
	//cout << " suma zielonych wynosi: " << suma_zielonych << endl;
	if (suma_zielonych == 0) cout << "Green cards does not exist" << endl;
	else
	{
		karty* zielone = (karty*)malloc(sizeof(karty) * suma_zielonych);
		uzupelnij_zielone(zielone, gracze, n, kociolki, k, 0);
		int wartosci_zielonych = sprawdz_wartosci(zielone, suma_zielonych);
		free(zielone);
		if (wartosci_zielonych == -1) cout << "Different green cards values occurred" << endl;
		else
		{
			cout << "Found " << suma_zielonych << " green cards, all with " << wartosci_zielonych << " value" << endl;
		}
	}
}
int* ilosc_kart_dla_kolorow(gracz* gracze, kociolek* kociolki, int n, int k) {
	int a = 0, b = 0, suma = 0;
	int* kolorki = (int*)malloc(sizeof(int) * k);
	for (int i = 0; i < k; i++) {
		a = ile_koloru(gracze, n, i + 1);
		b = ile_koloru2(kociolki, k, i + 1);
		suma = a + b;
		kolorki[i] = suma;
	}
	return kolorki;
}
void wypisz_card_numbers(int* kolorki, int k) {
	if (sprawdz_ilosci_kart_koloru(kolorki, k) == -1) {
		cout << "At least two colors with a different number of cards were found:" << endl;
		for (int i = 0; i < k; i++) {
			zwroc_kolor(i + 1);
			cout << "cards are " << kolorki[i] << endl;
		}
	}
	else {
		cout << "The number cards of all colors is equal: " << kolorki[0] << endl;
	}
}
void wypisz_wartosci_kart(int* kolorki, gracz* gracze, int n, kociolek* kociolki, int k) {
	if (sprawdz_ilosci_kart_koloru(kolorki, k) == -1)
	{
		int max = znajdz_najw(kolorki, k);
		int** tab_wartosci = (int**)malloc(sizeof(int*) * k); // alokacja pamieci
		for (int i = 0; i < k; i++) {
			tab_wartosci[i] = (int*)malloc(sizeof(int) * max);
		}// -> tab_wartosci[k][max] 
		for (int i = 0; i < k; i++) {
			uzupelnij_wartosci(tab_wartosci[i], gracze, n, kociolki, k, i + 1);
		}
		for (int i = 0; i < k; i++) {
			posortuj_tablice(tab_wartosci[i], kolorki[i]);
		}
		cout << "The values of cards of all colors are not identical:" << endl;
		for (int i = 0; i < k; i++) {
			zwroc_kolor(i + 1);
			cout << "cards values:";
			for (int j = 0; j < kolorki[i]; j++) {
				cout << " " << tab_wartosci[i][j];
			}
			cout << endl;
		}
		free(tab_wartosci);
	}
	else {
		int ilosc_kart = kolorki[0];
		//cout << "ilosc kart wynosi: " << kolorki[0] << endl;
		int** tab_wartosci = (int**)malloc(sizeof(int*) * k); // alokacja pamieci
		for (int i = 0; i < k; i++) {
			tab_wartosci[i] = (int*)malloc(sizeof(int) * ilosc_kart);
		}// -> tab_wartosci[k][ilosc_kart] 
		for (int i = 0; i < k; i++) {
			uzupelnij_wartosci(tab_wartosci[i], gracze, n, kociolki, k, i + 1);
		}
		for (int i = 0; i < k; i++) {
			posortuj_tablice(tab_wartosci[i], kolorki[i]);
		}
		int kontrolka = 0;
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < ilosc_kart; j++) {
				if (tab_wartosci[0][j] != tab_wartosci[i][j]) kontrolka = -1;
			}
		}
		if (kontrolka == 0) {
			cout << "The values of cards of all colors are identical:" << endl;
			for (int i = 0; i < ilosc_kart; i++) {
				cout << tab_wartosci[1][i] << " ";
			}
			cout << endl;
		}
		else
		{
			cout << "The values of cards of all colors are not identical:" << endl;
			for (int i = 0; i < k; i++) {
				zwroc_kolor(i + 1);
				cout << "cards values:";
				for (int j = 0; j < ilosc_kart; j++) {
					cout << " " << tab_wartosci[i][j];
				}
				cout << endl;
			}
		}


		free(tab_wartosci);
	}
}
void przetworz_pierwsze_wiersze_plik(int* tab, int ilosc,FILE* plik) {
	char string[max_row_size];
	int licznik = 0;
	char liczba[max_liczba_cyfr];
	for (int i = 0; i < ilosc; i++)
	{
		//cin.getline(string, max_row_size);
		fgets(string, max_row_size, plik);
		for (int j = 0; j < max_row_size; j++)
		{
			if (isdigit(string[j]))
			{
				liczba[licznik] = string[j];
				licznik++;
			}
			if (licznik != 0 && !isdigit(string[j]))
			{
				licznik = 0;
				tab[i] = atoi(liczba);
				char liczba[max_liczba_cyfr];
				break;
			}
		}
	}
}

int policz_kolor(gracz gracz, int kolor)
{
	int licznik = 0;
	for (int j = 0; j < gracz.decksize; j++)
	{
		if (gracz.deck[j].kolor == kolor) licznik++;
	}

	return licznik;
}
int szukaj_maxa(int* ilosci_kart, int n) {
	int max = 0;
	int indeks = -1;
	for (int i = 0; i < n; i++) {
		if (ilosci_kart[i] > max) {
			max = ilosci_kart[i];
			indeks = i;
		}
	}
	int licznik = 0;
	for (int i = 0; i < n; i++) {
		if (ilosci_kart[i] == max) licznik++;
	}
	if (licznik > 1) indeks = -1;
	return indeks;
}
void wypisz_punkty(gracz* gracze, int n) {
	for (int i = 0; i < n; i++) {
		cout << "Wynik gracza " << i + 1 << " = " << gracze[i].punkty << endl;
	}
}
int poprawnosc_liczby_kart_gracza(gracz* gracze, int n, int indeks_gracza, int active_player) {
	int id_obecnego = gracze[indeks_gracza].id;
	int liczba_kart_obecnego = gracze[indeks_gracza].handsize;
	int czy_wykonal_ruch;
	if (active_player > id_obecnego) czy_wykonal_ruch = 1;
	else czy_wykonal_ruch = 0;
	for (int i = 0; i < n; i++)
	{
		if (i < indeks_gracza)
		{
			if (czy_wykonal_ruch == 1) {
				if (liczba_kart_obecnego - gracze[i].handsize > 0) return -1;
			}
			else {
				if (gracze[i].id < active_player) {
					if (liczba_kart_obecnego - gracze[i].handsize < 0) return -1;
				}
				else {
					if (liczba_kart_obecnego - gracze[i].handsize > 0) return -1;
				}
			}
		}
		if (i > indeks_gracza)
		{
			if (czy_wykonal_ruch == 1)
			{
				if (gracze[i].id < active_player)
				{
					if (liczba_kart_obecnego - gracze[i].handsize < 0) return -1;
				}
				else
				{
					if (liczba_kart_obecnego - gracze[i].handsize > 0) return -1;
				}
			}
			else
			{
				if (liczba_kart_obecnego - gracze[i].handsize < 0) return -1;
			}
		}
	}
	return 1;
}
int przypisz_kolor_kociolkowi(kociolek* kociolki, int indeks_kociolka) {
	for (int i = 0; i < kociolki[indeks_kociolka].ilosc_kart; i++)
	{
		if (kociolki[indeks_kociolka].stos_kart[i].kolor != 0)
		{
			if (kociolki[indeks_kociolka].kolor_kociolka == 0) kociolki[indeks_kociolka].kolor_kociolka = kociolki[indeks_kociolka].stos_kart[i].kolor;
			else
			{
				if (kociolki[indeks_kociolka].kolor_kociolka != kociolki[indeks_kociolka].stos_kart[i].kolor) return -1;
			}
		}
	}
	return 1;
}
int przypisz_wartosci_kociolkowi(kociolek* kociolki, int indeks_kociolka, int explosion) {
	kociolki[indeks_kociolka].suma_wartosci_na_kociolku = 0;
	for (int i = 0; i < kociolki[indeks_kociolka].ilosc_kart; i++)
	{
		kociolki[indeks_kociolka].suma_wartosci_na_kociolku += kociolki[indeks_kociolka].stos_kart[i].wartosc;
		if (kociolki[indeks_kociolka].suma_wartosci_na_kociolku > explosion) return -1;
	}
	return 1;
}
void sprawdz_poprawnosc_stanu_gry(gracz* gracze, int n, kociolek* kociolki, int k, int active_player, int explosion) {
	int kontrolka = 0;
	for (int i = 0; i < n; i++) {
		if (poprawnosc_liczby_kart_gracza(gracze, n, i, active_player) == -1) kontrolka = 1;
	}
	if (kontrolka == 1) {
		cout << "The number of players cards on hand is wrong" << endl;
	}
	for (int i = 0; i < k; i++) {
		if (przypisz_kolor_kociolkowi(kociolki, i) == -1)
		{
			cout << "Two different colors were found on the " << i + 1 << " pile" << endl;
			kontrolka = 1;
		}
	}
	for (int i = 0; i < k; i++) {
		if (przypisz_wartosci_kociolkowi(kociolki, i, explosion) == -1)
		{
			cout << "Pile number " << i + 1 << " should explode earlier" << endl;
			kontrolka = 1;
		}
	}
	if (kontrolka == 0) cout << "Current state of the game is ok" << endl;
}
void usun_karte_z_reki(gracz& gracz, int indeks_karty) {

	for (int i = indeks_karty; i < gracz.handsize - 1; i++) {
		gracz.reka[i] = gracz.reka[i + 1];
	}
	gracz.handsize = gracz.handsize - 1;
}
void wypisz_stan_gry_do_pliku(gracz* gracze, int n, kociolek* kociolki, int k, int active_player, int explosion) {
	FILE* file;
	file = fopen(PLIK_STANGRY, "w");
	if (file != NULL) {
		//cout << "active player = " << active_player << endl;
		fprintf(file, "active player = %i\n", active_player);
		//cout << "players number = " << n << endl;
		fprintf(file, "players number = %i\n", n);
		//cout << "explosion threshold = " << explosion << endl;
		fprintf(file, "explosion threshold = %i\n", explosion);
		for (int i = 0; i < n; i++) {
			//cout << i + 1 << " player hand cards: ";
			fprintf(file, "%i player hand cards: ", i + 1);
			wypisz_reke_plik(gracze, i,file);
			//cout << endl;
			fprintf(file, "\n");
			//cout << i + 1 << " player deck cards:";
			fprintf(file, "%i player deck cards: ", i + 1);
			wypisz_deck_plik(gracze, i,file);
			//cout << endl;
			fprintf(file, "\n");
		}
		for (int i = 0; i < k; i++) {
			//cout << i + 1 << " pile cards:";
			fprintf(file, "%i pile cards: ", i + 1);
			wypisz_kociolek_plik(kociolki, i,file);
			//cout << endl;
			if(i+1!=k)fprintf(file, "\n");
		}
		fclose(file);
	}
	else cout << "Blad pliku";
}

void obsluz_wybuch(gracz* gracze, int active_player, kociolek* kociolki, int indeks_kociolka) {
	for (int i = 0; i < kociolki[indeks_kociolka].ilosc_kart; i++) {
		gracze[active_player].deck[gracze[active_player].decksize] = kociolki[indeks_kociolka].stos_kart[i];
		gracze[active_player].decksize++;
	}
	kociolki[indeks_kociolka].ilosc_kart = 0;
	kociolki[indeks_kociolka].suma_wartosci_na_kociolku = 0;
	kociolki[indeks_kociolka].kolor_kociolka = 0;
}
int cmp(const void* a, const void* b) {
	karty* kartaA = (karty*)a;
	karty* kartaB = (karty*)b;
	return(kartaA->wartosc - kartaB->wartosc);
}
void wykonaj_ruch_min(gracz* gracze, int n, kociolek* kociolki, int k, int active_player)
{
	
	int indeks = active_player - 1;
	qsort(gracze[indeks].reka, gracze[indeks].handsize, sizeof(karty), cmp);
	int ilosc_opcji = 0;
	int kontrolka = 0;
	int* opcje = (int*)malloc(sizeof(int) * k);
	for (int i = 0; i < k; i++) {
		przypisz_kolor_kociolkowi(kociolki, i);
	}
	if (gracze[indeks].reka[0].kolor == 0) {
		ilosc_opcji = k;
		for (int i = 0; i < k; i++) {
			opcje[i] = i;
		}
	}
	else {
		for (int i = 0; i < k; i++)
		{
			if (kociolki[i].kolor_kociolka == gracze[indeks].reka[0].kolor)
			{
				kociolki[i].stos_kart[kociolki[i].ilosc_kart] = gracze[indeks].reka[0];
				kociolki[i].ilosc_kart++;
				kociolki[i].suma_wartosci_na_kociolku += gracze[indeks].reka[0].wartosc;
				kontrolka++;
				break;
			}
		}
		if (kontrolka == 0) {
			for (int i = 0; i < k; i++)
			{
				if (kociolki[i].kolor_kociolka == 0)
				{
					opcje[ilosc_opcji] = i;
					ilosc_opcji++;
				}
			}
		}
	}
	if (kontrolka == 0) {
		/*for (int i = 0; i < ilosc_opcji; i++) {
			//cout << " Opcja z indeksem opcji: " << i << " = " << opcje[i];
		}*/
		int* opcje2 = (int*)malloc(sizeof(int) * ilosc_opcji);
		for (int i = 0; i < ilosc_opcji; i++) {
			opcje2[i] = kociolki[opcje[i]].ilosc_kart;
		}
		int najmniejszejopcji = zwroc_indeks_najmn(opcje2, ilosc_opcji, 0);
		int indeks_kociolka = opcje[najmniejszejopcji];
		//cout << "indeks kociolka z najmniejsza suma na stosie wynosi " << indeks_kociolka << endl;
		kociolki[indeks_kociolka].stos_kart[kociolki[indeks_kociolka].ilosc_kart] = gracze[indeks].reka[0];
		kociolki[indeks_kociolka].ilosc_kart++;
		kociolki[indeks_kociolka].suma_wartosci_na_kociolku += gracze[indeks].reka[0].wartosc;
		free(opcje2);
	}
	free(opcje);
	usun_karte_z_reki(gracze[indeks], 0);
}
void wykonaj_ruch(gracz* gracze, int n, kociolek* kociolki, int k, int active_player)
{
	int indeks = active_player - 1;
	for (int i = 0; i < k; i++) {
		przypisz_kolor_kociolkowi(kociolki, i);
	}
	if (gracze[indeks].reka[0].kolor == 0) {
		kociolki[0].stos_kart[kociolki[0].ilosc_kart] = gracze[indeks].reka[0];
		kociolki[0].ilosc_kart++;
		kociolki[0].suma_wartosci_na_kociolku += gracze[indeks].reka[0].wartosc;
	}
	else {
		int kontrolka = 0;
		for (int i = 0; i < k; i++)
		{
			if (kociolki[i].kolor_kociolka == gracze[indeks].reka[0].kolor)
			{
				kociolki[i].stos_kart[kociolki[i].ilosc_kart] = gracze[indeks].reka[0];
				kociolki[i].ilosc_kart++;
				kociolki[i].suma_wartosci_na_kociolku += gracze[indeks].reka[0].wartosc;
				kontrolka++;
				break;
			}
		}
		if (kontrolka == 0) {
			for (int i = 0; i < k; i++)
			{
				if (kociolki[i].kolor_kociolka == 0)
				{
					kociolki[i].stos_kart[kociolki[i].ilosc_kart] = gracze[indeks].reka[0];
					kociolki[i].ilosc_kart++;
					kociolki[i].kolor_kociolka = gracze[indeks].reka[0].kolor;
					kociolki[i].suma_wartosci_na_kociolku += gracze[indeks].reka[0].wartosc;
					break;
				}
			}
		}
	}
	usun_karte_z_reki(gracze[indeks], 0);
}
void wyzeruj_stan_gry(karty* talia,gracz* gracze,int n,kociolek* kociolki, int k) {
	int licznik = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < gracze[i].decksize; j++) {
			talia[licznik] = gracze[i].deck[j];
			licznik++;
		}
		gracze[i].decksize = 0;
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < kociolki[i].ilosc_kart; j++) {
			talia[licznik] = kociolki[i].stos_kart[j];
			licznik++;
		}
		kociolki[i].ilosc_kart = 0;
		kociolki[i].suma_wartosci_na_kociolku = 0;
		kociolki[i].kolor_kociolka = 0;
	}

}
int main(){
	char option;
	bool exit = false;
	wejscie wejscie;
	int k, g, gv, o, n, liczba_kart,explosion,active_player;
	int tab[3];
	int* tab_wartosci= (int*)malloc(sizeof(int));
	karty* talia = (karty*)malloc(sizeof(karty));
	gracz* gracze = (gracz*)malloc(sizeof(gracz));
	kociolek* kociolki = (kociolek*)malloc(sizeof(kociolek));
	char string[max_row_size];
	int licznik;
	char liczba[max_liczba_cyfr];
	FILE* plik_odczyt;
	int* kolorki = (int*)malloc(sizeof(int));
	bool koniec_rundy;
	int ilosc_rund;
	int nr_gracza_min = 0;
	int wygrane1 = 0, wygrane2 = 0,porownywarka=0;
	int najmnk = 0;
	while (!exit) {
		cout << "Wybierz opcje:" << endl;
		cout << "1 - utworz talie" << endl;
		cout << "2 - rozdaj karty" << endl;
		cout << "3 - wczytaj stan gry" << endl;
		cout << "4 - wykonaj prosty ruch " << endl;
		cout << "5 - Zagraj prosta gre " << endl;
		cout << "q - wyjdz" << endl;
		cin >> option;
		switch (option) {
		case '1':
			cout << "Wprowadz parametry do wygenerowania talii - ilosc kolorow - ilosc zielonych - wartosci zielonych - wartosci pozostalych" << endl;
			cin >> k >> g >> gv >> o;
			liczba_kart = o * k + g;
			talia = (karty*)malloc(sizeof(karty) * liczba_kart);
			wejscie.l_kociolkow = k;
			wejscie.l_zielonych = g;
			wejscie.w_zielonych = gv;
			wejscie.l_kart = o;
			tab_wartosci = (int*)malloc(sizeof(int) * o);
			for (int i = 0; i < o; i++) {
				cin >> tab_wartosci[i];
			}
			generuj_talie(talia, wejscie, tab_wartosci);
			wypisz_talie(talia, liczba_kart);
			break;
		case '2':
			cout << "Wprowadź parametry opisujace gre - ilosc graczy - prog wybuchu  kociolka" << endl;
			cin >> n >> explosion;
			active_player = 1;
			gracze = (gracz*)malloc(sizeof(gracz) * n);
			przypisz_wartosci_graczom2(gracze, n,liczba_kart);
			rozdaj_karty(gracze, talia, n, liczba_kart);
			kociolki = (kociolek*)malloc(sizeof(kociolek) * k);
			przypisz_wartosci_kociolkom2(kociolki, k,liczba_kart);
			wypisz_stan_gry_do_pliku(gracze, n, kociolki, k, active_player, explosion);
			break;
		case '3':
			licznik = 0;
			plik_odczyt = fopen(PLIK_ZRODLO, "r");
			if (plik_odczyt == NULL) cout << "Blad odczytu" << endl;
			else{
			przetworz_pierwsze_wiersze_plik(tab, 3,plik_odczyt);
			n = tab[1];
			active_player = tab[0];
			explosion = tab[2];
			gracze = (gracz*)malloc(sizeof(gracz) * n);
			przypisz_wartosci_graczom(gracze, n); // domyslne wartosci
			for (int i = 0; i < 2 * n; i++) {
				//cin.getline(string, max_row_size);
				fgets(string, max_row_size, plik_odczyt);
				przetworz_linie(gracze, i, string);
			}
			wypisz_graczy(gracze, n);
			k = sprawdz_ilosc_kolorow(gracze, n)-1;
			kociolki = (kociolek*)malloc(sizeof(kociolek) * k);
			przypisz_wartosci_kociolkom(kociolki, k); // domyslne wartosci
			for (int i = 0; i < k; i++)
			{
				//cin.getline(string, max_row_size);
				fgets(string, max_row_size, plik_odczyt);
				if (i + 1 == k) strcat(string, " ");
				przetworz_linie2(kociolki, string);
			}
			wypisz_kociolki(kociolki, k);
			sprawdzanie_zielonych_kart(gracze, kociolki, n, k);
			kolorki = ilosc_kart_dla_kolorow(gracze, kociolki, n, k);
			wypisz_card_numbers(kolorki, k);
			wypisz_wartosci_kart(kolorki, gracze, n, kociolki, k);
			sprawdz_poprawnosc_stanu_gry(gracze, n, kociolki, k, active_player, explosion);
			fclose(plik_odczyt);
			}
			break;
		case '4':
			cout << " Jezeli chcesz wykonac prosty ruch, wpisz 0, jezeli chcesz wybrac najmn karte, wpisz 1" << endl;
			cin >> najmnk;
			koniec_rundy = true;
			for (int i = 0; i < n; i++) {
				if (gracze[i].handsize > 0) koniec_rundy = false;
			}
			if (koniec_rundy) {
				int** ilosci_kart = (int**)malloc(sizeof(int*) * (k + 1)); // alokacja pamieci
				for (int i = 0; i < k + 1; i++) {
					ilosci_kart[i] = (int*)malloc(sizeof(int) * n);
				}// -> tab_wartosci[k+1][n]
				for (int i = 0; i < k + 1; i++) {
					for (int j = 0; j < n; j++) {
						ilosci_kart[i][j] = policz_kolor(gracze[j], i);
					}
				}
				for (int i = 1; i < k + 1; i++) {
					int indeks_gracza = szukaj_maxa(ilosci_kart[i], n);
					if (indeks_gracza >= 0) {
						cout << "Na kolor ";
						zwroc_kolor(i);
						cout << "odporny jest gracz " << indeks_gracza + 1 << endl;
						ilosci_kart[i][indeks_gracza] = 0;
					}
				}
				for (int i = 0; i < n; i++) { // dodaj punkty za zielone karty
					gracze[i].punkty += 2 * (ilosci_kart[0][i]);
				}
				for (int i = 1; i < k + 1; i++) { // dodaj punkty za pozostałe kolory kart
					for (int j = 0; j < n; j++) {
						gracze[j].punkty += ilosci_kart[i][j];
					}
				}
				wypisz_punkty(gracze, n);
				free(ilosci_kart);
				int suma = 0;
				for (int i = 0; i < n; i++) {
					suma += gracze[i].decksize;
				}
				for (int i = 0; i < k; i++) {
					suma += kociolki[i].ilosc_kart;
				}
				talia = (karty*)malloc(sizeof(karty) * suma);
				wyzeruj_stan_gry(talia, gracze, n, kociolki, k);
				rozdaj_karty(gracze, talia, n, suma);
				wypisz_stan_gry_do_pliku(gracze, n, kociolki, k, 1, explosion);
			}
			else {
				if(najmnk==1)wykonaj_ruch_min(gracze, n, kociolki, k, active_player);
				else wykonaj_ruch(gracze, n, kociolki, k, active_player);
				for (int i = 0; i < k; i++) {
					if (kociolki[i].suma_wartosci_na_kociolku > explosion) obsluz_wybuch(gracze, active_player - 1, kociolki, i);
				}
				active_player++;
				if (active_player > n) active_player = 1;
				wypisz_stan_gry_do_pliku(gracze, n, kociolki, k, active_player, explosion);
			}
			break;
		case '5':
			cout << "Wprowadz parametry do wygenerowania talii - ilosc kolorow - ilosc zielonych - wartosci zielonych - wartosci pozostalych" << endl;
			cin >> k >> g >> gv >> o;
			liczba_kart = o * k + g;
			talia = (karty*)malloc(sizeof(karty) * liczba_kart);
			wejscie.l_kociolkow = k;
			wejscie.l_zielonych = g;
			wejscie.w_zielonych = gv;
			wejscie.l_kart = o;
			tab_wartosci = (int*)malloc(sizeof(int) * o);
			for (int i = 0; i < o; i++) {
				cin >> tab_wartosci[i];
			}
			generuj_talie(talia, wejscie, tab_wartosci);
			wypisz_talie(talia, liczba_kart);
			cout << "Wprowadź parametry opisujace gre - ilosc graczy - prog wybuchu  kociolka - ilosc rund" << endl;
			cin >> n >> explosion >> ilosc_rund;
			cout << "Podaj numer gracza, ktory bedzie wybieral najmn karte ( jezeli bez, wpisz 0 )" << endl;
			cin >> nr_gracza_min;
			cout << "Jezeli chcesz porownac ilosc zwyciestw 2 graczy wpisz 1, jezeli nie - 0" << endl;
			cin >> porownywarka;
			active_player = 1;
			gracze = (gracz*)malloc(sizeof(gracz) * n);
			przypisz_wartosci_graczom2(gracze, n, liczba_kart);
			tasuj_talie(talia, liczba_kart);
			rozdaj_karty(gracze, talia, n, liczba_kart);
			kociolki = (kociolek*)malloc(sizeof(kociolek) * k);
			przypisz_wartosci_kociolkom2(kociolki, k, liczba_kart);
			wypisz_stan_gry_do_pliku(gracze, n, kociolki, k, active_player, explosion);
			while (ilosc_rund != 0) {
				//odczyt
				plik_odczyt = fopen(PLIK_ZRODLO, "r");
				if (plik_odczyt == NULL) cout << "Blad odczytu" << endl;
				else {
					przetworz_pierwsze_wiersze_plik(tab, 3, plik_odczyt);
					n = tab[1];
					active_player = tab[0];
					explosion = tab[2];
					gracze = (gracz*)malloc(sizeof(gracz) * n);
					przypisz_wartosci_graczom(gracze, n); // domyslne wartosci
					for (int i = 0; i < 2 * n; i++) {
						//cin.getline(string, max_row_size);
						fgets(string, max_row_size, plik_odczyt);
						przetworz_linie(gracze, i, string);
					}
					//wypisz_graczy(gracze, n);
					k = sprawdz_ilosc_kolorow(gracze, n) - 1;
					kociolki = (kociolek*)malloc(sizeof(kociolek) * k);
					przypisz_wartosci_kociolkom(kociolki, k); // domyslne wartosci
					for (int i = 0; i < k; i++)
					{
						//cin.getline(string, max_row_size);
						fgets(string, max_row_size, plik_odczyt);
						if (i + 1 == k) strcat(string, " ");
						przetworz_linie2(kociolki, string);
					}
					sprawdz_poprawnosc_stanu_gry(gracze, n, kociolki, k, active_player, explosion);
					fclose(plik_odczyt);
				}
				// odczyt
				//ruch

				koniec_rundy = true;
				for (int i = 0; i < n; i++) {
					if (gracze[i].handsize > 0) koniec_rundy = false;
				}
				if (koniec_rundy) {
					int** ilosci_kart = (int**)malloc(sizeof(int*) * (k + 1)); // alokacja pamieci
					for (int i = 0; i < k + 1; i++) {
						ilosci_kart[i] = (int*)malloc(sizeof(int) * n);
					}// -> tab_wartosci[k+1][n]
					for (int i = 0; i < k + 1; i++) {
						for (int j = 0; j < n; j++) {
							ilosci_kart[i][j] = policz_kolor(gracze[j], i);
						}
					}
					for (int i = 1; i < k + 1; i++) {
						int indeks_gracza = szukaj_maxa(ilosci_kart[i], n);
						if (indeks_gracza >= 0) {
							cout << "Na kolor ";
							zwroc_kolor(i);
							cout << "odporny jest gracz " << indeks_gracza + 1 << endl;
							ilosci_kart[i][indeks_gracza] = 0;
						}
					}
					for (int i = 0; i < n; i++) { // dodaj punkty za zielone karty
						gracze[i].punkty += 2 * (ilosci_kart[0][i]);
					}
					for (int i = 1; i < k + 1; i++) { // dodaj punkty za pozostałe kolory kart
						for (int j = 0; j < n; j++) {
							gracze[j].punkty += ilosci_kart[i][j];
						}
					}
					wypisz_punkty(gracze, n);
					if (porownywarka == 1) {
						if (gracze[0].punkty < gracze[1].punkty) wygrane1++;
						else if (gracze[0].punkty > gracze[1].punkty) wygrane2++;
					}
					free(ilosci_kart);
					int suma = 0;
					for (int i = 0; i < n; i++) {
						suma += gracze[i].decksize;
					}
					for (int i = 0; i < k; i++) {
						suma += kociolki[i].ilosc_kart;
					}
					talia = (karty*)malloc(sizeof(karty) * suma);
					wyzeruj_stan_gry(talia, gracze, n, kociolki, k);
					tasuj_talie(talia, liczba_kart);
					rozdaj_karty(gracze, talia, n, suma);
					wypisz_stan_gry_do_pliku(gracze, n, kociolki, k, 1, explosion);
					ilosc_rund--;
				}
				else {
					if (nr_gracza_min == active_player) {
						wykonaj_ruch_min(gracze, n, kociolki, k, active_player);
					}
					else wykonaj_ruch(gracze, n, kociolki, k, active_player);
					for (int i = 0; i < k; i++) {
						if (kociolki[i].suma_wartosci_na_kociolku > explosion) obsluz_wybuch(gracze, active_player - 1, kociolki, i);
					}
					active_player++;
					if (active_player > n) active_player = 1;
					wypisz_stan_gry_do_pliku(gracze, n, kociolki, k, active_player, explosion);
				}
			}
			if (porownywarka == 1) {
				cout << "Gracz 1 wygral " << wygrane1 << " razy" << endl;
				cout << "Gracz 2 wygral " << wygrane2 << " razy" << endl;
			}
			wygrane1 = 0;
			wygrane2 = 0;
			break;
		case 'q':
			free(talia);
			free(gracze);
			free(kociolki);
			free(tab_wartosci);
			free(kolorki);
			exit = true;
			break;
		}
	}
	return 0;
}