#ifndef _sampleMenu_
#define _sampleMenu_
#include "MenuManager.h"
#include <avr/pgmspace.h>
#include <LiquidCrystal_I2C.h>


//LED SETUP
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*
Generated using LCD Menu Builder at http://lcd-menu-bulder.cohesivecomputing.co.uk/.
*/

enum sampleMenuCommandId
{
  mnuCmdBack = 0,
  mnuCmdTopItem1,
  mnuCmdTopItem2,
  mnuCmdSubItem1,
  mnuCmdSubItemA,
  mnuCmdSubItemB,
  mnuCmdSubItemC,
  mnuCmdResetToDefaults
};

PROGMEM const char sampleMenu_back[] = "Back";
PROGMEM const char sampleMenu_exit[] = "Exit";

PROGMEM const char sampleMenu_2_1_1[] = "1 Sub item A";
PROGMEM const char sampleMenu_2_1_2[] = "2 Sub item B";
PROGMEM const char sampleMenu_2_1_3[] = "3 Sub item C";
PROGMEM const MenuItem sampleMenu_List_2_1[] = {{mnuCmdSubItemA, sampleMenu_2_1_1}, {mnuCmdSubItemB, sampleMenu_2_1_2}, {mnuCmdSubItemC, sampleMenu_2_1_3}, {mnuCmdBack, sampleMenu_back}};

PROGMEM const char sampleMenu_2_1[] = "1 Sub item 1";
PROGMEM const MenuItem sampleMenu_List_2[] = {{mnuCmdSubItem1, sampleMenu_2_1, sampleMenu_List_2_1, menuCount(sampleMenu_List_2_1)}, {mnuCmdBack, sampleMenu_back}};

PROGMEM const char sampleMenu_1[] = "1 Top item 1";
PROGMEM const char sampleMenu_2[] = "2 Top item 2";
PROGMEM const char sampleMenu_3[] = "3 Reset";
PROGMEM const MenuItem sampleMenu_Root[] = {{mnuCmdTopItem1, sampleMenu_1}, {mnuCmdTopItem2, sampleMenu_2, sampleMenu_List_2, menuCount(sampleMenu_List_2)}, {mnuCmdResetToDefaults, sampleMenu_3}, {mnuCmdBack, sampleMenu_exit}};

/*
case mnuCmdTopItem1 :
  break;
case mnuCmdSubItemA :
  break;
case mnuCmdSubItemB :
  break;
case mnuCmdSubItemC :
  break;
case mnuCmdResetToDefaults :
  break;
*/

/*
<?xml version="1.0"?>
<RootMenu xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">
  <Config IdPrefix="mnuCmd" VarPrefix="sampleMenu" UseNumbering="true" IncludeNumberHierarchy="false"
          MaxNameLen="15" MenuBackFirstItem="false" BackText="Back" ExitText="Exit" AvrProgMem="true"/>
  <MenuItems>
    <Item Id="TopItem1" Name="Top item 1"/>
    <Item Id="TopItem2" Name="Top item 2">
      <MenuItems>
        <Item Id="SubItem1" Name="Sub item 1">
          <MenuItems>
            <Item Id="SubItemA" Name="Sub item A"/>
            <Item Id="SubItemB" Name="Sub item B"/>
            <Item Id="SubItemC" Name="Sub item C"/>
          </MenuItems>
        </Item>
      </MenuItems>
    </Item>
    <Item Id="ResetToDefaults" Name="Reset"/>
  </MenuItems>
</RootMenu>
*/
#endif

void setup(){
  lcd.begin();
  lcd.backlight();
  }

void loop(){
  
  }  
