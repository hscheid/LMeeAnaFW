# AnaLMeeFW

## Postprocessing and plotting framework for low-mass dielectron analysis in ALICE

### Plotting

Handels inputs from to dielectron lego trains and produces one dimensional plots.
[Plotting documentation](https://github.com/hscheid/LMeeAnaFW/tree/main/PlottingFW/README.md)

To build you need to
1. Enter the PlottingFW directory with `cd PlottingFW`
2. Create a build directory with `mkdir build`
3. Enter the directory with `cd build`  
4. **optional** load your `ROOT` environment (`alienv enter ROOT/latets` or similar)
5. Configure the makefile with `cmake ..`
6. Now you can build a user executable with `make TARGET` (these are specified in the `CMakeLists.txt`)

### Input Data
The (binary) input root files are not included in the repository. A list of input files can be summarised in a table: [Input files](https://github.com/hscheid/LMeeAnaFW/tree/main/input#input-data-and-mc-simulations-for-the-2016-p-pb-data-analysis)
