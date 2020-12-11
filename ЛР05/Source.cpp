#include <iostream>
#include <locale>
#include <vector>
#include <Windows.h>

#define p0 1
#define dA 2
#define dB 1

using namespace std;

struct Process
{
	int birthTime,oldBirth, runTime, status,p = p0;
	bool nw=true;
};

/*
Статус:
* 0 - empty
* 1 - ready
* 2 - in progress
* 3 - done
*/

int main()
{
	setlocale(LC_ALL, "Russian");

	int n;
	vector<Process> processes;
	Process temp;

	while (true)
	{
		system("cls");
		cout << "Введите количество процессов: ";
		cin >> n;

		if (n > 0) break;
	}
	
	for (int i = 0; i < n; i++)
	{
		cout << endl << "ПРОЦЕСС №" << i + 1 << ":" << endl;
		cout << "Старт: ";
		cin >> temp.birthTime;
		cout << "Длительность: ";
		cin >> temp.runTime;
		temp.oldBirth = temp.birthTime;
		temp.status = (temp.birthTime == 0 ? 1 : 0);
		processes.push_back(temp);
	}

	bool b = true, inProg;

	cout << endl << "F C F S" << endl;

	cout << "\t";
	for (int i = 0; i < n; i++)
	{
		cout << i+1 << "\t";
	}
	cout << endl;

	for (int j = 1; b; j++)
	{
		b = false;

		inProg = false;

		for (int i = 0; i < n; i++)
		{
			if (processes[i].status == 2)
			{
				inProg = true;
				break;
			}
		}

		cout << j << " кв.\t";

		for (int i = 0; i < n; i++)
		{
			if (processes[i].birthTime < j && !inProg && processes[i].status != 2 && processes[i].status != 3)
			{
				processes[i].birthTime = j;
				processes[i].status = 2;
				inProg = true;
			}
			else
			{
				if (processes[i].birthTime < j && inProg && processes[i].status != 2 && processes[i].status != 3)
				{
					processes[i].status = 1;
				}
				else
				{
					if (j == processes[i].birthTime + processes[i].runTime)
					{
						processes[i].status = 3;
						inProg = false;

						/*for (int k = 0; k < n; k++)
						{
							if (processes[k].birthTime < j && !inProg && processes[k].status != 2 && processes[k].status != 3)
							{
								processes[k].birthTime = j;
								processes[k].status = 2;
								inProg = true;
							}
						}*/
					}
				}
			}

			switch (processes[i].status)
			{
			case 0:
				cout << "empty";
				break;
			case 1:
				cout << "ready";
				break;
			case 2:
				cout << "run";
				break;
			case 3:
				cout << "done";
				break;
			}

			cout << "\t";
		}

		Sleep(500);

		for (int i = 0; i < n; i++)
		{
			if (processes[i].status != 3)
			{
				b = true;
				cout << endl;
				break;
			}
		}
	}

	cout << endl;
	system("pause");
	
	for (int i = 0; i < n; i++)
	{
		processes[i].birthTime = processes[i].oldBirth;
		processes[i].status = (processes[i].birthTime == 0 ? 1 : 0);
	}

	cout << endl << "S R R" << endl;

	cout << "\t";
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << "\t";
	}
	cout << endl;

	b = true;

	for (int j = 1; b; j++)
	{
		b = false;

		cout << j << " кв.\t";

		int ooo = -1;
		int maxP = -1;

		for (int i = 0; i < n; i++)
		{
			if (processes[i].status == 0 && processes[i].birthTime < j) processes[i].status = 1;
		}

		for (int i = 0; i < n; i++)
		{
			if (processes[i].status == 1 && processes[i].p > maxP )
			{
				maxP = processes[i].p;
				ooo = i;
			}
			else
			{
				if (processes[i].status == 1 && processes[i].p == maxP)
				{
					if (processes[i].oldBirth < processes[ooo].oldBirth)
					{
						ooo = i;
					}
				}
			}
		}

		processes[ooo].status = 2;
		processes[ooo].runTime--;
		processes[ooo].nw = false;

		for (int i = 0; i < n; i++)
		{
			switch (processes[i].status)
			{
			case 0:
				cout << "emp";
				break;
			case 1:
				cout << "rea" << processes[i].p;
				break;
			case 2:
				cout << "run" << processes[i].p;
				break;
			case 3:
				cout << "don" << processes[i].p;
				break;
			}

			cout << "\t";
		}
		
		if (processes[ooo].runTime==0)
		{
			processes[ooo].status = 3;
		}

		for (int i = 0; i < n; i++)
		{
			if (processes[i].status==2)
			{
				processes[i].status = 1;
			}
			if (processes[i].status == 1 && processes[i].nw)
			{
				processes[i].p += dA;
				continue;
			}
			if (processes[i].status == 1 && !processes[i].nw)
			{
				processes[i].p += dB;
				continue;
			}
		}

		Sleep(500);

		for (int i = 0; i < n; i++)
		{
			if (processes[i].status != 3)
			{
				b = true;
				cout << endl;
				break;
			}
		}
	}
	
	cout << endl;
	system("pause");

	return 0;
}
