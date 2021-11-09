// pk3my_21_lab02.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>     // std::cout
#include <algorithm>    // std::count
#include <vector>       // std::vector
#include <array>        // std::array
#include <list>        // std::list
#include <deque>        // std::list
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <ctime>


using namespace std;

template<typename T>
static void drukuj(T POJ, bool x = 0)
{
	char podz = ',';
	if (x)
		podz = '\n';

	int size = POJ.size();
	if (size <= 0) {
		std::cout << "Kontener nie istnieje";
		return;
	}
	std::cout << '{';
	for (int l = 0; l < size - 1; l++) {
		std::cout << POJ[l];
		std::cout << podz;
	}
	std::cout << POJ[size - 1];
	std::cout << "}";
}



class MojeTrio
{
	friend struct cool_comparator;

	int a;
	double b;
	float c;
public:
	MojeTrio() :a(0), b(0), c() {};
	MojeTrio(int _a) :a(_a)
	{
		b = (rand() % 100000) / 1000.0;
		c = (rand() % 10000) / 1000.0;
	}
	auto get_tosort() const { return a; }; //  funkcja zwraca wartosc stosowana przy sortowaniu, moze to byc a b c lub cos inneo np. suma 3 liczb
	friend ostream& operator<<(ostream& os, const MojeTrio& dt);
};
ostream& operator<<(ostream& s, const MojeTrio& dt)
{
	s << dt.a << '\t' << dt.b << '\t' << dt.c;
	return s;
}

struct cool_comparator
{
	enum compare_type { A, B, SUMA };
	cool_comparator(compare_type ct) : m_ct(ct) {};

	bool operator()(const MojeTrio& lhs, const MojeTrio& rhs) const
	{
		switch (m_ct)
		{
		case A: return lhs.a < rhs.a; break;
		case B: return lhs.b < rhs.b; break;
		case SUMA: return (lhs.a + lhs.b) < (rhs.a + rhs.b); break;
		default: throw std::runtime_error{ "cos strasznego :c" }; break;
		}
	}

private:
	compare_type m_ct;

};


bool moje_compare(const MojeTrio& lhs, const MojeTrio& rhs)
{
	return lhs.get_tosort() < rhs.get_tosort();
}


struct comparator
{
	bool operator()(const MojeTrio& lhs, const MojeTrio& rhs) const
	{
		return lhs.get_tosort() < rhs.get_tosort();
	}
};






int main()
{

	srand(time(NULL));

	cout << "PROSZE WPISAC SWOJE IMIE I NAZWISKO " << endl;
	vector<int> Vec1 = { 10, 10, 3, 4, 10, 10, 7, 10, 10 };
	int licznik = -1;

	cout << "\n\nZAD 1: ZLICZANIE\n";

	// a)	Ile 10 jest w całym wektorze
	licznik = count(Vec1.begin(), Vec1.end(), 10);   // ile jest w całym wektorze
	cout << "W calym wektorze '10' jest: " << licznik << (" (pop: 6)\n");

	// b)	Ile 10 jest na końcu wektora. Ponieważ pozycja końca jest jedna, może być 1 lub 0 (jest albo nie 10).
	licznik = count(Vec1.end() - 1, Vec1.end(), 10);
	cout << "Na koncu '10' jest: " << licznik << (" (pop: 1)\n");

	//c)	Ile 10 jest od drugiego do przedostatniego elementu wektora.
	licznik = count(Vec1.begin() + 1, Vec1.end() - 1, 10);
	cout << "Od drugiego do przedostatniego elementu w wektorze 10 jest: " << licznik << (" (pop: 4)\n");





	//==============================================================
	// 
	cout << "\n\nZAD 2: KOPIOWANIE\n";
	vector<int> Vec2 = { 1,2,3,4,5,6,7,8,9,10 };
	deque<int> Deq2new;

	/* Kopiowanie z Vec2 */
	/* Przydatna funkcja dodająca na koniec pojemników: back_inserter - użyte też w przykładzie */
	/* a)  skopiuj 5 elementow z Vec2 ZACZYNAJAC od czwartego do nowego obiektu Deq2new*/
	copy(Vec2.begin() + 3, Vec2.begin() + 8, back_inserter(Deq2new));
	drukuj(Deq2new);
	cout << "\tOdp: {4,5,6,7,8} \n";

	/* b)  DOLÓŻ na koniec (przekopiuj) do Deq2new od drugiego do czwartego elementu  z Vec2*/
	move(Vec2.begin() + 1, Vec2.begin() + 4, back_inserter(Deq2new));
	drukuj(Deq2new);
	cout << "\tOdp: {4,5,6,7,8,2,3,4} \n";


	/* c) Zwiększ rozmiar kolejki o 3 (wykorzystaj metody resize() i size())
	Następnie wykorzystając algorytm copy_backward skopiuj z Vec2 pięć pierwszych
	elementów wstawiając od końca zwiększonej kolejki Deq2new.

	Spróbuj przewidzieć jak będzie wyglądała teraz ta kolejka.*/
	Deq2new.resize(Deq2new.size() + 3);
	copy_backward(Vec2.begin(), Vec2.begin() + 5, Deq2new.end());
	drukuj(Deq2new);
	cout << "\tDeq2new po wykorzystaniu copy_backward \n";

	/* d) Dokonaj rotacji w kontenerze (zamiany miejscami) w Deq2new,
	tak aby 5 ostatnich elementów, znalazło się na początku */
	rotate(Deq2new.begin(), Deq2new.end() - 5, Deq2new.end());
	drukuj(Deq2new);
	cout << "\tOdp: {1,2,3,4,5,4,5,6,7,8,2} \n";





	//==============================================================
	// Zad 3
	cout << "\n\nZAD 3: METODY/FUNKCJE\n";

	/* a) Stwórz wektor Tab3 (w tym zadaniu proszę go nie modyfikować)
	zawierający elementy typu MojeTrio. Pojemność wektora wyosi pojVec3 = 200000.
	Wypełnij go liczbami od 0 do pojVec3-1, wykorzystaj do tego: algorytm generate_n() oraz wyrażenie lambda ze zmienianą wartością zmiennej globalnej  */
	int pojVec3 = 200000;
	vector<MojeTrio> Tab3(pojVec3);
	int a = 0;
	generate_n(Tab3.begin(), pojVec3, [&a]() { return a++; });
	//
	//

	cout << "Tab3[0]=" << Tab3[0] << ("\t (odp: 0)\n");
	cout << "Tab3[end-1]=" << Tab3[pojVec3-1] << "\t (odp: " << pojVec3-1 << ")\n";
	cout << "Tab3[17]=" << Tab3[17] << ("\t (odp: 17)\n");



	/* b) Przemieszaj Tab3 odpowiednim algorytmem, możesz wykorzystać
	do tego gotowe funkcje z std*/

	cout << "\tPrzemieszane Tab3: \n";
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(Tab3.begin(), Tab3.end(), std::default_random_engine(seed));
	cout << "Tab3[0]=" << Tab3[0] << endl;
	cout << "Tab3[end-1]=" << Tab3[pojVec3 - 1] << endl;
	cout << "Tab3[17]=" << Tab3[17] << endl;


	/* c) Posortuj Tab3 wstawiając od razu do nowego wektora Vec3new
	(bez wcześniejszego przekopiowywania).
	Do sortowania wykorzystuj funkcję globalną, wyrażenie lambda oraz obiekt funkcyjny.
	Porównaj czasy. Możesz spróbować zmienić w get_tosort(), zwracany obiekt,
	tak, że wektor będzie sortowany biorąc pod uwagę różne kryteria. */
	cout << "\n SORTOWANIE\n";
	vector<MojeTrio> Vec3new(pojVec3);
	


	/* Mierzenie czasu na podstawie
	https://bulldogjob.pl/news/1474-jak-mierzyc-czas-wykonania-programu-w-c-c  	*/


	cout << "\nFunkcja globalna\n";
	auto begin = std::chrono::high_resolution_clock::now();
	// .............  sortowanie
	partial_sort_copy(Tab3.begin(), Tab3.end(), Vec3new.begin(), Vec3new.end(), moje_compare);
	cout << "Vec3new[0]=" << Vec3new[0] << ("\t (odp: 0)\n");
	cout << "Vec3new[end-1]=" << Vec3new[pojVec3 - 1] << "\t (odp: " << pojVec3 - 1 << ")\n";
	cout << "Vec3new[17]=" << Vec3new[17] << ("\t (odp: 17)\n");
	// Stop measuring time and calculate the elapsed time
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);




	cout << "\nWyrażenie Lambda\n";
	begin = std::chrono::high_resolution_clock::now();
	partial_sort_copy(Tab3.begin(), Tab3.end(), Vec3new.begin(), Vec3new.end(),
		[](const MojeTrio& lhs, const MojeTrio& rhs)
		{
			return lhs.get_tosort() < rhs.get_tosort();
		}
	);
	cout << "Vec3new[0]=" << Vec3new[0] << ("\t (odp: 0)\n");
	cout << "Vec3new[end-1]=" << Vec3new[pojVec3 - 1] << "\t (odp: " << pojVec3 - 1 << ")\n";
	cout << "Vec3new[17]=" << Vec3new[17] << ("\t (odp: 17)\n");
	// Stop measuring time and calculate the elapsed time
	end = std::chrono::high_resolution_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);


	cout << "\nObiekt funkcyjny\n";
	begin = std::chrono::high_resolution_clock::now();
	std::partial_sort_copy(Tab3.begin(), Tab3.end(), Vec3new.begin(), Vec3new.end(), comparator{});
	cout << "Vec3new[0]=" << Vec3new[0] << ("\t (odp: 0)\n");
	cout << "Vec3new[end-1]=" << Vec3new[pojVec3 - 1] << "\t (odp: " << pojVec3 - 1 << ")\n";
	cout << "Vec3new[17]=" << Vec3new[17] << ("\t (odp: 17)\n");
	// Stop measuring time and calculate the elapsed time
	end = std::chrono::high_resolution_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);



	//==============================================================
	// Zad 4
	cout << "\n\nZAD 4:\n";
	cout << "Sortowanie Tab3 wzgledem a\n";

	deque< MojeTrio> Poj4;
	std::sort(Tab3.begin(), Tab3.end(), cool_comparator(cool_comparator::A));
	std::copy(Tab3.begin(), Tab3.begin() + 10, std::front_inserter(Poj4));
	drukuj(Poj4, 1);


	cout << "\n\nSortowanie Tab3 wzgledem b\n";
	Poj4.clear(); /* czyszczenie pojemnika */
	std::sort(Tab3.begin(), Tab3.end(), cool_comparator(cool_comparator::B));
	std::copy(Tab3.begin(), Tab3.begin() + 10, std::front_inserter(Poj4)); 
	drukuj(Poj4, 1);


	cout << "\n\nSortowanie Tab3 wzgledem sumy\n";
	Poj4.clear(); /* czyszczenie pojemnika */
	std::sort(Tab3.begin(), Tab3.end(), cool_comparator(cool_comparator::SUMA));
	std::copy(Tab3.begin(), Tab3.begin() + 10, std::front_inserter(Poj4)); 
	drukuj(Poj4, 1);



	cout << "\n\n================\n";
	cout << "Koniec programu \n";



}


