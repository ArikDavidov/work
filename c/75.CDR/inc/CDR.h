#ifndef __CDR_H__
#define __CDR_H__

#include <stdio.h>

#define IMSI_LENGTH		15
#define MSISDN_LENGTH	15
#define IMEI_LENGTH		15
#define BRAND_LENGTH	64
#define MCC_MNC_LENGTH	6


typedef enum CallType
{
	MOC,		/**<  outgoing voice call  */
	MTC,		/**<  incoming voice call  */
	SMS_MO,		/**<  outgoing message     */
	SMS_MT,		/**<  incoming message     */
	GPRS		/**<  internet             */
} CallType;


typedef struct Cdr
{	/* All buffers are bigger than needed by one char
	   to accommodate the '\0' char at the end */
	char          m_imsi[IMSI_LENGTH + 1];                /**<  International mobile subscriber identity. Stored on a SIM card	*/
	char          m_msisdn[MSISDN_LENGTH + 1];            /**<  Subscriber ID in a mobile network                               */
	char          m_imei[IMEI_LENGTH + 1];                /**<  Subscriber Equipment number: 49-015420-323751                   */
	char          m_operatorBrandName[BRAND_LENGTH + 1];  /**<  for example: "Cellcom Israel"                                   */
	char          m_mccMnc[MCC_MNC_LENGTH + 1];           /**<  Mobile Country code (3-digits), Mobile Network Code(2-3-digits) */
	CallType      m_callType;                             /**<  Incoming/Outgoing call/SMS or internet                          */
	char          m_callDate[10 + 1];                     /**<  DD/MM/YYYY                                                      */
	char          m_callTime[8 + 1];                      /**<  HH:MM:SS                                                        */
	unsigned int  m_duration;                             /**<  in seconds                                                      */
	double        m_download;                             /**<  MB dowloaded if type is GPRS                                    */
	double        m_upload;                               /**<  MB uploaded if type is GPRS                                     */
	char          m_partyMsisdn[MSISDN_LENGTH + 1];       /**<  Corresponding party in this call, empty for GPRS                */
	char          m_partyOperator[MCC_MNC_LENGTH + 1];    /**<  Corresponding party’s mobile operator in this call              */
} Cdr;





#endif /* #ifndef __CDR_H__ */


