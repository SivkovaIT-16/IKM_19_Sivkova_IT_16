#include <iostream>
#include <map>
#include <string>
using namespace std;
class Tree
{
private:
    int key;
    Tree* left;
    Tree* right;
    bool ValKey(string element);//Проверка значения ключа
    bool ValWay(string element);//Проверка значения пути
public:
    typedef Tree* PTree;
    Tree(int x);//Конструктор 
    void Reading(multimap<string, int>& values, string filename);//Чтение данных из файла и запись в контейнер multimap
    PTree Build(multimap<string, int> values);//Построение дерева
    void Print(PTree root, int h);//Вывод дерева боком
    void Delete(PTree root);//Удаление дерева
};
