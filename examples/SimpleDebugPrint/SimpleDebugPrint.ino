#include <DebugPrint.h>

/**
 * Basic DebugPrint library example code
 */
int a = 0;
float f = 0.5f;

void setup() {
    DBG.setup();
    // Optionally, specify another serial output:
    // DBG.setup(Serial2);
}

void loop() {
    DBG.printf("test %f %d\n", f, a);
    a++;
    f += 0.5f;
    
    DBG.println("normal serial println");
    DBG.print("normal serial print");
    DBG.write('\n');
    delay(1000);
}
