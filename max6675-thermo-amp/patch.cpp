// Tell XOD where it could download the library:
#pragma XOD require "https://github.com/adafruit/MAX6675-library"

//Include C++ libraries
#include <max6675.h>

node {
    meta {
        // Define our custom type as a pointer on the class instance.
        using Type = MAX6675*;
    }
    
    static_assert(isValidDigitalPort(constant_input_SCLK), "must be a valid digital port");
    static_assert(isValidDigitalPort(constant_input_CS), "must be a valid digitial port");
    static_assert(isValidDigitalPort(constant_input_MISO), "must be a valid digital port");

    MAX6675 thermocouple = MAX6675(constant_input_SCLK, constant_input_CS, constant_input_MISO);


    void evaluate(Context ctx) {

        if (isSettingUp()) {
            // wait for MAX chip to stabilize
            delay(500);
        }

        if (isInputDirty<input_UPD>(ctx)) {
            emitValue<output_TempC>(ctx, thermocouple.readCelsius());
            emitValue<output_TempF>(ctx, thermocouple.readFahrenheit());
            emitValue<output_DONE>(ctx, 1);
        }
    }
}
