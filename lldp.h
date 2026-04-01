// Copyright (c) 2020 by HHD Software Ltd.
// This file is part of the HHD Software Device Monitoring Studio
// For usage and distribution policies, consult the license distributed with a product installation program

// Modification options:
// Trial mode: Modified file is loaded, compiled and used on startup
// Lite, Standard and Professional Editions: Pre-configured version is used, changes in this file will be ignored
// Ultimate Edition: Modified file is loaded, compiled and used on startup

// Link Layer Discovery Protocol

struct SystemCapabilitiesTLV
{
	struct _SystemCapabilities
	{
		WORD Other : 1;
		WORD Repeater : 1;
		WORD Bridge : 1;
		WORD WLANAccessPoint : 1;
		WORD Router : 1;
		WORD Telephone : 1;
		WORD DOCSISCableDevice : 1;
		WORD StationOnly : 1;
		WORD Reserved : 8;
	}SystemCapabilities;

	struct _EnabledCapabilities
	{
		WORD Other : 1;
		WORD Repeater : 1;
		WORD Bridge : 1;
		WORD WLANAccessPoint : 1;
		WORD Router : 1;
		WORD Telephone : 1;
		WORD DOCSISCableDevice : 1;
		WORD StationOnly : 1;
		WORD Reserved : 8;
	}EnabledCapabilities;
};

enum LLDPInterfaceNumberingSubtype : BYTE
{
	Unknown = 1,
	IfIndex = 2,
	SystemPortNumber = 3
};

enum ChassisIDSubType : BYTE
{
	Reserved,
	Chassis,
	InterfaceAlias,
	Port,
	MAC_Address,
	NetworkAddress,
	InterfaceName,
	LocallyAssigned
};

enum PortIDSubType
{
		Reserved,
		InterfaceAlias,
		Port,
		MAC_Address,
		NetworkAddress,
		InterfaceName,
		AgentCircuitID,
		LocallyAssigned
};

[category(protocol)] public struct LLDP
{
	struct LldpValue
	{

		struct _TLVHeader
		{
			WORD TLVType : 7;
			WORD TLVLength : 9;
		} TLVHeader;

		switch (TLVHeader.TLVType)
		{
		case 0x00:
			break;

		case 0x01:
			struct _ChassisIDTLV
			{
				ChassisIDSubType SubType;
				switch (SubType)
				{
				case 4:
					MacAddress MacAddress;
					break;
				case 1:
				case 5:
					char ChassisIDifName[TLVHeader.TLVLength - 1];
					break;
				default:
					BYTE ChassisID[TLVHeader.TLVLength];
				}
			}ChassisIDTLV;
			break;

		case 0x02:
			struct _PortIDTLV
			{
				PortIDSubType SubType;
				switch (SubType)
				{
				case 4:
					MacAddress MacAddress;
					break;
				case 1:
				case 5:
				case 7:
					char PortIDifName[TLVHeader.TLVLength - 1];
					break;
				default:
					BYTE PortID[TLVHeader.TLVLength - 1];
				}
			}PortIDTLV;
			break;
		case 0x03:
			struct _TimeToLiveTLV
			{
				WORD TimeToLive;
			}TimeToLiveTLV;
			break;
		case 0x04:
			struct _PortDescriptionTLV
			{
				char PortDescription[TLVHeader.TLVLength];
			}PortDescriptionTLV;
			break;

		case 0x05:
			struct _SystemNameTLV
			{
				char SystemName[TLVHeader.TLVLength];
			}SystemNameTLV;
			break;

		case 0x06:
			struct _SystemDescriptionTLV
			{
				char SystemDescription[TLVHeader.TLVLength];
			}SystemDescriptionTLV;
			break;

		case 0x07:
			SystemCapabilitiesTLV TLV;
			break;

		case 0x08:
			struct _ManagementAddress
			{
				BYTE Length;
				BYTE AddressSubtype;
				switch (AddressSubtype)
				{
				case 1:
					IPv4Address IPv4Address;
					break;
				case 2:
					IPv6Address IPv6Address;
					break;
				default:
					BYTE Address[Length - 1];
				}

				LLDPInterfaceNumberingSubtype InterfaceNumberingSubtype;
				DWORD InterfaceNumber;
				BYTE OIDStringLength;
				BYTE ObjectIdentifier[OIDStringLength];
			}ManagementAddress;
			break;

		case 0x7F:
			struct _TLV
			{
				//[onread(format("{0b2w8arf0}{1b2w8arf0}{2b2w8arf0}", _1[0], _1[1], _1[2]))]
				BYTE OUI[3];
				var oui = ((OUI[0] << 16) | OUI[1] << 8) | OUI[2];
				switch (oui)
				{
				case 0x00120f:
					struct _IEEE802_3
					{
						BYTE DefinedSubtype;
						switch (DefinedSubtype)
						{
						case 1:
							struct _MACOrPHYConfigurationOrStatusTLV
							{
								struct _AutoNegotiationSupportOrStatus
								{
									BYTE IfMauAutoNegSupported : 1;
									BYTE IfMauAutoNegAdminStatus : 1;
									BYTE Reserved : 6;
								}AutoNegotiationSupportOrStatus;

								struct _PMDAutoNegotiationAdvertisedCapability
								{
									WORD BOther : 1;
									WORD B10BaseT : 1;
									WORD B10BaseTFD : 1;
									WORD B100BaseT4 : 1;
									WORD B100BaseTX : 1;
									WORD B100BaseTXFD : 1;
									WORD B100BaseT2 : 1;
									WORD B100BaseT2FD : 1;
									WORD BFdxPause : 1;
									WORD BFdxAPause : 1;
									WORD BFdxSPause : 1;
									WORD BFdxBPause : 1;
									WORD B1000BaseX : 1;
									WORD B1000BaseXFD : 1;
									WORD B1000BaseT : 1;
									WORD B1000BaseTFD : 1;
								}PMDAutoNegotiationAdvertisedCapability;
							
								WORD OperationalMAUType;
							}MACOrPHYConfigurationOrStatusTLV;
							break;

						case 2:
							struct _PowerViaMDITLV
							{
								struct _MDIPowerSupport
								{
									BYTE PortClass : 1;
									BYTE PSEMDIPowerSupport : 1;
									BYTE PSEMDIPowerState : 1;
									BYTE PSEPairsControlAbility : 1;
									BYTE Reserved : 4;
								}MDIPowerSupport;

								BYTE PSEPowerPair;
								BYTE PowerClass;
							}PowerViaMDITLV;

							break;

						case 3:
							struct _LinkAggregationTLV
							{
								struct _AggregationStatus
								{
									BYTE AggregationCapability : 1;
									BYTE AggregationStatus : 1;
									BYTE Reserved : 6;
								}AggregationStatus;
								DWORD AggregatedPortID;
							}LinkAggregationTLV;
							break;

						case 4:
							WORD Maximum802_FrameSize;
							break;

						default:
							BYTE Payload[TLVHeader.TLVLength - 4];
						}
					}IEEE802_3;
					break;

				case 0x0012BB:
					struct _TIA
					{
						BYTE TIADefinedSubtype;
						switch (TIADefinedSubtype)
						{
						case 1:
							struct LLDPMEDCapabilitiesTLV
							{
								struct _LLDPMEDCapabilities
								{
									WORD LLDPMEDCapabilities : 1;
									WORD NetworkPolicy : 1;
									WORD LocationIdentification : 1;
									WORD ExtendedPowerViaMDIPSE : 1;
									WORD ExtendedPowerViaMDIPD : 1;
									WORD Inventory : 1;
									WORD Reserved2 : 10;
								}LLDPMEDCapabilities;
								BYTE LLDPMEDDeviceType;
							}LLDPMEDCapabilitiesTLV;
							break;

						case 2:
							struct _NetworkPolicyTLV
							{
								DWORD ApplicationType : 8;
								DWORD DSCPValue : 6;
								DWORD Layer2Priority : 3;
								DWORD VLANID : 12;
								DWORD Reserved : 1;
								DWORD Tagged : 1;
								DWORD UnknownPolicy : 1;
							}NetworkPolicyTLV;
							break;

						case 3:
							struct _LocationIdentificationTLV
							{
								BYTE LocationDataFormat;
								switch (LocationDataFormat)
								{
								case 1:
									struct _CoordinateBasedLCIDataFormat
									{
										BYTE Payload[16];
									}CoordinateBasedLCIDataFormat;
									break;
								case 2:
									struct _CivicAddressLCIdataformat
									{
										BYTE Length;
										BYTE What;
										char CountryCode[2];
										var nLCIEnd = current_offset + Length - 3;
										struct _LCI
										{
											BYTE Type;
											BYTE Length;
											char value[Length];
											if (current_offset >= nLCIEnd)
												$break_array(true);
										}lci[*];
									}CivicAddressLCIdataformat;
									break;
								case 3:
									char ELIN[TLVHeader.TLVLength - 5];
									break;
								default:
									BYTE LocationID[TLVHeader.TLVLength - 5];
								}
							}LocationIdentificationTLV;
							break;
						case 4:
							struct _ExtendedPowerViaMDITLV
							{
								BYTE PowerPriority : 4;
								BYTE PowerSource : 2;
								BYTE PowerType : 2;
								WORD PowerValue;
							}ExtendedPowerViaMDITLV;
							break;
						case 5:
							BYTE HardwareRevision[TLVHeader.TLVLength - 4];
							break;
						case 6:
							BYTE FirmwareRevision[TLVHeader.TLVLength - 4];
							break;
						case 7:
							BYTE SoftwareRevision[TLVHeader.TLVLength - 4];
							break;
						case 8:
							BYTE SerialNumber[TLVHeader.TLVLength - 4];
							break;
						case 9:
							BYTE ManufacturerName[TLVHeader.TLVLength - 4];
							break;
						case 10:
							BYTE ModelName[TLVHeader.TLVLength - 4];
							break;
						case 11:
							BYTE AssetID[TLVHeader.TLVLength - 4];
							break;
						}
					}TIA;
					break;

				case 0x0080C2:
					struct _IEEE802_1
					{
						BYTE IEEE802Dot1DefinedSubtype;
						switch (IEEE802Dot1DefinedSubtype)
						{
						case 1:
							WORD PortVLANIdentifier;
							break;
						case 2:
							struct _PortAndProtocolVLANIDTLV
							{
								struct _Flags
								{
									BYTE Reserved1 : 1;
									BYTE PortAndProtocolVLANSupported : 1;
									BYTE PortAndProtocolVLANEnabled : 1;
									BYTE Reserved2 : 5;
								}Flags;
								WORD PortAndProtocolVLANID;
							}PortAndProtocolVLANIDTLV;
							break;
						case 3:
							struct _VLANNameTLV
							{
								WORD VLANID;
								BYTE Length;
								char VLANName[Length];
							}VLANNameTLV;
							break;
						case 4:
							struct _ProtocolIdentityTLV
							{
								BYTE Length;
								BYTE ProtocolIdentity[Length];
							}ProtocolIdentityTLV;
							break;
						}
					}IEEE802_1;
					break;

				default:
					BYTE Payload[TLVHeader.TLVLength - 3];
				}
			}TLV;
			break;

		default:
			BYTE Payload[TLVHeader.TLVLength];
		}
		if (current_offset >= packet_size)
			$break_array(true);
	}values[*];
};
