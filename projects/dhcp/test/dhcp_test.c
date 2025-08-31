/**************************************
Exercise: DHCP
Date: 29/08/2025
Developer: Dana Chesner
Reviewer: 
Status: 
**************************************/

#include <stdio.h> /* printf */
#include <string.h> /* memcmp */

#include "dhcp.h" /* DHCPCreate */

#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RED "\033[1;31m"

static void TestCreateAndDestroy();
static void TestAllocateIP();
static void TestFreeIP();
static void TestCountFree();
static void TestFreeOfReservedAddress();

static void PrintValidity(size_t result, size_t expected, const char* test_name);

int main()
{
    TestCreateAndDestroy();
    
    TestAllocateIP();
    
    TestFreeIP();
       
    TestCountFree();

    TestFreeOfReservedAddress();

    return 0;
}

static void TestCreateAndDestroy()
{
    unsigned char netip[BYTES_IN_IPV4] = { 192, 168, 1, 0 };
    dhcp_t* dhcp = DHCPCreate(netip, 24);

    printf("TestCreateAndDestroy:\n");
    printf("---------------------\n");

    PrintValidity(NULL != dhcp, 1, "DHCPCreate should succeed");

    DHCPDestroy(dhcp);
    printf("DHCPDestroy (check with valgrind)\n");

    printf("\n");
}

static void TestAllocateIP()
{    
    unsigned char zero[BYTES_IN_IPV4] = { 0, 0, 0, 0 };
    unsigned char netip[BYTES_IN_IPV4] = { 10, 0, 0, 0 };
    unsigned char allocated[BYTES_IN_IPV4] = { 0 };
    unsigned char requested[BYTES_IN_IPV4] = { 10, 0, 0, 5 };
    dhcp_status_e status = SUCCESS;

    dhcp_t* dhcp = DHCPCreate(netip, 24);

    printf("TestAllocateIP:\n");
    printf("---------------\n");

    /* Request a specific IP */
    status = DHCPAllocateIP(dhcp, allocated, requested);
    PrintValidity(status, SUCCESS, "Allocate requested IP (10.0.0.5)");
    PrintValidity(0 == memcmp(allocated, requested, BYTES_IN_IPV4), 1, "Allocated matches requested");

    /* Request same IP again */
    status = DHCPAllocateIP(dhcp, allocated, requested);
    PrintValidity(status, IP_OCCUPIED_ALLOCATED_ANOTHER, "Reallocate same IP");
    PrintValidity(allocated[3], 6, "New allocated IP is 10.0.0.6");

    /* Automatic allocation */
    status = DHCPAllocateIP(dhcp, allocated, zero);
    PrintValidity(status, SUCCESS, "Automatic allocation (zero requested)");
    PrintValidity(allocated[3], 1, "Automatic allocation is 10.0.0.1");

    DHCPDestroy(dhcp);
    printf("\n");
}

static void TestFreeIP()
{
    unsigned char netip[BYTES_IN_IPV4] = { 172, 16, 0, 0 };
    unsigned char ip[BYTES_IN_IPV4] = { 172, 16, 0, 10 };
    unsigned char ip_not_in_range[BYTES_IN_IPV4] = { 172, 16, 1, 10 };
    unsigned char ip_not_allocated[BYTES_IN_IPV4] = { 172, 16, 0, 11 };
    unsigned char allocated[BYTES_IN_IPV4] = { 0 };
    dhcp_status_e status = SUCCESS;

    dhcp_t* dhcp = DHCPCreate(netip, 24);

    printf("TestFreeIP:\n");
    printf("-----------\n");

    DHCPAllocateIP(dhcp, allocated, ip);
    PrintValidity(0 == memcmp(allocated, ip, BYTES_IN_IPV4), 1, "Allocated requested IP");

    /* Valid free */
    status = DHCPFreeIP(dhcp, ip);
    PrintValidity(status, SUCCESS, "Free allocated IP");

    /* Free again */
    status = DHCPFreeIP(dhcp, ip);
    PrintValidity(status, DOUBLE_FREE, "Trying to free already freed IP");

    /* Free ip not in range */
    status = DHCPFreeIP(dhcp, ip_not_in_range);
    PrintValidity(status, IP_NOT_FOUND, "IP not found to free");

    /* Free ip that is not allocated */
    status = DHCPFreeIP(dhcp, ip_not_allocated);
    PrintValidity(status, DOUBLE_FREE, "IP not found to free");

    DHCPDestroy(dhcp);
    printf("\n");
}

static void TestCountFree()
{
    unsigned char netip[BYTES_IN_IPV4] = { 192, 168, 0, 0 };
    unsigned char ip_not_in_range[BYTES_IN_IPV4] = { 172, 16, 1, 10 };
    unsigned char ip1[BYTES_IN_IPV4] = { 192, 168, 0, 10 };
    unsigned char ip2[BYTES_IN_IPV4] = { 192, 168, 0, 8 };
    unsigned char ip3[BYTES_IN_IPV4] = { 192, 168, 0, 240 };
    unsigned char ip4[BYTES_IN_IPV4] = { 192, 168, 0, 100 };
    unsigned char allocated[BYTES_IN_IPV4] = { 0 };

    dhcp_t* dhcp = DHCPCreate(netip, 24);

    printf("TestCountFree:\n");
    printf("--------------\n");

    PrintValidity(DHCPCountFree(dhcp), 256 - 3, "Free count after create");

    DHCPAllocateIP(dhcp, allocated, ip1);
    PrintValidity(DHCPCountFree(dhcp), 256 - 3 - 1, "Free count after 1 allocation");

    /* Free ip not in range */
    DHCPFreeIP(dhcp, ip_not_in_range);
    PrintValidity(DHCPCountFree(dhcp), 256 - 3 - 1, "IP not found to free doesn't change the free count");

    /* Valid free */
    DHCPFreeIP(dhcp, allocated);
    PrintValidity(DHCPCountFree(dhcp), 256 - 3, "Free count should be as it started after valid free");

    /* Double free */
    DHCPFreeIP(dhcp, allocated);
    PrintValidity(DHCPCountFree(dhcp), 256 - 3, "Free count should be the same after attempting double free");

    DHCPAllocateIP(dhcp, allocated, ip2);
    DHCPAllocateIP(dhcp, allocated, ip3);
    DHCPAllocateIP(dhcp, allocated, ip4);
    PrintValidity(DHCPCountFree(dhcp), 256 - 3 - 3, "Free count after 4 allocations");

    DHCPDestroy(dhcp);
    printf("\n");
}

static void TestFreeOfReservedAddress()
{
    unsigned char netip[BYTES_IN_IPV4] = { 172, 16, 0, 0 };
    unsigned char ip[BYTES_IN_IPV4] = { 172, 16, 0, 254 };

    dhcp_t* dhcp = DHCPCreate(netip, 24);

    printf("TestFreeOfReservedAddress:\n");
    printf("--------------------------\n");

    printf("Should fail!!! It is testing assert:\n");

    /* Invalid free */
    DHCPFreeIP(dhcp, ip);

    printf("If you see this, it means you failed\n");

    DHCPDestroy(dhcp);
    printf("\n");
}

static void PrintValidity(size_t result, size_t expected, const char* test_name)
{
    if (result == expected)
    {
        printf(COLOR_GREEN "GOOD" COLOR_RESET " for: %s\n", test_name);
    }
    else
    {
        printf(COLOR_RED "BAD" COLOR_RESET " for: %s\n", test_name);
        printf("Expected: %lu, Got: %lu\n", expected, result);
    }
}
