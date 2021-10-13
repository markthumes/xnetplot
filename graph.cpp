#include "graph.h"
#include <stdio.h>

Graph::Graph( const char* name, int width, int height ){
	m_windowName = name;
	m_attrib.width = width;
	m_attrib.height = height;
	m_padding = X11::Point(0,0);
	m_dynamicSeriesCount = 0;
	m_dynamicSeries = NULL;
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
		if( m_series[i].valid == false ) continue;
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
		delete [] inverted;
	}
	for( unsigned int i = 0; i < m_dynamicSeriesCount; i++ ){
		if( m_dynamicSeries == NULL ) break;
		if( m_dynamicSeries[i] == NULL ) break;
		if( m_dynamicSeries[i]->valid == false ) continue;
		int count = m_dynamicSeries[i]->points.size();
		X11::Point *inverted = new X11::Point[count];
		for( int j = 0; j < count; j++ ){
			inverted[j].x =                   m_padding.x + m_dynamicSeries[i]->points[j].x;
			inverted[j].y = m_attrib.height - m_padding.y - m_dynamicSeries[i]->points[j].y;
		}
		if( m_series[i].modifier == Lines ){
			drawLines( m_dynamicSeries[i]->color, (X11::Line*)inverted, count / 2 );
		}
		else if( m_series[i].modifier == Points ){
			drawPoints( m_dynamicSeries[i]->color, inverted, count );
		}
		delete [] inverted;
	}
}

/* returns a reference to a series */
int Graph::addSeries( Series &s ){
	if( s.ID >= 0 ) return -1;
	for(unsigned int i = 0; i < m_series.size(); i++){
		if( m_series[i].valid == false ){
			m_series[i] = s;
			return s.ID = i;
		}
	}
	m_series.push_back(s);
	return s.ID = m_series.size() - 1;
}
int Graph::addSeries( Series* s ){
	m_dynamicSeriesCount++;
	m_dynamicSeries = (Graph::Series**)realloc( m_dynamicSeries, sizeof( Series* ) * m_dynamicSeriesCount );
	m_dynamicSeries[m_dynamicSeriesCount-1] = s;
}

void Graph::removeSeries( Series& s ){
	m_series[s.ID].valid = false;
	m_series[s.ID].points.clear();
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

