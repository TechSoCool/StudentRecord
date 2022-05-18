#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

ifstream inputName, inputGrade;
int const ROW = 5;
int const COL = 6;

struct Student {
	string name[ROW];
	string letterGrade[ROW];
	int grade[ROW][COL];
	int sumGrade[ROW] = {};
	double averageGrade[ROW];
};

void initialize(struct Student& data)
{
	inputName.open("Name.txt");
	inputGrade.open("Grades.txt");

	for (int r = 0; r < ROW; r++)
	{
		getline(inputName, data.name[r]);
		for (int c = 0; c < COL; c++)
		{
			inputGrade >> data.grade[r][c];
		}
	}

}

void display(struct Student& data) {
	ofstream file("Result.txt", ios::app);
	for (int r = 0; r < ROW; r++)
	{
		file << "Name: " << data.name[r] << endl;
		file << "Grade: ";

		for (int c = 0; c < COL; c++) {
			file << endl;
			file << "Sum: " << data.sumGrade[r];
			file << "Average: " << data.averageGrade[r];
			file << "Letter Grade: " << data.letterGrade[r];
			file << endl << endl;
		}
		file.close();
	}
}


void sum(struct Student& data) {
	int sum = 0;
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			data.sumGrade[r] = sum += data.grade[r][c];
		}
		sum = 0;
	}
}

void average(struct Student& data) {
	for (int r = 0; r < ROW; r++)
	{
		data.averageGrade[r] = (data.sumGrade[r] / 6);
	}
}

void letter(struct Student& data)
{
	for (int r = 0; r < ROW; r++)
	{
		if (data.averageGrade[r] >= 90)
			data.letterGrade[r] = 'A';
		else if (data.averageGrade[r] >= 80)
			data.letterGrade[r] = 'B';
		else if (data.averageGrade[r] >= 70)
			data.letterGrade[r] = 'C';
		else if (data.averageGrade[r] >= 60)
			data.letterGrade[r] = 'D';
		else
			data.letterGrade[r] = 'F';
	}
}

// sort alphabet order 
void sortOrder(struct Student& data) {
	int c = 0;

	for (int i = 0; i < ROW; i++) {
		for (int j = i + 1 ; j < ROW; j++) {
			if (data.name[i] > data.name[j]) {
				string temp = data.name[i];
				data.name[i] = data.name[j];
				data.name[j] = temp;

				// switch the grade
				for (int c = 0; c < COL; c++)
				{
					int temp1 = data.grade[i][c];
					data.grade[i][c] = data.grade[j][c];
					data.grade[j][c] = temp1;
				}

				// swith the sum
				int temp2 = data.sumGrade[i];
				data.sumGrade[i] = data.sumGrade[j];
				data.sumGrade[j] = temp2;

				// switch the average
				int temp3 = data.sumGrade[i];
				data.sumGrade[i] = data.sumGrade[j];
				data.sumGrade[j] = temp3;

				// switch LetterGrade
				string temp4 = data.letterGrade[i];
				data.letterGrade[i] = data.letterGrade[j];
				data.letterGrade[j] = temp4;

			}
		}
	}
}

int search(struct Student& data, string username, int i)
{
	for (i = 0; i < ROW; i++)
	{
		if (username == data.name[i]) {
			return i;
		}
	}
	return -1;
}


int main()
{
	Student data;
	initialize(data);
	sum(data);
	average(data);
	letter(data);
	sortOrder(data);
	display(data);

	string user;
	int position = 0;
	cout << "Enter the Student Name: ";
	getline(cin, user);

	int result = search(data, user, position);
	if (result == -1) {
		cout << "N/A" << endl;
	}
	else {
		cout << data.name[result] << endl;
		cout << "Grades: ";
		for (int x = 0; x < COL; x++)
		{
			cout << data.grade[result][x] << ' ';
		}
		cout << "\nSum: " << data.sumGrade[result] << endl;
		cout << "Average: " << data.averageGrade[result] << endl;
		cout << "Letter Grade: " << data.letterGrade[result] << endl;
	}

	system("pause");

		return 0;
}
