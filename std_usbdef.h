// Copyright (c) 2018 by HHD Software Ltd.
// This file is part of the HHD Software Device Monitoring Studio
// For usage and distribution policies, consult the license distributed with a product installation program

// Modification options:
// Trial mode: Modified file is loaded, compiled and used on startup
// Lite and Standard Editions: Protocol-related features are not available
// Professional Edition: Pre-configured version is used, changes in this file will be ignored
// Ultimate Edition: Modified file is loaded, compiled and used on startup

// This file contains common declarations used by USB protocols

#pragma once
#include "stddefs.h"

// event_type predefined field constants
enum
{
	EVENT_URB,
	EVENT_DEVICECONNECTED,
	EVENT_DEVICEDISCONNECTED,
	EVENT_DEVICESURPRISEREMOVAL,
	EVENT_DEVICEQUERYID,
	EVENT_DEVICEQUERYTEXT,
	EVENT_PIPEINFO,
	EVENT_QUERYINTERFACE,
};

#ifdef _SVC_X64
	typedef unsigned __int64 PVOID;
#else
	typedef unsigned long PVOID;
#endif

typedef unsigned long ULONG_PTR;
typedef PVOID PMDL;

typedef PVOID USBD_PIPE_HANDLE;
typedef PVOID USBD_CONFIGURATION_HANDLE;
typedef PVOID USBD_INTERFACE_HANDLE;

//
//  URB request codes
//
enum URB_FUNCTION : WORD
{
	URB_FUNCTION_SELECT_CONFIGURATION            = 0x0000,
	URB_FUNCTION_SELECT_INTERFACE                = 0x0001,
	URB_FUNCTION_ABORT_PIPE                      = 0x0002,
	URB_FUNCTION_TAKE_FRAME_LENGTH_CONTROL       = 0x0003,
	URB_FUNCTION_RELEASE_FRAME_LENGTH_CONTROL    = 0x0004,
	URB_FUNCTION_GET_FRAME_LENGTH                = 0x0005,
	URB_FUNCTION_SET_FRAME_LENGTH                = 0x0006,
	URB_FUNCTION_GET_CURRENT_FRAME_NUMBER        = 0x0007,
	URB_FUNCTION_CONTROL_TRANSFER                = 0x0008,
	URB_FUNCTION_BULK_OR_INTERRUPT_TRANSFER      = 0x0009,
	URB_FUNCTION_ISOCH_TRANSFER                  = 0x000A,
	URB_FUNCTION_GET_DESCRIPTOR_FROM_DEVICE      = 0x000B,
	URB_FUNCTION_SET_DESCRIPTOR_TO_DEVICE        = 0x000C,
	URB_FUNCTION_SET_FEATURE_TO_DEVICE           = 0x000D,
	URB_FUNCTION_SET_FEATURE_TO_INTERFACE        = 0x000E,
	URB_FUNCTION_SET_FEATURE_TO_ENDPOINT         = 0x000F,
	URB_FUNCTION_CLEAR_FEATURE_TO_DEVICE         = 0x0010,
	URB_FUNCTION_CLEAR_FEATURE_TO_INTERFACE      = 0x0011,
	URB_FUNCTION_CLEAR_FEATURE_TO_ENDPOINT       = 0x0012,
	URB_FUNCTION_GET_STATUS_FROM_DEVICE          = 0x0013,
	URB_FUNCTION_GET_STATUS_FROM_INTERFACE       = 0x0014,
	URB_FUNCTION_GET_STATUS_FROM_ENDPOINT        = 0x0015,
	URB_FUNCTION_RESERVED_0X0016                 = 0x0016,
	URB_FUNCTION_VENDOR_DEVICE                   = 0x0017,
	URB_FUNCTION_VENDOR_INTERFACE                = 0x0018,
	URB_FUNCTION_VENDOR_ENDPOINT                 = 0x0019,
	URB_FUNCTION_CLASS_DEVICE                    = 0x001A,
	URB_FUNCTION_CLASS_INTERFACE                 = 0x001B,
	URB_FUNCTION_CLASS_ENDPOINT                  = 0x001C,
	URB_FUNCTION_RESERVE_0X001D                  = 0x001D,
	// previously URB_FUNCTION_RESET_PIPE
	URB_FUNCTION_SYNC_RESET_PIPE_AND_CLEAR_STALL = 0x001E,
	URB_FUNCTION_RESET_PIPE = URB_FUNCTION_SYNC_RESET_PIPE_AND_CLEAR_STALL,
	URB_FUNCTION_CLASS_OTHER                     = 0x001F,
	URB_FUNCTION_VENDOR_OTHER                    = 0x0020,
	URB_FUNCTION_GET_STATUS_FROM_OTHER           = 0x0021,
	URB_FUNCTION_CLEAR_FEATURE_TO_OTHER          = 0x0022,
	URB_FUNCTION_SET_FEATURE_TO_OTHER            = 0x0023,
	URB_FUNCTION_GET_DESCRIPTOR_FROM_ENDPOINT    = 0x0024,
	URB_FUNCTION_SET_DESCRIPTOR_TO_ENDPOINT      = 0x0025,
	URB_FUNCTION_GET_CONFIGURATION               = 0x0026,
	URB_FUNCTION_GET_INTERFACE                   = 0x0027,
	URB_FUNCTION_GET_DESCRIPTOR_FROM_INTERFACE   = 0x0028,
	URB_FUNCTION_SET_DESCRIPTOR_TO_INTERFACE     = 0x0029
};

enum USBD_PIPE_TYPE
{
	UsbdPipeTypeControl,
	UsbdPipeTypeIsochronous,
	UsbdPipeTypeBulk,
	UsbdPipeTypeInterrupt
};

enum USBD_TRANSFER_FLAGS : ULONG
{
	DirectionIn			=0x00000001,
	ShortTransferOk			=0x00000002,
	IsoTransferAsap	=0x00000004,
	DefaultPipeTransfer		=0x00000008,
};

enum USBD_PIPE_FLAGS
{
	ChangeMaxPacket = 0x00000001,
	ShortPacketOptimize = 0x00000002,
	EnableRTThreadAccess = 0x00000004,
	MapAddTransfers = 0x00000008
};


[display(format("{0b016x}", bmRequestType))]
union RequestType
{
	struct
	{
		UCHAR Recipient : 5;
		UCHAR RequestType : 2;
		UCHAR Direction : 1;
	} bmRequestTypeD;
	UCHAR bmRequestType;
};

enum USB_REQUEST_TYPE
{
	SET_CUR = 0x01,
	GET_CUR = 0x81,
	SET_MIN = 0x02,
	GET_MIN = 0x82,
	SET_MAX = 0x03,
	GET_MAX = 0x83,
	SET_RES = 0x04,
	GET_RES = 0x84,
	SET_MEM = 0x05,
	GET_MEM = 0x85,
	GET_STAT = 0xFF
};

struct USB_SETUP_PACKET
{
	RequestType request_type;
	BYTE bRequest;
	union
	{
		struct
		{
			BYTE low;
			BYTE high;
		} vb;
		WORD vw;
	} value;
	WORD wIndex;
	WORD wLength;
};

enum EUsbClass : BYTE
{
	UsbInterface = 0x00,		//Use class information in the Interface Descriptors
	UsbAudio = 0x01,			//Audio
	UsbCommunication = 0x02,	//Communications and CDC Control
	UsbHID = 0x03,			//HID(Human Interface Device)
	UsbPhysical = 0x05,		//Physical
	UsbImage = 0x06,			//Image
	UsbPrinter = 0x07,		//Printer
	UsbMassStorage = 0x08,	//Mass Storage
	UsbHub = 0x09,			//Hub
	UsbCommData = 0x0A,		//CDC - Data
	UsbSmartCard = 0x0B,		//Smart Card
	UsbSecurity = 0x0D,		//Content Security
	UsbVideo = 0x0E,			//Video
	UsbHealthcare = 0x0F,	//Personal Healthcare
	UsbAudioVideo = 0x10,	//Audio / Video Devices
	UsbBillboard = 0x11,		//Billboard Device Class
	UsbBridge = 0x12,		//USB Type - C Bridge Class
	UsbDiagnostic = 0xDC,	//Diagnostic Device
	UsbWirelessController = 0xE0,	//Wireless Controller
	UsbMiscellaneous = 0xEF,			//Miscellaneous
	UsbApplicationSpecific = 0xFE,	//Application Specific
	UsbVendorSpecific = 0xFF			//Vendor Specific
};

