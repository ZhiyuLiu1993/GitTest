#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <queue>

using namespace std;

//编辑距离加权，纠错字
const int maxn = 1024 ;
int dist[32][32] ;
int dp[maxn][maxn] ;
int delCost = 3;
int insertCost = 3;
char dict[2][15] = {"qwertasdfgzxcv","yuiophjklbnm**"};

typedef struct Score_{
    string str;
    int sco;
}Score;

class Cmp{
public:      //公有函数
    bool operator()(Score &a, Score &b){   //注意operator后的括号
        return a.sco <= b.sco;   //<最大值优先 >最大值优先
    }
};

void calcWeidht()
{
    int i , j , x , y ;
    for( i = 0 ; i < 2 ; i++)
    {
        for ( j = 0 ; j < 14 ; j++)
        {
            if ( dict[i][j] == '*' )
            {
                break ;
            }
            for ( x = 0 ; x < 2 ; x++)
            {
                for ( y = 0 ; y < 14 ; y++)
                    if( dict[x][y] != '*' )
                    {
                        if(dict[i][j] == dict[x][y])
                            dist[dict[i][j]-'a'][dict[x][y]-'a'] = 0;
                        else if(i == x)
                            dist[dict[i][j]-'a'][dict[x][y]-'a'] = 1;
                        else
                            dist[dict[i][j]-'a'][dict[x][y]-'a'] = 2;
                    }
            }
        }
    }
}

inline int get_min(int a,int b)	{	return a < b ? a : b ;	}

int calcEditDist(string A, string B)
{
    int lenA = A.size();
    int lenB = B.size();
    int i , j ;

    for( i = 1 ; i <= lenA ; i++)
    {
        dp[i][0] = i * insertCost ;
    }
    for ( j = 1 ; j <= lenB ; j++)
    {
        dp[0][j] = j * insertCost ;
    }

    for ( i = 1 ; i <= lenA ; i++)
    {
        for ( j = 1 ; j <= lenB ; j++)
        {
            int changeCost = (A[i-1]==B[j-1]?0:dist[tolower(A[i-1])-'a'][tolower(B[j-1])-'a']) ;
            dp[i][j] = get_min(dp[i-1][j]+delCost,get_min(dp[i][j-1]+delCost,dp[i-1][j-1]+changeCost));
        }
    }

    return dp[lenA][lenB];
}

int main() {
    calcWeidht();

    string line;

    vector<string> str;
    string target;

    string temp;

    while (getline(cin, line)) {
        stringstream lss(line);
        lss >> target;
        while(lss >> temp)
            str.push_back(temp);
        priority_queue<Score, vector<Score>, Cmp> score;
        for (int i = 0; i < str.size(); ++i) {
            Score cur;
            cur.sco = calcEditDist(target, str[i]);
            cur.str = str[i];
            score.push(cur);
            if(i >= 3){
                score.pop();
            }
        }
        while(!score.empty()){
            cout << score.top().str << endl;
            score.pop();
        }

    }

    return 0;

}

