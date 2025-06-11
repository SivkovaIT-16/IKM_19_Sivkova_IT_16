//� ����� ���� n ����� �����, � ����� �� ������ ���� �� ���������� � ��������
//������ ���� ��������� ����(���� �� �����������).��������� ��������
//������ ����� �����, � ������� ���� �� ������ ������������ ���������
//�������� ����� � ���� �����(1 � ������� � ������� �������, 0 - ������� �
//������ �������).� ������ ������������� ��������� �������� 0.
//��������� ��������,
//����� ������ �� �����
//���� ���������.
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
        cout << "����������� ������ (����: �������� ����): " << endl;
        for (auto it = values.begin(); it != values.end(); it++)
        {
            cout << (*it).first << ": " << (*it).second << endl;
        }
        root = tree.Build(values);
        cout << "����������� ������:" << endl;
        tree.Print(root, 0);
    }
    catch (const exception& e)
    {
        cout << "������: " << e.what() << endl;
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

