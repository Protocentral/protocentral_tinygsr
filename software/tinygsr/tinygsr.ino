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

#include <Arduino.h>
#include <Wire.h>

#include <FIR.h>

#include <protocentral_TLA20xx.h>

#define TLA20XX_I2C_ADDR 0x49
#define CES_CMDIF_PKT_START_1 0x0A
#define CES_CMDIF_PKT_START_2 0xFA
#define CES_CMDIF_TYPE_DATA 0x02
#define CES_CMDIF_PKT_STOP 0x0B
#define DATA_LEN 9
#define ZERO 0

float val;
int16_t data;

volatile char DataPacket[DATA_LEN];
const char DataPacketFooter[2] = { ZERO, CES_CMDIF_PKT_STOP };
const char DataPacketHeader[5] = { CES_CMDIF_PKT_START_1, CES_CMDIF_PKT_START_2, DATA_LEN, ZERO, CES_CMDIF_TYPE_DATA };

TLA20XX tla2022(TLA20XX_I2C_ADDR);

FIR<float, 8> fir;

void setup() {
  delay(3000);
  Serial.begin(57600);
  Serial.println("Starting ADC...");

  float coef[8] = { 1., 1., 1., 1., 1., 1., 1., 1. };
  // Set the coefficients
  fir.setFilterCoeffs(coef);

  Wire.begin();

  tla2022.begin();

  tla2022.setMode(TLA20XX::OP_CONTINUOUS);
  tla2022.setDR(TLA20XX::DR_128SPS);
  tla2022.setFSR(TLA20XX::FSR_0_512V);
}

void loop() {
  val = fir.processReading(tla2022.read_adc());  // +/- 2.048 V FSR, 1 LSB = 1 mV
  data = (int16_t)val;

  //Serial.println(data);

  DataPacket[0] = (uint8_t)data;
  DataPacket[1] = (uint8_t)(data >> 8);
  DataPacket[2] = 0x00;
  DataPacket[3] = 0x00;

  //send packet header
  for (int i = 0; i < 5; i++) {

    Serial.write(DataPacketHeader[i]);
  }

  //send actual data
  for (int i = 0; i < DATA_LEN; i++) {

    Serial.write(DataPacket[i]);
  }

  //send packet footer
  for (int i = 0; i < 2; i++) {

    Serial.write(DataPacketFooter[i]);
  }
  delay(8);
}