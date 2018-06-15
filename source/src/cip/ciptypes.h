/*******************************************************************************
 * Copyright (c) 2009, Rockwell Automation, Inc.
 * Copyright (C) 2016-2018, SoftPLC Corportion.
 *
 ******************************************************************************/
#ifndef CIPSTER_CIPTYPES_H_
#define CIPSTER_CIPTYPES_H_


#include <string>
#include <vector>
#include <string.h>

#include "typedefs.h"
#include "trace.h"
#include "cipster_user_conf.h"
#include "ciperror.h"
#include "byte_bufs.h"

//* @brief Assembly Class Code
enum ClassIds
{
    kCipIdentityClass = 0x01,
    kCipMessageRouterClass = 0x02,
    kCipAssemblyClass = 0x04,
    kCipConnectionClass = 0x05,
    kCipConnectionManagerClass = 0x06,
    kCipTcpIpInterfaceClass = 0xF5,
    kCipEthernetLinkClass = 0xF6,
};


/**
 * Enum SegmentType
 * is the set of bits 7-5 in the Segment Type/Format byte
 */
enum SegmentType
{
    // Segments
    kSegmentTypePort = 0x00,                    ///< Port segment
    kSegmentTypeLogical  = 0x20,                ///< Logical segment
    kSegmentTypeNetwork  = 0x40,                ///< Network segment
    kSegmentTypeSymbolic = 0x60,                ///< Symbolic segment
    kSegmentTypeData = 0x80,                    ///< Data segment
    kSegmentTypeDataTypeConstructed = 0xA0,     ///< Data type constructed
    kSegmentTypeDataTypeElementary  = 0xC0,     ///< Data type elementary
    kSegmentTypeSegmentTypeReserved = 0xE0
};

/// Connection Manager Error codes
enum ConnectionManagerStatusCode
{
    kConnectionManagerStatusCodeSuccess = 0x00,
    kConnectionManagerStatusCodeErrorConnectionInUse = 0x0100,
    kConnectionManagerStatusCodeErrorTransportTriggerNotSupported = 0x0103,
    kConnectionManagerStatusCodeErrorOwnershipConflict = 0x0106,
    kConnectionManagerStatusCodeErrorConnectionNotFoundAtTargetApplication = 0x0107,
    kConnectionManagerStatusCodeErrorInvalidOToTConnectionType  = 0x123,
    kConnectionManagerStatusCodeErrorInvalidTToOConnectionType  = 0x124,
    kConnectionManagerStatusCodeErrorInvalidOToTConnectionSize  = 0x127,
    kConnectionManagerStatusCodeErrorInvalidTToOConnectionSize  = 0x128,
    kConnectionManagerStatusCodeErrorNoMoreConnectionsAvailable = 0x0113,
    kConnectionManagerStatusCodeErrorVendorIdOrProductcodeError = 0x0114,
    kConnectionManagerStatusCodeErrorDeviceTypeError    = 0x0115,
    kConnectionManagerStatusCodeErrorRevisionMismatch   = 0x0116,
    kConnectionManagerStatusCodeErrorPITGreaterThanRPI  = 0x011b,
    kConnectionManagerStatusCodeInvalidConfigurationApplicationPath = 0x0129,
    kConnectionManagerStatusCodeInvalidConsumingApllicationPath     = 0x012A,
    kConnectionManagerStatusCodeInvalidProducingApplicationPath     = 0x012B,
    kConnectionManagerStatusCodeInconsistentApplicationPathCombo    = 0x012F,
    kConnectionManagerStatusCodeNonListenOnlyConnectionNotOpened    = 0x0119,
    kConnectionManagerStatusCodeErrorParameterErrorInUnconnectedSendService = 0x0205,
    kConnectionManagerStatusCodeErrorInvalidSegmentTypeInPath   = 0x0315,
    kConnectionManagerStatusCodeTargetObjectOutOfConnections    = 0x011A
};


/**
 * Enum CipDataType
 * is the set of encoded CIP data types for CIP Messages
 */
enum CipDataType
{
    kCipAny = 0x00,         ///< data type that can not be directly encoded
    kCipBool = 0xC1,        ///< boolean data type
    kCipSint = 0xC2,        ///< 8-bit signed integer
    kCipInt = 0xC3,         ///< 16-bit signed integer
    kCipDint = 0xC4,        ///< 32-bit signed integer
    kCipLint = 0xC5,        ///< 64-bit signed integer
    kCipUsint = 0xC6,       ///< 8-bit unsignedeger
    kCipUint = 0xC7,        ///< 16-bit unsigned
    kCipUdint = 0xC8,       ///< 32-bit unsigned
    kCipUlint = 0xC9,       ///< 64-bit unsigned
    kCipReal = 0xCA,        ///< Single precision floating point
    kCipLreal = 0xCB,       ///< Double precision floating point
    kCipStime = 0xCC,       ///< Synchronous time information*, type of DINT
    kCipDate = 0xCD,        ///< Date only
    kCipTimeOfDay = 0xCE,   ///< Time of day
    kCipDateAndTime = 0xCF, ///< Date and time of day
    kCipString  = 0xD0,     ///< Character string, 1 byte per character
    kCipByte    = 0xD1,     ///< 8-bit bit string
    kCipWord    = 0xD2,     ///< 16-bit bit string
    kCipDword   = 0xD3,     ///< 32-bit bit string
    kCipLword   = 0xD4,     ///< 64-bit bit string
    kCipString2 = 0xD5,     ///< Character string, 2 byte per character
    kCipFtime   = 0xD6,     ///< Duration in micro-seconds, high resolution; range of DINT
    kCipLtime   = 0xD7,     ///< Duration in micro-seconds, high resolution, range of LINT
    kCipItime   = 0xD8,     ///< Duration in milli-seconds, short; range of INT
    kCipStringN = 0xD9,     ///< Character string, N byte per character
    kCipShortString = 0xDA, /**< Character string, 1 byte per character, 1 byte
                             *  length indicator */
    kCipTime = 0xDB,        ///< Duration in milli-seconds; range of DINT
//    kCipEpath = 0xDC,       ///< CIP path segments
    kCipEngUnit = 0xDD,     ///< Engineering Units
    kCipStringI = 0xDE,     ///< International Character String

    // definition of some CIP structs
    // need to be validated in IEC 61131-3 subclause 2.3.3
    // TODO: Check these codes
    kCipUsintUsint = 0xA0,                      ///< Used for CIP Identity attribute 4 Revision
    kCip6Usint = 0xA2,                          ///< Struct for MAC Address (six USINTs)
    kCipMemberList  = 0xA3,                     ///<
    kCipByteArray   = 0xA4,                     ///<
};


/**
 * Enum CIPServiceCode
 * is the set of CIP service codes.
 * Common services codes range from 0x01 to 0x1c.  Beyond that there can
 * be class or instance specific service codes and some may overlap.
 */
enum CIPServiceCode
{
    kGetAttributeAll = 0x01,
    kSetAttributeAll = 0x02,
    kGetAttributeList = 0x03,
    kSetAttributeList = 0x04,
    kReset  = 0x05,
    kStart  = 0x06,
    kStop   = 0x07,
    kCreate = 0x08,
    kDelete = 0x09,
    kMultipleServicePacket = 0x0A,
    kApplyAttributes = 0x0D,
    kGetAttributeSingle = 0x0E,
    kSetAttributeSingle = 0x10,
    kFindNextObjectInstance = 0x11,
    kRestore = 0x15,
    kSave = 0x16,
    kNoOperation    = 0x17,
    kGetMember  = 0x18,
    kSetMember  = 0x19,
    kInsertMember = 0x1A,
    kRemoveMember = 0x1B,
    kGroupSync = 0x1C,

    // Start CIP class or instance specific services, probably should go in class specific area
    kForwardClose = 0x4E,
    kUnconnectedSend = 0x52,
    kForwardOpen = 0x54,
    kLargeForwardOpen = 0x5b,
    kGetConnectionOwner = 0x5A
    // End CIP class or instance specific services
};


/// Definition of Get and Set Flags for CIP Attributes
enum CIPAttributeFlag           // TODO: Rework
{
    kNotSetOrGetable= 0,        ///< Neither set-able nor get-able
    kGetAll         = 1<<0,     ///< Get-able via CipClass::GetAttributeAll()
    kGetSingle      = 1<<1,     ///< Get-able via CipClass::GetAttribute()
    kSetSingle      = 1<<2,     ///< Set-able via CipClass::SetAttribute()

    kSetAndGet      = kGetAll | kGetSingle | kSetSingle,
};


enum IoConnectionEvent
{
    kIoConnectionEventOpened,
    kIoConnectionEventTimedOut,
    kIoConnectionEventClosed
};


struct CipByteArray
{
    EipUint16   length;     ///< Length of the Byte Array
    EipByte*    data;       ///< Pointer to the data
};


struct CipRevision
{
    EipUint8    major_revision;
    EipUint8    minor_revision;
};


class CipInstance;
class CipAttribute;
class CipClass;
class CipMessageRouterRequest;
class CipMessageRouterResponse;
class CipConn;


class CipCommonPacketFormatData;


// these are used for creating the getAttributeAll masks
// TODO there might be a way simplifying this using __VARARGS__ in #define
#define MASK1( a )          ( 1 << (a) )
#define MASK2( a, b )       ( 1 << (a) | 1 << (b) )
#define MASK3( a, b, c )    ( 1 << (a) | 1 << (b) | 1 << (c) )
#define MASK4( a, b, c, d ) ( 1 << (a) | 1 << (b) | 1 << (c) | 1 << (d) )
#define MASK5( a, b, c, d, e ) \
    ( 1 << (a) | 1 << (b) | 1 << (c) | 1 << (d) | 1 << (e) )

#define MASK6( a, b, c, d, e, f ) \
    ( 1 << (a) | 1 << (b) | 1 << (c) | 1 << (d) | 1 << (e) | 1 << (f) )

#define MASK7( a, b, c, d, e, f, g ) \
    ( 1 << (a) | 1 << (b) | 1 << (c) | 1 << (d) | 1 << (e) | 1 << (f) | 1 << (g) )

#define MASK8( a, b, c, d, e, f, g, h ) \
    ( 1 << (a) | 1 << (b) | 1 << (c) | 1 << (d) | 1 << (e) | 1 << (f) | \
      1 << (g) | 1 << (h) )

#define OR7( a, b, c, d, e, f, g ) \
    ( (a)<<6 | (b)<<5 | (c)<<4 | (d)<<3 | (e)<<2 || (f)<<1 || (g) )

#endif // CIPSTER_CIPTYPES_H_
