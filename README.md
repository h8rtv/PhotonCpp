


# PngToPhoton

Quick and dirty utility I've made to convert PNG files to Anycubic Photon 3d printer file format. It could be useful for PCB production. Source code was ported to C++ from [Photon File Validator](https://github.com/Photonsters/PhotonFileValidator) project.

# Usage

PngToPhoton.exe <input-1440x2560.png or directory> <output.photon> <layer_thickness?>

To read data from STDIN use '-' as filename.
"To read from a directory pass it in place of the input image.\n"
To write data from STDOUT use '-' as filename.
Default layer_thickness is 0.2 mm, if none is informed.

White and transparent areas of the image are treated as voids.
I insist on checking output with Photon File Validator after conversion. Use output at your own risk.

# Building

There is MSVC project for Windows and Makefile for Linux and MacOS X.
