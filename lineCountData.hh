#pragma once

//Separate struct for data about files, allows us to simply add more functionality,
//without turning all code upside-down.
struct lineCountData
{
    ulong lines=0;
    ulong emptyLines=0;
    ulong nonEmptyLines = 0;
    ulong wordCount = 0;
    ulong letterCount = 0;


    lineCountData operator+(const lineCountData& r)
    {
        lineCountData retData;
        retData.lines=this->lines+r.lines;
        retData.emptyLines=this->emptyLines+r.emptyLines;
        retData.nonEmptyLines=this->nonEmptyLines+r.nonEmptyLines;
        retData.wordCount=this->wordCount+r.wordCount;
        retData.letterCount=this->letterCount+r.letterCount;


        return retData;
    }

    lineCountData operator+=(const lineCountData& r)
    {
        lineCountData retData;
        this->lines+=r.lines;
        this->emptyLines+=r.emptyLines;
        this->nonEmptyLines+=r.nonEmptyLines;
        this->wordCount+=r.wordCount;
        this->letterCount+=r.letterCount;

        return *this;
    }

    lineCountData& operator=(const lineCountData& r)
    {
        this->lines=r.lines;
        this->emptyLines=r.emptyLines;
        this->nonEmptyLines=r.nonEmptyLines;
        this->wordCount=r.wordCount;
        this->letterCount=r.letterCount;
        return *this;
    }
};