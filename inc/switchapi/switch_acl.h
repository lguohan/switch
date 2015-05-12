/*
Copyright 2013-present Barefoot Networks, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

//
//  switch_acl.h
//  switch_api
//
//  Created on 7/10/14.
//  Copyright (c) 2014 bn. All rights reserved.
//

#ifndef _switch_acl_h_
#define _switch_acl_h_

#include "switch_id.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    
/** @defgroup ACL ACL API
 *  API functions define and manipulate Access lists
 *  @{
 */ // begin of ACL API
    
/** ACL Types */
typedef enum switch_acl_type_ {
    SWITCH_ACL_TYPE_IP,             /**< IPv4 ACL */
    SWITCH_ACL_TYPE_MAC,            /**< MAC ACL */
    SWITCH_ACL_TYPE_IPV6,           /**< IPv6 ACL */
    SWITCH_ACL_TYPE_MIRROR,         /**< Mirror ACL */
    SWITCH_ACL_TYPE_QOS,            /**< QoS ACL */
    SWITCH_ACL_TYPE_SYSTEM,         /**< Ingress System ACL */
    SWITCH_ACL_TYPE_EGRESS_SYSTEM,  /**< Egress System ACL */
    SWITCH_ACL_TYPE_IP_RACL,        /**< IPv4 Route ACL */
    SWITCH_ACL_TYPE_IPV6_RACL,      /**< IPv6 Route ACL */
    SWITCH_ACL_TYPE_MAX
} switch_acl_type_t;

/** Acl IP field enum */
typedef enum switch_acl_ip_field_ {
    SWITCH_ACL_IP_FIELD_IPV4_SRC,       /**< IPv4 Source address */
    SWITCH_ACL_IP_FIELD_IPV4_DEST,      /**< IPv4 Dest address */
    SWITCH_ACL_IP_FIELD_IP_PROTO,       /**< IP Protocol */
    SWITCH_ACL_IP_FIELD_L4_SOURCE_PORT, /**< L4 source port UDP/TCP */
    SWITCH_ACL_IP_FIELD_L4_DEST_PORT,   /**< L4 dest port UDP/TCP */
    SWITCH_ACL_IP_FIELD_ICMP_TYPE,      /**< ICMP type */
    SWITCH_ACL_IP_FIELD_ICMP_CODE,      /**< ICMP code */
    SWITCH_ACL_IP_FIELD_TCP_FLAGS,      /**< TCP flags */
    SWITCH_ACL_IP_FIELD_TTL,            /**< TTL */
    SWITCH_ACL_IP_FIELD_ETH_TYPE,       /**< Ether type */

    SWITCH_ACL_IP_FIELD_MAX
} switch_acl_ip_field_t;

/** Acl IPv6 field enum */
typedef enum switch_acl_ipv6_field_ {
    SWITCH_ACL_IPV6_FIELD_IPV6_SRC,         /**< IPv6 Source address */
    SWITCH_ACL_IPV6_FIELD_IPV6_DEST,        /**< IPv6 Destination address */
    SWITCH_ACL_IPV6_FIELD_IP_PROTO,         /**< IP protocol */
    SWITCH_ACL_IPV6_FIELD_L4_SOURCE_PORT,   /**< L4 source port (UDP/TCP) */
    SWITCH_ACL_IPV6_FIELD_L4_DEST_PORT,     /**< L4 Dest port (UDP/TCP) */
    SWITCH_ACL_IPV6_FIELD_ICMP_TYPE,        /**< ICMP type */
    SWITCH_ACL_IPV6_FIELD_ICMP_CODE,        /**< ICMP code */
    SWITCH_ACL_IPV6_FIELD_TCP_FLAGS,        /**< TCP flags */
    SWITCH_ACL_IPV6_FIELD_TTL,              /**< TTL */
    SWITCH_ACL_IPV6_FIELD_ETH_TYPE,         /**< Ether type */

    SWITCH_ACL_IPV6_FIELD_MAX
} switch_acl_ipv6_field_t;

/** Acl IP field list */
typedef union switch_acl_ip_value_ {
    unsigned int ipv4_source;                         /**< v4 source IP */
    unsigned int ipv4_dest;                           /**< v4 destination IP */
    unsigned short ip_proto;                          /**< protocol */
    unsigned short l4_source_port;                    /**< souce port */
    unsigned short l4_dest_port;                      /**< destination port */
    unsigned short eth_type;                          /**< ethernet type */
    unsigned char icmp_type;                          /**< icmp type */
    unsigned char icmp_code;                          /**< icmp code */
    unsigned char tcp_flags;                          /**< tcp flags */
    unsigned char ttl;                                /**< time to live */ 
} switch_acl_ip_value;

/** Acl IPv6 field list */
typedef union switch_acl_ipv6_value_ {
    uint128_t ipv6_source;                            /**< v6 souce IP */
    uint128_t ipv6_dest;                              /**< v6 destination IP */
    unsigned short ip_proto;                          /**< protocol */
    unsigned short l4_source_port;                    /**< source port */
    unsigned short l4_dest_port;                      /**< destination port */
    unsigned short eth_type;                          /**< ethernet type */
    unsigned char icmp_type;                          /**< icmp type */
    unsigned char icmp_code;                          /**< icmp code */
    unsigned char tcp_flags;                          /**< tcp flags */
    unsigned char ttl;                                /**< time to live */
    uint64_t source_mac;                              /**< source mac */
    uint64_t dest_mac;                                /**< destination mac */
} switch_acl_ipv6_value;

/** Acl IP mask */
typedef union switch_acl_ip_mask_ {
    unsigned type:1;                                  /**< acl mask type */
    union {
        uint32_t mask;                                /**< mask value */
        unsigned int start, end;                      /**< mask range */
    } u;                                              /**< ip mask union */
} switch_acl_ip_mask;

/** Acl IPV6 mask */
typedef union switch_acl_ipv6_mask_ {
    unsigned type:1;                                  /**< acl mask type */
    union {
        uint128_t mask;                               /**< mask value */
        unsigned int start, end;                      /**< mask range */
    } u;                                              /**< ipv6 mask union */
} switch_acl_ipv6_mask;

/** Acl IP key value pair */
typedef struct switch_acl_ip_key_value_pair_ {
    switch_acl_ip_field_t field;                          /**< acl ip field type */
    switch_acl_ip_value value;                            /**< acl ip field value */
    switch_acl_ip_mask mask;                              /**< acl ip field mask */
} switch_acl_ip_key_value_pair_t;

/** Acl IPv6 key value pair */
typedef struct {
    switch_acl_ipv6_field_t field;                        /**< acl ip field type */
    switch_acl_ipv6_value value;                          /**< acl ip field value */
    switch_acl_ipv6_mask mask;                            /**< acl ip field mask */
} switch_acl_ipv6_key_value_pair_t;

/** Acl IP action */
typedef enum switch_acl_ip_action_ {
    SWITCH_ACL_ACTION_NOP,                  /**< Do nothing action */
    SWITCH_ACL_ACTION_DROP,                 /**< Drop the packet */
    SWITCH_ACL_ACTION_PERMIT,               /**< Permit */
    SWITCH_ACL_ACTION_LOG,                  /**< Log packet by sending to CPU */
    SWITCH_ACL_ACTION_REDIRECT,             /**< Redirect packet to new destination */
    SWITCH_ACL_ACTION_REDIRECT_TO_CPU,      /**< Redirect packet to CPU */
    SWITCH_ACL_ACTION_COPY_TO_CPU,          /**< Send Copy of packet to CPU */
    SWITCH_ACL_ACTION_SET_NATMODE,          /**< Set NAT mode */
    SWITCH_ACL_ACTION_SET_MIRROR,           /**< Set mirror session */
    SWITCH_ACL_QOS_ACTION_COS,              /**< Set Class of Service */
    SWITCH_ACL_QOS_ACTION_DSCP,             /**< Set the DSCP */
    SWITCH_ACL_QOS_ACTION_TC,               /**< Set the traffic class */

    SWITCH_ACL_ACTION_MAX
} switch_acl_ip_action_t;

/** Acl Mac field enum */
typedef enum switch_acl_mac_field_ {
    SWITCH_ACL_MAC_FIELD_ETH_TYPE,              /**< Ether type */
    SWITCH_ACL_MAC_FIELD_SOURCE_MAC,            /**< Source MAC address */
    SWITCH_ACL_MAC_FIELD_DEST_MAC,              /**< Destination MAC address */

    SWITCH_ACL_MAC_FIELD_MAX
} switch_acl_mac_field_t;

/** Acl mac field list */
typedef union switch_acl_mac_value_ {
    unsigned short eth_type;                        /**< ethernet type */
    uint64_t source_mac;                            /**< source mac */
    uint64_t dest_mac;                              /**< destionation mac */
} switch_acl_mac_value;

/** Acl mac mask */
typedef union switch_acl_mac_mask_ {
    unsigned type:1;                                /**< acl mask type */
    union {
        uint64_t mask;                              /**< mask value */
        unsigned int start, end;                    /**< mask range */
    } u;                                            /**< mac mask union */
} switch_acl_mac_mask;

/** Acl mac key value pair */
typedef struct switch_acl_mac_key_value_pair_ {
    switch_acl_mac_field_t field;                       /**< acl mac field type */
    switch_acl_mac_value value;                         /**< acl mac field value */
    switch_acl_mac_mask mask;                           /**< acl mac field mask */
} switch_acl_mac_key_value_pair_t;

/** ACL ip racl field enum */
typedef enum switch_acl_ip_racl_field_ {
    SWITCH_ACL_IP_RACL_FIELD_IPV4_SRC,          /**< IPv4 Source address */
    SWITCH_ACL_IP_RACL_FIELD_IPV4_DEST,         /**< IPv4 Dest address */
    SWITCH_ACL_IP_RACL_FIELD_IP_PROTO,          /**< IP protocol (TCP/UDP) */
    SWITCH_ACL_IP_RACL_FIELD_L4_SOURCE_PORT,    /**< L4 source port */
    SWITCH_ACL_IP_RACL_FIELD_L4_DEST_PORT,      /**< L4 dest port */

    SWITCH_ACL_IP_RACL_FIELD_MAX
} switch_acl_ip_racl_field_t;

/** ACL ipv6 racl field enum */
typedef enum switch_acl_ipv6_racl_field_ {
    SWITCH_ACL_IPV6_RACL_FIELD_IPV6_SRC,        /**< IPv6 source address */
    SWITCH_ACL_IPV6_RACL_FIELD_IPV6_DEST,       /**< IPv6 dest address */
    SWITCH_ACL_IPV6_RACL_FIELD_IP_PROTO,        /**< IPv6 protocol */
    SWITCH_ACL_IPV6_RACL_FIELD_L4_SOURCE_PORT,  /**< L4 source port */
    SWITCH_ACL_IPV6_RACL_FIELD_L4_DEST_PORT,    /**< L4 dest port */

    SWITCH_ACL_IPV6_RACL_FIELD_MAX
} switch_acl_ipv6_racl_field_t;

/** Acl ip racl field list */
typedef union switch_acl_ip_racl_value_ {
    unsigned int ipv4_source;                       /**< v4 source IP */ 
    unsigned int ipv4_dest;                         /**< v4 destination IP */
    unsigned short ip_proto;                        /**< protocol */
    unsigned short l4_source_port;                  /**< source port */
    unsigned short l4_dest_port;                    /**< destination port */
} switch_acl_ip_racl_value;

/** Acl ipv6 racl field list */
typedef union switch_acl_ipv6_racl_value_ {
    uint128_t ipv6_source;                          /**< v6 source IP */
    uint128_t ipv6_dest;                            /**< v6 destination IP */
    unsigned short ip_proto;                        /**< protocol */
    unsigned short l4_source_port;                  /**< source port */
    unsigned short l4_dest_port;                    /**< destination port */
} switch_acl_ipv6_racl_value;

/** Acl ip racl mask */ 
typedef union switch_acl_ip_racl_mask_ {
    unsigned type:1;                                /**< acl mask type */ 
    union {
        uint32_t mask;                              /**< mask value */
        unsigned int start, end;                    /**< mask range */
    } u;                                            /**< ip racl mask union */
} switch_acl_ip_racl_mask;

/** Acl ipv6 racl mask */ 
typedef union switch_acl_ipv6_racl_mask_ {
    unsigned type:1;                                /**< acl mask type */
    union {
        uint128_t mask;                             /**< mask value */
        unsigned int start, end;                    /**< mask range */
    } u;                                            /**< ipv6 racl mask union */
} switch_acl_ipv6_racl_mask;

/** Acl ip racl key value pair */
typedef struct switch_acl_ip_racl_key_value_pair_ {
    switch_acl_ip_racl_field_t field;                   /**< acl ip racl field type */
    switch_acl_ip_racl_value value;                     /**< acl ip racl field value */
    switch_acl_ip_racl_mask mask;                       /**< acl ip racl field mask */
} switch_acl_ip_racl_key_value_pair_t;

/** Acl ipv6 racl key value pair */
typedef struct switch_acl_ipv6_racl_key_value_pair_ {
    switch_acl_ipv6_racl_field_t field;                 /**< acl ip racl field type */
    switch_acl_ipv6_racl_value value;                   /**< acl ip racl field value */
    switch_acl_ipv6_racl_mask mask;                     /**< acl ip racl field mask */
} switch_acl_ipv6_racl_key_value_pair_t;

/** Acl Qos field enum */
typedef enum switch_acl_qos_field_ {
    SWITCH_ACL_QOS_FIELD_IPV4_SRC,              /**< IPv4 Source address */
    SWITCH_ACL_QOS_FIELD_IPV4_DEST,             /**< IPv4 Dest address */
    SWITCH_ACL_QOS_FIELD_IP_PROTO,              /**< IP protocol */
    SWITCH_ACL_QOS_FIELD_TC,                    /**< IP traffic class */
    SWITCH_ACL_QOS_FIELD_EXP,                   /**< EXP value */
    SWITCH_ACL_QOS_FIELD_DSCP,                  /**< DSCP value */

    SWITCH_ACL_QOS_FIELD_MAX
} switch_acl_qos_field_t;

/** Acl qos field list */
typedef union switch_acl_qos_value_ {
    unsigned int ipv4_source;                       /**< v4 source IP */
    unsigned int ipv4_dest;                         /**< v4 destination IP */
    unsigned short ip_proto;                        /**< protocol */
    unsigned char tc;                               /**< traffic control */
    unsigned char exp;                              /**< experimental */
    unsigned char dscp;                             /**< dscp */
} switch_acl_qos_value;

/** Acl qod mask */
typedef union switch_acl_qos_mask_ {
    unsigned type:1;                                /**< acl mask type */
    union {
        uint32_t mask;                              /**< mask value */
        unsigned int start, end;                    /**< mask range */
    } u;                                            /**< qos mask union */
} switch_acl_qos_mask;

/** Acl qos key value pair */
typedef struct switch_acl_qos_key_value_pair_ {
    switch_acl_qos_field_t field;                       /**< acl qos field type */ 
    switch_acl_qos_value value;                         /**< acl qos field value */
    switch_acl_qos_mask mask;                           /**< acl qos field mask */
} switch_acl_qos_key_value_pair_t;

/** Acl mirror field enum */
typedef enum switch_acl_mirror_field_ {
    SWITCH_ACL_MIRROR_FIELD_IPV4_SRC,           /**< IPv4 source address */
    SWITCH_ACL_MIRROR_FIELD_IPV4_DEST,          /**< IPv4 dest address */
    SWITCH_ACL_MIRROR_FIELD_IP_PROTO,           /**< IP protocol */
    SWITCH_ACL_MIRROR_FIELD_ETH_TYPE,           /**< Ether type */
    SWITCH_ACL_MIRROR_FIELD_SOURCE_MAC,         /**< Source MAC address */
    SWITCH_ACL_MIRROR_FIELD_DEST_MAC,           /**< Dest MAC address */

    SWITCH_ACL_MIRROR_FIELD_MAX
} switch_acl_mirror_field_t;

/** Acl mirror field list */
typedef union switch_acl_mirror_value_ {
    unsigned int ipv4_source;                       /**< v4 source IP */
    unsigned int ipv4_dest;                         /**< v4 destination IP */
    unsigned short ip_proto;                        /**< protocol */
    unsigned short eth_type;                        /**< ethernet type */
    uint64_t source_mac;                            /**< source mac */
    uint64_t dest_mac;                              /**< destination mac */
} switch_acl_mirror_value;

/** Acl mirror mask */
typedef union switch_acl_mirror_mask_ {
    unsigned type:1;                                /**< acl mask type */
    union {
        uint32_t mask;                              /**< mask value */
        unsigned int start, end;                    /**< mask range */
    } u;                                            /**< mirror mask union */
} switch_acl_mirror_mask;

/** Acl mirror key value pair */
typedef struct switch_acl_mirror_key_value_pair_ {
    switch_acl_mirror_field_t field;                    /**< acl mirror field type */
    switch_acl_mirror_value value;                      /**< acl mirror field value */
    switch_acl_mirror_mask mask;                        /**< acl mirror field mask */
} switch_acl_mirror_key_value_pair_t;

/** Acl system field enum */
typedef enum switch_acl_system_field_ {
    SWITCH_ACL_SYSTEM_FIELD_IPV4_SRC,               /**< IPv4 Source address */
    SWITCH_ACL_SYSTEM_FIELD_IPV4_DEST,              /**< IPv4 Dest address */
    SWITCH_ACL_SYSTEM_FIELD_IP_PROTO,               /**< IP protocol */
    SWITCH_ACL_SYSTEM_FIELD_ETH_TYPE,               /**< Ether type */
    SWITCH_ACL_SYSTEM_FIELD_SOURCE_MAC,             /**< Source MAC address */
    SWITCH_ACL_SYSTEM_FIELD_DEST_MAC,               /**< Dest MAC address */
    SWITCH_ACL_SYSTEM_FIELD_IPSG_CHECK,             /**< IP sourceguard check */
    SWITCH_ACL_SYSTEM_FIELD_ACL_DENY,               /**< IP ACL Deny check */
    SWITCH_ACL_SYSTEM_FIELD_RACL_DENY,              /**< Route ACL deny check */
    SWITCH_ACL_SYSTEM_FIELD_URPF_CHECK,             /**< URPF check */
    SWITCH_ACL_SYSTEM_FIELD_SRC_VTEP_MISS,          /**< VTEP miss check */
    SWITCH_ACL_SYSTEM_FIELD_ROUTED,                 /**< Routed packet check */
    SWITCH_ACL_SYSTEM_FIELD_LINK_LOCAL,             /**< Link local address (IPv6) */
    SWITCH_ACL_SYSTEM_FIELD_BD_CHECK,               /**< Bridge domain check */
    SWITCH_ACL_SYSTEM_FIELD_TTL,                    /**< TTL */
    SWITCH_ACL_SYSTEM_FIELD_EGRESS_PORT,            /**< Egress port */
    SWITCH_ACL_SYSTEM_FIELD_STP_STATE,              /**< STP state */
    SWITCH_ACL_SYSTEM_FIELD_CONTROL_FRAME,          /**< Control frame */
    SWITCH_ACL_SYSTEM_FIELD_IPV4_ENABLED,           /**< IPv4 enabled on BD */

    SWITCH_ACL_SYSTEM_FIELD_MAX
} switch_acl_system_field_t;

/** Maximum Acl fields */
#define SWITCH_ACL_FIELD_MAX SWITCH_ACL_SYSTEM_FIELD_MAX

/** Acl system field list */
typedef union switch_acl_system_value_ {
    unsigned int ipv4_source;                         /**< v4 source IP */
    unsigned int ipv4_dest;                           /**< v4 destination IP */
    unsigned short ip_proto;                          /**< protocol */
    unsigned short eth_type;                          /**< ethernet type */
    switch_mac_addr_t source_mac;                         /**< source mac */
    switch_mac_addr_t dest_mac;                           /**< destination mac */
    unsigned ipsg_check :1,                           /**< ip sourceguard check */
             acl_deny:1,                              /**< acl deny */
             racl_deny:1,                             /**< racl deny */
             urpf_check_fail:1,                       /**< urpf check fail */
             src_vtep_miss:1,                         /**< source tunnel end point miss */
             routed:1,                                /**< routed */
             src_is_link_local:1,                     /**< link local source ip */
             bd_check:1,                              /**< same bd check */
             l2_miss:1,                               /**< mac table miss */
             l2_move:10,                              /**< mac move */
             control_frame:1,                         /**< control frame */
             ipv4_enabled:1;                          /**< IPv4 enabled on BD */
    unsigned char ttl;                                /**< time to live */
    unsigned short out_port;                          /**< egress port */
    unsigned char stp_state;                          /**< spanning tree port state */
} switch_acl_system_value;

/** Acl system mask */
typedef union switch_acl_system_mask_ {
    unsigned type:1;                                  /**< acl mask type */
    union {
        uint64_t mask;                                /**< mask value */
        unsigned int start, end;                      /**< mask range */
    } u;                                              /**< system acl mask union */
} switch_acl_system_mask;

/** Acl system key value pair */
typedef struct switch_acl_system_key_value_pair_ {
    switch_acl_system_field_t field;                      /**< acl system field type */
    switch_acl_system_value value;                        /**< acl system field value */
    switch_acl_system_mask mask;                          /**< acl system field mask */
} switch_acl_system_key_value_pair_t;

/** Acl action parameters */
typedef union switch_acl_action_params_ {
    struct {
        unsigned int clone_spec, drop_reason;         /**< mirror acl actions parameters */
    } mirror;                                         /**< mirror acl struct */
} switch_acl_action_params_t;

typedef switch_acl_ip_action_t switch_acl_ipv6_action_t;     /**< IPv6 acl action */
typedef switch_acl_ip_action_t switch_acl_mac_action_t;      /**< mac acl action */
typedef switch_acl_ip_action_t switch_acl_system_action_t;   /**< system acl action */
typedef switch_acl_ip_action_t switch_acl_action_t;          /**< acl action */

/**
 ACL Key list create
 @param device device
 @param type - acl type
*/
switch_handle_t switch_api_acl_list_create(switch_device_t device, switch_acl_type_t type);
    
/**
 Delete the ACL key list
 @param acl_handle handle of created ACL
*/
switch_status_t switch_api_acl_list_delete(switch_handle_t acl_handle);

/**
 Create ACL Rules
 @param acl_handle - Acl handle
 @param priority - priority of Acl
 @param key_value_count - key value pair count
 @param acl_kvp - pointer to multiple key value pair
 @param action - Acl action (permit/drop/redirect to cpu)
 @param action_params - optional action parameters
*/
switch_status_t switch_api_acl_rule_create(switch_handle_t acl_handle, unsigned int priority,
                                   unsigned int key_value_count, void *acl_kvp,
                                   switch_acl_action_t action, switch_acl_action_params_t *action_params);

/**
 Delete ACL Rules
 @param acl_handle - Acl handle
 @param priority - priority of acl rule
*/
switch_status_t switch_api_acl_rule_delete(switch_handle_t acl_handle, unsigned int priority);

/**
 Renumber ACL Rules
 @param acl_handle - Acl handle
 @param increment_priority - priority to reorder the acl rule
*/
switch_status_t switch_api_acl_renumber(switch_handle_t acl_handle, int increment_priority);

/**
 Apply ACLs on interfaces, VLANs, etc.
 @param acl_handle handle created with list_create
 @param interface_handle - Interface handle
*/ 
switch_status_t switch_api_acl_reference(switch_handle_t acl_handle, switch_handle_t interface_handle);

/**
 Apply ACLs on interfaces, VLANs, etc.
 @param acl_handle handle created with list_create
 @param interface_handle - Interface handle
*/ 
switch_status_t switch_api_acl_remove(switch_handle_t acl_handle, switch_handle_t interface_handle);

/** @} */ // end of ACL API

#ifdef __cplusplus
}
#endif

#endif
