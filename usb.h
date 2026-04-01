// Copyright (c) 2018 by HHD Software Ltd.
// This file is part of the HHD Software Device Monitoring Studio
// For usage and distribution policies, consult the license distributed with a product installation program

// Modification options:
// Trial mode: Modified file is loaded, compiled and used on startup
// Lite and Standard Editions: Protocol-related features are not available
// Professional Edition: Pre-configured version is used, changes in this file will be ignored
// Ultimate Edition: Modified file is loaded, compiled and used on startup

// See Usb packet at the bottom.

#pragma once

#pragma byte_order(LittleEndian)
#include "std_usbdefs.h"		// includes stddefs.h
#include "usb_video.h"			//USB Video Class Parser
#include "usb_audio.h"			//USB Audio Class Parser
#include "usb_comm.h"			//USB Communication Class Parser

enum USB_DESCRIPTOR_TYPE : BYTE
{
	USB_DEVICE_DESCRIPTOR_TYPE = 0x01,
	USB_CONFIGURATION_DESCRIPTOR_TYPE = 0x02,
	USB_STRING_DESCRIPTOR_TYPE = 0x03,
	USB_INTERFACE_DESCRIPTOR_TYPE = 0x04,
	USB_ENDPOINT_DESCRIPTOR_TYPE = 0x05,

	// USB 3.0 Descriptor Types
	USB_OTG_DESCRIPTOR_TYPE = 0x09,
	USB_DEBUG_DESCRIPTOR_TYPE = 0x0A,
	USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE = 0x0B,
	USB_SECURITY_DESCRIPTOR_TYPE = 0x0c,
	USB_KEY_DESCRIPTOR_TYPE = 0x0d,
	USB_ENCRYPTION_DESCRIPTOR_TYPE = 0x0e,

	USB_BOS_DESCRIPTOR_TYPE = 0x0F,
	USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE = 0x10,
	WIRELESS_ENDPOINT_COMPANION = 0x11,

	//hid
	HID_HID_DESCRIPTOR_TYPE             =0x21,
	HID_REPORT_DESCRIPTOR_TYPE          =0x22,

	USB_20_HUB_DESCRIPTOR_TYPE = 0x29,

	//USB 3.0
	USB_30_HUB_DESCRIPTOR_TYPE = 0x2A,

	//class specific
	CS_STRING = 0x23,
	CS_INTERFACE = 0x24,
	CS_ENDPOINT  = 0x25,

	USB_SUPERSPEED_ENDPOINT_COMPANION_DESCRIPTOR_TYPE = 0x30,
	SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION_TYPE = 0x31
};

function getDescriptorTypeFriendlyName(type)
{
	switch (type)
	{
	case USB_DEVICE_DESCRIPTOR_TYPE:
		return "Device Descriptor";
	case USB_CONFIGURATION_DESCRIPTOR_TYPE:
		return "Configuration Descriptor";
	case USB_STRING_DESCRIPTOR_TYPE:
		return "String Descriptor";
	case USB_INTERFACE_DESCRIPTOR_TYPE:
		return "Interface Descriptor";
	case USB_ENDPOINT_DESCRIPTOR_TYPE:
		return "Endpoint Descriptor";
	case USB_OTG_DESCRIPTOR_TYPE:
		return "On-The-Go Descriptor";
	case USB_DEBUG_DESCRIPTOR_TYPE:
		return "Debug Descriptor";
	case USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE:
		return "Interface Association Descriptor";
	case USB_SECURITY_DESCRIPTOR_TYPE:
		return "Security Descriptor";
	case USB_KEY_DESCRIPTOR_TYPE:
		return "Key Descriptor";
	case USB_ENCRYPTION_DESCRIPTOR_TYPE:
		return "Encryption Descriptor";
	case USB_BOS_DESCRIPTOR_TYPE:
		return "Binary Object Store Descriptor";
	case USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE:
		return "Device Capability Descriptor";
	case WIRELESS_ENDPOINT_COMPANION:
		return "Wireless Endpoint Companion Descriptor";
	case HID_HID_DESCRIPTOR_TYPE:
		return "HID Descriptor";
	case HID_REPORT_DESCRIPTOR_TYPE:
		return "HID Report Descriptor";
	case USB_20_HUB_DESCRIPTOR_TYPE:
		return "USB 2.0 Hub Descriptor";
	case USB_30_HUB_DESCRIPTOR_TYPE:
		return "USB 3.0 Hub Descriptor";
	case CS_STRING:
		return "Class-Specific String Descriptor";
	case CS_INTERFACE:
		return "Class-Specific Interface Descriptor";
	case CS_ENDPOINT:
		return "Class-Specific Endpoint Descriptor";
	case USB_SUPERSPEED_ENDPOINT_COMPANION_DESCRIPTOR_TYPE:
		return "SuperSpeed Endpoint Companion Descriptor";
	case SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION_TYPE:
		return "SuperSpeed Isochronous Endpoint Companion Descriptor";
	default:
		return "Unknown Descriptor";
	}
}

function convertToBCD(value)
{
	return format("{0}.{1}{2}", value >> 8, (value >> 4) & 0xf, value & 0xf);
}

function getUsagePageName(page)
{
	const pages1[]={ 
		"Undefined", 
		"Generic Desktop Controls", 
		"Simulation Controls",
		"VR Controls",
		"Sport Controls",
		"Game Controls",
		"Generic Device Controls",
		"Keyboard/Keypad",
		"LEDs",
		"Button",
		"Ordinal",
		"Telephony",
		"Consumer",
		"Digitizer",
		"PID Page",
		"Unicode"
	};
		
	if (page<0x11)
		return pages1[page];
	else if (page==0x14)
		return "Alphanumeric Display";
	else if (page==0x40)
		return "Medical Instruments";
	else if (0x80<=page && page<=0x83)
		return "Monitor";
	else if (0x84<=page && page<=0x87)
		return "Power";
	const pages2[]={
		"Bar Code Scanner",
		"Scale",
		"Magnetic Stripe Reading Devices",
		"Reserved Point of Sale",
		"Camera Control",
		"Arcade"
	};
	if (0x8c<=page && page<=0x91)
		return pages2[page-0x8c];
	else
		return "Unknown";
}

enum EndpointType : BYTE
{
	Control,
	Isochronous,
	Bulk,
	Interrupt
};

enum HID_COUNTRY_CODE : BYTE
{
	NotDefined,
	Arabic,
	Belgian,
	Canadian_Bilingual,
	Canadian_French,
	Czech_Republic,
	Danish,
	Finnish,
	French,
	German,
	Greek,
	Hebrew,
	Hungary,
	International,
	Italian,
	Japan_Katakana,
	Korean,
	Latin_American,
	Netherlands_Dutch,
	Norwegian,
	Persian_Farsi,
	Poland,
	Portuguese,
	Russia,
	Slovakia,
	Spanish,
	Swedish,
	Swiss_French,
	Swiss_German,
	Switzerland,
	Taiwan,
	Turkish_Q,
	UK,
	US,
	Yugoslavia,
	Turkish_F,
};

struct USB_DESCRIPTOR;

[display(getDescriptorTypeFriendlyName(bDescriptorType))]
struct USB_DESCRIPTOR
{
	var start_offset = current_offset;
	UCHAR bLength;
	[exact_only]
	USB_DESCRIPTOR_TYPE bDescriptorType;

	switch (bDescriptorType)
	{
		case USB_DEVICE_DESCRIPTOR_TYPE:
			[onread(convertToBCD(_1))]
			USHORT bcdUSB;
			UCHAR  bDeviceClass;
			UCHAR  bDeviceSubClass;
			UCHAR  bDeviceProtocol;
			UCHAR  bMaxPacketSize0;
			[format("b016x")]
			USHORT idVendor;
			$print("Vendor",usb_get_vendor_name(idVendor));
			[format("b016x")]
			USHORT idProduct;
			$print("Model",usb_get_model_name(idVendor, idProduct));
			[onread(convertToBCD(_1))]
			USHORT bcdDevice;
			UCHAR  iManufacturer;
			UCHAR  iProduct;
			UCHAR  iSerialNumber;
			UCHAR  bNumConfigurations;
			break;
		case USB_CONFIGURATION_DESCRIPTOR_TYPE:
			USHORT wTotalLength;
			UCHAR bNumInterfaces;
			UCHAR bConfigurationValue;
			UCHAR iConfiguration;

			UCHAR Reserved : 5;
			UCHAR SupportsRemoteWakeup : 1;
			UCHAR SelfPowered : 1;
			UCHAR PoweredByBus : 1;

			[onread(PoweredByBus ? format("{0b016x} -> {1} mA", _1, _1 * 2) : format("Unused {0}", _1))]
			UCHAR MaxPower;
			break;
		case USB_STRING_DESCRIPTOR_TYPE:
			var length=(bLength - 2) / sizeof(WCHAR);
			if (length > 0)
				WCHAR string[length];
			break;
		case USB_INTERFACE_DESCRIPTOR_TYPE:
			UCHAR bInterfaceNumber;
			UCHAR bAlternateSetting;
			UCHAR bNumEndpoints;
			EUsbClass bInterfaceClass;
			UCHAR bInterfaceSubClass;
			UCHAR bInterfaceProtocol;
			UCHAR iInterface;

			DeviceInterfaceClass = bInterfaceClass;
			DeviceInterfaceSubClass = bInterfaceSubClass;
			break;
		case USB_ENDPOINT_DESCRIPTOR_TYPE:
			UCHAR bEndpointAddress : 4;
			UCHAR Reserved : 3;

			[onread(_1 ? "Input" : "Output")]
			UCHAR Direction : 1;

			EndpointType type:2;
			UCHAR reserved:6;

			USHORT wMaxPacketSize;
			UCHAR bInterval;
			break;

		case USB_OTG_DESCRIPTOR_TYPE:
			union {
				[format("b2w8arf0")]
				BYTE bmValue;
				struct {
					BYTE SRP : 1;
					BYTE HNP : 1;
					BYTE ADP : 1;
					BYTE RSP : 1;
					BYTE Reserved : 4;
				}Attributes;
			}bmAttributes;

			if (current_offset - start_offset < bLength)
				WORD bcdOTG;
			break;

		case USB_DEBUG_DESCRIPTOR_TYPE:
			BYTE bDebugInEndpoint;
			BYTE bDebugOutEndpoint;
			break;

		case USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE:
			BYTE  bFirstInterface;
			BYTE  bInterfaceCount;
			BYTE  bFunctionClass;
			BYTE  bFunctionSubClass;
			BYTE  bFunctionProtocol;
			BYTE  iFunction;
			break;

		case USB_SECURITY_DESCRIPTOR_TYPE:
			WORD wTotalLength;
			BYTE bNumEncryptionTypes;
			break;
		case USB_KEY_DESCRIPTOR_TYPE:
			BYTE tTKID[3];
			BYTE bReserved;
			if(bLength - 6 > 0)
				BYTE bKeyData[bLength - 6];
			break;
		case USB_ENCRYPTION_DESCRIPTOR_TYPE:
			enum :BYTE 
			{
				Unsecure,
				Wired,
				CCM,
				RSA
			}bEncryptionType;
			BYTE bEncryptionValue;
			BYTE bAuthKeyIndex;
			break;

		case USB_BOS_DESCRIPTOR_TYPE:
			WORD wTotalLength;
			BYTE bNumDeviceCaps;

			struct UsbDeviceCapabilityDescriptor
			{
				BYTE bLength;
				BYTE bDescriptorType; //USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE
				enum : BYTE
				{
					WirelessUSB = 0x01,
					Usb20Extension,
					SuperspeedUSB,
					ContainerID,
					Platform,
					PowerDeliveryCapability,
					BatteryInfoCapability,
					PdConsumerPortCapability,
					PdProviderPortCapability,
					SuperspeedPlus,
					PrecisionTimeMeasurement,
					WirelessUsbExt
				}bDevCapabilityType;

				switch (bDevCapabilityType)
				{
				case WirelessUSB:
					union {
						[format("b2w8arf0")]
						BYTE bmValue;
						struct {
							BYTE Reserved : 1;
							BYTE P2P_DRD : 1;
							BYTE BeaconBehavior : 2;
							BYTE PowerIndication : 1;
							BYTE Reserved1 : 3;
						}Attributes;
					}bmAttributes;

					union {
						[format("b2w16arf0")]
						WORD wPHYRates;
						struct {
							WORD PHY_53:1;
							WORD PHY_80:1;
							WORD PHY_107:1;
							WORD PHY_160:1;
							WORD PHY_200:1;
							WORD PHY_320:1;
							WORD PHY_400:1;
							WORD PHY_480:1;
							WORD Reserved:8;
						}bits;
					}PHYRates; //Mbps

					BYTE bmTFITXPowerInfo;
					BYTE bmFFITXPowerInfo;
					WORD bmBandGroup;
					BYTE bReserved;
					break;

				case Usb20Extension:
					union {
						[format("b2w32arf0")]
						DWORD bmValue;
						struct {
							DWORD Reserved : 1;
							DWORD LPM : 1;
							DWORD Reserved1 : 30;
						}Extension;
					}bmAttributes;
					break;

				case SuperspeedUSB:
					union {
						[format("b2w8arf0")]
						BYTE bmValue;
						struct {
							UCHAR Reserved : 1;
							UCHAR LTM : 1;
							UCHAR Reserved1 : 6;
						}Attributes;
					}bmAttributes;

					union {
						[format("b2w16arf0")]
						WORD wSpeedsSupported;
						struct {
							WORD LowSpeedUSB : 1;
							WORD FullSpeedUSB : 1;
							WORD HighSpeedUSB : 1;
							WORD Gen1Speed: 1;
							WORD Reserved1 : 12;
						}SpeedsSupported;
					}bmSpeedsSupported;

					BYTE bFunctionalitySupport;
					
					//[format("Less than b016x  s")]
					BYTE bU1DeviceExitLatency;
					WORD bU2DeviceExitLatency;
					break;

				case ContainerID:
					BYTE bReserved;
					GUID ContainerID;
					break;

				case Platform:
					BYTE bReserved;
					GUID PlatformCapabilityUUID;
					BYTE CapabilityData[bLength - 17];
					break;

				case PowerDeliveryCapability:
					BYTE bReserved;
					union {
						[format("b2w32arf0")]
						DWORD bmValue;
						struct {
							DWORD Reserved : 1;
							DWORD BatteryCharging : 1;
							DWORD UsbPowerDelivery : 1;
							DWORD Provider : 1;
							DWORD Consumer : 1;
							DWORD ChargingPolicySupport : 1;
							DWORD UsbTypeC : 1;
							DWORD Reserved1 : 1;
							//bmPowerSource
							DWORD AcSupply : 1;
							DWORD Battery : 1;
							DWORD Other : 1;
							DWORD NumBatteries : 3;
							DWORD Vbus : 1;
							DWORD Reserved2 : 1;
							//reserved
							DWORD Reserved3 : 16;
						}PowerDelivery;
					}bmAttributes;
					WORD bcdBCVersion;
					WORD bcdPDVersion;
					WORD bcdUSBTypeCVersion;
					break;

				case BatteryInfoCapability:
					BYTE iBattery;
					BYTE iSerial;
					BYTE iManufacturer;
					BYTE bBatteryId;
					BYTE bReserved;
					DWORD dwChargedThreshold;
					DWORD dwWeakThreshold;
					DWORD dwBatteryDesignCapacity;
					DWORD dwBatteryLastFullchargeCapacity;
					break;

				case PdConsumerPortCapability:
					union {
						[format("b2w16arf0")]
						WORD wCapabilities;
						struct {
							WORD BatteryCharging : 1;
							WORD UsbPowerDelivery : 1;
							WORD UsbTypeC : 1;
							WORD Reserved1 : 13;
						}Capabilities;
					}bmCapabilities;

					WORD wMinVoltage;
					WORD wMaxVoltage;
					WORD wReserved;
					DWORD dwMaxOperatingPower;
					DWORD dwMaxPeakPower;
					DWORD dwMaxPeakPowerTime;
					break;

				case PdProviderPortCapability:
					union {
						[format("b2w16arf0")]
						WORD wCapabilities;
						struct {
							WORD BatteryCharging : 1;
							WORD UsbPowerDelivery : 1;
							WORD UsbTypeC : 1;
							WORD Reserved1 : 13;
						}Capabilities;
					}bmCapabilities;
					BYTE bNumOfPDObjects;
					BYTE bReserved;
					DWORD PowerDataObject[bNumOfPDObjects];
					break;

				case SuperspeedPlus:
					var AttributeCount = 0;
					BYTE bReserved;
					union {
						[format("b2w32arf0")]
						DWORD bmValue;
						struct {
							DWORD SublinkSpeedAttributeCount : 5;
							DWORD SublinkSpeedIdCount : 5;
							DWORD Reserved : 22;
							AttributeCount = SublinkSpeedAttributeCount;
						}SuperSpeedPlus;
					}bmAttributes;

					union {
						[format("b2w16arf0")]
						WORD bmValue;
						struct {
							WORD SublinkSpeedAttributeID : 4;
							WORD Reserved : 4;
							WORD MinRxLaneCount : 4;
							WORD MinTxLaneCount : 4;
						}FunctionalitySupport;
					}bmFunctionalitySupport;
					
					WORD wReserved;

					union {
						[format("b2w32arf0")]
						DWORD bmValue;
						struct {
							DWORD SublinkSpeedAttributeID : 4;
							DWORD LaneSpeedExponent : 2;
							DWORD SublinkType : 2;
							DWORD Reserved : 6;
							DWORD LinkProtocol : 2;
							DWORD LaneSpeedMantissa : 16;
						}SublinkSpeedAttr;
					}bmSublinkSpeedAttr[AttributeCount];
					
					break;

				case WirelessUsbExt:
					WORD wIdleTimeout;
					WORD wWakeUpLatency;
					BYTE bmControl;
					break;

				default:
					BYTE DeviceCapabilityData[bLength - 3];
				}
			}sub_descriptors[bNumDeviceCaps];

			break;
		//case USB_DEVICE_CAPABILITY_DESCRIPTOR_TYPE:
		//	break;

		case WIRELESS_ENDPOINT_COMPANION:
			BYTE bMaxBurst;
			BYTE bMaxSequence;
			WORD wMaxStreamDelay;
			WORD wOverTheAirPacketSize;
			BYTE bOverTheAirInterval;

			enum Attributes : BYTE 
			{
				NoDynamicSwitching = 0,
				DynamicSwitching,
				DynamicSwitchingAndContinuouslyScalable,
				Reserved
			}bmCompAttributes;
			break;

		case USB_20_HUB_DESCRIPTOR_TYPE:
			UCHAR   bNumberOfPorts;
			USHORT  wHubCharacteristics;
			UCHAR   bPowerOnToPowerGood;
			UCHAR   bHubControlCurrent;
			UCHAR   bRemoveAndPowerMask[64];
			break;

		case USB_30_HUB_DESCRIPTOR_TYPE:
			UCHAR   bNumberOfPorts;
			USHORT  wHubCharacteristics;
			UCHAR   bPowerOnToPowerGood;
			UCHAR   bHubControlCurrent;
			UCHAR   bHubHdrDecLat;
			USHORT  wHubDelay;
			USHORT  DeviceRemovable;
			break;

		case USB_SUPERSPEED_ENDPOINT_COMPANION_DESCRIPTOR_TYPE:
			UCHAR bMaxBurst;
			union {
				[format("b2w8arf0")]
				UCHAR AsUchar;
				struct {
					UCHAR MaxStreams : 5;
					UCHAR Reserved1 : 3;
				}Bulk;
				struct {
					UCHAR Mult : 2;
					UCHAR Reserved2 : 6;
				}Isochronous;
			}bmAttributes;
			USHORT wBytesPerInterval;
			break;

		case SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION_TYPE:
			WORD wReserved;
			DWORD dwBytesPerInterval;
			break;

		case HID_HID_DESCRIPTOR_TYPE:
			if(DeviceInterfaceClass == UsbHID)
			{
				[onread(convertToBCD(_1))]
				USHORT  bcdHID;
				[exact_only]
				HID_COUNTRY_CODE bCountry;
				UCHAR bNumDescriptors;
				struct
				{
					UCHAR bReportType;
					USHORT wReportLength;
					UCHAR raw[wReportLength];
				} reports[bNumDescriptors];
			}
			break;
		case CS_INTERFACE:
			BYTE bDescriptorSubtype; // descriptor subtype.

			switch (DeviceInterfaceClass)
			{
			//case 	UsbInterface:
			//	break;
			case 	UsbAudio:
				switch (DeviceInterfaceSubClass)
				{
				case AC_AUDIOCONTROL:
					AudioControlInterface ac_interface;
					break;
				case AC_AUDIOSTREAMING:
					AudioStreamingInterface as_interface;
					break;
				case AC_MIDISTREAMING:
					MidiStreamingInterface ms_interface;
					break;
				}
				break;
			case 	UsbCommunication:
				CommDescriptor comm_interface;
				break;
			//case 	UsbHID:
			//	break;
			//case 	UsbPhysical:
			//	break;
			//case 	UsbImage:
			//	break;
			//case 	UsbPrinter:
			//	break;
			//case 	UsbMassStorage:
			//	break;
			//case 	UsbHub:
			//	break;
			//case 	UsbCommData:
			//	break;
			//case 	UsbSmartCard:
			//	break;
			//case 	UsbSecurity:
			//	break;
			case 	UsbVideo:
				switch (DeviceInterfaceSubClass)
				{
				case SC_VIDEOCONTROL:
					VideoControlDescriptor video_control;
					break;
				case SC_VIDEOSTREAMING:
					VideoStreamingDescriptor video_streamnig;
					break;
				case SC_VIDEO_INTERFACE_COLLECTION:
					VideoInterfaceCollection interface_collection;
					break;
				}
				break;
			//case 	UsbHealthcare:
			//	break;
			//case 	UsbAudioVideo:
			//	break;
			//case 	UsbBillboard:
			//	break;
			//case 	UsbBridge:
			//	break;
			//case 	UsbDiagnostic:
			//	break;
			//case 	UsbWirelessController:
			//	break;
			//case 	UsbMiscellaneous:
			//	break;
			//case 	UsbApplicationSpecific:
			//	break;
			//case 	UsbVendorSpecific:
			//	break;
			}

			break;
		case CS_ENDPOINT:
			switch (DeviceInterfaceClass)
			{
			case 	UsbAudio:
				switch (DeviceInterfaceSubClass)
				{
				case AC_AUDIOCONTROL:
					ACInterruptEndpointDescriptor interrupt_endpoint;
					break;
				case AC_AUDIOSTREAMING:
					IsochronousAudioDataEndpointDescriptor iso_endpoint;
					break;
				}
				break;
			case UsbVideo:
				BYTE bDescriptorSubType;
				switch (DeviceInterfaceSubClass)
				{
				case SC_VIDEOCONTROL:
					if (bDescriptorSubType == EP_INTERRUPT)
						VideoControlEndpointDescriptor control_endpoint;
					break;
				case SC_VIDEOSTREAMING:
					//IsochronousAudioDataEndpointDescriptor iso_endpoint;
					break;
				}
				break;
			}
			break;
		default:
			UCHAR raw[bLength - 2];
	}

	var plength = current_offset - start_offset;
	if (plength < bLength)
		UCHAR unknown[bLength - plength];
	else if (plength > bLength)
		$shift_by(bLength - plength);
};

enum HID_ITEM_TYPE : BYTE
{
	Main,
	Global,
	Local,
	Reserved
};

enum HID_MAIN_TAG : BYTE
{
	Input=8,
	Output,
	Collection,
	Feature,
	EndCollection,
};

enum HID_GLOBAL_TAG : BYTE
{
	UsagePage,
	LogicalMinimum,
	LogicalMaximum,
	PhysicalMinimum,
	PhysicalMaximum,
	UnitExponent,
	Unit,
	ReportSize,
	ReportID,
	ReportCount,
	Push,
	Pop,
};

enum HID_LOCAL_TAG : BYTE
{
	Usage,
	UsageMinimum,
	UsageMaximum,
	DesignatorIndex,
	DesignatorMinimum,
	DesignatorMaximum,
	StringIndex,
	StringMinimum,
	StringMaximum,
	Delimiter,
};

[display(format("{0}, {1}, {2}, {3}, {4}, {5}, {6}",
	!b0 ? "Data" : "Constant",
	!b1 ? "Array" : "Variable",
	!b2 ? "Absolute" : "Relative",
	!b3 ? "No Wrap" : "Wrap",
	!b4 ? "Linear" : "Non-Linear",
	!b5 ? "Preferred State" : "No Preferred",
	!b6 ? "No Null Position" : "Null State"
))]
struct HID_MAIN_INPUT
{
	enum : BYTE { Data, Constant} b0:1;
	enum : BYTE { Array, Variable} b1:1;
	enum : BYTE { Absolute, Relative } b2:1;
	enum : BYTE { NoWrap, Wrap} b3:1;
	enum : BYTE { Linear,NonLinear} b4:1;
	enum : BYTE { PreferredState, NoPreferred} b5:1;
	enum : BYTE { NoNullPosition,NullState} b6:1;
};

[display(format("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}{8}",
	!b0 ? "Data" : "Constant",
	!b1 ? "Array" : "Variable",
	!b2 ? "Absolute" : "Relative",
	!b3 ? "No Wrap" : "Wrap",
	!b4 ? "Linear" : "Non-Linear",
	!b5 ? "Preferred State" : "No Preferred",
	!b6 ? "No Null Position" : "Null State",
	!b7 ? "Non Volatile" : "Volatile",
	is_valid(b8)? ", " + (!b8 ? "Bit Field" : "Buffered Bytes") : ""
))]
struct HID_MAIN_OUTPUT_OR_FEATURE
{
	enum : BYTE { Data, Constant} b0:1;
	enum : BYTE { Array, Variable} b1:1;
	enum : BYTE { Absolute, Relative } b2:1;
	enum : BYTE { NoWrap, Wrap} b3:1;
	enum : BYTE { Linear,NonLinear} b4:1;
	enum : BYTE { PreferredState, NoPreferred} b5:1;
	enum : BYTE { NoNullPosition,NullState} b6:1;
	enum : BYTE { NonVolatile, Volatile } b7:1;
	if (data_size==2)
	{
		enum : BYTE { BitField, BufferedBytes } b8:1;
		BYTE reserved:7;
	}
};

[display(value)]
struct HID_UNSIGNED_VARIABLE_FIELD
{
	switch (data_size)
	{
		case 1:
			UCHAR value;
			break;
		case 2:
			USHORT value;
			break;
		case 4:
			ULONG value;
	}
};

[display(value)]
struct HID_SIGNED_VARIABLE_FIELD
{
	switch (data_size)
	{
		case 1:
			char value;
			break;
		case 2:
			short value;
			break;
		case 4:
			int value;
	}
};

struct HID_REPORT_ITEM
{
	UCHAR size:2;
	[exact_only]
	HID_ITEM_TYPE type:2;
	switch (type)
	{
		case Main:
			[exact_only]
			HID_MAIN_TAG tag:4;
			break;
		case Global:
			[exact_only]
			HID_GLOBAL_TAG tag:4;
			break;
		case Local:
			[exact_only]
			HID_LOCAL_TAG tag:4;
			break;
		default:
			UCHAR tag:4;
	}
	
	if (size==2 && type==Reserved && tag==0xf)
	{
		// long item, skip for now
		UCHAR longDataSize;
		UCHAR longItemTag;
		UCHAR optional_data[longDataSize];		
	} else
	{
		var data_size = size == 3 ? 4 : size;
		var stored_offset = current_offset;
		
		switch (type)
		{
			case Main:
				switch (tag)
				{
					case Input:
						if (data_size==1)
							HID_MAIN_INPUT input;					
						break;
					case Output:
						if (data_size==1 || data_size==2)
							HID_MAIN_OUTPUT_OR_FEATURE output;
						break;
					case Feature:
						if (data_size==1 || data_size==2)
							HID_MAIN_OUTPUT_OR_FEATURE feature;
						break;
					case Collection:
						if (data_size>=1)
							enum : BYTE
							{
								Physical,
								Application,
								Logical,
								Report,
								NamedArray,
								UsageSwitch,
								UsageModifier,
							} collection;
						break;
				}
				break;
			case Global:
				switch(tag)
				{
					case ReportSize:
					case ReportCount:
					case ReportID:
					case Push:
					case Pop:
						HID_UNSIGNED_VARIABLE_FIELD value;
						break;
					case LogicalMinimum:
					case LogicalMaximum:
					case PhysicalMinimum:
					case PhysicalMaximum:
						HID_SIGNED_VARIABLE_FIELD value;
						break;
					case UsagePage:
						HID_UNSIGNED_VARIABLE_FIELD value;
						$print("page", getUsagePageName(value.value));
						break;
				}
//	UnitExponent,
//	Unit,
				break;
			case Local:
				HID_UNSIGNED_VARIABLE_FIELD value;
				break;
		}
				
		if (current_offset!=stored_offset+data_size)
			UCHAR optional_data[stored_offset+data_size-current_offset];
	}
};

struct HID_REPORT_DESCRIPTOR
{
	HID_REPORT_ITEM items[*];
};

// Status code enumeration
enum StatusCode : ULONG
{
	SUCCESS = 0,
	CRC = 0xC0000001,
	BTSTUFF = 0xC0000002,
	DATA_TOGGLE_MISMATCH = 0xC0000003,
	STALL_PID = 0xC0000004,
	DEV_NOT_RESPONDING = 0xC0000005,
	PID_CHECK_FAILURE = 0xC0000006,
	UNEXPECTED_PID = 0xC0000007,
	DATA_OVERRUN = 0xC0000008,
	DATA_UNDERRUN = 0xC0000009,
	RESERVED1 = 0xC000000A,
	RESERVED2 = 0xC000000B,
	BUFFER_OVERRUN = 0xC000000C,
	BUFFER_UNDERRUN = 0xC000000D,
	NOT_ACCESSED = 0xC000000F,
	FIFO = 0xC0000010,
	XACT_ERROR = 0xC0000011,
	BABBLE_DETECTED = 0xC0000012,
	DATA_BUFFER_ERROR = 0xC0000013,
	ENDPOINT_HALTED = 0xC0000030,
	INVALID_URB_FUNCTION = 0x80000200,
	INVALID_PARAMETER = 0x80000300,
	ERROR_BUSY = 0x80000400,
	INVALID_PIPE_HANDLE = 0x80000600,
	NO_BANDWIDTH = 0x80000700,
	INTERNAL_HC_ERROR = 0x80000800,
	ERROR_SHORT_TRANSFER = 0x80000900,
	BAD_START_FRAME = 0xC0000A00,
	ISOCH_REQUEST_FAILED = 0xC0000B00,
	FRAME_CONTROL_OWNED = 0xC0000C00,
	FRAME_CONTROL_NOT_OWNED = 0xC0000D00,
	NOT_SUPPORTED = 0xC0000E00,
	INAVLID_CONFIGURATION_DESCRIPTOR = 0xC0000F00,
	INVALID_CONFIGURATION_DESCRIPTOR = 0xC0000F00,
	INSUFFICIENT_RESOURCES = 0xC0001000,
	SET_CONFIG_FAILED = 0xC0002000,
	BUFFER_TOO_SMALL = 0xC0003000,
	INTERFACE_NOT_FOUND = 0xC0004000,
	INAVLID_PIPE_FLAGS = 0xC0005000,
	TIMEOUT = 0xC0006000,
	DEVICE_GONE = 0xC0007000,
	STATUS_NOT_MAPPED = 0xC0008000,
	HUB_INTERNAL_ERROR = 0xC0009000,
	CANCELED = 0xC0010000,
	ISO_NOT_ACCESSED_BY_HW = 0xC0020000,
	ISO_TD_ERROR = 0xC0030000,
	ISO_NA_LATE_USBPORT = 0xC0040000,
	ISO_NOT_ACCESSED_LATE = 0xC0050000,
	BAD_DESCRIPTOR = 0xC0100000,
	BAD_DESCRIPTOR_BLEN = 0xC0100001,
	BAD_DESCRIPTOR_TYPE = 0xC0100002,
	BAD_INTERFACE_DESCRIPTOR = 0xC0100003,
	BAD_ENDPOINT_DESCRIPTOR = 0xC0100004,
	BAD_INTERFACE_ASSOC_DESCRIPTOR = 0xC0100005,
	BAD_CONFIG_DESC_LENGTH = 0xC0100006,
	BAD_NUMBER_OF_INTERFACES = 0xC0100007,
	BAD_NUMBER_OF_ENDPOINTS = 0xC0100008,
	BAD_ENDPOINT_ADDRESS = 0xC0100009,
};

struct USBD_STATUS
{
	StatusCode Status;
	switch (Status >> 28)
	{
	case 0:
		$print("Type", "Success");
		break;
	case 1:
		$print("Type", "Pending");
		break;
	case 2:
	case 3:
		$print("Type", "Error");
		break;
	}
};

struct URB_HEADER
{
	// Fields filled in by client driver
	USHORT Length;
	URB_FUNCTION Function;
	USBD_STATUS Status;
	// Fields used only by USBD
	PVOID UsbdDeviceHandle; // device handle assigned to this device by USBD
	PVOID UsbdFlags;        // flags field reserved for USBD use.
};

struct URB_HCD_AREA
{
	PVOID Reserved8[8];
};

[category(protocol)]
public struct UsbPayload
{
	// General packet payload data
	BYTE Payload[packet_size - current_offset];
};

[category(protocol)]
public struct UsbConfigDescriptor
{
	var DeviceInterfaceClass = 0;
	var DeviceInterfaceSubClass = 0;

	USB_DESCRIPTOR descriptors[*];
};

 struct URB_BULK_OR_INTERRUPT_TRANSFER
{
	[format("b016x")]
	USBD_PIPE_HANDLE PipeHandle;
	USBD_TRANSFER_FLAGS TransferFlags;                // note: the direction bit will be set by USBD
	ULONG TransferBufferLength;
	[format("b016x")]
	PVOID TransferBuffer;
	[format("b016x")]
	PVOID TransferBufferMDL;             // *optional*
	PVOID UrbLink;
	URB_HCD_AREA hca;           // fields for HCD use
	UsbPayload Payload;
};

struct URB_CONTROL_DESCRIPTOR_REQUEST
{
	PVOID Reserved;
	ULONG Reserved0;
	ULONG TransferBufferLength;
	[format("b016x")]
	PVOID TransferBuffer;
	[format("b016x")]
	PMDL TransferBufferMDL;             // *optional*
	PVOID UrbLink;               // *reserved MBZ*
	URB_HCD_AREA hca;           // fields for HCD use
	USHORT Reserved1;
	UCHAR Index;
	[exact_only]
	USB_DESCRIPTOR_TYPE DescriptorType;
	USHORT LanguageId;
	USHORT Reserved2;

	if (is_packet_up)
		switch (DescriptorType)
		{
			case USB_DEVICE_DESCRIPTOR_TYPE:
			case USB_CONFIGURATION_DESCRIPTOR_TYPE:
			case USB_STRING_DESCRIPTOR_TYPE:
				var DeviceInterfaceClass = 0;
				var DeviceInterfaceSubClass = 0;

				USB_DESCRIPTOR descriptors[*];
				break;
			default:
				UsbPayload Payload;
		}
};

struct USBD_ISO_PACKET_DESCRIPTOR
{
	ULONG Offset;       // INPUT Offset of the packet from the begining of the buffer.
	ULONG Length;       // OUTPUT length of data received (for in). OUTPUT 0 for OUT.
	USBD_STATUS Status; // status code for this packet.
};

struct URB_ISOCH_TRANSFER
{
	// This block is the same as CommonTransfer
	[format("b016x")]
	USBD_PIPE_HANDLE PipeHandle;
	USBD_TRANSFER_FLAGS TransferFlags;
	ULONG TransferBufferLength;
	[format("b016x")]
	PVOID TransferBuffer;
	[format("b016x")]
	PMDL TransferBufferMDL;             // *optional*
	PVOID UrbLink;               // *optional* link to next urb request
								 // if this is a chain of commands
	URB_HCD_AREA hca;           // fields for HCD use

								//
								// this block contains transfer fields
								// specific to isochronous transfers
								//

								// 32 bit frame number to begin this transfer on, must be within 1000
								// frames of the current USB frame or an error is returned.

								// START_ISO_TRANSFER_ASAP flag in transferFlags:
								// If this flag is set and no transfers have been submitted
								// for the pipe then the transfer will begin on the next frame
								// and StartFrame will be updated with the frame number the transfer
								// was started on.
								// If this flag is set and the pipe has active transfers then
								// the transfer will be queued to begin on the frame after the
								// last transfer queued is completed.
								//
	ULONG StartFrame;
	// number of packets that make up this request
	ULONG NumberOfPackets;
	// number of packets that completed with errors
	ULONG ErrorCount;
	USBD_ISO_PACKET_DESCRIPTOR IsoPacket;
	UsbPayload Payload;
};

struct URB_CONTROL_TRANSFER
{
	[format("b016x")]
	USBD_PIPE_HANDLE PipeHandle;
	USBD_TRANSFER_FLAGS TransferFlags;
	ULONG TransferBufferLength;
	[format("b016x")]
	PVOID TransferBuffer;
	[format("b016x")]
	PMDL TransferBufferMDL;             // *optional*
	PVOID UrbLink;               // *reserved MBZ*
	URB_HCD_AREA hca;           // fields for HCD use
								//UCHAR SetupPacket[8];
};

struct _USB_CONFIGURATION_DESCRIPTOR
{
	UCHAR bLength;
	UCHAR bDescriptorType;
	USHORT wTotalLength;
	UCHAR bNumInterfaces;
	UCHAR bConfigurationValue;
	UCHAR iConfiguration;
	UCHAR bmAttributes;
	UCHAR MaxPower;
};

struct USBD_PIPE_INFORMATION
{
	//
	// OUTPUT
	// These fields are filled in by USBD
	//
	USHORT MaximumPacketSize;  // Maximum packet size for this pipe
	UCHAR EndpointAddress;     // 8 bit USB endpoint address (includes direction)
							   // taken from endpoint descriptor
	UCHAR Interval;            // Polling interval in ms if interrupt pipe

	USBD_PIPE_TYPE PipeType;   // PipeType identifies type of transfer valid for this pipe
	[format("b016x")]
	USBD_PIPE_HANDLE PipeHandle;

	//
	// INPUT
	// These fields are filled in by the client driver
	//
	ULONG MaximumTransferSize; // Maximum size for a single request
							   // in bytes.
	USBD_PIPE_FLAGS PipeFlags;
};

struct USBD_INTERFACE_INFORMATION
{
	USHORT Length;       // Length of this structure, including
						 // all pipe information structures that
						 // follow.
						 //
						 // INPUT
						 //
						 // Interface number and Alternate setting this
						 // structure is associated with
						 //
	UCHAR InterfaceNumber;
	UCHAR AlternateSetting;

	//
	// OUTPUT
	// These fields are filled in by USBD
	//
	UCHAR Class;
	UCHAR SubClass;
	UCHAR Protocol;
	UCHAR Reserved;

	USBD_INTERFACE_HANDLE InterfaceHandle;
	ULONG NumberOfPipes;

	UCHAR pad[current_offset % sizeof(PVOID)];
	//
	// INPUT/OUPUT
	// see PIPE_INFORMATION

	USBD_PIPE_INFORMATION Pipes[NumberOfPipes];
};

struct URB_SELECT_CONFIGURATION
{
	// NULL indicates to set the device
	// to the 'unconfigured' state
	// ie set to configuration 0
	//   PUSB_CONFIGURATION_DESCRIPTOR ConfigurationDescriptor;
	//    USBD_CONFIGURATION_HANDLE ConfigurationHandle;
	PVOID ConfigurationDescriptor;
	USBD_CONFIGURATION_HANDLE ConfigurationHandle;
	USBD_INTERFACE_INFORMATION Interface;
};

struct URB_SELECT_INTERFACE
{
	USBD_CONFIGURATION_HANDLE ConfigurationHandle;
	// client must input AlternateSetting & Interface Number
	// class driver returns interface and handle
	// for new alternate setting
	USBD_INTERFACE_INFORMATION Interface;
};

struct URB_PIPE_REQUEST
{
	[format("b016x")]
	USBD_PIPE_HANDLE PipeHandle;
	ULONG Reserved;
};

struct URB_CONTROL_GET_STATUS_REQUEST
{
	PVOID Reserved;
	ULONG Reserved0;
	ULONG TransferBufferLength;
	[format("b016x")]
	PVOID TransferBuffer;
	[format("b016x")]
	PMDL TransferBufferMDL;             // *optional*
	PVOID UrbLink;               // *reserved MBZ*
	URB_HCD_AREA hca;           // fields for HCD use
	UCHAR Reserved1[4];
	USHORT Index;                       // zero, interface or endpoint
	USHORT Reserved2;
	UsbPayload Payload;
};

struct URB_CONTROL_FEATURE_REQUEST
{
	PVOID Reserved;
	ULONG Reserved2;
	ULONG Reserved3;
	PVOID Reserved4;
	PMDL Reserved5;
	PVOID UrbLink;               // *reserved MBZ*
	URB_HCD_AREA hca;           // fields for HCD use
	USHORT Reserved0;
	USHORT FeatureSelector;
	USHORT Index;                       // zero, interface or endpoint
	USHORT Reserved1;
};

struct URB_CONTROL_VENDOR_OR_CLASS_REQUEST
{
	PVOID Reserved;
	USBD_TRANSFER_FLAGS TransferFlags;
	ULONG TransferBufferLength;
	[format("b016x")]
	PVOID TransferBuffer;
	[format("b016x")]
	PMDL TransferBufferMDL;             // *optional*
	PVOID UrbLink;               // *reserved MBZ*
	URB_HCD_AREA hca;           // fields for HCD use
								//UCHAR RequestTypeReservedBits;
								//UCHAR Request;
								//USHORT Value;
								//USHORT Index;
								//USHORT Reserved1;
};

struct URB_CONTROL_GET_INTERFACE_REQUEST
{
	PVOID Reserved;
	ULONG Reserved0;
	ULONG TransferBufferLength;
	[format("b016x")]
	PVOID TransferBuffer;
	[format("b016x")]
	PMDL TransferBufferMDL;             // *optional*
	PVOID UrbLink;               // *reserved MBZ*
	URB_HCD_AREA hca;           // fields for HCD use
	UCHAR Reserved1[4];
	USHORT Interface;
	USHORT Reserved2;
	UsbPayload Payload;
};

struct URB_GET_FRAME_LENGTH
{
	ULONG FrameLength;
	ULONG FrameNumber;
};

struct URB_SET_FRAME_LENGTH
{
	LONG FrameLengthDelta;
};

struct URB_GET_CURRENT_FRAME_NUMBER
{
	ULONG FrameNumber;
};

struct URB
{
	URB_HEADER UrbHeader;
	switch (UrbHeader.Function)
	{
		// Descriptor requests
	case URB_FUNCTION_GET_DESCRIPTOR_FROM_DEVICE:
	case URB_FUNCTION_GET_DESCRIPTOR_FROM_ENDPOINT:
	case URB_FUNCTION_GET_DESCRIPTOR_FROM_INTERFACE:
		URB_CONTROL_DESCRIPTOR_REQUEST UrbControlDescriptorRequest;
		break;
	case URB_FUNCTION_SET_DESCRIPTOR_TO_DEVICE:
	case URB_FUNCTION_SET_DESCRIPTOR_TO_ENDPOINT:
	case URB_FUNCTION_SET_DESCRIPTOR_TO_INTERFACE:
		URB_CONTROL_DESCRIPTOR_REQUEST UrbControlDescriptorRequest;
		break;
	case URB_FUNCTION_BULK_OR_INTERRUPT_TRANSFER:
	case URB_FUNCTION_GET_CONFIGURATION:
		URB_BULK_OR_INTERRUPT_TRANSFER BulkOrInterrupt;
		break;
	case URB_FUNCTION_ISOCH_TRANSFER:
		URB_ISOCH_TRANSFER UrbIsochronousTransfer;
		break;
	case URB_FUNCTION_CONTROL_TRANSFER:
		URB_CONTROL_TRANSFER UrbControlTransfer;
		USB_SETUP_PACKET setup_packet;

		if (setup_packet.bRequest == 0x6 /* GET DESCRIPTOR */ && setup_packet.request_type.bmRequestTypeD.Direction == 1)
		{
			switch (setup_packet.value.vb.high)
			{
				case USB_DEVICE_DESCRIPTOR_TYPE:
				case USB_CONFIGURATION_DESCRIPTOR_TYPE:
				case USB_STRING_DESCRIPTOR_TYPE:
					var DeviceInterfaceClass = 0;
					var DeviceInterfaceSubClass = 0;

					USB_DESCRIPTOR descriptors[*];
					break;
				case HID_REPORT_DESCRIPTOR_TYPE:
					HID_REPORT_DESCRIPTOR hid_report_descriptor;
					break;
			}
		}
		else
		{
			var Class = usb_getclass(device_source);

			switch (Class)
			{
			case USB_DEVICE_CLASS_VIDEO:
				$remove_to(ref(setup_packet));
				VideoControlRequest video;
				break;
			case USB_DEVICE_CLASS_AUDIO:
				$remove_to(ref(setup_packet));
				AudioRequest audio;
				break;
			}
		}
		break;
	case URB_FUNCTION_SELECT_CONFIGURATION:
		URB_SELECT_CONFIGURATION UrbSelectConfiguration;
		break;
	case URB_FUNCTION_SELECT_INTERFACE:
		URB_SELECT_INTERFACE UrbSelectInterface;
		break;
	case URB_FUNCTION_ABORT_PIPE:
	case URB_FUNCTION_RESET_PIPE:
		URB_PIPE_REQUEST UrbPipeRequest;
		break;
	case URB_FUNCTION_GET_STATUS_FROM_DEVICE:
	case URB_FUNCTION_GET_STATUS_FROM_INTERFACE:
	case URB_FUNCTION_GET_STATUS_FROM_ENDPOINT:
	case URB_FUNCTION_GET_STATUS_FROM_OTHER:
		URB_CONTROL_GET_STATUS_REQUEST UrbControlGetStatusRequest;
		break;
	case URB_FUNCTION_SET_FEATURE_TO_DEVICE:
	case URB_FUNCTION_SET_FEATURE_TO_INTERFACE:
	case URB_FUNCTION_SET_FEATURE_TO_ENDPOINT:
	case URB_FUNCTION_SET_FEATURE_TO_OTHER:
	case URB_FUNCTION_CLEAR_FEATURE_TO_DEVICE:
	case URB_FUNCTION_CLEAR_FEATURE_TO_INTERFACE:
	case URB_FUNCTION_CLEAR_FEATURE_TO_ENDPOINT:
	case URB_FUNCTION_CLEAR_FEATURE_TO_OTHER:
		URB_CONTROL_FEATURE_REQUEST UrbControlFeatureRequest;
		break;
	case URB_FUNCTION_VENDOR_DEVICE:
	case URB_FUNCTION_VENDOR_INTERFACE:
	case URB_FUNCTION_VENDOR_ENDPOINT:
	case URB_FUNCTION_VENDOR_OTHER:

	case URB_FUNCTION_CLASS_DEVICE:
	case URB_FUNCTION_CLASS_INTERFACE:
	case URB_FUNCTION_CLASS_ENDPOINT:
	case URB_FUNCTION_CLASS_OTHER:
		URB_CONTROL_VENDOR_OR_CLASS_REQUEST UrbControlVendorClassRequest;

		var Class = usb_getclass(device_source);

		switch (Class)
		{
		case USB_DEVICE_CLASS_VIDEO:
			VideoControlRequest video;
			break;
		case USB_DEVICE_CLASS_AUDIO:
			AudioRequest audio;
			break;
		}
		break;
	case URB_FUNCTION_GET_INTERFACE:
		URB_CONTROL_GET_INTERFACE_REQUEST UrbControlGetInterfaceRequest;
		break;
	case URB_FUNCTION_GET_FRAME_LENGTH:
		URB_GET_FRAME_LENGTH UrbGetFrameLength;
		break;
	case URB_FUNCTION_SET_FRAME_LENGTH:
		URB_SET_FRAME_LENGTH UrbSetFrameLength;
		break;
	case URB_FUNCTION_GET_CURRENT_FRAME_NUMBER:
		URB_GET_CURRENT_FRAME_NUMBER UrbGetCurrentFrameNumber;
		break;
	}
};

enum DEVICE_TEXT_TYPE : ULONG
{
	DeviceTextDescription = 0,            // DeviceDesc property
	DeviceTextLocationInformation = 1     // DeviceLocation property
};

struct USBPACKET_QUERYINTERFACE
{
	GUID InterfaceGuid;
	USHORT InterfaceSize;
	USHORT Version;
	ULONG status;
	ULONG_PTR Information;
};

struct USBPACKET_QUERY
{
	ULONG status;
	DEVICE_TEXT_TYPE QueryType;
	wchar_t Text[(packet_size - current_offset)/sizeof(wchar_t)];
};

[category(protocol)] public struct Usb
{
	$print("Direction", is_packet_up ? "Up" : "Down");

	switch (event_type)
	{
	case EVENT_URB:	// URB
		URB urb;
		break;
	case EVENT_DEVICECONNECTED:
		pstring_w device_connected;
		break;
	case EVENT_DEVICEDISCONNECTED:
		break;
	case EVENT_DEVICESURPRISEREMOVAL:
		break;
	case EVENT_DEVICEQUERYID:
		USBPACKET_QUERY device_query;
		break;
	case EVENT_DEVICEQUERYTEXT:
		USBPACKET_QUERY text_query;
		break;
	case EVENT_PIPEINFO:
		USBD_INTERFACE_INFORMATION pipe_info;
		break;
	case EVENT_QUERYINTERFACE:
		USBPACKET_QUERYINTERFACE query;
		break;
	}
};
