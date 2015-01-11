#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    char buffer[64];
    char user_name[32];
    char access_token[64];
    int amount = 0;
    int new_amount = 0;

    strcpy(access_token, post_value(getenv("HTTP_COOKIE"), "access_token"));
    stringify_hex(access_token, user_name);

    if (check_user(user_name) == 0)
    {
        printf("Status: 404\n");
        headers();
        printf("User not into existing");
        return;
    }

    get_parameter("amount", buffer);
    sscanf(buffer, "%d", &amount);
    new_amount = get_balance(user_name) - amount;
    
    sprintf(buffer, "echo to: Withdrawal %d %d >> ../../db/user_%s", amount,
            new_amount, user_name);
    system(buffer);

    sprintf(buffer, "/cgi-bin/show/show-user?user_name=%s", user_name);
    redirect(buffer);
    headers();
    printf("amt %d",get_balance(user_name));
}
