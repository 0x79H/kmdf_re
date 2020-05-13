# kmdf_re fork

This is a forked version of [kmdf_re](https://github.com/IOActive/kmdf_re).
This adds up to date definitions of `_WDFFUNCTIONS` as well as apply the correct type for the detected KMDFLibrary version. All WDF functions are typed, types have been extracted from [open source kmdf repository](https://github.com/Microsoft/Windows-Driver-Frameworks) by Microsoft

Credits : Enrique Nissim

Original readme below

# Reverse Engineering and Bug Hunting on KMDF Drivers

Link to slides: https://ioactive.com/wp-content/uploads/2018/09/Reverse_Engineering_and_Bug_Hunting_On_KMDF_Drivers.pdf

kmdf_re is a small idapython code that attempts to rename common structures and find usages of interesting kmdf callbacks.

Presentation given at AsiaSecWest 2018 (https://www.asiasecwest.com) and 44Con 2018 (https://44con.com/)

## Author
* [Enrique Nissim](https://twitter.com/kiqueNissim)