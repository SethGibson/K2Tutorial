#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Kinect2.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class K2TutorialApp : public AppNative {
public:
	void setup();
	void prepareSettings( Settings *pSettings );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
	Kinect2::DeviceRef mKinect;
	Kinect2::Frame mFrame;

	gl::Texture mRgbTexture;
	Kinect2::Body mBody_0;
	std::map<JointType, Kinect2::Body::Joint> mJoints;
};

void K2TutorialApp::prepareSettings( Settings *pSettings )
{
	pSettings->setWindowSize(1280,720);
	pSettings->setFrameRate(30);
}

void K2TutorialApp::setup()
{
	mKinect = Kinect2::Device::create();

	//TODO: Deep dive into DeviceOptions, not all these may be necessary, some may be redundant
	mKinect->start(Kinect2::DeviceOptions().enableColor().enableInfrared().enableBody());
}

void K2TutorialApp::mouseDown( MouseEvent event )
{
}

void K2TutorialApp::update()
{
	mJoints.clear();
	if(mKinect->getFrame().getTimeStamp()>mFrame.getTimeStamp())
	{
		mFrame = mKinect->getFrame();
		if(mFrame.getColor())
			mRgbTexture = gl::Texture(mFrame.getColor());
		
		//I'm lazy, but if you're not, getBodies() returns std::vector<Kinect2::Body>
		auto cBodies = mFrame.getBodies();
		if(cBodies.size()>0)
			mJoints = cBodies.at(0).getJointMap();
	}
}

void K2TutorialApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	if(mRgbTexture)
	{
		gl::draw(mRgbTexture, Rectf(Vec2f::zero(), getWindowSize()));
		if(mJoints.size()>0)
		{
			gl::enableAlphaBlending();
			gl::pushMatrices();
			gl::scale(Vec2f(getWindowSize())/Vec2f(mRgbTexture.getSize()));
			for(auto cJoint : mJoints)
			{
				Vec2f cJointPos = Kinect2::mapBodyCoordToColor(cJoint.second.getPosition(), mKinect->getCoordinateMapper());
				gl::color(ColorA(0,1,0.25f,0.5f));
				gl::drawSolidCircle(cJointPos, 20);
				gl::color(ColorA(1,1,1,1));
				gl::drawStrokedCircle(cJointPos, 20);
			}
			gl::disableAlphaBlending();
			gl::popMatrices();
		}
	}
}

CINDER_APP_NATIVE( K2TutorialApp, RendererGl )
