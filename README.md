# Reproducible Agar Colony Count

## Summary
Are you
- spending days counting colonies on agar plates;
- worrying your colony counts will be challenged by others?

Using this pipeline, you can let your computer count for you by using
- :iphone: **phone cameras** to capture your result agar plates under a high colour-contrast condition;
- :memo: a csv table showing your RGB colour threshold and pixels-to-colony ratio

## Pipeline Overview
![pipeline](/img/pipeline.png)

## Why should you use the pipeline?

## Computer language requirements
Users can choose their pipeline out of the following two:
1. C & python3
0. C, R & shell

And respective language requirements are:
- C-gcc compiler 4.2.1
- [python](https://www.python.org/) (>=3.7.3)
    - package requirements are documented in `requirements.txt`
- [R](https://www.r-project.org/) (>=2.10.0)
    - [imager](https://www.rdocumentation.org/packages/imager/versions/0.42.3)
- *NIX shell environment
    - the built-in terminal app in MacOS/Linux
    - [Linux enumerators](https://www.ubuntupit.com/best-linux-emulators-for-windows-system/) in Windows
    - [Virtual Machines](https://www.digitaltrends.com/computing/best-virtual-machines/)

## Setting up the pipeline

## How to use it

## The Supervisor csv format
image name | R (px 1) | G (px 1) | B (px 1) | R (px 2) | G (px 2) | B (px 2) | ratio (optional)
--- | --- | --- | --- | --- | --- | --- | ---
example 1 | 0 | 0 | 0 | 255 | 255 | 255 |
example 2 | 77 | 196 | 213 | 30 | 200 | 213 | 12
1. The number columns and RGB sequences are fixed (except the optional one)
0. Image names must be the same as the corresponding filenames of the photo the rows represent
0. The colour scale of RGB is from **0 to 255**
0. RGB ranges are independent from one another; using one pixel for all three parameters is solely for **convenience** and **efficiency**

## Credits
Please provide a **URL to this repository** in manuscripts to let others know how to reproduce your results.

## License
All source files in this repository are under Apache-2.0 License, the text of which can be found in the LICENSE file.

## Version History
Ver | Features
--- | ---
0.0.1 | Initial release
