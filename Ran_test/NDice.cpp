#include <iostream>
#include <cmath>


using namespace std;

int g_MaxValue = 6;

class Solution{
	public:
		void  PrintProbablity(int number){
			if(number < 1)
				return;

			int *pProbabilities[2];
			pProbabilities[0] = new int [g_MaxValue * number + 1]; 
			pProbabilities[1] = new int [g_MaxValue * number + 1]; 

			for(int i = 0; i < g_MaxValue * number + 1; ++i){
				pProbabilities[0][i] = 0;
				pProbabilities[1][i] = 0;
			}

			int flag = 0;
			
			for(int i = 1; i <= g_MaxValue; i++){
				pProbabilities[flag][i] = 1;
			}

			for(int k = 2; k <= number; ++k){
				for(int i = 0; i < k; ++i)
					pProbabilities[1-flag][i] = 0;

				for(int i = k; i <= g_MaxValue*k; ++i){
					pProbabilities[1-flag][i] = 0; 
					for(int j = 1; j < i && j <= g_MaxValue; ++j){
						pProbabilities[1-flag][i] += pProbabilities[flag][i-j];

					}
				}
				flag = 1 - flag;
			}

			double total = pow((double)g_MaxValue, number);
			for(int i = number; i <= g_MaxValue*number;++i){
				double ratio = (double)pProbabilities[flag][i] / total;
				cout<<i<<":"<<ratio<<endl;
			}

			delete []pProbabilities[0];
			delete []pProbabilities[1];
		}
};

int main(){
	Solution a;
	a.PrintProbablity(3);

	return 0;
}

