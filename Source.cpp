#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

struct record
{
	int number;
	int key;
	char TwoName[100];
};

int CreateBoolTxt(string nametf, string namebf)
{
	ifstream itf(nametf);
	if (itf)
	{
		fstream obf(namebf, ios::out | ios::binary);
		record r;
		while (!itf.eof())
		{
			itf >> r.number;
			itf >> r.key;
			itf.get();
			itf.getline(r.TwoName, 100, '\n');
			obf.write((char*)&r, sizeof(record));
		}
		itf.close();
		obf.close();
		return 0;
	}
	return 1;
}

int PoiskKeyInBinFile(string namebf, int key)
{
	ifstream bf;
	bf.open(namebf, ios::binary);
	record r;
	int numRecord = 0;
	bf.read((char*)&r, sizeof(record));
	while (!bf.eof())
	{
		if (r.key == key)
		{
			bf.close();
			return numRecord;
		}
		numRecord++;
		bf.read((char*)&r, sizeof(record));
	}
	bf.close();
	return -1;
}

int PoiskNumberInBinFile(string namebf, int Number)
{
	ifstream bf;
	bf.open(namebf, ios::binary);
	record r;
	int numRecord = 0;
	bf.read((char*)&r, sizeof(record));
	while (!bf.eof())
	{
		if (r.number == Number)
		{
			bf.close();
			return numRecord;
		}
		numRecord++;
		bf.read((char*)&r, sizeof(record));
	}
	bf.close();
	return -1;
}

void NewFileBin(string namebf, int key, string namenewbf)
{
	ifstream bf;
	bf.open(namebf, ios::binary);
	record r;
	fstream obf(namenewbf, ios::out | ios::binary);
	bf.read((char*)&r, sizeof(record));
	while (!bf.eof())
	{
		if (r.key == key)
		{
			obf.write((char*)&r, sizeof(record));
		}
		bf.read((char*)&r, sizeof(record));
	}
	bf.close();
	obf.close();
}

void DeleteBin(string namebf, unsigned int n)
{
	ifstream bf;
	bf.open(namebf, ios::binary);
	record r;
	vector <record> a;
	bf.read((char*)&r, sizeof(record));
	int i = 1;
	while (!bf.eof())
	{
		if (i != n)
		{
			a.push_back(r);
		}
		++i;
		bf.read((char*)&r, sizeof(record));
	}
	bf.close();
	ofstream nbf;
	nbf.open(namebf, ios::binary);
	for (int i = 0; i < a.size(); ++i)
	{
		nbf.write((char*)&a[i], sizeof(record));
	}
	nbf.close();
}

void ZamenaBin(string namebf, int number, int newkey, int newNumber, string NewName)
{
	ifstream bf;
	bf.open(namebf, ios::binary);
	record r;
	vector <record> a;
	bf.read((char*)&r, sizeof(record));
	while (!bf.eof())
	{
		if (r.number == number)
		{
			r.key = newkey;
			r.number = newNumber;
			for (int i = 0; i < NewName.size(); ++i)
			{
				r.TwoName[i] = NewName[i];
			}
			r.TwoName[NewName.size()] = '\0';
		}
		a.push_back(r);
		bf.read((char*)&r, sizeof(record));
	}
	bf.close();
	ofstream nbf;
	nbf.open(namebf, ios::binary);
	for (int i = 0; i < a.size(); ++i)
	{
		nbf.write((char*)&a[i], sizeof(record));
	}
	nbf.close();
}

void ZamenaBinFile(string namebf, string TwoName, string NewName)
{
	
	ifstream bf;
	bf.open(namebf, ios::binary);
	record r;
	vector <record> a;
	string TwoNameS;
	bf.read((char*)&r, sizeof(record));
	while (!bf.eof())
	{
		TwoNameS = "";
		for (int i = 0; r.TwoName[i] != '\0'; ++i)
		{
			TwoNameS += r.TwoName[i];
		}
		if (TwoNameS == TwoName)
		{
			for (int i = 0; i < NewName.size(); ++i)
			{
				r.TwoName[i] = NewName[i];
			}
			r.TwoName[NewName.size()] = '\0';
		}
		a.push_back(r);
		bf.read((char*)&r, sizeof(record));
	}
	bf.close();
	ofstream nbf;
	nbf.open(namebf, ios::binary);
	for (int i = 0; i < a.size(); ++i)
	{
		nbf.write((char*)&a[i], sizeof(record));
	}
	nbf.close();
}

int OutBinFile(string namebf)
{
	fstream obf(namebf, ios::in | ios::binary);
	if (obf.is_open())
	{
		record r;
		obf.read((char*)&r, sizeof(r));
		while (!obf.eof())
		{
			cout << r.number << " " << r.key << " " << r.TwoName << endl;
			obf.read((char*)&r, sizeof(record));
		}
		obf.close();
		return 0;
	}
	return 1;
}

int main()
{
	int kod = CreateBoolTxt("ab.txt", "Data.dat");
	if (kod == 0)
	{
		OutBinFile("Data.dat");
		cout << endl;
		int numRecord = PoiskKeyInBinFile("Data.dat", 10);
		cout << numRecord << endl;
		numRecord = PoiskNumberInBinFile("Data.dat", 3);
		cout << numRecord << endl;
		NewFileBin("Data.dat", 1, "NewData.dat");
		OutBinFile("NewData.dat");
		cout << endl;
		ZamenaBinFile("Data.dat", "five", "Nick");
		OutBinFile("Data.dat");
		cout << endl;
		DeleteBin("Data.dat", 3);
		OutBinFile("Data.dat");
		cout << endl;
		ZamenaBin("Data.dat", 2, 5, 1, "Nick");
		OutBinFile("Data.dat");
	}
	else
	{
		cout << "error";
	}
	return 0;
}