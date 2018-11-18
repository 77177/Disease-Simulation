#include <iostream>
#include <time.h>
#include <list>
#include <fstream>
#include <conio.h>

using namespace std;

enum tst { white, brown, black, spotted };
class creature
{
public:

	char name[10];
	tst	color;
	int age;
	bool radioactive_mutant_vampire_creature, sex;
	int place[2];
};

int main()
{
	srand(time(NULL));
	char field[80][80];
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			field[i][j] = ' ';
		}
	}
	streampos g = 0, s = 0;
	long long male = 0, female = 0, vamps = 0, vamp_counter = 0, female_counter = 0;
	int year = 0, size = 0;
	time_t n = time(NULL);
	char k = ' ';
	char mbn[10][10]{ "Jack","Jamee","Joseph","Mike","Matt","Leo","Leon","Zack","Ian","Kurt" },
	fbn[10][10]{ "Jacklyn","Jay","Josephine","Misa","Masie","Lisa","Lyina","Debra","Ina","Aziza" };
	list<creature> pop;

	//CLEARING OUT THE FILES
	remove("qwerty.txt");
	remove("qwerty123.txt");

	//START INTERFACE
	cout << "//////////////////////////////////////////////////////////////" << endl;
	cout << "Disease simulation" << endl;
	cout << "//////////////////////////////////////////////////////////////" << endl << endl;
	cout << "Designations: " << endl;
	cout << "f(F) - young(adult) female" << endl << "m(M) - young(adult) male" << endl << "X - infected" << endl << endl;
	cout << "Controls: " << endl;
	cout << "q - play the simulation forward" << endl << "w - pause" << endl << "e - rewind" << endl << endl;
	cout << "Press any key to start..." << endl;
	_getch();

	//INSERT THE FIRST 5 CREATUERS
	for (int i = 0; i < 5; i++)
	{
		creature form;
		int c = rand() % 2;
			if (c == 0)
		{
			form.sex = 0;
		}
		else
		{
			form.sex = 1;
		}
		form.age = 0;
		c = rand() % 4;
		if (c == 0)
		{
			form.color = white;
		}
		else if (c == 1)
		{
			form.color = spotted;
		}
		else if (c == 2)
		{
			form.color = brown;
		}
		else if (c == 3)
		{
			form.color = black;
		}
		c = rand() % 10;
		if (form.sex == 0)
		{
			int j = -1;
			do {
				j++;
				form.name[j] = mbn[c][j];
			} while (form.name[j] != '\0');
		}
		else
		{
			int j = -1;
			do {
				j++;
				form.name[j] = fbn[c][j];
			} while (form.name[j] != '\0');
		}
		c = rand() % 100;
		if (c == 0 || c == 1)
		{
			form.radioactive_mutant_vampire_creature = true;
		}
		else
		{
			form.radioactive_mutant_vampire_creature = false;
		}

		int a, b;
		do {
			a = rand() % 80;
			b = rand() % 80;
			form.place[0] = a;
			form.place[1] = b;
			if (field[a][b] == ' ')
			{
				if (form.sex == 1 && form.radioactive_mutant_vampire_creature == false)
				{
					field[form.place[0]][form.place[1]] = 'f';
				}
				else if (form.sex == 0 && form.radioactive_mutant_vampire_creature == false)
				{
					field[form.place[0]][form.place[1]] = 'm';
				}
				else if (form.radioactive_mutant_vampire_creature == true)
				{
					field[form.place[0]][form.place[1]] = 'X';
				}
				break;
			}
		} while (field[a][b] != ' ');
		pop.push_back(form);
	}
	list<creature>::iterator m;
	do
	{
		if (time(NULL) == n + 0,1)
		{   //CLEAN THE CONSOLE
			system("cls");
			if (k == 'q') {

				//SAVE TO FILE
				ofstream fout("qwerty.txt", ios_base::app | ios_base::binary);
				size = pop.size();
				fout.write((char*)&year, 4);
				fout.write((char*)&size, 4);
				for (m = pop.begin(); m != pop.end(); m++)
				{
					creature form = *m;
					fout.write((char*)&form, sizeof(form));
				}
				g = fout.tellp();
				fout.close();

				//ZOMBIE INFECTION COUNT
				for (m = pop.begin(); m != pop.end(); m++)
				{
					if (m->radioactive_mutant_vampire_creature == true)
					{
						int a, b;
						list<creature>::iterator g;
						bool infected = false;


						a = m->place[0];
						b = m->place[1];

						if (((a + 1) <= 79) && ((field[a + 1][b] != ' ' && field[a + 1][b] != 'X')))
						{
							a++;
							infected = true;
						}
						else if ((a - 1) >= 0 && (field[a - 1][b] != ' ' && field[a - 1][b] != 'X'))
						{
							a--;
							infected = true;

						}
						else if (b + 1 <= 79 && (field[a][b + 1] != ' ' && field[a][b + 1] != 'X'))
						{
							b++;
							infected = true;
						}
						else if (b - 1 >= 0 && (field[a][b - 1] != ' ' && field[a][b - 1] != 'X'))
						{
							b--;
							infected = true;
						}
						else if ((a + 1 <= 79) && (b + 1 <= 79) && (field[a + 1][b + 1] != ' ' && field[a + 1][b + 1] != 'X'))
						{
							a++;
							b++;
							infected = true;
						}
						else if ((a - 1 >= 0) && (b + 1 <= 79) && (field[a - 1][b + 1] != ' ' && field[a - 1][b + 1] != 'X'))
						{
							a--;
							b++;
							infected = true;
						}
						else if ((a - 1 >= 0) && (b - 1 >= 0) && (field[a - 1][b - 1] != ' ' && field[a - 1][b - 1] != 'X'))
						{
							a--;
							b--;
							infected = true;
						}
						else if ((a + 1 <= 79) && (b - 1 >= 0) && (field[a + 1][b - 1] != ' ' && field[a + 1][b - 1] != 'X'))
						{
							a++;
							b--;
							infected = true;
						}
						else
						{
							infected = false;
						}

						if (infected == true)
						{
							field[a][b] = 'X';
						}
					}
				}
				for (m = pop.begin(); m != pop.end(); m++)
				{
					if (field[m->place[0]][m->place[1]] == 'X' && m->radioactive_mutant_vampire_creature == false)
					{
						m->radioactive_mutant_vampire_creature = true;
						if (m->sex == 0 && m->age >= 2)
						{
							male--;
						}
						else if (m->sex == 1 && m->age >= 2)
						{
							female--;
						}
					}
				}

				//MOVE 
				for (m = pop.begin(); m != pop.end(); m++)
				{
					int Computer_choice;
					bool moved = false, filled1 = false;
					bool filled2 = false;
					bool filled3 = false;
					bool filled4 = false;
					while (moved == false)
					{
						Computer_choice = rand() % 4;
						switch (Computer_choice)
						{
						case 0:
						{
							if (field[m->place[0] - 1][m->place[1]] != ' ' || m->place[0] == 0)
							{
								filled1 = true;
							}
							else if (field[m->place[0] - 1][m->place[1]] == ' ')
							{
								field[m->place[0]][m->place[1]] = ' ';
								m->place[0] -= 1;
								if (m->age >= 2 && m->sex == 1 && m->radioactive_mutant_vampire_creature == false)
								{
									field[m->place[0]][m->place[1]] = 'F';
								}
								else if (m->age >= 2 && m->sex == 0 && m->radioactive_mutant_vampire_creature == false)
								{
									field[m->place[0]][m->place[1]] = 'M';
								}
								else if (m->sex == 1 && m->radioactive_mutant_vampire_creature == false && m->age < 2)
								{
									field[m->place[0]][m->place[1]] = 'f';
								}
								else if (m->sex == 0 && m->radioactive_mutant_vampire_creature == false && m->age < 2)
								{
									field[m->place[0]][m->place[1]] = 'm';
								}
								else if (m->radioactive_mutant_vampire_creature == true)
								{
									field[m->place[0]][m->place[1]] = 'X';
								}
								moved = true;
							}
							break;
						}
						case 1:
						{
							if (field[m->place[0] + 1][m->place[1]] != ' ' || m->place[0] == 79)
							{
								filled2 = true;
							}
							else if (field[m->place[0] + 1][m->place[1]] == ' ')
							{
								field[m->place[0]][m->place[1]] = ' ';
								m->place[0] += 1;
								if (m->age >= 2 && m->sex == 1 && m->radioactive_mutant_vampire_creature == false)
								{
									field[m->place[0]][m->place[1]] = 'F';
								}
								else if (m->age >= 2 && m->sex == 0 && m->radioactive_mutant_vampire_creature == false)
								{
									field[m->place[0]][m->place[1]] = 'M';
								}
								else if (m->sex == 1 && m->radioactive_mutant_vampire_creature == false && m->age < 2)
								{
									field[m->place[0]][m->place[1]] = 'f';
								}
								else if (m->sex == 0 && m->radioactive_mutant_vampire_creature == false && m->age < 2)
								{
									field[m->place[0]][m->place[1]] = 'm';
								}
								else if (m->radioactive_mutant_vampire_creature == true)
								{
									field[m->place[0]][m->place[1]] = 'X';
								}
								moved = true;
							}
							break;
						}
						case 2:
						{if (field[m->place[0]][m->place[1] - 1] != ' ' || m->place[1] == 0)
						{
							filled3 = true;
						}
						else if (field[m->place[0]][m->place[1] - 1] == ' ')
						{
							field[m->place[0]][m->place[1]] = ' ';
							m->place[1] -= 1;
							if (m->age >= 2 && m->sex == 1 && m->radioactive_mutant_vampire_creature == false)
							{
								field[m->place[0]][m->place[1]] = 'F';
							}
							else if (m->age >= 2 && m->sex == 0 && m->radioactive_mutant_vampire_creature == false)
							{
								field[m->place[0]][m->place[1]] = 'M';
							}
							else if (m->sex == 1 && m->radioactive_mutant_vampire_creature == false && m->age < 2)
							{
								field[m->place[0]][m->place[1]] = 'f';
							}
							else if (m->sex == 0 && m->radioactive_mutant_vampire_creature == false && m->age < 2)
							{
								field[m->place[0]][m->place[1]] = 'm';
							}
							else if (m->radioactive_mutant_vampire_creature == true)
							{
								field[m->place[0]][m->place[1]] = 'X';
							}
							moved = true;
						}
						break;
						}
						case 3:
						{ if (field[m->place[0]][m->place[1] + 1] != ' ' || m->place[1] == 79)
						{
							filled4 = true;
						}
						else if (field[m->place[0]][m->place[1] + 1] == ' ')
						{
							field[m->place[0]][m->place[1]] = ' ';
							m->place[1] += 1;
							if (m->age >= 2 && m->sex == 1 && m->radioactive_mutant_vampire_creature == false)
							{
								field[m->place[0]][m->place[1]] = 'F';
							}
							else if (m->age >= 2 && m->sex == 0 && m->radioactive_mutant_vampire_creature == false)
							{
								field[m->place[0]][m->place[1]] = 'M';
							}
							else if (m->sex == 1 && m->radioactive_mutant_vampire_creature == false && m->age < 2)
							{
								field[m->place[0]][m->place[1]] = 'f';
							}
							else if (m->sex == 0 && m->radioactive_mutant_vampire_creature == false && m->age < 2)
							{
								field[m->place[0]][m->place[1]] = 'm';
							}
							else if (m->radioactive_mutant_vampire_creature == true)
							{
								field[m->place[0]][m->place[1]] = 'X';
							}
							moved = true;
						}
						break;
						}
						}

						if ((filled1 == true && filled2 == true) && (filled3 == true && filled4 == true))
						{
							break;
						}
					}
				}

				//BIRTH COUNT
				female_counter = female;
				if (male >= 1)
				{
					m = pop.begin();
					while (female_counter != 0)
					{
						if ((m->sex == 1 && m->age >= 2) && m->radioactive_mutant_vampire_creature == false)
						{
							creature form;
							int c = rand() % 2;
							if (c == 0)
							{
								form.sex = 0;
							}
							else
							{
								form.sex = 1;
							}
							form.age = 0;
							form.color = m->color;
							c = rand() % 10;
							if (form.sex == 0)
							{
								int j = -1;
								do {
									j++;
									form.name[j] = mbn[c][j];
								} while (form.name[j] != '\0');
							}
							else
							{
								int j = -1;
								do {
									j++;
									form.name[j] = fbn[c][j];
								} while (form.name[j] != '\0');
							}
							c = rand() % 100;
							if (c == 0 || c == 1)
							{
								form.radioactive_mutant_vampire_creature = true;
								vamps += 1;
							}
							else
							{
								form.radioactive_mutant_vampire_creature = false;
							}
							int a, b;
							a = m->place[0];
							b = m->place[1];
							bool birth = true;
							{
								if (((a + 1) <= 79) && (field[a + 1][b] == ' '))
								{
									a++;
								}
								else if ((a - 1) >= 0 && field[a - 1][b] == ' ')
								{
									a--;
								}
								else if ((b + 1 <= 79) && field[a][b + 1] == ' ')
								{
									b++;
								}
								else if ((b - 1 >= 0) && field[a][b - 1] == ' ')
								{
									b--;
								}
								else if ((a + 1 <= 79) && (b + 1 <= 79) && field[a + 1][b + 1] == ' ')
								{
									a++;
									b++;
								}
								else if ((a - 1 >= 0) && (b + 1 <= 79) && field[a - 1][b + 1] == ' ')
								{
									a--;
									b++;
								}
								else if ((a - 1 >= 0) && (b - 1 >= 0) && field[a - 1][b - 1] == ' ')
								{
									a--;
									b--;
						     	}
								else if ((a + 1 <= 79) && (b - 1 >= 0) && field[a + 1][b - 1] == ' ')
								{
									a++;
									b--;
								}
								else
								{
									birth = false;
								}
							}

							if (birth == true)
							{
								form.place[0] = a;
								form.place[1] = b;
								if (form.sex == 1 && form.radioactive_mutant_vampire_creature == false)
								{
									field[form.place[0]][form.place[1]] = 'f';
								}
								else if (form.sex == 0 && form.radioactive_mutant_vampire_creature == false)
								{
									field[form.place[0]][form.place[1]] = 'm';
								}
								else if (form.radioactive_mutant_vampire_creature == true)
								{
									field[form.place[0]][form.place[1]] = 'X';
								}
								pop.push_back(form);
							}
							female_counter--;
						}
						m++;
					}
				}

				//ADD A YEAR| FEMALE AND MALE AND ZOMBIE GROUPING| DEATH OF CREATURE DUE TO AGE|
				m = pop.begin();
				vamps = 0;
				female = 0;
				male = 0;
				while (m != pop.end())
				{
					if (m->age == 10 && m->radioactive_mutant_vampire_creature == false)
					{
						field[m->place[0]][m->place[1]] = ' ';
						if (m->sex == 0)
						{
							male -= 1;
						}
						else
						{
							female -= 1;
						}
						m = pop.erase(m);
					}
					else if (m->age == 50)
					{
						field[m->place[0]][m->place[1]] = ' ';
						m = pop.erase(m);
						vamps--;
					}
					else
					{
						m->age += 1;
						if (m->radioactive_mutant_vampire_creature == true)
						{
							vamps++;
						}
						else if (m->radioactive_mutant_vampire_creature == false && m->age >= 2 && m->sex == 0)
						{
							male++;
						}
						else if (m->radioactive_mutant_vampire_creature == false && m->age >= 2 && m->sex == 1)
						{
							female++;
						}
						if (m->sex == 0 && m->age == 2 && m->radioactive_mutant_vampire_creature == false)
						{
							field[m->place[0]][m->place[1]] = 'M';
						}
						else if (m->sex == 1 && m->age == 2 && m->radioactive_mutant_vampire_creature == false)
						{
							field[m->place[0]][m->place[1]] = 'F';
						}
						m++;
					}
				}
				vamp_counter = vamps;
				year++;
			}
			else if (k == 'e')
			{
				int y, q, bas = year - 1;
				streampos pos = 0;

				if (year != 0)
				{
					//REWRITE TO A CREATED FILE
					ifstream fin("qwerty.txt", ios_base::binary);
					ofstream fin2("qwerty123.txt", ios_base::app | ios_base::binary);
					do
					{
						pop.clear();
						fin.read((char*)&y, sizeof(int));
						fin.read((char*)&q, sizeof(int));

						for (int i = 0; i < q; i++)
						{
							creature form;
							fin.read((char*)&form, sizeof(creature));
							pop.push_back(form);
						}
						m = pop.begin();
						if (y <= (bas - 1))
						{

							fin2.write((char*)&y, sizeof(int));
							fin2.write((char*)&q, sizeof(int));

							for (int i = 0; i < q; i++)
							{
								fin2.write((char*)&*m, sizeof(creature));
								m++;
							}
							pos = fin2.tellp();
						}
					} while (y != bas);
					fin2.close();
					fin.close();
					g = pos;

					//RENAME THE FILE
					remove("qwerty.txt");
					rename("qwerty123.txt", "qwerty.txt");

					//RECOUNT THE POPULATION
					for (int i = 0; i < 80; i++)
					{
						for (int j = 0; j < 80; j++)
						{
							field[i][j] = ' ';
						}
					}
					female = 0;
					male = 0;
					vamps = 0;
					for (m = pop.begin(); m != pop.end(); m++)
					{
						if (m->sex == 0 && m->age < 2 && m->radioactive_mutant_vampire_creature == false)
						{
							field[m->place[0]][m->place[1]] = 'm';
						}
						else if (m->sex == 1 && m->age < 2 && m->radioactive_mutant_vampire_creature == false)
						{
							field[m->place[0]][m->place[1]] = 'f';
						}
						else if (m->sex == 0 && m->age >= 2 && m->radioactive_mutant_vampire_creature == false)
						{
							field[m->place[0]][m->place[1]] = 'M';
							male++;
						}
						else if (m->sex == 1 && m->age >= 2 && m->radioactive_mutant_vampire_creature == false)
						{
							field[m->place[0]][m->place[1]] = 'F';
							female++;
						}
						else if (m->radioactive_mutant_vampire_creature == true)
						{
							field[m->place[0]][m->place[1]] = 'X';
							vamps++;
						}
					}
					year--;
				}
				else
				{
					pop.clear();
					year--;
				}
			}
			else if (k == 'w')
			{
				//NO CHANGES
			}

//PRINT OUT THE FIELD
			for (int i = 0; i < 80; i++)
			{
				cout << field[i][0] << field[i][1] << field[i][2] << field[i][3] << field[i][4]
					<< field[i][5] << field[i][6] << field[i][7] << field[i][8] << field[i][9]
					<< field[i][10] << field[i][11] << field[i][12] << field[i][13] << field[i][14]
					<< field[i][15] << field[i][16] << field[i][17] << field[i][18] << field[i][19]
					<< field[i][20] << field[i][21] << field[i][22] << field[i][23] << field[i][24] << field[i][25]
					<< field[i][26] << field[i][27] << field[i][28] << field[i][29] << field[i][30]
					<< field[i][31] << field[i][32] << field[i][33] << field[i][34] << field[i][35]
					<< field[i][36] << field[i][37] << field[i][38] << field[i][39] << field[i][40]
					<< field[i][41] << field[i][42] << field[i][43] << field[i][44] << field[i][45]
					<< field[i][46] << field[i][47] << field[i][48] << field[i][49] << field[i][50]
					<< field[i][51] << field[i][52] << field[i][53] << field[i][54] << field[i][55]
					<< field[i][56] << field[i][57] << field[i][58] << field[i][59] << field[i][60]
					<< field[i][61] << field[i][62] << field[i][63] << field[i][64] << field[i][65]
					<< field[i][66] << field[i][67] << field[i][68] << field[i][69] << field[i][70]
					<< field[i][71] << field[i][72] << field[i][73] << field[i][74] << field[i][75]
					<< field[i][76] << field[i][77] << field[i][78] << field[i][79];
			}

			cout << "Year: " << year << endl;

			if (_kbhit() == 1 && year >= 0)
			{
				k = _getch();
			}
				
			n = time(NULL);
		}
	} while (pop.size() != 0);
	system("cls");
	cout << "The population died out after " << year << " years" << endl;
	return 0;
}



