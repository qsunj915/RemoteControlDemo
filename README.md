# README

## TIPS:

* 使用前注意
    * 宏定义：options -> C/C++ -> 在Define中加入STM32F40_41xxx
    * 添加新功能之前要注意Pin不要重复
* 目前存在的问题
    * main函数运行时，通信丢包很严重(原因不明)。==程序要保证通信开始后不进入main==
    * 长时间运行时可能会出现程序莫名卡死



### 功能&一些函数的说明：

* LED：LED_FilpForISR() ==> 用于在中断中切换led灯状态
    * para:LED编号，切换led灯状态所需要的进入中断的次数
* KEY：keyHandle() ==> 用于读取按键值，会自动把按键值存入 *KEY_G* 数组中
* GUI：OLED_GUI_Task() ==> 更新OLED屏
* ADC：JOY_ADC_Calibration() ==> ADC值滤波并存入 *ADC_Value_G* 数组中
* NRF：
    * TransmitData_Pack() ==> 将要通信的数据打包存入 *TransmitData_SendFrame*
    * NRF24L01_TxPacket() ==> 发送数据(不建议更改模板中的实参)



## Pins:

| Pin  | Func     |
| ---- | -------- |
| A0   | ADC1     |
| A1   | ADC1     |
| A2   | ADC1     |
| A3   | ADC1     |
| A4   | ADC1     |
| A5   | ADC1     |
| A6   | ADC1     |
| A7   | ADC1     |
| A8   | NRF_CE   |
| A9   | USART1   |
| A10  | USART1   |
| A11  | NRF_IRQ  |
| B8   | I2C_SCL  |
| B9   | I2C_SDA  |
| B12  | SPI_NSS  |
| B13  | SPI_SCL  |
| B14  | SPI_MISO |
| B15  | SPI_MOSI |
| C6   | LED0     |
| C7   | LED1     |
| D0   | KEY0     |
| D1   | KEY1     |
| D2   | KEY2     |
| D3   | KEY3     |
| D4   | KEY4     |
| D5   | KEY5     |
| D6   | KEY6     |
| D7   | KEY7     |
| D8   | KEY8     |
| D9   | KEY9     |
| D10  | KEY14    |
| D11  | KEY15    |
| D12  | KEY10    |
| D13  | KEY11    |
| D14  | KEY12    |
| D15  | KEY13    |



<div align='right'> 2021/10/22</div>
<div align='right'> qsunj</div>

