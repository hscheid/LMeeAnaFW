## Configuration files for AddTasks

Summary of different configuration files to steer the AddTask.

### Data:

| **File**                                      | **comments**                                                                                          |
|:---------------------------------------------:|:-----------------------------------------------------------------------------------------------------:|
|Config_sscheid_lowmass_pPb_FAST_AOD_[1,2,3].C  | Produces 3d histos for ULS and LS and mixed events. Each contains 10 cut settings for the variation.  |

### Monte Carlo:
| **File**                                      | **comments**                                                                                          |
|:---------------------------------------------:|:-----------------------------------------------------------------------------------------------------:|
|Config_sscheid_efficiencyV2.C                  | Setup efficiency correction. Efficiency calculated as a function of pT and mass.                      |
|Config_sscheid_lowmass_pPb_FAST_AOD_MC[2].C    | Generate templates for defined MC signals. In addition templaets for phiV fits/efficiency corresction |
