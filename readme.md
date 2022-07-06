main.c
    Shell continuosly runs in main.c
    Command should preferrably be below 1000 words

prompt.c
    Prints the prompt required

proc.c
    Processes the buffer string into commands and removes stray spaces
    Checks if & or | is present and seperates command string into atomic commands and processes differently if it is a bacckground process

echo.c
    Processes echo command

pwd.c
    Processes pwd command

dirdes.c
    Processes the ls command

change.c
    Processes the cd command and accepts maximum of 2 args

pinfo.c
    Processes the pinfo command

back.c
    Any background process and its status check is performed here

forward.c
    This file processes the command per pipe calling ex.c if implementation is not available

ex.c
    This file processes the non-implemented commands

bg.c
    Contains the execution of the bg process where the number given along with it is a relative one.

env.c
    Contains implementation of setenv and unsetenv

fg.c
    Contains implementation of fg proccess where the number given is a relative one.

kjob.c
    Contains implementation of kjob process.

overkill.c
    Contains implementation of overkill
    Overkill is also called at the quitting of shell

pinfo.c
    Provides process information given the process id or by default the shell

redirection.c
    Handles the redirection process. Redirection includes > >> < <<(NO Special Meaning taken as input) Any other is not accepted

    Only last file along with its redirection mode is applicable

updatehistory.c
    Updates history when the shell exits

hisdisplay.c
    Displays the recent commands.If the commands stored is less than the asked number,Appropriate error message is displayed. Assumed that there is no H.txt file in the 

NOTE: History works only if the directory of execution has write permissions

Some Helper Programs:
    linkedlist.c
        Helps in execution of the status of background processes
        Contains implementation of jobs process.The sequential number is generated on the spot to maintain sequentiality.That is modifying a process will change the number(Ctrl Z , kjob,kill).




