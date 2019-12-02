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


 bool is_rock(Pos p){

	Cell c =cell(p);
	if((c.type==Outside or c.type==Cave)and c.id==-1) return true;
	else return false;


 } 

 void lados_dwarf(Pos& p, int& id, bool& yes, int extra,bool landlord){
	
	yes=false;

	int smash=0; 

	bool attack=false;

	bool run=false;

	int scared=0;


	int land=0;
 	
 	for(int i=0; i<8; i++){ //para ver lo de los lados

		if(pos_ok((p+Dir(i)).i,(p+Dir(i)).j)){ //si esa posicion es buena
			
			Cell c= cell((p+Dir(i)).i,(p+Dir(i)).j);

			
			if(c.treasure==true){
			
				yes=true;
				command(id,Dir(i));
				return;
			}

			else if(c.id!=-1 and c.owner!=me()){ //malo
				
				Unit u= unit(c.id);
				Unit tina= unit(id);
				if(u.health<=tina.health){
					attack=true;
					smash=i;
				}
				else if(u.type==Troll or u.type==Balrog){

					run=true;
					scared=i;			

				}
			}
			else if(c.id==-1 and c.owner!=me() and landlord){

				land=i;
			}

		}
	}
	if(attack==true){
		
		yes=true;
		command(id,Dir(smash));
		return;

	}
	if(run==true){
		yes=true;
		if(Dir(scared)==Bottom or Dir(scared)==BR or Dir(scared)==LB){

			if(pos_ok(p+Dir(4)) and is_rock(p+Dir(4))) command(id,Top);
			return;

		}
		if(Dir(scared)==Top or Dir(scared)==TL or Dir(scared)==RT){

			if(pos_ok(p+Dir(0)) and is_rock(p+Dir(0))) command(id,Bottom);
			return;

		}
		if(Dir(scared)==Right or Dir(scared)==BR or Dir(scared)==RT){

			if(pos_ok(p+Dir(6)) and is_rock(p+Dir(6))) command(id,Left);
			return;

		}
		if(Dir(scared)==Left or Dir(scared)==TL or Dir(scared)==LB){

			if(pos_ok(p+Dir(2)) and is_rock(p+Dir(2))) command(id,Right);
			return;

		}
		if(Dir(scared)!=Right and Dir(scared)!=Bottom){

			if(pos_ok(p+Dir(1)) and is_rock(p+Dir(1))) command(id,BR);
			return;

		}
		if(Dir(scared)!=Top and Dir(scared)!=Right){

			if(pos_ok(p+Dir(3)) and is_rock(p+Dir(3))) command(id,RT);
			return;

		}

		if(Dir(scared)!=Top and Dir(scared)!=Left){

			if(pos_ok(p+Dir(5)) and is_rock(p+Dir(5))) command(id,TL);
			return;

		}
		if(Dir(scared)!=Left and Dir(scared)!=Bottom){

			if(pos_ok(p+Dir(7)) and is_rock(p+Dir(7))) command(id,LB);
			return;

		}

	}
	if(landlord){ 
		yes=true;
		command(id,Dir(land));
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
	for (int i=0; i<60 and not found; i++){
		for(int j=0; j<60 and not found; j++){

			if(pos_ok(i,j)){
				Cell c= cell(i,j);
				if (c.treasure==true){
				      	found = true;
					ti=i;
					na=j;
				}
			
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
					if(c.treasure) cost=0;
					else if(c.type==Rock) cost=coinz[xnow][ynow]+c.turns;
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

void forthecoinz(vector<vector< int > >& coinz, Pos& p, int& id, bool& landlord){

	
	int const inf = numeric_limits<int>::max();
	
	int min=inf;
	int max=0;
	//int ygo=0;
	for ( int i=0; i<8; i++){

			
		if(pos_ok(p+Dir(i))){
			if(coinz[(p+Dir(i)).i][(p+Dir(i)).j] < min){

				min= coinz[(p+Dir(i)).i][(p+Dir(i)).j];
				max = i;
			
			
			}
		}
	}
	if(max> (200-round())) landlord=true;
	command(id, Dir(max));
}





  void move_dwarves() {

	int const inf = numeric_limits<int>::max();
	
	vector<vector<int> > coinz(60,vector<int>(60,inf));
	coinzz(coinz);
	bool landlord=false;
  	vector<int> D = dwarves(me());
	int extra=0;
  	for (int id : D) {
		
		extra++;
	        Pos p = unit(id).pos;
	
		bool yes=false;
		lados_dwarf(p,id,yes,extra,landlord);

		if(not yes and not landlord) {
			
			forthecoinz(coinz,p,id,landlord);
		
		}
		else if(not yes and landlord){

			command(id,Dir(random(0,7)));
		}
		
	}
  }

 void persecucion(Pos p, int x2, int y2,bool& yes, vector<vector<pair<int,int> > >& rec ){
	
	queue<pair<Pos,int> > q; 
	q.push(make_pair(p,0));
	vector<vector<bool> > visited(64, vector<bool>(64,false)); 
	while(!q.empty() ){

		Pos pa=q.front().first;
		int dista=q.front().second;

		q.pop();
		visited[pa.i][pa.j]=true;

		for(int i=0; i<8; i=i+2){

			Pos p3=pa+Dir(i);
			if(pos_ok(p3)){

				if(p3.i==x2 and p3.j==y2){
					rec[p3.i][p3.j]=make_pair(pa.i,pa.j);
			       		yes=true;
					return;
				}	//done
				else if(visited[p3.i][p3.j]==false){

					visited[p3.i][p3.j]=true;
					int dist=dista+1;
					rec[p3.i][p3.j]=make_pair(pa.i,pa.j);
					q.push(make_pair(p3,dist));

				}

			}
		}
	}
	
	yes=false;
	


 }
 
 void lados_mago(Pos p, bool& yes, int id){

 	
 	yes=false;
 	
 	
 	//mirar tesoros
 	for(int i=0; i<8; i++){ //para ver lo de los lados

		if(pos_ok(p+Dir(i))){ //si esa posicion es buena
			
			Cell c= cell(p+Dir(i));

			if(c.id!=-1 and c.owner!=me()){ //todos los malos, si hay malos al lado
				
				yes=true;
				if(Dir(i)==Right or Dir(i)==RT or Dir(i)==BR){
					if(pos_ok(p+Dir(6)))command(id, Left); 
					else if(Dir(i)==BR and pos_ok(p+Dir(4))) command(id, Top);
					else if(pos_ok(p+Dir(0))) command(id, Bottom);
					else command(id, Dir(2*random(0, 3))); 
				} 
				else if(Dir(i)==Left or Dir(i)==TL or Dir(i)==LB){
			       		if(pos_ok(p+Dir(2))) command(id,Right);
					else if(Dir(i)==LB and pos_ok(p+Dir(4))) command(id, Top);
					else if(pos_ok(p+Dir(0))) command(id, Bottom);
					else command(id, Dir(2*random(0, 3))); 
				}
				else if(Dir(i)==RT or Dir(i)==Top or Dir(i)==TL){
			       		if(pos_ok(p+Dir(0)))command(id, Bottom);
					else if(Dir(i)==TL and pos_ok(p+Dir(2))) command(id,Right);
					else if(pos_ok(p+Dir(6))) command(id,Left);
					else command(id, Dir(2*random(0, 3)));  
					}
				else if(Dir(i)==Bottom or Dir(i)==BR or Dir(i)==LB){
				 	if(pos_ok(p+Dir(4)))  command(id, Top);
					else if(Dir(i)==LB and pos_ok(p+Dir(2))) command(id,Right);
					else if(pos_ok(p+Dir(6))) command(id,Left);
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
 
 void seguir(Pos p, int id ){
 	
 	VI D = dwarves(me());
	int x=p.i;
	int y=p.j;
 		 
 	 for(int i: D){

		Pos p2=unit(i).pos;
		int x2=p2.i;
		int y2=p2.j; //posicion del dwarf
		if(x2<x+8 and x2>x-8 and y2<y+8 and y2>y-8){
			
				
			vector<vector<pair<int,int> > > rec(64, vector<pair<int,int> > (64,make_pair(-1,-1)));
			bool yes=false;
			persecucion(p,x2,y2,yes,rec); //mirar si puede llegar al dwarf
				
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
		lados_mago(p,yes,id);
		if(not yes)seguir(p,id);
	
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
