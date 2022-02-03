# Pair Efficiency Calculator
Code to calculate the pair efficiency from the train outputs of the ALICE Dielectron framework.
Input files are found in the `../input/mc` directory, the ouputs are then in `./output`.
The code utilises the `helper` and `rebinner` class from the PlottingFW. The output files are used as input for the analysis in the `PlottingFW`.

## Usage
Cmake and make can be used to produce an executable. The steering is done in a configuration file, which is parsed by the executable. The different configurrations are stored in the `configs` directory.
