#include <algorithm>
#ifdef ANDROIDSDL
#include <android/log.h>
#endif
#include <guichan.hpp>
#include <iostream>
#include <SDL/SDL_ttf.h>
#include <guichan/sdl.hpp>
#include "guichan/contrib/sdl/sdltruetypefont.hpp"
#include <string>
#include "rw_config.h"

namespace widgets
{
  extern std::string menuFileDisk[4];
  extern std::string menu_extfs;
  extern std::string menu_nocdrom;
  void run_menuLoad_guichan(char *curr_path, int aLoadType);
  void show_settings_TabVolumes(void);
  extern gcn::Color baseCol;
  extern gcn::Container* top;
  extern gcn::TabbedArea* tabbedArea;
  extern gcn::Icon* background2;
  extern gcn::Widget* activateAfterClose;
    
  // Tab Volumes
  gcn::Container *tab_volumes;
  gcn::ListBox* volumeListBox;
  gcn::ScrollArea* volumeScrollArea;
  gcn::Button* button_add;
  gcn::Button* button_create;
  gcn::Button* button_remove;
  gcn::Button* button_hostfs;
  gcn::TextField* textField_hostfs;
  gcn::CheckBox* checkBox_nocdrom; 

    class VolumeListModel : public gcn::ListModel
    {
    public:
        int getNumberOfElements()
        {
            return 4;
        }

        std::string getElementAt(int i)
        {
            return menuFileDisk[i];
        }
    };
    VolumeListModel volumeListModel;

  class AddButtonActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
	    if (actionEvent.getSource() == button_add)
	    {
	      	activateAfterClose = button_add;
     		run_menuLoad_guichan(currentDir, MENU_ADD_VOLUME);
  	    }
      }
  };
  AddButtonActionListener* addButtonActionListener;

  class RemoveButtonActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
	    if (actionEvent.getSource() == button_remove)
	    {
	      	activateAfterClose = button_remove;
			int selectedItem = 0;
#if VIDEO_PLUS_CRASHES
			selectedItem=volumeListBox->getSelected();
#endif
			menuFileDisk[selectedItem]="";
			for (int i=3; i>0; i--)
			{
				if ((menuFileDisk[i-1]=="") && (menuFileDisk[i]!=""))
				{
					menuFileDisk[i-1]=menuFileDisk[i];
					menuFileDisk[i]="";
				}
			}
			for (int i=0; i<3; i++)
			{
				if ((menuFileDisk[i]=="") && (menuFileDisk[i+1]!=""))
				{
					menuFileDisk[i]=menuFileDisk[i+1];
					menuFileDisk[i+1]="";
				}
			}
			
  	    }
      }
  };
  RemoveButtonActionListener* removeButtonActionListener;

  class HostfsButtonActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
	    if (actionEvent.getSource() == button_hostfs)
	    {
	      	activateAfterClose = button_hostfs;
     		run_menuLoad_guichan(currentDir, MENU_ADD_DIR);
  	    }
      }
  };
  HostfsButtonActionListener* hostfsButtonActionListener;

  class NocdromActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
	    if (actionEvent.getSource() == checkBox_nocdrom)
	       if (checkBox_nocdrom->isSelected())
				menu_nocdrom="true";
	       else
				menu_nocdrom="false";
      }
  };
  NocdromActionListener* nocdromActionListener;
  
  void menuTabVolumes_Init()
  {
#if VIDEO_PLUS_CRASHES
    volumeListBox = new gcn::ListBox(&volumeListModel);
    volumeListBox->setId("volumeList");
    volumeListBox->setSize(650,150);
    volumeListBox->setBaseColor(baseCol);
    volumeListBox->setWrappingEnabled(true);
    volumeScrollArea = new gcn::ScrollArea(volumeListBox);
    volumeScrollArea->setFrameSize(1);
    volumeScrollArea->setPosition(10,10);
    volumeScrollArea->setSize(580,100);
    volumeScrollArea->setScrollbarWidth(20);
    volumeScrollArea->setBaseColor(baseCol);
#endif
  	button_add = new gcn::Button("Add");
  	button_add->setSize(80,30);
  	button_add->setPosition(10,125);
    button_add->setBaseColor(baseCol);
    button_add->setId("Add");
    addButtonActionListener = new AddButtonActionListener();
  	button_add->addActionListener(addButtonActionListener);
  	button_create = new gcn::Button("Create");
  	button_create->setSize(80,30);
  	button_create->setPosition(255,125);
    button_create->setBaseColor(baseCol);
    button_create->setId("Create");
  	button_remove = new gcn::Button("Remove");
  	button_remove->setSize(80,30);
  	button_remove->setPosition(500,125);
    button_remove->setBaseColor(baseCol);
    button_remove->setId("Remove");
    removeButtonActionListener = new RemoveButtonActionListener();
  	button_remove->addActionListener(removeButtonActionListener);

  	button_hostfs = new gcn::Button("HostFS Dir");
  	button_hostfs->setSize(85,30);
  	button_hostfs->setPosition(10,185);
    button_hostfs->setBaseColor(baseCol);
    button_hostfs->setId("HostFS");
    hostfsButtonActionListener = new HostfsButtonActionListener();
  	button_hostfs->addActionListener(hostfsButtonActionListener);	
	
  	textField_hostfs = new gcn::TextField("                                                            ");
  	textField_hostfs->setSize(450,22);
  	textField_hostfs->setPosition(110,190);
  	textField_hostfs->setEnabled(false);
    textField_hostfs->setBaseColor(baseCol);
	
	checkBox_nocdrom = new gcn::CheckBox("Disable CD-ROM driver");
	checkBox_nocdrom->setPosition(10,240);
	checkBox_nocdrom->setId("nocdrom");
	checkBox_nocdrom->setBaseColor(baseCol);
	nocdromActionListener = new NocdromActionListener();
	checkBox_nocdrom->addActionListener(nocdromActionListener);
	
    tab_volumes = new gcn::Container();
	tab_volumes->add(background2);
#if VIDEO_PLUS_CRASHES
	tab_volumes->add(volumeScrollArea);
#endif
	tab_volumes->add(button_add);
	tab_volumes->add(button_remove);
	tab_volumes->add(button_create);
	tab_volumes->add(button_hostfs);
	tab_volumes->add(textField_hostfs);
	tab_volumes->add(checkBox_nocdrom);
  	tab_volumes->setSize(600,340);
    tab_volumes->setBaseColor(baseCol);
  }
  

  void menuTabVolumes_Exit()
  {
    delete tab_volumes;
#if VIDEO_PLUS_CRASHES
    delete volumeListBox;
    delete volumeScrollArea;
#endif
    delete button_add;
    delete button_create;
    delete button_remove;
    delete button_hostfs;
    delete textField_hostfs;
    delete checkBox_nocdrom; 
	
    delete addButtonActionListener;
    delete removeButtonActionListener;
    delete hostfsButtonActionListener;
    delete nocdromActionListener;
  }

  void show_settings_TabVolumes()
  {
		textField_hostfs->setText(menu_extfs);
	if (menu_nocdrom=="true")
	    checkBox_nocdrom->setSelected(true);
	else
	    checkBox_nocdrom->setSelected(false);
  }

}
