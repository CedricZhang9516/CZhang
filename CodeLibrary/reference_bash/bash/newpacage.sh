#Make a new package.
#The example is from RhopiAlg to PpbAlg.
#In use change Rhopi to former name, change Ppb to latest name.
#Change requirements in TestRelease.
#Type 'sh bianyi.sh'.
#By Dong Chao, modified by Long Yunfei.

rm -rf PpbAlg
cp  -r RhopiAlg PpbAlg &&
cd PpbAlg/ &&
rename Rhopi Ppb * &&
cd PpbAlg-00-00-*/  &&
rename Rhopi Ppb * &&
cd src/  &&
rename Rhopi Ppb *.cxx &&
sed -i 's/Rhopi/Ppb/g' *.cxx &&
cd components/  &&
rename Rhopi Ppb *.cxx &&
sed -i 's/Rhopi/Ppb/g' *.cxx &&
cd ../../Ppb*/  &&
rename Rhopi Ppb *.h &&
sed -i 's/Rhopi/Ppb/g' *.h  &&
cd ../cmt &&
sed -i 's/Rhopi/Ppb/g' requirements 
cd ../share &&
rename jobOptions_Rhopi jobOptions_Ppb * &&
sed -i 's/Rhopi/Ppb/g' jobOptions_Ppb.txt  &&
cd 

