# PintOS
#### Operating System CT[656] Case Study Assignment IOE 

Developed at Stanford, PintOS is a straightforward operating system used for teaching-learning purposes. Mainstream Linux OS codes are complex, with  millions of lines of code of great complexity rendering them hard to study. PintOS kernel is only of about 10000 lines of code and provides a barebone OS for students to learn the basics of OS concepts and implement features and modules on their own.

# PintOS Installation Guide on WSL (Ubuntu) in Windows

This guide will walk you through the process of setting up PintOS on a Windows system using WSL (Windows Subsystem for Linux) with Ubuntu.

## Prerequisites

1. **Windows 10 or 11**: Make sure you are running at least Windows 10, version 2004 or higher, with the build number 19041 or higher.
2. **WSL (Windows Subsystem for Linux)**: Install WSL and set up an Ubuntu distribution.
   
## Step 1: Install WSL and Ubuntu

1. Open PowerShell as Administrator and run the following command to enable WSL:
    ```bash
    wsl --install
    ```

2. After installation, reboot your machine if prompted.

3. Set Ubuntu as your default distribution:
    ```bash
    wsl --set-default-version 2
    ```

4. Install Ubuntu from the Microsoft Store.

5. Launch Ubuntu from the Start Menu and complete the initial setup by creating a user account.

## Step 2: Install Necessary Dependencies

Once inside the Ubuntu terminal, run the following commands to install the required packages:

```bash
sudo apt update
sudo apt upgrade -y
sudo apt install -y git qemu gcc make gdb
```
Check if qemu is installed properly.
```bash
qemu-system-x86_64
```

## Step 3: Clone the PintOS Repository

Clone the PintOS repository to your local machine:

```sh
git clone https://github.com/abhishek5211/pintos.git
cd pintos
cp -r edited-pintos $HOME/pintos
```
Alternatively you can download zip file / clone the file in windows and copy to linux from windows folder. The linux file system is mounted on windows.
![image](https://github.com/user-attachments/assets/e46ba878-160c-4683-893a-331aa1c5aa95)
Copy the original-pintos folder from downloads and copy to the /home/[your-username] directory from Windows file explorer.
![image](https://github.com/user-attachments/assets/26f6edd6-80e0-453b-8b1b-f439def51dc2)

## Step 4: Setting up PintOS.

## Changes in src/utils 
Open the file pintos-gdb present in /home/[your-username]/pintos/src/utils and changed line number 4 to
GDBMACROS=../misc/gdb-macros
I have used gedit for the editing purpose. The line number can be set visible by going to preferences option.
![image](https://github.com/user-attachments/assets/2454c0dd-8d4e-4c36-806a-3e75a04c5b00)

Open the Makefile in the utils directory and replaced line number 5 by
LDLIBS = -lm
![image](https://github.com/user-attachments/assets/b3445ebf-c77c-4129-92cb-e6bebbc8182b)

Compile the utils folder
```bash
make
```

![image](https://github.com/user-attachments/assets/e3af20f5-a640-4b37-bc7d-c96f1ef47d1a)


## Changes in src/threads

Open the file Make.vars present in /home/[your-username]/pintos/src/threads and changed the last line to

SIMULATOR = –qemu

![image](https://github.com/user-attachments/assets/62a1560f-45a5-4004-87e4-a1c52035d8fe)

Compile the threads folder
```bash
make
```
The output should look like this. If there are errors, there's is issue with GDB compiler.
![image](https://github.com/user-attachments/assets/47408f69-e3c8-4a4c-a1f0-06dc6d5d03f4)

## Final Changes in src/utils and QEMU linking
Link qemu symbolic link
```bash
sudo ln -s /usr/bin/qemu-system-x86_64 /usr/bin/qemu
```


Open the file pintos present in the utils directory and change line number 103 to

$sim = “qemu” if !defined $sim;

![image](https://github.com/user-attachments/assets/f89d539a-1b2d-4881-bdee-30f4a079bda2)

Since you've compiled the threads the kernel and loader resides in pintos/src/threads/build location.
Change line number 259 to
my $name = find_file (“../threads/build/kernel.bin”);

![image](https://github.com/user-attachments/assets/dc1e8b73-3523-4eb1-8587-465b79512276)


Open the file Pintos.pm in the utils directory and change line number 362 to

$name = find_file (“../threads/build/loader.bin”) if !defined $name;

![image](https://github.com/user-attachments/assets/34d4c48a-98bf-42e0-9ba7-c5e0ada2b0f7)


In the same folder verify if pintos executes.
```bash
pintos run alarm-multiple
```
![image](https://github.com/user-attachments/assets/84d07803-e9d6-4cfd-8275-5748e1195aac)

If you've encountered this permission denied error. Congratulations you've to suffer more!!

```bash
sudo chmod +x pintos
```

![image](https://github.com/user-attachments/assets/e7f7c7fe-87af-4003-a23d-a073eb77e47f)

If this error occurs, the pintos file is malformed at the given line. change line 916 with

	if ($^V ge 5.8.0) {
![image](https://github.com/user-attachments/assets/6cd7b9d0-3eff-4e09-89b1-a8c21e30b657)

```bash
pintos run alarm-multiple
```
If you get a never-ending looping error, your pintOS is corrupted, time to get another OS. The current git or 
this https://github.com/WyldeCat/pintos-anon.git will certainly work.
![image](https://github.com/user-attachments/assets/8da558bc-6aa1-4bcd-be4f-8762e078d784)

At last export the path variable so you can call pintos from any directory. Add the following at the end of file.
```bash
sudo nano ~/.bashrc
```
export PATH=$HOME/pintos/src/utils:$PATH


## PintOS Added Changes
### Implementing a Wait Queue in PintOS
### Objective
Replace the existing busy-wait method with a wait queue. When a thread sleeps, it should enter the wait queue and later move to the ready queue to be executed after a specified time.

### Implementation
#### Data Structures:

ready_list: Manages threads that are ready to be executed.
sleeping_list: Manages threads that are sleeping.
Enqueue:

#### Function 
thread_sleep_until(int64_t ticks_end)
Purpose: Puts the thread to sleep until the specified ticks_end.

Process:
Saves the endTicks information (current time + sleep time ticks).
Enqueues the thread in sleeping_list.
Calls thread_block() to block the thread's execution.

Timer Sleep Function:
File: pintos/src/device/timer.c
Function: timer_sleep(int64_t ticks)
Process:
Disables interrupts.
Adds the current thread to the sleeping_list.
Sets the thread's endTicks.
Calls sema_down(&thread_current()->sleep_Sem) to put the thread to sleep.
Re-enables interrupts.

#### Dequeue:
File: timer_interrupt in timer.c
Purpose: Checks for threads that need to wake up on each timer tick.
Process:
The function thread_awake(int64_t current_tick) iterates through sleeping_list.
Threads with expired sleep times are removed from sleeping_list.
Woken threads are added back to ready_list using thread_unblock()

#### Result 
The product of the iteration count and sleep duration appears in non-descending order.
![image](https://github.com/user-attachments/assets/a8c97f98-62f5-4291-a3ab-6a6ea7ad671c)



