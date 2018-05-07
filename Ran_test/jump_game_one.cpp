#include <iostream>
#include <algorithm>

class Solution{
	public:
		bool canJump(int A[], int n){
			int maxPosition = 0;
			for(int i = 0; i < n && i <= maxPosition; ++i){
				maxPosition = max(maxPosition, A[i] + i);
				if(maxPosition >= n-1)
					return true;
			}
			return false;
		}
};

int main(){
	Solution a;
	int A[] = {2, 0, 0};

	cout<<a.canJump(A, 3)<<endl;

	return 0;
}

