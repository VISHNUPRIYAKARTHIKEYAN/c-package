TOPIC:FILE SYNCHRONIZATION

It is implemented using C Programming in Linux Operating System

In TERMINAL 1:
cd /home/kali/Desktop/c1/
nano sync.c 
gcc sync.c -o sync 
mkdir sd 
mkdir dd  
cd /home/kali/Desktop/c1/sd/   
touch f1.txt 
echo "content">f1.txt 
touch f2.txt 
cd ..
./sync /home/kali/Desktop/c1/sd /home/kali/Desktop/c1/dd 

->after modification in terminal 2 it'll show like this:
File synchronization started. Press Ctrl+C to exit.
File changed. Performing synchronization...

In TERMINAL 2:
echo "Updated content" > f1.txt

In TERMINAL 3:
cd "/home/kali/Desktop/c1/dd" 
ls
->f1.txt  f2.txt
                



  
