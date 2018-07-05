/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "Descriptors.h"

/** Device descriptor structure. This descriptor, located in SRAM memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(01.10),
	.Class                  = CDC_CSCP_CDCClass,
	.SubClass               = CDC_CSCP_NoSpecificSubclass,
	.Protocol               = CDC_CSCP_NoSpecificProtocol,

	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

	.VendorID               = DEVICE_VID,
	.ProductID              = DEVICE_PID,
	.ReleaseNumber          = VERSION_BCD(00.01),

	.ManufacturerStrIndex   = 0x02,
	.ProductStrIndex        = 0x01,
	.SerialNumStrIndex      = 0x03,

	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Configuration descriptor structure. This descriptor, located in SRAM memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t ConfigurationDescriptor =
{
	.Config =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces        = 2,

			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,

			.ConfigAttributes       = USB_CONFIG_ATTR_BUSPOWERED,

			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},

	.CDC_CCI_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0,
			.AlternateSetting       = 0,

			.TotalEndpoints         = 1,

			.Class                  = CDC_CSCP_CDCClass,
			.SubClass               = CDC_CSCP_ACMSubclass,
			.Protocol               = CDC_CSCP_ATCommandProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.CDC_Functional_Header =
		{
			.Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalHeader_t), .Type = DTYPE_CSInterface},
			.Subtype                = 0x00,

			.CDCSpecification       = VERSION_BCD(01.10),
		},

	.CDC_Functional_ACM =
		{
			.Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalACM_t), .Type = DTYPE_CSInterface},
			.Subtype                = 0x02,

			.Capabilities           = 0x04,
		},

	.CDC_Functional_Union =
		{
			.Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalUnion_t), .Type = DTYPE_CSInterface},
			.Subtype                = 0x06,

			.MasterInterfaceNumber  = 0,
			.SlaveInterfaceNumber   = 1,
		},

	.CDC_NotificationEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DIR_IN | CDC_NOTIFICATION_EPNUM),
			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = CDC_NOTIFICATION_EPSIZE,
			.PollingIntervalMS      = 0xFF
		},

	.CDC_DCI_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 1,
			.AlternateSetting       = 0,

			.TotalEndpoints         = 2,

			.Class                  = CDC_CSCP_CDCDataClass,
			.SubClass               = CDC_CSCP_NoDataSubclass,
			.Protocol               = CDC_CSCP_NoDataProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.CDC_DataOutEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DIR_OUT | CDC_RX_EPNUM),
			.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = CDC_TXRX_EPSIZE,
			.PollingIntervalMS      = 0x01
		},

	.CDC_DataInEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DIR_IN | CDC_TX_EPNUM),
			.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = CDC_TXRX_EPSIZE,
			.PollingIntervalMS      = 0x01
		}
};

/** Language descriptor structure. This descriptor, located in SRAM memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},

	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t ProductString =
{
	.Header                 = {.Size = USB_STRING_LEN(61), .Type = DTYPE_String},

	#if DEVICE_PID == 0x0003
	.UnicodeString          = L"Original Prusa i3 MK3 Multi Material 2.0 upgrade (bootloader)"
	#elif DEVICE_PID == 0x0036
	.UnicodeString          = L"Arduino Leonardo" 
	#elif DEVICE_PID == 0x0037
	.UnicodeString			= L"Arduino Micro   "
	#elif DEVICE_PID == 0x003C
	.UnicodeString			= L"Arduino Esplora "
	#else
	.UnicodeString			= L"USB IO board    "
	#endif
};

const USB_Descriptor_String_t ManufNameString = 
{
	.Header					= {.Size = USB_STRING_LEN(28), .Type = DTYPE_String},
	
	#if DEVICE_VID == 0x2c99
	.UnicodeString			= L"Prusa Research (prusa3d.com)"
	#elif DEVICE_VID == 0x2341
	.UnicodeString			= L"Arduino LLC"
	#else
	.UnicodeString			= L"Unknown    "
	#endif
};

// macro to disable interrupts and return the previous status flags
#define DISABLE_INT()                            \
({                                               \
    uint8_t flag;                                \
    __asm__ __volatile__                         \
    (                                            \
        "in %0, 0x3f"               "\n\t"       \
        "cli"                       "\n\t"       \
        : "=r" (flag)                            \
        :                                        \
        : "memory"                               \
    );                                           \
    flag;                                        \
})

// macro to restore the previous interrupt enable state
#define RESTORE_INT(flag)                        \
({                                               \
    __asm__ __volatile__                         \
    (                                            \
        "out 0x3f, %0"               "\n\t"      \
        :                                        \
        : "d" (flag)                             \
        : "memory"                               \
    );                                           \
})

// macro to read a byte from the "signature row" given its index
#define READ_SIG_BYTE(idx)                       \
({                                               \
    uint8_t val = _BV(SPMEN) | _BV(SIGRD);       \
    uint8_t *sigPtr = (uint8_t *)(uint16_t)idx;  \
    uint8_t stat = DISABLE_INT();                \
    __asm__                                      \
    (                                            \
        "out %2, %0"        "\n\t"               \
        "lpm %0, Z"         "\n\t"               \
        : "=r" (val)                             \
        : "z" (sigPtr),                          \
          "I" (_SFR_IO_ADDR(SPMCSR)),            \
          "0" (val)                              \
    );                                           \
    RESTORE_INT(stat);                           \
    val;                                         \
})

#define Flash_read_sn(pos)          (READ_SIG_BYTE((0x07*2)+(pos)))	//!< This macro function allows to read the serial number of the product.
#define SN_LENGTH                   10                     			//!< Size of the serial number containt in product.

struct
{
	USB_Descriptor_Header_t Header;
	uint16_t UnicodeString[SN_LENGTH * 2];
} ATTR_PACKED SerialNumberString;

/** This function is called by the library when in device mode, and must be overridden (see LUFA library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = &DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			if (!(DescriptorNumber))
			{
				Address = &LanguageString;
				Size    = LanguageString.Header.Size;
			}
			else if (DescriptorNumber == DeviceDescriptor.ProductStrIndex) 
			{
				Address = &ProductString;
				Size    = ProductString.Header.Size;
			} else if (DescriptorNumber == DeviceDescriptor.ManufacturerStrIndex)
			{
				Address = &ManufNameString;
				Size	= ManufNameString.Header.Size;
			} else if (DescriptorNumber == DeviceDescriptor.SerialNumStrIndex)
			{
				uint8_t i = 0;
				SerialNumberString.Header.Size = USB_STRING_LEN(20);
				SerialNumberString.Header.Type = DTYPE_String;
				for (; i < SN_LENGTH * 2; ++ i) {
					uint8_t id = Flash_read_sn(i >> 1);
					if (i & 1)
						id &= 0x0f;
					else
						id >>= 4;
					SerialNumberString.UnicodeString[i] = id + ((id < 10) ? '0' : ('A' - 10));
				}
				Address = &SerialNumberString;
				Size	= SerialNumberString.Header.Size;
			}

			break;
	}

	*DescriptorAddress = Address;
	return Size;
}
