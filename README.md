# Info
Package is provided by Loupe  
https://loupe.team  
info@loupe.team  
1-800-240-7042  

# Description
This repo provides packages that allow basic error logger functionality.

### Program Package
This program package will install the Diagnostics B&R package that will contain the ErrorProg program for a Automation Studio project and all its dependencies.  
The ErrorProgInit program will perform simple initialization of parameters if needed.
The ErrorProgCyclic program will call the a few critical function blocks from the ErrorLib library that manage the globally scoped error collector.

### Library Package
This library package allows access to the error collector function blocks.

# Installation
To install using the Loupe Package Manager (LPM), in an initialized Automation Studio project directory run `lpm install errorprog`. Note that this will also pull in the library package as a dependency.  
If you only want to install the library package, run `lpm install errorlib`.  
For more information about LPM, see https://loupeteam.github.io/LoupeDocs/tools/lpm.html.

# Documentation
For more documentation and examples, see https://loupeteam.github.io/LoupeDocs/libraries/errorlib.html (or you can run `lpm docs errorlib`).

# Licensing

This project is licensed under the [MIT License](LICENSE).