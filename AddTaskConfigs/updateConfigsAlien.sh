#!/bin/bash

#alien-token-init

aHOME="/alice/cern.ch/user/h/hscheid"                   # alien home directory
DIR="PWGDQ/dielectron/macrosLMEE/thesis"                # directory where to store the configs

LOCALDIR=`pwd`                                            # local workdir
#LOCALDIR="$ALICE_ROOT/$DIR/$CONFIG"                      # local workdir
# configs to upload

# colors
Cm="\033[35m"
Cy="\033[33m"
Cc="\033[36m"
Cb="\033[34m"
Cg="\033[32m"
Cr="\033[31m"
Cw="\033[37m"
Cz="\033[m"
Br="\033[41m"
By="\033[43m"

if [ $# -lt 1 ]; then
  CONFIGLIST=$(ls *".C")
else
  CONFIGLIST=$*
fi

echo -e "${Cm}files to upload:\n ${Cb}$CONFIGLIST${Cz}"
echo -e "${Cm}destination:\n $aHOME/$DIR ${Cz}"
####################

I=0
for CONFIG in $CONFIGLIST ; do

  if [ -f "$LOCALDIR/$CONFIG" ] ; then
    echo -e "${Cg}uploading file $I: ${Cb}$CONFIG${Cz}"
    alien.py rm ${aHOME}/${DIR}/${CONFIG}
	  #alien_cp -snt 50 file:"$LOCALDIR/$CONFIG" alien://"$aHOME/$DIR"@ALICE::CERN::Castor2
	  alien.py cp file:${LOCALDIR}/${CONFIG} alien://${aHOME}/${DIR}/${CONFIG} #removed @ALICE::CERN::Castor2 since it should not be used
    let I=I+1
  fi

done

echo -e "${Cg}files now present on alien:${Cz}"
alien.py ls ${aHOME}/${DIR}
