#include <iostream>
#include <string>

using namespace std;

struct Stack {
    char Data;
    Stack* Next;
};

int Prioritet(char Element) {
    if (Element == '(') return 1;
    if (Element == '~') return 4;
    if (Element == '*' || Element == '/') return 3;
    if (Element == '+' || Element == '-') return 2;
}

void AddElement(Stack*& P_begin, char Element) {
    Stack* P = new Stack;
    P->Data = Element;
    P->Next = P_begin;
    P_begin = P;
}

char GetElement(Stack*& P_begin) {
    if (P_begin == nullptr) return '\0';
    Stack* Temp = P_begin;
    P_begin = P_begin->Next;
    return Temp->Data;
    delete Temp;
}

bool CreateString(string& InfixString, string& PostfixString) {
    Stack* P_begin = nullptr;
    string NewInfixString;
    int countOpen = 0;
    int countClose = 0;

    for (int i = 0; i < InfixString.size(); i++) {
        char c = InfixString[i];

        if (c == ' ') {
            continue;
        } 
        else {
            NewInfixString += InfixString[i];
        }

        if (c == '(') {
            countOpen++;
        }

        if (c == ')') {
            countClose++;
        }

        if (!isdigit(c) && c != '-' && c != '+' && c != '/' && c != '*' && c != '(' && c != ')') {
            return false;
            exit;
        }

    }

    if (countOpen == countClose) {

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

            if (c == '(') {
                AddElement(P_begin, c);
            }

            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '~') {
                while (P_begin != nullptr && P_begin->Data != '(' &&
                    Prioritet(P_begin->Data) >= Prioritet(c)) {
                    PostfixString += GetElement(P_begin);
                    PostfixString += " ";
                }
                AddElement(P_begin, c);
            }

            if (c == ')') {
                while (P_begin != nullptr && P_begin->Data != '(') {
                    PostfixString += GetElement(P_begin);
                    PostfixString += " ";
                }
                if (P_begin != nullptr && P_begin->Data == '(') {
                    GetElement(P_begin);
                }
            }
        }

        while (P_begin != nullptr) {
            PostfixString += GetElement(P_begin);
            PostfixString += " ";
        }

    }

    else {
        cout << "В вашем выражении не хватает скобок, открывающих: " << countOpen << ", закрываюших: " << countClose << endl;
    }

    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");

    string InfixString;
    string PostfixString;
    cout << "Введите выражение в инфиксной форме: ";
    getline(cin, InfixString);

    if (CreateString(InfixString, PostfixString)) {
        cout << "Постфиксная форма: " << PostfixString << endl;
    }

    else {
        cout << "Выражение содержит некорректные символы" << endl;
    }

    return 0;
}