// ______          _        _____            _             _ 
// | ___ \        | |      /  __ \          | |           | |
// | |_/ / __ ___ | |_ ___ | /  \/ ___ _ __ | |_ _ __ __ _| |
// |  __/ '__/ _ \| __/ _ \| |    / _ \ '_ \| __| '__/ _` | |
// | |  | | | (_) | || (_) | \__/\  __/ | | | |_| | | (_| | |
// \_|  |_|  \___/ \__\___/ \____/\___|_| |_|\__|_|  \__,_|_|

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Arduino Library for the TI TLA20XX ADC (https://www.ti.com/product/TLA20XX)
//
//  Copyright (c) 2022 ProtoCentral
//
//  Written by: Ashwin Whitchurch (ashwin@protocentral.com)
//
//  This software is licensed under the MIT License(http://opensource.org/licenses/MIT).
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
//  NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef protocentral_tla2022_h
#define protocentral_tla2022_h

#include <Arduino.h>
#include <Wire.h>

#define TLA20XX_CONV_REG 0x00
#define TLA20XX_CONF_REG 0x01

class TLA20XX
{
  public:
    enum DR {
        DR_128SPS = 0x00,
        DR_250SPS = 0x01,
        DR_490SPS = 0x02,
        DR_920SPS = 0x03,
        DR_1600SPS = 0x04,
        DR_2400SPS = 0x05,
        DR_3300SPS = 0x06,
    };

     enum FSR {
        FSR_6_144V = 0x00,
        FSR_4_096V = 0x01,
        FSR_2_048V = 0x02,
        FSR_1_024V = 0x03,
        FSR_0_512V = 0x04,
        FSR_0_256V = 0x05,
    };

    enum MUX {
        MUX_AIN0_AIN1 = 0x00,
        MUX_AIN0_AIN3 = 0x01,
        MUX_AIN1_AIN3 = 0x02,
        MUX_AIN2_AIN3 = 0x03,
        MUX_AIN0_GND = 0x04,
        MUX_AIN1_GND = 0x05,
        MUX_AIN2_GND = 0x06,
        MUX_AIN3_GND = 0x07,
    };

    enum MODE {
        OP_CONTINUOUS = 0,
        OP_SINGLE = 1
    };

    TLA20XX(uint8_t i2c_addr);
    void begin(void);
    int16_t read_adc();
    void setFSR(FSR fsr);
    void setMode(MODE mode);
    void setDR(DR rate);
    void setMux(MUX mux);

  private:
    void write_reg(uint8_t reg_addr, uint16_t data);
    uint16_t read_reg(uint8_t reg_addr);

    uint8_t _i2c_addr;

    union I2C_data {
        uint8_t u8_bytes[2];
        uint16_t u16_value;
    } _i2c_data;
};

#endif
