#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

class var{
public:
    var() {
        type = Int;
        value.i = 0;
    }
    var(const var& a) {
        if (type == String)
            delete value.str;
        type = a.type;
        value = a.value;
    }
    enum {
        Int,
        Char,
        String
    } type;
    union {
        int i;
        char c;
        char* str;
    } value;
};

const unsigned int datasLength = 2048;
var* datas[datasLength];
unsigned int index = 0;

int run(string);
string script(string);
var* singleParse(string,unsigned int&);

int main(int argc,char* argv[])
{
    if (argc > 1) {
        run(script(argv[1]));
    }
    else {
        cout << "Hello NewFuck\n";
        cout << "Type 'quit' to exit\n";
        string cmd = "";
        datas[0] = new var;
        for (int i = 1; i < datasLength; i++)
            datas[i] = NULL;
        while (cmd != "quit") {
            cout << ">>>";
            getline(std::cin, cmd);
            cmd += '\n';
            run(cmd);
        }
        std::cin.get();
    }
}

int run(string cmd) {
    for (unsigned int i = 0; i < cmd.length(); i++) {
        switch (cmd[i]) {
        case 'r':
            run(script(datas[index]->value.str));
            break;
        case 'i':
            if (datas[index]->type == var::String) {
                delete datas[index]->value.str;
                datas[index]->value.str = NULL;
            }
            datas[index]->type = var::Int;
            break; 
        case 'c':
            if (datas[index]->type == var::String) {
                delete datas[index]->value.str;
                datas[index]->value.str = NULL;
            }
            datas[index]->type = var::Char;
            break;
        case 's':
            if (datas[index]->type != var::String){
                datas[index]->type = var::String;
                datas[index]->value.str = new char[1025];
            }
            break;
        case '+':
            if (datas[index]->type == var::Int)
                datas[index]->value.i++;
            else if (datas[index]->type == var::Char)
                datas[index]->value.c++;
            else
                cout << "failed adding in " << i << endl;
            break;
        case '-':
            if (datas[index]->type == var::Int)
                datas[index]->value.i--;
            else if (datas[index]->type == var::Char)
                datas[index]->value.c--;
            else
                cout << "failed substrictiing in " << i << endl;
            break;
        case '.':
            if (datas[index]->type == var::Int)
                cout << datas[index]->value.i << endl;
            else if (datas[index]->type == var::Char)
                cout << datas[index]->value.c << endl;
            else if (datas[index]->type == var::String)
                cout << datas[index]->value.str << endl;
            break;
        case ',':
            if (datas[index]->type == var::Int)
                std::cin >> datas[index]->value.i;
            else if (datas[index]->type == var::Char)
                std::cin >> datas[index]->value.c;
            else if (datas[index]->type == var::String)
                std::cin >> datas[index]->value.str;
            std::cin.get();
            break;
        case ';':
            if (datas[index]->type == var::Int)
                std::cin >> datas[index]->value.i;
            else if (datas[index]->type == var::Char)
                std::cin >> datas[index]->value.c;
            else if (datas[index]->type == var::String)
                std::cin.getline(datas[index]->value.str, 1024);
            break;
        case '>':
            if (index + 1 >= datasLength)
                cout << "failed to move" << endl;
            else {
                index++;
                if (datas[index] == NULL)
                    datas[index] = new var;
            }
            break;
        case '<':
            if (index == 0)
                cout << "failed to move" << endl;
            else
                index--;
            break;
        case '(':
            if (datas[index]->value.i) {
                string block = "";
                for (unsigned int j = i + 1; j < cmd.length(); j++)
                    block += cmd[j];
                i += run(block) + 1;
            }
            else {
                unsigned int count = 1;
                for (++i; i < cmd.length() && count; i++)
                    if (cmd[i] == '(') count++;
                    else if (cmd[i] == ')') count--;
                i--;
            }
            break;
        case ')':
            return i;
            break;
        case '[': 
            if (datas[index]->value.i) {
                string block = "";
                int pos = 0;
                for (unsigned int j = i + 1; j - 1 < cmd.length(); j++)
                    block += cmd[j];
                while (datas[index]->value.i) {
                    pos = run(block);
                }
                i += pos + 1;
            }
            else {
                unsigned int count = 1;
                for (++i; i < cmd.length() && count; i++)
                    if (cmd[i] == '[') count++;
                    else if (cmd[i] == ']') count--;
                i--;
            }
            break;
        case ']':
            return i;
            break;
        case '=': {
            var* result = singleParse(cmd, ++i);
            if (datas[index]->type == var::Int) {
                datas[index]->value.i = result->value.i;
                delete result;
            }
            else if (datas[index]->type == var::Char) {
                datas[index]->value.c = result->value.c;
                delete result;
            }
            else
                datas[index] = result;
        }
            break;
        case '#':
            for(i;i < cmd.length() && cmd[i] != '\n';i++);
            break;
        }
    }
}

string script(string path) {
    string result, x;
    ifstream file;
    file.open(path);
    while (!file.eof()) {
        getline(file, x);
        result += x;
        result += '\n';
    }
    return result;
}

var* singleParse(string str,unsigned int& index) {
    var* result = NULL;
    if (isdigit(str[index])) {
        result = new var;
        result->type = var::Int;
        string num;
        for (index; index < str.length() && isdigit(str[index]); index++) {
            num += str[index];
        }
        for (int i = 0; i < num.length(); i++)
            result->value.i = result->value.i * 10 + num[i] - 48;
        index--;
    }
    if (str[index] == '\'') {
        result = new var;
        result->type = var::Char;
        result->value.c = str[++index];
        index++;
    }
    if (str[index] == '"') {
        index++;
        result = new var;
        result->type = var::String;
        result->value.str = new char[1025];
        int i = 0;
        for (index; index < str.length() && str[index] != '"'; index++)
            result->value.str[i++] = str[index];
        result->value.str[i] = '\0';
    }
    return result;
}