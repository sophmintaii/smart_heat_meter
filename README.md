# Smart Heat Meter
**Principles of Computer Organisation coursework**
## Authors:
* Morozevych Yaroslav - https://github.com/yarmor20
* Myntiuk Sofiia - https://github.com/sophmintaii
* Muliarska Yana - https://github.com/muliarska
## Description & purpose
Nowadays, centralized systems of heating are wide-spread. Independent on how much heat people really consume in separate flat, they will pay the same amount with all the others. This system does not encourage energy saving and is simply unfair.

To solve the problem, we are going to calculate which part of the total amount of heat one flat really consumes. Using the fact that heat capacity of the water is constant and so is amount of water, we need to calculate change in temperature on the floor and divide it by total change of temperature. Next, we need to distribute heat loss between all the flats and add it to the result. This will be exactly the part of the total bill that the flat residents are going to pay.
## What we have done?
* Got acquainted with PSoC BLE Kit.
* Connected it to the phone app via Bluetooth.
* Learnt how to measure CPU temperature and sent it to the app.
* Connected data sensor to the board.
* Learnt how to measure temperature using the heat sensor.
* Changed the sensor.
* Figured out how to send temperature from the sensor(s) to the phone using BLE.
## Equipment
* CU8CKIT-042-BLE-A (PSoC 4200 BLE Pioneer Kit)
* OneWire DS18S20 Heat Sensor