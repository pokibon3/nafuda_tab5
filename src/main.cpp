#include <SD_MMC.h>
//#include <LittleFS.h>
#include <M5Unified.h>

#define MAX_FILES 100
String fileName[MAX_FILES];
uint16_t fileNum = 0;
int16_t fileSel  = 0;

//===========================================================
//	getFileNames() ： get File Name From SPIFFS
//===========================================================
static int getFileNames()
{
    int count = 0;
//    File root = SPIFFS.open("/");
    File root = SD_MMC.open("/");
    File fName = root.openNextFile();
    while (fName) {
        String file = fName.name();
        if (file.endsWith(".jpg") || file.endsWith(".jpeg")) {
            fileName[count] = "/" + file;
            count++;
        if (count >= MAX_FILES) break;
        }
        fName = root.openNextFile();
    }
    for (int i = 0; i < count; i++) {
        Serial.println(fileName[i]);
    }
    return count;
}

//===========================================================
//	drawFile() ： Draw jpg File to LCD
//===========================================================
bool drawFile(String filename)
{
    bool ret = false;
    M5.Lcd.startWrite();
    M5.Lcd.println(filename);
    ret = !M5.Lcd.drawJpgFile(SD_MMC, filename, 0, 0, M5.Display.width(),
                              M5.Display.height(), 0, 0, 0.0F, 0.0F,
                              middle_center);
    M5.Lcd.endWrite();

	return ret;
}

//===========================================================
//	setup() ： Arduino Setup
//===========================================================
void setup(void) {
    // シリアルモニタの初期化
    Serial.begin(115200);
    
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Lcd.setRotation(2);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.fillScreen(BLACK);

    // SDの初期化
    if (!SD_MMC.begin()) {
        M5.Lcd.println("SD Mount Failed");
        return;
    }
    fileNum = getFileNames();
    if (fileNum == 0) {
        M5.Lcd.println("No File");
        return;
    } else {
        drawFile(fileName[0]);
    }    
}
 
void loop(void) {
    M5.update();
    auto touch = M5.Touch.getDetail();
    if (touch.wasClicked()) {
//        M5.Speaker.tone(1600, 500);
        drawFile(fileName[fileSel]);    
        fileSel++;
        if (fileSel >= fileNum) {
            fileSel = 0;
        }
    }
}
