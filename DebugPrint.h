#ifndef __DEBUGPRINT_H__
#define __DEBUGPRINT_H__

/** 
 * Chris De Pasquale
 * Nov. 2019
 * 
 * Serial debug output util wrapper. 
 * 
 * Includes LibPrintf, which redirects 'printf' calls to Serial by default
 * 
 * Usage:
 *     // in setup()
 *     DBG::setup();
 *     // or, if using Serial2 for example
 *     DBG::setup(Serial2);
 *     
 *     // to print output
 *     DBG::print("Print w/o newline");
 *     DBG::println("Print w/ newline");
 *     DBG::printf("With %formatting! %d", 0.1, 1);
 *     
 *     // on fatal error
 *     DBG::exit("Fatal: something bad happened. Here are some numbers: %d %d", 1, 2);
 *     DBG::exit(); // prints 'FATAL ERROR'
 * 
 * Comment out the 'DEBUG_SERIAL_OUT' definition to enable/disable
 * debug printing to serial. 
 * 
 * When commented out, implementation and printf library will be
 * removed, stubs will remain to avoid compilation errors.
 * 
 * These stubs should be optimized away by the compiler.
 */
#define DEBUG_SERIAL_OUT


#ifdef DEBUG_SERIAL_OUT

    #include <stdarg.h>
    #include <LibPrintf.h>
    #include <HardwareSerial.h>
    
    // Forward declaration
    class DebugPrint;
    
    /**
     * Global debug printer object.
     */
    extern DebugPrint DBG;
    
    
    class DebugPrint {
    
        static const long DEFAULT_BAUD = 115200;
        
        HardwareSerial* g_pSerial = &Serial;
    
    public:
    
        void setup() {
            setup(Serial, DEFAULT_BAUD);
        }
        
        void setup(HardwareSerial& serial) {
            setup(serial, DEFAULT_BAUD);   
        }
        
        void setup(HardwareSerial& serial, long baud) {
            serial.begin(baud);
            g_pSerial = &serial;
            printf_init(serial);
        }
        
        /** Write an unformatted string to serial output  */
        void print(const char* out) {
            g_pSerial->print(out);
        }

        /** Write an unformatted string to serial output, a newline is appended automatically */
        void println(const char* out) {
            g_pSerial->println(out);    
        }
        
        /** Write a newline to serial output */
        void println() {
            g_pSerial->println();
        }
    
        /** Util - Print byte values in hex, with a newline at the end*/
        void writeln(const char* buf, int len) {
            for (int i = 0; i < len; i++) {
                printf("0x%X ", (unsigned char)buf[i]);
            }
            print("\n");
        }
    
        /** Util - Print byte values in decimal, with a newline at the end*/
        void dwriteln(const char* buf, int len) {
            for (int i = 0; i < len; i++) {
                printf("%hhu ", (unsigned char)buf[i]);
            }
            print("\n");
        }

        /** Write a single character to serial output */
        void write(char c) {
            g_pSerial->write(c);
        }
    
        /** 
         * Formatted print, includes support for floats etc. 
         * See libprintf documentation for more information 
         */
        void printf(const char* fmt, ...) {
            va_list args;
            va_start(args, fmt);
    
            // Forward to printf
            vprintf(fmt, args);
            
            va_end(args);
        }
    
        /**
         * Util - print an error and exit 
         * TODO: This should print line and file info
         */
        void exit() {
            print("FATAL ERROR");
    
            // Loop until reset
            while(1){}
        }
        
        /**
         * Util - Exit and print a formatted error string
         * 'FATAL ERROR: ' is prepended to the error string
         */
        void exit(const char* fmt, ...) {
            print("FATAL ERROR: ");
            
            va_list args;
            va_start(args, fmt);
    
            // Forward to printf
            vprintf(fmt, args);
            
            va_end(args);
    
            // Loop until reset
            while(1){}
        }
    };
        
#else

    // Stub debug namespace. Should all be optimized away by compiler
    class DebugPrint {
    
    public:
    
        void setup() {}
        
        void setup(HardwareSerial& serial) {}
        
        void print(const char* out) {}
    
        void println(const char* out) {}
    
        void printf(const char* fmt, ...) {}
    
        void writeln(const char* buf, int len);
    
        void dwriteln(const char* buf, int len);

        void write(char c);
    
        /** Loop until reset */
        void exit() { while(1){} }
        
        void exit(const char* fmt, ...) { exit(); }
    };
        
#endif


#endif
