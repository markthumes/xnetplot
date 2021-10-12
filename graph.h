#include "x11wrapper/x11wrapper.h"
#include <vector>
#include <unistd.h>

class Graph : public X11 {
public:
	typedef enum{
		Lines,
		Points
	}Modifier;
	class Series{
	public:
		X11::Color color;
		int width;
		Modifier modifier;
		std::vector<X11::Point> points;
	};
public:
	Graph( const char* name, int width, int height );
	void drawFrame();
	void render();
	int addSeries( Series s );
	void setPadding( int x, int y ){ m_padding = X11::Point( x, y ); }
private:
	std::vector<Series> m_series;
	X11::Point m_padding;
	X11::Point m_origin;
};
