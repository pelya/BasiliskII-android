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
  extern std::string menu_cpu;
  extern std::string menu_fpu;
  extern std::string menu_ramsize;
  extern std::string menu_modelid;
  extern std::string menu_idlewait;
  extern std::string menu_rom;
  extern std::string menu_ignoresegv;

  void show_settings_TabMisc(void);
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
  gcn::Container *tab_misc;
  gcn::Window *group_cpu;
  gcn::RadioButton* radioButton_cpu68020;
  gcn::RadioButton* radioButton_cpu68030;
  gcn::RadioButton* radioButton_cpu68040;
  gcn::Window *group_modelid;
  gcn::RadioButton* radioButton_modelid5;
  gcn::RadioButton* radioButton_modelid14;
  gcn::CheckBox* checkBox_fpu; 
  gcn::CheckBox* checkBox_idlewait;
  gcn::CheckBox* checkBox_ignoresegv;
  gcn::Button* button_rom;
  gcn::TextField* textField_rom;

  gcn::Label* label_rammem;
  gcn::Container* backgrd_rammem;
  gcn::Label* label_ramsize;
  gcn::Container* backgrd_ramsize;  
  gcn::Slider* slider_ramsize;  

  class CPUButtonActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
  	    if (actionEvent.getSource() == radioButton_cpu68020)
			menu_cpu="2";
		else if (actionEvent.getSource() == radioButton_cpu68030)
			menu_cpu="3";
		else if (actionEvent.getSource() == radioButton_cpu68040)
			menu_cpu="4";
      }
  };
  CPUButtonActionListener* cpuButtonActionListener;

  class ModelidButtonActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
  	    if (actionEvent.getSource() == radioButton_modelid5)
			menu_modelid="5";
		else if (actionEvent.getSource() == radioButton_modelid14)
			menu_modelid="14";
      }
  };
  ModelidButtonActionListener* modelidButtonActionListener;
  
  class FpuActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
	    if (actionEvent.getSource() == checkBox_fpu)
	       if (checkBox_fpu->isSelected())
				menu_fpu="true";
	       else
				menu_fpu="false";
      }
  };
  FpuActionListener* fpuActionListener;
  
  class IdlewaitActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
	    if (actionEvent.getSource() == checkBox_idlewait)
	       if (checkBox_idlewait->isSelected())
				menu_idlewait="true";
	       else
				menu_idlewait="false";
      }
  };
  IdlewaitActionListener* idlewaitActionListener;
  
  class IgnoresegvActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
	    if (actionEvent.getSource() == checkBox_ignoresegv)
	       if (checkBox_ignoresegv->isSelected())
				menu_ignoresegv="true";
	       else
				menu_ignoresegv="false";
      }
  };
  IgnoresegvActionListener* ignoresegvActionListener;
  
  class RomButtonActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
	    if (actionEvent.getSource() == button_rom)
	    {
     		run_menuLoad_guichan(currentDir, MENU_SELECT_ROM);
  	    }
      }
  };
  RomButtonActionListener* romButtonActionListener;
 
  class RamsizeSliderActionListener : public gcn::ActionListener
  {
    public:
      void action(const gcn::ActionEvent& actionEvent)
      {
		std::string ramsize_value[9]={"2097152","4194304","8388608","16777216","33554432","67108864","134217728","268435456","536870912"};
 	    if (actionEvent.getSource() == slider_ramsize) {
    		menu_ramsize=ramsize_value[int(slider_ramsize->getValue())];
		}	
    		show_settings_TabMisc();
      }
  };
  RamsizeSliderActionListener* ramsizeSliderActionListener;
 
  void menuTabMisc_Init()
  {
  	// Select CPU
  	radioButton_cpu68020 = new gcn::RadioButton("68020", "radiocpugroup");
	radioButton_cpu68020->setPosition(5,10);
  	radioButton_cpu68020->setId("68020");
	radioButton_cpu68030 = new gcn::RadioButton("68030", "radiocpugroup");
	radioButton_cpu68030->setPosition(5,40);
  	radioButton_cpu68030->setId("68030");
	radioButton_cpu68040 = new gcn::RadioButton("68040", "radiocpugroup");
	radioButton_cpu68040->setPosition(5,70);
  	radioButton_cpu68040->setId("68040");
	cpuButtonActionListener = new CPUButtonActionListener();
  	radioButton_cpu68020->addActionListener(cpuButtonActionListener);
  	radioButton_cpu68030->addActionListener(cpuButtonActionListener);
	radioButton_cpu68040->addActionListener(cpuButtonActionListener);
  	group_cpu = new gcn::Window("CPU");
  	group_cpu->setPosition(10,20);
  	group_cpu->add(radioButton_cpu68020);
  	group_cpu->add(radioButton_cpu68030);
	group_cpu->add(radioButton_cpu68040);
  	group_cpu->setMovable(false);
  	group_cpu->setSize(90,115);
    group_cpu->setBaseColor(baseCol);

	// Select ModelID
  	radioButton_modelid5 = new gcn::RadioButton("Mac IIci (MacOS 7.x)", "radiomodelidgroup");
	radioButton_modelid5->setPosition(5,10);
  	radioButton_modelid5->setId("modelid5");
	radioButton_modelid14 = new gcn::RadioButton("Quadra 900 (MaoOS 8.x)", "radiomodelidgroup");
	radioButton_modelid14->setPosition(5,40);
  	radioButton_modelid14->setId("modelid14");
	modelidButtonActionListener = new ModelidButtonActionListener();
  	radioButton_modelid5->addActionListener(modelidButtonActionListener);
  	radioButton_modelid14->addActionListener(modelidButtonActionListener);
	group_modelid = new gcn::Window("Mac Model ID");
  	group_modelid->setPosition(115,20);
  	group_modelid->add(radioButton_modelid5);
  	group_modelid->add(radioButton_modelid14);
  	group_modelid->setMovable(false);
  	group_modelid->setSize(220,85);
    group_modelid->setBaseColor(baseCol);
	
	// Select FPU
	checkBox_fpu = new gcn::CheckBox("use FPU");
	checkBox_fpu->setPosition(10,170);
	checkBox_fpu->setId("fpu");
	checkBox_fpu->setBaseColor(baseCol);
	fpuActionListener = new FpuActionListener();
	checkBox_fpu->addActionListener(fpuActionListener);
	
	// Select idlewait
	checkBox_idlewait = new gcn::CheckBox("Don't use CPU when idle");
	checkBox_idlewait->setPosition(10,210);
	checkBox_idlewait->setId("idlewait");
	checkBox_idlewait->setBaseColor(baseCol);
	idlewaitActionListener = new IdlewaitActionListener();
	checkBox_idlewait->addActionListener(idlewaitActionListener);

	// Select ignoresegv
	checkBox_ignoresegv = new gcn::CheckBox("Ignore Illegal Memory Accesses");
	checkBox_ignoresegv->setPosition(10,250);
	checkBox_ignoresegv->setId("ignoresegv");
	checkBox_ignoresegv->setBaseColor(baseCol);
	ignoresegvActionListener = new IgnoresegvActionListener();
	checkBox_ignoresegv->addActionListener(ignoresegvActionListener);
	
	// Select ROM
  	button_rom = new gcn::Button("ROM file");
  	button_rom->setSize(80,30);
  	button_rom->setPosition(10,295);
    button_rom->setBaseColor(baseCol);
    button_rom->setId("rom");
    romButtonActionListener = new RomButtonActionListener();
  	button_rom->addActionListener(romButtonActionListener);	
	
  	textField_rom = new gcn::TextField("                                                            ");
  	textField_rom->setSize(450,22);
  	textField_rom->setPosition(110,300);
  	textField_rom->setEnabled(false);
    textField_rom->setBaseColor(baseCol);
	
	// setelct RamSize
  	label_rammem = new gcn::Label("RAM Size");
  	label_rammem->setPosition(4, 2);
  	backgrd_rammem = new gcn::Container();
  	backgrd_rammem->setOpaque(true);
  	backgrd_rammem->setBaseColor(baseColLabel);
  	backgrd_rammem->setPosition(115, 130);
  	backgrd_rammem->setSize(80, 23);
    backgrd_rammem->add(label_rammem);
	slider_ramsize = new gcn::Slider(0, 8);
	slider_ramsize->setPosition(210,130);
	slider_ramsize->setSize(150, 21);
	slider_ramsize->setMarkerLength(24);
	slider_ramsize->setStepLength(1);
	slider_ramsize->setId("RAMSize");
	ramsizeSliderActionListener = new RamsizeSliderActionListener();
	slider_ramsize->addActionListener(ramsizeSliderActionListener);
	label_ramsize = new gcn::Label("None     ");
  	label_ramsize->setPosition(4, 2);
	backgrd_ramsize = new gcn::Container();
  	backgrd_ramsize->setOpaque(true);
  	backgrd_ramsize->setBaseColor(baseColLabel);
  	backgrd_ramsize->setPosition(375, 130);
  	backgrd_ramsize->setSize(60, 23);
    backgrd_ramsize->add(label_ramsize); 
	
  	tab_misc = new gcn::Container();
	tab_misc->add(background2);
	tab_misc->add(group_cpu);
	tab_misc->add(checkBox_fpu);
	tab_misc->add(checkBox_idlewait);
	tab_misc->add(checkBox_ignoresegv);
	tab_misc->add(group_modelid);
	tab_misc->add(button_rom);
	tab_misc->add(textField_rom);
  	tab_misc->add(backgrd_rammem);
  	tab_misc->add(slider_ramsize);
  	tab_misc->add(backgrd_ramsize);
	tab_misc->setSize(600,340);
    tab_misc->setBaseColor(baseCol);
  }
  
  
  void menuTabMisc_Exit()
  {
    delete tab_misc;
    delete group_cpu;
    delete radioButton_cpu68020;
    delete radioButton_cpu68030;
	delete radioButton_cpu68040;
	delete group_modelid;
	delete radioButton_modelid5;
	delete radioButton_modelid14;
	delete checkBox_fpu; 
	delete checkBox_idlewait;
	delete checkBox_ignoresegv;
	delete button_rom;
	delete textField_rom;
	delete label_ramsize;
	delete backgrd_rammem;
	delete label_rammem;
	delete backgrd_ramsize;  
	delete slider_ramsize;  

    delete modelidButtonActionListener;
    delete cpuButtonActionListener;
    delete fpuActionListener;
    delete idlewaitActionListener;
        delete ignoresegvActionListener;
	delete romButtonActionListener;
	delete ramsizeSliderActionListener;
  }
  
  
  void show_settings_TabMisc()
  {
	textField_rom->setText(menu_rom);
  	if (menu_cpu=="2")
	    radioButton_cpu68020->setSelected(true);
	else if (menu_cpu=="3")
	    radioButton_cpu68030->setSelected(true);
	else if (menu_cpu=="4")
	    radioButton_cpu68040->setSelected(true);
		
	if (menu_modelid=="5")
		radioButton_modelid5->setSelected(true);
	else if (menu_modelid=="14")
		radioButton_modelid14->setSelected(true);

	if (menu_fpu=="true")
	    checkBox_fpu->setSelected(true);
	else
	    checkBox_fpu->setSelected(false);

	if (menu_idlewait=="true")
	    checkBox_idlewait->setSelected(true);
	else
	    checkBox_idlewait->setSelected(false);
		
	if (menu_ignoresegv=="true")
	    checkBox_ignoresegv->setSelected(true);
	else
	    checkBox_ignoresegv->setSelected(false);

	const char *MemSize_list[] = { "2Mb", "4Mb", "8Mb", "16Mb", "32Mb", "64Mb", "128Mb", "256Mb", "512Mb"};
	int memsize=std::atoi(menu_ramsize.c_str());
	switch (memsize)
	{
		case 2097152:
			slider_ramsize->setValue(0);
			label_ramsize->setCaption("2Mb");
			break;
		case 4194304:
			slider_ramsize->setValue(1);
			label_ramsize->setCaption("4Mb");
			break;
		case 8388608:
			slider_ramsize->setValue(2);
			label_ramsize->setCaption("8Mb");
			break;
		case 16777216:
			slider_ramsize->setValue(3);
			label_ramsize->setCaption("16Mb");
			break;
		case 33554432:
			slider_ramsize->setValue(4);
			label_ramsize->setCaption("32Mb");
			break;
		case 67108864:
			slider_ramsize->setValue(5);
			label_ramsize->setCaption("64Mb");
			break;
		case 134217728:
			slider_ramsize->setValue(6);
			label_ramsize->setCaption("128Mb");
			break;
		case 268435456:
			slider_ramsize->setValue(7);
			label_ramsize->setCaption("256Mb");
			break;
		case 536870912:
			slider_ramsize->setValue(8);
			label_ramsize->setCaption("512Mb");
			break;
		default:
			break;
	}
  }
  
}
