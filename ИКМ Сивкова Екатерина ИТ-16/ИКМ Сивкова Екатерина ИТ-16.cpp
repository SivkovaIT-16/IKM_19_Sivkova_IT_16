//¬ файле даны n целых чисел, и здесь же указан путь их размещени€ в бинарном
//дереве виде двоичного кода(коды не повтор€ютс€).ѕостроить двоичное
//дерево целых чисел, в котором путь по дереву определ€етс€ указанным
//двоичным кодом в этом листе(1 Ц переход к правому потомку, 0 - переход к
//левому потомку).¬ корень автоматически заноситс€ значение 0.
//”читывать ситуацию,
//когда дерево не может
//быть построено.
#include <iostream>
#include <map>
#include <string>
#include <windows.h>
#include "Header.h"
int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Tree::PTree root = nullptr;
    try 
    {
        string filename = "FileName.txt";
        multimap<string, int> values;
        Tree tree(0);
        tree.Reading(values, filename);
        cout << "ѕрочитанные данные (путь: значение узла): " << endl;
        for (auto it = values.begin(); it != values.end(); it++)
        {
            cout << (*it).first << ": " << (*it).second << endl;
        }
        root = tree.Build(values);
        cout << "ѕостроенное дерево:" << endl;
        tree.Print(root, 0);
    }
    catch (const exception& e)
    {
        cout << "ќшибка: " << e.what() << endl;
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

