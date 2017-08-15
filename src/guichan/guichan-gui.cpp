/*
 *  Basilisk II (C) pelya
 *  Basilisk II (C) 2017 Google
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <algorithm>
#ifdef ANDROIDSDL
#include <android/log.h>
#endif
#include <guichan.hpp>
#include <iostream>
#include <sstream>
#include <SDL/SDL_ttf.h>
#include <guichan/sdl.hpp>
#include "guichan/contrib/sdl/sdltruetypefont.hpp"

#define PANDORA

#if defined(ANDROID)
#include <SDL_screenkeyboard.h>
#endif

SDL_Surface* GuiScreen;
int emulating;
bool running = false;
SDL_Joystick *joy0;

#define GUI_WIDTH  640
#define GUI_HEIGHT 480

char currentDir[300]=".";

namespace globals
{
    gcn::Gui* gui;
}

namespace sdl
{
  // Main objects to draw graphics and get user input
  gcn::SDLGraphics* graphics;
  gcn::SDLInput* input;
  gcn::SDLImageLoader* imageLoader;

  void init()
  {

    GuiScreen = SDL_SetVideoMode(GUI_WIDTH, GUI_HEIGHT, 16, SDL_SWSURFACE);
    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

#ifdef ANDROIDSDL
	  // Enable Android multitouch
	  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	  joy0 = SDL_JoystickOpen(0);
#endif
#ifdef PANDORA
    SDL_ShowCursor(SDL_ENABLE);
#endif

    imageLoader = new gcn::SDLImageLoader();
    gcn::Image::setImageLoader(imageLoader);

    graphics = new gcn::SDLGraphics();
    graphics->setTarget(GuiScreen);
    
    input = new gcn::SDLInput();

    globals::gui = new gcn::Gui();
    globals::gui->setGraphics(graphics);
    globals::gui->setInput(input);
  }


  void halt()
  {
    delete globals::gui;
    delete imageLoader;
    delete input;
    delete graphics;
  }


  void run()
  {
    // The main loop
    while(running)
    {
      // Check user input
      SDL_Event event;
      while(SDL_PollEvent(&event))
      {
    		if (event.type == SDL_QUIT)
    		{
    			running = false;
    			break;
    		}
        else if (event.type == SDL_KEYDOWN)
        {
          switch(event.key.keysym.sym)
          {
//            case SDLK_q:
//        			running = false;
//        			break;
            
            case SDLK_ESCAPE:
            case SDLK_RCTRL:
              running = false;
              break;

#ifndef PANDORA
            case SDLK_f:
              if (event.key.keysym.mod & KMOD_CTRL)
              {
                // Works with X11 only
                SDL_WM_ToggleFullScreen(GuiScreen);
              }
              break;
#endif
          }
        }
#ifdef ANDROIDSDL
		/*
		 * Now that we are done polling and using SDL events we pass
		 * the leftovers to the SDLInput object to later be handled by
		 * the Gui. (This example doesn't require us to do this 'cause a
		 * label doesn't use input. But will do it anyway to show how to
		 * set up an SDL application with Guichan.)
		 */
		if (event.type == SDL_MOUSEMOTION ||
			event.type == SDL_MOUSEBUTTONDOWN ||
			event.type == SDL_MOUSEBUTTONUP)
		{
			// Filter emulated mouse events for Guichan, we wand absolute input
		}
		else
		{
			// Convert multitouch event to SDL mouse event
			static int x = 0, y = 0, buttons = 0, wx=0, wy=0, pr=0;
			SDL_Event event2;
			memcpy(&event2, &event, sizeof(event));
			if (event.type == SDL_JOYBALLMOTION &&
				event.jball.which == 0 &&
				event.jball.ball == 0)
			{
				event2.type = SDL_MOUSEMOTION;
				event2.motion.which = 0;
				event2.motion.state = buttons;
				event2.motion.xrel = event.jball.xrel - x;
				event2.motion.yrel = event.jball.yrel - y;
				if (event.jball.xrel!=0)
				{
				  x = event.jball.xrel;
				  y = event.jball.yrel;
				}
				event2.motion.x = x;
				event2.motion.y = y;
				//__android_log_print(ANDROID_LOG_INFO, "GUICHAN","Mouse motion %d %d btns %d", x, y, buttons);
				if (buttons == 0)
				{
					// Push mouse motion event first, then button down event
					input->pushInput(event2);
					buttons = SDL_BUTTON_LMASK;
					event2.type = SDL_MOUSEBUTTONDOWN;
					event2.button.which = 0;
					event2.button.button = SDL_BUTTON_LEFT;
					event2.button.state =  SDL_PRESSED;
					event2.button.x = x;
					event2.button.y = y;
					//__android_log_print(ANDROID_LOG_INFO, "GUICHAN","Mouse button %d coords %d %d", buttons, x, y);
				}
			}
			if (event.type == SDL_JOYBUTTONUP &&
				event.jbutton.which == 0 &&
				event.jbutton.button == 0)
			{
				// Do not push button down event here, because we need mouse motion event first
				buttons = 0;
				event2.type = SDL_MOUSEBUTTONUP;
				event2.button.which = 0;
				event2.button.button = SDL_BUTTON_LEFT;
				event2.button.state = SDL_RELEASED;
				event2.button.x = x;
				event2.button.y = y;
				//__android_log_print(ANDROID_LOG_INFO, "GUICHAN","Mouse button %d coords %d %d", buttons, x, y);
			}
			input->pushInput(event2);
		}
#else
        input->pushInput(event);
#endif
	    }
      // Now we let the Gui object perform its logic.
      globals::gui->logic();
      // Now we let the Gui object draw itself.
      globals::gui->draw();
      // Finally we update the screen.
      SDL_Flip(GuiScreen);
    }
  }

}


namespace widgets
{
  extern void readConfig();
  extern void writeConfig();
  extern void run_menuLoad_guichan(char *curr_path, int aLoadType);
  extern gcn::Window *window_load; 
  
  void show_settings_TabVolumes(void);
  void show_settings_TabMisc(void);
  void show_settings_TabDisplaySound(void);
  void show_settings_TabNetwork(void);
 
  void menuTabVolumes_Init(void);
  void menuTabVolumes_Exit(void);
  void menuTabMisc_Init(void);
  void menuTabMisc_Exit(void);
  void menuTabDisplaySound_Init(void);
  void menuTabDisplaySound_Exit(void);
  void menuTabNetwork_Init(void);
  void menuTabNetwork_Exit(void);
  void loadMenu_Init(void);
  void loadMenu_Exit(void);
  
  void show_settings();
  
  gcn::Color baseCol;
  gcn::Color baseColLabel;
  gcn::Container* top;
  gcn::contrib::SDLTrueTypeFont* font;

  // Presets
  
  // Main buttons
  gcn::Image *background_image;
  gcn::Icon* background;
  gcn::Image *background2_image;
  gcn::Icon* background2;
  gcn::Button* button_reset;
  gcn::Button* button_resume;
  gcn::Button* button_quit;
  gcn::TabbedArea* tabbedArea;

    // Tab-Dialog
  extern gcn::Container *tab_volumes;
  extern gcn::Container *tab_misc;
  extern gcn::Container *tab_displaysound; 
  extern gcn::Container *tab_network; 
    
  const int numTabs = 4;
  gcn::Tab *allTabs[numTabs];
  
  class QuitButtonActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
  			running = false;
			exit(0);
      }
  };
  QuitButtonActionListener* quitButtonActionListener;


  class ResetButtonActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
		writeConfig();
		running = false;
      }
  };
  ResetButtonActionListener* resetButtonActionListener;


  class ResumeButtonActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
    			running = false;
      }
  };
  ResumeButtonActionListener* resumeButtonActionListener;

  void init()
  {
    baseCol.r = 192;
    baseCol.g = 192;
    baseCol.b = 208;
    baseColLabel.r = baseCol.r;
    baseColLabel.g = baseCol.g;
    baseColLabel.b = baseCol.b;
    baseColLabel.a = 192;
    
    top = new gcn::Container();
    top->setDimension(gcn::Rectangle(0, 0, 640, 480));
    top->setBaseColor(baseCol);
    globals::gui->setTop(top);

    TTF_Init();
    font = new gcn::contrib::SDLTrueTypeFont("data/FreeSans.ttf", 16);	
    gcn::Widget::setGlobalFont(font);
	
    background_image = gcn::Image::load("data/background.jpg");
    background = new gcn::Icon(background_image);
    background2_image = gcn::Image::load("data/background2.jpg");
    background2 = new gcn::Icon(background2_image);	
	
  	//--------------------------------------------------
  	// Create main buttons
  	//--------------------------------------------------
    
  	button_quit = new gcn::Button("Quit");
  	button_quit->setSize(90,50);
    button_quit->setBaseColor(baseCol);
    button_quit->setId("Quit");
    quitButtonActionListener = new QuitButtonActionListener();
    button_quit->addActionListener(quitButtonActionListener);
    
  	button_reset = new gcn::Button("Start");
  	button_reset->setSize(90,50);
    button_reset->setBaseColor(baseCol);
  	button_reset->setId("Start");
    resetButtonActionListener = new ResetButtonActionListener();
    button_reset->addActionListener(resetButtonActionListener);

  	button_resume = new gcn::Button("Resume");
  	button_resume->setSize(90,50);
    button_resume->setBaseColor(baseCol);
  	button_resume->setId("Resume");
    resumeButtonActionListener = new ResumeButtonActionListener();
    button_resume->addActionListener(resumeButtonActionListener);

  	//--------------------------------------------------
    // Tabs
  	//--------------------------------------------------

    menuTabVolumes_Init();
	menuTabMisc_Init();
	menuTabDisplaySound_Init(); 
	menuTabNetwork_Init();

  	//--------------------------------------------------
    // Tab-Dialog
  	//--------------------------------------------------
    tabbedArea = new gcn::TabbedArea();
    tabbedArea->setSize(600, 370);
  	tabbedArea->setFocusable(false);
    tabbedArea->setBaseColor(baseCol);
    tabbedArea->setId("tabbedArea");
    for(int i=0; i<numTabs; ++i)
    {
      allTabs[i] = new gcn::Tab();
      allTabs[i]->setBaseColor(baseCol);
    }

	 allTabs[0]->setCaption(" Volumes ");
	 tabbedArea->addTab(allTabs[0], tab_volumes);
	 allTabs[1]->setCaption(" Memory/Misc ");
	 tabbedArea->addTab(allTabs[1], tab_misc);
	 allTabs[2]->setCaption(" Graphics/Sound ");
	 tabbedArea->addTab(allTabs[2], tab_displaysound);
	 allTabs[3]->setCaption(" Network ");
	 tabbedArea->addTab(allTabs[3], tab_network);
	
	loadMenu_Init(); 
	
  	//--------------------------------------------------
    // Place everything on main form
  	//--------------------------------------------------
    top->add(background, 0, 0);
    top->add(tabbedArea, 20, 20);
    top->add(button_reset, 210, 410);
//    top->add(button_resume, 320, 410);
    top->add(button_quit, 340, 410);
    top->add(window_load, 120, 90); 
	
  	//--------------------------------------------------
  	// Display values on controls
  	//--------------------------------------------------
  	show_settings();	
  }

  void halt()
  {
	menuTabVolumes_Exit();
	menuTabMisc_Exit();
	menuTabDisplaySound_Exit();
	menuTabNetwork_Exit();
	loadMenu_Exit(); 
	
    delete tabbedArea;
    delete button_reset;
    delete button_resume;
    delete button_quit;
	
	

    delete resumeButtonActionListener;
    delete resetButtonActionListener;
    delete quitButtonActionListener;

    delete background;
    delete background_image;
    delete background2;
    delete background2_image;
	
    delete font;
    delete top;
	
    for(int i=0; i<numTabs; ++i)
      delete allTabs[i];
  }

  //-----------------------------------------------
  // Start of helper functions
  //-----------------------------------------------
  void show_settings()
  {
    show_settings_TabVolumes();
	show_settings_TabMisc();
	show_settings_TabDisplaySound();
	show_settings_TabNetwork();
  }
  
} 

 int gui_open (void)
 {
#ifdef ANDROID	  
  SDL_ANDROID_SetScreenKeyboardShown(0);
#endif
   running = true;
   
   try
   {
    widgets::readConfig();
    sdl::init();
    widgets::init();
    sdl::run();
    widgets::halt();
    sdl::halt();
    SDL_JoystickClose (joy0);
#ifdef ANDROID	  
  SDL_ANDROID_SetScreenKeyboardShown(1);
#endif
   }

   // Catch all Guichan exceptions.
   catch (gcn::Exception e)
   {
       std::cout << e.getMessage() << std::endl;
       SDL_Quit();
   }
   // Catch all Std exceptions.
   catch (std::exception e)
   {
       std::cout << "Std exception: " << e.what() << std::endl;
       SDL_Quit();
   }
   // Catch all unknown exceptions.
   catch (...)
   {
       std::cout << "Unknown exception" << std::endl;
       SDL_Quit();
   }

     return -1;
 }
