#include "vpnmt.h"

int UserGet(User_Config *Cuser);
User_Config * SessionGet();
User_Pass * Get_Pass(User_Pass * p);
void fromSet_U();

int Get_INI()
{
    extern char buffer[BUFFER];
    extern struct vpn_tool C_Vpntool;
    FILE *vpn_ini;
    vpn_ini=fopen(VPN_INI, "r");
    if(vpn_ini == NULL) return -1;
    while (fgets(buffer, BUFFER, vpn_ini) != NULL)
    {
        if(buffer[0] != '#')
        {
            if (strstr(buffer, "Ip") != NULL)
            {
                strcpy(C_Vpntool.Ip, get_string(format(buffer),'='));
            }
            else if(strstr(buffer, "Cycle") != NULL)
            {
                C_Vpntool.Cycle=atoi(get_string(format(buffer),'='));
            }
            else if (strstr(buffer, "Mshost") != NULL)
            {
                strcpy(C_Vpntool.Mshost, get_string(format(buffer),'='));
            }
            else if(strstr(buffer, "Msport") != NULL)
            {
                C_Vpntool.Msport=atoi(get_string(format(buffer),'='));
            }
            else if(strstr(buffer, "Msuser") != NULL)
            {
                strcpy(C_Vpntool.Msuser, get_string(format(buffer),'='));
            }
            else if(strstr(buffer, "Mspass") != NULL)
            {
                strcpy(C_Vpntool.Mspass, get_string(format(buffer),'='));
            }
            else if(strstr(buffer, "Msdb") != NULL)
            {
                strcpy(C_Vpntool.Msdb, get_string(format(buffer),'='));
            }
            else if(strstr(buffer, "Sfhub") != NULL)
            {
                strcpy(C_Vpntool.Sfhub, get_string(format(buffer),'='));
            }
            else if(strstr(buffer, "Sfpass") != NULL)
            {
                strcpy(C_Vpntool.Sfpass,get_string(format(buffer),'='));
            }

        }
    }
    fclose(vpn_ini);
    return 0;
}

User_Config * U_olConfigGet()
{
    User_Config *user;
    if((user=SessionGet()) !=NULL)
    {
        User_Config *b;
        char s[40];
        b=user;
        while(b!=NULL)
        {
            UserGet(b);
            b=b->next;
        }
    }
    return user;
}

User_Pass * Get_Ass()
{
    if(access(Pass_path,0) < 0) return NULL;
    extern char buffer[BUFFER];
    extern struct vpn_tool C_Vpntool;
    FILE *con;
    User_Pass *a, *b;
    int line = 0;
    cmd_Flush();
    fromSet_U();
    a = (User_Pass *) malloc(sizeof(User_Pass));
    a->next = NULL;
    a->front =NULL;
    b = a;
    con = fopen(v_s_path2, "r");
    if (con == NULL)     return NULL;
    while (fgets(buffer, BUFFER, con) != NULL)
    {

        line++;
        if (line >= PLINE && (line - PLINE) % PC2 == 0 )
        {
            if (strstr(buffer, "declare") != NULL)
            {
                strcpy(b->name, get_string(format(buffer),' '));
            }
        }
        if (line-PC1 >= PLINE && (line-PC1 - PLINE) % PC2 == 0 )
        {
            if (strstr(buffer, "bool Access") != NULL)
            {
                if(strstr(buffer,"true") == 0)
                {

                    b->access=0;
                }
                else
                {
                    b->access=1;
                }
                a = (User_Pass *) malloc(sizeof(User_Pass));
                a->next=b;
                a->front=NULL;
                b->front=a;
                b=a;
            }
        }

    }
    fclose(con);
    if (a->next == NULL)
    {
        free(a);
        a = NULL;
        b=NULL;
        return a;
    }
    else
    {
        a=a->next;
        a->front=NULL;
        free(b);
        b = NULL;
    }
    Get_Pass(a);
    return a;
}

User_Pass * Get_Pass(User_Pass * p)
{
    FILE *con;
    User_Pass * b;
    con = fopen(Pass_path, "r");
    if (con == NULL)     return NULL;
    while(fgets(buffer,BUFFER, con) !=NULL)
    {
        char name[20];
        char pass[20];
        b=p;

        strcpy(pass, get_string(format(buffer),';'));

        *strchr(buffer,';')='\0';
        strcpy(name, buffer);

        while(b!=NULL)
        {
            if(strcmp(b->name, name) == 0)
            {
                strcpy(b->pass, pass);
                break;
            }
            b=b->next;
        }
    }
    fclose(con);
    return p;
}

User_Config * SessionGet()
{
    extern char buffer[BUFFER];
    extern struct vpn_tool C_Vpntool;
    FILE *con;
    User_Config *a, *b;
    int line = 0;
    cmd_SessionList();
    a = (User_Config *) malloc(sizeof(User_Config));
    a->next = NULL;
    b = a;
    con = fopen(SessionList_path, "r");
    if (con == NULL)
    {
        return NULL;
    }
    while (fgets(buffer, BUFFER, con) != NULL)
    {

        line++;
        if (line > LINE && (line - LINE) % C == 0)
        {
            if (strstr(buffer, "Session Name") != NULL)
            {
                strcpy(b->Session, get_string(format(buffer),'|'));

                a = (User_Config *) malloc(sizeof(User_Config));
                a->next=b;
                b=a;
            }
        }
    }
    fclose(con);
    if (a->next == NULL)
    {
        free(a);
        a = NULL;
        b=NULL;
    }
    else
    {
        a=a->next;
        free(b);
        b = NULL;
    }
    return a;
}

int UserGet(User_Config *Cuser)
{
    extern char buffer[BUFFER];
    FILE *User;
    int line = 0;
    cmd_SessionGet(Cuser->Session);
    User = fopen(SessionGet_path,"r");
    if(User == NULL) return -1;
    while (fgets(buffer, BUFFER, User) != NULL && line < LOGINS)
    {

        switch (++line)
        {
        case MODE:
            if(strcmp(get_string(format(buffer),'|'), "127.0.0.1") == 0)
            {
                strcpy(Cuser->mode, "TCP");
            }
            else
            {
                strcpy(Cuser->mode, "UDP");
            }
            break;
        case NAME:
            strcpy(Cuser->name, get_string(format(buffer),'|'));
            break;
        case OOUT:
            Cuser->Ooutgoing = stou(get_string(format(buffer),'|'));
            break;
        case OIN:
            Cuser->Oincoming = stou(get_string(format(buffer),'|'));
            break;
        }
    }
    fclose(User);
    cmd_Userget(Cuser->name);
    User = fopen(UserGet_path, "r");
    if (User == NULL)
        return -1;
    line = 0;
    while (fgets(buffer, BUFFER, User) != NULL && line < LOGINS)
    {

        switch (++line)
        {
        case OUT:
            Cuser->outgoing = stou(get_string(format(buffer),'|'));
            break;
        case OBT:
            Cuser->outgoing = Cuser->outgoing + stou(get_string(format(buffer),'|'));
            break;
        case IUT:
            Cuser->incoming = stou(get_string(format(buffer),'|'));
            break;
        case IBT:
            Cuser->incoming = Cuser->incoming + stou(get_string(format(buffer),'|'));
            break;
        case UP:
            Cuser->up = stou(get_string(format(buffer),'|'));
            break;
        case DOWN:
            Cuser->down = stou(get_string(format(buffer),'|'));
            break;
        case LOGINS:
            Cuser->logins = stou(get_string(format(buffer),'|'));
            break;
        }
    }
    fclose(User);
    return 0;
}

void freelist(User_Config *list, User_Pass *pass)
{
    User_Config *a;
    User_Pass *b;
    while(list !=NULL)
    {
        a=list;
        list=list->next;
        free(a);
    }
    while(pass !=NULL)
    {
        b=pass;
        pass=pass->next;
        free(b);
    }
}

void fromSet_U()
{
    char *s1="VirtualDhcpServer";
    FILE *fp1, *fp2;
    int a=0;
    char ch;
    fp2=fopen(v_s_path2"1","w");
    if((fp1=fopen(v_s_path1,"r")) != NULL)
    {
        while((ch=fgetc(fp1))!=EOF )
        {
            if(ch!='\t' && ch!='\r' &&ch!='{' && ch!='}')
            {
                fputc(ch,fp2);
            }
        }
    }
    fclose(fp1);
    fclose(fp2);
    fp1=fopen(v_s_path2"1","r");
    fp2=fopen(v_s_path2,"w");
    while (fgets(buffer,BUFFER,fp1) !=NULL)
    {
        if(strstr(buffer,s1) ) a=1;


        if(a==1)
        {
            fprintf(fp2,"%s",buffer);
        }
    }

    fclose(fp1);
    fclose(fp2);
    remove(v_s_path2"1");
}
