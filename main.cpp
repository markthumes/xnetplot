#include "graph.h"
#include <stdio.h>
#include <unistd.h>

int main(){
	float frate = 1.0/60.0;
	Graph g("New Window", 1000, 1000);
	g.open();
	g.setBackground( X11::Color(0,0,0) );
	g.setDoubleBuffered();


	Graph::Series s[10];
	for( int i = 0; i < 10; i++ ){
		for( int j = 0; j < 100; j++ ){
			s[i].modifier = Graph::Lines;
			s[i].points.push_back(X11::Point(j, i*j));
		}
		g.addSeries(&s[i]);
	}

	g.setPadding( 100, 100 );
#if 0
	g.removeSeries(1);
	g.removeSeries(3);
	g.removeSeries(5);
	g.removeSeries(7);
#endif
	int frame = 0;
	while(g.isOpen()){
		s[0].points.push_back(X11::Point(frame, frame++));
		g.update(frate);
	}
	g.close();
	return 1;
}
