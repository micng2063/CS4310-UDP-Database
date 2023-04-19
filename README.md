# CS 4310: Project 2: Student Database with UDP
# Description:
- A simple database that stores student information (ID, Name, Score) on host server (Eros) and allows user to add entry, search for ID or score, delete entry, etc. on the client server (Zeus) . This program used UDP as the transfer protocol.
# Instruction:
[Transfer files to servers] scp client_udp.c server_udp.c [TXState ID]@eros.cs.txstate.edu:~\
[Enter Txstate Password]...
[Open a window on Eros] ssh [TXState ID]@eros.cs.txstate.edu
[Open a window on Zeus] ssh [TXState ID]@zeus.cs.txstate.edu
[Compile and run the following on Eros first]
gcc -o s server_udp.c
./s
[Combine and run the following on Zeus]
gcc -o c client_udp.c
./c eros.cs.txstate.edu

#README: Program is partially incomplete and does not include:
- a function that read student information from text file.
- a function that check whether input information is correct type (int, char)
- a function that mallocate new size of struct object.

/***************Server program**************************/

/* server_udp.c is on eros.cs.txstate.edu
  open a window on eros.
  compile and run the server program first:
  $gcc -o s server_udp.c
  $./s
*/

/****************Client program********************************/

/* client_udp.c is on zeus.cs.txstate.edu
  open a window on zeus.
  compile:
  $gcc -o c client_udp.c
  $./c eros.cs.txstate.edu
*/
