#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <unordered_map>

std::string alegereCuvant()
{
	std::fstream fisier;
	fisier.open("date.txt", std::ios::in);
	if (!fisier)
	{
		exit(1);
	}
	int numarCuvinte = 0;
	std::string cuvant;
	std::vector<std::string> cuvinte;
	while (!fisier.eof())
	{
		fisier >> cuvant;
		cuvinte.push_back(cuvant);
	}
	srand(unsigned int(time(NULL)));
	return cuvinte[rand() % cuvinte.size()];
}

class Spanzuratoare
{
	int m_greseliPermise;
	std::unordered_map<char, std::vector<int>> m_pozitieChar;
	std::vector<char> m_formareCuvant;

	void printStareCuvant()
	{
		for (int i = 0; i < m_formareCuvant.size(); i++)
		{
			if (i + 1 < m_formareCuvant.size() && m_formareCuvant[i + 1] != '_')
			{
				std::cout << m_formareCuvant[i];
			}
			else if (m_formareCuvant[i] != '_')
			{
				std::cout << m_formareCuvant[i];
			}
			else
			{
				std::cout << m_formareCuvant[i] << " ";
			}
		}
		std::cout << std::endl;
	}
public:
	Spanzuratoare(std::string cuvant, int greseliPermise = 6)
	{
		m_greseliPermise = greseliPermise;
		int pozitie = 0;
		m_formareCuvant.resize(cuvant.size());
		for (char c : cuvant)
		{
			m_pozitieChar[c].push_back(pozitie);
			m_formareCuvant[pozitie] = '_';
			pozitie++;
		}
	}
	void Start()
	{
		std::cout << "Introduceti 0 pentru a opri jocul" << std::endl;
		char caracter = '1';
		int litereGhicite = 0;
		while (litereGhicite != m_formareCuvant.size())
		{
			printStareCuvant();
			std::cin >> caracter;
			if (m_pozitieChar[caracter].size() != 0)
			{
				m_formareCuvant[m_pozitieChar[caracter].front()] = caracter;
				m_pozitieChar[caracter].erase(m_pozitieChar[caracter].begin());
				litereGhicite++;
			}
			else if (caracter != '0')
			{
				m_greseliPermise--;
				std::cout << "Litera incorecta, mai ai " << m_greseliPermise << " greseli permise" << std::endl;
				if (m_greseliPermise == 0)
				{
					caracter = '0';
					std::cout << "Ai pierdut!";
					return;
				}
			}
			else
			{
				std::cout << "Goodbye!";
				return;
			}
		}
		printStareCuvant();
		std::cout << "Ai castigat!";
	}

};

int main()
{
	std::string cuvant = alegereCuvant();
	Spanzuratoare joc(cuvant);
	joc.Start();
	return 0;
}