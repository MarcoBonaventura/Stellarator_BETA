#include "CApp.h"

CApp CApp::Logger;

std::ofstream logger ("log.txt");

void CApp::OnLog(std::string file, int line, std::string messageText, std::string messageOUT) {

    /** enable or disable file log */
    LogFile = false;

    if (LogFile)
    {
        logger <<"File "<<file<<" @line: "<<line<<" >> "<<messageText<<" - "<<messageOUT<<std::endl;

        logger.flush();
    }

}

