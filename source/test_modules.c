/*
 * test_cbfifo.c - test the cbfifo implementation
 *
 * Author: Howdy Pierce, howdy.pierce@colorado.edu
 *
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "test_modules.h"
#include "cbfifo.h"
#include "led.h"
#include "systick.h"
#include "i2c.h"
#include "accelerometer.h"

static void self_test_accelerometer_mode(int mode);

void test_cbfifo()
{
    cbfifo_reset(TRANSMIT);
  	cbfifo_reset(RECEIVE);

  char *str ="To be, or not to be: that is the question:\n"
    "Whether 'tis nobler in the mind to suffer\n"
    "The slings and arrows of outrageous fortune,\n"
    "Or to take arms against a sea of troubles,\n"
    "And by opposing end them? To die, to sleep--\n"
    "No more--and by a sleep to say we end\n"
    "The heart-ache and the thousand natural shocks\n"
    "That flesh is heir to, 'tis a consummation\n"
    "Devoutly to be wish'd. To die, to sleep;\n"
    "To sleep: perchance to dream: ay, there's the rub;\n"
    "For in that sleep of death what dreams may come\n"
    "When we have shuffled off this mortal coil,\n"
    "Must give us pause.";

  char buf[1024];
  const int cap = cbfifo_capacity(TRANSMIT);

  assert(strlen(str) >= cap*2);
  assert(sizeof(buf) > cap);
  assert(cap == 256 || cap == 255);

  assert(cbfifo_length(TRANSMIT) == 0);
  assert(cbfifo_length(RECEIVE) == 0);
  assert(cbfifo_dequeue(TRANSMIT, buf, cap) == 0);
  assert(cbfifo_dequeue(RECEIVE, buf, cap) == 0);
  assert(cbfifo_dequeue(TRANSMIT,buf, 1) == 0);
  assert(cbfifo_dequeue(RECEIVE,buf, 1) == 0);


  // enqueue 10 bytes, then dequeue same amt
  assert(cbfifo_enqueue(TRANSMIT,str, 10) == 10);
  assert(cbfifo_enqueue(RECEIVE,str, 10) == 10);
  assert(cbfifo_length(TRANSMIT) == 10);
  assert(cbfifo_length(RECEIVE) == 10);
  assert(cbfifo_dequeue(TRANSMIT,buf, 10) == 10);
  assert(cbfifo_dequeue(RECEIVE,buf, 10) == 10);
  assert(strncmp(buf, str, 10) == 0);
  assert(strncmp(buf, str, 10) == 0);
  assert(cbfifo_length(TRANSMIT) == 0);
  assert(cbfifo_length(RECEIVE) == 0);

  // enqueue 20 bytes;  dequeue 5, then another 20
  assert(cbfifo_enqueue(TRANSMIT,str, 20) == 20);
  assert(cbfifo_enqueue(RECEIVE,str, 20) == 20);
  assert(cbfifo_length(TRANSMIT) == 20);
  assert(cbfifo_length(RECEIVE) == 20);
  assert(cbfifo_dequeue(TRANSMIT,buf, 5) == 5);
  assert(cbfifo_dequeue(RECEIVE,buf, 5) == 5);
  assert(cbfifo_length(TRANSMIT) == 15);
  assert(cbfifo_length(RECEIVE) == 15);
  assert(cbfifo_dequeue(TRANSMIT,buf+5, 20) == 15);
  assert(cbfifo_dequeue(RECEIVE,buf+5, 20) == 15);
  assert(cbfifo_length(TRANSMIT) == 0);
  assert(cbfifo_length(RECEIVE) == 0);
  assert(strncmp(buf, str, 20) == 0);
  assert(strncmp(buf, str, 20) == 0);

  // fill buffer and then read it back out
  assert(cbfifo_enqueue(TRANSMIT,str, cap) == cap);
  assert(cbfifo_enqueue(RECEIVE,str, cap) == cap);
  assert(cbfifo_length(TRANSMIT) == cap);
  assert(cbfifo_length(RECEIVE) == cap);
  assert(cbfifo_enqueue(TRANSMIT,str, 1) == 0);
  assert(cbfifo_enqueue(RECEIVE,str, 1) == 0);
  assert(cbfifo_dequeue(TRANSMIT,buf, cap) == cap);
  assert(cbfifo_dequeue(RECEIVE,buf, cap) == cap);
  assert(cbfifo_length(TRANSMIT) == 0);
  assert(cbfifo_length(RECEIVE) == 0);
  assert(strncmp(buf, str, cap) == 0);
  assert(strncmp(buf, str, cap) == 0);

  // Add 20 bytes and pull out 18
  assert(cbfifo_enqueue(TRANSMIT,str, 20) == 20);
  assert(cbfifo_enqueue(RECEIVE,str, 20) == 20);
  assert(cbfifo_length(TRANSMIT) == 20);
  assert(cbfifo_length(RECEIVE) == 20);
  assert(cbfifo_dequeue(TRANSMIT,buf, 18) == 18);
  assert(cbfifo_dequeue(RECEIVE,buf, 18) == 18);
  assert(cbfifo_length(TRANSMIT) == 2);
  assert(cbfifo_length(RECEIVE) == 2);
  assert(strncmp(buf, str, 18) == 0);
  assert(strncmp(buf, str, 18) == 0);

  // Now add a bunch of data in 4 chunks
  int chunk_size = (cap-2) / 4;
  for (int i=0; i<4; i++) {
    assert(cbfifo_enqueue(TRANSMIT,str+i*chunk_size, chunk_size) == chunk_size);
    assert(cbfifo_length(TRANSMIT) == (i+1)*chunk_size + 2);
    assert(cbfifo_enqueue(RECEIVE,str+i*chunk_size, chunk_size) == chunk_size);
    assert(cbfifo_length(RECEIVE) == (i+1)*chunk_size + 2);
  }
  assert(cbfifo_length(TRANSMIT) == 4*chunk_size + 2);
  assert(cbfifo_length(RECEIVE) == 4*chunk_size + 2);

  // Take out the 2 remaining bytes from above
  assert(cbfifo_dequeue(TRANSMIT,buf, 2) == 2);
  assert(strncmp(buf, str+18, 2) == 0);
  assert(cbfifo_dequeue(RECEIVE,buf, 2) == 2);
  assert(strncmp(buf, str+18, 2) == 0);


  // now read those chunks out a byte at a time
  for (int i=0; i<chunk_size*4; i++) {
    assert(cbfifo_dequeue(TRANSMIT,buf+i, 1) == 1);
    assert(cbfifo_length(TRANSMIT) == chunk_size*4 - i - 1);
    assert(cbfifo_dequeue(RECEIVE,buf+i, 1) == 1);
    assert(cbfifo_length(RECEIVE) == chunk_size*4 - i - 1);
  }
  assert(strncmp(buf, str, chunk_size*4) == 0);

  // write more than capacity
  assert(cbfifo_enqueue(TRANSMIT,str, 65) == 65);
  assert(cbfifo_enqueue(TRANSMIT,str+65, cap) == cap-65);
  assert(cbfifo_length(TRANSMIT) == cap);
  assert(cbfifo_dequeue(TRANSMIT,buf, cap) == cap);
  assert(cbfifo_length(TRANSMIT) == 0);
  assert(strncmp(buf, str, cap) == 0);
  assert(cbfifo_enqueue(RECEIVE,str, 65) == 65);
  assert(cbfifo_enqueue(RECEIVE,str+65, cap) == cap-65);
  assert(cbfifo_length(RECEIVE) == cap);
  assert(cbfifo_dequeue(RECEIVE,buf, cap) == cap);
  assert(cbfifo_length(RECEIVE) == 0);
  assert(strncmp(buf, str, cap) == 0);

  // write zero bytes
  assert(cbfifo_enqueue(TRANSMIT,str, 0) == 0);
  assert(cbfifo_length(TRANSMIT) == 0);
  assert(cbfifo_enqueue(RECEIVE,str, 0) == 0);
  assert(cbfifo_length(RECEIVE) == 0);

  // Exercise the following conditions:
  //    enqueue when read < write:
  //        bytes < CAP-write  (1)
  //        bytes exactly CAP-write  (2)
  //        bytes > CAP-write but < space available (3)
  //        bytes exactly the space available (4)
  //        bytes > space available (5)
  assert(cbfifo_enqueue(TRANSMIT,str, 32) == 32);  // advance so that read < write
  assert(cbfifo_length(TRANSMIT) == 32);
  assert(cbfifo_dequeue(TRANSMIT,buf, 16) == 16);
  assert(cbfifo_length(TRANSMIT) == 16);
  assert(strncmp(buf, str, 16) == 0);
  assert(cbfifo_enqueue(RECEIVE,str, 32) == 32);  // advance so that read < write
  assert(cbfifo_length(RECEIVE) == 32);
  assert(cbfifo_dequeue(RECEIVE,buf, 16) == 16);
  assert(cbfifo_length(RECEIVE) == 16);
  assert(strncmp(buf, str, 16) == 0);

  assert(cbfifo_enqueue(TRANSMIT,str+32, 32) == 32);  // (1)
  assert(cbfifo_length(TRANSMIT) == 48);
  assert(cbfifo_enqueue(TRANSMIT,str+64, cap-64) == cap-64);  // (2)
  assert(cbfifo_length(TRANSMIT) == cap-16);
  assert(cbfifo_dequeue(TRANSMIT,buf+16, cap-16) == cap-16);
  assert(strncmp(buf, str, cap) == 0);
  assert(cbfifo_enqueue(RECEIVE,str+32, 32) == 32);  // (1)
  assert(cbfifo_length(RECEIVE) == 48);
  assert(cbfifo_enqueue(RECEIVE,str+64, cap-64) == cap-64);  // (2)
  assert(cbfifo_length(RECEIVE) == cap-16);
  assert(cbfifo_dequeue(RECEIVE,buf+16, cap-16) == cap-16);
  assert(strncmp(buf, str, cap) == 0);

  assert(cbfifo_enqueue(TRANSMIT,str, 32) == 32);  // advance so that read < write
  assert(cbfifo_length(TRANSMIT) == 32);
  assert(cbfifo_dequeue(TRANSMIT,buf, 16) == 16);
  assert(cbfifo_length(TRANSMIT) == 16);
  assert(strncmp(buf, str, 16) == 0);
  assert(cbfifo_enqueue(RECEIVE,str, 32) == 32);  // advance so that read < write
  assert(cbfifo_length(RECEIVE) == 32);
  assert(cbfifo_dequeue(RECEIVE,buf, 16) == 16);
  assert(cbfifo_length(RECEIVE) == 16);
  assert(strncmp(buf, str, 16) == 0);

  assert(cbfifo_enqueue(TRANSMIT,str+32, cap-20) == cap-20);  // (3)
  assert(cbfifo_length(TRANSMIT) == cap-4);
  assert(cbfifo_dequeue(TRANSMIT,buf, cap-8) == cap-8);
  assert(strncmp(buf, str+16, cap-8) == 0);
  assert(cbfifo_length(TRANSMIT) == 4);
  assert(cbfifo_dequeue(TRANSMIT,buf, 8) == 4);
  assert(strncmp(buf, str+16+cap-8, 4) == 0);
  assert(cbfifo_length(TRANSMIT) == 0);

  assert(cbfifo_enqueue(RECEIVE,str+32, cap-20) == cap-20);  // (3)
  assert(cbfifo_length(RECEIVE) == cap-4);
  assert(cbfifo_dequeue(RECEIVE,buf, cap-8) == cap-8);
  assert(strncmp(buf, str+16, cap-8) == 0);
  assert(cbfifo_length(RECEIVE) == 4);
  assert(cbfifo_dequeue(RECEIVE,buf, 8) == 4);
  assert(strncmp(buf, str+16+cap-8, 4) == 0);
  assert(cbfifo_length(RECEIVE) == 0);

  assert(cbfifo_enqueue(TRANSMIT,str, 49) == 49);  // advance so that read < write
  assert(cbfifo_length(TRANSMIT) == 49);
  assert(cbfifo_dequeue(TRANSMIT,buf, 16) == 16);
  assert(cbfifo_length(TRANSMIT) == 33);
  assert(strncmp(buf, str, 16) == 0);

  assert(cbfifo_enqueue(RECEIVE,str, 49) == 49);  // advance so that read < write
  assert(cbfifo_length(RECEIVE) == 49);
  assert(cbfifo_dequeue(RECEIVE,buf, 16) == 16);
  assert(cbfifo_length(RECEIVE) == 33);
  assert(strncmp(buf, str, 16) == 0);

  assert(cbfifo_enqueue(TRANSMIT,str+49, cap-33) == cap-33);  // (4)
  assert(cbfifo_length(TRANSMIT) == cap);
  assert(cbfifo_dequeue(TRANSMIT,buf, cap) == cap);
  assert(cbfifo_length(TRANSMIT) == 0);
  assert(strncmp(buf, str+16, cap) == 0);

  assert(cbfifo_enqueue(RECEIVE,str+49, cap-33) == cap-33);  // (4)
  assert(cbfifo_length(RECEIVE) == cap);
  assert(cbfifo_dequeue(RECEIVE,buf, cap) == cap);
  assert(cbfifo_length(RECEIVE) == 0);
  assert(strncmp(buf, str+16, cap) == 0);

  assert(cbfifo_enqueue(TRANSMIT,str, 32) == 32);  // advance so that read < write
  assert(cbfifo_length(TRANSMIT) == 32);
  assert(cbfifo_dequeue(TRANSMIT,buf, 16) == 16);
  assert(cbfifo_length(TRANSMIT) == 16);
  assert(strncmp(buf, str, 16) == 0);

  assert(cbfifo_enqueue(RECEIVE,str, 32) == 32);  // advance so that read < write
  assert(cbfifo_length(RECEIVE) == 32);
  assert(cbfifo_dequeue(RECEIVE,buf, 16) == 16);
  assert(cbfifo_length(RECEIVE) == 16);
  assert(strncmp(buf, str, 16) == 0);

  assert(cbfifo_enqueue(TRANSMIT,str+32, cap) == cap-16);  // (5)
  assert(cbfifo_dequeue(TRANSMIT,buf, 1) == 1);
  assert(cbfifo_length(TRANSMIT) == cap-1);
  assert(cbfifo_dequeue(TRANSMIT,buf+1, cap-1) == cap-1);
  assert(cbfifo_length(TRANSMIT) == 0);
  assert(strncmp(buf, str+16, cap) == 0);

  assert(cbfifo_enqueue(RECEIVE,str+32, cap) == cap-16);  // (5)
  assert(cbfifo_dequeue(RECEIVE,buf, 1) == 1);
  assert(cbfifo_length(RECEIVE) == cap-1);
  assert(cbfifo_dequeue(RECEIVE,buf+1, cap-1) == cap-1);
  assert(cbfifo_length(RECEIVE) == 0);
  assert(strncmp(buf, str+16, cap) == 0);
  //    enqueue when write < read:
  //        bytes < read-write (6)
  //        bytes exactly read-write (= the space available) (7)
  //        bytes > space available (8)

  int wpos=0, rpos=0;
  assert(cbfifo_enqueue(TRANSMIT,str, cap-4) == cap-4);
  wpos += cap-4;
  assert(cbfifo_length(TRANSMIT) == cap-4);
  assert(cbfifo_dequeue(TRANSMIT,buf, 32) == 32);
  rpos += 32;
  assert(cbfifo_length(TRANSMIT) == cap-36);
  assert(strncmp(buf, str, 32) == 0);
  assert(cbfifo_enqueue(TRANSMIT,str+wpos, 12) == 12);
  wpos += 12;
  assert(cbfifo_length(TRANSMIT) == cap-24);

  assert(cbfifo_enqueue(TRANSMIT,str+wpos, 16) == 16);  // (6)
  assert(cbfifo_length(TRANSMIT) == cap-8);
  assert(cbfifo_dequeue(TRANSMIT,buf, cap) == cap-8);
  assert(cbfifo_length(TRANSMIT) == 0);
  assert(strncmp(buf, str+rpos, cap-8) == 0);

  wpos=0; rpos=0;
  assert(cbfifo_enqueue(RECEIVE,str, cap-4) == cap-4);
  wpos += cap-4;
  assert(cbfifo_length(RECEIVE) == cap-4);
  assert(cbfifo_dequeue(RECEIVE,buf, 32) == 32);
  rpos += 32;
  assert(cbfifo_length(RECEIVE) == cap-36);
  assert(strncmp(buf, str, 32) == 0);
  assert(cbfifo_enqueue(RECEIVE,str+wpos, 12) == 12);
  wpos += 12;
  assert(cbfifo_length(RECEIVE) == cap-24);

  assert(cbfifo_enqueue(RECEIVE,str+wpos, 16) == 16);  // (6)
  assert(cbfifo_length(RECEIVE) == cap-8);
  assert(cbfifo_dequeue(RECEIVE,buf, cap) == cap-8);
  assert(cbfifo_length(RECEIVE) == 0);
  assert(strncmp(buf, str+rpos, cap-8) == 0);

  // reset
  wpos=0;
  rpos=0;
  assert(cbfifo_enqueue(TRANSMIT,str, cap-4) == cap-4);
  wpos += cap-4;
  assert(cbfifo_length(TRANSMIT) == cap-4);
  assert(cbfifo_dequeue(TRANSMIT,buf, 32) == 32);
  rpos += 32;
  assert(cbfifo_length(TRANSMIT) == cap-36);
  assert(strncmp(buf, str, 32) == 0);
  assert(cbfifo_enqueue(TRANSMIT,str+wpos, 12) == 12);
  wpos += 12;
  assert(cbfifo_length(TRANSMIT) == cap-24);

  assert(cbfifo_enqueue(TRANSMIT,str+wpos, 24) == 24);  // (7)
  assert(cbfifo_length(TRANSMIT) == cap);
  assert(cbfifo_dequeue(TRANSMIT,buf, cap) == cap);
  assert(cbfifo_length(TRANSMIT) == 0);
  assert(strncmp(buf, str+rpos, cap) == 0);

  // reset
  wpos=0;
  rpos=0;
  assert(cbfifo_enqueue(RECEIVE,str, cap-4) == cap-4);
  wpos += cap-4;
  assert(cbfifo_length(RECEIVE) == cap-4);
  assert(cbfifo_dequeue(RECEIVE,buf, 32) == 32);
  rpos += 32;
  assert(cbfifo_length(RECEIVE) == cap-36);
  assert(strncmp(buf, str, 32) == 0);
  assert(cbfifo_enqueue(RECEIVE,str+wpos, 12) == 12);
  wpos += 12;
  assert(cbfifo_length(RECEIVE) == cap-24);

  assert(cbfifo_enqueue(RECEIVE,str+wpos, 24) == 24);  // (7)
  assert(cbfifo_length(RECEIVE) == cap);
  assert(cbfifo_dequeue(RECEIVE,buf, cap) == cap);
  assert(cbfifo_length(RECEIVE) == 0);
  assert(strncmp(buf, str+rpos, cap) == 0);

  // reset
  wpos=0;
  rpos=0;
  assert(cbfifo_enqueue(TRANSMIT,str, cap-4) == cap-4);
  wpos += cap-4;
  assert(cbfifo_length(TRANSMIT) == cap-4);
  assert(cbfifo_dequeue(TRANSMIT,buf, 32) == 32);
  rpos += 32;
  assert(cbfifo_length(TRANSMIT) == cap-36);
  assert(strncmp(buf, str, 32) == 0);
  assert(cbfifo_enqueue(TRANSMIT,str+wpos, 12) == 12);
  wpos += 12;
  assert(cbfifo_length(TRANSMIT) == cap-24);

  assert(cbfifo_enqueue(TRANSMIT,str+wpos, 64) == 24);  // (8)
  assert(cbfifo_length(TRANSMIT) == cap);
  assert(cbfifo_dequeue(TRANSMIT,buf, cap) == cap);
  assert(cbfifo_length(TRANSMIT) == 0);
  assert(strncmp(buf, str+rpos, cap) == 0);

  // reset
  wpos=0;
  rpos=0;
  assert(cbfifo_enqueue(RECEIVE,str, cap-4) == cap-4);
  wpos += cap-4;
  assert(cbfifo_length(RECEIVE) == cap-4);
  assert(cbfifo_dequeue(RECEIVE,buf, 32) == 32);
  rpos += 32;
  assert(cbfifo_length(RECEIVE) == cap-36);
  assert(strncmp(buf, str, 32) == 0);
  assert(cbfifo_enqueue(RECEIVE,str+wpos, 12) == 12);
  wpos += 12;
  assert(cbfifo_length(RECEIVE) == cap-24);

  assert(cbfifo_enqueue(RECEIVE,str+wpos, 64) == 24);  // (8)
  assert(cbfifo_length(RECEIVE) == cap);
  assert(cbfifo_dequeue(RECEIVE,buf, cap) == cap);
  assert(cbfifo_length(RECEIVE) == 0);
  assert(strncmp(buf, str+rpos, cap) == 0);


  cbfifo_reset(TRANSMIT);
  cbfifo_reset(RECEIVE);

  printf("%s: Transmit: passed all test cases\n\r%s: Receive: passed all test cases\n\r", __FUNCTION__);
}

void test_tpm_led()
{
	printf("%s: Testing RGB LED by changing PWM duty cycle\n\r", __FUNCTION__);
	for (int i = 0; i<MAX_DUTY_CYCLE; i+=0x10)
	{
		for (int j = 0; j<MAX_DUTY_CYCLE; j+=0x10)
		{
			for (int k = 0; k<MAX_DUTY_CYCLE; k+=0x10)
			{
				test_LED_ON(i,j,k);
				delay(1);
			}
		}
	}
}

void self_test_accelerometer()													// Testing function to verify the output thrown by the accelerometer
{
	printf("Testing Accelerometer Readings: \n\r");
	int x_test[10], y_test[10], z_test[10];
	int x_sum=0, y_sum=0, z_sum=0;
	for(int i=0;i<10;i++)											// Taking 10 samples to verify our output
	{
		self_test_accelerometer_mode(ON);											// Switching on SELF test mode and storing values
		read_full_xyz();
		x_test[i]=acc_X;
		y_test[i]=acc_Y;
		z_test[i]=acc_Z;

		//printf("ON:\n\rX test: %d, Y test: %d, Z test: %d\n\r",x_test[i],y_test[i],z_test[i]);
		//printf("X: %d, Y: %d, Z: %d\n\r\n\r",acc_X,acc_Y,acc_Z);

		self_test_accelerometer_mode(OFF);										// Switching off the SELF test mode and storing values
		read_full_xyz();
		x_test[i]-=acc_X;											// Calculating the difference between the 2 modes
		y_test[i]-=acc_Y;
		z_test[i]-=acc_Z;

		//printf("OFF:\n\rX test: %d, Y test: %d, Z test: %d\n\r",x_test[i],y_test[i],z_test[i]);
		//printf("X: %d, Y: %d, Z: %d\n\r\n\r",acc_X,acc_Y,acc_Z);

		x_sum+=x_test[i];											// To calculate the average, finding their sum
		y_sum+=y_test[i];
		z_sum+=z_test[i];

		//printf("Xsum: %d, Ysum: %d, Zsum: %d\n\r\n\r",x_sum,y_sum,z_sum);
	}
	//printf("Xsum: %d, Ysum: %d, Zsum: %d\n\r\n\r",x_sum,y_sum,z_sum);
	if((x_sum/10 > X_REFERENCE) && (y_sum/10 > Y_REFERENCE) && (z_sum/10 > Z_REFERENCE))			// checking the average with the reference values
	{
		printf("Accelerometer Readings Verified Successfully!!!\n\r");
	}
	else
	{
		printf("Accelerometer Readings Verification FAILED\n\r");
	}
}

static void self_test_accelerometer_mode(int mode)
{
	if(mode == ON)
	{
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x00);		// Putting into standby mode by clearing the active bit in REG_CTRL1
		delay(5);										// Delay given to give time for the I2c values to set
		i2c_write_byte(MMA_ADDR, REG_CTRL2, 0x80);		// Putting into Self_test mode by setting the ST bit as 1 in REG_CTRL2
		delay(5);										// Delay given to give time for the I2c values to set
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);		// Putting into Active mode by setting the Active bit as 1 in REG_CTRL1
		delay(5);
	}
	else if(mode == OFF)
	{
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x00);		// Putting into standby mode by clearing the active bit in REG_CTRL1
		delay(5);										// Delay given to give time for the I2c values to set
		i2c_write_byte(MMA_ADDR, REG_CTRL2, 0x00);		// Getting out of the Self test mode by clearing the ST bit in REG_CTRL2
		delay(5);										// Delay given to give time for the I2c values to set
		i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);		// Going back to the Active mode by setting the active bit to 1 in REG_CTRL1
		delay(5);
	}

}
