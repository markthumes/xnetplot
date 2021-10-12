#include "graph.h"
#include <stdio.h>

Graph::Graph( const char* name, int width, int height ){
	m_windowName = name;
	m_attrib.width = width;
	m_attrib.height = height;
	m_padding = X11::Point(0,0);
}
void Graph::drawFrame(){
	X11::Point topLeft ( m_padding.x, m_padding.y );
	X11::Point btmLeft ( m_padding.x, m_attrib.height - m_padding.y );
	X11::Point btmRight( m_attrib.width - m_padding.x, btmLeft.y );
	drawLine( X11::Color(1,1,1), X11::Line( topLeft, btmLeft ) );
	drawLine( X11::Color(1,1,1), X11::Line( btmLeft, btmRight) );
}

void Graph::render(){
	drawFrame();
	for( unsigned int i = 0; i < m_series.size(); i++ ){
		if( m_series[i].draw == false ) continue;
		int count = m_series[i].points.size();
		X11::Point* inverted = new X11::Point[count];
		for( int j = 0; j < count; j++ ){
			inverted[j].x =                   m_padding.x + m_series[i].points[j].x;
			inverted[j].y = m_attrib.height - m_padding.y - m_series[i].points[j].y;
		}
		if( m_series[i].modifier == Lines ){
			drawLines( m_series[i].color, (X11::Line*)inverted, count / 2 );
		}
		else if( m_series[i].modifier == Points ){
			drawPoints( m_series[i].color, inverted, count );
		}
	}
}

/* returns a reference to a series */
int Graph::addSeries( Series &s ){
	if( s.ID >= 0 ) return -1;
	for(int i = 0; i < m_series.size(); i++){
		if( m_series[i].draw == false ){
			m_series[i] = s;
			return s.ID = i;
		}
	}
	m_series.push_back(s);
	return s.ID = m_series.size() - 1;
}

void Graph::removeSeries( Series& s ){
	m_series[s.ID].draw = false;
}

void Graph::update( float timeSeconds ){
	while( XPending(getDisplay()) ){
		XEvent xev;
		XNextEvent( getDisplay(), &xev );
		if( xev.type == Expose ){
			getAttributes();
			refresh();
		}
		if( xev.type == KeyPress ){
			m_open = false;
		}
	}
	render();
	refresh( timeSeconds );
}

