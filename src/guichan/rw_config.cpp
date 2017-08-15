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

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
//#include "conio.h"

using namespace std;
namespace widgets
{
	std::string menuFileDisk[4];
	string menu_extfs;
	string menu_seriala;
	string menu_serialb;
	string menu_udptunnel;
	string menu_udpport;
	string menu_ether;
    string menu_bootdrive;
	string menu_bootdriver;
	string menu_ramsize;
	string menu_frameskip;
	string menu_modelid;
	string menu_cpu;
	string menu_fpu;
	string menu_nocdrom;
	string menu_nosound;
	string menu_noclipconversion;
	string menu_nogui;
	string menu_jit;
	string menu_jitfpu;
	string menu_jitdebug;
	string menu_jitcachesize;
	string menu_jitlazyflush;
	string menu_jitinline;
	string menu_keyboardtype;
	string menu_keycodes;
	string menu_mousewheelmode;
	string menu_mousewheellines;
	string menu_dsp;
	string menu_mixer;
	string menu_idlewait;
	string menu_ignoresegv;
	string menu_rom;
	string menu_screen;
	
	char* prefsName=".basilisk_ii_prefs";

void defConfig()
{
	for (int i=0; i<4; i++)
		menuFileDisk[i]="";
	menu_extfs="/";
	menu_seriala="/dev/ttyS0";
	menu_serialb="/dev/ttyS1";
	menu_udptunnel="false";
	menu_udpport="6066";
	menu_bootdrive="0";
	menu_bootdriver="0";
	menu_ramsize="8388608";
	menu_frameskip="6";
	menu_modelid="5";
	menu_cpu="3";
	menu_fpu="false";
	menu_nocdrom="false";
	menu_nosound="false";
	menu_noclipconversion="false";
	menu_nogui="false";
	menu_jit="false";
	menu_jitfpu="false";
	menu_jitdebug="false";
	menu_jitcachesize="0";
	menu_jitlazyflush="false";
	menu_jitinline="false";
	menu_keyboardtype="5";
	menu_keycodes="false";
	menu_mousewheelmode="1";
	menu_mousewheellines="3";
	menu_dsp="/dev/dsp";
	menu_mixer="/dev/mixer";
	menu_idlewait="true";
	menu_ignoresegv="true";
	menu_rom="Mac_OS.ROM";
	menu_screen="win/640/480";
	menu_ether = "";
}
	
void readConfig()
{
	char readed_string[99];
	char current_string[99];
	char char1,char2,char3,char4;
	string prev_string;
	int lenght;
	int disk_n;
	disk_n=0;
	defConfig();
	ifstream myfile;
	myfile.open(prefsName);
	if (!(myfile.is_open()))
		{
			cout << "Unable to open file.";
			return;
		}
	while (!myfile.eof())
	{
		myfile>>readed_string;
		strcpy(current_string,readed_string);
		if (prev_string==string("disk") && disk_n < 4)
		{
			menuFileDisk[disk_n]=current_string;
			disk_n++;
		}
		if (prev_string==string("extfs"))
			menu_extfs=current_string;
		if (prev_string==string("seriala"))
			menu_seriala=current_string;
		if (prev_string==string("serialb"))
			menu_serialb=current_string;
		if (prev_string==string("udptunnel"))
			menu_udptunnel=current_string;
		if (prev_string==string("udpport"))
			menu_udpport=current_string;
		if (prev_string==string("bootdrive"))
			menu_bootdrive=current_string;
		if (prev_string==string("bootdriver"))
			menu_bootdriver=current_string;
		if (prev_string==string("ramsize"))
			menu_ramsize=current_string;
		if (prev_string==string("frameskip"))
			menu_frameskip=current_string;
		if (prev_string==string("modelid"))
			menu_modelid=current_string;
		if (prev_string==string("cpu"))
			menu_cpu=current_string;
		if (prev_string==string("fpu"))
			menu_fpu=current_string;
		if (prev_string==string("nocdrom"))
			menu_nocdrom=current_string;
		if (prev_string==string("nosound"))
			menu_nosound=current_string;
		if (prev_string==string("noclipconversion"))
			menu_noclipconversion=current_string;
		if (prev_string==string("nogui"))
			menu_nogui=current_string;
		if (prev_string==string("jit"))
			menu_jit=current_string;
		if (prev_string==string("jitfpu"))
			menu_jitfpu=current_string;
		if (prev_string==string("jitdebug"))
			menu_jitdebug=current_string;
		if (prev_string==string("jitcachesize"))
			menu_jitcachesize=current_string;
		if (prev_string==string("jitlazyflush"))
			menu_jitlazyflush=current_string;
		if (prev_string==string("jitinline"))
			menu_jitinline=current_string;
		if (prev_string==string("keyboardtype"))
			menu_keyboardtype=current_string;
		if (prev_string==string("mousewheelmode"))
			menu_mousewheelmode=current_string;
		if (prev_string==string("mousewheellines"))
			menu_mousewheellines=current_string;
		if (prev_string==string("dsp"))
			menu_dsp=current_string;
		if (prev_string==string("mixer"))
			menu_mixer=current_string;
		if (prev_string==string("ignoresegv"))
			menu_ignoresegv=current_string;
		if (prev_string==string("idlewait"))
			menu_idlewait=current_string;
		if (prev_string==string("rom"))
			menu_rom=current_string;			
		if (prev_string==string("screen"))
			menu_screen=current_string;
		if (prev_string==string("ether"))
			menu_ether=current_string;
		prev_string=readed_string;
	}
	myfile.close();
}

void writeConfig()
{
	char saved_string[2048];
	ofstream myfile;
	myfile.open(prefsName);
	strcpy(saved_string,"");
	for (int i=0; i<4; i++)
	{
		if (menuFileDisk[i]!="")
		{
			strcat(saved_string,"disk ");
			strcat(saved_string,menuFileDisk[i].c_str());
			strcat(saved_string,"\n");
		}
	}
	strcat(saved_string,"extfs ");
	strcat(saved_string,menu_extfs.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"seriala ");
	strcat(saved_string,menu_seriala.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"serialb ");
	strcat(saved_string,menu_serialb.c_str());
	strcat(saved_string,"\n");
	if (menu_ether != "")
	{
		strcat(saved_string,"ether ");
		strcat(saved_string,menu_ether.c_str());
		strcat(saved_string,"\n");
	}
	strcat(saved_string,"udptunnel ");
	strcat(saved_string,menu_udptunnel.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"udpport ");
	strcat(saved_string,menu_udpport.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"bootdrive ");
	strcat(saved_string,menu_bootdrive.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"bootdriver ");
	strcat(saved_string,menu_bootdriver.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"ramsize ");
	strcat(saved_string,menu_ramsize.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"frameskip ");
	strcat(saved_string,menu_frameskip.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"modelid ");
	strcat(saved_string,menu_modelid.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"cpu ");
	strcat(saved_string,menu_cpu.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"fpu ");
	strcat(saved_string,menu_fpu.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"nocdrom ");
	strcat(saved_string,menu_nocdrom.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"nosound ");
	strcat(saved_string,menu_nosound.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"noclipconversion ");
	strcat(saved_string,menu_noclipconversion.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"nogui ");
	strcat(saved_string,menu_nogui.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"jit ");
	strcat(saved_string,menu_jit.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"jitfpu ");
	strcat(saved_string,menu_jitfpu.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"jitdebug ");
	strcat(saved_string,menu_jitdebug.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"jitcachesize ");
	strcat(saved_string,menu_jitcachesize.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"jitlazyflush ");
	strcat(saved_string,menu_jitlazyflush.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"jitinline ");
	strcat(saved_string,menu_jitinline.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"keyboardtype ");
	strcat(saved_string,menu_keyboardtype.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"keycodes ");
	strcat(saved_string,menu_keycodes.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"mousewheelmode ");
	strcat(saved_string,menu_mousewheelmode.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"mousewheellines ");
	strcat(saved_string,menu_mousewheellines.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"dsp ");
	strcat(saved_string,menu_dsp.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"mixer ");
	strcat(saved_string,menu_mixer.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"ignoresegv ");
	strcat(saved_string,menu_ignoresegv.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"idlewait ");
	strcat(saved_string,menu_idlewait.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"rom ");
	strcat(saved_string,menu_rom.c_str());
	strcat(saved_string,"\n");
	strcat(saved_string,"screen ");
	strcat(saved_string,menu_screen.c_str());
	strcat(saved_string,"\n");
	myfile<<saved_string;
	myfile.close();
}
}
