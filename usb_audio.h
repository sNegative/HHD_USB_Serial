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
	USB_DEVICE_CLASS_AUDIO = 0x01
};

enum
{
	AC_UNDEFINED = 0x00,
	AC_AUDIOCONTROL = 0x01,
	AC_AUDIOSTREAMING = 0x02,
	AC_MIDISTREAMING = 0x03
};

enum
{
	INTERFACE_PROTOCOL_UNDEFINED = 0x00,
	IP_VERSION_02_00 = 0x20
};

enum
{
	REQ_UNKNOWN,
	DESC_HEADER,
	DESC_INPUT_TERMINAL,
	DESC_OUTPUT_TERMINAL,
	DESC_MIXER_UNIT,
	DESC_SELECTOR_UNIT,
	DESC_FEATURE_UNIT,
	DESC_PROCESSING_UNIT,
	DESC_EXT_UNIT,

	REQ_AS_INTERFACE,
	REQ_AS_ENPOINT,
	REQ_ADD_MEMORY,
	REQ_GETSTATUS
};


enum	// Terminal
{
	TE_CONTROL_UNDEFINED,
	COPY_PROTECT_CONTROL
};

enum	// Feature
{
	FU_CONTROL_UNDEFINED,
	MUTE_CONTROL,
	VOLUME_CONTROL,
	BASS_CONTROL,
	MID_CONTROL,
	TREBLE_CONTROL,
	GRAPHIC_EQUALIZER_CONTROL,
	AUTOMATIC_GAIN_CONTROL,
	DELAY_CONTROL,
	BASS_BOOST_CONTROL,
	LOUDNESS_CONTROL
};

enum // PROCESSING UNIT controls
{
	PU_UPDOWN = 1,
	PU_DOLBY,
	PU_3D,
	PU_REVERB,
	PU_CHORUS,
	PU_COMPRESSOR,
};

// enums from document:
enum	// Up-Down
{
	UD_CONTROL_UNDEFINED,
	UD_ENABLE_CONTROL,
	UD_MODE_SELECT_CONTROL
};

enum	// Dolby Pro Logic
{
	DP_CONTROL_UNDEFINED,
	DP_ENABLE_CONTROL,
	DP_MODE_SELECT_CONTROL
};

enum	// 3D stereo
{
	TRID_CONTROL_UNDEFINED,
	TRID_ENABLE_CONTROL,
	SPACIOUSNESS_CONTROL = 3
};

enum	// Reverb
{
	RV_CONTROL_UNDEFINED,
	RV_ENABLE_CONTROL,
	REVERB_LEVEL_CONTROL,
	REVERB_TIME_CONTROL,
	REVERB_FEEDBACK_CONTROL
};

enum	// Chorus
{
	CH_CONTROL_UNDEFINED,
	CH_ENABLE_CONTROL,
	CHORUS_LEVEL_CONTROL,
	CHORUS_RATE_CONTROL,
	CHORUS_DEPTH_CONTROL
};

enum	// Dynamic Range Compressor
{
	DR_CONTROL_UNDEFINED,
	DR_ENABLE_CONTROL,
	COMPRESSION_RATE_CONTROL,
	MAXAMPL_CONTROL,
	THRESHOLD_CONTROL,
	ATTACK_TIME,
	RELEASE_TIME
};

enum	// Extension Unit
{
	XU_CONTROL_UNDEFINED,
	XU_ENABLE_CONTROL
};

enum	// Endpoint
{
	EP_CONTROL_UNDEFINED,
	SAMPLING_FREQ_CONTROL,
	PITCH_CONTROL
};




//Audio Descriptors

enum
{
	AC_DESCRIPTOR_UNDEFINED  = 0x00,
	HEADER = 0x01,
	INPUT_TERMINAL = 0x02,
	OUTPUT_TERMINAL = 0x03,
	MIXER_UNIT = 0x04,
	SELECTOR_UNIT = 0x05,
	FEATURE_UNIT = 0x06,
	EFFECT_UNIT = 0x07,
	PROCESSING_UNIT = 0x08,
	EXTENSION_UNIT = 0x09,
	CLOCK_SOURCE = 0x0A,
	CLOCK_SELECTOR = 0x0B,
	CLOCK_MULTIPLIER = 0x0C,
	SAMPLE_RATE_CONVERTER = 0x0D,
};

struct ClockSourceDescriptor
{
	BYTE bClockID; // Constant uniquely identifying the Clock Source Entity within the audio function.

	union ClockAttributes
	{
		struct
		{
			BYTE ClockType : 2;
			BYTE ClockSyncronized : 1;
			BYTE Reserved : 5;
		}clock;
		[format("b2w8arf0")]
		BYTE bmAttributes;
	}clock_attributes;
	struct ClockControl
	{
		BYTE ClockFrequencyControl : 2;
		BYTE ClockValidityControl : 2;
		BYTE Reserved : 4;
	}controls;

	BYTE bAssocTerminal;	// Terminal ID of the Terminal that is associated with this Clock Source.
	BYTE iClockSource;		// Index of a string descriptor, describing the Clock Source Entity.
};



struct ClockSelectorDescriptor
{
	BYTE bClockID;
	BYTE bNrInPins;
	BYTE baCSourceID[bNrInPins];
	union ClockControl
	{
		struct
		{
			BYTE ClockSelectorControl : 2;
			BYTE Reserved : 6;
		}clock;
		[format("b2w8arf0")]
		BYTE bmControls;
	}clock_control;
	BYTE iClockSelector;
};


struct ClockMultiplierDescriptor
{
	BYTE bClockID;
	BYTE bCSourceID;

	union ClockControl
	{
		struct
		{
			BYTE ClockNumeratorControl : 2;
			BYTE ClockDenominatorControl : 2;
			BYTE Reserved : 4;
		}clock;
		[format("b2w8arf0")]
		BYTE bmControls;
	}clock_control;
	BYTE iClockMultiplier;
};

struct InputTerminalDescriptor
{
	BYTE bTerminalID;
	WORD wTerminalType;
	BYTE bAssocTerminal;
	BYTE bCSourceID;
	BYTE bNrChannels;

	DWORD bmChannelConfig;
	BYTE iChannelNames;

	union TerminalControl
	{
		struct
		{
			WORD CopyProtect : 2;
			WORD ConnectorControl : 2;
			WORD OverloadControl : 2;
			WORD ClusterControl : 2;
			WORD UnderflowControl : 2;
			WORD OverflowControl : 2;
			WORD Reserved : 4;
		}terminal;
		[format("b2w16arf0")]
		WORD bmControls;
	}terminal_control;

	BYTE iTerminal;
};


struct OutputTerminalDescriptor
{
	BYTE bTerminalID;
	WORD wTerminalType;
	BYTE bAssocTerminal;
	BYTE bSourceID;
	BYTE bCSourceID;

	DWORD bmChannelConfig;
	BYTE iChannelNames;

	WORD bmControls;

	union TerminalControl
	{
		struct
		{
			WORD CopyProtect : 2;
			WORD ConnectorControl : 2;
			WORD OverloadControl : 2;
			WORD ClusterControl : 2;
			WORD UnderflowControl : 2;
			WORD OverflowControl : 2;
			WORD Reserved : 4;
		}terminal;
		[format("b2w16arf0")]
		WORD bmControls;
	}terminal_control;

	BYTE iTerminal;
};




struct MixerUnitDescriptor
{
	BYTE bUnitID;
	BYTE bNrInPins;
	BYTE baSourceID[bNrInPins];

	BYTE bNrChannels;
	DWORD bmChannelConfig;
	BYTE iChannelNames;

	union MixerControl
	{
		struct
		{
			BYTE CopyProtect : 2;
			BYTE UnderflowControl : 2;
			BYTE OverflowControl : 2;
			WORD Reserved : 2;
		}mixer;
		[format("b2w8arf0")]
		BYTE bmControls;
	}controls;
	BYTE iMixer;
};


struct SelectorUnitDescriptor
{
	BYTE bUnitID;
	BYTE bNrInPins;
	BYTE baSourceID[bNrInPins];
	BYTE bmControls;
	BYTE iSelector;
};


struct FeatureUnitDescriptor
{
	BYTE bUnitID;
	BYTE bSourceID;

	var num_channels = ((bLength - 1) - (current_offset - start_offset)) / sizeof(DWORD);

	union FeatureControl
	{
		struct
		{
			DWORD MuteControl : 2;
			DWORD VolumeControl : 2;
			DWORD BassControl : 2;
			DWORD MidControl : 2;
			DWORD TrebleControl : 2;
			DWORD GraphicEqualizer : 2;
			DWORD AutomaticGain : 2;
			DWORD DelayControl : 2;
			DWORD BassBoostControl : 2;
			DWORD LoudnessControl : 2;
			DWORD InputGainControl : 2;
			DWORD InputGainPadControl : 2;
			DWORD PhaseInverterControl : 2;
			DWORD UnderflowControl : 2;
			DWORD OverfowControl : 2;
			DWORD Reserved : 2;
		}feature;
		[format("b2w32arf0")]
		DWORD bmControls;
	}controls[num_channels];

	BYTE iFeature;
};


struct SamplingRateConverterDescriptor
{
	BYTE bUnitID;
	BYTE bSourceID;
	BYTE bCSourceInID;
	BYTE bCSourceOutID;
	BYTE iSRC;
};


struct EffectDescriptor
{
	enum EffectType : WORD
	{
		EFFECT_UNDEFINED,
		PARAM_EQ_SECTION_EFFECT = 1,
		REVERBERATION_EFFECT,
		MOD_DELAY_EFFECT,
		DYN_RANGE_COMP_EFFECT
	};

	BYTE bUnitID;
	WORD wEffectType;
	BYTE bSourceID;

	var num_channels = ((bLength - 1) - (current_offset - start_offset)) / sizeof(DWORD);

	switch (wEffectType)
	{
	case PARAM_EQ_SECTION_EFFECT:
		union EQEffect
		{
			struct
			{
				DWORD EnableControl : 2;
				DWORD CenterFrequencyControl : 2;
				DWORD QFactorControl : 2;
				DWORD GainControl : 2;
				DWORD UnderflowControl : 2;
				DWORD OverflowControl : 2;
				DWORD Reserved : 20;
			}effect;
			[format("b2w32arf0")]
			DWORD bmControls;
		}controls[num_channels];
		break;

	case REVERBERATION_EFFECT:
		union ReverberationEffect
		{
			struct
			{
				DWORD EnableControl : 2;
				DWORD TypeControl : 2;
				DWORD LevelControl : 2;
				DWORD TimeControl : 2;
				DWORD DelayFeedbackControl : 2;
				DWORD PreDelayControl : 2;
				DWORD DensityControl : 2;
				DWORD HiFreqRollOffControl : 2;
				DWORD UnderflowControl : 2;
				DWORD OverflowControl : 2;
				DWORD Reserved : 12;
			}reverb_effect;
			[format("b2w32arf0")]
			DWORD bmControls;
		}controls[num_channels];
		break;

	case MOD_DELAY_EFFECT:
		union ModeDelayEffect
		{
			struct 
			{
				DWORD EnableControl : 2;
				DWORD BalanceControl : 2;
				DWORD RateControl : 2;
				DWORD DepthControl : 2;
				DWORD TimeControl : 2;
				DWORD FeedbackLevelControl : 2;
				DWORD UnderflowControl : 2;
				DWORD OverflowControl : 2;
				DWORD Reserved : 16;
			}mod_delay;
			[format("b2w32arf0")]
			DWORD bmControls;
		}controls[num_channels];
		break;

	case DYN_RANGE_COMP_EFFECT:
		union DynRangeCompEffect
		{
			struct
			{
				DWORD EnableControl : 2;
				DWORD CompressionRatioControl : 2;
				DWORD MaxAmplControl : 2;
				DWORD ThresholdControl : 2;
				DWORD AttackTimeControl : 2;
				DWORD ReleaseTimeControl : 2;
				DWORD UnderflowControl : 2;
				DWORD OverflowControl : 2;
				DWORD Reserved : 16;
			}dyn_range;
			[format("b2w32arf0")]
			DWORD bmControls;
		}controls[num_channels];
		break;
	}

	BYTE iEffects;
};


struct ProcessingUnitDescriptor
{
	enum
	{
		PROCESS_UNDEFINED,
		UPDOWNMIX_PROCESS = 1,
		DOLBY_PROLOGIC_PROCESS,
		STEREO_EXTENDER_PROCESS
	};

	BYTE bUnitID;
	WORD wProcessType;
	BYTE bNrInPins;

	BYTE baSourceID[bNrInPins];

	BYTE bNrChannels;
	DWORD bmChannelConfig;

	BYTE iChannelNames;
	switch (wProcessType)
	{
	case UPDOWNMIX_PROCESS:
		union UpDownProcess
		{
			struct
			{
				WORD EnableControl : 2;
				WORD ModeSelectControl : 2;
				WORD ClusterControl : 2;
				WORD UnderflowControl : 2;
				WORD OverflowControl : 2;
				WORD Reserved : 6;
			}updown;
			[format("b2w16arf0")]
			WORD bmControls;
		}controls;
		break;

	case DOLBY_PROLOGIC_PROCESS:
		union DolbyPrologicProcess
		{
			struct
			{
				WORD EnableControl : 2;
				WORD ModeSelectControl : 2;
				WORD ClusterControl : 2;
				WORD UnderflowControl : 2;
				WORD OverflowControl : 2;
				WORD Reserved : 6;
			}dolby;
			[format("b2w16arf0")]
			WORD bmControls;
		}controls;
		break;

	case STEREO_EXTENDER_PROCESS:
		union StereoExtenderProcess
		{
			struct
			{
				WORD EnableControl : 2;
				WORD WidthControl : 2;
				WORD ClusterControl : 2;
				WORD UnderflowControl : 2;
				WORD OverflowControl : 2;
				WORD Reserved : 6;
			}stereo;
			[format("b2w16arf0")]
			WORD bmControls;
		}controls;
		break;

		break;
	}

	BYTE iProcessing;

	switch (wProcessType)
	{
	case DOLBY_PROLOGIC_PROCESS:
	case UPDOWNMIX_PROCESS:
		BYTE bNrModes;
		DWORD daModes[bNrModes];
		break;

	case STEREO_EXTENDER_PROCESS:
		break;

	default:
		BYTE ProcessSpecific[bLength - (current_offset - start_offset)];
	}
};

struct  ExtensionUnitDescriptor
{
	BYTE bUnitID;
	WORD wExtensionCode;
	BYTE bNrInPins;

	BYTE bNrChannels[bNrInPins];
	DWORD bmChannelConfig;
	BYTE iChannelNames;

	union ExtensionControl
	{
		struct
		{
			BYTE EnableControl : 2;
			BYTE ClusterControl : 2;
			BYTE UnderflowControl : 2;
			BYTE OverflowControl : 2;
		}extensions;
		[format("b2w8arf0")]
		BYTE bmControls;
	}controls;


	BYTE iExtension;
};

struct HeaderDescriptor
{
	WORD bcdADC;
	BYTE bCategory;
	WORD wTotalLength; //Total number of bytes returned for the class - specific AudioControl interface descriptor.Includes the combined length of this descriptor header and all Clock Source, Unit and Terminal descriptors.
	union ExtensionControl
	{
		struct
		{
			BYTE LatencyControl : 2;
			BYTE Reserved : 6;
		}header;
		[format("b2w8arf0")]
		BYTE bmControls;
	}controls;
};

//Audio Control

struct AudioControlInterface
{
	switch (bDescriptorSubtype)
	{
	case HEADER:
		HeaderDescriptor header;
		break;
	case INPUT_TERMINAL:
		InputTerminalDescriptor input_terminal;
		break;
	case OUTPUT_TERMINAL:
		OutputTerminalDescriptor output_terminal;
		break;
	case MIXER_UNIT:
		MixerUnitDescriptor mixer_unit;
		break;
	case SELECTOR_UNIT:
		SelectorUnitDescriptor selector_unit;
		break;
	case FEATURE_UNIT:
		FeatureUnitDescriptor feature_unit;
		break;
	case EFFECT_UNIT:
		EffectDescriptor effect;
		break;
	case PROCESSING_UNIT:
		ProcessingUnitDescriptor processing_unit;
		break;
	case EXTENSION_UNIT:
		ExtensionUnitDescriptor extension_unit;
		break;
	case CLOCK_SOURCE:
		ClockSourceDescriptor clock_source;
		break;
	case CLOCK_SELECTOR:
		ClockSelectorDescriptor clock_selector;
		break;
	case CLOCK_MULTIPLIER:
		ClockMultiplierDescriptor clock_multiplier;
		break;
	case SAMPLE_RATE_CONVERTER:
		SamplingRateConverterDescriptor sampling_rate;
		break;
	}
};

struct ACInterruptEndpointDescriptor
{
	BYTE bEndpointAddress;

	BYTE bmAttributes;
	WORD wMaxPacketSize;
	BYTE bInterval;
};

//Audio streaming
[display(format("{0} Hz", (aSampleFreq[2]<<16)|(aSampleFreq[1]<<8)|aSampleFreq[0]))]
struct SampleFreq
{
	BYTE aSampleFreq[3];
};

struct AudioStreamingInterface
{
	enum
	{
		AS_DESCRIPTOR_UNDEFINED,
		AS_GENERAL,
		AS_FORMAT_TYPE,
		AS_ENCODER,
		AS_DECODER
	};

	enum DecoderEnum : BYTE
	{
		DECODER_UNDEFINED,
		OTHER_DECODER,
		MPEG_DECODER,
		AC3_DECODER,
		WMA_DECODER,
		DTS_DECODER
	};

	enum EncoderEnum : BYTE
	{
		ENCODER_UNDEFINED,
		OTHER_ENCODER,
		MPEG_ENCODER,
		AC3_ENCODER,
		WMA_ENCODER,
		DTS_ENCODER
	};

	enum EFormatTypes : BYTE
	{
		FORMAT_TYPE_UNDEFINED = 0x00,
		FORMAT_TYPE_I,
		FORMAT_TYPE_II,
		FORMAT_TYPE_III,
		FORMAT_TYPE_IV,
		EXT_FORMAT_TYPE_I = 0x81,
		EXT_FORMAT_TYPE_II,
		EXT_FORMAT_TYPE_III
	};

	switch (bDescriptorSubtype)
	{
	case AS_GENERAL:
		BYTE bTerminalLink;
		BYTE bmControls;
		BYTE bFormatType;
		DWORD bmFormats;
		BYTE bNrChannels;
		DWORD bmChannelConfig;
		BYTE iChannelNames;
		break;

	case AS_ENCODER:
		BYTE bEncoderID;
		BYTE bEncoder;

		union EncoderControl
		{
			struct
			{
				DWORD BitRateControl : 2;
				DWORD QualityControl : 2;
				DWORD VBRControl : 2;
				DWORD TypeControl : 2;
				DWORD UnderflowControl : 2;
				DWORD OverflowControl : 2;
				DWORD EncoderErrorControl : 2;
				DWORD Param1Control : 2;
				DWORD Param2Control : 2;
				DWORD Param3Control : 2;
				DWORD Param4Control : 2;
				DWORD Param5Control : 2;
				DWORD Param6Control : 2;
				DWORD Param7Control : 2;
				DWORD Param8Control : 2;
				DWORD Reserved : 2;
			}encoder;
			[format("b2w32arf0")]
			DWORD bmControls;
		}controls;

		BYTE iParam[8];
		BYTE iEncoder;
		break;

	case AS_DECODER:
		BYTE bDecoderID;
		DecoderEnum bDecoder;

		switch (bDecoder)
		{
		case MPEG_DECODER:
			union MPEGCapabilities
			{
				struct
				{
					WORD Layer1 : 1;
					WORD Layer2 : 1;
					WORD Layer3 : 1;
					WORD Mpeg1Only : 1;
					WORD Mpeg1DualChanel : 1;
					WORD Mpeg2SecondStereo : 1;
					WORD Mpeg2_71_ChannelAug : 1;
					WORD AdaptiveMultiChannelPrediction : 1;
					WORD Mpeg2MultiLangSupport : 2;
					WORD HalfFsSupprrt : 1;
					WORD Reserved : 5;
				}capabilities;
				[format("b2w16arf0")]
				WORD bmMPEGCapabilities;
			}mpeg_capabilities;

			union MPEGFeatures
			{
				struct
				{
					BYTE Reserved : 4;
					BYTE IDRC : 2;
					BYTE Reserved1 : 2;

				}features;
				[format("b2w8arf0")]
				BYTE bmMPEGFeatures;
			}mpeg_features;

			break;

		case AC3_DECODER:
			DWORD bmBSID;
			BYTE bmAC3Features;
			break;

		case WMA_DECODER:
			WORD bmWMAProfile;
			break;

		case DTS_DECODER:
			BYTE bmCapabilities;
			break;

		case DECODER_UNDEFINED:
		case OTHER_DECODER:
		default:
			break;
		}

		BYTE bmControls;
		BYTE iDecoder;

		break;

	case AS_FORMAT_TYPE:
		BYTE bFormatType;

		switch (bFormatType)
		{
		case FORMAT_TYPE_I:
			BYTE bNrChannels;
			BYTE bSubslotSize;
			BYTE bBitResolution;
			BYTE bSampleFreqType;
			SampleFreq sample_freq;
			break;
		case FORMAT_TYPE_II:
			WORD wMaxBitRate;
			WORD wSlotsPerFrame;
			break;
		case FORMAT_TYPE_III:
			BYTE bSubslotSize;
			BYTE bBitResolution;
			break;

		case EXT_FORMAT_TYPE_I:
			BYTE bSubslotSize;
			BYTE bBitResolution;
			BYTE bHeaderLength;
			BYTE bControlSize;
			BYTE bSideBandProtocol;
			break;
		case EXT_FORMAT_TYPE_II:
			WORD wMaxBitRate;
			WORD wSamplesPerFrame;
			BYTE bHeaderLength;
			BYTE bSideBandProtocol;
			break;
		case EXT_FORMAT_TYPE_III:
			BYTE bSubslotSize;
			BYTE bBitResolution;
			BYTE bHeaderLength;
			BYTE bSideBandProtocol;
			break;
		}

		break;
	}
};

//Midi Streaming
struct MidiStreamingInterface
{
	BYTE raw[packet_size - current_offset];
};


struct IsochronousAudioDataEndpointDescriptor
{
	//switch (bDescriptorSubType)
	//{
	//case EP_GENERAL:
	//	break;
	//}

	//EP_GENERAL

	BYTE bmAttributes;
	union IsoDataControl
	{
		struct
		{
			BYTE PitchControl : 2;
			BYTE DataOverrunControl : 2;
			BYTE DataUnderrunControl : 2;
			BYTE Reserved : 2;
		}iso_data;
		[format("b2w8arf0")]
		BYTE bmControls;
	}controls;

	enum :BYTE
	{
		Undefined,
		Milliseconds,
		DecodedPCMsamples
	}bLockDelayUnits;

	WORD wLockDelay;
};


struct AudioRequest
{
	RequestType request_type;
	enum EAC_Requests : BYTE
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
	} bRequest;

	WORD wValue;
	BYTE bInterface;
	BYTE bUnitID;
	WORD wLength;

	if (current_offset < packet_size)
	{
		var UnitID = usb_get_unit_id(device_source, bUnitID);
		switch (request_type.bmRequestTypeD.Recipient)
		{
		case 1://AudioControl:
			switch (UnitID)
			{
			case DESC_INPUT_TERMINAL:
			case DESC_OUTPUT_TERMINAL:

				struct AudioTerminalRequest
				{
					switch(wValue>>8)
					{
					case COPY_PROTECT_CONTROL:
						enum ECopyProtect : BYTE
						{
							CPL0, //Copying is permitted without restriction.
							CPL1, //CPL1: One generation of copies may be made.The material is copyright protected and is the original.
							CPL2  //CPL2 : The material is copyright protected and no digital copying is permitted.
						}copy_protect;
						break;

					case TE_CONTROL_UNDEFINED:
						break;
					}
				}terminal_request;
				break;
			case DESC_MIXER_UNIT:
				struct MixerRequest
				{
					$print("ICN", wValue >> 8);
					$print("OCN", wValue & 0xFF);

					WORD Value[wLength / 2];
				}mixer_request;
				break;
			case DESC_SELECTOR_UNIT:
				struct SelectorRequest
				{
					BYTE Value;
				}selector_request;
				break;
			case DESC_FEATURE_UNIT:
				struct FeatureRequest
				{
					$print("Chanel Number", wValue & 0xFF);
				
					switch (wValue >> 8)
					{
					case FU_CONTROL_UNDEFINED:
						break;
					case MUTE_CONTROL:
						struct FeatureMuteControl
						{
							BYTE Value;
						}feature_mute_control;
						break;
					case VOLUME_CONTROL:
						struct FeatureVolumeControl
						{
							if (UnitID == 0xFF)
							{
								WORD Values[wLength / 2];
							}
							else
							{
								BYTE Values[wLength];
							}
						}feature_volume_control;
						break;
					case BASS_CONTROL:
						struct FeatureBassControl
						{
							BYTE Value;
						}feature_bass_control;
						break;
					case MID_CONTROL:
						struct FeatureMidControl
						{
							BYTE Value;
						}feature_mid_control;
						break;
					case TREBLE_CONTROL:
						struct FeatureTrebleControl
						{
							BYTE Value;
						}feature_treble_control;
						break;
					case GRAPHIC_EQUALIZER_CONTROL:
						struct FeatureEqualControl
						{//TODO: show bits
							DWORD Band;
							DWORD Value;
						}feature_equal_control;
						break;
					case AUTOMATIC_GAIN_CONTROL:
						struct FeatureGainControl
						{
							BYTE Value;
						}feature_gain_control;
						break;
					case DELAY_CONTROL:
						struct FeatureDelayControl
						{
							WORD Delay[wLength / 2]; // * 0.0156 ms
						}feature_delay_control;
						break;
					case BASS_BOOST_CONTROL:
						struct FeatureBassBoostControl
						{
							BYTE Value;
						}feature_bass_boost_control;
						break;
					case LOUDNESS_CONTROL:
						struct FeatureLoudnessControl
						{
							BYTE Value;
						}feature_loudness_control;
						break;
					}
				}feature_request;
				break;
			case DESC_PROCESSING_UNIT:
				struct ProcessingUnitRequest
				{
					var TypeID = usb_get_processing_unit_id(device_source, bUnitID);

					switch (TypeID/*bUnitID*/)
					{
					case PU_UPDOWN:
						struct PUUpDown
						{
							switch (wValue >> 8)
							{
							case UD_CONTROL_UNDEFINED:
								//BYTE Undefined;
								break;
							case UD_ENABLE_CONTROL:
								enum EBool : BYTE
								{
									FALSE,
									TRUE
								}enable;
								break;
							case UD_MODE_SELECT_CONTROL:
								BYTE Mode;
								break;
							}
						}up_down;
						break;
					case PU_DOLBY:
						struct PUDolby
						{
							switch (wValue >> 8)
							{
							case UD_CONTROL_UNDEFINED:
								//BYTE Undefined;
								break;
							case UD_ENABLE_CONTROL:
								enum EBool : BYTE
								{
									Enable,
									Disable
								}enable;
								break;
							case UD_MODE_SELECT_CONTROL:
								BYTE Mode;
								break;
							}
						}dolby;
						break;
					case PU_3D:
						struct PU3D
						{
							switch (wValue >> 8)
							{
							case TRID_CONTROL_UNDEFINED:
								//BYTE Undefined;
								break;
							case TRID_ENABLE_CONTROL:
								enum EBool : BYTE
								{
									FALSE,
									TRUE
								}enable;
								break;
							case SPACIOUSNESS_CONTROL:
								BYTE Spaciosness;
								break;
							}
						}_3d;
						break;
					case PU_REVERB:
						struct PUReverb
						{
							switch (wValue >> 8)
							{
							case RV_CONTROL_UNDEFINED:
								//
								break;
							case RV_ENABLE_CONTROL:
								enum EBool : BYTE
								{
									FALSE,
									TRUE
								}enable;
								break;
							case REVERB_LEVEL_CONTROL:
								BYTE ReverbLevel;
								break;
							case REVERB_TIME_CONTROL:
								WORD ReverbTime; // (in 1 / 256 s)
								break;
							case REVERB_FEEDBACK_CONTROL:
								BYTE ReverbFeedback;
								break;
							}
						}reverb;
						break;
					case PU_CHORUS:
						struct PUChorus
						{
							switch (wValue >> 8)
							{
							case CH_CONTROL_UNDEFINED:
								//BYTE Undefined;
								break;
							case CH_ENABLE_CONTROL:
								BYTE ChorusEnable;
								break;
							case CHORUS_LEVEL_CONTROL:
								BYTE ChorusLevel; // in %
								break;
							case CHORUS_RATE_CONTROL:
								WORD ChorusRate; // (in 1 / 256 hZ)
								break;
							case CHORUS_DEPTH_CONTROL:
								WORD ChorusDepth; // (in 1 / 256 ms)
								break;
							}
						}chorus;
						break;
					case PU_COMPRESSOR:
						struct PUCompressor
						{
							switch (wValue >> 8)
							{
							case DR_CONTROL_UNDEFINED:
								//BYTE Undefined;
								break;
							case DR_ENABLE_CONTROL:
								BYTE Enable;
								break;
							case COMPRESSION_RATE_CONTROL:
								WORD CompressionRate; // (in 1 / 256 dB / dB)
								break;
							case MAXAMPL_CONTROL:
								WORD MaxAmplitude; // (in 1 / 256 dB)
								break;
							case THRESHOLD_CONTROL:
								WORD Threshold; // (in 1 / 256 dB)
								break;
							case ATTACK_TIME:
								WORD AttackTime; // (in 1 / 256 ms)
								break;
							case RELEASE_TIME:
								WORD ReleaseTime; // (in 1 / 256 ms)
								break;
							}
						}compressor;
						break;
					}
				}processing_unit_request;
				break;
			case DESC_EXT_UNIT:
				struct ExtensionRequest
				{
					switch (wValue >> 8)
					{
					case XU_CONTROL_UNDEFINED:
						//UndefinedControl
						break;
					case XU_ENABLE_CONTROL:
						struct EnableControl
						{
							BYTE Enable;
						}enable;
						break;
					}
				};
				break;
			}

			break;
		case 2://AudioStreaming
			switch (bUnitID)
			{
			case REQ_AS_INTERFACE:
				//ASInterfaceRequest
				break;
			case REQ_AS_ENPOINT:
				struct ASEndpointRequest
				{
					switch (wValue >> 8)
					{
					case EP_CONTROL_UNDEFINED:
						//
						break;
					case SAMPLING_FREQ_CONTROL:
						BYTE SamplingFrequency[3]; //Sampling Frequency(in Hz) (3 byte size)
						break;
					case PITCH_CONTROL:
						enum ESwitch : BYTE
						{
							ON,
							OFF
						}PitchControl;
						break;
					}

				}endpoint_request;
				break;
			case REQ_ADD_MEMORY:
				struct ADDMemoryRequest
				{
					BYTE ImplementationDependent[packet_size - current_offset];
				}add_memory;
				break;
			case REQ_GETSTATUS:
				struct StatusRequest
				{

				}get_status;
				break;
			}
			break;
	}
	//struct MidiStreaming
		   //var length = (packet_size - current_offset) / 4;
		   //BYTE Code;
		   //var cable = (Code & 0xF0) >> 4; 

		   //switch (Code & 0x0F)
		   //{
		   //case 0x04: //SySex codes
		   //case 0x05:
		   //case 0x06:
		   //case 0x07:

		   //	break;
		   //}
		   //break;
		}

};

