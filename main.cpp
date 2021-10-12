#include "graph.h"
#include <unistd.h>

int main(){
	float frate = 1.0/120.0;
	Graph g("New Window", 1000, 1000);
	g.open();
	g.setBackground( X11::Color(0,0,0) );
	g.setDoubleBuffered();
	bool open = true;
	Graph::Series s;
	s.color = X11::Color(0,1,1);
	s.width = 3;
	s.modifier = Graph::Lines;
	for( int i = -100; i < 100; i++ ){
		s.points.push_back( X11::Point( i, i*i/10 ) );
	}
	g.addSeries( s );
	g.setPadding( 100, 100 );
	while(open){
		while( XPending(g.getDisplay()) ){
			XEvent xev;
			XNextEvent( g.getDisplay(), &xev );
			if( xev.type == Expose ){
				g.getAttributes();
				g.refresh();
			}
			if( xev.type == KeyPress ){
				open = false;
			}
		}
		g.render();
		g.refresh(frate);
	}
	g.close();
	return 1;
}
