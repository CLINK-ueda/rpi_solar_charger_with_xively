/*
  RaspberryPi Solar battery charging monitor

  Coded by Yasuhiro ISHII

  This software is distributed under the license of Apache2.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <xively.h>
#include <xi_helpers.h>
#include <xi_err.h>
#include "vimeter.h"
#include "conf_xively.h"

bool update_xively(char* api_key,char* feed_id,char* datastream_id,int val);

int main(void)
{
  int fd;
  unsigned short id;
  signed int v;
  signed int c;
  char buff[20];

  fd = open("/dev/i2c-0",O_RDWR);
  if(fd < 0){
    printf("i2c open error\n");
    exit(1);
  }
    
  while(1){
    ina_getVoltage(fd,&v);
    ina_getCurrent(fd,&c);

    update_xively(XIVELY_API_KEY,XIVELY_FEED_ID,"VOLTAGE",v);
    update_xively(XIVELY_API_KEY,XIVELY_FEED_ID,"CURRENT",c);
    
    printf("Voltage = %d[mV],Current = %d[mA]\n",v,c);
    sleep(2);
  }

  close(fd);
}

//    "example_01 api_key feed_id datastream_id value\n";

bool update_xively(char* api_key,char* feed_id,char* datastream_id,int val)
{
    xi_context_t* xi_context = xi_create_context(XI_HTTP,api_key,atoi(feed_id));

    // check if everything works
    if( xi_context == 0 )
    {
        return false;
    }

    xi_datapoint_t datapoint;
    xi_set_value_i32( &datapoint,val);

    { // get actual timestamp
        time_t timer = 0;
        time( &timer );
        datapoint.timestamp.timestamp = timer;
    }

    xi_datastream_update( xi_context
            , atoi( feed_id ), datastream_id
            , &datapoint.value );

    printf( "err: %d - %s\n", ( int ) xi_get_last_error(), xi_get_error_string( xi_get_last_error() ) );

    // destroy the context cause we don't need it anymore
    xi_delete_context( xi_context );

    return(true);
}
