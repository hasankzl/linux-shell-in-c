# linuxShellWithC
Linux Shell program with C


# Design overview

The program I have made is a shell program that can run linux terminal codes. The program can operate in 2 different modes, interactive and batch. It works by executing commands received from the user in interactive mode. If in batch mode reads the file given by the user and runs the commands that write in the file.

The execvp () function was used for the execution of commands. The first parameter of this function takes the command to be run and the second parameter takes the parameters of the command to be executed. This function also has a return value. If the function returns -1, it means that the command entered was not executed successfully. In this case, an error message is displayed to the user.

The fgets () function was used to read the commands entered by the user. Commands entered were split by semicolon character ";" using strtok () function . In this way, if the user entered more than one command on the same line, we were able to break these commands into parts.

The fopen () function was used to read the file the user wanted. The file was read by entering the user entered file as a parameter in this function. If the file does not exist, the function returns null. By checking this situation, it was possible to check whether the file entered by the user exists.



# Running the program

First you need the compile the code. For that I already create a makefile. You can simply type "make" and code will be compile.

![makefile](https://raw.githubusercontent.com/CoderSau/linuxShellWithC/main/images/make.PNG)

After that you can execute the file named "program"

![execute](https://raw.githubusercontent.com/CoderSau/linuxShellWithC/main/images/execute.PNG)


than you can type your commands. In the below example I've run 2 commands at the same time one is "ls" and other one is "ls -la".


![execute](https://raw.githubusercontent.com/CoderSau/linuxShellWithC/main/images/commands.PNG)

> stops when the application reads the "quit" command

> It is normal for application outputs to get mixed up since parallel operation


# Running the program in batch mode 

after you compile the code you can pass a text file and shell will runs the commands that write in the file.

In below example I have a text file named "test.txt" and this file includes this text


ls  ; ls -la

ls


when I try to run it I get this result

![execute](https://raw.githubusercontent.com/CoderSau/linuxShellWithC/main/images/bachmode.PNG)

> stops when the application reads the "quit" command

> It is normal for application outputs to get mixed up since parallel operation



# Quit the application
stops when the application reads the "quit" command or you can use "ctrl + c"

![quit1](https://raw.githubusercontent.com/CoderSau/linuxShellWithC/main/images/quit1.PNG)

![quit2](https://raw.githubusercontent.com/CoderSau/linuxShellWithC/main/images/quit2.PNG)



# references

I got help from this code while developing this application

https://gist.github.com/parse/966049
