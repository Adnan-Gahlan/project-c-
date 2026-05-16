#ifndef VALIDATION_H
#define VALIDATION_H

#include <cstring>

bool isValidUsername(const char username[])
{
    if (strlen(username) == 0)
        return false;

    for (int i = 0; username[i] != '\0'; i++)
    {
        if (!((username[i] >= 'A' && username[i] <= 'Z') ||
              (username[i] >= 'a' && username[i] <= 'z')))
            return false;
    }
    return true;
}
bool isValidPhone(const char phone[])
{
    if (strlen(phone) != 9)
        return false;

    if (!(strncmp(phone, "71", 2) == 0 ||
          strncmp(phone, "73", 2) == 0 ||
          strncmp(phone, "77", 2) == 0 ||
          strncmp(phone, "78", 2) == 0))
        return false;

    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
            return false;
    }

    return true;
}

#endif
