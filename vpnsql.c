#include "vpnsql.h"
#include<time.h>

int mysql_set_user(User_Config *user);
User_Pass * mysql_get_snyc();
User_Pass * delpass(User_Pass *head,User_Pass * pass);

void mysqlconnect()
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql = mysql_init(NULL);
    if (!mysql_real_connect(mysql, C_Vpntool.Mshost,
                            C_Vpntool.Msuser, C_Vpntool.Mspass, C_Vpntool.Msdb, C_Vpntool.Msport, NULL, 0))
    {
        fprintf(stderr, "'%s'\n", mysql_error(mysql));
		dbug("无法连接mysql\n");
        exit(1);
    }
    sprintf(buffer,"select * from server where ip='%s'", C_Vpntool.Ip);
    if (mysql_query(mysql, buffer)) exit(1);
    res = mysql_store_result(mysql);
    if((row = mysql_fetch_row(res)) == NULL)
    {
        sprintf(buffer,"insert into server (ip,sent,recv,online) values ('%s',0,0,0)", C_Vpntool.Ip);
        if (mysql_query(mysql, buffer)) exit(1);
    }
    mysql_free_result(res);
}

void mysql_user(User_Config *user)
{
    MYSQL_RES *res;
    MYSQL_ROW row;

    sprintf(buffer,"UPDATE openvpn set osent=0, orecv=0, online=0");
    if (mysql_query(mysql, buffer)) exit(1);

    sprintf(buffer,"update server_list set osent=0, orecv=0, online=0 where ip='%s'", C_Vpntool.Ip);
    if (mysql_query(mysql, buffer)) exit(1);
    while(user!=NULL)
    {
        mysql_set_user(user);
        user=user->next;
    }

    sprintf(buffer,"select * from server where ip='%s'", C_Vpntool.Ip);
    if (mysql_query(mysql, buffer)) exit(1);
	res = mysql_store_result(mysql);
	 if((row = mysql_fetch_row(res)) == NULL)
    {
        sprintf(buffer,"insert into server (ip,sent,recv,online) values ('%s',0,0,0)", C_Vpntool.Ip);
        if (mysql_query(mysql, buffer)) exit(1);
    }
	mysql_free_result(res);

	sprintf(buffer,"UPDATE server SET sent = (select sum(sent) from server_list where ip='%s') WHERE ip = '%s'", C_Vpntool.Ip, C_Vpntool.Ip);
    if (mysql_query(mysql, buffer)) exit(1);
    sprintf(buffer,"UPDATE server SET recv = (select sum(recv) from server_list where ip='%s') WHERE ip = '%s'", C_Vpntool.Ip, C_Vpntool.Ip);
    if (mysql_query(mysql, buffer)) exit(1);
    sprintf(buffer,"UPDATE server SET online=(select sum(online) from server_list where ip='%s') WHERE ip = '%s'", C_Vpntool.Ip, C_Vpntool.Ip);
    if (mysql_query(mysql, buffer)) exit(1);
	
}

int mysql_set_user(User_Config *user)
{
    MYSQL_RES *res1;
    MYSQL_RES *res2;
    MYSQL_ROW row1;
    MYSQL_ROW row2;
    sprintf(buffer,"select * from openvpn where iuser='%s'", user->name);
    if (mysql_query(mysql, buffer)) exit(1);
    res1 = mysql_store_result(mysql);
    if((row1 = mysql_fetch_row(res1)) == NULL)
    {
        cmd_UserStop(user->name);
        cmd_SessionDisconnect(user->Session);
        return (1);
    }


    sprintf(buffer,"select * from server_list where user='%s' and ip='%s'", user->name, C_Vpntool.Ip);
    if (mysql_query(mysql, buffer)) exit(1);
    res2 = mysql_store_result(mysql);
    if((row2 = mysql_fetch_row(res2)) == NULL)
    {
        cmd_UserDelete(user->name);
        cmd_UserCreate(user->name, row1[5]);
        sprintf(buffer,"insert into server_list (ip,user,sent,recv,osent,orecv,online) values ('%s','%s',0,0,0,0,0)", C_Vpntool.Ip, user->name);
        if (mysql_query(mysql, buffer)) exit(1);
    }
    sprintf(buffer,"update server_list set sent=%ld, recv=%ld, osent=osent+%ld, orecv=orecv+%ld, online=online+1 where ip='%s' and user='%s'", user->outgoing, user->incoming, user->Ooutgoing, user->Oincoming, C_Vpntool.Ip, user->name);
    if (mysql_query(mysql, buffer)) exit(1);

    sprintf(buffer,"UPDATE openvpn SET isent = (select sum(sent) from server_list where user='%s') WHERE iuser = '%s'", user->name, user->name);
    if (mysql_query(mysql, buffer)) exit(1);
    sprintf(buffer,"UPDATE openvpn SET irecv = (select sum(recv) from server_list where user='%s') WHERE iuser = '%s'", user->name, user->name);
    if (mysql_query(mysql, buffer)) exit(1);
    sprintf(buffer,"UPDATE openvpn SET online=(select sum(online) from server_list where user='%s') WHERE iuser = '%s'", user->name, user->name);
    if (mysql_query(mysql, buffer)) exit(1);
    sprintf(buffer,"UPDATE openvpn SET osent=(select sum(osent) from server_list where user='%s') WHERE iuser = '%s'", user->name, user->name);
    if (mysql_query(mysql, buffer)) exit(1);
    sprintf(buffer,"UPDATE openvpn SET orecv=(select sum(orecv) from server_list where user='%s') WHERE iuser = '%s'", user->name, user->name);
    if (mysql_query(mysql, buffer)) exit(1);
    mysql_free_result(res1);

    sprintf(buffer,"select * from openvpn where iuser='%s'", user->name);
    if (mysql_query(mysql, buffer)) exit(1);
    res1 = mysql_store_result(mysql);
    row1 = mysql_fetch_row(res1);
    time_t timep;
    time (&timep);
    if(stou(row1[2])+stou(row1[3])>=stou(row1[4])||stou(row1[6])==0||timep>stou(row1[8]))
    {
        cmd_UserStop(user->name);
        cmd_SessionDisconnect(user->Session);
        sprintf(buffer,"UPDATE openvpn SET i=0 where iuser='%s'", user->name);
        if (mysql_query(mysql, buffer)) exit(1);
    }

    mysql_free_result(res1);
    mysql_free_result(res2);
    return (0);
}

User_Pass * mysql_get_snyc()
{
    User_Pass *a, *b;
    MYSQL_RES *res;
    MYSQL_ROW row;
    time_t timep;
    time (&timep);
    a = (User_Pass *) malloc(sizeof(User_Pass));
    a->next = NULL;
    a->front = NULL;
    b = a;
    sprintf(buffer,"select * from openvpn");
    if (mysql_query(mysql, buffer)) exit(1);
    res = mysql_store_result(mysql);
	if(res->row_count == 0){
		mysql_free_result(res);
		free(a);
        a = NULL;
        b=NULL;
        return NULL;
	}
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        strcpy(b->name, row[1]);
        strcpy(b->pass, row[5]);
        b->access=atoi(row[6]);
	if(timep>stou(row[8]) && stou(row[6])==1 ){
		cmd_UserStop(b->name);
		sprintf(buffer,"UPDATE openvpn SET i=0 where iuser='%s'", b->name);
                if (mysql_query(mysql, buffer)) exit(1);
        }
        a = (User_Pass *) malloc(sizeof(User_Pass));
        a->next=b;
        a->front=NULL;
        b->front=a;
        b=a;
    }
    a=a->next;
    a->front=NULL;
    free(b);
    b = NULL;
    mysql_free_result(res);
    return a;
}

User_Pass * mysql_snyc(User_Pass * pass)
{
    User_Pass *a,*b,*c,*tmp;
    int x=0;
    a=mysql_get_snyc();
    c=a;
    b=pass;
    while(b!=NULL)
    {
        c=a;
        while(c!=NULL)
        {
            if(strcmp(b->name, c->name) == 0)
            {
                if(strcmp(b->pass, c->pass) != 0)
                {
                    sprintf(buffer, "sed -i \"s/^%s;.*$/%s;%s/g\" "Pass_path, c->name, c->name, c->pass);
                    system(buffer);
                    cmd_UserPasswordSet(b->name,c->pass);
                }

                if(b->access!=c->access)
                {
                    if(c->access == 1)
                    {
                        cmd_UserStart(b->name);
                    }
                    else
                    {
                        cmd_UserStop(b->name);
                    }
                }

                if(c->front==NULL)
                {
                    a=delpass(a, c);
                }
                else
                {
                    delpass(a,c);
                }

                x=1;
                break;
            }
            c=c->next;
        }

        if(x==1)
        {
            if(b->front==NULL)
            {
                x=0;
                pass=delpass(pass, b);
                b=pass;
                continue;
            }
            else
            {
                x=0;
                tmp=b->front;
                delpass(pass,b);
                b=tmp;
            }
        }

        b=b->next;
    }

    c=a;
    b=pass;
    while(b!=NULL)
    {
        sprintf(buffer,"sed -i \"/%s;/d\" "Pass_path, b->name);
        system(buffer);
        cmd_UserDelete(b->name);
        b=b->next;
    }
    while(c!=NULL)
    {
        sprintf(buffer, "echo \"%s;%s\" >> "Pass_path, c->name, c->pass);
        system(buffer);
        cmd_UserCreate(c->name, c->pass);
        c=c->next;
    }

    freelist(NULL, a);
    return pass;
}

User_Pass * delpass(User_Pass *head,User_Pass * pass)
{
    User_Pass *tmp;
    if(pass->front==NULL)
    {
        if(pass->next==NULL)
        {
            free(pass);
            pass=NULL;
            head=NULL;
        }
        else
        {
            tmp=pass;
            pass=pass->next;
            pass->front=NULL;
            head=pass;
            free(tmp);
        }
    }
    else
    {
        if(pass->next==NULL)
        {
            pass->front->next=NULL;
            free(pass);
        }
        else
        {
            pass->front->next=pass->next;
            pass->next->front=pass->front;
            free(pass);
        }
    }
    return head;
}
