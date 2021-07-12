#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define SIZE 301
using namespace std;

class LCS
{
public:
    int DP[SIZE][SIZE];
    int num;
    string a, b;
    string str[SIZE];
    LCS(string x,string y)//�غc�l
    {
        a = x;
        b = y;
        num = 0;
        memset(DP, 0, sizeof(DP));
        memset(str, 0, sizeof(str));
    }
    //�Q��DP�����r���諸���G�A�ѨMLCS���D
    void setDP()
    {
        int i, j;
        for(i = 0; i <= a.size(); i++)
            DP[i][0] = 0;
        for(j = 0; j <= b.size(); j++)
            DP[0][j] = 0;
        for(i = 1; i <= a.size(); i++)
        {
            for(j = 1; j <= b.size(); j++)
            {
                if(a[i-1] == b[j-1])
                    DP[i][j] = DP[i-1][j-1] + 1;
                else
                    DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
            }
        }
    }
    //���j�禡�A�N�ŦX�����|�s�Jstr
    void Track(string str[SIZE], string tmp, int i, int j)
    {
        while(DP[i][j] > 0)
        {
            //�ŦX���|
            if(a[i-1] == b[j-1])
            {
                i--;
                j--;
                tmp += a[i];
            }
            else
            {
                if(DP[i][j-1]>DP[i-1][j])//�����j�M
                {
                    j--;
                }
                else if(DP[i][j-1]<DP[i-1][j])//���W�j�M
                {
                    i--;
                }
                else//�Y���䳣�i�H�h�^�X�{�Ƽƪ����|�A�Q�λ��j�l��
                {
                    Track(str, tmp, i, j-1);
                    Track(str, tmp, i-1, j);
                    return;
                }
            }
        }
        int flag = 0;
        //tmp���������X�����|���r��A�P�C�ӥ��e���r����
        for(int k=0; k<num; k++)
        {
            if(tmp == str[k])
                flag = 1;
        }
        //�Y�S�����ƫh�[�J�}�C
        if(flag == 0)
        {
            str[num] = tmp;
            num++;
        }
    }
};
int main()
{
    int i;
    string x, y;
    while(cin>>x>>y)
    {
        string temp;
        LCS DNA(x, y);
        DNA.setDP();
        if(DNA.DP[DNA.a.size()][DNA.b.size()] == 0)
            cout<<"No common sequence."<<endl;
        else
        {
            DNA.Track(DNA.str, temp, DNA.a.size(), DNA.b.size());
            for(i=0; i < DNA.num; i++)//����r��
            {
                reverse(DNA.str[i].begin(),DNA.str[i].end());
            }
            sort(DNA.str, DNA.str + DNA.num);//�ƧǦr��
            for(i=0; i < DNA.num; i++)
            {
                cout<<DNA.str[i]<<endl;
            }
        }
        cout<<endl;
    }
}
