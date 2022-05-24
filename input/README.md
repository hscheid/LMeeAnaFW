Input data and MC simulations for the 2016 p-Pb data analysis
=============================================================

The different analysis inputs will be summarised with the respective trains that they were produced with. Lets
try to do some bookkeeping...

Data
----

The outputs can be found with the information in the table on the train website: [DQ_pPb_AOD](https://alimonitor.cern.ch/trains/train.jsp?train_id=117)

| **File**              | **Dataset** | **Reco Pass** | **Train number** | **comments**            | `path/to/file/`                   |
|:---------------------:|:-----------:|:-------------:|:----------------:|:-----------------------:|:---------------------------------:|
| LHC16q_pass2_cutVar_1 |   LHC16q    |     pass2     |       389        | 10/30 cuts (fast+woSDD) | ./data/LHC16q_pass2_cutVar_1.root |

MC
--

The outputs can be found with the information in the table on the train website: [DQ_pPbMC_AOD](https://alimonitor.cern.ch/trains/train.jsp?train_id=119)
Used for efficiency corrections pass1 analysis.
| **File**      | **Dataset** | **Reco Pass** | **Train number** | **comments**                                                             | `path/to/file/`                            |
|:-------------:|:-----------:|:-------------:|:----------------:|:------------------------------------------------------------------------:|:------------------------------------------:|
| LHC19h9_fast  |   LHC16q    |     pass1     |       656        |                 HF enhanced [JIRA][1]                                    |  `./mc/efficiecny/LHC19h9_fast_656.root`   |
| LHC19h9_woSDD |   LHC16q    |     pass1     |       660        |                 HF enhanced [JIRA][1]                                    |  `./mc/efficiency/LHC19h9_woSDD_660.root`  |
|    LHC18f3    |   LHC16q    |     pass1     |       659        |                 GP (fast+woSDD) [JIRA][5]                                |    `./mc/efficiency/LHC18f3_559.root`      |


Used for MC QA for pass2 anchored productions
| **File**      | **Dataset** | **Reco Pass** | **Train number** | **comments**                                                             | `path/to/file/`                |
|:-------------:|:-----------:|:-------------:|:----------------:|:------------------------------------------------------------------------:|:------------------------------:|
| LHC19h9_fast  |   LHC16q    |     pass1     |       643        |                 HF enhanced, no OOB rejection [JIRA][1]                  |  `./mc/mcQALHC19h9_fast.root`  |
|   LHC20f11c   |   LHC16q    |     pass2     |       642        |                GP (fast+woSDD), no OOB rejection [JIRA][1]               |   `./mc/mcQA/LHC20f11c.root`   |
|    LHC21b6    |   LHC16q    |     pass2     |       644        |              HF enhanced (10%), no OOB rejection [JIRA][3]               |    `./mc/mcQA/LHC21b6.root`    |
|   LHC21b6b    |   LHC16q    |     pass2     |       641        | HF enhanced (10% after fixing `galice.root`), no OOB rejection [JIRA][3] |   `./mc/mcQA/LHC21b6b.root`    |
| LHC21b6b_oob  |   LHC16q    |     pass2     |       649        |         HF enhanced (10% after fixing `galice.root`), [JIRA][3]          | `./mc/mcQA/LHC21b6b_oob.root`  |
|  LHC21b6_oob  |   LHC16q    |     pass2     |       653        |                       HF enhanced (10%) [JIRA][3]                        |  `./mc/mcQA/LHC21b6_oob.root`  |
| LHC20f11c_oob |   LHC16q    |     pass2     |       650        |                         GP (fast+woSDD) [JIRA][4]                        | `./mc/mcQA/LHC20f11c_oob.root` |
|    LHC18f3    |   LHC16q    |     pass1     |       654        |                        GP (fast+woSDD) [JIRA][5]                         |    `./mc/mcQA/LHC18f3.root`    |

<!-- Links to JIRA tickets of different productions -->
[1]: https://alice.its.cern.ch/jira/browse/ALIROOT-8648?jql=text%20~%20%22LHC19h9%22
[2]: https://alice.its.cern.ch/jira/browse/PWGPP-614?jql=text%20~%20%22LHC20f11c%22
[3]: https://alice.its.cern.ch/jira/browse/ALIROOT-8648?jql=text%20~%20%22LHC21b6%22
[4]: https://alice.its.cern.ch/jira/browse/PWGPP-614?jql=text%20~%20%22LHC20f11c%22
[5]: https://alice.its.cern.ch/jira/browse/ALIROOT-7792?jql=text%20~%20%22LHC18f3%22
