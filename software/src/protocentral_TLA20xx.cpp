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

#include "protocentral_TLA20xx.h"

TLA20XX::TLA20XX(uint8_t i2c_addr)
{
    _i2c_addr=i2c_addr;
}

void TLA20XX::write_reg(uint8_t reg_addr, uint16_t in_data)
{
    _i2c_data.u16_value = in_data;

	Wire.beginTransmission(_i2c_addr);  

	Wire.write(reg_addr);           
	Wire.write(_i2c_data.u8_bytes[1]);
    Wire.write(_i2c_data.u8_bytes[0]);     

	Wire.endTransmission();           
}

uint16_t TLA20XX::read_reg(uint8_t reg_addr){
	uint16_t data; 
	
    Wire.beginTransmission(_i2c_addr);

	Wire.write(reg_addr);

	Wire.endTransmission(false);
	Wire.requestFrom(_i2c_addr, (uint8_t) 2);

    _i2c_data.u8_bytes[1]=Wire.read();
    _i2c_data.u8_bytes[0]=Wire.read();

	data = _i2c_data.u16_value;
    
	return data;
}

void TLA20XX::setFSR(TLA20XX::FSR range) {
    uint16_t conf = read_reg(TLA20XX_CONF_REG);

    conf &= ~0x0E00;
    conf |= range << 9;

    write_reg(TLA20XX_CONF_REG,conf);
}

void TLA20XX::setMode(TLA20XX::MODE mode) {
    uint16_t conf = read_reg(TLA20XX_CONF_REG);

    conf &= ~(1 << 8);
    if (mode == OP_SINGLE) {
        conf |= (1 << 8);
    }
    write_reg(TLA20XX_CONF_REG,conf);
}

void TLA20XX::setDR(TLA20XX::DR rate) {
    uint16_t conf = read_reg(TLA20XX_CONF_REG);

    conf |= rate << 5;
    write_reg(TLA20XX_CONF_REG,conf);
}

void TLA20XX::setMux(TLA20XX::MUX mux){
   uint16_t conf = read_reg(TLA20XX_CONF_REG);
    // clear MUX bits
    conf &= ~0x7000;

    conf |= mux << 12;
    write_reg(TLA20XX_CONF_REG,conf);
}

int16_t TLA20XX::read_adc() {
    uint16_t in_data = read_reg(TLA20XX_CONV_REG);

    int16_t ret = (int16_t) in_data;
    ret>>=4;

    return ret;
}

void TLA20XX::begin() 
{
    uint16_t init = read_reg(TLA20XX_CONF_REG);

    Serial.print("Inited: ");
    Serial.println(init);

    write_reg(TLA20XX_CONF_REG,0x8683);
}