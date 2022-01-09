# Cyborg_Maker 
## team_42 submission to Dotslash 5.0
Video Link: [https://youtu.be/f3kNpFIdn4I]  
Presentation Link: [https://www.canva.com/design/DAE01rR7rN8/S5ar6qBLzxRB5_6DidSqMg/view?utm_content=DAE01rR7rN8&utm_campaign=designshare&utm_medium=link&utm_source=publishpresent]  


A glove which enhances the ability of a maker to measure certain parameters on-the-go.  
And a mouse which eliminates the need of an external mouse, and can navigate the cursor with the finger while coding.

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
   Theory: Using a voltage divider circuit, voltage drop is measured across a known resistor
   
2. Ohmmeter  
   Range: 200 Ω to 200 kΩ  
   Accuracy: 20-50 Ω*  
   Theory: Using a voltage divider circuit, voltage drop is measured across an unkown resistor with known voltage
   
3. Ammeter 
   Range: 20 mA to 5A  
   Scale factor: 185 mV/A*   
   (Used Hall effect sensor (ACS712T) for this.)    
   
4. Capacitance meter  
   Range: 0.4 μF to 4F  
   Accuracy: 0.1 μF*  
   Theory:  
   τ=R*C  
           τ is time constant measured through micros function in the code, τ=0.693  
           R is known 220Ω   
           From above data we calculate the value of C(Capacitance)  
           
           
5. Distance Measurement  
   Range: 2 cm to 400 cm  
   (Used HC-SR04 ultrasonic sensor.)  
   Theory: Using the the phenomenon of bouncing of sound waves and speed of sound in air we can calculate any distance between two rigid flat bodies  
   
6. RPM Optical Tachometer  
   Range: 100 to 4000 RPM*  
   (Used IR sensor.)  
   Instructions:  
   First, cover the shaft with black tape and stick a small white tape longitudal. Then, keep the IR sensor at 3-4 cm from the shaft and select RPM mode of the glove.  
   
7. Angle measurement (NOT COMPELETED YET)  
   Range: 0° to 180°  
   Accuracy: 0.02°    
   Theory: Angle is measured using the component of earth's graavity  
   
8. Temperature and Humidity  
   Range: 20° to 60° C  
   Measures Ambient temperature, nearby humidity and heat index.  
   Theory: Temperature is measured using a thermistor, and humidity is measured using an atmospheric capacitance  
   
9. Air Mouse  
   Full cursor and button control  
   Emulator- Emulates Mouse and Keyboard and mouse is controlled with MPU9250  
   
   
 > * Error increases as the measuring values increases.  
-----
### Parts Used
1. Arduino Uno.
2. Breadboard and jumper wires. 
3. Eight switches.
4. Various Resistors(10k, 2.2k, 1k and 220 ohms) and Capacitors(10V 2200microFarads).
5. IMU MPU-9250.
6. DHT11 Humidity sensor.
7. 1602 lcd screen.
8. Hall Effect sensor(ACS 712t).
9. IR sensor.
10. Ultrasonic distance sensor(HCSr04).
11. Arduino Pro Micro.
12. Potentiometer(10 k ohms).
