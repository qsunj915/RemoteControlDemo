/**
  ******************************************************************************
  * @file    wave_filter.h
  * @author  
  * @version V1.0
  * @date    21-5-25
  * @brief   copy
  *****************************************************************************
  */
#ifndef __WAVE_FILTER_H__
#define __WAVE_FILTER_H__

#include "stm32f4xx.h"

typedef int16_t TYPE_WAVE, *pTYPE_WAVE;
typedef int16_t TYPE_WAVE_RETURN;

// ��ѡ������
void wave_sort(pTYPE_WAVE pfilter_head, pTYPE_WAVE pfilter_end);


/*
    ����һ��ֵ,�����˲����ֵ
    ���ѵõ���ֵ�������˲���ͷ
    �˲�����Сһ��Ϊ����
*/

// ��ֵ�˲�
TYPE_WAVE_RETURN wave_filter_mean  (pTYPE_WAVE pfilter_head, pTYPE_WAVE pfilter_end, TYPE_WAVE input_data);
// ����˲�
TYPE_WAVE_RETURN wave_filter_conv(pTYPE_WAVE pfilter_head, pTYPE_WAVE pfilter_end, 
                                  pTYPE_WAVE filter,     TYPE_WAVE input_data);
// ��ֵ�˲�
TYPE_WAVE_RETURN wave_filter_median(pTYPE_WAVE pfilter_head, pTYPE_WAVE pfilter_end, TYPE_WAVE input_data);

#endif
