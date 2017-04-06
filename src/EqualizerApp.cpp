#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

// poscene
#include "poScene/Scene.h"

#include "ViewController.hpp"
#include "DNAFrag.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;



class EqualizerApp : public App {
  public:
	void setup() override;
    void mouseDown( po::scene::MouseEvent event );
	void update() override;
	void draw() override;
    
    SceneRef mScene;
    
    ViewControllerRef mViewController;
    


};

void EqualizerApp::setup()
{
    mViewController = equalizer::ViewController::create();
    
    mScene = Scene::create(mViewController);
    

}

void EqualizerApp::mouseDown( po::scene::MouseEvent event )
{
    
    // do a thing
    
}

void EqualizerApp::update()
{
    mScene->update();
}

void EqualizerApp::draw()
{
    
     	gl::clear( Color( 1,1,1 ) );
    mScene->draw();

   
   // ci::gl::color(0,0,0);
    //        ci::gl::drawSolidRoundedRect(ci::Rectf(0,0,40,40), 1);
    
}
void prepareSettings( EqualizerApp::Settings * settings){
    settings->setHighDensityDisplayEnabled();
    settings->setMultiTouchEnabled(false);

    settings->setWindowSize(1440, 215);

}


CINDER_APP( EqualizerApp, RendererGl(RendererGl::Options().msaa( 16 ) ), prepareSettings )
