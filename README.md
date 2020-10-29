# Reproducible Agar Colony Count

## Summary

Are you

- spending days counting colonies on agar plates;
- worrying your colony counts will be challenged by others?

Using this pipeline, you can let your computer count for you by using

- :iphone: **phone cameras** to capture your result agar plates under a high colour-contrast condition;
- :memo: a csv table showing your RGB colour threshold and pixels-to-colony ratio

## Why should you use the pipeline?

## OS requirements

## Computer Language & external packages requirements
- [python](https://www.python.org/) (>=3.7.3)
    - package requirements are documented in `requirements.txt`
- C-gcc compiler 4.2.1

## Setting up

## The Supervisor csv format
image name | R (px 1) | G (px 1) | B (px 1) | R (px 2) | G (px 2) | B (px 2) | ratio (optional)
--- | --- | --- | --- | --- | --- | --- | ---
example 1 | 0 | 0 | 0 | 255 | 255 | 255 |
example 2 | 77 | 196 | 213 | 30 | 200 | 213 | 12

1. The number columns and RGB sequences are fixed (except the optional one)
0. Image names must be the same as the corresponding filenames of the photo the rows represent
0. The colour scale of RGB is from **0 to 255**
0. RGB ranges are independent from one another; using one pixel for all three parameters is solely for **convenience** and **efficiency**

## Version History
Ver | Features
--- | ---
0.0.1 | Initial release

## License

All source files in this repository are under Apache-2.0 License, the text of which can be found in the LICENSE file.

## Credits
