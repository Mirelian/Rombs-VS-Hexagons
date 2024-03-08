
![Screenshot 2024-03-08 171951](https://github.com/Mirelian/Rombs-VS-Hexagons/assets/64906131/1b2bcd63-9e73-4de7-b01b-17a8a5c005ef)

This project uses the gfx-framework.
```
git clone https://github.com/UPB-Graphics/gfx-framework
```

**Setup**:

1.  Open a command shell in the gfx-framework folder
2.  Run the following command:
```
cd src/lab_m1
git submodule add https://github.com/Mirelian/Rombs-VS-Hexagons
git submodule update --init --recursive
```
3.  Open the lab_list.h file in src/lab_m1 and add:
```
#include "lab_m1/Rombs-VS-Hexagons/Rombs VS Hexagons.h"
```
4.  Open the main.cpp file in src and change the 'world' object to:
```
World* world = new m1::R_VS_H;
```
5. Build and run the gfx-framewok folder with CMake
