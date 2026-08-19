/**
  ******************************************************************************
  * @file           : drive.c
  * @brief          : Drive functions
  ******************************************************************************
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "flash.h"
uint32_t FirstPage = 0, NbOfPages = 0, BankNumber = 0;
uint32_t Address = 0, PAGEError = 0;
__IO uint32_t data32 = 0 , MemoryProgramStatus = 0;
static FLASH_EraseInitTypeDef EraseInitStruct;


static uint32_t GetPage(uint32_t Addr)
{
  uint32_t page = 0;

  if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
  {
    /* Bank 1 */
    page = (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
  }
  else
  {
    /* Bank 2 */
    page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
  }
  return page;
}
static uint32_t GetBank(uint32_t Addr)
{
  return FLASH_BANK_1;
}

void FlashErase(uint32_t pageCount)
{
	  HAL_FLASH_Unlock();
	  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
	  FirstPage = GetPage(FLASH_USER_START_ADDR);
	  /* Get the number of pages to erase from 1st page */
	  NbOfPages = GetPage(FLASH_USER_END_ADDR) - FirstPage + 1;
	  /* Get the bank */
	  BankNumber = GetBank(FLASH_USER_START_ADDR);
	  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	  EraseInitStruct.Banks       = BankNumber;
	  EraseInitStruct.Page        = FirstPage;
	  EraseInitStruct.NbPages     = pageCount;

	  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	     you have to make sure that these data are rewritten before they are accessed during code
	     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	     DCRST and ICRST bits in the FLASH_CR register. */
	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
	  {
		  while(1){};
	  }
}
void FlashWrite(uint32_t address, uint64_t data)
{
  Address = FLASH_USER_START_ADDR + address;
  if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, data) != HAL_OK)
  {
    while(1){};
  }
}

uint64_t FlashRead(uint32_t address)
{
	uint64_t tmp;
  Address = FLASH_USER_START_ADDR + address;
  tmp = *(__IO uint32_t *)Address;
  Address += 4;
  tmp = tmp | (uint64_t)(*(__IO uint32_t *)Address) << 32;
  return tmp;
}
