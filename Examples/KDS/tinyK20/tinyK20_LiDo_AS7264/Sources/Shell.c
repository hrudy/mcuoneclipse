/*
 * Shell.c
 *
 *  Created on: 04.08.2011
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Shell.h"
#include "CLS1.h"
#include "KIN1.h"
#include "I2CSPY1.h"
#include "PORT_PDD.h"

static const CLS1_ParseCommandCallback CmdParserTable[] =
{
  CLS1_ParseCommand,
  KIN1_ParseCommand,
  I2CSPY1_ParseCommand,
  NULL /* sentinel */
};

void SHELL_Parse(void) {
  (void)CLS1_ReadAndParseWithCommandTable(CLS1_DefaultShellBuffer, sizeof(CLS1_DefaultShellBuffer), CLS1_GetStdio(), CmdParserTable);
}

void SHELL_Init(void) {
  /* need pull-up on UART Rx pin (PTC3) on tinyK20 */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 3, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 3, PORT_PDD_PULL_ENABLE);
  CLS1_DefaultShellBuffer[0] = '\0';
}
