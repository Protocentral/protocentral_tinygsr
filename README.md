# protocentral_tinygsr

ProtoCentral tinyGSR breakout board can be used to measure the electrical conductivity of the skin. GSR is a galvanic skin response (GSR) that assesses a person’s emotional state or arousal level by monitoring variations in sweat gland activity. When a person is emotionally aroused or stressed, their sweat gland activity increases, which can be measured as changes in the electrical conductivity of the skin. With onboard LM324P Operational Amplifiers & TLA2022 has 12-bit resolution ADC and can operate at a sample rate of 3.3 kSPS (thousands of samples per second) through an I2C interface.

## Wiring the board to your Arduino

If you have bought the breakout the connection with the Arduino board is as follows:

|tinyGSR pin label| Arduino Connection   |Pin Function      |
|----------------- |:--------------------:|-----------------:|
| VCC             | +5V                   |  Supply voltage       |
| SDA              | A4               |  Serial data   |
| SCL              | A5            | Serial clock          |
| GND              | Gnd  

### Interfacing with Qwiic
The tinyGSR has an On-board Qwiic compatible connectors to bring flexibility in interfacing. It makes prototyping easy, less complex and interfacing with I2C has been put up simple. The board has built-in support for popular qwiic sensors. This would make it more suitable to plug in, detect the sensor, upload the code and read data.

# Visualizing data using the ProtoCentral OpenView GUI

The GUI for visualizing the skin response is written in Processing, based on Java and is cross-compliable across platforms.

![ProtoCentral Openview]()

Java 8 is required on all platforms for running the processing-based GUI application. You can download Java for your platform from the Official Java website.

You can download and install ProtoCentral OpenView from [this GitHub Repo](https://github.com/Protocentral/protocentral_openview). You can also program your Arduino with the example sketch specific to OpenView.

Once you have opened the OpenView GUI, make sure to select “tinyGSR” under the “Board” dropdown. If everything goes well, you will be able to see the screen as pictured above.

License Information
===================

![License](license_mark.svg)

This product is open source! Both, our hardware and software are open source and licensed under the following licenses:

Hardware
---------

**All hardware is released under the [CERN-OHL-P v2](https://ohwr.org/cern_ohl_p_v2.txt)** license.

Copyright CERN 2020.

This source describes Open Hardware and is licensed under the CERN-OHL-P v2.

You may redistribute and modify this documentation and make products
using it under the terms of the CERN-OHL-P v2 (https:/cern.ch/cern-ohl).
This documentation is distributed WITHOUT ANY EXPRESS OR IMPLIED
WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY
AND FITNESS FOR A PARTICULAR PURPOSE. Please see the CERN-OHL-P v2
for applicable conditions

Software
--------

**All software is released under the MIT License(http://opensource.org/licenses/MIT).**

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Documentation
-------------
**All documentation is released under [Creative Commons Share-alike 4.0 International](http://creativecommons.org/licenses/by-sa/4.0/).**
![CC-BY-SA-4.0](https://i.creativecommons.org/l/by-sa/4.0/88x31.png)

You are free to:

* Share — copy and redistribute the material in any medium or format
* Adapt — remix, transform, and build upon the material for any purpose, even commercially.
The licensor cannot revoke these freedoms as long as you follow the license terms.

Under the following terms:

* Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
* ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.

Please check [*LICENSE.md*](LICENSE.md) for detailed license descriptions.
