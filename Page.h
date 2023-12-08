/*
FILE: Page.h
BY: Zach Drury, David Schwab, Dylan Mordhorst
FOR: OS, Transy U, 2023
Purpose: Interface: Page object definition
*/

#include <iostream>

class Page{
    private:
        int pageNum;    //the page number
        int amountUsed;     //counter, shows times the frame has been used with current page

    public:
        Page();    //constructor
        int pageNumber();   //return pageNum
        void setNumber(int num);
        int getUsed();  //return amountUsed
        int incrementUsed();    //increment amountUsed, return new value
        void resetUsed();   //reset amountUsed to 0
        void pageCopy(Page copyPage);   //copy new page info into this page
};