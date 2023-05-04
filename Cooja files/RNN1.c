/*
 * Copyright (c) 2010, Swedish Institute of Computer Science.
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
 *         Contiki Collect View Shell
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"
#include "shell.h"
#include "serial-shell.h"
#include "collect-view.h"

#define WITH_COFFEE 0

/*---------------------------------------------------------------------------*/
PROCESS(collect_view_shell_process, "Routing updates");

AUTOSTART_PROCESSES(&collect_view_shell_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(collect_view_shell_process, ev, data)
{
  PROCESS_BEGIN();

  serial_shell_init();
  shell_blink_init();
   int malicious[]={2,6,7,4,10,3,8,9,14,34,45,67,78,23,34};
#if WITH_COFFEE
  shell_file_init();
  shell_coffee_init();
#endif /* WITH_COFFEE */
    int i=0;
    int etxlimit=10;
    int rankself=23;
    int selfrank=34;
    int n1etx,n2etx,n1rank,n2rank;
    int prefer;
    while (i != malicious[i] && i <15 )
    {
      n1etx=rand();
      n2etx=rand();
      if((n1etx <= etxlimit)&&(n2etx <= etxlimit))
      {

	n1rank=rand();
	n2rank=rand();
	if((n1rank <= rankself)&&(n2rank <= rankself))
	{
		prefer=n1etx;	
	}
	else if((n1rank <= selfrank)&&(n2rank <= selfrank))
	{
		prefer=n1etx;	
	}
        else
        {
		prefer=0;
	}
      }
	
      else
	{
		if((n1etx <= etxlimit)||(n2etx <= etxlimit))
		      {
			prefer=n1etx;

		      }
      		 else
       		 {
			prefer=0;
		  }

	  
	}

	 printf("best parent[v] = parent[u] + C[v][u] is %d\n" , prefer);

   
      i=i+1;
    }
  /* shell_download_init(); */
  /* shell_rime_sendcmd_init(); */
  /* shell_ps_init(); */
  shell_reboot_init();
  shell_rime_init();
  shell_rime_netcmd_init();
  /* shell_rime_ping_init(); */
  /* shell_rime_debug_init(); */
  /* shell_rime_debug_runicast_init(); */
  shell_powertrace_init();
  /* shell_base64_init(); */
  shell_text_init();
  shell_time_init();
  /* shell_checkpoint_init(); */
  /* shell_sendtest_init(); */

#if CONTIKI_TARGET_SKY
  shell_sky_init();
#endif /* CONTIKI_TARGET_SKY */

  shell_collect_view_init();

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
