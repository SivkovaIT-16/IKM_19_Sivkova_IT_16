#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "Header.h"
using namespace std;
bool Tree::ValKey(string element)//�������� �������� �����
{
    if (element.empty())
    {
        return false;
    }
    int start = 0;
    if (element[0] == '0')
    {
        return false;
    }
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
bool Tree::ValWay(string element)//�������� �������� ����
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
Tree::Tree(int x) : key(x), left(nullptr), right(nullptr) {}//�����������
void Tree::Reading(multimap<string, int>& values, string filename)//������ ������ �� ����� � ������ � ��������� multimap
{
    int numLine = 0;
    string line;
    ifstream file(filename, ios::out);
    if (!file)
    {
        throw runtime_error("���� �� ��� ������.");
    }
    if (file.peek() == EOF)
    {
        throw runtime_error("���� ������. ������� ������ � ���� � ������������� ���������.");
    }

    while (getline(file, line))
    {
        numLine++;
        istringstream str(line);
        string val, way;
        if (!(str >> val))
        {
            throw runtime_error("�� ������� �������� ���� � ������ " + to_string(numLine) + ".");
        }
        if (!(str >> way))
        {
            throw runtime_error("�� ������ ���� ��� ���� �� ��������� " + val + " � ������ " + to_string(numLine) + ".");
        }
        string excess;
        if (str >> excess)
        {
            throw runtime_error("������ ������ � ������ " + to_string(numLine) + ".");

        }
        if (!ValKey(val))
        {
            throw runtime_error("������������ �������� ���� " + val + " � ������ " + to_string(numLine) + ".");
        }
        if (!ValWay(way))
        {
            throw runtime_error("������������ ���� " + way + " � ������ " + to_string(numLine) + ".");
        }
        values.insert(pair<string, int>(way, stoi(val)));
    }
    file.close();
}
Tree::PTree Tree::Build(multimap<string, int> values)//���������� ������
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
                        throw runtime_error("���� " + way + " �� ����������.");
                    }
                    if (i == way.size() - 1)
                    {
                        if (Node->left && Node->left->key != key)
                        {
                            throw runtime_error("����, ���� �������� " + way + " ��� �������� ��������.");
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
                        throw runtime_error("���� " + way + " �� ����������.");
                    }
                    if (i == way.size() - 1)
                    {
                        if (Node->right && Node->right->key != key)
                        {
                            throw runtime_error("����, ���� �������� " + way + " ��� �������� ��������.");
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
void Tree::Print(PTree root, int h)//����� ������ �����
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
void Tree::Delete(PTree root)//�������� ������
{
    if (!root)
    {
        return;
    }
    Delete(root->left);
    Delete(root->right);
    delete root;
}
