/**
  ******************************************************************************
  * @file    main.c
  * @author  qsunj
  * @date    21-5-21
  * @brief  
  ******************************************************************************
  */
#include "main.h"

int	main()
{
	System_Init();
	
	while(1)
	{
		Serial_Send( Serial1, "Romote Running!\r\n");
	}
}

