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
    bool ValKey(string element);//�������� �������� �����
    bool ValWay(string element);//�������� �������� ����
public:
    typedef Tree* PTree;
    Tree(int x);//����������� 
    void Reading(multimap<string, int>& values, string filename);//������ ������ �� ����� � ������ � ��������� multimap
    PTree Build(multimap<string, int> values);//���������� ������
    void Print(PTree root, int h);//����� ������ �����
    void Delete(PTree root);//�������� ������
};
