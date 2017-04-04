#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class EqualizerApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void EqualizerApp::setup()
{
}

void EqualizerApp::mouseDown( MouseEvent event )
{
}

void EqualizerApp::update()
{
}

void EqualizerApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( EqualizerApp, RendererGl )
