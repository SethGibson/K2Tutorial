#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Kinect2.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class K2TutorialApp : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
	Kinect2::DeviceRef mKinect;
	Kinect2::Frame mFrame;
};

void K2TutorialApp::setup()
{
}

void K2TutorialApp::mouseDown( MouseEvent event )
{
}

void K2TutorialApp::update()
{
}

void K2TutorialApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( K2TutorialApp, RendererGl )
