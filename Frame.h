/*
FILE: Frame.h
BY: Zach Drury, David Schwab, Dylan Mordhorst
FOR: OS, Transy U, 2023
Purpose: Interface: Frame object definition
*/

#include "Page.h"

class Frame{
    private:

        bool pageLoaded;    //returns T or F whether frame contains a page
        Page activePage;    //current page loaded in this frame
        int frameSize;  //constant size of frame


    public:

        Frame();    //frame created with default framesize

        void setSize(int newSize);  //frame size set to different size

        bool hasPage(); //return pageLoaded

        Page getPage();     //return stored page number
        void setPage(Page newPage);     //sets new page in frame
        void addHasPage();   //sets pageLoaded to true

        void printData();   //print all frame info
};