#include "graph.h"
#include <stdio.h>
#include <unistd.h>

int main(){
	float frate = 1.0/120.0;
	Graph g("New Window", 1000, 1000);
	g.open();
	g.setBackground( X11::Color(0,0,0) );
	g.setDoubleBuffered();


	Graph::Series s[3];
	s[0].color = X11::Color(0,1,1);
	s[0].width = 3;
	s[0].modifier = Graph::Lines;
	for( int i = -100; i < 100; i++ ){
		s[0].points.push_back( X11::Point( i, i*i/10 ) );
	}
	g.addSeries( s[0] );

	s[1].color = X11::Color(1,1,0);
	s[1].modifier = Graph::Points;
	for( int i = 0; i < 100; i++ ){
		s[1].points.push_back( X11::Point( i*4, i ) );
	}
	g.addSeries( s[1] );

	s[2].color = X11::Color(1,0,1);
	s[2].modifier = Graph::Lines;
	for(int i = -100; i < 100; i++ ){
		s[2].points.push_back( X11::Point( i*i, 10 + i ));
	}
	g.addSeries( s[2] );

	g.setPadding( 100, 100 );
	while(g.isOpen()){
		g.update(frate);
	}
	g.close();
	return 1;
}
