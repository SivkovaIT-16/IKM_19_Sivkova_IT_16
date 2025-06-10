#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "Header.h"
using namespace std;
bool Tree::ValKey(string element)//Проверка значения ключа
{
    if (element.empty())
    {
        return false;
    }
    int start = 0;
    if (element[0] == '-')
    {
        start = 1;
        if (element.size() == 1)
        {
            return false;
        }
    }
    for (int i = start; i < element.size(); i++)
    {
        if (!isdigit(element[i]))
        {
            return false;
        }
    }
    return true;
}
bool Tree::ValWay(string element)//Проверка значения пути
{
    if (element.empty())
    {
        return false;
    }
    for (int i = 0; i < element.size(); i++)
    {
        if (element[i] != '0' && element[i] != '1')
        {
            return false;
        }
    }
    return true;
}
Tree::Tree(int x) : key(x), left(nullptr), right(nullptr) {}//Конструктор
void Tree::Reading(multimap<string, int>& values, string filename)//Чтение данных из файла и запись в контейнер multimap
{
    int numLine = 0;
    string line;
    ifstream file(filename, ios::out);
    if (!file)
    {
        throw runtime_error("Файл не был открыт.");
    }
    if (file.peek() == EOF)
    {
        throw runtime_error("Файл пустой. Введите данные в файл и перезапустите программу.");
    }

    while (getline(file, line))
    {
        numLine++;
        istringstream str(line);
        string val, way;
        if (!(str >> val))
        {
            throw runtime_error("Не указано значение узла в строке " + to_string(numLine) + ".");
        }
        if (!(str >> way))
        {
            throw runtime_error("Не указан путь для узла со значением " + val + " в строке " + to_string(numLine) + ".");
        }
        string excess;
        if (str >> excess)
        {
            throw runtime_error("Лишние данные в строке " + to_string(numLine) + ".");

        }
        if (!ValKey(val))
        {
            throw runtime_error("Некорректное значение узла " + val + " в строке " + to_string(numLine) + ".");
        }
        if (!ValWay(way))
        {
            throw runtime_error("Некорректный путь " + way + " в строке " + to_string(numLine) + ".");
        }
        values.insert(pair<string, int>(way, stoi(val)));
    }
    file.close();
}
Tree::PTree Tree::Build(multimap<string, int> values)//Построение дерева
{
    PTree root = new Tree(0);
    try
    {
        for (auto& it : values)
        {
            string way = it.first;
            int key = it.second;
            PTree Node = root;
            for (int i = 0; i < way.size(); i++)
            {
                char direction = way[i];
                if (Node && direction == '0')
                {
                    if (!Node->left && i != way.size() - 1)
                    {
                        throw runtime_error("Пути " + way + " не существует.");
                    }
                    if (i == way.size() - 1)
                    {
                        if (Node->left && Node->left->key != key)
                        {
                            throw runtime_error("Узел, путь которого " + way + " уже содержит значение.");
                        }
                        Node->left = new Tree(key);
                    }
                    else
                    {
                        Node = Node->left;
                    }
                }
                else if (Node && direction == '1')
                {
                    if (!Node->right && i != way.size() - 1)
                    {
                        throw runtime_error("Пути " + way + " не существует.");
                    }
                    if (i == way.size() - 1)
                    {
                        if (Node->right && Node->right->key != key)
                        {
                            throw runtime_error("Узел, путь которого " + way + " уже содержит значение.");
                        }
                        Node->right = new Tree(key);
                    }
                    else
                    {
                        Node = Node->right;
                    }
                }
            }
        }
        return root;
    }
    catch (...)
    {
        Delete(root);
        throw;
    }
}
void Tree::Print(PTree root, int h)//Вывод дерева боком
{
    int i;
    if (root != nullptr)
    {
        Print(root->right, h + 1);
        for (i = 1; i <= h; i++)
        {
            cout << "        ";
        }
        cout << root->key << endl;
        cout << endl;
        Print(root->left, h + 1);
    }
}
void Tree::Delete(PTree root)//Удаление дерева
{
    if (!root)
    {
        return;
    }
    Delete(root->left);
    Delete(root->right);
    delete root;
}
