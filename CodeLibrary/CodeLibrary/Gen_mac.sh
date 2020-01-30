#!/bin/bash

i=1

#427

while [ "$i" != "51" ]
do
    
    
    i=$(($i+1))
    
    touch ./0704_mac/musr_simple_0704_$i.mac
    echo " 


################################################################################################################
# -- ROTATION MATRICES --
################################################################################################################

# 3 parameters -> Define Euler angles (the 4th par. is set to zero).
# 4 parameters -> Define axis + rotation.
# HEP computations ordinarily use the active rotation viewpoint (object is rotated NOT axes). 
# Therefore, rotations about an axis imply ACTIVE COUNTER-CLOCKWISE rotation in this package.
# Rotation around a specified axis means counter-clockwise rot. around the positive direction of the axis.

# Define rotations for the field maps of Trigger and Ring Anode:
/musr/command rotation rotU   0  0  1  180
/musr/command rotation rotD   0  0  1    0
/musr/command rotation rotR   0  0  1   90
/musr/command rotation rotL   0  0  1  -90
/musr/command rotation rotMB  0  1  0   45
/musr/command rotation rot90  0  1  0   90
/musr/command rotation rotm90  0  1  0   -90
/musr/command rotation rotm45  0  1  0   -45
/musr/command rotation rot45  0  1  0   45
/musr/command rotation rot180 0  1  0  180
/musr/command rotation rotEB  1  0  0   90
/musr/command rotation rotEBe 0 90 90
/musr/command rotation rotEB2  0 90 180
/musr/command rotation rotEBe2 0 -90 -90

/musr/command rotation rotEB3  0 1 0 180
################################################################################################################
# -- BEAMLINE GEOMETRY --
################################################################################################################

# WORLD = Laboratory reference frame, the origin is in the centre of the MCH top flange
/musr/command construct box World  1100  300  2000 G4_Galactic 0 0 0 no_logical_volume norot dead -1

# MINIMUM WORD HALF LENGTH 1250 mm!
#/musr/command construct box World 2000 2000 4000 G4_Galactic 0 0 0 no_logical_volume norot dead -1

# World visual attributes (optional)
#/musr/command visattributes log_World lightblue


#==============================================================================================================
# MAIN CHAMBER                       Rmin Rmax  D/2                      x0 y0 z0
#==============================================================================================================
/musr/command construct tubs MCH    199.2 203.2 260.0 0 360 Steel         780 0 -744   log_World  norot dead 100
/musr/command construct tubs MCHvac   0   199.2 243.0 0 360 G4_Galactic   780 0 -744   log_World  norot dead 101

#removed 20160607 rkita
#/musr/command construct tubs FLvac    0    98.6  20.5 0 360 G4_Galactic   780 0 -480.5 log_World  norot dead 102

#generate at /gun/vertex  780. 0. -845. mm

#relative coordinate #forward 1mm
#/musr/command construct box  gen      100  100.0   0.1         G4_Galactic   0 0  -100.  log_MCHvac norot musr/ScintSD 990

#Real target 20160607 rkita
#/musr/command construct box  gen      100  100.0   0.1         G4_Galactic   0 0  -108.  log_MCHvac norot musr/ScintSD 990

#original
#change 20160607 rkita
#/musr/command construct box  gen      100  100.0   0.1         G4_Galactic   780 0  -845.  log_World norot musr/ScintSD 998
#/musr/command construct box  savegen      100  100.0   0.1         G4_Galactic   780 0  -845.  log_World norot musr/ScintSD 970

#change 20160607 rkita
#/musr/command construct box  SOAexit  100  100.0   0.1         G4_Galactic   780 0  -460.  log_World norot musr/ScintSD 991 
#/musr/command construct box  saveSOAexit  100  100.0   0.1         G4_Galactic   780 0  -460.  log_World norot musr/ScintSD 971 

/musr/command construct tubs  saveGen  0   40    0.1 0 360 G4_Galactic   0     0  -100   log_MCHvac norot  musr/ScintSD 900

#==============================================================================================================
# SOA LENS
#==============================================================================================================
 #mod 20170820 Grid
/musr/command construct tubs Grid    40    87     1 0 360 Steel           0 0  -92   log_MCHvac norot dead 110
/musr/command construct tubs SOAp1   38    87    19 0 360 Steel           0 0  -56   log_MCHvac norot dead 111
/musr/command construct tubs SOAp2   70    74    98 0 360 Steel           0 0   71   log_MCHvac norot dead 112   
/musr/command construct tubs SOAp3   38    87     1 0 360 Steel           0 0  180   log_MCHvac norot dead 113

/musr/command construct tubs  saveSOA00 0   38    0.1 0 360 G4_Galactic    0     0    -73   log_MCHvac  norot  musr/ScintSD 701
/musr/command construct tubs  saveSOA01 0   38    0.1 0 360 G4_Galactic    0     0    -70   log_MCHvac  norot  musr/ScintSD 702
/musr/command construct tubs  saveSOA02 0   38    0.1 0 360 G4_Galactic    0     0    -67   log_MCHvac  norot  musr/ScintSD 703
/musr/command construct tubs  saveSOA03 0   38    0.1 0 360 G4_Galactic    0     0    -47   log_MCHvac  norot  musr/ScintSD 704
/musr/command construct tubs  saveSOA04 0   38    0.1 0 360 G4_Galactic    0     0    -50   log_MCHvac  norot  musr/ScintSD 705

/musr/command construct tubs  saveSOA10 0   38    0.1 0 360 G4_Galactic    0     0    -45   log_MCHvac  norot  musr/ScintSD 711
/musr/command construct tubs  saveSOA11 0   38    0.1 0 360 G4_Galactic    0     0    -40   log_MCHvac  norot  musr/ScintSD 712
/musr/command construct tubs  saveSOA12 0   38    0.1 0 360 G4_Galactic    0     0    -30   log_MCHvac  norot  musr/ScintSD 713
/musr/command construct tubs  saveSOA13 0   38    0.1 0 360 G4_Galactic    0     0    -25   log_MCHvac  norot  musr/ScintSD 714



/musr/command construct tubs  saveSOA05 0   70    0.1 0 360 G4_Galactic   0     0    -20   log_MCHvac  norot  musr/ScintSD 706
/musr/command construct tubs  saveSOA06 0   70    0.1 0 360 G4_Galactic   0     0    0   log_MCHvac  norot  musr/ScintSD 707
/musr/command construct tubs  saveSOA07 0   70    0.1 0 360 G4_Galactic   0     0    20   log_MCHvac  norot  musr/ScintSD 708
/musr/command construct tubs  saveSOA08 0   70    0.1 0 360 G4_Galactic   0     0    40   log_MCHvac  norot  musr/ScintSD 709
/musr/command construct tubs  saveSOA09 0   70    0.1 0 360 G4_Galactic   0     0    60   log_MCHvac  norot  musr/ScintSD 710


/musr/command construct tubs  saveSOA1 0   38    0.1 0 360 G4_Galactic   0     0   -57   log_MCHvac norot  musr/ScintSD 901
/musr/command construct tubs  saveSOA2 0   74    0.1 0 360 G4_Galactic   0     0    71   log_MCHvac norot  musr/ScintSD 902
/musr/command construct tubs  saveSOA3 0   87    0.1 0 360 G4_Galactic   0     0   180   log_MCHvac norot  musr/ScintSD 903
/musr/command construct tubs  saveSOAe 0   40    0.1 0 360 G4_Galactic   780.0 0  -460   log_World  norot  musr/ScintSD 904

#================================================================================================================
#  Spacer 1
#================================================================================================================
#/musr/command construct tubs SP1       80   82  222.5 0 360 Steel        780 0  -237.5 log_World   norot dead 120
#/musr/command construct tubs SP1vac     0   80  222.5 0 360 G4_Galactic  780 0  -237.5 log_World   norot dead 121

#================================================================================================================
#  GV1
#================================================================================================================
#removed 20160608rkita
#/musr/command construct tubs GV1     0    80  40 0 360 G4_Galactic       780 0    -197.5   log_World norot dead 130

#================================================================================================================
#  collimator after SOA
#================================================================================================================
#/musr/command construct tubs GV1     0    80  40 0 360 G4_Galactic       780 0    -197.5   log_World norot dead 130

###/musr/command construct tubs  Col     5   200    5 0 360 Steel         780   0.0   -387   log_World norot dead 130
#/musr/command construct tubs  Col      10   80    3 0 360 Steel         780   0.0   -387   log_World norot dead 130


#/musr/command construct tubs  Col     2   80    3 0 360 Steel         780   0.0   -387   log_World norot dead 130
#/musr/command construct cons  Col     10 100 10 100  10    0 360 Steel         780   0.0   -387   log_World norot dead 130
#mod 20170820 saveCol
/musr/command construct tubs  saveCol 0   80    0.1 0 360 G4_Galactic   780   0.0   -380   log_World norot  musr/ScintSD 905

#================================================================================================================
#  Q1    cylpart: Rmin Rmax Length/2 height
#================================================================================================================

#/musr/command construct tubs    Q1ch   0   101.6  80  0 360 Steel         780   0.0   -117.5   log_World norot dead 140
#mod 20170820  Q1ch
/musr/command construct tubs    Q1ch   0   101.6  80  0 360 Steel         780   0.0   -160   log_World norot dead 140
/musr/command construct tubs    Q1vac  0    98.6  80  0 360 G4_Galactic     0   0.0      0   log_Q1ch  norot dead 141
/musr/command construct cylpart Q1R    0    45.6  40 20     Steel       -85.6   0.0      0   log_Q1vac rotR  dead 142
/musr/command construct cylpart Q1L    0    45.6  40 20     Steel        85.6   0.0      0   log_Q1vac rotL  dead 143
/musr/command construct cylpart Q1D    0    45.6  40 20     Steel           0 -85.6      0   log_Q1vac rotD  dead 144
/musr/command construct cylpart Q1U    0    45.6  40 20     Steel           0  85.6      0   log_Q1vac rotU  dead 145
/musr/command construct tubs  saveQ1 0   101    0.1 0 360 G4_Galactic   0   0.0   -80   log_Q1ch norot  musr/ScintSD 906

#================================================================================================================
#  Q2    cylpart: Rmin Rmax Length/2 height
#================================================================================================================
#/musr/command construct tubs    Q2ch   0   101.6  80  0 360 Steel         780   0.0     35   log_World norot dead 160
#/musr/command construct tubs    Q2ch   0   101.6  80  0 360 Steel         780   0.0    -85   log_World norot dead 160
#/musr/command construct tubs    Q2ch   0   101.6  80  0 360 Steel         780   0.0    43   log_World norot dead 160
#mod 20170820 Q2ch saveQ2 saveQe2

/musr/command construct tubs    Q2ch   0   101.6  79  0 360 Steel         780   0.0    0   log_World norot dead 160
/musr/command construct tubs    Q2vac  0    98.6  79  0 360 G4_Galactic     0   0.0      0   log_Q2ch  norot dead 161
/musr/command construct cylpart Q2R    0    45.6  40 20     Steel       -85.6   0.0      0   log_Q2vac rotR  dead 162
/musr/command construct cylpart Q2L    0    45.6  40 20     Steel        85.6   0.0      0   log_Q2vac rotL  dead 163
/musr/command construct cylpart Q2D    0    45.6  40 20     Steel           0 -85.6      0   log_Q2vac rotD  dead 164
/musr/command construct cylpart Q2U    0    45.6  40 20     Steel           0  85.6      0   log_Q2vac rotU  dead 165
/musr/command construct tubs  saveQ2  0   88    0.1 0 360 G4_Galactic   780   0   -80   log_World norot  musr/ScintSD 907
/musr/command construct tubs  saveQe2 0   101   0.1 0 360 G4_Galactic   780   0 80      log_World norot  musr/ScintSD 908


#================================================================================================================
#  Electric Deflector
#================================================================================================================
#field origin is x-114.75 relative to beam axis and 445.25 relative to front face of input flange. Here 780-114.75 = 665.25

#mod 20170820 EB EBplus EB minus saveBendIn saveBendOut
#/musr/command construct box  EB         20   10  1          G4_Galactic   580 0  420   log_World rotEB2  dead 190
#/musr/command construct box  EB         20   10  3          G4_Galactic   580 0  420   log_World rotEB2  dead 190
/musr/command construct box  EB         20   10  3          G4_Galactic   580 0  420   log_World rotEB3  dead 190
/musr/command construct tubs EBplus    450  457 80   0  90  Steel         380 0  220   log_World rotEBe2 dead 192
/musr/command construct tubs EBminus   343  350 80   0  90  Steel         380 0  220   log_World rotEBe2 dead 193
/musr/command construct tubs saveBendIn  0  100  0.1 0 360  G4_Galactic   780 0  160   log_World norot   musr/ScintSD 909

/musr/command construct tubs saveBendOut0 0  100  0.1 0 360  G4_Galactic   700 0  420   log_World rot45   musr/ScintSD 800
/musr/command construct tubs saveBendOut1 0  100  0.1 0 360  G4_Galactic   650 0  470   log_World rot45   musr/ScintSD 801
/musr/command construct tubs saveBendOut2 0  100  0.1 0 360  G4_Galactic   600 0  520   log_World rot45   musr/ScintSD 802

/musr/command construct tubs  saveBendOut3  0   101    0.1 0 360 G4_Galactic   450   0.0   620   log_World rot90  musr/ScintSD 910
/musr/command construct tubs  saveBendOut4  0   101    0.1 0 360 G4_Galactic   390   0.0   620   log_World rot90  musr/ScintSD 911

#================================================================================================================
#  Q3    cylpart: Rmin Rmax Length/2 height
#================================================================================================================

#mod 20170820 Q3ch saveQ3
/musr/command construct tubs Q3ch      0   101.6  79 0 360 Steel        240.0      0.0  620   log_World rot90 dead 180
/musr/command construct tubs Q3vac     0    98.6  79 0 360 G4_Galactic    0.0      0.0    0   log_Q3ch  norot  dead 181
/musr/command construct cylpart Q3R    0    45.6  40 20    Steel        -85.6      0.0    0   log_Q3vac rotR  dead 182
/musr/command construct cylpart Q3L    0    45.6  40 20    Steel         85.6      0.0    0   log_Q3vac rotL  dead 183
/musr/command construct cylpart Q3D    0    45.6  40 20    Steel          0.0    -85.6    0   log_Q3vac rotD  dead 184
/musr/command construct cylpart Q3U    0    45.6  40 20    Steel          0.0     85.6    0   log_Q3vac rotU  dead 185

/musr/command construct tubs  saveQ3  0   101    0.1 0 360 G4_Galactic   320   0.0   620   log_World rot90  musr/ScintSD 912


#================================================================================================================
#  Q4    cylpart: Rmin Rmax Length/2 height
#================================================================================================================
#mod 20170820 Q4ch saveQ4 saveQe4
/musr/command construct tubs Q4ch      0   101.6  79 0 360 Steel          80      0.0  620   log_World rot90 dead 200
/musr/command construct tubs Q4vac     0    98.6  79 0 360 G4_Galactic    0.0      0.0    0   log_Q4ch  norot  dead 201
/musr/command construct cylpart Q4R    0    45.6  40 20    Steel        -85.6      0.0    0   log_Q4vac rotR  dead 202
/musr/command construct cylpart Q4L    0    45.6  40 20    Steel         85.6      0.0    0   log_Q4vac rotL  dead 203
/musr/command construct cylpart Q4D    0    45.6  40 20    Steel          0.0    -85.6    0   log_Q4vac rotD  dead 204
/musr/command construct cylpart Q4U    0    45.6  40 20    Steel          0.0     85.6    0   log_Q4vac rotU  dead 205
/musr/command construct tubs  saveQ4  0   101    0.1 0 360 G4_Galactic   160   0.0   620   log_World rot90  musr/ScintSD 913
/musr/command construct tubs  saveQe4  0   101    0.1 0 360 G4_Galactic    0   0.0   620   log_World rot90  musr/ScintSD 914


#================================================================================================================
#  MB
#================================================================================================================
#mod 20170820 MB MB_ApBody1 MB_ApBody2 saveMBin saveMBout Shield saveQ5in
/musr/command construct box  MB           5.0  1   20        G4_Galactic    -402.28 0  693.72    log_World      rotMB dead 150

/musr/command construct box  MB_cham1 292.5 42.5 2      Steel	    -317.5 0  577.5   log_World      norot dead  155
/musr/command construct box  MB_cham2 100 42.5 2        Steel	    -125 0  662.5   log_World      norot dead  156
/musr/command construct box  MB_cham3 2 42.5 101.25     Steel	    -432.5 0  971.25   log_World      norot dead  157
/musr/command construct box  MB_cham4 2 42.5 205      Steel	    -517.5 0  867.5   log_World      norot dead  158
/musr/command construct box  MB_cham5 46.25 42.5 2      Steel	    -563.75 0  662.5   log_World      norot dead  159
/musr/command construct box  MB_cham6 2 42.5 146.72      Steel	    -328.75 0  766.25   log_World      rot45 dead  130
/musr/command construct box  MB_top1 292.5 2 42.5      Steel	    -317.5 42.5  620   log_World      norot dead  131
/musr/command construct box  MB_top2 42.5 2 205      Steel	    -475 42.5  867.5   log_World      norot dead  132
/musr/command construct box  MB_top3 103.75 2 103.75      Steel	    -328.75 42.5  766.25   log_World      norot dead  133
/musr/command construct box  MB_bottom1 292.5 2 42.5      Steel	    -317.5 -42.5  620   log_World      norot dead  134
/musr/command construct box  MB_bottom2 42.5 2 205      Steel	    -475 -42.5  867.5   log_World      norot dead  135
/musr/command construct box  MB_bottom3 103.75 2 103.75      Steel	    -328.75 -42.5  766.25   log_World      norot dead  136

#/musr/command construct tubs  saveMBin   0   101    0.1 0 360 G4_Galactic   -167 0  636   log_World rot90  musr/ScintSD 914

/musr/command construct tubs  saveMBin0   0   101    0.1 0 360 G4_Galactic   -100 0  620   log_World rot90  musr/ScintSD 915

/musr/command construct tubs  saveMBin1   0   101    0.1 0 360 G4_Galactic   -200 0  620   log_World rot90  musr/ScintSD 916
/musr/command construct tubs  saveMBin2   0   120    0.1 0 360 G4_Galactic   -375 0  750   log_World rot45  musr/ScintSD 917

#/musr/command construct tubs  saveMBin3   0   101    0.1 0 360 G4_Galactic   -400 0  770   log_World rot45  musr/ScintSD 817

/musr/command construct tubs  saveMBout0  0   101    0.1 0 360 G4_Galactic   -475 0  897.5   log_World norot  musr/ScintSD 1018
/musr/command construct tubs  saveMBout1  0   101    0.1 0 360 G4_Galactic   -475 0  977.5   log_World norot  musr/ScintSD 1019

/musr/command construct tubs  saveMBout  0   101    0.1 0 360 G4_Galactic   -475 0  1097.5   log_World norot  musr/ScintSD 918

/musr/command construct tubs  SNUDetCham       74.7    76.2    67.5 0 360  Steel    -771.2        0  620   log_World rot90 dead 930
/musr/command construct tubs  saveStMCP       0    70    0.1 0 360  G4_Galactic    -766.7        0  620   log_World rot90 musr/ScintSD 931

/musr/command construct tubs    Shield  50  70  45 0 360 Steel      -475   0.0      1167.5   log_World  norot dead 195
#/musr/command construct tubs    saveQ5in    0   101    0.1 0 360 G4_Galactic    -475 0  1237.5   log_World norot  musr/ScintSD 916

#================================================================================================================
#  Q5    cylpart: Rmin Rmax Length/2 height
#================================================================================================================
#mod 20170820 Q5ch saveQ5out saveBPM BPM
/musr/command construct tubs Q5ch      0   101.6  80 0 360 Steel       -475.0      0.0  1317.5   log_World norot dead 170
/musr/command construct tubs Q5vac     0    98.6  80 0 360 G4_Galactic    0.0      0.0    0   log_Q5ch  norot  dead 171
/musr/command construct cylpart Q5R    0    45.6  40 20    Steel        -85.6      0.0    0   log_Q5vac rotR  dead 172
/musr/command construct cylpart Q5L    0    45.6  40 20    Steel         85.6      0.0    0   log_Q5vac rotL  dead 173
/musr/command construct cylpart Q5D    0    45.6  40 20    Steel          0.0    -85.6    0   log_Q5vac rotD  dead 174
/musr/command construct cylpart Q5U    0    45.6  40 20    Steel          0.0     85.6    0   log_Q5vac rotU  dead 175

/musr/command construct tubs    saveQ5in   0   101    0.1 0 360 G4_Galactic    -475 0  1237.5   log_World norot  musr/ScintSD 1020

/musr/command construct tubs    saveQ5out    0   101    0.1 0 360 G4_Galactic    -475 0  1397.5   log_World norot  musr/ScintSD 919

#/musr/command construct tubs  saveMCP  0   101    0.1 0 360 G4_Galactic   -373   0.0   636   log_World rot90  musr/ScintSD 916
#/musr/command construct box  MCPreal   100  100.0   1      G4_Galactic   -375 0  636  log_World rot90 musr/ScintSD 979

/musr/command construct tubs  KEKDetCham       75    76.5    160 0 360  Steel    -475        0  1582.5   log_World norot dead 922
#/musr/command construct box  KEKDet           1   1   1	     G4_Galactic       -475 0    1582.5    log_World norot dead 929
/musr/command construct box  savePosCounter1  5  75 100	     G4_Galactic       -577 0    1582.5    log_World norot musr/ScintSD 923
/musr/command construct box  savePosCounter2  5  75 100	     G4_Galactic       -599 0    1582.5    log_World norot musr/ScintSD 924
/musr/command construct box  savePosCounter3  75  5 100	     G4_Galactic        -475 102    1582.5    log_World norot musr/ScintSD 925
/musr/command construct box  savePosCounter4  75  5 100	     G4_Galactic        -475 124    1582.5    log_World norot musr/ScintSD 926
/musr/command construct box  savePosCounter5  5  75 100	     G4_Galactic        -373 0   1582.5    log_World norot musr/ScintSD 927
/musr/command construct box  savePosCounter6  5  75 100	     G4_Galactic        -351 0   1582.5    log_World norot musr/ScintSD 928

/musr/command construct tubs  saveBPM       0    150    0.1 0 360  G4_Galactic    -475        0  1660.5   log_World norot musr/ScintSD 920
/musr/command construct tubs  BPM       0    70    1 0 360  Steel    -475        0  1663.2   log_World norot musr/ScintSD 921


#==================================================================================================================
#    Applying fields
#===================================================================================================================
#change 2.2425 (20keV) -> 0.769
#sector_field.map is generated with I~17.6

#2016A setup
#modified by rkita 20170629
#mod 20170820

/musr/command globalfield SOA_field  780.0 0 -708.0  fromfile 3DE SOA_20000_0000_0000_0000.txt log_MCHvac 1
/musr/command globalfield SOA_field  780.0 0 -708.0  fromfile 3DE SOA_0000_20000_0000_0000.txt log_MCHvac 0.947
#/musr/command globalfield SOA_field  780.0 0 -708.0  fromfile 3DE SOA_0000_20000_0000_0000.txt log_MCHvac 0.9972
/musr/command globalfield SOA_field  780.0 0 -708.0  fromfile 3DE SOA_0000_0000_20000_0000.txt log_MCHvac 0.902
/musr/command globalfield SOA_field  780.0 0 -708.0  fromfile 3DE SOA_0000_0000_0000_20000.txt log_MCHvac 0.8

/musr/command globalfield Q1_field   780 0  -144   fromfile 3DE Q1_3D_map.map   log_Q1vac     0

/musr/command globalfield Q2_field   780 0   16      fromfile 3DE Q1_3D_map.map   log_Q2vac    0.56
#/musr/command globalfield Q2_field   780 0   16      fromfile 3DE Q1_3D_map.map   log_Q2vac    0.0

/musr/command globalfield Q3_field   240 0   636.0   fromfile 3DE Q1_3D_map.map   log_Q3vac    -1.088
#/musr/command globalfield Q3_field   240 0   636.0   fromfile 3DE Q1_3D_map.map   log_Q3vac    0


/musr/command globalfield Q4_field    80 0   636.0   fromfile 3DE Q1_3D_map.map   log_Q4vac    1.056
#/musr/command globalfield Q4_field    80 0   636.0   fromfile 3DE Q1_3D_map.map   log_Q4vac    0.0

#/musr/command globalfield EB_field   580 0   420   fromfile 3DE EB_fieldmap.map log_EB       5.00
/musr/command globalfield EB_field   580 0   420   fromfile 3DE test7.map log_EB       235.00
#/musr/command globalfield EB_field   580 3   420   fromfile 3DE EB_fieldmap.map log_EB       5.00

# actual I=16.3A at longrun 2016A 
/musr/command globalfield MB_field  -402.28  0  693.72       fromfile 3DB sector_field.map log_MB   -0.926

#by cedric
#/musr/command globalfield Q5_field   -423.0 0  1330.5  fromfile 3DE Q1_3D_map.map  log_Q5vac    -1
/musr/command globalfield Q5_field   -475.0 0  1330.5  fromfile 3DE Q1_3D_map.map  log_Q5vac   0 


#EQ plus, Horizontal:Focus, Vertical: Defocus??, 170109
#if applying 0.4kV to EQ, the number should be 0.4 x 2 x 0.5/0.625



# Set parameters for particle tracking in an EM field
/musr/command globalfield setparameter SetLargestAcceptableStep 0.5
/musr/command globalfield setparameter SetMinimumEpsilonStep 5e-5
/musr/command globalfield setparameter SetMaximumEpsilonStep 0.001
/musr/command globalfield setparameter SetDeltaOneStep 0.1
/musr/command globalfield setparameter SetDeltaIntersection 0.01
/musr/command globalfield printparameters
/musr/command globalfield printFieldValueAtPoint  780 0 166
/musr/command globalfield printFieldValueAtPoint  780 0 156
/musr/command globalfield printFieldValueAtPoint  780 0 146
/musr/command globalfield printFieldValueAtPoint  780 0 136
/musr/command globalfield printFieldValueAtPoint  780 0 126
/musr/command globalfield printFieldValueAtPoint  780 0 116
/musr/command globalfield printFieldValueAtPoint  780 0 106
/musr/command globalfield printFieldValueAtPoint  780 0 96
/musr/command globalfield printFieldValueAtPoint  780 0 86
/musr/command globalfield printFieldValueAtPoint  780 0 76
/musr/command globalfield printFieldValueAtPoint  780 0 66
/musr/command globalfield printFieldValueAtPoint  780 0 56
/musr/command globalfield printFieldValueAtPoint  780 0 46
/musr/command globalfield printFieldValueAtPoint  780 0 36
/musr/command globalfield printFieldValueAtPoint  780 0 26
/musr/command globalfield printFieldValueAtPoint  780 0 16
/musr/command globalfield printFieldValueAtPoint  780 0 6
/musr/command globalfield printFieldValueAtPoint  780 0 -4
/musr/command globalfield printFieldValueAtPoint  780 0 -14
/musr/command globalfield printFieldValueAtPoint  780 0 -24
/musr/command globalfield printFieldValueAtPoint  780 0 -34
/musr/command globalfield printFieldValueAtPoint  780 0 -44
/musr/command globalfield printFieldValueAtPoint  780 0 -54
/musr/command globalfield printFieldValueAtPoint  780 0 -64
/musr/command globalfield printFieldValueAtPoint  780 0 -74
/musr/command globalfield printFieldValueAtPoint  780 0 -84
/musr/command globalfield printFieldValueAtPoint  780 0 -94
/musr/command globalfield printFieldValueAtPoint  780 0 -104
/musr/command globalfield printFieldValueAtPoint  780 0 -114
/musr/command globalfield printFieldValueAtPoint  780 0 -124
/musr/command globalfield printFieldValueAtPoint  780 0 -134
/musr/command globalfield printFieldValueAtPoint  780 0 -144
/musr/command globalfield printFieldValueAtPoint  780 0 -154

###################################################################################
#########################  P H Y S I C S      P R O C E S S E S  ##################
###################################################################################
# --- Low Energy (default) ---
#*/musr/command process addDiscreteProcess gamma G4LowEnergyPhotoElectric
#*/musr/command process addDiscreteProcess gamma G4LowEnergyCompton
#*/musr/command process addDiscreteProcess gamma G4LowEnergyGammaConversion
#*/musr/command process addDiscreteProcess gamma G4LowEnergyRayleigh
/musr/command process addProcess         e-    G4MultipleScattering -1 1 1
#/musr/command process addDiscreteProcess e-    G4CoulombScattering
#/musr/command process addProcess         e-    G4LowEnergyIonisation -1 2 2
#/musr/command process addProcess         e-    G4LowEnergyBremsstrahlung -1 -1 3
/musr/command process addProcess         e+    G4MultipleScattering -1 1 1
#/musr/command process addDiscreteProcess e+    G4CoulombScattering
/musr/command process addProcess         e+    G4eIonisation    -1 2 2
/musr/command process addProcess         e+    G4eBremsstrahlung   -1 3 3
/musr/command process addProcess         e+    G4eplusAnnihilation 0 -1 4

# --- Muons ---
/musr/command process addProcess          mu+   G4MultipleScattering -1 1 1
/musr/command process addProcess          proton   G4MultipleScattering -1 1 1
#/musr/command process addProcess          mu+   MultipleAndCoulombScattering -1 1 1 goulombRegion
#/musr/command process addDiscreteProcess  mu+   G4CoulombScattering
/musr/command process addProcess          mu+   G4MuIonisation       -1 2 2
/musr/command process addProcess          proton   G4MuIonisation       -1 2 2
/musr/command process addProcess          mu+   G4MuBremsstrahlung   -1 3 3
/musr/command process addProcess          mu+   G4MuPairProduction   -1 4 4
/musr/command process addProcess          mu-   G4MultipleScattering -1 1 1
#/musr/command process addDiscreteProcess  mu-   G4CoulombScattering
/musr/command process addProcess          mu-   G4MuIonisation       -1 2 2
/musr/command process addProcess          mu-   G4MuBremsstrahlung   -1 3 3
/musr/command process addProcess          mu-   G4MuPairProduction   -1 4 4
# --- Muonium ---
/musr/command process addProcess          mu+   musrMuFormation     -1 -1 2
#cks - the following line not supported yet, has to be tested (at the moment, musrMuScatter is hard wired in the musrPhysicsList.cc):
#/musr/command process addProcess          Mu   musrMuScatter        -1 -1 1





################################################################################################################
# -- Setting simulation PARAMETERS --
################################################################################################################

# Set the overall range cut (default 0.1 mm)
#*/run/setCut 1 mm

# Set user limits
#/musr/command SetUserLimits log_World ustepMax(mm) utrakMax(mm) utimeMax(ns) uekinMin(MeV) urangMin(mm)
/musr/command SetUserLimits log_World      -1         -1             -1          1e-7          -1
#/musr/command SetUserLimits log_World      -0.5         -0.5             -0.5          1e-7          -0.5

# Store ALL the events in a ROOT tree or just the interesting ones? (default is true)
#*/musr/command storeOnlyEventsWithHits false

# abandon all positron tracks to study where muons are stopping
/musr/command killAllPositrons true

# Set the minimum time separation between two subsequent signals in the same detector (in ns)
/musr/command signalSeparationTime 0.1

# Override runID number
#*/musr/run/runID 21

# Set the frequency of event printing
/musr/run/howOftenToPrintEvent 100

# RANDOM option choices: (specify the random number generator initialisation)
# 0 ... no initialisation (default)
# 1 ... use actual computer time to initialise now                    # Pseudo-random numbers
# 2 ... use event number to initialise at the beginning of each event # Reproducible numbers
# 3 ... read in the random no. initial values for each event from a file
/musr/run/randomOption 1 

# VISUALIZATION options
# To enable or disable visualization uncomment one of these lines
# To modify visualization options edit the file vis.mac
#/vis/disable
#/vis/viewer/set/viewpointVector 0 1 0




################################################################################################################
# -- Setting PARTICLE GUN parameters --
################################################################################################################

# Default momentum  direction: 001, i.e. 0z.
# Default muon spin direction: 100, i.e. 0x.
# Default particle type: mu+ (can be changed to Mu)

# Set particle type	
/gun/primaryparticle mu+

# Set beam vertex 

#modified 20160607 rkita
#Real surface of a target
/gun/vertex  780. 0. -852. mm

#/gun/vertexsigma    4. 4.  0  mm
/gun/vertexsigma    0. 0.  0  mm

/gun/kenergy 0.0001 keV 


# Set beam momentum direction
#/gun/tiltsigma 30 30 0 deg
/gun/tiltsigma 0 0 0 deg

# Set muon spin direction
/gun/muonPolarizVector 0 0 -1
/gun/muonPolarizFraction 0.5

# Set time profile of the ionize muonium (muon starting time)
/gun/starttimesigma 60 ns


/gun/decaytimelimits 10400 10420 219700.03 ns

 

/gun/turtlefilename 0703_Point_${i}.dat


#/control/execute vis.mac

# BEAM ON
/run/beamOn  650 
#/run/beamOn   68



">>./0704_mac/musr_simple_0704_$i.mac
done



