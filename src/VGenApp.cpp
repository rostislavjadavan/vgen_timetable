
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Font.h"
#include "Resources.h"
#include "Spout.h"
#include "TimetableConfig.h"
#include "TextRender.h"
#include "Console.h"
#include "AppTimer.h"

using namespace ci;
using namespace ci::app;
using namespace std;

static const bool PREMULT = false;
static const int APP_WIDTH = 800;
static const int APP_HEIGHT = 600;

class VGenApp : public App {
 public:
	 static void prepareSettings(Settings *settings);

	 SpoutSender spoutsender;	
	 bool bInitialized;							
	 bool bMemoryMode;									
	 char SenderName[256];
	 gl::Texture2dRef spoutTexture;

	 Console console;
	 AppTimer timer;
	 TextRender textRender;

	void setup() override;
	void draw() override;
	void shutdown();

	gl::Texture2dRef	mTexture, mSimpleTexture;
};

void VGenApp::prepareSettings(Settings *settings)
{
	settings->setResizable(false);
	settings->setWindowSize(APP_WIDTH, APP_HEIGHT);
}

void VGenApp::shutdown()
{
	timer.stop();
	spoutsender.ReleaseSender();
}

void VGenApp::setup()
{
	TimetableConfig config;
	config.load("timetable.json");
	textRender.initTimetable(config);
	
	spoutTexture = gl::Texture2d::create(APP_WIDTH, APP_HEIGHT);
	strcpy_s(SenderName, "vgen.timetable");
	bInitialized = spoutsender.CreateSender(SenderName, APP_WIDTH, APP_HEIGHT);	

	timer.start();
}
	
void VGenApp::draw()
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	gl::setMatricesWindow(getWindowSize());

	gl::enableAlphaBlending( PREMULT );

	gl::color( Color::white() );
	mTexture = textRender.render(timer.getTime(), timer.getGlobalTime());
	float posX = mTexture->getBounds().getCenter().x;
	float posY = mTexture->getBounds().getCenter().y;
	gl::draw(mTexture, vec2(APP_WIDTH / 2 - posX, APP_HEIGHT / 2 - posY));
	
	if (bInitialized) {		
		spoutTexture.get()->bind();
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, getWindowWidth(), getWindowHeight());
		spoutTexture.get()->unbind();
		spoutsender.SendTexture(spoutTexture.get()->getId(), spoutTexture.get()->getTarget(), spoutTexture.get()->getWidth(), spoutTexture.get()->getHeight());
	}

	console.add(timer.getDebug());
	console.add(textRender.getDebug());
	gl::draw(console.getOutput(), vec2(5, 5));
}

CINDER_APP( VGenApp, RendererGl, VGenApp::prepareSettings)