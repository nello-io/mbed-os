/**
 * @file lorawan_types.h
 *
 * @brief Contains data structures required by LoRaWANBase class.
 *
 *  \code
 *   ______                              _
 *  / _____)             _              | |
 * ( (____  _____ ____ _| |_ _____  ____| |__
 *  \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *  _____) ) ____| | | || |_| ____( (___| | | |
 * (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *   (C)2013 Semtech
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions===============
 *
 * \endcode
 *
 *
 * License: Revised BSD License, see LICENSE.TXT file include in the project
 *
 * Maintainer: Miguel Luis ( Semtech ), Gregory Cristian ( Semtech ) and Daniel Jaeckle ( STACKFORCE )
 *
 * Copyright (c) 2017, Arm Limited and affiliates.
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef MBED_LORAWAN_TYPES_H_
#define MBED_LORAWAN_TYPES_H_

#include "platform/Callback.h"

/**
 * Option Flags for send(), receive() APIs
 */
#define MSG_UNCONFIRMED_FLAG                  0x01
#define MSG_CONFIRMED_FLAG                    0x02
#define MSG_MULTICAST_FLAG                    0x04
#define MSG_PROPRIETARY_FLAG                  0x08

/**
 * Bit mask for message flags
 */

#define MSG_FLAG_MASK                         0x0F

/**
 * Mask for unconfirmed multicast message
 */
#define MSG_UNCONFIRMED_MULTICAST              0x05

/**
 * Mask for confirmed multicast message
 */
#define MSG_CONFIRMED_MULTICAST                0x06

/**
 * Mask for unconfirmed message proprietary message
 */
#define MSG_UNCONFIRMED_PROPRIETARY            0x09

/**
 * Mask for confirmed proprietary message
 */
#define MSG_CONFIRMED_PROPRIETARY              0x0A

/**
 * LoRaWAN device classes definition.
 *
 * LoRaWAN Specification V1.0.2, chapter 2.1.
 */
typedef enum {
    /**
     * LoRaWAN device class A.
     *
     * LoRaWAN Specification V1.0.2, chapter 3.
     */
    CLASS_A,
    /**
     * LoRaWAN device class B.
     *
     * LoRaWAN Specification V1.0.2, chapter 8.
     */
    CLASS_B,
    /**
     * LoRaWAN device class C.
     *
     * LoRaWAN Specification V1.0.2, chapter 17.
     */
    CLASS_C,
} device_class_t;

/**
 * lorawan_status_t contains status codes in
 * response to stack operations
 */
typedef enum lorawan_status {
    LORAWAN_STATUS_OK = 0,                         /**< Service started successfully */
    LORAWAN_STATUS_BUSY = -1000,                   /**< Service not started - LoRaMAC is busy */
    LORAWAN_STATUS_WOULD_BLOCK = -1001,            /**< LoRaMAC cannot send at the moment or have nothing to read */
    LORAWAN_STATUS_SERVICE_UNKNOWN = -1002,        /**< Service unknown */
    LORAWAN_STATUS_PARAMETER_INVALID = -1003,      /**< Service not started - invalid parameter */
    LORAWAN_STATUS_FREQUENCY_INVALID = -1004,      /**< Service not started - invalid frequency */
    LORAWAN_STATUS_DATARATE_INVALID = -1005,       /**< Service not started - invalid datarate */
    LORAWAN_STATUS_FREQ_AND_DR_INVALID = -1006,    /**< Service not started - invalid frequency and datarate */
    LORAWAN_STATUS_NO_NETWORK_JOINED = -1009,      /**< Service not started - the device is not in a LoRaWAN */
    LORAWAN_STATUS_LENGTH_ERROR = -1010,           /**< Service not started - payload lenght error */
    LORAWAN_STATUS_DEVICE_OFF = -1011,             /**< Service not started - the device is switched off */
    LORAWAN_STATUS_NOT_INITIALIZED = -1012,        /**< Service not started - stack not initialized */
    LORAWAN_STATUS_UNSUPPORTED = -1013,            /**< Service not supported */
    LORAWAN_STATUS_CRYPTO_FAIL = -1014,            /**< Service not started - crypto failure */
    LORAWAN_STATUS_PORT_INVALID = -1015,           /**< Invalid port */
    LORAWAN_STATUS_CONNECT_IN_PROGRESS = -1016,    /**< Services started - Connection in progress */
    LORAWAN_STATUS_NO_ACTIVE_SESSIONS = -1017,            /**< Services not started - No active session */
    LORAWAN_STATUS_IDLE = -1018,                   /**< Services started - Idle at the moment */
#if defined(LORAWAN_COMPLIANCE_TEST)
    LORAWAN_STATUS_COMPLIANCE_TEST_ON = -1019,     /**< Compliance test - is on-going */
#endif
    LORAWAN_STATUS_DUTYCYCLE_RESTRICTED = -1020,
    LORAWAN_STATUS_NO_CHANNEL_FOUND = -1021,
    LORAWAN_STATUS_NO_FREE_CHANNEL_FOUND = -1022,
} lorawan_status_t;

/** The lorawan_connect_otaa structure.
 *
 * A structure representing the LoRaWAN Over The Air Activation
 * parameters.
 */
typedef struct {
    /** End-device identifier
     *
     * LoRaWAN Specification V1.0.2, chapter 6.2.1
     */
    uint8_t *dev_eui;
    /** Application identifier
     *
     * LoRaWAN Specification V1.0.2, chapter 6.1.2
     */
    uint8_t *app_eui;
    /** AES-128 application key
     *
     * LoRaWAN Specification V1.0.2, chapter 6.2.2
     */
    uint8_t *app_key;
    /** Join request trials
     *
     * Number of trials for the join request.
     */
    uint8_t nb_trials;
} lorawan_connect_otaa_t;

/** The lorawan_connect_abp structure.
 *
 * A structure representing the LoRaWAN Activation By Personalization
 * parameters.
 */
typedef struct {
    /** Network identifier
     *
     * LoRaWAN Specification V1.0.2, chapter 6.1.1
     */
    uint32_t nwk_id;
    /** End-device address
     *
     * LoRaWAN Specification V1.0.2, chapter 6.1.1
     */
    uint32_t dev_addr;
    /** Network session key
     *
     * LoRaWAN Specification V1.0.2, chapter 6.1.3
     */
    uint8_t *nwk_skey;
    /** Application session key
     *
     * LoRaWAN Specification V1.0.2, chapter 6.1.4
     */
    uint8_t *app_skey;
} lorawan_connect_abp_t;

/** lorawan_connect_t structure
 *
 * A structure representing the parameters for different connections.
 */
typedef struct lorawan_connect {
    /**
     * Select the connection type, either LORAWAN_CONNECTION_OTAA
     * or LORAWAN_CONNECTION_ABP.
     */
    uint8_t connect_type;

    union {
        /**
         * Join the network using OTA
         */
        lorawan_connect_otaa_t otaa;
        /**
         * Authentication by personalization
         */
        lorawan_connect_abp_t abp;
    } connection_u;

} lorawan_connect_t;

/**
 * Events needed to announce stack operation results.
 *
 * CONNECTED            - When the connection is complete
 * DISCONNECTED         - When the protocol is shut down in response to disconnect()
 * TX_DONE              - When a packet is sent
 * TX_TIMEOUT,          - When stack was unable to send packet in TX window
 * TX_ERROR,            - A general TX error
 * TX_CRYPTO_ERROR,     - If MIC fails, or any other crypto relted error
 * TX_SCHEDULING_ERROR, - When stack is unable to schedule packet
 * RX_DONE,             - When there is something to receive
 * RX_TIMEOUT,          - Not yet mapped
 * RX_ERROR             - A general RX error
 * JOIN_FAILURE         - When all Joining retries are exhausted
 * UPLINK_REQUIRED      - Stack indicates application that some uplink needed
 * AUTOMATIC_UPLINK_ERROR - Stack tried automatically send uplink but some error occurred.
 *                          Application should initiate uplink as soon as possible.
 *
 */
typedef enum lora_events {
    CONNECTED=0,
    DISCONNECTED,
    TX_DONE,
    TX_TIMEOUT,
    TX_ERROR,
    TX_CRYPTO_ERROR,
    TX_SCHEDULING_ERROR,
    RX_DONE,
    RX_TIMEOUT,
    RX_ERROR,
    JOIN_FAILURE,
    UPLINK_REQUIRED,
    AUTOMATIC_UPLINK_ERROR,
} lorawan_event_t;

/**
 * Stack level callback functions
 *
 * 'lorawan_app_callbacks_t' is a structure that holds pointers to the application
 * provided methods which are needed to be called in response to certain
 * requests. The structure is default constructed to set all pointers to NULL.
 * So if the user does not provide the pointer, a response will not be posted.
 * However, the 'lorawan_events' callback is mandatory to be provided as it
 * contains essential events.
 *
 * A link check request could be sent whenever the device tries to send a
 * message and if the network server responds with a link check response,
 * the stack notifies the application be calling the appropriate method set using
 * 'link_check_resp' callback. The result is thus transported to the application
 * via callback function provided.
 *
 * As can be seen from declaration, mbed::Callback<void(uint8_t, uint8_t)> *link_check_resp)
 * carries two parameters. First one is Demodulation Margin and the second one
 * is number of gateways involved in the path to network server.
 *
 * 'battery_level' callback goes in the down direction, i.e., it informs
 * the stack about the battery level by calling a function provided
 * by the upper layers.
 */
typedef struct  {
     /**
      * Mandatory. Event Callback must be provided
      */
     mbed::Callback<void(lorawan_event_t)> events;

     /**
      * Optional
      */
     mbed::Callback<void(uint8_t, uint8_t)> link_check_resp;

     /**
      * Battery level return value must follow the specification
      * for DevStatusAns MAC command:
      *
      *     0       The end-device is connected to an external power source
      *     1 - 254 The battery level, 1 being at minimum and 254 being at maximum
      *     255     The end-device was not able to measure the battery level.
      */
     mbed::Callback<uint8_t(void)> battery_level;
} lorawan_app_callbacks_t;

/**
 * DO NOT MODIFY, WILL BREAK THE API!
 *
 * Structure containing a given data rate range.
 */
typedef union {
    /**
     * Byte-access to the bits.
     */
    int8_t value;
    /**
     * The structure to store the minimum and the maximum datarate.
     */
    struct fields_s {
        /**
         * The minimum data rate.
         *
         * LoRaWAN Regional Parameters V1.0.2rB.
         *
         * The allowed ranges are region-specific.
         * Please refer to \ref DR_0 to \ref DR_15 for details.
         */
        int8_t min :4;
        /**
         * The maximum data rate.
         *
         * LoRaWAN Regional Parameters V1.0.2rB.
         *
         * The allowed ranges are region-specific.
         * Please refer to \ref DR_0 to \ref DR_15 for details.
         */
        int8_t max :4;
    } fields;
} dr_range_t;

/**
 * DO NOT MODIFY, WILL BREAK THE API!
 *
 * LoRaMAC channel definition.
 */
typedef struct {
    /**
     * The frequency in Hz.
     */
    uint32_t frequency;
    /**
     * The alternative frequency for RX window 1.
     */
    uint32_t rx1_frequency;
    /**
     * The data rate definition.
     */
    dr_range_t dr_range;
    /**
     * The band index.
     */
    uint8_t band;
} channel_params_t;

/**
 * DO NOT MODIFY, WILL BREAK THE API!
 *
 * Structure to hold parameters for a LoRa channel.
 */
typedef struct lora_channels_s {
    uint8_t id;
    channel_params_t ch_param;
} loramac_channel_t;

/**
 * DO NOT MODIFY, WILL BREAK THE API!
 *
 * This data structures contains LoRaWAN channel plan, i.e., a pointer to a
 * list of channels and the total number of channels included in the plan.
 */
typedef struct lora_channelplan {
    uint8_t nb_channels;    // number of channels
    loramac_channel_t *channels;
} lorawan_channelplan_t;

#endif /* MBED_LORAWAN_TYPES_H_ */
