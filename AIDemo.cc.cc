#include "Player.hh"


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

 



  void move_dwarves() {
    VI D = dwarves(me());
    int n = D.size();
    VI perm = random_permutation(n);
    for (int i = 0; i < n; ++i) {
      // id is an own dwarf. For some reason (or not) we treat our dwarves in random order.
      int id = D[perm[i]];
      if (random(0, 2) == 0) command(id, Dir(random(0, 7))); // With probability 1/3, we move at random.
      else { // Otherwise, ...
        bool enemy = false;
        for (int k = 0; not enemy and k < 8; ++k) {
          Pos p = unit(id).pos;
          if (pos_ok(p)) {
            int id2 = cell(p).id;
            if (id2 != -1 and unit(id2).player != me()) { // if we are next to an enemy, we attack.
              enemy = true;
              command(id, Dir(k));
            }
          }
        }
        // Finally, the following code does several things, most of them stupid.
        // It's just to show that there are many possibilities.
        if (not enemy) {
          if (round() < 40) command(id, Left);
          else if (round() > 180) command(id, None);
          else if (random(0, 1)) {
            set<Pos> S;
            while ((int)S.size() < 4) S.insert(Pos(random(0, 59), random(0, 59)));
            vector<Pos> V(S.begin(), S.end());
            if (V[random(0, 3)].i >= 30 ) command(id, Bottom);
            else command(id, RT);
          }
          else if (status(0) > 0.8) command(id, Left);
          else if (unit(id).health < 20) command(id, Dir(2*random(0, 3)));
          else if (cell(10, 20).owner == 2) command(id, TL);
          else if (nb_cells(3) > 50) command(id, LB);
          else if (nb_treasures(me()) < 4) command(id, BR);
          else if (cell(Pos(20, 30)).type == Cave) command(id, Bottom);
          else if (cell(Pos(2, 2)).treasure) command(id, Top);
          else cerr << unit(id).pos << endl; // You can print to cerr to debug.
        }
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
 
 void lados_mago(int x, int y, int& yes){
 	
 	yes=false;
 	
 	int wai[]={1,1,1,0,0,-1,-1,-1};
 	int ix[]={-1,0,1,-1,1,-1,0,1};
 	
 	
 	for(int i=0; i<8; i++){ //para ver lo de los lados

		if(pos_ok((x+ix[i]),(y+wai[i]))){
			
			Cell c= cell(x+ix[i],y+wai[i]);

			if(c.id!=-1 and c.owner!=me()){ //todos los malos, si hay malos al lado
				
				yes=true;
				if(ix[i]==1 and pos_ok(x-1,y))	command(id, Left);
				else if(ix[i]==-1 and pos_ok(x+1,y)) command(id, Right);
				else if(wai[i]==1 and pos_ok(x,y-1)) command(id, Bottom);
				else if(wai[i]==-1 and pos_ok(x,y+1)) command(id, Top);
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
 
 void seguir(int x, int y){
 	
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

		lados_mago(x,y,yes);
		if(not yes)seguir(x,y);
	
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
