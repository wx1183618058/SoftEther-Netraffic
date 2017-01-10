#include "vpntool.h"

void cmd_Userget(char *user);
void cmd_SessionGet(char *session);
void cmd_SessionList();
void cmd_SessionDisconnect(char *ssession);
void cmd_UserDelete(char *user);
void cmd_UserStop(char *user);
void cmd_UserStart(char *user);
void cmd_UserCreate(char *user, char *pass);
void cmd_MaxUpload(char *user, int up);
void cmd_MaxDownload(char *user, int down);
void cmd_Login(char *user, int logs);
void cmd_UserPasswordSet(char *user, char *pass);
void cmd_Flush();
