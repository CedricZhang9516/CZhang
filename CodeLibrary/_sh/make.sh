

#for file_a in ${Folder_A}/*; do
i=10

SOA_S3=0.99
EQ12=0
EQ34=0

while [ "$i" != "20" ]
do
    #p=$(( 200 * $i ))
    #p=$(($p+1))
    #q=200
    ${SOA_S3}=$((${SOA_S3}-0.01))
    EQ1=$((${EQ12}-0.01))
    EQ2=$((-${EQ12}+0.01))
    EQ3=$((${EQ34}-0.01))
    EQ4=$((-${EQ34}+0.01))
    i=$(($i+1))

    echo "

source ./GenMac1_shifted_alignment_CM20mis_plus_horizontal_detail.sh 200924_${i}_s1  /\
	1 0.995 0.995 ${SOA_S3}   -2.2 2.2 1.9 -1.9 0.0   241 -0.93 /\
	0 1 0  /\
	0 2000 0  /\
	780.0 0.0 -599 /\
	-402.7  -0.0  689.55 /\
	-45.0661 /\
	-0.17 0.1325 /\
	-0.68 -0.0394 /\
	-0.80 89.8030 /\
	-1.30 89.9785 /\
	-0.21 -89.9143 /\
	779.73 779.29 779.09 578.53 418.74 617.65 617.21 0 0
func_File

    ">>SBL_200924_EQ12.txt

done


