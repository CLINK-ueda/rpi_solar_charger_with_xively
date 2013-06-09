/*
  RaspberryPi Solar battery charging monitor

  Coded by Yasuhiro ISHII

  This software is distributed under the license of Apache2.0
*/

#ifndef __VIMETER_H__
#define __VIMETER_H__

int ina_getDieId(int fd,unsigned short* id);
int ina_getVoltage(int fd,int* vol);
int ina_getCurrent(int fd,int* curr);

#endif /* __VIMETER_H__ */
