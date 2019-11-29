#include <iostream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

int const inf = numeric_limits<int>::max();

int main(){
	
	vector<vector<int > > map(6, vector<int> (6,inf));
	vector<vector<char > > v(6, vector<char> (6,0));
	
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			
			cin >>	v[i][j];
				
		}
	}
	
	typedef pair<int, pair <int,int> > p;
	
	int ix[]={ -1, 0, 1, -1,1,-1,0,1};
	int wai[]={1,1,1,0,0,0,-1,-1,-1};
	
	
	vector<vector<bool> > visited(6, vector<bool>(6,false));
	
	priority_queue< p, vector<p>, greater<p> > q;
	
	q.push(make_pair(0,make_pair(0,5))); //primer tesoro
	
	map[0][5]=0; //tesoro igual 0	
	
	while(not q.empty()){
		
		p now = q.top();
		q.pop();
		int xnow=now.second.first;
		int ynow=now.second.second;
		
		if(!visited[xnow][ynow]){
			
			
			visited[xnow][ynow] =true;
			
			for(int i=0; i< 8; i++){
				
				//adj;
				if(xnow + ix[i]>=0 and xnow + ix[i]<6 and ynow + wai[i]>=0 and ynow + wai[i]<6){
					//if pos okey
					
					int xaux=xnow+ix[i];
					int yaux=ynow+wai[i];
					int cost;
					if(v[xaux][yaux]=='R') cost=map[xnow][ynow]+5;
					else if(v[xaux][yaux]=='T') cost=0;
					else cost=map[xnow][ynow]+1;
					
					if(map[xaux][yaux] > cost){
						
						map[xaux][yaux] = cost;
						
						q.push(make_pair(cost,make_pair(xaux,yaux) ));
					
					
					} 
				
				}
			}
			
		}
		
		
		
		
	}
	
	
	
	
	//print map
	
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			
			cout <<	map[i][j] << " ";
				
		}
		cout << endl;
	}
	
	
	
	
}
