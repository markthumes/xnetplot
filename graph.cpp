#include "graph.h"

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
	for( int i = 0; i < m_series.size(); i++ ){
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

int Graph::addSeries( Series s ){
	m_series.push_back(s);
	return m_series.size();
}

