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
 
 int ownernew(Cell& c){
     
     //si soy yo devuelve 1
     //si es outside devuelve 0
    // si no es de nadie devuelve -1
      
     if(c.type==Abyss or c.type==Granite or c.type==Outside) return 0;
    if(c.owner==me()) return 1;
    else return -1;
         

 }


 void lados_dwarf(Pos& p, int& id, bool& yes ){
	

	int smash=0; 

	bool attack=false;
    bool attackif=false;

	bool run=false;

	int scared=0;
    bool camaradas=true;

    
 	
 	for(int i=0; i<8; i++){ //para ver lo de los lados

		if(pos_ok(p+Dir(i))){ //si esa posicion es buena
			
			Cell c= cell((p+Dir(i)).i,(p+Dir(i)).j);

			
			if(c.treasure==true){
			
				yes=true;
				command(id,Dir(i));
				return;
			}
			

			else if(c.id!=-1){ //alguien
				
				Unit u= unit(c.id);
				Unit tina= unit(id);
				if(u.player!=me() and u.health<=tina.health){
					attack=true;
					smash=i;
				}
				
				else if(u.type==Troll){

					run=true;
					scared=i;			

				}
				else if(u.player!=me() and u.health>tina.health) attackif=true;
                
				else if(u.player==me()) camaradas=true;
            }
            

				
            
		}
	}
	if(attack==true and not run){
		

        yes=true;
        command(id,Dir(smash));
        return;
        

	}
	if(attackif==true and camaradas and not run){
		

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
    
    int danger= balrog_id ();
    Unit ew = unit(danger);
    Pos mortal= ew.pos;
    int mortalx= mortal.i;
    int mortaly=mortal.j;
    for(int i=0; i<8; i++) coinz[mortalx+ix[i]][mortaly+wai[i]]=inf;
    int ixx[]={ -2,2,-2,2,2,-2,0,0,-1,+1,-1,+1,2,2,-2,-2};
	int waii[]={-2,2,2,-2,0,0,2,-2,2,2,-2,-2,1,-1,1,-1};	
    for(int i=0; i<16; i++) coinz[mortalx+ixx[i]][mortaly+waii[i]]=inf;

 }
 
void slayer(vector<vector<int > >& killingspree){

	typedef pair<int, pair <int,int> > p;
	
	int ix[]={ -1, 0, 1, -1,1,-1,0,1};
	int wai[]={1,1,1,0,0,-1,-1,-1};	
	int const inf = numeric_limits<int>::max();

	//buscar un dwarf
	bool found=false;
	int ti;
	int na;
	for (int i=0; i<60 and not found; i++){
		for(int j=0; j<60 and not found; j++){

                Cell c= cell(i,j);
                if(c.id!=-1){ //alguien
                        
                        Unit malechor= unit(c.id);
                        if(malechor.type!=Troll and malechor.type!=Balrog and malechor.player!=me()){
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

	killingspree[ti][na]=0; //tesoro igual 0
	Unit malo;
    bool yo;
   

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
                    yo=false;
                  //  otros=false;
                   // toomuch=false;
                   if(c.id!=-1 ){ //alguien
                       malo= unit(c.id);
                       if(malo.type!=Troll and malo.type!=Balrog and malo.player!=me()) { //malo
                           yo=true;
                       }
                   }
					if(yo==true) cost=0; //es un malvado q no es un troll o un balrog
					else if(c.type==Rock) cost=killingspree[xnow][ynow]+c.turns;
					else if(c.type==Abyss) cost=inf;
					else if(c.type==Granite) cost=inf;
					else cost=killingspree[xnow][ynow]+1;

					if(killingspree[xaux][yaux] > cost){

						killingspree[xaux][yaux] = cost;

						q.push(make_pair(cost,make_pair(xaux,yaux) ));


					}
				}
			}
		}
    }
    
    int danger= balrog_id ();
    Unit ew = unit(danger);
    Pos mortal= ew.pos;
    int mortalx= mortal.i;
    int mortaly=mortal.j;
    for(int i=0; i<8; i++) killingspree[mortalx+ix[i]][mortaly+wai[i]]=inf;
     int ixx[]={ -2,2,-2,2,2,-2,0,0,-1,+1,-1,+1,2,2,-2,-2};
	int waii[]={-2,2,2,-2,0,0,2,-2,2,2,-2,-2,1,-1,1,-1};	
    for(int i=0; i<16; i++) killingspree[mortalx+ixx[i]][mortaly+waii[i]]=inf;
    

 }
 
 
 
void forthecoinz(vector<vector< int > >& coinz, Pos& p, int& id){

	
	int const inf = numeric_limits<int>::max();
	
	int min=inf;
	int max=0;
    int realmax=inf;
    int minreal=inf;
    int posi;
    int nohaynada;
    bool nohay=false;
    int roquita;
    bool roka=false;
    bool landlord=false;
   
    
	//int ygo=0;
	for ( int i=0; i<8; i++){

			
		if(pos_ok(p+Dir(i)) ){
            posi=coinz[(p+Dir(i)).i][(p+Dir(i)).j];
            Cell tina= cell(((p+Dir(i)).i),((p+Dir(i)).j));
			if(posi < min ){
                //Cell tina= cell(((p+Dir(i)).i),((p+Dir(i)).j));
				min= posi;
				max = i;
                if((ownernew(tina)==-1) and  posi < minreal) {
                  
                    minreal=posi;
                    realmax=i;
                    
                }
			}
			if((ownernew(tina)==-1)) {
                
                if(not nohay and tina.type==Cave){
                    nohay=true;
                    nohaynada=i;
                }
                if(not roka and tina.type==Rock){
                    
                    roka=true;
                    roquita=i;
                    
                }
            }
		}
	}
	if(min> (200-round())) landlord=true;
    if(minreal!=inf and minreal==min) max=realmax;
    Cell tinapower = cell(p+Dir(max));
	if(tinapower.id==-1 and not landlord){ //va hacia el sitio minimo si no hay nadie
        command(id, Dir(max));
        return;
    }
    
    if(nohay or landlord) { //va hacia sitio no mio
        command(id, Dir(nohaynada));
        return;
    }
    if(roka or landlord){ //destruye roka
        
        command(id, Dir(roquita));
        return;
    }
    
    
}


void koro(vector<vector< int > >& killingspree, Pos& p, int& id){

	
	int const inf = numeric_limits<int>::max();
	
	int min=inf;
	int max=0;
    int posi;
    int nohaynada;
    bool nohay=false;
    int roquita;
    bool roka=false;
    bool landlord=false;
   
    
	//int ygo=0;
	for ( int i=0; i<8; i++){

			
		if(pos_ok(p+Dir(i)) ){
            posi=killingspree[(p+Dir(i)).i][(p+Dir(i)).j];
            Cell tina= cell(((p+Dir(i)).i),((p+Dir(i)).j));
			if(posi < min){
                //Cell tina= cell(((p+Dir(i)).i),((p+Dir(i)).j));
				min= posi;
				max = i;
                
			}
			if((ownernew(tina)==-1)) {
                
                if(not nohay and tina.type==Cave){
                    nohay=true;
                    nohaynada=i;
                }
                if(not roka and tina.type==Rock){
                    
                    roka=true;
                    roquita=i;
                    
                }
            }
		}
	}
	if(min> (200-round())) landlord=true;
    Cell tinapower = cell(p+Dir(max));
	if(tinapower.id==-1 and not landlord){ //va hacia el sitio minimo si no hay nadie
        command(id, Dir(max));
        return;
    }
    
    if(nohay or landlord) { //va hacia sitio no mio
        command(id, Dir(nohaynada));
        return;
    }
    if(roka or landlord){ //destruye roka
        
        command(id, Dir(roquita));
        return;
    }
    
    
}

bool hay_mago(Pos& p){
    
    
    for(int i=0; i<8; i++){
        
        if(pos_ok(p+Dir(i))){
            
            Cell c= cell(p+Dir(i));
            if(c.id!=-1 ){
                
                Unit ismago = unit(c.id);
                if(ismago.type==Wizard and ismago.player==me()) return true;
                 
            }
        }
    }
    
    return false;
}
    
void move_dwarves() {

	int const inf = numeric_limits<int>::max();
    
	vector<vector<int> > coinz(60,vector<int>(60,inf));
	coinzz(coinz);
	vector<vector<int> > killingspree(60,vector<int>(60,inf));
    slayer(killingspree);
  	vector<int> D = dwarves(me());
    

  	for (int id : D) {
		
        
        Pos p = unit(id).pos;
        
       
        
            
            bool yes=false;
       
            lados_dwarf(p,id,yes);

            if(not yes) {
                
                 if(hay_mago(p)){
            
                    koro(killingspree,p,id);
            
                }
			
                else forthecoinz(coinz,p,id);
		
            }
        
    }
    
  }

 
 void lados_mago(Pos p, bool& yes, int id){

 	
 	//mirar tesoros
 	for(int i=0; i<8; i++){ //para ver lo de los lados

		if(pos_ok(p+Dir(i))){ //si esa posicion es buena
			
			Cell c= cell(p+Dir(i));

			if(c.id!=-1){ //alguien
                
                Unit g=unit(c.id);
                if( g.player!=me()){
                    yes=true;
                    vector<bool> vo(4,false); //mirar si es roka
                    for(int i=0; i<8; i=i+2){
                    
                    
                        if(pos_ok(p+Dir(i)) and is_rock(p+Dir(i))) vo[i/2]=true; //no hay nadie i es cave or outside
                  
                    }
				
				
                    if(Dir(i)==Right or Dir(i)==RT or Dir(i)==BR){
                        if(pos_ok(p+Dir(6))and vo[3]==true)command(id, Left); 
                        else if(Dir(i)==BR and pos_ok(p+Dir(4)) and vo[2]==true) command(id, Top);
                        else if(pos_ok(p+Dir(0))and vo[0]==true) command(id, Bottom);
					 
                    } 
                    else if(Dir(i)==Left or Dir(i)==TL or Dir(i)==LB){
			       		if(pos_ok(p+Dir(2))and vo[1]==true) command(id,Right);
                        else if(Dir(i)==LB and pos_ok(p+Dir(4))and vo[2]==true) command(id, Top);
                        else if(pos_ok(p+Dir(0))and vo[0]==true) command(id, Bottom);
					 
                    }
                    else if(Dir(i)==RT or Dir(i)==Top or Dir(i)==TL){
			       		if(pos_ok(p+Dir(0))and vo[0]==true)command(id, Bottom);
                        else if(Dir(i)==TL and pos_ok(p+Dir(2))and vo[1]==true) command(id,Right);
                        else if(pos_ok(p+Dir(6))and vo[3]==true) command(id,Left);
					 
					}
                    else if(Dir(i)==Bottom or Dir(i)==BR or Dir(i)==LB){
                        if(pos_ok(p+Dir(4))and vo[2]==true)  command(id, Top);
                        else if(Dir(i)==LB and pos_ok(p+Dir(2))and vo[1]==true) command(id,Right);
                        else if(pos_ok(p+Dir(6))and vo[3]==true) command(id,Left);
					 
                    }
                    //puedes poner ranom aqui
                    return;	
                }
                else if(g.player==me()){ //si hay una tropa mia al lado

                    Unit idk= unit(c.id); //que tropa mia hay
                    if(idk.type==Dwarf){
                        command(id,None);
                        yes=true;
                        return; //si hay dwarf al lado no te muevas	
                    }
                }
            }
        }
    }
 }

 
void power(vector<vector<int > >& bambam){
    

	typedef pair<int, pair <int,int> > p;
	
	int ix[]={-1,1,0,0};
	int wai[]={0,0,-1,1};	
    
	int const inf = numeric_limits<int>::max();

	//buscar un dwarf;
	int ti; 
	int na;
    Unit ichi;
    int price;
    
    vector<vector<bool> > visited(60, vector<bool>(60,false));
    

	priority_queue< p, vector<p>, greater<p> > q;

    
    vector<int> d = dwarves(me());
    
    int cuat =d.size();
    
    for(int i=0; i<1; i++){
        
        ichi= unit(d[i]);
        ti=ichi.pos.i;
        na=ichi.pos.j;
        q.push(make_pair(0,make_pair(ti,na)));
        bambam[ti][na]=0;
        
    }
    

    
    

	while(not q.empty()){

		p now = q.top();
		q.pop();
		int xnow=now.second.first;
		int ynow=now.second.second;
        int price=now.first;

		if(!visited[xnow][ynow]){

			visited[xnow][ynow] =true;

			for(int i=0; i< 4; i++){

				//adj;
				if(pos_ok(xnow+ix[i], ynow+wai[i])){
					//if pos okey
                   
					int xaux=xnow+ix[i];
					int yaux=ynow+wai[i];
                    int cost;
					
					Cell c =cell (xaux, yaux);
                  
                    if(c.type==Cave or c.type==Outside){
                        
                        bool hey=false;
                        
                        if(c.id!=-1){
                            
                            Unit cool= unit(c.id);
                            if(cool.type==Dwarf and cool.player==me()){
                                cost=0;
                                hey=true;
                            }
                        }
                
                         if(not hey) cost=price+1;
                       
                        if(bambam[xaux][yaux] > cost ){
    
                            bambam[xaux][yaux] = cost;

                            q.push(make_pair(cost,make_pair(xaux,yaux) ));
                        
                        }

					}
				}
			}
		}
    }
    
    
    int danger= balrog_id ();
    Unit ew = unit(danger);
    Pos mortal= ew.pos;
    int mortalx= mortal.i;
    int mortaly=mortal.j;
    for(int i=0; i<4; i++) bambam[mortalx+ix[i]][mortaly+wai[i]]=inf; 
    int ixx[]={-1, 1,-1,1};
    int waii[]={1,-1,-1,1};	
    for(int i=0; i<4; i++) bambam[mortalx+ixx[i]][mortaly+waii[i]]=inf; 
    //poner mas rango al balrog
    int ixxx[]={ -2,2,-2,2,2,-2,0,0,-1,+1,-1,+1,2,2,-2,-2};
	int waiii[]={-2,2,2,-2,0,0,2,-2,2,2,-2,-2,1,-1,1,-1};	
    for(int i=0; i<16; i++) bambam[mortalx+ixxx[i]][mortaly+waiii[i]]=inf;

 }
 void gogo(vector<vector< int > >& bambam, Pos& p, int& id){

	
	int const inf = numeric_limits<int>::max();
	
	int min=inf;
	int max=0;
    int posi;
    
	//int ygo=0;
	for ( int i=0; i<4; i=i+2){

			
		if(pos_ok(p+Dir(i)) and is_rock(p+Dir(i))){
            
            posi=bambam[(p+Dir(i)).i][(p+Dir(i)).j];
            
            
			if(posi < min){
              
				min= posi;
				max = i;
                
			}
		}
	}
       if(pos_ok(p+Dir(max))){ 
        //cout << min << " " << Dir(max) << endl;
        command(id, Dir(max));
        return;
       }
}

void move_wizards() {
    
    int const inf = numeric_limits<int>::max();
    
    vector<vector<int> > bambam(60,vector<int>(60,inf));
	power(bambam);
    
    for(int i=0; i<60; i++){
     for(int j=0; j<60; j++){
         
         if(bambam[i][j]!=inf)cout << bambam[i][j] << " " ;
         if(bambam[i][j]<10) cout << " ";
         else cout << "XX" << " " ;
     }
     cout << endl;
        
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

  vector<int> W = wizards(me());
  for (int id : W) {
	
        Pos p = unit(id).pos;
	
		
		//las dos funciones de magos estan mal
		bool yes=false;
		lados_mago(p,yes,id);
        if(not yes){
            
           
            gogo(bambam,p,id);
          
            
        } 
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
