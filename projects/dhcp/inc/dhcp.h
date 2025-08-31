/************************************
 * Exercise: DHCP server
 * Date: 27/08/25
 * Developer: Baruch Haimson
 * Reviewer: Avi
 * Status: In Progress
 ************************************/

#ifndef __ILRD_DHCP_H__
#define __ILRD_DHCP_H__

#include <stddef.h> /* size_t */

#define BYTES_IN_IPV4 (4)

typedef struct dhcp dhcp_t;

typedef enum status
{
    SUCCESS,
    ALLOC_FAILURE,
    IP_OCCUPIED_ALLOCATED_ANOTHER,
    NO_IP_AVAILABLE,
    DOUBLE_FREE,
    IP_NOT_FOUND
} dhcp_status_e;

/* O(1) */
/* malloc for dhcp struct after that insert the three mask adn after that do create for the trie according the size of the subnet */
dhcp_t* DHCPCreate(const unsigned char netip[BYTES_IN_IPV4], size_t mask);

/* O(n) n= 2^mask */
void DHCPDestroy(dhcp_t* dhcp);

/* O(n) n= mask */
dhcp_status_e DHCPAllocateIP(dhcp_t* dhcp, unsigned char allocated_ip[BYTES_IN_IPV4], const unsigned char requested_ip[BYTES_IN_IPV4]);

/* O(n) n= mask */
dhcp_status_e DHCPFreeIP(dhcp_t* dhcp, const unsigned char ip[BYTES_IN_IPV4]);

/* O(1)? decide for yourself */
size_t DHCPCountFree(const dhcp_t* dhcp);

#endif /* __ILRD_DHCP_H__ */
