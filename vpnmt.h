#include "vpntool.h"
#include "vpnother.h"
#include "vpncmd.h"
#include <unistd.h>

int Get_INI();
User_Config * U_olConfigGet();
User_Pass * Get_Ass();
void freelist(User_Config *list, User_Pass *pass);
