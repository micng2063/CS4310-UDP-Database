# CS 4310: Project 2: Student Database with UDP
# Description:
- A simple database that stores student information (ID, Name, Score) on host server (Eros) and allows user to add entry, search for ID or score, delete entry, etc. on the client server (Zeus) . This program used UDP as the transfer protocol.
# Instruction:
1. [Transfer files to servers] scp client_udp.c server_udp.c [TXState ID]@eros.cs.txstate.edu:~\
2. [Enter Txstate Password]...
3. [Open a window on Eros] ssh [TXState ID]@eros.cs.txstate.edu
4. [Open a window on Zeus] ssh [TXState ID]@zeus.cs.txstate.edu
5. [Compile and run the following on Eros first]
gcc -o s server_udp.c
./s
6. [Combine and run the following on Zeus]
gcc -o c client_udp.c
./c eros.cs.txstate.edu

# README:
- Program is partially incomplete and does not include:
1. a function that read student information from text file.
2. a function that check whether input information is correct type (int, char)
3. a function that mallocate new size of struct object.

![Client program](http://url/to/img.png](https://i.imgur.com/Fku1Z76.png)
![Server program](http://url/to/img.png](https://i.imgur.com/ddNQ4iM.png)
