# WinSmartisanKey
Apple Keyboard (model A1314 and A1644) Driver for Windows 10.

![keyboards](keyboards.png)

WinSmartisanKey enables the use of the **Apple Wireless Keyboard (A1314)** and the **Apple Magic Keyboard (A1644)**
under a native 64-bit **Windows 10** installation. No other drivers (such as Apple's Bootcamp) are needed.

Specifically: 
- Swaps the Fn-Ctrl keys to align with standard Windows keyboard layouts (not supported by Apple's Bootcamp driver).
- Maps the missing Windows keys such as the Del, Insert, Print Screen, Pause/Break, etc.
- Respects all the small details such as typematic properties of keys, something which was not possible with the older [WinA1314](https://github.com/samartzidis/WinA1314) driver.
- Includes an installer that automates the task of properly and cleanly installing or uninstalling the driver.

Only 64-bit versions of Windows 10 are currently supported. You may also be able to install the driver on Windows 7, 8 or 8.1 (64-bit) but this has not been tested.

### Technical Details
WinSmartisanKey is fully implemented as a HIDCLASS LowerFilter WDM kernel mode driver. 

![keyboard-driver-stack](keyboard-driver-stack.png)

Sitting inbetween HIDCLASS and the bluetooth HID Transport driver; allows the interpretation of the input data 
before they reach HIDCLASS and get split out into TLC interfaces as HID Hot Buttons or as KBDClass (normal keys) input. 
This allows full and proper re-mapping of all of the keys (incl. Fn, Eject), by also respecting typematic properties. 
The older WinA1314 driver was not capable of that as it was implemented using *Francisco Lopes*'s [Interception](http://www.oblita.com/interception.html) driver, which is an UpperLevel filter KBDClass class driver. As a completely kernel-mode based implementation, it is also more secure than WinA1314 as it does not expose any keyboard input data to user mode. It also only attaches to the targeted keyboard device leaving the rest of your keyboard devices unaffected.


### Installation
Due to the fact that the driver is signed with a self-signed test certificate, Windows will not allow the installation unless it is 
running in **TESTSIGNING** mode. 

Please make sure that you understand all the potential **[implications](https://msdn.microsoft.com/en-us/windows/hardware/drivers/install/the-testsigning-boot-configuration-option)** of running your system in TESTSIGNING mode as well as the fact that WinSmartisanKey is ***free software*** that you are willing to build and/or use completely ***at your own risk.***

To set Windows in TESTSIGNING mode you will need to issue the below command in an Administrative command prompt and then reboot. Note that switching to TESTSIGNING mode will fail with an error message if you are running Windows on UEFI BIOS, unless **Secure Boot** is turned off. In that case, you will need to reboot into your BIOS first and disable Secure Boot.

``` Bcdedit.exe -set TESTSIGNING ON ```

You can now run the latest Setup.msi installer release from [releases](https://github.com/samartzidis/WinSmartisanKey/releases).

To uninstall, run the uninstaller from the ```Control Panel``` ```Programs``` and then manually revert TESTSIGNING mode by issuing the following command (in an Administrative command prompt):

``` Bcdedit.exe -set TESTSIGNING OFF ```


### Key Mapppings

**WinSmartisanKey** creates the following key mappings:

  <table>
    <tr>
      <th>Input Physical Key(s)</th>
      <th>Output Logical Key</th>
    </tr>
    <tr>
      <td>Ctrl</td><td>Fn</td>
    </tr>
    <tr>
      <td>Fn</td><td>Left Ctrl</td>
    </tr>
    <tr>
      <td>Eject</td><td>Delete</td>
    </tr>
  </table>

  And then:

  <table>
    <tr>
      <th>Input Logical Key(s)</th>
      <th>Output Logical Key</th>
    </tr>
    <tr>
      <td>Fn + [F1-F12]</td><td>[F13-F24]</td>
    </tr>
    <tr>
      <td>Fn + Left Ctrl</td><td>Right Ctrl</td>
    </tr>
    <tr>
      <td>Fn + Enter</td><td>Insert</td>
    </tr>
    <tr>
      <td>Fn + P</td><td>Print Screen</td>
    </tr>
    <tr>
      <td>Fn + S</td><td>Scroll Lock</td>
    </tr>
    <tr>
      <td>Fn + B</td><td>Pause/Break</td>
    </tr>
    <tr>
      <td>Fn + Up</td><td>Page Up</td>
    </tr>
    <tr>
      <td>Fn + Down</td><td>Page Down</td>
    </tr>
    <tr>
      <td>Fn + Left</td><td>Home</td>
    </tr>
    <tr>
      <td>Fn + Right</td><td>End</td>
    </tr>
  </table>

### Driver Settings

You can use regedit.exe to optionally modify certain driver settings.

To enable/disable the **Alt-Cmd key swapping** edit the DWORD key value: **HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\WinSmartisanKey\SwapAltCmd**. The default value is 0 (off).

To enable/disable the **Fn-Ctrl key swapping** edit the DWORD key value:
**HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\WinSmartisanKey\SwapFnCtrl**. The default value is 1 (on).

After changing any of these values, you will need to disconnect/connect your associated Apple keyboard(s) to trigger a driver reload, or alternatively reboot your machine.

### Build Instructions

To build the driver you will need **Visual Studio 2017** along with an installation of the 
  **Windows 10 Driver Kit (WDK)**. For the installer project, you will additionally need to install the **[WiX toolset](http://wixtoolset.org/)** version v3.10.3
  or better. 


