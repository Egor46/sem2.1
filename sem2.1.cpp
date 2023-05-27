#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

// номер 6

const int MAX_NAME = 20;

using namespace std;

typedef char Edu, Fam, Prof;

struct birthDate {
public:
	int bdate;
	unsigned short int day = 0, month = 0, year = 0;

	birthDate() {
		bdate = 0;
	};

	void transform() {
		int tdate = bdate;
		year = tdate % 10000;
		tdate /= 10000;
		month = tdate % 100;
		tdate /= 100;
		day = tdate % 100;
	}
};

ifstream& operator >> (ifstream& in, birthDate& a) {
	in >> a.bdate;
	a.transform();
	return in;
}

struct address {
	char city[25]{};
	char street[30]{};
	int house;
	int apt;

	address() {
		house = 0;
		apt = 0;
	};
};
ifstream& operator >> (ifstream& in, address& a) {
	in >> a.city >> a.street >> a.house >> a.apt;
	return in;
}


struct pinfo {
	char familia[MAX_NAME]{}, name[MAX_NAME]{}, patronymic[MAX_NAME]{};
	birthDate bdate;
	Edu edu;
	Fam fam;
	int childAmount;
	Prof prof;
	address adr;
	int phone;

	pinfo() {
		edu = 0;
		fam = 0;
		phone = 0;
		prof = 0;
		childAmount = 0;
	}
};

ifstream& operator >> (ifstream& in, pinfo& a) {
	in >> a.familia >> a.name >> a.patronymic;
	in >> a.bdate >> a.edu >> a.fam >> a.childAmount >> a.prof;
	in >> a.adr >> a.phone;
	return in;
}

ostream& operator << (ostream& out, pinfo a) {
	string base;
	base = (string)a.familia + ' ' + a.name[0] + ". " + a.patronymic[0];
	out << base;
	return out;
}

ofstream& operator << (ofstream& out, pinfo a) {
	out << a.familia << ' ' << a.name << ' ' << a.patronymic << ' ' << a.bdate.bdate << ' ' << a.edu << ' ' << a.fam << ' ' << a.childAmount << ' ' << a.prof << ' '
		<< a.adr.city << ' ' << a.adr.street << ' ' << a.adr.house << ' ' << a.adr.apt << ' ' << a.phone;
	return out;
}

void createBinary(ifstream& in) {
	ofstream out("work.bin", ios::binary);
	pinfo t;
	while (!in.eof()) {
		in >> t;
		out.write((char*)&t, sizeof(t));
	}
	out.close();
}

void TaskAAux(ifstream& in, Edu& min, Edu& max) {
	pinfo p;
	int mm[] = { 0, 0 ,0 }; // В C Н
	while (!in.eof()) {
		in >> p;
		if (p.edu == 'В') mm[0]++;
		else if (p.edu == 'С') mm[1]++;
		else mm[2]++;
	}
	min = mm[0] < mm[1] ? (mm[0] < mm[2] ? 'В' : 'Н') : (mm[1] < mm[2] ? 'С' : 'Н');
	max = mm[0] > mm[1] ? (mm[0] > mm[2] ? 'В' : 'Н') : (mm[1] > mm[2] ? 'С' : 'Н');
}

void TaskAMain(ifstream& in, Edu min, Edu max) {
	ofstream minL("least.bin", ios::binary);
	ofstream maxL("most.bin", ios::binary);
	pinfo p;
	while (!in.eof()) {
		in >> p;
		if (p.edu == min) {
			minL.write((char*)&p, sizeof(p));
		}
		else if (p.edu == max) {
			maxL.write((char*)&p, sizeof(p));
		}
	}
	minL.close();
	maxL.close();
}

void TaskB() {
	ifstream most("least.bin", ios::binary);
	ifstream least("most.bin", ios::binary);
	pinfo p1, p2;
	cout << setw(88) << setfill('-') << '\n';
	cout.setf(ios::left);
	cout << setw(43) << setfill(' ') << "|          Наименьшая группа" << setw(43) << "|               Наибольшая группа" << '|' << endl;
	cout << setw(43) << setfill('-') << '|' << setw(43) << '|' << '|' << endl;
	cout << setw(17) << setfill(' ') << "|   Фамилия ИО" << "| Возр |" << " Сем.п |" << " Дет |" << " Пр ";
	cout << setw(17) << setfill(' ') << "|   Фамилия ИО" << "| Возр |" << " Сем.п |" << " Дет |" << " Пр |" << endl;
	cout << setw(86) << setfill('-') << '|' <<'|' << endl;
	while (!least.eof() && !most.eof()) {
		least.read((char*)&p1, sizeof(p1));
		most.read((char*)&p2, sizeof(p2));
		cout << setfill(' ') <<  setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|'
			<< setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|' << '|' << endl;
		cout << setfill(' ') << '|' << left << setw(16) << p1 << "|  " << setw(4) << 2023 - p1.bdate.year << "|   " << setw(4)
			<< p1.fam << "|  " << setw(3) << p1.childAmount << "| " << setw(3) << p1.prof << "|";
		cout << setfill(' ') << left << setw(16) << p2 << "|  " << setw(4) << 2023 - p2.bdate.year << "|   " << setw(4)
			<< p2.fam << "|  " << setw(3) << p2.childAmount << "| " << setw(3) << p2.prof << "|" << endl;
		cout << setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|'
			<< setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|' << '|' << endl;
		cout << setw(86) << setfill('-') << '|' << '|' << endl;
	}
	if (least.eof()) {
		while (!most.eof()) {
			most.read((char*)&p1, sizeof(p1));
			cout << setfill(' ') << setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|'
				<< setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|' << '|' << endl;
			cout << setfill(' ') << '|' << left << setw(16) << p1 << "|  " << setw(4) << 2023 - p1.bdate.year << "|   " << setw(4)
				<< p1.fam << "|  " << setw(3) << p1.childAmount << "| " << setw(3) << p1.prof
				<< setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|' << '|' << endl;
			

			cout << setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|'
				<< setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|' << '|' << endl;
			cout << setw(86) << setfill('-') << '|' << '|' << endl;
		}
	}
	else if (most.eof()) {
		while (!least.eof()) {
			least.read((char*)&p2, sizeof(p2));
			cout << setfill(' ') << setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|'
				<< setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|' << '|' << endl;
			cout << setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|' << '|' <<
				setfill(' ') << left << setw(16) << p2 << "|  " << setw(4) << 2023 - p2.bdate.year << "|   " << setw(4)
				<< p2.fam << "|  " << setw(3) << p2.childAmount << "| " << setw(3) << p2.prof << "|" << endl;
			cout << setfill(' ') << setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|'
				<< setw(17) << '|' << setw(7) << '|' << setw(8) << '|' << setw(6) << '|' << setw(5) << '|' << '|' << endl;
			cout << setw(86) << setfill('-') << '|' << '|' << endl;
		}
	}
	least.close();
	most.close();
}

int main() {
	setlocale(LC_ALL, "rus");
	ifstream in("base.txt");
	Edu min, max;
	TaskAAux(in, min, max);
	in.close();
	in.open("base.txt");
	TaskAMain(in,min,max);
	in.close();
	TaskB();
}
