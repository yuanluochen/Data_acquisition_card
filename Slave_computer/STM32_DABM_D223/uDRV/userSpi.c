#include "main.h"


u8 spi_transmit_receive8(SPI_TypeDef *spi,u8 tx)
{
	uint32_t timeout_cnt;
	static const uint32_t timeout_cnt_num = 1000000;
	
	timeout_cnt = 0;
	
	while(!LL_SPI_IsActiveFlag_TXE(spi)){
		timeout_cnt++;
		if(timeout_cnt > timeout_cnt_num){
			break;
		}
	}
	
	LL_SPI_TransmitData8(spi, tx);
	
	timeout_cnt = 0;
	while(LL_SPI_IsActiveFlag_BSY(spi)){
		timeout_cnt++;
		if(timeout_cnt > timeout_cnt_num){
			break;
		}
	}	
	
	timeout_cnt = 0;
	while(!LL_SPI_IsActiveFlag_RXNE(spi)){
		timeout_cnt++;
		if(timeout_cnt > timeout_cnt_num){
			break;
		}
	}

	return LL_SPI_ReceiveData8(spi);

}


u16 spi_transmit_receive16(SPI_TypeDef *spi,u16 tx)
{
	uint32_t timeout_cnt;
	static const uint32_t timeout_cnt_num = 1000000;
	
	timeout_cnt = 0;
	
	while(!LL_SPI_IsActiveFlag_TXE(spi)){
		timeout_cnt++;
		if(timeout_cnt > timeout_cnt_num){
			break;
		}
	}
	
	LL_SPI_TransmitData16(spi, tx);
	
	timeout_cnt = 0;
	while(LL_SPI_IsActiveFlag_BSY(spi)){
		timeout_cnt++;
		if(timeout_cnt > timeout_cnt_num){
			break;
		}
	}	
	
	timeout_cnt = 0;
	while(!LL_SPI_IsActiveFlag_RXNE(spi)){
		timeout_cnt++;
		if(timeout_cnt > timeout_cnt_num){
			break;
		}
	}

	return LL_SPI_ReceiveData16(spi);

}