#include <iostream>
#include <string>

using namespace std;

struct Stack {
    char Data;
    Stack* Next;
};

int Prioritet(char Element) {
    if (Element == '(') return 4;
    if (Element == '~') return 3;
    if (Element == '*' || Element == '/') return 2;
    if (Element == '+' || Element == '-') return 1;
    return 0;
}

void AddElement(Stack*& P_begin, char Element) {
    Stack* P = new Stack;
    P->Data = Element;
    P->Next = P_begin;
    P_begin = P;
}

char SeeHead(Stack* P_begin) {
    if (P_begin == nullptr) return '\0';
    return P_begin->Data;
}

char GetElement(Stack*& P_begin) {
    if (P_begin == nullptr) return '\0';
    Stack* Temp = P_begin;
    P_begin = P_begin->Next;
    return Temp->Data;
    delete Temp;
}

bool CorrectString(string & InfixString, string& NewInfixString) {
    int countDigit = 0;
    int countOperation = 0;

    for (int i = 0; i < InfixString.size(); i++) {
        char c = InfixString[i];

        if (!isdigit(c) && c != '-' && c != '+' && c != '/' && c != '*' && c != '(' && c != ')' && c != ' ') {
            cout << "Строка содержит недопустимый символ: " << c << endl;
            return false;
        }

        if (c != ' ') {
            NewInfixString += c;
        }

        if (isdigit(c)) {
            countDigit++;
        }

        if (c == '+' || c == '/' || c == '*') {
            if (i == 0) {
                cout << "В начале может быть использован только унарный минус, ваш знак: " << c << endl;
                return false;
            }
            countOperation++;
        }

        if (c == '-' && i != 0 && NewInfixString[i - 1] != '(') {
            countOperation++;
        }

    }

    for (int i = 0; i < NewInfixString.size(); i++) {
        char c = NewInfixString[i];

        if ((c == '-' || c == '+' || c == '*' || c == '/') && (i > 0 && (NewInfixString[i - 1] == '-' ||
            NewInfixString[i - 1] == '*' || NewInfixString[i - 1] == '+' || NewInfixString[i - 1] == '/'))) {
            cout << "Две операции подряд недопустимы" << endl;
            return false;
        }

    }

    if (countDigit == 0 || (countDigit > 1 && countOperation != countDigit - 1)) {
        cout << "Лишние или недостающие операнды или операторы" << endl;
        return false;
    }

    return true;
}

bool CreateString(string& NewInfixString, string& PostfixString) {
    Stack* P_begin = nullptr;
    
    for (int i = 0; i < NewInfixString.size(); i++) {
        char c = NewInfixString[i];

        if (c == '-' && (i == 0 || NewInfixString[i - 1] == '(' ||
            NewInfixString[i - 1] == '+' || NewInfixString[i - 1] == '-' ||
            NewInfixString[i - 1] == '*' || NewInfixString[i - 1] == '/')) {
            AddElement(P_begin, '~');
            continue;
        }

        if (isdigit(c)) {
            PostfixString += c;
            PostfixString += " ";
        }

        else if (c == '(' || c == '+' || c == '-' || c == '*' || c == '/' || c == '~') {
            while (P_begin != nullptr && SeeHead(P_begin) != '(' &&
                Prioritet(SeeHead(P_begin)) >= Prioritet(c)) {
                PostfixString += GetElement(P_begin);
                PostfixString += " ";
            }
            AddElement(P_begin, c);
        }

        else if (c == ')') {
            while (P_begin != nullptr && SeeHead(P_begin) != '(') {
                PostfixString += GetElement(P_begin);
                PostfixString += " ";
            }
            if (P_begin != nullptr && SeeHead(P_begin) == '(') {
                GetElement(P_begin); 
            }
        }

    }

    while (P_begin != nullptr) {
        if (SeeHead(P_begin) != '(' && SeeHead(P_begin) != ')') {
            PostfixString += GetElement(P_begin);
            PostfixString += " ";
        }
        else {
            GetElement(P_begin);
        }
    }
    
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");

    string InfixString;
    string PostfixString;
    string NewInfixString;

    cout << "Введите выражение в инфиксной форме, например, 2 + 3 * 4 или (2 + 3) * 4: ";
    getline(cin, InfixString);

    if (!CorrectString(InfixString, NewInfixString)) {
        return 0;
    }

    if (CreateString(NewInfixString, PostfixString)) {
        cout << "Постфиксная форма: " << PostfixString << endl;
    }

    else {
        cout << "Выражение записано некорректно" << endl;
    }

    return 0;
}