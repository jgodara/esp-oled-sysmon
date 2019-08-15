# ESP8266 Oled Display System Monitor

A simple sketch that shows CPU and RAM on an OLED Display.
The sketch conntects to Flask server that exposes an API with the required details.

## Setting up

### Wiring

The OLED display is connected to the ESP8266 Module like this:

| Pin        | ESP8266           
| ------------- |:-------------|
| VCC/VIN      | `3v3` |
| SCL      | `D1`      |
| SDA | `D2`      |
| GND | `GND` |

### Running the Flask server

```shell
$ git clone https://github.com/jgodara/esp-oled-sysmon
$ cd esp-oled-sysmon
$ pipenv shell
$ pipenv install
$ python app.py
```

### Making changes to the sketch

You also want to make some changes in the sketch to make it connect to your WiFi and point it to the Flask server.
All you have to do is put in your WiFi credentials and the Hostname/Address of the server.

## TODOs

- Better code
- Documentation