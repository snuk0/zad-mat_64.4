#include <iostream>
#include <fstream>
using namespace std;

const int SIZE = 200;
ifstream in("dane_obrazki.txt");
char tab[21][21];

void readPicture() {
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 21; j++) {
            if (i == 20 && j == 20) return;
            in >> tab[i][j];
        }
    }
}


int countWrongParityHorizontal() {
    int sum = 0, counter = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 21; j++) {
            if (tab[i][j] == '1' && j != 20) sum++;
            if (j == 20) {
                if (sum % 2 == 0 && tab[i][j] == '1') counter++;
                if (sum % 2 == 1 && tab[i][j] == '0') counter++;
            }
        }
        sum = 0;
    }
    return counter;
}

int countWrongParityVertical() {
    int sum = 0, counter = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 21; j++) {
            if (tab[j][i] == '1' && j != 20) sum++;
            if (j == 20) {
                if (sum % 2 == 0 && tab[j][i] == '1') counter++;
                if (sum % 2 == 1 && tab[j][i] == '0') counter++;
            }
        }
        sum = 0;
    }
    return counter;
}

int countWrongParity() {
    return countWrongParityHorizontal() + countWrongParityVertical();
}

bool isCorrect() {
    if (countWrongParity() == 0) return true;
}

bool isRepairable() {
    if (isCorrect()) return false;
    if (countWrongParityVertical() < 2 && countWrongParityHorizontal() < 2)
        return true;
}

int main() {
    int pictureCounter = 0, controlSum, line, column;
    for (int n = 0; n < SIZE; n++) 
    {
        readPicture();
        pictureCounter++;
        if (isRepairable()) {
            column = 0;
            line = 0;
            cout << "(" << pictureCounter << ", ";
            // Sprawdzenie bitu poziomo
            if (countWrongParityHorizontal() == 1) {
                controlSum = 0;
                for (int i = 0; i < 20; i++) {
                    for (int j = 0; j < 21; j++) {
                        if (tab[i][j] == '1' && j != 20) controlSum++;
                        if (j == 20) {
                            if ((controlSum % 2 == 0 && tab[i][j] == '1') ||
                                (controlSum % 2 == 1 && tab[i][j] == '0')) {
                                line = i + 1;
                            }
                        }
                    }
                    controlSum = 0;
                }
            }
            // Sprawdzenie bitu pionowo
            if (countWrongParityVertical() == 1) {
                controlSum = 0;
                for (int i = 0; i < 20; i++) {
                    for (int j = 0; j < 21; j++) {
                        if (tab[j][i] == '1' && j != 20) controlSum++;
                        if (j == 20) {
                            if ((controlSum % 2 == 0 && tab[j][i] == '1') ||
                                (controlSum % 2 == 1 && tab[j][i] == '0')) {
                                column = i + 1;
                            }
                        }
                    }
                    controlSum = 0;
                }
            }
            if (line == 0) line = 21;
            if (column == 0) column = 21;
            cout << line << ", " << column << ")" << endl;
        }
    }

}
