## Input data and MC simulations for the 2016 p-Pb data analysis
The different analysis inputs will be summarised with the respective trains that they were produced with.
Lets
try to do some bookkeeping...

### Data
The outputs can be found with the information in the table on the train website: [DQ_pPb_AOD](https://alimonitor.cern.ch/trains/train.jsp?train_id=117)

|**File**| **Dataset** | **Reco Pass** | **Train number** | **comments** | `path/to/file/` |
| :----: | :---------: | :-----------: | :--------------: | :----------: |:--------------: |
|LHC16q_pass2_cutVar_1| LHC16q | pass2| 389 | 10/30 cuts (fast+woSDD) | `./data/LHC16q_pass2_cutVar_1.root`|

### MC
The outputs can be found with the information in the table on the train website: [DQ_pPbMC_AOD](https://alimonitor.cern.ch/trains/train.jsp?train_id=119)

|**File**| **Dataset** | **Reco Pass** | **Train number** | **comments** | `path/to/file/` |
| :----: | :---------: | :-----------: | :--------------: | :----------: |:--------------: |
| LHC19h9_fast | LHC16q | pass1 | 643 | HF enhanced MC [JIRA](https://alice.its.cern.ch/jira/browse/ALIROOT-8648?jql=text%20~%20%22LHC19h9%22) | `./mc/mcQALHC19h9_fast.root` |
| LHC20f11c    | LHC16q | pass2 | 642 | GP MC (fast+woSDD) [JIRA](https://alice.its.cern.ch/jira/browse/PWGPP-614?jql=text%20~%20%22LHC20f11c%22) | `./mc/mcQA/LHC20f11c.root` |
| LHC21b6      | LHC16q | pass2 | 644 | HF enhanced MC (10%) [JIRA](https://alice.its.cern.ch/jira/browse/ALIROOT-8648?jql=text%20~%20%22LHC21b6%22) | `./mc/mcQA/LHC21b6.root` |
| LHC21b6b     | LHC16q | pass2 | 641 | HF enhanced MC (10% after fixing `galice.root`) [JIRA](https://alice.its.cern.ch/jira/browse/ALIROOT-8648?jql=text%20~%20%22LHC21b6%22) | `./mc/mcQA/LHC21b6b.root` |
