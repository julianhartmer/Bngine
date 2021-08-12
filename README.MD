# :b:ngine

# Setup
This project comes with SDL2 development files. Building this project works out-of-the-box. To run the built executable, you need to add SDL runtime files to the path. You can do this by changing the debug environment:
1. In the top bar go to Project->Bngine Properties
2. In the new dialog, navigate to Debugging and change the environment variables by clicking on edit.
3. Add the line `PATH=lib\SDL2_image-2.0.5\lib\lib_x64;lib\SDL2-2.0.14\lib\lib_x64;%PATH%`