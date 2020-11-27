# Reproducible Agar Colony Count

## :camera: + :triangular_ruler: + :computer: = :bar_chart:  

This pipeline is automating the tedious step of **counting regular-sized units** on a 2D plane, such as counting microbial colonies on an agar plate.  By using **phone cameras** and **XY coordinates** of the photos, users can count thousands of colonies in a photo within minutes.  The counting result is also completely reproducible and justifiable.

## The Pipeline
![pipeline](/img/pipeline.png)

Details of each program component and (intermediate) outputs are documented in the [**MANUAL**](https://htmlpreview.github.io/?https://raw.githubusercontent.com/ph-u/agalony/master/manual/detailed_instruction.html?token=AMIZLGHZU4EYI4VQAC2LTDS7YDPOY) and there is an [**example**](https://htmlpreview.github.io/?https://raw.githubusercontent.com/ph-u/agalony/master/manual/example.html?token=AMIZLGCRNQONXJ4XXOAQDD27YDPWA) relating to this pipeline.

## Why should you use the pipeline?

1. Quick & accurate
    - The pipeline speed bottleneck is on translating the binary RGB in each pixel of a photo into a spreadsheet/csv (comma-separated value)
    - A 2.2MB photo can be translated into a 167MB csv **within two minutes**
    - Pixel-filtering steps take **less than a minute** to complete, and these steps **need very little RAM**
    - Pixel-filtering uses RGB data sampled from user-defined areas on the photo, so the filters are **independent from the programming language used** to translate the photos
0. Reproducible
    - Same photos :camera:, same criteria :triangular_ruler:, same counting result :bar_chart:
    - Because the result only depends on the XY-coordinates, the RGB data sample would not change as long as the **photo size kept constant**
0. Justifiable
    - RGB colour of filtered colonies **can be plotted and verified** by observation, so the colour ranges can be scientifically justified
    - Photos with complete documentation (i.e. data attributes, such as experimental conditions and type of organisms in the photo) can be challenged (hence falsifiable), **boosting confidence to well-conducted experiments**

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

## Uninstall / remove the pipeline
Delete the program directory (or folder).  This pipeline does not create other directories at any other locations in users' computers.

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
