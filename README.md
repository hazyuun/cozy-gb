# Cozy Gameboy Emulator
![Tetris](logo.png)

>This project is just for fun, you you are looking for a GB emulator just to play games, this might not be what you are looking for, because there are many better GB emulators that are well tested and supporting all types of cartridges.

|![Link's Awakening](screenshots/TLoZ.gif)|![Super Mario Land](screenshots/SML.gif)|
|---|---|
|![Tetris](screenshots/TETRIS.gif)|![Blargg](screenshots/blargg.gif)|

## Getting started
### Dependencies
In order to compile, you will need :
* `glfw`
* `glew`
* `glm`
### Compiling
Make directories :
```bash
$ mkdir obj bin
```
and run the Makefile using :
```bash
$ make
```
### Playing
```bash
$ ./bin/cozy-gb path/to/the/rom
```


## TODO
- [ ] APU
- [ ] Timer
- [x] MBC1
- [ ] MBC2
- [ ] MBC3
- [ ] Debugger
- [ ] GUI


