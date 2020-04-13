#include<iostream>
#include<cstdlib>           // for including the random function 
#include<conio.h>
#include<time.h>  // to display current and unique time stamp
using namespace std;
enum edir { STOP =0, LEFT =1, UPLEFT =2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT =5, DOWNRIGHT =6};  // total 6 directions 
int rand();
class cball
{
    private :
    int x, y;
	int originalX, originalY; // for the rest of the game the position of the x and y is set to the original one .
	edir direction ;   // for the enum function making the object 
		
	public:
	  cball(int  posX , int posY)
	   {
			originalX = posX;
			originalY =posY;
			x = posX;
			y = posY ;
			direction = STOP;
		} 
		  void Reset()
		  {                        // once the game is over it has to reset acc to this function
		  	x= originalX;
		  	y=originalY;
		  	direction = STOP;
		  }
		   void changedirection( edir d)
		   {
		   	 direction =d;
		   	 
		   }
		   void randomdirection()
		   {
		   	direction =(edir) (rand()%6+1); // since we have six directions given so we have used %6.
		   }
		inline int getX()
		{
		  return x;
		}
		inline int getY()
		{
			return y;
		}
		 inline edir getdirection()    // use of inline so that it can directly use it , it doen't  has to use it calling another function
		 {
		 	return direction ;
		 }
		  void move ()     //for the movement of the ball and the paddle
		  {
		  	switch(direction)    // it must be included as we have mentioned the order in the enum function 
		  	{
		  		case STOP:
		  			break;
		  		case LEFT :
		  		    x++;
				    break;
				case UPLEFT:
				     x-- ; y--;
				     break;
				case DOWNLEFT:
				     x-- ; y++;
				     break;
				case UPRIGHT :
				     x++ ; y--;
				     break;
				case  DOWNRIGHT :
				     x++ ; y++;
				     break;
				default :
			     	break;	
			}
	    }
		  friend ostream & operator<<(ostream & o, cball c)
		  {
		  	o<<"ball ["<<c.x <<","<<c.y <<"]["<<c.direction<<"]";
		  	return o;
		  }
    };
 class cpaddle
 {
   private :
   int x ,y;
   int originalX , originalY;
   
 public:
  cpaddle()
  {
  	x=y=0;
	  }	
	cpaddle(int posX ,int posY)
	{
		originalX =posX;
		originalY = posY;
		x= posX;
		y= posY;
	  }  
	  	inline int getX()
		{
		  return x;
		}
		inline int getY()
		{
			return y;
		}
		void Reset()
		  {                                // to reset the game 
		  	x= originalX;
		  	y=originalY;
		  }
		  void moveup(){
		  	y--;
		  }
		 void movedown()
		 {
		 	 x--;
		 }
		  friend ostream & operator<<(ostream & o, cpaddle c)
		  {
		  	o<<"paddle ["<<c.x <<","<<c.y <<"]";
		  	return o;
		  }
 };
 class gamemanager{
 	private:
 		int width ;
 		int height;
 		char up1, down1, up2,down2;
 		bool quit ;
 		int score1,score2;
 		cball *ball;
 		cpaddle * player1;
 		cpaddle * player2;
 		
		 public:
		 	gamemanager(int w, int h)
		 	{
		 		srand(time(NULL)); // current time and unique time stamp
		 		quit =false;
		 		up1='w';up2='i';
		 		down1='s'; down2='k';
		 		score1=score2=0;
		 		width = w;
		 		height =h;
		 		ball = new cball(w/2, h/2);
		 		player1 = new cpaddle (1,h/2-3);
		 		player2 = new cpaddle(w-2, h/2-3);
		 		
			 }
		 	~gamemanager()
		 	{
		 		delete ball,player1,player2; // to avoid the memory leak.
			 }
			 void scoreup( cpaddle *player)
			 {
			 	if(player== player1)
			 	
			 		score1++;
				 
				 else if (player == player2) 
				 	score2++;
				 	
				 	ball->Reset();
					 player1-> Reset();
					 player2-> Reset();      // after everything is over to set into the new one  
			   }
	void draw()
	{
		system("cls");
		for(int i=0;i<width +2 ; i++)
          cout<<"\xB2";	
		  cout<< endl;
		  
		  for(int i=0;i< height ;i++)
		  {
		  	for(int j=0;j< width ;j++)
		   {
		  		int ballx= ball->getX();
		  		int bally= ball->getY();
		  		int player1x = player1->getX();
		  		int player2x = player2->getX();
		  		int player1y = player1-> getY();
		  		int player2y = player2-> getY();
		  		
		  		if(j==0) // first actual character on the screen
		  		cout<<"\xB2";
		  		if(ballx == j && bally == i)
		  		cout<<"O"; // ball
		  		else if(player1x == j && player1y == i)
		  		 cout<<"\xDB" ; // player1
		  		else if(player2x == j && player2y == i)
		  	     cout<<"\xDB" ;// player2
		  		 
		  	        
		  		else if(player1x == j && player1y +1 == i)
		  		    cout<<"\xDB" ; // player1
		  	    else if(player1x == j && player1y +2 == i)
		  		    cout<<"\xDB" ;// player1
		 	    else if(player1x == j && player1y +3 == i)    // at the end will print the four segment for the player
		  		    cout<<"\xDB" ;// player1
				   
				else if(player2x == j && player2y +1 == i)
		  		    cout<<"\xDB" ; // player2                        // making the two plain plank for the game of ping pong 
		  		else if(player2x == j && player2y +2 == i)
		  		    cout<<"\xDB" ;// player2
		  	    else if(player2x == j && player2y +3 == i)    // at the end will print the four segment for the player
		  		    cout<<"\xDB" ;// player2
		  		   
			    else 
		  		 cout<<" ";
		  		
		  		if(j==width-1)
		  		cout<<"\xB2";
			}
			 cout<<endl;
		}
		  
		  for(int i =0 ;i<width +2;i++)
		  cout<<"\xB2";
		  cout<<endl;
		  
		  cout<<score1<<endl;
		  cout<<score2<<endl;     // scores to be displayed for the player 
		  }
  void input()
  {
  	ball->move();
  	int ballx= ball->getX();
	int bally= ball->getY();
	int player1x = player1->getX();
	int player2x = player2->getX();
	int player1y = player1-> getY();
	int player2y = player2-> getY();
    
	if(_kbhit())
	{   // if we hit anything on the keyboard then we will be getting the current result with the getch function
		char current = _getch();
		if(current == up1)
		 player1->moveup();
		 
	    if(current == up2)
		 player2->moveup();
		 
		if(current == down1)
		if( player1y +4 < height)
		   player1->movedown();
		   
		if(current == down2)
		if( player2y +4 < height)
		 player2->movedown();
		   
		if(ball->getdirection()== STOP)
		 ball->randomdirection();
		 
		 if(current == 'q')
		 {
		 	quit =true;
		  } 
		}	
	}
	
	 void logic()
	 {
	 	int ballx= ball->getX();
		int bally= ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1-> getY();
		int player2y = player2-> getY();
		
		// this logic is for the left paddle 
		for(int i=0;i<4 ;i++)
		if(ballx==player1x+1)
		    if(bally == player1y +i)
		    ball->changedirection((edir)(rand()%3+4));
		  
		  // this is for the right paddle   
		    for(int i=0;i<4 ;i++)
		if(ballx==player2x -1) // since it is one block on the left  so that it could bounce off 
		    if(bally == player2y +i)
		    ball->changedirection((edir)(rand()%3+1));
		    
		    // for the bottom wall
        if(bally == height -1)
         ball->changedirection(ball->getdirection()== DOWNRIGHT ? UPRIGHT : UPLEFT);
        
        // for the top wall 
        if(bally == 0)
        ball->changedirection(ball->getdirection()== UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        
        //if the ball is on the right wall 
        if(ballx== width -1)
        scoreup(player1);
        
        // if the ball is on the left wall
         if(ballx== 0)
        scoreup(player2);

	}
	
	void run()
	{
		while(!quit)
		{
			draw();
			input();
			logic();
		}
			 }         
 };
 

int main()
{
	/*cball c(0,0);
	cout<<c<<endl;
	c.randomdirection();
	cout<<c<<endl;  // for the checking of the pong movement 
	c.move() ;
	cout<<c<<endl;
	c.randomdirection();
	c.move();
	cout<<c<<endl;*/
 /*	cpaddle p1(0,0);
	cpaddle p2 (10,0);
	cout<<p1<<endl;     // for checking the paddle of the pong 
	cout<<p2<<endl;
	p1.moveup();
	p2.movedown();
	cout<<p1<<endl;
	cout<<p2<<endl; */
	gamemanager c(40,20);
	c.run();
	return 0;
	
}

