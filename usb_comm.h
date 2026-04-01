// Copyright (c) 2018 by HHD Software Ltd.
// This file is part of the HHD Software Device Monitoring Studio
// For usage and distribution policies, consult the license distributed with a product installation program

// Modification options:
// Trial mode: Modified file is loaded, compiled and used on startup
// Lite and Standard Editions: Protocol-related features are not available
// Professional Edition: Pre-configured version is used, changes in this file will be ignored
// Ultimate Edition: Modified file is loaded, compiled and used on startup

#pragma once

#pragma byte_order(LittleEndian)
#include "std_usbdefs.h"		// includes stddefs.h


enum
{
	HEADER,
	CALL_MANAGMENT,
	ABSTRACT_CONTROL_MANAGMENT,
	DIRECT_LINE_MANAGMENT,
	TELEPHONE_RINGER,
	TELEPHONE_CALL,
	UNION,
	COUNTRY_SELECTION,
	TELEPHONE_OP_MODE,
	USB_TERMINAL,
	NET_CHANNEL_TERMINAL,
	PROTOCOL_UNIT,
	EXTENSION_UNIT,
	MULTICHANNEL_MANAGMENT,
	CAPI_MANAGMENT,
	ETHERNET,
	ATM
};

enum
{
	CC_DIRECT_LINE_CONTROL= 1,
	CC_ABSTRACT_CONTROL,
	CC_TELEPHONE_CONTROL,
	CC_MULTICHANNEL_CONTROL,
	CC_CAPI_CONTROL,
	CC_ETHERNET_NETWORKING_CONTROL,
	CC_ATM_NETWORKING_CONTROL
};

struct CommDescriptor
{
	switch (bDescriptorSubtype)
	{
	case HEADER:
		WORD bcdCDC;
		break;
	case CALL_MANAGMENT:
		union Call
		{
			struct
			{
				BYTE UseClassInterface : 1;
				BYTE SelfControl : 1;
				BYTE Reserved : 6;
			}controls;
			BYTE bmCapatibilities;
		}call_capatibilities;
		[format("b2w8arf0")]
		BYTE bDataInterface;
		break;
	case ABSTRACT_CONTROL_MANAGMENT:
		union AbstractControl
		{
			struct
			{
				BYTE FeatureSupport : 1;
				BYTE LineStateSupport : 1;
				BYTE Send_Break_Support : 1;
				BYTE NotificationSupport : 1;
				BYTE Reserved : 4;
			}controls;
			[format("b2w8arf0")]
			BYTE bmCapatibilities;
		}abstract_control_capatibilities;
	break;
	case DIRECT_LINE_MANAGMENT:
		union DirectLine
		{
			struct
			{
				BYTE PulseSupport : 1;
				BYTE AuxSupport : 1;
				BYTE ExtSupport : 1;
				BYTE Reserved : 5;
			}controls;
			[format("b2w8arf0")]
			BYTE bmCapatibilities;
		}direct_line_capatibilities;
		break;
	case TELEPHONE_RINGER:
		BYTE bRingerVolSteps;
		BYTE bNumRingerPatterns;
		break;
	case TELEPHONE_CALL:
		union TelephoneCallState
		{
			struct
			{
				BYTE InterruptedDialtoneReport : 1;
				BYTE AllLineStateReport : 1;
				BYTE CallerID : 1;
				BYTE DistinctiveRinging : 1;
				BYTE DigitsReport : 1;
				BYTE LineStateChangeNotification : 1;
				BYTE Reserved : 2;
			}controls;
			[format("b2w8arf0")]
			BYTE bmCapatibilities;
		}telephone_call_capatibilities;
		break;
	case UNION:
		BYTE bMasterInterface;
		BYTE bSlaveInterface[bLength - (current_offset - start_offset)];
		break;
	case COUNTRY_SELECTION:
		BYTE iCountryCodeRelDate;
		WORD wCountryCode[(bLength - (current_offset - start_offset)) / sizeof(WORD)];
		break;
	case TELEPHONE_OP_MODE:
		union OperationalModes
		{
			struct
			{
				BYTE SimpleModeSupport : 1;
				BYTE StandAloneSupport : 1;
				BYTE ComputerCentricSupport : 1;
				BYTE Reserved : 5;
			}controls;
			[format("b2w8arf0")]
			BYTE bmCapatibilities;
		}operational_modes_capatibilities;
		break;
	case USB_TERMINAL:
		BYTE bEntityId;
		BYTE bInInterfaceNo;
		BYTE bOutInterfaceNo;

		union UsbTerminal
		{
			struct
			{
				BYTE WrapperUsed : 1;
				BYTE Reserved : 7;
			}options;
			[format("b2w8arf0")]
			BYTE bmOptions;
		}usb_terminal_options;

		BYTE bChild[bLength - (current_offset - start_offset)];
		break;
	case NET_CHANNEL_TERMINAL:
		BYTE bEntityId;
		BYTE iName;
		BYTE bChannelIndex;
		enum PhysicalInterface : BYTE
		{
			None,
			ISDN
		}physical_interface;

		break;
	case PROTOCOL_UNIT:
		BYTE bEntityId;
		BYTE bProtocol;
		BYTE bChild[bLength - (current_offset - start_offset)];
		break;
	case EXTENSION_UNIT:
		BYTE bEntityId;
		BYTE bExtensionCode;
		BYTE iName;
		BYTE bChild[bLength - (current_offset - start_offset)];
		break;
	case MULTICHANNEL_MANAGMENT:
		union Multichannel
		{
			struct
			{
				BYTE StoresUnitParameter : 1;
				BYTE Clear_Unit : 1;
				BYTE Set_Unit : 1;
				BYTE Reserved : 5;
			}options;
			[format("b2w8arf0")]
			BYTE bmOptions;
		}multichannel_options;
		break;
	case CAPI_MANAGMENT:
		union CAPI
		{
			struct
			{
				BYTE SimpleCAPI : 1;
				BYTE Reserved : 7;
			}options;
			[format("b2w8arf0")]
			BYTE bmOptions;
		}capi_options;
		break;
	case ETHERNET:
		BYTE iMacAddress;

		union EthernetStatistics
		{
			struct
			{
				DWORD XMIT_OK : 1;
				DWORD RVC_OK : 1;
				DWORD XMIT_ERROR : 1;
				DWORD RCV_ERROR : 1;
				DWORD RCV_NO_BUFFER : 1;
				DWORD DIRECTED_BYTES_XMIT : 1;
				DWORD DIRECTED_FRAMES_XMIT : 1;
				DWORD MULTICAST_BYTES_XMIT : 1;
				DWORD MULTICAST_FRAMES_XMIT : 1;
				DWORD BROADCAST_BYTES_XMIT : 1;
				DWORD BROADCAST_FRAMES_XMIT : 1;
				DWORD DIRECTED_BYTES_RCV : 1;
				DWORD DIRECTED_FRAMES_RCV : 1;
				DWORD MULTICAST_BYTES_RCV : 1;
				DWORD MULTICAST_FRAMES_RCV : 1;
				DWORD BROADCAST_BYTES_RCV : 1;
				DWORD BROADCAST_FRAMES_RCV : 1;
				DWORD RCV_CRC_ERROR : 1;
				DWORD TRANSMIT_QUEUE_LENGTH : 1;
				DWORD RCV_ERROR_ALIGNMENT : 1;
				DWORD XMIT_ONE_COLLISION : 1;
				DWORD XMIT_MORE_COLLISIONS : 1;
				DWORD XMIT_DEFERRED : 1;
				DWORD XMIT_MAX_COLLISIONS : 1;
				DWORD RCV_OVERRUN : 1;
				DWORD XMIT_UNDERRUN : 1;
				DWORD XMIT_HEARTBEAT_FAILURE : 1;
				DWORD XMIT_TIMES_CRS_LOST : 1;
				DWORD XMIT_LATE_COLLISIONS : 1;
				DWORD Reserved : 3;
			}options;
			[format("b2w32arf0")]
			DWORD bmEthernetStatistics;
		}ethernet_statistics;
		WORD wMaxSegmentSize;
		WORD wNumberMCFilters;
		BYTE bNumberPowerFilters;
		break;
	case ATM:
		BYTE iEndSystemIdentifier;
		union DataCapabilities
		{
			struct
			{
				BYTE Reserved : 1;
				BYTE Type1 : 1;
				BYTE Type2 : 1;
				BYTE Type3 : 1;
				BYTE Reserved1 : 4;
			}bits;
			[format("b2w8arf0")]
			BYTE bmDataCapabilities;
		}data_capabilities;

		union ATMDeviceStatistics
		{
			struct
			{
				BYTE DS_CELLS_RECEIVED : 1;
				BYTE US_CELLS_SENT : 1;
				BYTE DS_CELLS_HEC_ERROR_CORRECTED : 1;
				BYTE VC_DS_CELLS_RECEIVED : 1;
				BYTE VC_US_CELLS_SENT : 1;
				BYTE Reserved : 3;
			}bits;
			[format("b2w8arf0")]
			BYTE bmATMDeviceStatistics;
		}atm_device_statistics;
		WORD wType2MaxSegmentSize;
		WORD wType3MaxSegmentSize;
		WORD wMAxWC;

		break;
	}
};
