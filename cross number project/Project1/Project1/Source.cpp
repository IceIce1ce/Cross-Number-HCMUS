#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;

int *computeLsp(string pat)
{
    int* lsp = new int[pat.size()];
    lsp[0] = 0;
    int j = 0;
    for(int i = 1; i < pat.size(); i++)
    {
        while(j > 0 && pat[j] != pat[i]) j = lsp[j - 1];
        if(pat[j] == pat[i]) j++;
        lsp[i] = j;
    }
    return lsp;
}

int kmp(string txt, string pat)
{
    int *lsp = computeLsp(pat);
    int j = 0;
    for(int i = 0; i < txt.length(); i++)
    {
        while(j > 0 && pat[j] != txt[i]) j = lsp[j - 1];
        if(pat[j] == txt[i]) j++;
        if(j == pat.length())
        {
            //cout << "Pattern found at index: " << i - (pat.length() - 1);
            //j = lsp[j - 1];
            return i - (j - 1);
        }
    }
	delete[] lsp;
    return -1;
}

void CreateMatrix(char **arr, int row, int column, char x)
{
	arr = new char*[row];
	for (int i = 0; i < row; i++)
	{
		arr[i] = new char[column];
		for (int j = 0; j < column; j++)
		{
			arr[i][j] = x; 
		}
	}
}

vector<string> List_UPDOWN(char **arr, int row, int column)
{
	vector<string> list_updown;
	for (int i = 1; i <= column; i++)
	{
		string temp = "";
		for (int j = 1; j <= row; j++)
		{
			temp += arr[j][i];
		}
		list_updown.push_back(temp);
	}
	return list_updown;
}

vector<string> List_LEFTRIGHT(char **arr, int row, int column)
{
	vector<string> list_leftright;
	for (int i = 1; i <= row; i++)
	{
		string temp = "";
		for (int j = 1; j <= column; j++)
		{
			temp += arr[i][j];
		}
		list_leftright.push_back(temp);
	}
	return list_leftright;
}

string Check(vector<string> arr_updown, vector<string> arr_leftright, string pat)
{
	stringstream writer;
	int value1 = -1, value2 = -1;
	for (int i = 0; i < arr_updown.size(); i++)
	{
		value1 = kmp(arr_updown[i], pat);
		if (value1 != -1)
		{
			writer << pat << " " << "(" << value1 + 1 << "," << i + 1 << ")" << " " << "TD";
			break;
		}
	}
	for(int i = 0; i < arr_leftright.size(); i++)
	{
		value2 = kmp(arr_leftright[i], pat);
		if (value2 != -1)
		{
			writer<< pat << " " << "(" << i+1 << "," << value2 + 1 << ")" << " " << "LR";
			break;
		}
	}
	if (value1 == -1 && value2 == -1)
	{
		writer << pat << " " << "(" << 0 << "," << 0 << ")" << " " << "NF";
	}
	return writer.str();
}

void ReadFile(string read, string write)
{
	ifstream fin;
	ofstream fout;
	fin.open(read);
	fout.open(write);
	if (!fin.is_open() || !fout.is_open()) return;
	char temp;
	int H_height, W_weight;
	char** arr;
	for (int i = 0; i < 1; i++)
	{
		fin >> H_height;
		cout << H_height << endl;
		fin >> W_weight;
		cout << W_weight << endl;
	}
	arr = new char* [H_height];
	for (int i = 1; i <= H_height; i++)
	{
		arr[i] = new char[W_weight];
		for (int j = 1; j <= W_weight; j++)
		{
			fin >> temp;
			if (temp != ' ') arr[i][j] = temp;
		}
	}
	vector<string> updown = List_UPDOWN(arr, H_height, W_weight);
	vector<string> leftright = List_LEFTRIGHT(arr, H_height, W_weight);
	string data;
	string result;
	for (int i = H_height + 2; ; i++)
	{
		fin >> data;
		if (data == "#") break;
		cout << data << endl;
		result = Check(updown, leftright, data);
		fout << result << endl;
	}
	fin.close();
	fout.close();
}

int main()
{
    /*string text = "UCMARVELOLE"; 
    string pattern = "MARVEL"; 
    int result = kmp(text, pattern);
    if(kmp(text, pattern) != -1) cout << "Pattern found at index: " << result;
    else cout << "Not found";*/
	ReadFile("input.txt", "output.txt");
    return 0;
}