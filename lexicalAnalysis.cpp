#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

bool operatorCheck(char ch)
{
    if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '>' || ch == '<' || ch == '=' || ch == '%')
    {
        return true;
    }

    return false;
}

bool delimiterCheck(char ch)
{
    if (ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}')
    {
        return true;
    }
    return false;
}

bool keyworkCheck(list<char> check)
{
    list<string> keywords = {"auto", "double", "int", "struct", "break", "else", "long", "endif", "printf", "main",
                             "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union",
                             "const", "short", "float", "unsigned", "continue", "for", "signed", "void", "default",
                             "goto", "sizeof", "volatile", "do", "if", "static", "while", "print", "then"};

    string toCheck(check.begin(), check.end());
    if (find(keywords.begin(), keywords.end(), toCheck) != keywords.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    fstream file;
    file.open("program.txt", ios::in);
    if (!file)
    {
        cout << "File doesn't exist\n";
    }

    list<char> bufferList;
    list<char> operatorList;
    list<char> delimiterList;
    list<char> comments;
    list<string> keywordList;
    list<string> numberList;
    list<string> variableList;

    char ch;
    while (file >> noskipws >> ch && ch != '$')
    {
        if (ch == '/' && file.peek() == '*')
        {
            while (true)
            {
                comments.push_back(ch);
                file >> noskipws >> ch;
                if (ch == '*' && file.peek() == '/')
                {
                    break;
                }
            }
        }
        bufferList.push_back(ch);
        if (isspace(ch) || operatorCheck(ch) || delimiterCheck(ch))
        {
            if (operatorCheck(ch) && find(operatorList.begin(), operatorList.end(), ch) == operatorList.end())
            {
                operatorList.push_back(ch);
            }
            else if (delimiterCheck(ch) && find(delimiterList.begin(), delimiterList.end(), ch) == delimiterList.end())
            {
                delimiterList.push_back(ch);
            }

            bufferList.pop_back();
            string foundKeyword(bufferList.begin(), bufferList.end());
            bool is_number = true;
            for (char c : foundKeyword)
            {
                if (!isdigit(c))
                {
                    is_number = false;
                    break;
                }
            }
            if (keyworkCheck(bufferList))
            {
                if (find(keywordList.begin(), keywordList.end(), foundKeyword) == keywordList.end())
                {
                    keywordList.push_back(foundKeyword);
                }
                bufferList.clear();
            }
            else if (is_number)
            {
                if (find(numberList.begin(), numberList.end(), foundKeyword) == numberList.end())
                {
                    numberList.push_back(foundKeyword);
                }
                bufferList.clear();
            }
            else
            {
                if (find(variableList.begin(), variableList.end(), foundKeyword) == variableList.end())
                {
                    variableList.push_back(foundKeyword);
                }
                bufferList.clear();
            }
        }
    }

    cout << "\nKeywords list:\n ";
    for (auto it = keywordList.begin(); it != keywordList.end(); it++)
    {
        cout << *it << " ";
    }
    cout << "\nNumbers list:\n ";
    for (auto it = numberList.begin(); it != numberList.end(); it++)
    {
        cout << *it << " ";
    }
    cout << "\nVariables list:\n ";
    for (auto it = variableList.begin(); it != variableList.end(); it++)
    {
        cout << *it << " ";
    }
    cout << "\nOperators list:\n ";
    for (auto it = operatorList.begin(); it != operatorList.end(); it++)
    {
        cout << *it;
    }
    cout << "\nDelimiters list:\n ";
    for (auto it = delimiterList.begin(); it != delimiterList.end(); it++)
    {
        cout << *it;
    }
    cout << "\nComments list:\n ";
    for (auto it = comments.begin(); it != comments.end(); it++)
    {
        cout << *it;
    }

    file.close();
    cout << "\nend\n";
    return 0;
}
