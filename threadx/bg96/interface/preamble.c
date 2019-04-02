/*
 *  Created on: 04.06.2018
 *      Author: Georgi Angelov
 */
 
#pragma GCC target ("arm")

#include "threadx_api/txm_module.h"

#define _RO_BASE_ 0x40000000

extern void (*IMAGE_ER_RO_LENGTH 	[]) (void);
extern void (*IMAGE_ER_ZI_ZI_LENGTH []) (void);
extern void (*IMAGE_ER_RW_LENGTH 	[]) (void);
extern void (*SHELL_ENTRY     		[]) (void);
extern void (*THREAD_ENTRY 	  		[]) (void);
extern void (*THREAD_CALLBACK 		[]) (void);

TXM_MODULE_PREAMBLE __txm_module_preamble __attribute__ (( section (".preamble") )) =
{
	(ULONG)0x4D4F4455,											/* Download Module ID ( UDOM )                  */
	(ULONG)5,													/* Major Version ID                             */
    (ULONG)3,													/* Minor Version ID                             */
    (ULONG)32,													/* Module Preamble Size, in 32-bit words        */
    (ULONG)0x12345678,											/* Module ID (application defined)              */
    (ULONG)0x01000000,											/* Properties Bit Map                           */
    (ULONG)SHELL_ENTRY  	- _RO_BASE_,						/* Module Shell Entry Function                  */
    (ULONG)THREAD_ENTRY    	- _RO_BASE_,						/* Module Thread Start Function                 */
    (ULONG)0,													/* Module Thread Stop Function                  */
    (ULONG)180,													/* Module Thread Priority            			*/
    (ULONG)8192,												/* Module Thread Stack            				*/
    (ULONG)THREAD_CALLBACK 	- _RO_BASE_, 						/* Module Callback Thread Function              */
    (ULONG)25,													/* Module Callback Thread Priority              */
    (ULONG)8192,												/* Module Callback Thread Stack Size            */
    (ULONG)IMAGE_ER_RO_LENGTH,									/* Module Instruction Area Size                 */
    (ULONG)IMAGE_ER_ZI_ZI_LENGTH,								/* Module Data Area Size                        */
    (ULONG)_RO_BASE_,											/* Reserved                                     */
    (ULONG)IMAGE_ER_RW_LENGTH,									/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Reserved                                     */
    (ULONG)0,													/* Module Instruction Area Checksum [Optional]  */
};
