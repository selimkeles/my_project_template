# Task Scheduler Submodule

This submodule is created to use a task scheduler where you can execute or push forward functions using C language. Below is a brief description of the files and their purposes:

## Files and Descriptions

### trk_message.h
Defines the message types, process times, and structures used for message handling.

### trk_messageDefinitions.h
Contains the enumeration of different message types.

### trk_messageFunctions.h
Declares the message processing functions and the message functions array.

### trk_messageFunctions.c
Implements the message processing functions and initializes the message functions array.

### trk_message.c
Contains the core logic for handling messages, including pushing, stopping, and processing messages.

### ata_message.h
Declares the callback functions and the message stack overflow handler.

### ata_message.c
Implements the callback functions and the message stack overflow handler.

## Usage

To use the task scheduler, you need to call the following functions in your system:

```c
trk_Message(msg_1msTimer, NULL, msg_ProcessInstant);  // call this every 1ms in your system
trk_Message(msg_ProcessMessages, NULL, msg_ProcessForever);   // call this in main
```

These calls ensure that the task scheduler processes messages and executes the corresponding functions at the correct times.