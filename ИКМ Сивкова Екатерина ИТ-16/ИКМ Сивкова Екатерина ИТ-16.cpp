//В файле даны n целых чисел, и здесь же указан путь их размещения в бинарном
//дереве виде двоичного кода(коды не повторяются).Построить двоичное
//дерево целых чисел, в котором путь по дереву определяется указанным
//двоичным кодом в этом листе(1 – переход к правому потомку, 0 - переход к
//левому потомку).В корень автоматически заносится значение 0.
//Учитывать ситуацию,
//когда дерево не может
//быть построено.
#include <iostream>
#include <map>
#include <string>
#include "Header.h"
int main()
{
    setlocale(LC_ALL, "Russian");
    Tree::PTree root = nullptr;
    try 
    {
        string filename = "FileName.txt";
        multimap<string, int> values;
        Tree tree(0);
        tree.Reading(values, filename);
        cout << "Прочитанные данные (путь: значение узла): " << endl;
        for (auto it = values.begin(); it != values.end(); it++)
        {
            cout << (*it).first << ": " << (*it).second << endl;
        }
        root = tree.Build(values);
        cout << "Построенное дерево:" << endl;
        tree.Print(root, 0);
    }
    catch (const exception& e)
    {
        cout << "Ошибка: " << e.what() << endl;
        if (root) 
        {
            Tree node(0);
            node.Delete(root);
        }
        return 1;
    }
    if (root) 
    {
        Tree node(0);
        node.Delete(root);
    }
    return 0;
}

