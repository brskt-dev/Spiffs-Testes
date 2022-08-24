#pragma once

#include <SPIFFS.h>
#include <Arduino.h>

class MySpiffs
{
private:
    String _path;

public:
    String readFile();
    void deleteFile();
    void begin(String path);
    void writeFile(String message);
    void appendFile(String message, String _ln = "");
};
