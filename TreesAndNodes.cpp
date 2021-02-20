#include <iostream>
#include <stdlib.h>
using namespace std;


// klasa Skupa napravljena preko liste

class SkupLista{
private:
	struct Element{                                                                                      //Izgled elementa liste                    
		Element* prethodni, *sledeci;            
		int broj;
		Element(int n,Element* s=nullptr) {
			broj = n;
			prethodni = sledeci = s;
		}
		
	};
	int velicina;
	Element* prvi, *poslednji;
	
  //================================================================================================	
public:
	explicit SkupLista() {                                                                                              //Default Konstruktor za stvaranje praznog Skupa
		prvi = poslednji = nullptr;
		velicina = 0;
 }
 //================================================================================================
	SkupLista(const SkupLista& skp) {                                                                                              //Kopirajuci kontruktor
		prvi = poslednji = nullptr;
		if (skp.prvi != nullptr) {
			Element* tek = skp.prvi;
			do { 
				Element* novi = new Element(tek->broj);
				if (!prvi) prvi = novi;
				else poslednji->sledeci = novi;
				novi->prethodni = poslednji;
				poslednji = novi;
				prvi->prethodni = poslednji;
				poslednji->sledeci = prvi;
				tek = tek->sledeci;
			} while (tek != skp.prvi);
			velicina = skp.velicina;
		}
	
	}
//===========================================================================================================	
	SkupLista(SkupLista&& skp) {                                                                                                           //Premestajuci konstruktor
		prvi = skp.prvi;
		poslednji = skp.poslednji;
		skp.prvi = skp.poslednji = nullptr;
		velicina = skp.velicina;
	
	}
//==========================================================================================================
	  
                                                                                                                                           //Destruktor
	~SkupLista() {
		IsprazniSkup();
	}                                                                                                             
//==========================================================================================================
	void IsprazniSkup() {                                                                                                              // Funkcija Isprazni skup
		Element* tekuci = prvi;
		while (prvi != poslednji) {
			prvi = prvi->sledeci;
			prvi->prethodni = poslednji;
			poslednji->sledeci = prvi;
			delete tekuci;
			tekuci = prvi;
		}
		delete tekuci;
		prvi = poslednji = nullptr;
		velicina = 0;

	}
//=============================================================================================================
	friend ostream& operator<<(ostream& it, const SkupLista& skup) {                                                                    //Operator za ispis skupa
		if (skup.prvi != nullptr) {
			it << "{";
			Element* tek = skup.prvi;
			while (tek != skup.poslednji) {
				it << tek->broj << ",";

				tek = tek->sledeci;

			}
			return it << skup.poslednji->broj << "}" << endl;

		}
		else return it << "Skup je prazan." << endl;

	}
//==============================================================================================================
	bool Pronadji(int b) {                                                                                                            //Funkcija za utvrdjivanje pripadnosti skupu
		if (prvi == nullptr) return false;
		Element*tek = prvi;
		do {
			if (tek->broj == b) return true;
			else tek = tek->sledeci;
		} while (tek != prvi && tek->broj <= b);
		return false;
	}
//===============================================================================================================
	SkupLista& operator+=( int br) {                                                                                                 //Operator za dodavanje elemenata
		if (prvi == nullptr) {                                         
			poslednji = prvi = new Element(br);
			prvi->prethodni = poslednji;
			poslednji->sledeci = prvi;
			
		}
		                                                    
		else {
			if (prvi->broj > br) {
				Element*pom = new Element(br);
				pom->prethodni = poslednji;
				pom->sledeci = prvi;
				prvi->prethodni = pom;
				poslednji->sledeci = pom;
				prvi = pom;

			}
			else { if (poslednji->broj < br) {
				Element*pom = new Element(br);
				pom->prethodni = poslednji;
				pom->sledeci = prvi;
				prvi->prethodni = pom;
				poslednji->sledeci = pom;
				poslednji = pom;
			}
			else {
				Element* tekuci = prvi;
				while (tekuci->broj < br) {
					tekuci = tekuci->sledeci;
				}
				Element*pom = new Element(br);
				pom->sledeci = tekuci;
				pom->prethodni = tekuci->prethodni;
				Element*prethodnik = pom->prethodni;
				prethodnik->sledeci = pom;
				tekuci->prethodni = pom;
			}
			    }
		}
		velicina++;
		return *this;
	}
//=================================================================================================================================
	void SearchAndDestroy(int br) {                                                                                                       //Funkcija za brisanje elementa
		if (prvi == poslednji) { 
			delete prvi;
			prvi = poslednji = nullptr;
			velicina--;
			return;
		}
		if (prvi->broj == br) {
			Element* tek = prvi;
			prvi = prvi->sledeci;
			prvi->prethodni = poslednji;
			poslednji->sledeci = prvi;
			delete tek;
			velicina--;
			return;
		}
		if (poslednji->broj == br) {
			Element*tek = poslednji;
			poslednji = poslednji->prethodni;
			poslednji->sledeci = prvi;
			prvi->prethodni = poslednji;
			delete tek;
			velicina--;
			return;
		}
		Element* tek = prvi->sledeci;
		while (tek->broj != br) {
			tek = tek->sledeci;
		}
		Element*left = tek->prethodni;
		Element*right = tek->sledeci;
		left->sledeci = right;
		right->prethodni = left;
		delete tek;
		velicina--;
	}
//===========================================================================================================================	
	void OcistiOpseg(int min, int max) {                                                                                                                                      //Funkcija za brisanje opsega
		if (prvi == nullptr) return;                                                     //prazan skup

		if ((prvi->broj < min && poslednji->broj < min) || (prvi->broj > max && poslednji->broj > max))return;   //opseg van elemenata skupa
		if (prvi->broj <= min && poslednji->broj <= max) {
			IsprazniSkup(); return;
		}                                                                                         //ceo skup obuhvacen
		Element*tek = prvi;                                                                     //brise sve od pocetka do gornjeg opsega
		while (tek == prvi) {
			if (prvi->broj >= min && prvi->broj <= max) {
				prvi = prvi->sledeci;
				prvi->prethodni = poslednji;
				poslednji->sledeci = prvi;
				delete tek;
				velicina--;
				tek = prvi;
			}

			else break;
		}
		tek = poslednji;
		while (tek == poslednji) {
			if (poslednji->broj >= min && poslednji->broj <= max) {

				poslednji = poslednji->prethodni;
				prvi->prethodni = poslednji;
				poslednji->sledeci = prvi;
				delete tek;
				velicina--;
				tek = poslednji;

			}
			else break;
		}
		tek = prvi->sledeci;
		do {
			if (tek->broj >= min && tek->broj <= max) {
				Element*left = tek->prethodni;
				Element*right = tek->sledeci;
				left->sledeci = right;
				right->prethodni = left;
				delete tek;
				velicina--;
				tek = right;
			}
			else tek = tek->sledeci;

		} while (tek != poslednji);
	}
	//===========================================================================================================================================================
	                                                                                                                                                                        //Funkcija za dohvatanje velicine
	int GetSize()const { return velicina; }

	//======================================================================================================

	SkupLista& Razlika( SkupLista& A, SkupLista& B) {                                                                                                                       //Razlika Dva Skupa
		Element*tek = A.prvi;
		do {
			if (!B.Pronadji(tek->broj)) *this+=tek->broj;
			tek = tek->sledeci;
		} while (tek != A.prvi);
		return *this;
	}

};

//=================================================================================================================================                //Kraj Klase SkupLista
                                                                                                                                                                                 

int main() {                                                                                                                                      // Glavni program

	cout << "Dobro dosli!" << endl;
	
	
	while (1) {
		cout << "Izaberite nacin implementacije" << endl;
		cout << "\n1. Lista\n"
			"\n2. Stablo\n"
			"\n0. Napustite program\n";
		int n;
		cin >> n;
		if (n == 1) {
			SkupLista A, B, C, D;
			bool kraj = false;
			//Meni sa komandama
			while (!kraj) {
				cout << "Unesite zeljenu komandu:" << endl;
				cout << "\n1. Isprazni skup\n"
					"\n2. Proveri da li je element clan skupa\n"
					"\n3. Dodajte elemente\n"
					"\n4. Obrisite element\n"
					"\n5. Obrisite elemente u nekom opsegu\n"
					"\n6. Trenutna velicina skupa\n"
					"\n7. Ispisi elemente skupa\n"
					"\n8. Izvrsite razliku dva skupa\n"
					"\n9. Vratite se na izbor implementacije\n"
					"\n0. Napustite program\n";

				int komanda;
				cin >> komanda;
				switch (komanda) {
				case 1: A.IsprazniSkup();                                                                                                               //Pozivanje komande za praznjenje skupa
					cout << "Obrisali ste sve elemente skupa!" << endl;
					break;
					//===============================================================================================================================			
				case 2: cout << "Unesite vrednost elementa koga zelite da pronadjete:" << endl;                                                          //Komanda za ispitivanje pripadnosti elementa
					int vr;
					cin >> vr;
					if (A.Pronadji(vr)) cout << "Element pripada skupu!" << endl;
					else                cout << "Elemenet ne pripada skupu!" << endl;
					break;
					//================================================================================================================================
				case 3: cout << "Koliko zelite elemenata da dodate?" << endl;                                                                            // Komanda za dodavanje elementa
					int p, brojic;
					do {
						cin >> p;
						if (p < 0) cout << "Ne mozete uneti negativan broj elemenata! Molimo vas pokusajte ponovo!" << endl;

					} while (p < 0);
					if (p == 0) break;
					cout << "Unesite zeljene elemente:" << endl;
					for (int i = 0; i < p; i++) {
						cin >> brojic;
						if (!(A.Pronadji(brojic)))  A += brojic;
					}
					break;
					//================================================================================================================================
				case 4: cout << "Unesite vrednost elementa kog zelite da obrisete:" << endl;                                                            // Komanda za pojedinacno brisanje elemenata
					int garbage;
					cin >> garbage;
					if (A.Pronadji(garbage)) A.SearchAndDestroy(garbage);
					else cout << "Taj element ne postoji u skupu!" << endl;
					break;
					//=================================================================================================================================
				case 5:
					cout << "Unesite donju granicu opsega:" << endl;                                                                                   //Komanda  za brisanje elemenata u opsegu
					int low, high;
					cin >> low;
					cout << "Unesite gornju granicu opsega:" << endl;
					cin >> high;
					if (high < low) {
						cout << "Donja granica ne moze biti veca od gornje!" << endl;
						break;
					}
					if (high == low) {
						if (A.Pronadji(low)) { A.SearchAndDestroy(low); }
						break;
					}
					A.OcistiOpseg(low, high);
					break;
					//========================================================================================================================
				case 6: cout << " Skup trenutno ima " << A.GetSize() << " elemenata." << endl;                                                                    //Ispis broja elemenata
					break;
					//============================================================================================                                                   
				case 7: cout << A << endl;                                                                                 //Ispis svih elemenata skupa
					break;
					//===========================================================================
				case 8:                                                                                                                                     //Razlika dva skupa
					cout << "Koliko zelite elemenata da dodate u 1.skup?" << endl;                                                                        // Komanda za dodavanje elementa u prvi skup
					int br1, el1;
					do {
						cin >> br1;
						if (br1 <= 0) cout << "Ne mozete uneti negativan broj elemenata! Molimo vas pokusajte ponovo" << endl;

					} while (br1 <= 0);
					cout << "Unesite zeljene elemente" << endl;
					for (int i = 0; i < br1; i++) {
						cin >> el1;
						if (!(A.Pronadji(el1)))  B += el1;
					}
					cout << "Koliko zelite elemenata da dodate u 2. skup?" << endl;                                                                        // Komanda za dodavanje elementa u drugi skup
					int br2, el2;
					do {
						cin >> br2;
						if (br2 <= 0) cout << "Ne mozete uneti negativan broj elemenata! Molimo vas pokusajte ponovo" << endl;

					} while (br2 <= 0);
					cout << "Unesite zeljene elemente" << endl;
					for (int i = 0; i < br2; i++) {
						cin >> el2;
						if (!(A.Pronadji(el2)))  C += el2;
					}

					D.Razlika(B, C);

					cout << "Rezultat razlike vasa dva skupa je skup D=" << D << endl;
					B.IsprazniSkup();
					C.IsprazniSkup();
					D.IsprazniSkup();
					break;
					//==================================================================================================================================
				case 9: kraj = true;
					break;
				case 0: cout << "Uspesno ste napustili program,Zbogom!" << endl;                                                                                         // Komanda za zavrsetak programa
					return 0;
				default: cout << "Uneli ste nepostojecu komandu!" << endl;
				}

			}
		}
//===================================================================================================================================================               //Pocetak komandi za rad sa implementacijom skupa kao stablo
		if (n == 2) {
			cout << "Jos nije spremna implementacija stablo" << endl;
		}
		if (n == 0) return 0;
		if (n!=0 && n!=1 && n!=2) cout << "Nedozvoljen izbor!" << endl;
	}
}