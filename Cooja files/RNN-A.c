/*
 * Copyright (c) 2007, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         Testing the broadcast layer in Rime
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"
#include "net/rime.h"
#include "random.h"

#include "dev/button-sensor.h"

#include "dev/leds.h"

#include <stdio.h>
/*---------------------------------------------------------------------------*/
PROCESS(example_broadcast_process, "Dataset-1.csv");
AUTOSTART_PROCESSES(&example_broadcast_process);
/*---------------------------------------------------------------------------*/
static void
broadcast_recv(struct broadcast_conn *c, const rimeaddr_t *from)
{
static signed char rss;
  static signed char rss_val;
  static signed char rss_offset;
  printf("Long short Term memory from %d.%d: '%s'\n",
         from->u8[0], from->u8[1], (char *)packetbuf_dataptr());
 rss_val = ' ';
  rss_offset=45;
  rss=rss_val + rss_offset;
  printf("Parent - RSS signal strength is %d\n",rss);

}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;
/*---------------------------------------------------------------------------*/
int nbr[7][3];
int r[7];
PROCESS_THREAD(example_broadcast_process, ev, data)
{
  static struct etimer et;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  broadcast_open(&broadcast, 129, &broadcast_call);
  nbr[0][0]=2;
  nbr[0][1]=3;
  nbr[0][2]=4;
  nbr[1][0]=1;
  nbr[1][1]=4;
  nbr[1][2]=5;
  nbr[2][0]=1;
  nbr[2][1]=4;
  nbr[2][2]=6;
  nbr[3][0]=1;
  nbr[3][1]=2;
  nbr[3][2]=3;
  nbr[4][0]=2;
  nbr[4][1]=7;
  nbr[4][2]=0;
  nbr[5][0]=3;
  nbr[5][1]=7;
  nbr[5][2]=0;
  nbr[6][0]=5;
  nbr[6][1]=6;
  nbr[6][2]=0;
  r[0]=4;
  r[1]=2;
  r[2]=3;
  r[3]=1;
  r[4]=6;
  r[5]=9;
  r[6]=7;
int j,i;
  for( i=0;i<7;i++)
	{
		for( j=0;j<3;j++)
		{
			 printf("Best Routing node of node no. %d is %d\n",i+1,nbr[i][j]);
		}
	}
 i=0;
while(i<10)
{
etimer_set(&et, CLOCK_SECOND * 4 + random_rand() % (CLOCK_SECOND * 4));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
 packetbuf_copyfrom("Change in neighbour", 20);
    broadcast_send(&broadcast);
i=i+1;
}

 /* while(1) {

    // Delay 2-4 seconds 
    etimer_set(&et, CLOCK_SECOND * 4 + random_rand() % (CLOCK_SECOND * 4));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    packetbuf_copyfrom("hai", 6);
    broadcast_send(&broadcast);
    printf("broadcast message sent\n");
  }*/


  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
