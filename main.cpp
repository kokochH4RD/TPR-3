#include <iostream>
#include <fstream>
#include <vector>
#define CONTAINER_LIMIT 100
#define WEIGHT_COUNT 15

using namespace std;
class Weight {
	public:
		int weight;
		int index;
};


class Container
{
public:
	int weight = 0;
	vector<int> indexs;
	bool addItem(Weight item);
	static int count;
	int index;
	Container();

	
	
};
int Container::count = 1;
Container::Container()
{
	index = count;
	count++;
	
};

int findMax(vector<Container> containers) {
	int minimum = INT_MAX;
	int index = 0;
	for (size_t i = 0; i < containers.size(); i++)
	{
		if (containers[i].weight < minimum)
		{
			minimum = containers[i].weight;
			index = i;
		}
	}
	return index;

}

void NFA(Weight *weights, vector<Container> &containers) {
	for (size_t i = 0; i < WEIGHT_COUNT;)
	{
		if (containers.back().addItem(weights[i]))
		{
			i++;
		}
		else
		{
			
			containers.push_back(Container());
			containers.back().addItem(weights[i]);
			i++;

		}

	}
	for (size_t i = 0; i < containers.size(); i++)
	{
		cout << "Container " << i+1 << " :  ";
		for (size_t j = 0; j < containers[i].indexs.size(); j++)
		{
			cout<<containers[i].indexs[j] << "  ";
		}
		cout << endl;
	}


	/*for (size_t i = 0; i < containers.size(); i++)
	{
		for (size_t j = 0; j < containers[i].indexs.size(); j++)
		{
			cout << containers[i].indexs[j] << "  ";
		}
	}cout << endl;*/


}


/* i �������� �� �������
   j �������� �� �����������
*/
void FFA(Weight *weights, vector<Container> &containers) {
	for (size_t i = 0; i < WEIGHT_COUNT;)
	{
		if (containers.back().addItem(weights[i]))	i++;		//���� � ���� � ��������� ��������� ������ �� ���������� �� ������
		else
		{
			bool created = false;									//���� �� ������ �� ������ ��������� �� � ������ �������� � ����������
			bool flag = false;										//���� �� ������ �� ������ ����� �� ��� �������� ����������
			int j = 0;
			while ( j < containers.size() - 1)						//���������� �� ������� �����, � ����, ��� �������� ����������
			{

				if (flag == false) {
				
						if(!containers.back().addItem(weights[i]));		//����� ���� ������ ���� �� ����� �������� � �������� ��� if ������ ��������� � ����������
						flag = containers[j].addItem(weights[i]);
				}			
				j++;													//������� �� ������ ���������� ��� ���������
			}
			if (flag) {													
				i++;													//������� �� ������ ������
			}
			else
			{
				containers.push_back(Container());						//��������� ���������� �� ��������� ������
				containers.back().addItem(weights[i]);
				created = true;										    //��������� �� �������� ������ ��������� �� � ������ ����� ��� ������ � ����������
				i++;
			}
			
		}

	}
	for (size_t i = 0; i < containers.size(); i++)
	{
		cout << "Container " << i + 1 << " :  ";
		for (size_t j = 0; j < containers[i].indexs.size(); j++)
		{
			cout << containers[i].indexs[j] << "  ";
		}
		cout << endl;
	}

}


void WFA(Weight *weights, vector<Container> &containers) {
	bool created = true;
	for (size_t i = 0; i < WEIGHT_COUNT;)
	{
		if (containers.back().addItem(weights[i]))	i++;		
		else
		{
			if ( containers[findMax(containers)].addItem(weights[i])) i++;
			else {

				containers.push_back(Container());						
				containers.back().addItem(weights[i]);
				created = false;									
				i++;
			}
		}
	}
}

int main() {
	ifstream inputFileStream("inputs.txt");

	Weight* weights = new Weight[WEIGHT_COUNT];
	int i = 0;
	while (!inputFileStream.eof())
	{
		
		inputFileStream >> weights[i].weight;
		weights[i].index = i+1;
		i++;
	}
	for (size_t i = 0; i < WEIGHT_COUNT; i++)
	{
		cout << weights[i].weight << "  " << weights[i].index << endl;
	}
	
	vector<Container> containers;
	containers.resize(1);
	
	FFA(weights, containers);
	//WFA(weights, containers);
	system("pause");
}

bool Container::addItem(Weight item)
{
	if(weight + item.weight >CONTAINER_LIMIT)
		{
			return false;
		}	
	else {
		weight += item.weight;
		indexs.push_back(item.index);
		return true;
	}
}


