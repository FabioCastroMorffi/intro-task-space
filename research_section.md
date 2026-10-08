# Research Section

## Serial Communication

- What is the difference between a half duplex and a full duplex communication channel? What kind of communication channel does SPI and I2C use ? 

Full duplex implies that the communication can happen in both ways at the same time which means that the receiver and the transmitter can both get and send data. In consequence, you need two different wires for receiving and transmitting data and a total of 4 pins between transmitter and receiver. However, half duplex implies communication only happens one way so, at a given moment, the transmitter and receiver either send or receive the data, not both; this leads to an improvement in terms of pins to a total of 2 pins for data and 1 wire.

As for the communication channel of an SPI, it relies on 4 pins, two for data I both directions, 1 to synchronize clocks where the controller sets the speed and 1 for selecting the peripheral to which to send the data. For I2C, there’s only two pins, 1 for data (which is why its a half-duplex) and another for synchronizing through the serial clock.

- In I2C, how many data frames are sent during a single message? For each data frame identified, give a brief description of their purpose.

After the start condition and the address frame, informing which peripheral to talk to, are transmitted, there are as many data frames as necessary sent before concluding the message with the stop condition. Each data frame is followed by an acknowledge bit signaling whether the peripheral is busy or whether it received the frame. A data frame is composed of 8 bits so if we wanted to send two ASCII characters we send 2 data frames. Finally, the address frame also ends on an ACK bit and a read/write bit specifying the direction of the communication. 

-  How many bits of information can you send in a single I2C message? Given a potentiometer that has a decimal range of 0d0 - 0d1023, how many messages would you have to send to include all of the potentiometer’s bits? 

We can send 1 byte per data frame in a single I2C message encompassing from 0 to 255 decimal values. Given the range of the potentiometer, we need two data frames which can go up to 2^16 – 1 decimal values where the last value of the potentiometer would be represented as [ 0000 0011 ]1 [ 1111 1111]2 if it was MSB first.

- Given a SPI network of 1 master and N slaves, give a general equation to identify the number of wires that will connect to the master board. Assume we only want a single slave to be selected at any given moment. How many wires would be needed if the network was using I2C?

For an SPI setup with N peripherals where each peripheral gets 1 chip select wire, we require n + 3 cables given all peripherals share the same 3 wires for data transmission and clock and 1 additional wire per peripheral for chip select. For I2C, given that the controller shares the data and clock with all the peripherals the amount of wires required drops to 2 for N peripherals which really helps in terms of pin savings.

- List some pros and cons to both I2C and SPI?

From the previous question, a clear advantage of I2C is that it requires less available pins and wires for the same setup as SPI. That comes at the disadvantage that it can only send or receive data from the peripheral whereas SPI is full duplex. In addition, SPI’s setup usually allows for a maximum of 1 controller because of bus contention but it is faster with “clock rates upwards of 10MHz (and thus, 10 million bits per second) for some devices” from the recommended reading. I2C in contrast allows for multiple controllers but its slower. In conclusion, these two communication protocols contrast each other because the most of the pros of I2C are the cons of SPI and vice-versa.

## UML State Diagram

- From the figure below and the sample code provided, complete the implementation of the state diagram. You can choose to omit the sub-states for Heating.

```c++
state = idle;
while (True) {
    switch(state){
        case "Cooling":
            state = tooCold(desiredTemp) ? "Heating"
                    : atTemp(desiredTemp) ? "Idle"
                    : "Cooling";
            break;
        case "Heating":
            /* switches for sub-states ommitted
             * But they would prolly go something like
             *
             * while(!turnOn()) {
             *      // wait before checking again
             * }
             *
             * or just stick with the switch conditions
             * on the "Activating" and "Active" states
            */
            state = tooHot(desiredTemp) ? "Cooling"
                    : atTemp(desiredTemp) ? "Idle"
                    : "Heating";
            break;
        default:
            state = tooHot(desiredTemp) ? "Cooling"
                    : tooCold(desiredTemp) ? "Heating"
                    : "Idle";
    }
}
```

# Theoretical Section

- Perform the following boolean operations (0b denotes a binary value, 0x denotes a hexadecimal value)
    1. 0xF3 & 0x81 = 0x81
    2. 0b1 << 15 = 0b1000000000000000
    3. 0b1001 | 0b1100 = 0xC
    4. (0b1110110 >> 4) & 0x3 = 0b11

- Given a 16 bit binary message, a uint16_t variable called msg, where the most significant bit (MSB) contains the value of a button input and the 10 least significant bits (LSBs) contain the values of a potentiometer reading, complete the following bitwise operations to extract the desired output from msg.

  The format of msg would look as follows
  `msg = button 0 0 0 0 0 pot[9] pot[8] pot[7] pot[6] pot[5] pot[4] pot[3] pot[2] pot[1] pot[0]`
  bool buttonState = msg >> 15;
  uint16_t potValue = msg << 6;

- Write an arduino implementation for a rising edge triggered pushbutton.
  ```c++
    pinMode(buttonPin, INPUT);
    int prevState = 0;
    while (True) {
        bool pinState = digitalRead(buttonPin);
        // check for change in state and for state to be 1
        if (pinState && pinState != prevState) {
            ;
        }
        prevState = pinState;
    }
  ```

- If you were to implement a falling edge triggered pushbutton, what would change from the code implementation above?

Given both require a change in state, I'd make the outer if condition for the change of state and then a nested if else condition for the state's boolean to trigger rising edge on high and falling edge on low.

- Give examples of when an edge sensitive pushbutton or a level sensitive pushbutton would be required.

I think whenever we don't want to check for a continuos signal. For example, it becomes useful when counting, we do not want to increase the value of a variable keeping track of discrete amounts whenever the user input stays longer on a high signal. As for satellites, I can imagine many systems depend on these conditions. For instance, in motor control, you'd want the condition to be triggered only once after the change.


