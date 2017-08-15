/*
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
#include <SDL/SDL_ttf.h>
#include <guichan/sdl.hpp>
#include "guichan/contrib/sdl/sdltruetypefont.hpp"
#include "rw_config.h"

namespace widgets
{
  extern std::string menu_ether;
  extern std::string menu_udptunnel;
  extern std::string menu_udpport;

  void show_settings_TabNetwork(void);
  extern void run_menuLoad_guichan(char *curr_path, int aLoadType);

  extern gcn::Color baseCol;
  extern gcn::Color baseColLabel;
  extern gcn::Container* top;
  extern gcn::TabbedArea* tabbedArea;
  extern gcn::Icon* background2;
  
#ifdef ANDROIDSDL
  extern gcn::contrib::SDLTrueTypeFont* font2;
#endif

  // Tab Main
  gcn::Container *tab_network;
  gcn::Window *group_network_type;
  gcn::RadioButton* radioButton_network_none;
  gcn::RadioButton* radioButton_network_slirp;
  gcn::RadioButton* radioButton_network_udptunnel;

  class NetworkTypeButtonActionListener : public gcn::ActionListener
  {
  public:
    void action(const gcn::ActionEvent& actionEvent)
    {
      if (actionEvent.getSource() == radioButton_network_none)
	{
	  menu_ether="";
	  menu_udptunnel="false";
	}
      else if (actionEvent.getSource() == radioButton_network_slirp)
	{
	  menu_ether="slirp";
	  menu_udptunnel="false";
	}
      else if (actionEvent.getSource() == radioButton_network_udptunnel)
	{	  
	  menu_ether="";
	  menu_udptunnel="true";
	}
      show_settings_TabNetwork();
    }
  };
  NetworkTypeButtonActionListener* networkTypeButtonActionListener;
 
  void menuTabNetwork_Init()
  {
    // Select CPU
    radioButton_network_none = new gcn::RadioButton("None", "radionetworktypegroup");
    radioButton_network_none->setPosition(5,10);
    radioButton_network_none->setId("none");
    radioButton_network_slirp = new gcn::RadioButton("Internet (slirp)", "radionetworktypegroup");
    radioButton_network_slirp->setPosition(5,40);
    radioButton_network_slirp->setId("slirp");
    radioButton_network_udptunnel = new gcn::RadioButton("UDP tunnel", "radionetworktypegroup");
    radioButton_network_udptunnel->setPosition(5,70);
    radioButton_network_udptunnel->setId("udptunnel");
    networkTypeButtonActionListener = new NetworkTypeButtonActionListener();
    radioButton_network_none->addActionListener(networkTypeButtonActionListener);
    radioButton_network_slirp->addActionListener(networkTypeButtonActionListener);
    radioButton_network_udptunnel->addActionListener(networkTypeButtonActionListener);
    group_network_type = new gcn::Window("Network type");
    group_network_type->setPosition(10,20);
    group_network_type->add(radioButton_network_none);
    group_network_type->add(radioButton_network_slirp);
    group_network_type->add(radioButton_network_udptunnel);
    group_network_type->setMovable(false);
    group_network_type->setSize(150,115);
    group_network_type->setBaseColor(baseCol);
	
    tab_network = new gcn::Container();
    tab_network->add(background2);
    tab_network->add(group_network_type);
    tab_network->setSize(600,340);
    tab_network->setBaseColor(baseCol);
  }
  
  
  void menuTabNetwork_Exit()
  {
    delete tab_network;
    delete group_network_type;
    delete radioButton_network_none;
    delete radioButton_network_slirp;
    delete radioButton_network_udptunnel;
  }
  
  
  void show_settings_TabNetwork()
  {
    if (menu_udptunnel=="true")
      radioButton_network_udptunnel->setSelected(true);
    else if (menu_ether=="slirp")
      radioButton_network_slirp->setSelected(true);
    else
      radioButton_network_none->setSelected(true);
  }  
}
