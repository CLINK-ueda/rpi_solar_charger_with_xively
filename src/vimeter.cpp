/*
  RaspberryPi Solar battery charging monitor

  Coded by Yasuhiro ISHII

  This software is distributed under the license of Apache2.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

#define I2C_SLAVEADDR_INA 0x40

int ina_getDieId(int fd,unsigned short* id);
int ina_getVoltage(int fd,int* vol);
int ina_getCurrent(int fd,int* curr);
static int ina_getValue(int fd,int addr,int* val);

int ina_getDieId(int fd,unsigned short* id)
{
  struct i2c_rdwr_ioctl_data data;
  struct i2c_msg msg[2];
  int result;
  unsigned char buff[2] = { 0 };
  unsigned char buff2[2] = { 0 };

  memset((void*)&data,0,sizeof(struct i2c_rdwr_ioctl_data));
  memset((void*)msg,0,sizeof(msg));

  buff[0] = 0x00;

  msg[0].addr = I2C_SLAVEADDR_INA;
  msg[0].flags = 0;
  msg[0].len = 1;
  msg[0].buf = buff;

  msg[1].addr = msg[0].addr;
  msg[1].flags = I2C_M_RD;
  msg[1].len = 2;
  msg[1].buf = buff2;

  data.msgs = msg;
  data.nmsgs = 2;

  result = ioctl(fd,I2C_RDWR,&data);

  return(0);
}

int ina_getVoltage(int fd,int* vol)
{
  int result;

  result = ina_getValue(fd,2,vol);
  *vol += *vol >> 2;

  return(result);
}

int ina_getCurrent(int fd,int* curr)
{
  int result;
  
  result = ina_getValue(fd,4,curr);

  return(result);
}

static int ina_getValue(int fd,int addr,int* val)
{
  struct i2c_rdwr_ioctl_data data;
  struct i2c_msg msg[2];
  int result;
  unsigned char buff[2] = { 0 };
  unsigned char buff2[2] = { 0 };

  memset((void*)&data,0,sizeof(struct i2c_rdwr_ioctl_data));
  memset((void*)msg,0,sizeof(msg));

  buff[0] = addr;

  msg[0].addr = I2C_SLAVEADDR_INA;
  msg[0].flags = 0;
  msg[0].len = 1;
  msg[0].buf = buff;

  msg[1].addr = msg[0].addr;
  msg[1].flags = I2C_M_RD;
  msg[1].len = 2;
  msg[1].buf = buff2;

  data.msgs = msg;
  data.nmsgs = 2;

  result = ioctl(fd,I2C_RDWR,&data);

  *val = buff2[0]<<8 | buff2[1];

  return(0);
}
