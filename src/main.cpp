#include <SD_MMC.h>
//#include <LittleFS.h>
#include <M5Unified.h>

void setup(void) {
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

    // BMP画像の表示
    if (!M5.Lcd.drawJpgFile(SD_MMC,  "/image.jpg", 0, 0, M5.Display.width(),
                            M5.Display.height(), 0, 0, 0.0F, 0.0F,
                            middle_center)) {
      M5.Lcd.println("Image display failed!");
    }
}
 
void loop(void) {
    delay(1);
//    M5_UPDATE();
}
