// Realisation of 'water levels' problem via priority_queue
//(C) lorem.ipsum.989

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;
void Push(int *arr,priority_queue<pair<int, int>,vector<pair<int, int>>> &stack,vector<bool> &V,int idx){
    if(V[idx]) return;
    V[idx]=true;
    stack.push(pair<int, int>(idx,arr[idx])); //Pushing index (N*i+i) and height at this index
}
int Area(int *arr,int M,int N){
	int i;
    if(N<3 || M<3) return 0;			//if less than 3x3, obviously doesn't contain any water
    vector<bool> enabled(M*N,false);	//auxiliary array to prevent pushing duplicates
    priority_queue<pair<int, int>,vector<pair<int, int>>> stack; //our queue itself
    for(i=0;i<M;i++){							//=================
        Push(arr,stack,enabled,i*N);			//Pushing M's
        Push(arr,stack,enabled,i*N+N-1);		//=================
    }
    for(i=1;i<N-1;i++){							//================
        Push(arr,stack,enabled,i);				//Pushing N's
        Push(arr,stack,enabled,N*(M-1)+i);		//================
    }
    int smin=INT_MIN; 
    int res=0;
    while(!stack.empty()){						// While stack still contains elements,
        pair<int, int> P=stack.top();			// Duplicate uppermost element
        stack.pop();							// And pop it out
        int idx=P.first;						// Index to idx
        if(P.second>smin) smin=P.second;		// If height exceeds previous one, height to smin
        else res+=smin-P.second;				// else add diff to result
        int x=idx%N,y=idx/N;					// idx%N is first coord (j from main()), idx/N is second coord (i from main())  
        if(x>0) Push(arr,stack,enabled,idx-1);	// Passing idx-1 to next iteration while we don't meet left border
        if(x<N-1) Push(arr,stack,enabled,idx+1);// Same for right border
        if(y>0) Push(arr,stack,enabled,idx-N);	// Same for y...
        if(y<M-1) Push(arr,stack,enabled,idx+N);
    }
    return res;
}
int main(int argc, _TCHAR* argv[])
{
	int N,M;
	scanf_s("%d %d", &N, &M);
	int* matrix=new int[M*N];
	for(int i=0; i<N; i++)
		for(int j=0;j<M;j++)
			scanf_s("%d", &matrix[N*i+j]);
	printf_s("%d\n", Area(matrix, N, M));
	system("PAUSE");
	return 0;
}

