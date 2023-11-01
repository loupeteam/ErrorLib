# Info
Library is provided by Loupe  
https://loupe.team  
info@loupe.team  
1-800-240-7042  

# Description
The ErrorLib library collects all machine component errors into one location for easy display and acknowledgement of errors.

Error handling is an integral part of any system. It is often undervalued, though, since it does not directly add functionality. To make matters worse, there is often inconsistency in error handling at the component level, which makes error handling at the system level much more difficult and far less portable. The end result is longer development time.

The ErrorLib library was developed to solve these problems. It gathers errors from different machine components into one place, effectively solving the problem of system level error handling. It consolidates all of the pertinent error status information, such as the source of the error and the error text, and provides one point of access to acknowledge these errors.

The ErrorProg task contained in this repo is a wrapper that sets up the library and can be deployed for cyclic execution. 

# Usage 
The ErrorLib functionality can be integrated into any project using a couple of data structures and a few function calls.

For more documentation and examples, see https://loupeteam.github.io/LoupeDocs/libraries/errorlib.html

# Installation
To install the task and the library using the Loupe Package Manager (LPM), in an initialized Automation Studio project directory run `lpm install errorprogpkg`. If you only want to install the library and not the task, run `lpm install errorlib`. For more information about LPM, see https://loupeteam.github.io/LoupeDocs/tools/lpm.html

## Licensing

This project is licensed under the [MIT License](LICENSE).