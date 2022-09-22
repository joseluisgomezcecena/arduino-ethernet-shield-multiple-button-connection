# Arduino Button and Ethernet Shield

These scripts allow for multiple button presses at the same time, they also allow for buttons to be pressed for a long time and only detect one press until the button is released and pressed again.

It also shows how to connect to a server on button press and call a script.

## Installation

If your connection to a server is blocked change de MAC address located at the top of the script.

```c
//change this
byte mac[] = { 0xDE, 0xAD, 0xDB, 0xEF, 0xFE, 0xFD };
```

## License
[MIT](https://choosealicense.com/licenses/mit/)