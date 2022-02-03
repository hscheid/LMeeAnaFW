# Pair Efficiency Calculator
Code to calculate the pair efficiency from the train outputs of the ALICE Dielectron framework.
Input files are found in the `../input/mc` directory, the ouputs are then in `./output`.
The code utilises the `helper` and `rebinner` class from the PlottingFW. The output files are used as input for the analysis in the `PlottingFW`.

## Usage
Cmake and make can be used to produce an executable. This is by default placed in the `build` directory, but can be copied wherever one wants it. The steering is done in a configuration file, which is parsed by the executable. The different configurations are stored in the `configs` directory. It is advised to abstain from the usage of relative paths.
̨The configuration file contains the information on the input file, the cocktail file used for weighting and can be given a binning for the mass and pair pt axis of the output histograms.
It should be made sure that the provided binning is compatible with the original binning of the input file.


The pair efficiency calculation can then be run simply by:
```
./calcEffi config.txt
```
