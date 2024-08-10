# PintOS
Operating System CT[656] Case Study Assignment IOE 

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



