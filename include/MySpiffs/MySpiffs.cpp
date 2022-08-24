
#include "MySpiffs.h"

/** reading file in the spiffs
 * @return string content
 */
String MySpiffs::readFile()
{
    File file = SPIFFS.open(_path.c_str(), FILE_READ);

    String txt = "";
    while (file.available())
        txt = file.readString();

    file.close();

    // Serial.println("_readFile " + txt);
    return txt;
}

/** deleting file in the spiffs */
void MySpiffs::deleteFile()
{
    if (SPIFFS.remove(_path))
        Serial.println(F("- file deleted"));
    else
        Serial.println(F("- delete failed"));
}

/** Initialization */
void MySpiffs::begin(String path)
{
    _path = path;

    if (!SPIFFS.begin(true))
    {
        Serial.println(F("SPIFFS Mount Failed"));
        return;
    }
}

/** writing file in the spiffs
 * @param message content
 */
void MySpiffs::writeFile(String message)
{
    File file = SPIFFS.open(_path.c_str(), FILE_WRITE);

    if (!file)
    {
        Serial.println(F("- failed to open file for writing"));
        return;
    }

    if (file.print(message.c_str()))
        Serial.println(F("- file written"));
    else
        Serial.println(F("- write failed"));

    file.close();
}

/** append file in the spiffs
 * @param message content
 * @param _ln wish print or println
 */
void MySpiffs::appendFile(String message, String _ln)
{
    File file = SPIFFS.open(_path.c_str(), FILE_APPEND);

    if (!file)
    {
        Serial.println(F("- failed to open file for writing"));
        return;
    }

    if (_ln == "")
    {
        if (file.print(message.c_str()))
            Serial.println(F("- file appended"));
        else
            Serial.println(F("- append failed"));
    }
    else
    {
        if (file.println(message.c_str()))
            Serial.println(F("- file appended \n"));
        else
            Serial.println(F("- append failed"));
    }

    file.close();
}
