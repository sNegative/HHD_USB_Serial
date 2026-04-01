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

//#define SU_INPUT_SELECT_CONTROL 1

enum
{
	USB_DEVICE_CLASS_VIDEO = 0x0E
};

enum
{
	PC_PROTOCOL_UNDEFINED  = 0x00,
	PC_PROTOCOL_15 = 0x01
};

enum
{
	SC_UNDEFINED = 0x00,
	SC_VIDEOCONTROL = 0x01,
	SC_VIDEOSTREAMING = 0x02,
	SC_VIDEO_INTERFACE_COLLECTION = 0x03
};

//endpoint subtypes
enum
{
	EP_UNDEFINED = 0x00,
	EP_GENERAL,
	EP_ENDPOINT,
	EP_INTERRUPT
};

enum EAC_Requests : BYTE
{
	RC_UNDEFINED, 
	SET_CUR = 0x01,		// set cur
	SET_CUR_ALL = 0x11, //rev 1.5
	GET_CUR = 0x81,		// get cur	
	GET_MIN = 0x82,		// get min
	GET_MAX = 0x83,		// get max
	GET_RES = 0x84,		// get res
	GET_LEN = 0x85,		// get len
	GET_INFO = 0x86,	// get info
	GET_DEF = 0x87,		// get def

	//rev 1.5
	GET_CUR_ALL = 0x91,
	GET_MIN_ALL = 0x92,
	GET_MAX_ALL = 0x93,
	GET_RES_ALL = 0x94,
	GET_DEF_ALL = 0x97
};

// CT
enum ETerminalControlSelector
{
	CT_CONTROL_UNDEFINED,
	CT_SCANNING_MODE_CONTROL,
	CT_AE_MODE_CONTROL,
	CT_AE_PRIORITY_CONTROL,
	CT_EXPOSURE_TIME_ABSOLUTE_CONTROL,
	CT_EXPOSURE_TIME_RELATIVE_CONTROL,
	CT_FOCUS_ABSOLUTE_CONTROL,
	CT_FOCUS_RELATIVE_CONTROL,
	CT_FOCUS_AUTO_CONTROL,
	CT_IRIS_ABSOLUTE_CONTROL,
	CT_IRIS_RELATIVE_CONTROL,
	CT_ZOOM_ABSOLUTE_CONTROL,
	CT_ZOOM_RELATIVE_CONTROL,
	CT_PANTILT_ABSOLUTE_CONTROL,
	CT_PANTILT_RELATIVE_CONTROL,
	CT_ROLL_ABSOLUTE_CONTROL,
	CT_ROLL_RELATIVE_CONTROL,
	CT_PRIVACY_CONTROL,

	//rev 1.5
	CT_FOCUS_SIMPLE_CONTROL,
	CT_WINDOW_CONTROL,
	CT_REGION_OF_INTEREST_CONTROL
};

// PU
enum EProcessingUnitControlSelector
{
	PU_CONTROL_UNDEFINED,
	PU_BACKLIGHT_COMPENSATION_CONTROL,
	PU_BRIGHTNESS_CONTROL,
	PU_CONTRAST_CONTROL,
	PU_GAIN_CONTROL,
	PU_POWER_LINE_FREQUENCY_CONTROL,
	PU_HUE_CONTROL,
	PU_SATURATION_CONTROL,
	PU_SHARPNESS_CONTROL,
	PU_GAMMA_CONTROL,
	PU_WHITE_BALANCE_TEMPERATURE_CONTROL,
	PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL,
	PU_WHITE_BALANCE_COMPONENT_CONTROL,
	PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL,
	PU_DIGITAL_MULTIPLIER_CONTROL,
	PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL,
	PU_HUE_AUTO_CONTROL,
	PU_ANALOG_VIDEO_STANDARD_CONTROL,
	PU_ANALOG_LOCK_STATUS_CONTROL,

	//rev 1.5
	PU_CONTRAST_AUTO_CONTROL
};

// VS
enum EVideoStreamingInterfaceControlSelector
{
	VS_PROBE_CONTROL = 1,
	VS_COMMIT_CONTROL,
	VS_STILL_PROBE_CONTROL,
	VS_STILL_COMMIT_CONTROL,
	VS_STILL_IMAGE_TRIGGER_CONTROL,
	VS_STREAM_ERROR_CODE_CONTROL,
	VS_GENERATE_KEY_FRAME_CONTROL,
	VS_UPDATE_FRAME_SEGMENT_CONTROL,
	VS_SYNCH_DELAY_CONTROL
};

// SU
enum ESelectorUnitControlSelectors
{
	SU_CONTROL_UNDEFINED,
	SU_INPUT_SELECT_CONTROL
};

//rev 1.5
enum EEncodingUnitControlSelectors
{
	EU_CONTROL_UNDEFINED,
	EU_SELECT_LAYER_CONTROL,
	EU_PROFILE_TOOLSET_CONTROL,
	EU_VIDEO_RESOLUTION_CONTROL,
	EU_MIN_FRAME_INTERVAL_CONTROL,
	EU_SLICE_MODE_CONTROL,
	EU_RATE_CONTROL_MODE_CONTROL,
	EU_AVERAGE_BITRATE_CONTROL,
	EU_CPB_SIZE_CONTROL,
	EU_PEAK_BIT_RATE_CONTROL,
	EU_QUANTIZATION_PARAMS_CONTROL,
	EU_SYNC_REF_FRAME_CONTROL,
	EU_LTR_BUFFER_CONTROL,
	EU_LTR_PICTURE_CONTROL,
	EU_LTR_VALIDATION_CONTROL,
	EU_LEVEL_IDC_LIMIT_CONTROL,
	EU_SEI_PAYLOADTYPE_CONTROL,
	EU_QP_RANGE_CONTROL,
	EU_PRIORITY_CONTROL,
	EU_START_OR_STOP_LAYER_CONTROL,
	EU_ERROR_RESILIENCY_CONTROL
};

enum
{
	VC_HEADER = 1,
	VC_INPUT_TERMINAL,
	VC_OUTPUT_TERMINAL,
	VC_SELECTOR_UNIT,
	VC_PROCESSING_UNIT,
	VC_EXTENSION_UNIT,
	//rev 1.5
	VC_ENCODING_UNIT
};

enum
{
	VS_UNDEFINED = 0x00,
	VS_INPUT_HEADER,
	VS_OUTPUT_HEADER,
	VS_STILL_IMAGE_FRAME,
	VS_FORMAT_UNCOMPRESSED,
	VS_FRAME_UNCOMPRESSED,
	VS_FORMAT_MJPEG,
	VS_FRAME_MJPEG,
	VS_FORMAT_MPEG2TS = 0x0A,
	VS_FORMAT_DV = 0x0C,
	VS_COLORFORMAT = 0x0D,
	VS_FORMAT_FRAME_BASED = 0x10,
	VS_FRAME_FRAME_BASED,
	VS_FORMAT_STREAM_BASED,
	VS_FORMAT_H264,
	VS_FRAME_H264,
	VS_FORMAT_H264_SIMULCAST,
	VS_FORMAT_VP8,
	VS_FRAME_VP8,
	VS_FORMAT_VP8_SIMULCAST
};

enum EControlInterface
{
	VideoControlInterface = 0,
	VideoStreamingInterface = 1,

};

enum ERequestIndex
{
	ProbeControlID = 1,
	CameraTerminalID = 2,
	MediaTransportTerminalID = 3,
	SelectorUnitID = 4,
	ProcessingUnitID = 5,
	ExtensionUnitID,
	//rev 1.5
	EncodingUnitID
};


//Video Descriptors

struct VideoInterfaceHeaderDescriptor
{
	WORD bcdUVC;
	WORD wTotalLength;
	DWORD dwClockFrequency;
	BYTE bInCollection;
	BYTE baInterfaceNr[bInCollection];
};

struct VideoInputTerminalDescriptor
{
	BYTE bTerminalID;
	enum : WORD
	{
		ITT_VENDOR_SPECIFIC = 0x0200,
		ITT_CAMERA = 0x0201,
		ITT_MEDIA_TRANSPORT_INPUT = 0x0202
	}wTerminalType;

	BYTE bAssocTerminal;
	BYTE iTerminal;

	//TODO: Depending on the Terminal type, certain Input Terminal descriptors have additional fields. 
	switch (wTerminalType)
	{
	case ITT_CAMERA:
		WORD wObjectiveFocalLengthMin;
		WORD wObjectiveFocalLengthMax;
		WORD wOcularFocalLength;
		BYTE bControlSize;

		union CameraControl
		{
			struct
			{
				BYTE ScanningMode : 1;
				BYTE AutoExposureMode : 1;
				BYTE AutoExposurePriority : 1;
				BYTE ExposureTimeAbsolute : 1;
				BYTE ExposureTimeRelative : 1;
				BYTE FocusAbsolute : 1;
				BYTE FocusRelative : 1;
				BYTE IrisAbsolute : 1;
				BYTE IrisRelative : 1;
				BYTE ZoomAbsolute : 1;
				BYTE ZoomRelative : 1;
				BYTE PanTiltAbsolute : 1;
				BYTE PanTiltRelative : 1;
				BYTE RollAbsolute : 1;
				BYTE RollRelative : 1;
				BYTE Reserved1 : 1;
				BYTE Reserved2 : 1;
				BYTE Focus : 1;
				BYTE Auto : 1;
				BYTE Privacy : 1;
				BYTE FocusSimple : 1;
				BYTE Window : 1;
				BYTE RegionOfInterest : 1;
				BYTE Reserved3 : 1;
			}camera;
			[onread(format("{0b2w8arf0}{1b2w8arf0}{2b2w8arf0}", _1[0], _1[1], _1[2]))]
			BYTE bmControls[3];
		}control;

//		bmControls
		break;
	default:
		BYTE raw[bLength - (current_offset - start_offset)];
	}
};

struct VideoOutputTerminalDescriptor
{
	BYTE bTerminalID;
	enum : WORD
	{
		OTT_VENDOR_SPECIFIC = 0x0300,
		OTT_DISPLAY = 0x0301,
		OTT_MEDIA_TRANSPORT_OUTPUT = 0x0302
	}wTerminalType;

	BYTE bAssocTerminal;
	BYTE bSourceID;
	BYTE iTerminal;

	//TODO: Depending on the Terminal type, certain Output Terminal descriptors have additional fields. 
	switch (wTerminalType)
	{
	case OTT_DISPLAY:

		break;
	default:
		BYTE raw[bLength - (current_offset - start_offset)];
	}
};

struct VideoSelectorUnitDescriptor
{
	BYTE bUnitID;
	BYTE bNrInPins;
	BYTE baSourceID[bNrInPins];
	BYTE iSelector;
};

struct VideoProcessingUnitDescriptor
{
	BYTE bUnitID;
	BYTE bSourceID;
	WORD wMaxMultiplier;
	BYTE bControlSize;

	union ProcessingControl
	{
		struct
		{

			BYTE Brightness : 1;
			BYTE Contrast : 1;
			BYTE Hue : 1;
			BYTE Saturation : 1;
			BYTE Sharpness : 1;
			BYTE Gamma : 1;
			BYTE WhiteBalance : 1;
			BYTE Temperature : 1;
			BYTE WhiteBalanceComponent : 1;
			BYTE BacklightCompensation : 1;
			BYTE Gain : 1;
			BYTE PowerLineFrequency : 1;
			BYTE HueAuto : 1;
			BYTE WhiteBalanceTemperature : 1;
			BYTE Auto : 1;
			BYTE WhiteBalanceComponentAuto : 1;
			BYTE DigitalMultiplier : 1;
			BYTE DigitalMultiplierLimit : 1;
			BYTE AnalogVideoStandard : 1;
			BYTE AnalogVideoLockStatus : 1;
			BYTE ContrastAuto : 1;
			BYTE Reserved : 3;
		}camera;
		[onread(format("{0b2w8arf0}{1b2w8arf0}{2b2w8arf0}", _1[0], _1[1], _1[2]))]
		BYTE bmControls[3];
	}control;

	BYTE iProcessing;

	union VideoStandards
	{
		struct
		{
			BYTE None : 1;
			BYTE NTSC_525_60 : 1;
			BYTE PAL_625_50 : 1;
			BYTE SECAM_625_50 : 1;
			BYTE NTSC_625_50 : 1;
			BYTE PAL_525_60 : 1;
			BYTE Reserved : 2;
		}video_standards;
		[format("b2w8arf0")]
		BYTE bmVideoStandards;
	}control;
};

struct VideoExtensionUnitDescriptor
{
	BYTE bUnitID;
	GUID guidExtensionCode;
	BYTE bNumControls;
	BYTE bNrInPins;
	BYTE baSourceID[bNrInPins];
	BYTE bControlSize;
	BYTE bmControls[bControlSize]; //Vendor-specific
	BYTE iExtension; //Index of a string descriptor that describes this extension unit. 
};

struct VideoEncodingUnitDescriptor
{
	BYTE bUnitID;
	BYTE bSourceID;
	BYTE iEncoding;
	BYTE bControlSize;

	union EncodingControl
	{
		struct
		{
			BYTE SelectLayer : 1;
			BYTE ProfileAndToolset : 1;
			BYTE VideoResolution : 1;
			BYTE MinimumFrameInterval : 1;
			BYTE SliceMode : 1;
			BYTE RateControlMode : 1;
			BYTE AverageBitRate : 1;
			BYTE CPBSize : 1;
			BYTE PeakBitRate : 1;
			BYTE QuantizationParameter : 1;
			BYTE Synchronization: 1;
			BYTE LongTermBuffer : 1;
			BYTE Picture : 1;
			BYTE Validation : 1;
			BYTE LevelIDC : 1;
			BYTE SEIMessage : 1;
			BYTE QPRange : 1;
			BYTE PriorityID : 1;
			BYTE StartStopLayerOrView : 1;
			BYTE ErrorResiliency : 1;
			BYTE Reserved : 4;
		}encodings;
		[onread(format("{0b2w8arf0}{1b2w8arf0}{2b2w8arf0}", _1[0], _1[1], _1[2]))]
		BYTE bmControls[3];
	}control;




	//BYTE bmControls;
	//BYTE bmControlsRuntime;
	union EncodingRuntimeControl
	{
		struct
		{
			BYTE None : 1;
		}encodings;
		[format("b2w8arf0")]
		BYTE bmControlsRuntime;
	}runtime_control;

};

struct VideoControlDescriptor
{
	switch (bDescriptorSubtype)
	{
	case VC_HEADER:
		VideoInterfaceHeaderDescriptor header;
		break;
	case VC_INPUT_TERMINAL:
		VideoInputTerminalDescriptor input_terminal;
		break;
	case VC_OUTPUT_TERMINAL:
		VideoOutputTerminalDescriptor output_terminal;
		break;
	case VC_SELECTOR_UNIT:
		VideoSelectorUnitDescriptor selector;
		break;
	case VC_PROCESSING_UNIT:
		VideoProcessingUnitDescriptor processing;
		break;
	case VC_EXTENSION_UNIT:
		VideoExtensionUnitDescriptor extension;
		break;
	case VC_ENCODING_UNIT:
		VideoEncodingUnitDescriptor encoding;
		break;
	}
};

struct VideoControlEndpointDescriptor
{
	//BYTE bDescriptorSubType; //EP_INTERRUPT
	WORD wMaxTransferSize;
};


//Audio Streaming
struct VideoStreamingInputHeaderDescriptor
{
	BYTE bNumFormats;
	WORD wTotalLength;
	BYTE bEndpointAddress;
	BYTE bmInfo;
	BYTE bTerminalLink;
	BYTE bStillCaptureMethod;
	BYTE bTriggerSupport;
	BYTE bTriggerUsage;
	BYTE bControlSize;
	BYTE bmaControls[bControlSize];
};

struct VideoStreamingOutputHeaderDescriptor
{
	BYTE bNumFormats;
	WORD wTotalLength;
	BYTE bEndpointAddress;
	BYTE bTerminalLink;
	BYTE bControlSize;
	BYTE bmaControls[bControlSize];
};

struct VideoStreamingStillImageDescriptor
{
	BYTE bEndpointAddress;
	BYTE bNumImageSizePatterns;
	struct ImageSize
	{
		WORD wWidth;
		WORD wHeight;
	}image_sizes[bNumImageSizePatterns];
	BYTE bNumCompressionPattern;
	BYTE bCompression[bNumCompressionPattern];
};

struct VideoStreamingColorMatchingDescriptor
{
	enum : BYTE
	{
		Unspecified = 0, //Image characteristics unknown 
		BT709_sRGB,
		BT470_2M,
		BT470_2BG,
		SMPTE170M,
		SMPTE240M
	}bColorPrimaries;

	enum :BYTE
	{
		Unspecified = 0, //Image characteristics unknown 
		BT709_sRGB,
		BT470_2M,
		BT470_2BG,
		SMPTE170M,
		SMPTE240M,
		Linear,
		sRGB
	}bTransferCharacteristics;

	enum :BYTE
	{
		Unspecified = 0,
		BT709,
		FCC,
		BT470,
		SMPTE_170M,
		SMPTE_240M
	}bMatrixCoefficients;
};

struct VideoStreamingDescriptor
{
	switch (bDescriptorSubtype)
	{
	case VS_UNDEFINED:
		break;
	case VS_INPUT_HEADER:
		VideoStreamingInputHeaderDescriptor input_header;
		break;
	case VS_OUTPUT_HEADER:
		VideoStreamingOutputHeaderDescriptor output_header;
		break;
	case VS_STILL_IMAGE_FRAME:
		VideoStreamingStillImageDescriptor still_image_frame;
		break;
	case VS_FORMAT_UNCOMPRESSED:
		struct FormatUncompressed
		{
			BYTE bFormatIndex;
			BYTE bNumFrameDescriptors;
			GUID guidFormat;
			BYTE bBitsPerPixel;
			BYTE bDefaultFrameIndex;
			BYTE bAspectRatioX;
			BYTE bAspectRatioY;
			BYTE bmInterlaceFlags;
			enum :BYTE { NoRestrictions, RestrictDuplication } bCopyProtect;
		}uncompressed;
		break;
	case VS_FRAME_UNCOMPRESSED:
		struct FrameUncompressed
		{
			BYTE bFrameIndex;
			union FrameCapabilities
			{
				struct
				{
					BYTE StillImageSupported : 1;
					BYTE FixedFrameRate : 1;
					BYTE Reserved : 6;
				}control;
				[format("b2w8arf0")]
				BYTE bmCapabilities;
			}capabilities;

			WORD wWidth;
			WORD wHeight;
			DWORD dwMinBitRate;
			DWORD dwMaxBitRate;
			DWORD dwMaxVideoFrameBufferSize;
			DWORD dwDefaultFrameInterval;
			BYTE bFrameIntervalType;
			DWORD dwMinFrameInterval;
			DWORD dwMaxFrameInterval;
			DWORD dwFrameIntervalStep;
			DWORD dwFrameInterval[bFrameIntervalType];
		}uncompressed_frame;
		break;
	case VS_FORMAT_MJPEG:
		struct FormatMjpeg
		{
			BYTE bFormatIndex;
			BYTE bNumFrameDescriptors;
			BYTE bmFlags;
			BYTE bDefaultFrameIndex;
			BYTE bAspectRatioX;
			BYTE bAspectRatioY;
			BYTE bmInterlaceFlags;
			enum :BYTE { NoRestrictions, RestrictDuplication } bCopyProtect;
		}mjpeg;
		break;
	case VS_FRAME_MJPEG:
		struct FrameMjpeg
		{
			BYTE bFrameIndex;
			BYTE bmCapabilities;
			WORD wWidth;
			WORD wHeight;
			DWORD dwMinBitRate;
			DWORD dwMaxBitRate;
			DWORD dwMaxVideoFrameBufferSize;
			DWORD dwDefaultFrameInterval;
			BYTE bFrameIntervalType;
			DWORD dwMinFrameInterval;
			DWORD dwMaxFrameInterval;
			DWORD dwFrameIntervalStep;
			DWORD dwFrameInterval[bFrameIntervalType];
		}frame_mjpeg;
		break;
	case VS_FORMAT_MPEG2TS:
		struct FormatMpeg2TS
		{
			BYTE bFormatIndex;
			BYTE bDataOffset;
			BYTE bPacketLength;
			BYTE bStrideLength;
			GUID guidStrideFormat;
		}format_mpeg2ts;
		break;
	case VS_FORMAT_DV:
		struct FormatDV
		{
			BYTE bFormatIndex;
			DWORD dwMaxVideoFrameBufferSize;
			enum :BYTE
			{
				SDDV,
				SDLDV,
				HDDV,
				_50Hz = 0x80,
				//_60Hz,
			}bFormatType;
		}format_dv;
		break;
	case VS_COLORFORMAT:
		VideoStreamingColorMatchingDescriptor color_format;
		break;
	case VS_FORMAT_FRAME_BASED:
		struct FormatFrameBased
		{
			BYTE bFormatIndex;
			BYTE bNumFrameDescriptors;
			GUID guidFormat;
			BYTE bBitsPerPixel;
			BYTE bDefaultFrameIndex;
			BYTE bAspectRatioX;
			BYTE bAspectRatioY;
			BYTE bmInterlaceFlags;
			enum :BYTE { FALSE, TRUE } bCopyProtect;
			enum :BYTE { FALSE, TRUE } bVariableSize;
		}frame_based;
		break;
	case VS_FRAME_FRAME_BASED:
		struct FrameFrameBased
		{
			BYTE bFrameIndex;
			BYTE bmCapabilities;
			WORD wWidth;
			WORD wHeight;
			DWORD dwMinBitRate;
			DWORD dwMaxBitRate;
			DWORD dwDefaultFrameInterval;
			BYTE bFrameIntervalType;
			DWORD dwBytesPerLine;
			DWORD dwMinFrameInterval; //100ns units
			DWORD dwMaxFrameInterval;
			DWORD dwFrameIntervalStep;
			DWORD dwFrameInterval[bFrameIntervalType];
		}frame_frame;
		break;
	case VS_FORMAT_STREAM_BASED:
		struct FormatStreamBased
		{
			BYTE bFormatIndex;
			GUID guidFormat;
			DWORD dwPacketLength;
		}stream_based;
		break;
	case VS_FORMAT_H264:
	case VS_FORMAT_H264_SIMULCAST:
		struct FormatH264
		{
			BYTE bFormatIndex;
			BYTE bNumFrameDescriptors;
			BYTE bDefaultFrameIndex;
			BYTE bMaxCodecConfigDelay;

			BYTE bmSupportedSliceModes;
			BYTE bmSupportedSyncFrameTypes;
			BYTE bResolutionScaling;
			BYTE Reserved1;
			BYTE bmSupportedRateControlModes;
			WORD wMaxMBperSecOneResolutionNoScalability;
			WORD wMaxMBperSecTwoResolutionsNoScalability;
			WORD wMaxMBperSecThreeResolutionsNoScalability;
			WORD wMaxMBperSecFourResolutionsNoScalability;
			WORD wMaxMBperSecOneResolutionTemporalScalability;
			WORD wMaxMBperSecTwoResolutionsTemporalScalablility;
			WORD wMaxMBperSecThreeResolutionsTemporalScalability;
			WORD wMaxMBperSecFourResolutionsTemporalScalability;
			WORD wMaxMBperSecOneResolutionTemporalQualityScalability;
			WORD wMaxMBperSecTwoResolutionsTemporalQualityScalability;
			WORD wMaxMBperSecThreeResolutionsTemporalQualityScalablity;
			WORD wMaxMBperSecFourResolutionsTemporalQualityScalability;
			WORD wMaxMBperSecOneResolutionsTemporalSpatialScalability;
			WORD wMaxMBperSecTwoResolutionsTemporalSpatialScalability;
			WORD wMaxMBperSecThreeResolutionsTemporalSpatialScalability;
			WORD wMaxMBperSecFourResolutionsTemporalSpatialScalability;
			WORD wMaxMBperSecOneResolutionFullScalability;
			WORD wMaxMBperSecTwoResolutionsFullScalability;
			WORD wMaxMBperSecThreeResolutionsFullScalability;
			WORD wMaxMBperSecFourResolutionsFullScalability;
		};
		break;

	case VS_FRAME_H264:
		struct PayloadVideoFrame
		{
			BYTE bFrameIndex;
			WORD wWidth;
			WORD wHeight;
			WORD wSARwidth;
			WORD wSARheight;

			enum :WORD
			{
				ConstrainedBaselineProfile = 0x4240,
				BaselineProfile = 0x4200,
				MainProfile = 0x4D00,
				ConstrainedHighProfile = 0x640C,
				HighProfile = 0x6400,
				ScalableConstrainedBaselineProfile = 0x5304,
				ScalableBaselineProfile = 0x5300,
				ScalableConstrainedHighProfile = 0x5604,
				ScalableHighProfile = 0x5600,
				MultiviewHighProfile = 0x7600,
				StereoHighProfile = 0x8000
			}wProfile; 

			BYTE bLevelIDC;
			WORD wConstrainedToolset;
			DWORD bmSupportedUsages;
			WORD  bmCapabilities;

			union SVCCapabilities
			{
				struct
				{
					DWORD MaxNumberOfTemporalLayers : 3;
					DWORD RewriteSupport : 1;
					DWORD MaxNumberOfCGSLayers:3;
					DWORD MaxNumberOfMGSSublayers : 3;
					DWORD AdditionalSNRscalability : 1;
					DWORD MaxNumberOfSpatialLayers : 3;
					DWORD Reserved : 17;
				}capabilities;
				[format("b2w32arf0")]
				DWORD bmSVCCapabilities;
			}svc_capabilities;
			
			union MVCCapabilities
			{
				struct
				{
					DWORD MaxNumberOfTemporalLayers : 3;
					DWORD MaxNumberOfViewComponents : 8;
					DWORD Reserved : 21;
				}capabilities;
				[format("b2w32arf0")]
				DWORD bmMVCCapabilities;
			}mvc_capabilities;

			DWORD dwMinBitRate;
			DWORD dwMaxBitRate;
			DWORD dwDefaultFrameInterval;
			BYTE bNumFrameIntervals;
			DWORD dwFrameInterval[bNumFrameIntervals];
		}payload_frame;
		break;
	case VS_FORMAT_VP8:
	case VS_FORMAT_VP8_SIMULCAST:
		struct VP8Format
		{
			BYTE bFormatIndex;
			BYTE bNumFrameDescriptors;
			BYTE bDefaultFrameIndex;
			BYTE bMaxCodecConfigDelay;
			BYTE bSupportedPartitionCount;

			union SupportedSyncFrameTypes
			{
				struct
				{
					BYTE Reset : 1;
					BYTE IntraFrame : 1;
					BYTE GoldenFrame : 1;
					BYTE AlternateReferenceFrame : 1;
					BYTE GradualDecoderRefreshFrames : 1;
					BYTE Reserved : 3;
				}control;
				[format("b2w8arf0")]
				BYTE bmSupportedSyncFrameTypes;
			}supported_sync_frame_types;

			BYTE bResolutionScaling;

			union SupportedRateControlModes
			{
				struct RateControlMode
				{
					BYTE VBR : 1;
					BYTE CBR : 1;
					BYTE ConstantQP : 1;
					BYTE GVBR : 1;
					BYTE Reserved : 4;
				}RateControlModes;
				[format("b2w8arf0")]
				BYTE bmSupportedRateControlModes;
			}rate_control_modes;

			WORD wMaxMBperSec;
		}vp8_format;
		break;
	case VS_FRAME_VP8:
		struct VP8Frame
		{
			BYTE bFrameIndex;
			WORD wWidth;
			WORD wHeight;
			BYTE bmSupportedUsages;

			union Capabilities
			{
				struct
				{
					WORD Reserved : 1;
					WORD Reserved1 : 1;
					WORD ConstantFrameRate:1;
					WORD ConstantQP : 1;
					WORD Reserved2 : 1;
					WORD Reserved3 : 1;
					WORD GoldenFrame : 1;
					WORD AlternateReferenceFrame : 1;
					WORD Reserved4 : 8;
				}control;
				[format("b2w8arf0")]
				BYTE bmCapabilities;
			}capabilities;

			DWORD bmScalabilityCapabilities;
			DWORD dwMinBitRate;
			DWORD dwMaxBitRate;
			DWORD dwDefaultFrameInterval;
			BYTE bNumFrameIntervals;
			DWORD dwFrameInterval[bNumFrameIntervals];
		}vp8_frame;
		break;
	}
};

//Video Streaming Endpoint Descriptors
struct BulkVideoDataEndpointDescriptor
{
	BYTE bEndpointAddress;
	BYTE bmAttributes;
	WORD wMaxPacketSize;
	BYTE bInterval;
};

//Interface Collection
struct VideoInterfaceCollection
{
	BYTE bFirstInterface;
	BYTE bInterfaceCount;
	BYTE bFunctionClass;
	BYTE bFunctionSubClass;
	BYTE bFunctionProtocol;
	BYTE iFunction;
};


struct ProbeControl
{
	WORD bmHint;
	BYTE bFormatIndex;
	BYTE bFrameIndex;
	DWORD dwFrameInterval;
	WORD wKeyFrameRate;
	WORD wPFrameRate;
	WORD wCompQuality;
	WORD wCompWindowSize;
	WORD wDelay;
	DWORD dwMaxVideoFrameSize;
	DWORD dwMaxPayloadTransferSize;

	//DWORD dwClockFrequency;
	//BYTE bmFramingInfo;
	//BYTE bPreferedVersion;
	//BYTE bMinVersion;
	//BYTE bMaxVersion;
};


struct VideoControlRequest
{
	RequestType request_type;
	EAC_Requests bRequest;
	WORD wValue;
	BYTE bInterface;
	BYTE bTerminalType;
	WORD wLength;

	var UnitID = usb_get_unit_id(device_source, bTerminalType);
	var PayloadSize = packet_size - current_offset;

	if (current_offset < packet_size)
	{
		switch(bInterface)
		{
		case 0://VideoControl:
			switch(UnitID)
			{
			case 0:
				//VC_VIDEO section
				switch (wValue >> 8)
				{
				case 1:
					struct VideoDevicePowerMode
					{
						union
						{
							BYTE PowerMode : 4;
							BYTE DeviceDependentMode : 1;
							BYTE SuppliedByUsb : 1;
							BYTE SuppliedByBattery : 1;
							BYTE SuppliedByAc : 1;
						};
						[format("b2w8arf0")]
						BYTE bDevicePowerMode;
					}device_power_mode;
					break;
				case 2:
					struct VideoRequestErrorCodeControl
					{
						enum RequestErrorCode : BYTE
						{
							NoError = 0x0,
							NotReady = 0x02,
							WrongState = 0x03,
							Power = 0x04,
							OutOfRange = 0x05,
							InvalidUnit = 0x06,
							InvalidControl = 0x07,
							InvalidRequest = 0x08,
							//0x8 - 0xFE :  reserved
							Unknown = 0xFF
						}bRequestErrorCode;
					}request_error_code_control;
					break;
				}

			case ProbeControlID:
				break;

				//CT_ section
			case CameraTerminalID:

				switch (wValue >> 8)
				{
				case CT_CONTROL_UNDEFINED:
					break;
				case CT_SCANNING_MODE_CONTROL:
					struct VideoScanningModeControl
					{
						enum bScanningMode :BYTE
						{
							Interlaced,
							Progressive
						}bScanningMode;
					}scanning_mode_control;
					break;
				case CT_AE_MODE_CONTROL:
					struct VideoAutoExposureModeControl
					{
						union
						{
							BYTE ManualMode : 1;
							BYTE AutoMode : 1;
							BYTE ShutterPriorityMode : 1;
							BYTE AperturePriorityMode : 1;
							BYTE Reserved : 4;
						}AutoExposureMode;
						[format("b2w8arf0")]
						BYTE bAutoExposureMode;
					}auto_exposure_mode_control;
					break;
				case CT_AE_PRIORITY_CONTROL:
					struct VideoAutoExposurePriorityControl
					{
						BYTE bAutoExposurePriority;
					}auto_exposure_priority_control;
					break;
				case CT_EXPOSURE_TIME_ABSOLUTE_CONTROL:
					struct VideoExposureTimeAbsoluteControl
					{
						DWORD dwExposureTimeAbsolute; // 1/10000 sec
					}exposure_time_absolute_control;
					break;
				case CT_EXPOSURE_TIME_RELATIVE_CONTROL:
					struct VideoExposureTimeRelativeControl
					{
						enum ExposureTimeRelative : BYTE
						{
							Default,
							Incremented,
							Decremented
						}bExposureTimeRelative;
					}exposure_time_relative_control;
					break;
				case CT_FOCUS_ABSOLUTE_CONTROL:
					struct VideoFocusAbsoluteControl
					{
						WORD wFocusAbsolute;
					}focus_absolute_control;
					break;
				case CT_FOCUS_RELATIVE_CONTROL:
					struct VideoFocusRelativeControl
					{
						enum FocusRelative : BYTE
						{
							Stop,
							FocusNearDirection,
							FoucusInfinite = 0xFF
						}bFocusRelative;
						BYTE bSpeed;
					}focus_relative_control;
					break;
				case CT_FOCUS_AUTO_CONTROL:
					struct VideoFocusAutoControl
					{
						BYTE bFocusAuto;
					}focus_auto_control;
					break;
				case CT_IRIS_ABSOLUTE_CONTROL:
					struct VideoIrisAbsoluteControl
					{
						WORD wIrisAbsolute;
					}iris_absolute_control;
					break;
				case CT_IRIS_RELATIVE_CONTROL:
					struct VideoIrisRelativeControl
					{
						enum IrisRelative :BYTE
						{
							Default,
							IrisIsOpened,
							IrisIsClosed = 0xFF
						}bIrisRelative;
					}iris_relative_control;
					break;
				case CT_ZOOM_ABSOLUTE_CONTROL:
					struct VideoZoomAbsoluteControl
					{
						WORD wObjectiveFocalLength;
					}zoom_absolute_control;
					break;
				case CT_ZOOM_RELATIVE_CONTROL:
					struct VideoZoomRelativeControl
					{
						enum Zoom : BYTE
						{
							Stop,
							TelephotoDirection,
							WideAngleDirection = 0xFF
						}bZoom;

						enum DigitalZoom : BYTE
						{
							OFF,
							ON
						}bDigitalZoom;

						BYTE bSpeed;
					}zoom_relative_control;
					break;
				case CT_PANTILT_ABSOLUTE_CONTROL:
					struct VideoPanTiltAbsoluteControl
					{
						DWORD dwPanAbsolute;
						DWORD dwTiltAbsolute;
					}pantilt_absolute_control;
					break;
				case CT_PANTILT_RELATIVE_CONTROL:
					struct VideoPanTiltRelativeControl
					{
						enum PanRelative : BYTE
						{
							Stop,
							Clocwise,
							CounterClocwise = 0xFF
						}bPanRelative;
						BYTE bPanSpeed;
						enum TiltRelative : BYTE
						{
							Stop,
							PointPlaneUp,
							PointPlaneDown = 0xFF
						}bTiltRelative;
						BYTE bTiltSpeed;
					}pantilt_relative_control;
					break;
				case CT_ROLL_ABSOLUTE_CONTROL:
					struct VideowRollAbsoluteControl
					{
						WORD wRollAbsolute;
					}roll_absolute_control;
					break;
				case CT_ROLL_RELATIVE_CONTROL:
					struct VideoRollRelativeControl
					{
						BYTE bRollRelative;
						BYTE bSpeed;
					}roll_relative_control;
					break;
				case CT_PRIVACY_CONTROL:
					struct VideoPrivacyControl
					{
						BYTE bPrivacy;
					}privacy_control;
					break;

				case CT_FOCUS_SIMPLE_CONTROL:
					struct VideoFocusSimpleControl
					{
						enum Focus : BYTE
						{
							FullRange,
							Macro,
							People,
							Scene
						}bFocus;
					}focus_simple_control;
					break;
				case CT_WINDOW_CONTROL:
					struct VideoWindwoControl
					{
						WORD wWindow_Top;
						WORD wWindow_Left;
						WORD wWindow_Bottom;
						WORD wWindow_Right;
						WORD wNumSteps;
						WORD bmNumStepsUnits;
					}window_control;
					break;
				case CT_REGION_OF_INTEREST_CONTROL:
					struct VideoRegionOfInterestControl
					{
						WORD wROI_Top;
						WORD wROI_Left;
						WORD wROI_Bottom;
						WORD wROI_Right;

						union
						{
							struct
							{
								WORD AutoExposure : 1;
								WORD AutoIris : 1;
								WORD AutoWhiteBalance : 1;
								WORD AutoFocus : 1;
								WORD AutoFaceDetect : 1;
								WORD AutoDetectAndTrack : 1;
								WORD ImageStabilization : 1;
								WORD HigherQuality : 1;
								WORD Reserved : 7;
							}bmAutoControlsD;
							[format("b2w16arf0")]
							WORD bmAutoControls;
						}AutoControls;
					}region_of_interest_control;
					break;
				}
				break;

			case MediaTransportTerminalID:

				break;

				//SU_ section
			case SelectorUnitID:
				switch (wValue >> 8)
				{
				case SU_CONTROL_UNDEFINED:
					break;
				case SU_INPUT_SELECT_CONTROL:
					struct VideoInputSelectControl
					{
						BYTE bSelector;
					}input_select_control;
					break;
				}

				break;

			case ProcessingUnitID:

				switch (wValue >> 8)
				{
				case PU_CONTROL_UNDEFINED:
					break;
				case PU_BACKLIGHT_COMPENSATION_CONTROL:
					struct VideoBacklightCompensationControl
					{
						WORD wBacklightCompensation;
					}backlight_compensation_control;
					break;
				case PU_BRIGHTNESS_CONTROL:
					struct VideoBrightnessControl
					{
						WORD wBrightness;
					}brightness_control;
					break;
				case PU_CONTRAST_CONTROL:
					struct VideoContrastControl
					{
						WORD wContrast;
					}contrast_control;
					break;
				case PU_GAIN_CONTROL:
					struct VideoGainControl
					{
						WORD wGain;
					}gain_control;
					break;
				case PU_POWER_LINE_FREQUENCY_CONTROL:
					struct VideoPowerLineFrequencyControl
					{
						enum EPowerLineFrequency : BYTE
						{
							Disabled,
							Hz50,
							Hz60
						}bPowerLineFrequency;
					}power_line_frequency_control;
					break;
				case PU_HUE_CONTROL:
					struct VideoHueControl
					{
						WORD wHue;
					}hue_control;
					break;
				case PU_SATURATION_CONTROL:
					struct VideoSaturationControl
					{
						WORD wSaturation;
					}saturation_control;
					break;
				case PU_SHARPNESS_CONTROL:
					struct VideoSharpnessControl
					{
						WORD wSharpness;
					}sharpness_control;
					break;
				case PU_GAMMA_CONTROL:
					struct VideoGammaControl
					{
						WORD wGamma;
					}gamma_control;
					break;
				case PU_WHITE_BALANCE_TEMPERATURE_CONTROL:
					struct VideoWhiteBalanceTemperature
					{
						BYTE bWhiteBalanceTemperature;
					}white_balance_temperature;
					break;
				case PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL:
					struct VideoWhiteBalanceTemperatureAuto
					{
						BYTE bWhiteBalanceTemperatureAuto;
					}white_balance_temperature_auto;
					break;
				case PU_WHITE_BALANCE_COMPONENT_CONTROL:
					struct VideoWhiteBalanceComponent
					{
						WORD wWhiteBalanceBlue;
						WORD wWhiteBalanceRed;
					}white_balance_component;
					break;
				case PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL:
					struct VideoWhiteBalanceComponentAuto
					{
						BYTE bWhiteBalanceComponentAuto;
					}white_balance_component_auto;
					break;
				case PU_DIGITAL_MULTIPLIER_CONTROL:
					struct VideoDigitalMultiplierControl
					{
						WORD wMultiplierStep; //TODO: digital zoom
					}digital_multiplier_control;
					break;
				case PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL:
					struct VideoDigitalMultiplierLimitControl
					{
						WORD wMultiplierLimit; //TODO: digital zoom
					}digital_multiplier_limit_control;
					break;
				case PU_HUE_AUTO_CONTROL:
					struct VideoHueAutoControl
					{
						BYTE bHueAuto;
					}hue_auto_control;
					break;
				case PU_ANALOG_VIDEO_STANDARD_CONTROL:
					struct VideoStandardControl
					{
						enum EStatus : BYTE
						{
							None,
							NTSC_525_60,
							PAL_625_50,
							SECAM_625_50,
							NTSC_625_50,
							PAL_525_60
						}bVideoStandard;
					}standard_control;
					break;
				case PU_ANALOG_LOCK_STATUS_CONTROL:
					struct VideoLockStatusControl
					{
						enum EStatus : BYTE
						{
							VideoDecoderIsLocked,
							VideoDecoderIsNotLocked,
						}bStatus;
					}lock_status_control;
					break;
				case PU_CONTRAST_AUTO_CONTROL:
					struct VideoContrastAutoControl
					{
						BYTE bContrastAuto;
					}contrast_auto_control;
					break;
				}
				break;

			case EncodingUnitID:
				switch (wValue >> 8)
				{
				case EU_SELECT_LAYER_CONTROL:
					struct VideoSelectLayerControl
					{
						WORD wLayerOrViewID;
					}select_layer_control;
					break;
				case EU_PROFILE_TOOLSET_CONTROL:
					struct VideoProfileToolsetControl
					{
						WORD wProfile;
						WORD wConstrainedToolset;
						BYTE bmSettings;
					}profile_toolset_control;
					break;
				case EU_VIDEO_RESOLUTION_CONTROL:
					struct VideoResolutionControl
					{
						WORD wWidth;
						WORD wHeight;
					}resolution_control;
					break;
				case EU_MIN_FRAME_INTERVAL_CONTROL:
					struct VideoMinimumFrameIntervalControl
					{
						DWORD dwFrameInterval;
					}min_frame_interval_control;
					break;
				case EU_SLICE_MODE_CONTROL:
					struct VideoSliceModeControl
					{
						enum SliceMode : WORD
						{
							MaximumNumberOfMBsPerSlice,
							TargetCompressedSizePerSlice,
							NumberOfSlicesPerFrameMode,
							NumberOfMacroblockRowsPerSlice
						}wSliceMode;

						WORD wSliceConfigSetting;
					}slice_mode_control;
					break;
				case EU_RATE_CONTROL_MODE_CONTROL:
					struct VideoControlModeControl
					{
						enum RateControlMode : BYTE
						{
							Reserved,
							VBR,
							CBR,
							ConstantQP,
							GVBR,
							VBRN,
							GVBRN
						}bRateControlMode;
					}rate_control_mode_control;
					break;
				case EU_AVERAGE_BITRATE_CONTROL:
					struct VideoAverageBitrateControl
					{
						DWORD dwAverageBitRate;
					}average_bitrate_control;
					break;
				case EU_CPB_SIZE_CONTROL:
					struct VideoCPBSizeControl
					{
						DWORD dwCPBsize;
					}cpb_size_control;
					break;
				case EU_PEAK_BIT_RATE_CONTROL:
					struct VideoPeakBitRateControl
					{
						DWORD dwPeakBitRate;
					}peak_bit_rate_control;
					break;
				case EU_QUANTIZATION_PARAMS_CONTROL:
					struct VideoQuantizationParameterControl
					{
						WORD wQpPrime_I;
						WORD wQpPrime_P;
						WORD wQpPrime_B;
					}quantization_params_control;
					break;
				case EU_SYNC_REF_FRAME_CONTROL:
					struct VideoSyncRefFrameControl
					{
						BYTE bSyncFrameType;
						WORD wSyncFrameInterval;
						BYTE bGradualDecoderRefresh;
					}sync_ref_frame_control;
					break;
				case EU_LTR_BUFFER_CONTROL:
					struct VideoLTRBufferControl
					{
						BYTE bNumHostControlLTRBuffers;
						BYTE bTrustMode;
					}ltr_buffer_control;
					break;
				case EU_LTR_PICTURE_CONTROL:
					struct VideoLTRPictureControl
					{
						BYTE bPutAtPositionInLTRBuffer;
						BYTE bLTRMode;
					}ltr_picture_control;
					break;
				case EU_LTR_VALIDATION_CONTROL:
					struct VideoLTRValidationControl
					{
						WORD bmValidLTRs;
					}ltr_validation_control;
					break;
				case EU_LEVEL_IDC_LIMIT_CONTROL:
					struct VideoLevelIDCLimitControl
					{
						BYTE bLevelIDC;
					}level_idc_limit_control;
					break;
				case EU_SEI_PAYLOADTYPE_CONTROL:
					union VideoSeiPayloadControl
					{
						struct
						{
							QWORD buffering_period : 1;
							QWORD pic_timing : 1;
							QWORD pan_scan_rect : 1;
							QWORD filler_payload : 1;
							QWORD user_data_registered_itu_t_t35 : 1;
							QWORD user_data_unregistered : 1;
							QWORD recovery_point : 1;
							QWORD dec_ref_pic_marking_repetition : 1;
							QWORD spare_pic : 1;
							QWORD scene_info : 1;
							QWORD sub_seq_info : 1;
							QWORD sub_seq_layer_characteristics : 1;
							QWORD sub_seq_characteristics : 1;
							QWORD full_frame_freeze : 1;
							QWORD full_frame_freeze_release : 1;
							QWORD full_frame_snapshot : 1;
							QWORD progressive_refinement_segment_start : 1;
							QWORD progressive_refinement_segment_end : 1;
							QWORD motion_constrained_slice_group_set : 1;
							QWORD film_grain_characteristics : 1;
							QWORD deblocking_filter_display_preference : 1;
							QWORD stereo_video_info : 1;
							QWORD post_filter_hint : 1;
							QWORD tone_mapping_info : 1;
							QWORD scalability_info : 1;
							QWORD sub_pic_scalable_layer : 1;
							QWORD non_required_layer_rep : 1;
							QWORD priority_layer_info : 1;
							QWORD layers_not_present : 1;
							QWORD layer_dependency_change : 1;
							QWORD scalable_nesting : 1;
							QWORD base_layer_temporal_hrd : 1;
							QWORD quality_layer_integrity_check : 1;
							QWORD redundant_pic_property : 1;
							QWORD tl0_dep_rep_index : 1;
							QWORD tl_switching_point : 1;
							QWORD parallel_decoding_info : 1;
							QWORD mvc_scalable_nesting : 1;
							QWORD view_scalability_info : 1;
							QWORD multiview_scene_info : 1;
							QWORD multiview_acquisition_info : 1;
							QWORD non_required_view_component : 1;
							QWORD view_dependency_change : 1;
							QWORD operation_points_not_present : 1;
							QWORD base_view_temporal_hrd : 1;
							QWORD frame_packing_arrangement : 1;
							QWORD Reserved : 17;
						} bmSEIMessagesD;
						[format("b2w64arf0")]
						QWORD bmSEIMessages;
					}sei_payloadtype_control;
					break;
				case EU_QP_RANGE_CONTROL:
					struct VideoQPRangeControl
					{
						BYTE bMinQp;
						BYTE bMaxQp;
					}qp_range_control;
					break;
				case EU_PRIORITY_CONTROL:
					struct VideoPriorityControl
					{
						BYTE bPriority;
					}priority_control;
					break;
				case EU_START_OR_STOP_LAYER_CONTROL:
					struct VideoStartStopLayerControl
					{
						enum Update : BYTE
						{
							StopStreaming,
							StartStreaming
						}bUpdate;
					}start_or_stop_layer_control;
					break;
				case EU_ERROR_RESILIENCY_CONTROL:
					struct VideoErrorResiliencyControl
					{
						WORD bmErrorResiliencyFeatures;
					}error_resiliency_control;
					break;
				}
				break;

			}
			break;
		case 1://VideoStreaming:
			//VS_ section
			switch (wValue >> 8)
			{
			case VS_PROBE_CONTROL:
				ProbeControl probe_control;
				break;
			case VS_COMMIT_CONTROL:
				ProbeControl commit_control;
				break;
			case VS_STILL_PROBE_CONTROL:
				struct VideoStillProbeControl
				{
					BYTE bFormatIndex;
					BYTE bFrameIndex;
					BYTE bCompressionIndex;
					DWORD dwMaxVideoFrameSize;
					DWORD dwMaxPayloadTransferSize;
				}still_probe_control;
				break;
			case VS_STILL_COMMIT_CONTROL:
				struct VideoStillCommitControl //same as VideoStillProbeControl
				{
					BYTE bFormatIndex;
					BYTE bFrameIndex;
					BYTE bCompressionIndex;
					DWORD dwMaxVideoFrameSize;
					DWORD dwMaxPayloadTransferSize;
				}still_commit_control;
				break;
			case VS_STILL_IMAGE_TRIGGER_CONTROL:
				struct VideoStillTriggerControl
				{
					enum EStillImageTriggerControl : BYTE
					{
						Normal = 0,
						TransmitStillImage,
						TransmitViaDedicatedBulkPipe,
						Abort
					}bTrigger;
				}still_trigger_control;
				break;
			case VS_STREAM_ERROR_CODE_CONTROL:
				struct VideoStreamErrorCodeControl
				{
					enum EErrorCode : BYTE
					{
						NoError,
						ProtectedContent,
						InputBufferUnderrun,
						DataDiscontinuity,
						OutputBufferUnderrun,
						OutputBufferOverrun,
						FormatChange,
						StillImageCaptureError,
						UnknownError
					}bStreamErrorCode;
				}stream_error_code_control;
				break;
			case VS_GENERATE_KEY_FRAME_CONTROL:
				struct VideoGenerateKeyFrameControl
				{
					enum EStillImageTriggerControl : BYTE
					{
						NormalOperation = 0,
						GenerateKeyframe
					}bGenerateKeyFrame;
				}keyframe_control;
				break;
			case VS_UPDATE_FRAME_SEGMENT_CONTROL:
				struct VideoUpdateFrameSegmentControl
				{
					BYTE bStartFrameSegment;
					BYTE bEndFrameSegment;
				}update_frame_segment_control;
				break;
			case VS_SYNCH_DELAY_CONTROL:
				struct VideoSyncDelayControl
				{
					WORD wDelay;
				}sync_delay_control;
				break;
			}
		}

	}

};
