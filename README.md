# ECEN5813-Course-Project  
  
## **Project Topic**	: 	Digital Angle Gauge using MMA8451 Accelerometer and Serial Communication using UART  
  
## **Author**		: 	Tanmay Mahendra Kothale  
			(Tanmay.Kothale@Colorado.edu)  
  
## **UART Parameters**	:	Baud Rate: 38400, Stop Bits: 2  

## This project is implemented in **DEBUG** build only.

## **Source files included**  
main.c
accelerometer.h/.c  
cbfifo.h/.c  
command_process.h/.c  
i2c.h/.c  
led.h/.c  
line_accumulate.h/.c  
sysclock.h/.c  
systick.h/.c  
test_modules.h/.c  
touch.h/.c  
uart.h/.c  
  
## **Project Description**
1. The project implements a certain set of commands using the command processor.  
2. The project also implements a digital angle gauge.  
3. Available commands and their description can be seen using 'help' command in the command processor. 
4. RGB LED functionality is implemented to act as an indicator for user to know which command is being executed or which command was executed last. According to the project proposal, the design initially was a white color will be glowing whenever the processor is ready for next command. However, the processing speed of the command processor is so high such that the change of color will not be visible to naked eye, hence, that requirement is removed.  
5. TSI module is implemented to adjust the brightness of the LED. Use 'touch' command to adjust the brightness. Initially, I was planning to poll the tsi module, but since we are using a while block to accumulate the line, the tsi module is not being polled properly. Thus, I implemented a command which will then poll the tsi until the desired brightness is reached. To adjust the brightness, we will tap on the tsi module. First, if the brightness is greater than 0, a tap will gradually decrease the brightness by 10%. Once, the brightness is 0 (LED OFF), tap will increase the brightness gradually by 10%. This goes so on and so forth till we perform a hard tap on the tsi module which is the exit condition of the loop.  
6. Since, the LED is acting as an indicator, I have assigned one color to each command. The command table along with its colors is:  
  
| Command | Color | Hex Value |
| -- | -- | -- |
| Author | Cyan | 0x00FFFF |
| Help | Neon | 0x70FF07 |
| Brightness | Sky Blue | 0x0770FF |
| Angle | Yellow | 0xFFFF00 |
| Color | Magenta | 0xFF00FF |
| Touch | Blue | 0x0000FF |
| Calibrate | Green | 0x00FF00 |
| Invalid Command | Red | 0xFF0000 |
  
**Other available colors are:**  
  
| Color | Hex Value |
| -- | -- |
| Pink | 0xFF70FF |
| White | 0xFFFFFF |
  
7. The user can change the color assigned to the command at his discretion. Use 'color' command for the same. See help command for more information.  
8. The user can set angle using the 'angle' command. See help command for more information. Once the angle is set, then the LED will start blinking with Yellow color (unless the user chooses to change the color). Once the desired angle is reached, the LED will start glowing solid yellow color (unless user changes this color assignment).  
9. User can also change the LED brightness using brightness command. See help command for more information.  
10. Systick interrupt is used for delay function.  

## **Video Link**:  
https://drive.google.com/drive/folders/15QF-XE1jtWvhr13ZNwFdF5Y0PsxS0GEy?usp=sharing
**Please use CU Email ID to access the video file.**