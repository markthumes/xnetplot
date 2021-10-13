#include "x11wrapper/x11wrapper.h"
#include <vector>
#include <stdlib.h>
#include <unistd.h>

class Graph : public X11 {
public:
	typedef enum{
		Lines,
		Points
	}Modifier;
	class Series{
	public:
		Series(){
			valid = true;
			ID = -1;
			modifier = Points;
		}
		int ID;
		bool valid;
		X11::Color color;
		int width;
		Modifier modifier;
		std::vector<X11::Point> points;
	};
public:
	Graph( const char* name, int width, int height );
	int addSeries( Series &s );
	int addSeries( Series *s );
	void removeSeries( Series &s );
	void setPadding( int x, int y ){ m_padding = X11::Point( x, y ); }

	void update( float timeSeconds = 0.0 );
protected:
	void drawFrame();
	void render();
private:
	std::vector<Series>  m_series;
	Series** m_dynamicSeries;
	int m_dynamicSeriesCount;
	X11::Point m_padding;
	X11::Point m_origin;
};
