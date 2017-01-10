#include "vpnother.h"

char *format(char *linedata)
{
    char *c;
    if( (c = strstr(linedata,"\r\n")) != NULL)
    {
        strcpy(c, "\0\0");
    }
    else if( (c=strchr(linedata, '\n') ) !=NULL || (c=strchr(linedata, '\r'))!=NULL )
    {
        *c='\0';
    }
    return linedata;
}

char *get_string(char *string, char c)
{
    char *ch;
    ch=strchr(string, c);
    return ch+1;
}

uint64_t stou(char *number)
{
    uint64_t sum = 0;
    int x;
    for (x = 0; x < strlen(number); x++)
    {
        if (number[x] >= '0' && number[x] <= '9')
            sum = sum * 10 + number[x] - '0';

    }

    return sum;
}

void logs(User_Config *list, User_Pass *pass)
{
    User_Config *a;
    User_Pass *b;
    printf("%d %d %s %s %s %s %s %s\n", C_Vpntool.Cycle, C_Vpntool.Msport, C_Vpntool.Mshost, C_Vpntool.Msuser, C_Vpntool.Mspass, C_Vpntool.Msdb, C_Vpntool.Sfhub, C_Vpntool.Sfpass);
    a=list;
    while(a!=NULL)
    {
        printf("%s %s %s %ld %ld %ld %ld %d %d %d\n", a->name, a->mode, a->Session, a->outgoing, a->incoming, a->Ooutgoing, a->Oincoming, a->up, a->down, a->logins);
        a=a->next;
    }
    b=pass;
    while(b!=NULL)
    {
        printf("%s\n%s\n%d\n", b->name, b->pass, b->access);
        b=b->next;
    }
}
