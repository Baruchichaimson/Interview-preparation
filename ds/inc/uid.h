/***************************
 * Exercise: uid
 * Date:     20/07/25
 * Developer: Baruch Haimson
 * Reviewer: matan
 * Status:   Aproved
 ***************************/

#ifndef ILRD_UID_H
#define ILRD_UID_H

#include <time.h> /* time_t */
#include <sys/types.h> /* pid_t */

/*
 * A unique identifier structure composed of:
 * - counter: a unique incrementing counter
 * - timestamp: creation time (seconds since Epoch)
 * - pid: process ID (pid_t)
 * - ip: IP address of the machine (string up to 14 bytes including '\0')
 */
typedef struct uid
{
    size_t counter;
    time_t timestamp;
    pid_t pid;
    unsigned char ip[14];
} ilrd_uid_t;

/*
 * A constant global value representing an invalid UID (used in case of error).
 */
extern const ilrd_uid_t UIDbadUID;

/*
 * Creates a new unique UID containing:
 * - unique counter
 * - current timestamp
 * - current process ID
 * - machine IP address 
 * Returns: valid UID on success, UIDbadUID on failure ( IP not found).
 * Complexity: O(1)
 */
ilrd_uid_t UIDCreate(void);

/*
 * Compares two UIDs for full equality (counter, timestamp, pid, ip).
 * Returns: 1 if UIDs are identical, 0 otherwise.
 * Complexity: O(1)
 */
int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);

#endif /* ILRD_UID_H */





































