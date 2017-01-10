#include "vpncmd.h"

void cmd_Userget(char *user) {
    sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd UserGet %s > "Save"UserGet.config", C_Vpntool.Sfhub, user);
    system(buffer);
}

void cmd_SessionGet(char *session) {
    sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd SessionGet %s > "Save"SessionGet.config", C_Vpntool.Sfhub, session);
    system(buffer);
}

void cmd_SessionList() {
    sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd SessionList > "Save"SessionList.config", C_Vpntool.Sfhub);
    system(buffer);
}

void cmd_SessionDisconnect(char *ssession) {
    sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd SessionDisconnect %s", C_Vpntool.Sfhub, ssession);
    system(buffer);
}

void cmd_UserDelete(char *user) {
    sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd UserDelete %s", C_Vpntool.Sfhub, user);
    system(buffer);
}

void cmd_UserStop(char *user) {
    sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd UserPolicySet %s /NAME:Access /VALUE:no", C_Vpntool.Sfhub, user);
    system(buffer);
}

void cmd_UserStart(char *user) {
    sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd UserPolicySet %s /NAME:Access /VALUE:yes", C_Vpntool.Sfhub, user);
    system(buffer);
}

void cmd_UserCreate(char *user, char *pass) {
    sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd UserCreate %s /GROUP:none /REALNAME:none /NOTE:none", C_Vpntool.Sfhub, user);
    system(buffer);
sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd UserPasswordSet %s /PASSWORD:%s", C_Vpntool.Sfhub, user, pass);
    system(buffer);
sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd UserPolicySet %s /NAME:Access /VALUE:yes", C_Vpntool.Sfhub, user);
    system(buffer);
}

void cmd_MaxUpload(char *user, int up) {
sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd UserPolicySet %s /NAME:MaxUpload /VALUE:%d", C_Vpntool.Sfhub, user, up);
    system(buffer);
}

void cmd_MaxDownload(char *user, int down) {
sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd UserPolicySet %s /NAME:MaxDownload /VALUE:%d", C_Vpntool.Sfhub, user, down);
    system(buffer);
}

void cmd_Login(char *user, int logs) {
sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd UserPolicySet %s /NAME:MultiLogins /VALUE:%d", C_Vpntool.Sfhub, user, logs);
    system(buffer);
}

void cmd_UserPasswordSet(char *user, char *pass) {
sprintf(buffer, Vpncmd_path"vpncmd /server localhost /hub:%s /cmd UserPasswordSet %s /PASSWORD:%s", C_Vpntool.Sfhub, user, pass);
    system(buffer);
}

void cmd_Flush() {
sprintf(buffer, Vpncmd_path"vpncmd /server localhost /password:%s /adminhub:%s /cmd Flush", C_Vpntool.Sfpass, C_Vpntool.Sfhub);
    system(buffer);
}
