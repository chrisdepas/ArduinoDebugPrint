DebugPrint
=============

Simple debug print library, with printf support.
Note - Uses libprintf for printf support, see Dependencies

## Basic Usage

```cpp

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
```



## Disabling debug output
- To disable debug output, modify `DebugPrint.h` in this library, and comment 
  out the `#define DEBUG_SERIAL_OUT` line
- This is an Arduino IDE limitation - #define statements in a sketch aren't accessible in library code

## Dependencies
- [Libprintf](https://github.com/embeddedartistry/arduino-printf) by Embedded Artistry
    - This can be installed through Library Manager by searching for 'Libprintf'
    
    
