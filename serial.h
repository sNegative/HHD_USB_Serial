// Copyright (c) 2018 by HHD Software Ltd.
// This file is part of the HHD Software Device Monitoring Studio
// For usage and distribution policies, consult the license distributed with a product installation program

// Modification options:
// Trial mode: Modified file is loaded, compiled and used on startup
// Lite and Standard Editions: Protocol-related features are not available
// Professional Edition: Pre-configured version is used, changes in this file will be ignored
// Ultimate Edition: Modified file is loaded, compiled and used on startup

// See Serial packet at the bottom.

#pragma once

#include "std_serialdefs.h"		// includes stddefs.h
#include "ppp.h"

// CONNECTPACKET is generated on session startup and/or on PnP connect/disconnect device events
struct CONNECTPACKET
{
hidden:
	char padding;
visible:
	int Connected;
	WCHAR Payload[(packet_size - current_offset) / 2];
	
	title = format("\"{0}\" connected to session", Payload);
};

[category(protocol)] public union ModbusSerial
{
	var PayloadSize = packet_size - current_offset;

	if (PayloadSize)
	{
	hidden:
		char ModbusPayload[PayloadSize];
		var IsAsciiMode = (ModbusPayload[0] == ':' && ModbusPayload[PayloadSize - 1] == 0x0a && ModbusPayload[PayloadSize - 2] == 0x0d);

	visible:
#pragma byte_order(BigEndian)

		if (IsAsciiMode)
			ModbusAscii modbus_ascii;
		else
			Modbus modbus;
#pragma byte_order(LittleEndian)
	}
};

// This structure defines a serial packet payload

[category(protocol)]
public struct PPPSerial
{
	BYTE FlagStart; //0x7e
	BYTE Address;
	BYTE Control;
	PPPFrame frame;
	WORD FCS; //can be DWORD
	BYTE End; //0x7e
};

// This structure defines a serial packet payload
[category(protocol)]
public struct SerialPayload
{
	var comm_mode = get_communications_mode();

	if (comm_mode == PPP_COMMUNICATION)
	{
		// For PPP communication mode, the payload is PPP packet
		PPPSerial ppp;
	}
	else if ((comm_mode == MODBUS_COMMUNICATION_RTU) || (comm_mode == MODBUS_COMMUNICATION_ASCII))
	{
		// For MODBUS communication mode, payload is ModbusSerial packet
		ModbusSerial modbus_packet;
	}
	else
	{
		// Otherwise, present payload as a BYTE array
		BYTE Payload[packet_size - current_offset];
		title = format("{0}: {1} bytes", Type == IRP_MJ_READ ? "IRP_MJ_READ" : "IRP_MJ_WRITE", sizeof(Payload));
	}
};

// This structure represents a serial bridge protocol
[category(protocol)]
public struct BridgePacket
{
	var comm_mode = get_communications_mode();
	var Type = (sending_device == 1) ? IRP_MJ_READ : IRP_MJ_WRITE;
	var is_ppp = comm_mode == PPP_COMMUNICATION;
	var is_modbus = (comm_mode == MODBUS_COMMUNICATION_RTU) || (comm_mode == MODBUS_COMMUNICATION_ASCII);
	var packet_type = PACKET_GENERAL;
	var PayloadSize = packet_size - current_offset;
	var DataValid = true;
	var is_packet_up = (sending_device == 1) ? true : false;
	var status = 0;

	SerialPayload Payload;
};

// The following structures and enumerations are used in IOPACKET structure
struct SERIAL_CHARS
{
	UCHAR EofChar;
	UCHAR ErrorChar;
	UCHAR BreakChar;
	UCHAR EventChar;
	UCHAR XonChar;
	UCHAR XoffChar;
};

enum SerialError : ULONG
{
	SERIAL_ERROR_BREAK				=0x00000001,
	SERIAL_ERROR_FRAMING			=0x00000002,
	SERIAL_ERROR_OVERRUN			=0x00000004,
	SERIAL_ERROR_QUEUEOVERRUN	=0x00000008,
	SERIAL_ERROR_PARITY				=0x00000010,
};

enum HoldReason : ULONG
{
	SERIAL_TX_WAITING_FOR_CTS			=0x00000001,
	SERIAL_TX_WAITING_FOR_DSR			=0x00000002,
	SERIAL_TX_WAITING_FOR_DCD			=0x00000004,
	SERIAL_TX_WAITING_FOR_XON			=0x00000008,
	SERIAL_TX_WAITING_XOFF_SENT		=0x00000010,
	SERIAL_TX_WAITING_ON_BREAK			=0x00000020,
	SERIAL_RX_WAITING_FOR_DSR			=0x00000040,
};

struct SERIAL_STATUS
{
	SerialError Errors;
	HoldReason HoldReasons;
	ULONG AmountInInQueue;
	ULONG AmountInOutQueue;
	BOOLEAN EofReceived;
	BOOLEAN WaitForImmediate;
};

enum ControlHandshake : ULONG
{
	SERIAL_DTR_CONTROL				=0x01,
	SERIAL_DTR_HANDSHAKE			=0x02,
	SERIAL_CTS_HANDSHAKE			=0x08,
	SERIAL_DSR_HANDSHAKE			=0x10,
	SERIAL_DCD_HANDSHAKE			=0x20,
	SERIAL_DSR_SENSITIVITY			=0x40,
	SERIAL_ERROR_ABORT				=0x80000000,
};

enum FlowReplace : ULONG
{
	SERIAL_AUTO_TRANSMIT			=0x01,
	SERIAL_AUTO_RECEIVE				=0x02,
	SERIAL_ERROR_CHAR					=0x04,
	SERIAL_NULL_STRIPPING			=0x08,
	SERIAL_BREAK_CHAR					=0x10,
	SERIAL_RTS_CONTROL				=0x40,
	SERIAL_RTS_HANDSHAKE			=0x80,
	SERIAL_XOFF_CONTINUE			=0x80000000,
};

struct SERIAL_HANDFLOW
{
	ControlHandshake handshake;
	FlowReplace flow;
	LONG XonLimit;
	LONG XoffLimit;
};

struct SERIAL_LINE_CONTROL
{
	StopBitEnum StopBits;
	ParityEnum Parity;
	UCHAR WordLength;
};

struct COMMPROP
{
	WORD wPacketLength;
	WORD wPacketVersion;
	DWORD dwServiceMask;
	DWORD dwReserved1;
	DWORD dwMaxTxQueue;
	DWORD dwMaxRxQueue;
	MaskBaudRates dwMaxBaud;
	MaskProviders dwProvSubType;
	MaskCapabilities dwProvCapabilities;
	MaskSettable dwSettableParams;
	MaskBaudRates dwSettableBaud;
	MaskBits wSettableData;
	MaskParity wSettableStopParity;
	DWORD dwCurrentTxQueue;
	DWORD dwCurrentRxQueue;
	DWORD dwProvSpec1;
	DWORD dwProvSpec2;
	WCHAR wcProvChar[1];
};

struct SERIALPERF_STATS
{
	ULONG ReceivedCount;
	ULONG TransmittedCount;
	ULONG FrameErrorCount;
	ULONG SerialOverrunErrorCount;
	ULONG BufferOverrunErrorCount;
	ULONG ParityErrorCount;
};

struct SERIAL_TIMEOUTS
{
	ULONG ReadIntervalTimeout;
	ULONG ReadTotalTimeoutMultiplier;
	ULONG ReadTotalTimeoutConstant;
	ULONG WriteTotalTimeoutMultiplier;
	ULONG WriteTotalTimeoutConstant;
};

struct _SERIAL_QUEUE_SIZE
{
	ULONG InSize;
	ULONG OutSize;
};

// IOPACKET structure describes the serial I/O control packet
struct IOPACKET
{
hidden:
	char padding;
visible:
	[symbolic_only, exact_only]
	IOCTL IoCode;
	var io_code = visualize(ref(IoCode));

	if (is_packet_up)
	{
		// The following control codes contain data only for UP packets
		switch (IoCode)
		{
		case IOCTL_SERIAL_CONFIG_SIZE:
			ULONG ConfigSize;
			title = format("{0}: {1}", io_code, ConfigSize);
			break;
		case IOCTL_SERIAL_GET_BAUD_RATE:
			ULONG CurrentBaudRate;
			title = format("{0}: {1}", io_code, CurrentBaudRate);
			break;
		case IOCTL_SERIAL_GET_CHARS:
			SERIAL_CHARS CurrentChars;
			title = format("{0}: {1}", io_code, visualize(ref(CurrentChars)));
			break;
		case IOCTL_SERIAL_GET_COMMSTATUS:
			SERIAL_STATUS CurrentStatus;
			title = format("{0}: {1}", io_code, visualize(ref(CurrentStatus)));
			break;
		case IOCTL_SERIAL_GET_DTRRTS:
			DWORD Code;
			$print("DTR", (Code & SERIAL_DTR_STATE) ? "ON" : "OFF");
			$print("RTS", (Code & SERIAL_RTS_STATE) ? "ON" : "OFF");
			title = format("{0}: DTR = {1}, RTS = {2}", io_code, DTR, RTS);
			break;
		case IOCTL_SERIAL_GET_HANDFLOW:
			SERIAL_HANDFLOW CurrentHandFlow;
			title = format("{0}: {1}", io_code, visualize(ref(CurrentHandFlow)));
			break;
		case IOCTL_SERIAL_GET_LINE_CONTROL:
			SERIAL_LINE_CONTROL CurrentLineControl;
			title = format("{0}: {1}", io_code, visualize(ref(CurrentLineControl)));
			break;
		case IOCTL_SERIAL_GET_PROPERTIES:
			COMMPROP CurrentCommProp;
			title = format("{0}: {1}", io_code, visualize(ref(CurrentCommProp)));
			break;
		case IOCTL_SERIAL_GET_STATS:
			SERIALPERF_STATS CurrentStats;
			title = format("{0}: {1}", io_code, visualize(ref(CurrentStats)));
			break;
		case IOCTL_SERIAL_GET_TIMEOUTS:
			SERIAL_TIMEOUTS CurrentTimeout;
			title = format("{0}: {1}", io_code, visualize(ref(CurrentTimeout)));
			break;
		case IOCTL_SERIAL_GET_WAIT_MASK:
			MaskEvents CurrentWaitMask;
			title = format("{0}: {1}", io_code, visualize(ref(CurrentWaitMask)));
			break;
		case IOCTL_SERIAL_WAIT_ON_MASK:
			MaskEvents WaitResult;
			title = format("{0}: {1}", io_code, visualize(ref(WaitResult)));
			break;
		case IOCTL_SERIAL_GET_MODEMSTATUS:
			MaskModemStatus ModemStatus;
			title = format("{0}: {1}", io_code, visualize(ref(ModemStatus)));
			break;
		default:
			title = io_code;
		}
	}
	else
	{
		// The following control codes contain data only for DOWN packets
		switch (IoCode)
		{
		case IOCTL_SERIAL_SET_BAUD_RATE:
			ULONG NewBaudRate;
			title = format("{0}: {1}", io_code, NewBaudRate);
			break;
		case IOCTL_SERIAL_SET_CHARS:
			SERIAL_CHARS NewChars;
			title = format("{0}: {1}", io_code, visualize(ref(NewChars)));
			break;
		case IOCTL_SERIAL_SET_HANDFLOW:
			SERIAL_HANDFLOW NewHandflow;
			title = format("{0}: {1}", io_code, visualize(ref(NewHandflow)));
			break;
		case IOCTL_SERIAL_SET_LINE_CONTROL:
			SERIAL_LINE_CONTROL NewLineControl;
			title = format("{0}: {1}", io_code, visualize(ref(NewLineControl)));
			break;
		case IOCTL_SERIAL_SET_TIMEOUTS:
			SERIAL_TIMEOUTS NewTimeOuts;
			title = format("{0}: {1}", io_code, visualize(ref(NewTimeOuts)));
			break;
		case IOCTL_SERIAL_SET_WAIT_MASK:
			MaskEvents NewWaitMask;
			title = format("{0}: {1}", io_code, visualize(ref(NewWaitMask)));
			break;
		case IOCTL_SERIAL_IMMEDIATE_CHAR:
			BYTE ImmediateChar;
			title = format("{0}: {1b016x}", io_code, ImmediateChar);
			break;
		case IOCTL_SERIAL_PURGE:
			MaskPurge PurgeMask;
			title = format("{0}: {1}", io_code, PurgeMask);
			break;
		case IOCTL_SERIAL_SET_QUEUE_SIZE:
			_SERIAL_QUEUE_SIZE SERIAL_QUEUE_SIZE;
			title = format("{0}: {1}", io_code, visualize(ref(SERIAL_QUEUE_SIZE)));
			break;
		case IOCTL_SERIAL_LSRMST_INSERT:
			BYTE escapeChar;
			title = format("{0}: {1b016x}", io_code, escapeChar);
			break;
		default:
			title = io_code;
		}
	}
};

struct CREATEPACKET
{
	ULONG ProcessId;
	title = format("Port opened by ProcessId = {0}", ProcessId);
};

// This structure represents a serial protocol
[category(protocol), display(title)] public struct Serial
{
	#pragma byte_order(LittleEndian)

	// Synthesize Direction field
	$print("Direction", is_packet_up ? "Up":"Down");

	var comm_mode = get_communications_mode();
	var is_ppp = comm_mode == PPP_COMMUNICATION;
	var is_modbus = (comm_mode == MODBUS_COMMUNICATION_RTU) || (comm_mode == MODBUS_COMMUNICATION_ASCII);
	var title = "Serial";

	switch (packet_type)
	{
	case PACKET_CONDISCONNECT:
		// This internal packet is generated when monitoring session connects or disconnects to/from the device. This event happens in the beginning or after PnP disconnect/connect events
		CONNECTPACKET conn_disconn;
		break;
	case PACKET_GENERAL:
		// General packet is either READ, WRITE or CLOSE packet

		if (is_ppp || is_modbus)
		{
			// For PPP and MODBUS communication mode, we hide padding and IRP major function fields
		hidden:
			char padding;
			IrpMJFunction Type;
		visible:
			// This packet contains valid data only if the following condition is TRUE
			var DataValid = (Type == IRP_MJ_READ && is_packet_up) || (Type == IRP_MJ_WRITE && !is_packet_up);
			if (DataValid)
			{
				if (Type != IRP_MJ_CLOSE)
					SerialPayload Payload;
				else
					$print("Request", "Close Request");
			}
		}
		else
		{
		hidden:
			char padding;
		visible:
			IrpMJFunction Type;

			var PayloadSize = packet_size - current_offset;
			var DataValid = (Type == IRP_MJ_READ && is_packet_up) || (Type == IRP_MJ_WRITE && !is_packet_up);

			if (DataValid)
			{
				switch (Type)
				{
				case IRP_MJ_READ:
				case IRP_MJ_WRITE:
					SerialPayload Payload;
					break;
				case IRP_MJ_CLOSE:
					$print("Request", "Close Request");
					title = "IRP_MJ_CLOSE";
					break;
				}
			}
		}
		break;
	case PACKET_CREATE:
		// This internal packet is generated when client application opens a port handle
		CREATEPACKET create;
		break;
	case PACKET_IO:
		// This is a I/O control packet
		IOPACKET io;
		break;
	}

	title = (is_packet_up ? "\u2191 " : "\u2193 ") + title;
};
