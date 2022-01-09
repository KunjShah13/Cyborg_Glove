# Cyborg_Maker 
## team_42 submission to Dotslash 5.0
Video Link: []  
Presentation Link: [https://www.canva.com/design/DAE01rR7rN8/S5ar6qBLzxRB5_6DidSqMg/view?utm_content=DAE01rR7rN8&utm_campaign=designshare&utm_medium=link&utm_source=publishpresent]  


A glove which enhances the ability of a maker to measure certain parameters on-the-go.  
And a mouse which eliminates the need of an external mouse, and can navigate with the finger while coding.

The parameters which can be measured are:(in the order of selection modes)  
  =>  Mechanical Measurements  
    1. Tempearture and Humidity  
    2. RPM Tachometer  
    3. Distance  
    4. Angle measurement/Spirit Leveller (NOT COMPELETED)
    
  =>  Electrical Measurements  
    5. Voltmeter  
    6. Capacitance meter  
    7. Ammeter  
    8. Ohmmeter

-----
### Technical Details
> To select any mode, press red switch for electrical instruments and yellow for mechanical instruments, and tilt your hand to select a mode.(left for 1,5, forward for 2,6, right for 3,7, backward for 4,8)  
1. Voltmeter   
   Range: 0V to 30V   
   Accuracy: 0.01 V
   
2. Ohmmeter  
   Range: 200 Ω to 200 kΩ  
   Accuracy: 20-50 Ω*  
   
3. Ammeter  
   Range: 20 mA to 5A  
   Scale factor: 185 mV/A*   
   (Used Hall effect sensor for this.)    
   
4. Capacitance meter  
   Range: 0.4 μF to 4F
   Accuracy: 0.1 μF*
   
5. Distance Measurement  
   Range: 2 cm to 400 cm  
   (Used HC-SR04 ultrasonic sensor.)  
   
6. RPM Optical Tachometer  
   Range: 100 to 4000 RPM* 
   (Used IR sensor.)
   First, cover the shaft with black tape and stick a small white tape longitudal. Then, keep the IR sensor at 3-4 cm from the shaft and select RPM mode of the glove.  
   
7. Angle measurement (NOT COMPELETED YET)  
   Range: 0° to 180°  
   Accuracy: 0.02°    
   
8. Temperature and Humidity  
   Range: 20° to 60° C  
   Measures Ambient temperature, nearby humidity and heat index.  
   
 > * Error increases as the measuring values increases.  
-----
### Parts Used
1. Arduino Uno  
2. Breadboard and jumper wires  
3. Switches, rotary switch.
4. Various Resistors and Capacitors
5. IMU MPU-9250
6. Humidity sensor
7. 1602 lcd screen
8. Hall Effect sensor
9. IR infrared sensor
10. Ultrasonic distance sensor
