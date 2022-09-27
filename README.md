# SSH_basic
```
SSH server basic setup, (for "password less" login) and strategic domotic home control.
                           
                                               o
                                              (^)
                                             -=H=- BISHOP
                                              ] [
                                             /___\
  
```
 * ( A not So crazy way, to take the hand on your wifi domain and any GPIOs via
 simple C or python programs. )
 * In that way your program can internally talk to your remote servers without 
 having to type password at each time.
 (that the added value of any hosted linux single board with embedded wifi.)
                                 (at my sens...)
 * allow for intance to possibly (from touch screen) with simple tinker python 
 interface remotely control any switchs, alarm, light ect with universal time referance, 
 auto boot up and internet update of the wlan status device...
 * this technic is an easy way of doing this without heavy new software skills 
 while keeping the full transparency for the end user. 
 so why closing eyes on this amazing possibility ? 
 !! C++ qt interface is the pro way to fix the graphic aspect !
```
                             The penguins take care of your home :)
                                            .-"""-.
                                           '       \
                                          |,.  ,-.  |
                                          |()L( ()| |
                                          |,'  `".| |
                                          |.___.',| `
                                         .j `--"' `  `.
                                        / '        '   \
                                       / /          `   `.
                                      / /            `    .
                                     / /              l   |
                                    . ,               |   |
                                    ,"`.             .|   |
                                  .'   ``.          | `..-'l
                                |       `.`,        |      `.
                                |         `.    __.j         )
                                |__        |--""___|      ,-'
                                   `"--...,+""""   `._,.-' mh
```
( A Raspberry pi or beagelboard are recommanded for regular security updates and aviability ... )
... linux is the dreamed platform for learning and tweaking everything without almost no secret for the developer ...
without this pure opensource philosophy, we are stuck in corporation, politic & dictat 

we have to pull this at our own avantage as community of user ! sharing controlling & teaching !

* So, get your yellow palm ready for a true soft start !
		       
***********************************************************************************
* Install open ssh if not allready installed:
```
$ sudo apt install openssh-server
```

* The first step is to make a public and private key (for encrypted link.)
```
$ sudo ssh-keygen -t rsa
```
" just enter blank text for "passphrase"
" then locate the path of the genrated key file: ( ~/.ssh in general )

* Step2 copy the key on the server:

on the server side type:
```
$ sudo systemctl enable ssh 
$ sudo systemctl start ssh 
$ ip addr 
```
and note the ssh server ip for wlan0... that your ip server

* On your client side:
```
$ sudo ssh-copy-id -i ~/.ssh/id_rsa username@ipserver
```
of couse replace your username and ipserver with your local server session characteristic...

* Then now you can simply login remotely on server with:
```
$ ssh username@ipserver 
```
no password are needed anymore for login via ssh from client

* If everything work well 
on **(server side !) you can now go in:
```
$ sudo vim /etc/ssh/sshd_config 
```
and add the two following text line instructions:

```
PubkeyAuthentication yes
PasswordAuthentication no
```
this will disable password login on the server via ssh login from client...
(the encrypted key will be used instead )

!!! So only encrypted link will work from now... !!!
(*** established by the ssh-copy-id command... ***)

"switch back to PasswordAuthentication yes if you want to reenable remote connection via 
password for eventualy adding other parrallel clients this allow to restart
the procedure on each new clients localy... by generating encrypted key with ( the above method ),
then link them with the ssh-copy-id command (for every singel one...)
and once all links are made lock the server again by switching 
PasswordAuthentication to "no" in ```/etc/ssh/sshd_config```

by the way the list of allowed keys by the server are stored in plane text 
at ~/.ssh on server side.

* Next type on terminal (always on serverside):
```
$ sudo systemctl restart ssh
```
( for refreshing the new list of host allowed on the server ).

Now you can code a simple program on the client side for controling gpio or anything remotly !
more on this in a moment... 

* For controling the server (on server side):
```
$ sudo systemctl disable ssh
```
( will not start up ssh server anymore, after reboot... )
```
$ sudo systemctl stop ssh
```
( will just stop for this session the server)
```
$ sudo systemctl enable ssh
```
(start the server)
```
$ sudo systemctl status ssh    
```
( for cheking actual status )

* For additional security mesures:

   * use a compiled and minimalist linux kernel.
   * "failtoban" and "ufw"/iptables setup is also recomanded.
	
* Remotely control the server:

  "the server restrict distant sudo command...
  and so, a password are claim from the server at each "super user domain" (sudo) commad
  for that we have to set the server to ask for superuser password only ONE time at the
  bigenning of the journey/session..."

* On server side type:
```
$ sudo visudo 
```
* Under the line starting %root or %admin type
your_user_name_session ALL=NOPASSWD: ALL

like this: (julien is my username)
```
%sudo   ALL=(ALL:ALL) ALL
julien ALL=NOPASSWD: ALL
```
F2 key for saving with nano ( be care full to don't make error before saving you can mess 
your login file, futher more a warning is triggered in case of error before save as protection ! 
read well the escape key for qiting without saving the instructions !

* Then loggout & login your session for update the server status.

* Now you have type your password only one time by session !!!

* Now for security purpose you have to log on server via $ ssh username@serverip 
once then type sudo apt update (or anything else in sudo only one time !) 
this allow the next comming sudo instructions to run properly without code,
but once it's done it's ok for all the day !!! ( it's like a bluetooth pairing )

* Now with a simple C line code like this:
```
system("ssh -t username@sshipserver touch ~/My_yellow_palm"); 
// Warning ! Your mind must be pure ! now you remotely control a computer !
```
you can do anything you want easly on your private home network with safety and encryption. 

*****************************************************************************************************
Is that things is for naive children ? certainly not ! but 
it's bound to the comunication domain with the whole security issue comming with ! 

I say that because often we see 8 years old childrens with raspberrypi on picture promotion. 
that fun and positive ! but a computer is open on internet and bad people may 
be every where even inside your smart wc !!! 
We have to be aware of that a soon as possible !   
-> what if the next notice will be on server socket through outside internet connection !
nothing bad except that involve penal responsabillity out of the scope of a children or 
young student... what if my 14 years hold girl have a webcam set and a full access on internet in her bed room ?
an education of the wild world must be done. and god know that's a delicate topic that we cannot avoid...
So every thing comme with fear in this digital and wild world... caution never harm !
******************************************************************************************************

* The following is a unix more advance way to run command in pure C:
from https://linuxhint.com/posix-spawn-c-programming/
```
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

extern char **environ;

void run_cmd(char *cmd)
{
    pid_t pid;
    char *argv[] = {"sh", "-c", cmd, NULL};
    int status;
    printf("Run command: %sn", cmd);
    status = posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);
    if (status == 0) {
        printf("Child pid: %in", pid);
        do {
          if (waitpid(pid, &status, 0) != -1) {
            printf("Child status %dn", WEXITSTATUS(status));
          } else {
            perror("waitpid");
            exit(1);
          }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    } else {
        printf("posix_spawn: %sn", strerror(status));
    }
}

void main(int argc, char* argv[])
{
    run_cmd(argv[1]);
    return;
}
```
******************************************************************************
