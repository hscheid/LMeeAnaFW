# Makefile, das einzelne Dateien kompiliert und verlinkt (inkl der root-files)
# Wird eine Datei/Klasse ge�ndert m�ssen die anderen Dateien/Klassen nicht neu kompiliert werden

#    Wahl des Compilers
# CXX = clang++
 CXX = g++

#    DEBUG MODE
#    -Wall setzt (fast) alle Compilerwarnungen
#    -Werror setzt mehr Warnungen
#    -Wextra setzt noch mehr Warnungen
#    -ggdb erg�nzt debuginfos
 CXXFLAGS = -ggdb -Wall -Wextra -std=c++11 -I`root-config --incdir` -Og
# CXXFLAGS = -ggdb -Wall -Werror -Wextra -std=c++11 -stdlib=libc++ -I`root-config --incdir` -Og
# CXXFLAGS = -ggdb -Wall -Wextra -I`root-config --incdir` -Og
# use standard:
# CXXFLAGS = -ggdb -Wall -Wextra -I`root-config --incdir` -std=c++11
# CXXFLAGS = -ggdb -Wall -Wextra -std=c++14 -I`root-config --incdir`
# use optimization:
# CXXFLAGS = -O3 -Wall -Wextra -I`root-config --incdir`
#    RELEASE MODE
#    -O3 Gr��tm�gliche Optimierung; -O1 und -O2 sind kleinere Optimierungen; -Os optimiert Gr��e; -Og mit Debuginfos
# CXXFLAGS = -march=native -O3 -std=c++11 -I`root-config --incdir`


#    libraries die beim Linken eingesetzt werden
LDFLAGS = `root-config --libs` -lEG

# doesn't seem to work yet (carsten)
OBJDIR=obj
objects = $(addprefix $(OBJDIR)/, main.o LmManager.o LmBackground.o LmSignal.o LmHandler.o LmHelper.o)

#   $@ setzt hier das Namen des Targets ein
#   $^ setzt hier alle Prerequisites ein
#    $< setzt hier Name des ersten Prerequisite ein
#    -o dateiname setzt den Namen der zu erstellenden Datei
#    -c kompiliert aber linkt nicht
ana: ana.exe
carsten: carsten.exe
carsten_sys: carsten_sys.exe
carsten_phiV: carsten_phiV.exe
jerome: jerome.exe
jerome_sys: jerome_sys.exe
jerome_PbPb: jerome_PbPb.exe
nadia: nadia.exe
patrick: patrick.exe
pat_bg: pat_bg.exe
pat_sys: pat_sys.exe
sebastian: sebastian.exe
theo_pPb: theo_pPb.exe
theo_pp: theo_pp.exe
theo_Misc: theo_Misc.exe
theo: theo.exe


#Beispiel:
#zu_erstellende_datei(target): daf�r_gebrauchte_dateien(prerequisites)
#    g++ -o target -O3 -std=c++11 -I`root-config --incdir` prerequisites `root-config --libs` -lEG

# ana.exe: $(objects)
# 	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)

# $(OBJDIR)/%.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<

ana.exe: obj/main.o	            		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
carsten.exe: obj/carsten.o      		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
carsten_sys.exe: obj/carsten_sys.o  obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
carsten_phiV.exe: obj/carsten_phiV.o  obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
jerome.exe: obj/jerome.o        		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
jerome_sys.exe: obj/jerome_sys.o        		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
jerome_PbPb.exe: obj/jerome_PbPb.o        		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)



nadia.exe: obj/nadia.o        		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
patrick.exe: obj/patrick.o      		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
pat_bg.exe: obj/pat_bg.o        		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
pat_sys.exe: obj/pat_sys.o      		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
sebastian.exe: obj/sebastian.o  		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
theo_pPb.exe: obj/theo_pPb.o    		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
theo_pp.exe: obj/theo_pp.o      		obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
theo_Misc.exe: obj/theo_Misc.o obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)
theo.exe: obj/theo.o obj/LmManager.o obj/LmBackground.o obj/LmSignal.o obj/LmHandler.o obj/LmHelper.o obj/LmCocktailMan.o obj/LmCocktailPart.o obj/LmCocktail.o obj/LmBaseSignal.o obj/LmBaseManager.o obj/LmHistogram.o obj/LmFitter.o obj/LmFitFunctions.o obj/LmQA.o obj/LmMultiQA.o obj/LmFileManager.o obj/LmRebinner.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDFLAGS)

obj/main.o: src/user/main.cpp src/user/config.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/carsten.o: src/user/carsten.cpp src/user/carsten.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/carsten_sys.o: src/user/carsten_sys.cpp src/user/carsten_sys.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/carsten_phiV.o: src/user/carsten_phiV.cpp src/user/carsten_phiV.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/jerome.o: src/user/jerome.cpp src/user/jerome.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/jerome_sys.o: src/user/jerome_sys.cpp src/user/jerome.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/jerome_PbPb.o: src/user/jerome_PbPb.cpp src/user/jerome_PbPb.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/nadia.o: src/user/nadia.cpp src/user/nadia.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/patrick.o: src/user/patrick.cpp src/user/patrick.h src/user/patrick_common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/pat_bg.o: src/user/pat_bg.cpp src/user/pat_bg.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/pat_sys.o: src/user/pat_sys.cpp src/user/pat_sys.h src/user/patrick_common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/sebastian.o: src/user/sebastian.cpp src/user/sebastian.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/theo_pPb.o: src/user/theo_pPb.cpp src/user/theo_pPb.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/theo_pp.o: src/user/theo_pp.cpp src/user/theo_pp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/theo_Misc.o: src/user/theo_Misc.cpp src/user/theo_Misc.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
obj/theo.o: src/user/theo.cpp src/user/theo.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmManager.o: src/core/LmManager.cpp src/core/LmManager.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmBackground.o: src/core/LmBackground.cpp src/core/LmBackground.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmSignal.o: src/core/LmSignal.cpp src/core/LmSignal.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmHandler.o: src/core/LmHandler.cpp src/core/LmHandler.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmHelper.o: src/core/LmHelper.cpp src/core/LmHelper.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmCocktailMan.o: src/core/LmCocktailMan.cpp src/core/LmCocktailMan.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmCocktailPart.o: src/core/LmCocktailPart.cpp src/core/LmCocktailPart.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmCocktail.o: src/core/LmCocktail.cpp src/core/LmCocktail.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmBaseSignal.o: src/core/LmBaseSignal.cpp src/core/LmBaseSignal.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmBaseManager.o: src/core/LmBaseManager.cpp src/core/LmBaseManager.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmHistogram.o: src/core/LmHistogram.cpp src/core/LmHistogram.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmFitter.o: src/core/LmFitter.cpp src/core/LmFitter.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmFitFunctions.o: src/core/LmFitFunctions.cpp src/core/LmFitFunctions.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmQA.o: src/core/LmQA.cpp src/core/LmQA.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmMultiQA.o: src/core/LmMultiQA.cpp src/core/LmMultiQA.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmFileManager.o: src/core/LmFileManager.cpp src/core/LmFileManager.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/LmRebinner.o: src/core/LmRebinner.cpp src/core/LmRebinner.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

#L�schen der einzelnen Objekte
.PHONY: clean cleanpdf cleanest
clean:
	rm obj/*.o
cleanpdf:
	rm *.pdf
cleanest: clean
	rm *.exe
	rm *.pdf
