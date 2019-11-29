#include "Player.hh"
#include <limits>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME ShimaSama


// DISCLAIMER: The following Demo player is *not* meant to do anything
// sensible. It is provided just to illustrate how to use the API.
// Please use AINull.cc as a template for your player.


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

  typedef vector<int> VI;

  map<int, int> kind; // For wizards: 0 -> random, 1 -> cyclic.

 

 void lados_dwarf(int x, int y, int id, bool& yes){
	
	yes=false;
 	
 	int wai[]={1,1,1,0,0,-1,-1,-1};
 	int ix[]={-1,0,1,-1,1,-1,0,1};
 	
 	
 	for(int i=0; i<8; i++){ //para ver lo de los lados

		if(pos_ok((x+ix[i]),(y+wai[i]))){ //si esa posicion es buena
			
			Cell c= cell(x+ix[i],y+wai[i]);

			bool attack=false;
			
			if(c.id!=-1 and c.owner!=me()){ //malo
				
				Unit u = unit(c.id);
				Unit tina= unit(id);
				if(u.health < tina.health) attack=true; //mirar si no es troll..

			}

			if(c.treasure or attack ){
				
				yes=true;
				if(i==0) command(id,TL);
				else if(i==1) command(id,Top);
				else if(i==2) command(id, RT);
				else if(i==3) command(id, Left);
				else if(i==4) command(id, Right);
				else if(i==5) command(id,LB);
				else if(i==6) command(id,Bottom);
				else if(i==7) command(id,LB);
				return;
			}

	//		if(c.id!=-1 and c.owner!=me()){ //todos los malos, si hay malos al lado
			
				//ahora no lo hago	
	//		}
		}
	}
 	

 }

 void coinzz(vector<vector<int > >& coinz){

	typedef pair<int, pair <int,int> > p;
	
	int ix[]={ -1, 0, 1, -1,1,-1,0,1};
	int wai[]={1,1,1,0,0,-1,-1,-1};	
	int const inf = numeric_limits<int>::max();

	//buscar un tesoro
	bool found=false;
	int ti;
	int na;
	for (ti=0; ti<60 and not found; ti++){
		for(int na=0; na<60 and not found; na++){

			if(pos_ok(ti,na)){Cell c= cell(ti,na);
				if (c.treasure==true)  found = true;
			
			}
		}
	}

	vector<vector<bool> > visited(60, vector<bool>(60,false));

	priority_queue< p, vector<p>, greater<p> > q;

	q.push(make_pair(0,make_pair(ti,na))); //primer tesoro

	coinz[ti][na]=0; //tesoro igual 0

	while(not q.empty()){

		p now = q.top();
		q.pop();
		int xnow=now.second.first;
		int ynow=now.second.second;

		if(!visited[xnow][ynow]){


			visited[xnow][ynow] =true;

			for(int i=0; i< 8; i++){

				//adj;
				if(pos_ok(xnow+ix[i], ynow+wai[i])){
					//if pos okey

					int xaux=xnow+ix[i];
					int yaux=ynow+wai[i];
					int cost;
					Cell c =cell (xaux, yaux);
					//CellType = c.type;
					if(c.type==Rock) cost=coinz[xnow][ynow]+c.turns;
					else if(c.type==Abyss) cost=inf;
					else if(c.type==Granite) cost=inf;
					else cost=coinz[xnow][ynow]+1;

					if(coinz[xaux][yaux] > cost){

						coinz[xaux][yaux] = cost;

						q.push(make_pair(cost,make_pair(xaux,yaux) ));


					}

				}
			}

		}


}

 }

void forthecoinz(vector<vector< int > >& coinz,int x, int y, int id){

	int ix[]={0,1,1,1,0,-1,-1,-1};
	int wai[]={-1,-1,0,1,1,1,0,-1};
	
	int const inf = numeric_limits<int>::max();

	int min=inf;
	int i;
	//int ygo=0;
	for ( i=0; i<8; i++){

			
		if(pos_ok(x+ix[i], y+wai[i])){
			if(coinz[x+ix[i]][y+wai[i]] < min){

				min= coinz[x+ix[i]][y+wai[i]];
			
			
			}
		}

		
	}
	if(i==0) command(id, Bottom);
	else if(i==1) command(id, BR);
	else if(i==2) command(id, Right);
	else if(i==3) command(id, RT);
	else if(i==4) command(id, Top);
	else if(i==5) command(id, TL);
	else if(i==6) command(id, Left);
	else if(i==7) command(id, LB);


}





  void move_dwarves() {

	int const inf = numeric_limits<int>::max();
	
	vector<vector<int> > coinz(60,vector<int>(60,inf));
	coinzz(coinz);

    
  	vector<int> D = dwarves(me());
  	for (int id : D) {
	
        Pos p = unit(id).pos;
	
		int x= p.i; //pos del dwarf
		int y=p.j;
		bool yes=false;
		lados_dwarf(x,y,id,yes);

		if(not yes) {
		
			forthecoinz(coinz,x,y,id);
		
		
		}
		
	}
  }

 void persecucion(int x, int y, int x2, int y2,bool& yes, vector<vector<pair<int,int> > >& rec ){
	
	queue<pair<pair<int,int>,int> > q; 
	q.push(make_pair(make_pair(x,y),0));
	vector<vector<bool> > visited(64, vector<bool>(64,false)); 
	while(!q.empty() ){

		int ix[]={1,-1,0,0};
		int wai[]={0,0,1,-1};

		int xa=q.front().first.first; 
		int ya=q.front().first.second;
		int dista=q.front().second;

		q.pop();
		visited[xa][ya]=true;

		for(int i=0; i<4; i++){


			int x3=xa+ix[i];
			int y3=ya+wai[i];

			if(pos_ok(x3,y3)){

				if(x3==x2 and y3==y2){
					rec[x3][y3]=make_pair(xa,ya);
			       		yes=true;
					return;
				}	//done
				else if(visited[x3][y3]==false){

					visited[x3][y3]=true;
					int dist=dista+1;
					rec[x3][y3]=make_pair(xa,ya);
					q.push(make_pair(make_pair(x3,y3),dist));

				}

			}
		}
	}
	
	yes=false;
	


 }
 
 void lados_mago(int x, int y, bool& yes, int id){

 	
 	yes=false;
 	
 	int wai[]={1,1,1,0,0,-1,-1,-1};
 	int ix[]={-1,0,1,-1,1,-1,0,1};
 	
 	//mirar tesoros
 	for(int i=0; i<8; i++){ //para ver lo de los lados

		if(pos_ok((x+ix[i]),(y+wai[i]))){ //si esa posicion es buena
			
			Cell c= cell(x+ix[i],y+wai[i]);

			if(c.id!=-1 and c.owner!=me()){ //todos los malos, si hay malos al lado
				
				yes=true;
				if(ix[i]==1 ){
					if(pos_ok(x-1,y))command(id, Left);
					else if(wai[i]==-1 and pos_ok(x,y+1)) command(id, Top);
					else if(pos_ok(x,y-1)) command(id, Bottom);
					else command(id, Dir(2*random(0, 3))); 
				}
				else if(ix[i]==-1){
			       		if(pos_ok(x+1,y)) command(id,Right);
					else if(wai[i]==-1 and pos_ok(x,y+1)) command(id, Top);
					else if(pos_ok(x,y-1)) command(id, Bottom);
					else command(id, Dir(2*random(0, 3))); 
				}
				else if(wai[i]==1){
			       		if(pos_ok(x,y-1))command(id, Bottom);
					else if(ix[i]==-1 and pos_ok(x+1,y)) command(id,Right);
					else if(pos_ok(x-1,y)) command(id,Left);
					else command(id, Dir(2*random(0, 3))); 
				}
				else if(wai[i]==-1){
				 	if(pos_ok(x,y+1))  command(id, Top);
					else if(ix[i]==-1 and pos_ok(x+1,y)) command(id,Right);
					else if(pos_ok(x-1,y)) command(id,Left);
					else command(id, Dir(2*random(0, 3))); 
				}
				//puedes poner ranom aqui
				return;	
			}
			else if(c.id!=-1 and c.owner==me() ){ //si hay una tropa mia al lado

				Unit idk= unit(c.id); //que tropa mia hay
				if(idk.type==0){
					yes=true;
					return; //si hay dwarf al lado no te muevas	
				}
			}
		}
	}
 	
 	
 }
 
 void seguir(int x, int y, int id ){
 	
 	VI D = dwarves(me());
 		 
 	 for(int i: D){

		Pos p2=unit(i).pos;
		int x2=p2.i;
		int y2=p2.j; //posicion del dwarf
		if(x2<x+8 and x2>x-8 and y2<y+8 and y2>y-8){
			
				
			vector<vector<pair<int,int> > > rec(64, vector<pair<int,int> > (64,make_pair(-1,-1)));
			bool yes=false;
			persecucion(x,y,x2,y2,yes,rec); //mirar si puede llegar al dwarf
				
			if(yes){ //se mueve hacia el dwarf en teoria
				
				stack< pair<int,int> > res;
				while(rec[x2][y2]!=make_pair(-1,-1)){
					res.push(make_pair(x2,y2));
					pair<int,int> aux= rec[x2][y2];
					x2=aux.first;
					y2=aux.second;


				}
				pair<int,int> aux=res.top();
				
				if(aux.first==(x-1)) command(id, Left);
				else if(aux.first==(x+1)) command(id, Right);
				else if(aux.second==(y-1)) command (id, Bottom);
				else  command (id, Top);	
				return;
			}

		}		

	 }
	 command(id, Dir(2*random(0, 3))); //si no hay ningun dwarf cerca
 }

void move_wizards() {

  vector<int> W = wizards(me());
  for (int id : W) {
	
        Pos p = unit(id).pos;
	
		int x= p.i; //pos del mago
		int y=p.j;
		
		bool yes;
		lados_mago(x,y,yes,id);
		if(not yes)seguir(x,y,id);
	
   }
 }




  /**
   * Play method, invoked once per each round.
   */
  void play () {

	  
    move_dwarves();
    move_wizards();
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
