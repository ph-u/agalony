# Reproducible Agar Colony Count

## Camera + Coordinates = Count

This pipeline is automating the tedious step of **counting regular-sized units** on a 2D plane, such as counting microbial colonies on an agar plate.  By using **phone cameras** and **XY coordinates** of the photos, users can count thousands of colonies in a photo within minutes.  The counting result is also completely reproducible and justifiable.

## The Pipeline
![pipeline](https://raw.githubusercontent.com/ph-u/docManual/master/agalony/img/pipeline.png)

Details of each program component and (intermediate) outputs are documented in the [**MANUAL**](https://htmlpreview.github.io/?https://raw.githubusercontent.com/ph-u/docManual/master/agalony/manual/detailed_instruction.html?token=AMIZLGHZU4EYI4VQAC2LTDS7YDPOY) and there is an [**example**](https://htmlpreview.github.io/?https://raw.githubusercontent.com/ph-u/docManual/master/agalony/manual/example.html?token=AMIZLGCRNQONXJ4XXOAQDD27YDPWA) relating to this pipeline.

## Why should you use the pipeline?

1. Quick & accurate
    - The pipeline speed bottleneck is on translating the binary RGB in each pixel of a photo into a spreadsheet/csv (comma-separated value)
    - A 2.2MB photo can be translated into a 167MB csv **within two minutes**
    - Pixel-filtering steps take **less than a minute** to complete, and these steps **need very little RAM**
    - Pixel-filtering uses RGB data sampled from user-defined areas on the photo, so the filters are **independent from the programming language used** to translate the photos
0. Reproducible
    - Same photos, same criteria, same counting results
    - Because the result only depends on the XY-coordinates, the RGB data sample would not change as long as the **photo size kept constant**
0. Justifiable
    - RGB colour of filtered colonies **can be plotted and verified** by observation, so the colour ranges can be scientifically justified
    - Photos with complete documentation (i.e. data attributes, such as experimental conditions and type of organisms in the photo) can be challenged (hence falsifiable), **boosting confidence to well-conducted experiments**

## Computer language requirements
- *NIX shell environment
    - the built-in terminal app in MacOS/Linux
    - [Linux enumerators](https://www.ubuntupit.com/best-linux-emulators-for-windows-system/) in Windows
    - [Virtual Machines](https://www.digitaltrends.com/computing/best-virtual-machines/)
- C-gcc compiler >=4.2.1
- (option 1) [python](https://www.python.org/) (>=3.7.3)
    - package requirements are documented in `requirements.txt`
- (option 2) [R](https://www.r-project.org/) (>=2.10.0)
    - [imager](https://www.rdocumentation.org/packages/imager/versions/0.42.3)

## Setting up the pipeline

1. Go to the [Release](https://github.com/ph-u/agalony/releases) page of this repository and download any one zip file
0. Unzip the package and put it anywhere handy -- you probably need to use your mouse to pull the pipeline script (i.e. agalony.sh) to your terminal unless you've set up an alias
0. Run the following command in the terminal
```
bash /full/path/to/build.sh
```

## [Using](https://htmlpreview.github.io/?https://raw.githubusercontent.com/ph-u/docManual/master/agalony/manual/detailed_instruction.html?token=AMIZLGHZU4EYI4VQAC2LTDS7YDPOY) the pipeline
1. Put all photos in a single directory with a file `range.csv`
0. `range.csv` format: 15 columns
    - image name [column 1]
    - XY bounaries for the circular view of pixel collection [column 2-5: X1, Y1, X2, Y2]
    - XY boundaries for the 1st sample colony for RGB range construction [column 6-9]
    - XY boundaries for the 2nd sample colony for RGB range construction [column 10-13]
    - **H**orizontal or **P**ortrait photo [column 14: H/P]
    - "pixels to one colony" ratio [column 15: an integer, mostly >1]
0. `bash /full/path/to/agalony.sh [prc] [/full/path/of/photos] [nCPU]`
    - first option: quick pipeline selection
    - p = python3 image translation interpreter (option 1)
    - r = Rscript image translation interpreter (option 2)
    - c = clear intermediate csv files (optional)
    - Suggestion: use [p] or [r] only to save intermediate files for checking whether colour thresholds are correctly placed; final run use [pc] or [rc] to save disk space

An [**example**](https://htmlpreview.github.io/?https://raw.githubusercontent.com/ph-u/docManual/master/agalony/manual/example.html?token=AMIZLGCRNQONXJ4XXOAQDD27YDPWA) is also provided for a clearer illustration.

## **Warning**
Users should only put photos and one `range.csv` in the data folder before running this program, especially when using the "clear" (c) option to permanent delete intermediate files.  

It is the sole responsibility of users to ensure only the necessary input files are in the directory this program works on; this pipeline never process data outside the user-indicated photo directory.  

It is strongly suggested a subdirectory embedded within the usual data directory is used to contain all photos and a `range.csv` for this unit identification step.

## Uninstall / remove the pipeline
Delete the program directory (or folder).  This pipeline does not create other directories at any other locations in users' computers.

## Credits
Please provide a source to this repository (e.g. URL) in manuscripts to let others know how to reproduce your results.

## License
All source files in this repository are under Apache-2.0 License, the text of which can be found in the LICENSE file.

## Stylish Git-page
[https://ph-u.github.io/agalony/](https://ph-u.github.io/agalony/)

## Version History
1.0.0 - modify CLI, more efficient pipeline (C-script)  
0.0.1 - Initial release
