#!/bin/bash
# $ 07/2017 lindbohansen@gmail.com $

width=-151.5
length=-958.5
filename="figaro-fullsource.mac"

echo "# FIGARO source iterator" > $filename
echo "# $ 07/2017 lindbohansen@gmail.com $" >> $filename
echo "###" >> $filename

strengthsfile=../figaro/figaro-source-strengths.csv

OLDIFS=$IFS
IFS=,
[ ! -f $strengthsfile ] && { echo "$strengthsfile not found"; exit 99; }
{ read
counter=0
while read radius height strength
do
  if [ $counter -eq 0 ]
  then
        echo "# source 1.17 MeV" >> $filename
	echo "/gps/particle gamma" >> $filename
	echo "/gps/pos/type Volume" >> $filename
	echo "/gps/pos/shape Cylinder" >> $filename
	echo "/gps/pos/radius $radius cm" >> $filename
	echo "/gps/pos/halfz 0.25 cm" >> $filename
	echo "/gps/pos/centre $width $height $length cm" >> $filename
	echo "/gps/pos/rot1 1 0 0" >> $filename
	echo "/gps/pos/rot2 0 0 1" >> $filename
	echo "/gps/ang/type iso" >> $filename
	echo "/gps/energy 1.17 MeV" >> $filename
	echo "/gps/source/intensity $strength" >> $filename
	if [ $radius == '1.5' ]
	then
	  echo "/gps/pos/confine SteelSource" >> $filename
        fi

        echo "# source 1.33 MeV" >> $filename
	echo "/gps/source/add $strength" >> $filename
	echo "/gps/particle gamma" >> $filename
	echo "/gps/pos/type Volume" >> $filename
	echo "/gps/pos/shape Cylinder" >> $filename
	echo "/gps/pos/radius $radius cm" >> $filename
	echo "/gps/pos/halfz 0.25 cm" >> $filename
	echo "/gps/pos/centre $width $height $length cm" >> $filename
	echo "/gps/pos/rot1 1 0 0" >> $filename
	echo "/gps/pos/rot2 0 0 1" >> $filename
	echo "/gps/ang/type iso" >> $filename
	echo "/gps/energy 1.33 MeV" >> $filename
	if [ $radius == '1.5' ]
	then
	  echo "/gps/pos/confine SteelSource" >> $filename
        fi

	echo "###" >> $filename
        ((counter++))
  else
        echo "# source 1.17 MeV" >> $filename
        echo "/gps/source/add $strength" >> $filename
	echo "/gps/particle gamma" >> $filename
	echo "/gps/pos/type Volume" >> $filename
	echo "/gps/pos/shape Cylinder" >> $filename
	echo "/gps/pos/radius $radius cm" >> $filename
	echo "/gps/pos/halfz 0.25 cm" >> $filename
	echo "/gps/pos/centre $width $height $length cm" >> $filename
	echo "/gps/pos/rot1 1 0 0" >> $filename
	echo "/gps/pos/rot2 0 0 1" >> $filename
	echo "/gps/ang/type iso" >> $filename
	echo "/gps/energy 1.17 MeV" >> $filename
	if [ $radius == '1.5' ]
	then
	  echo "/gps/pos/confine SteelSource" >> $filename
        fi

	echo "# source 1.33 MeV" >> $filename
	echo "/gps/source/add $strength" >> $filename
	echo "/gps/particle gamma" >> $filename
	echo "/gps/pos/type Volume" >> $filename
	echo "/gps/pos/shape Cylinder" >> $filename
	echo "/gps/pos/radius $radius cm" >> $filename
	echo "/gps/pos/halfz 0.25 cm" >> $filename
	echo "/gps/pos/centre $width $height $length cm" >> $filename
	echo "/gps/pos/rot1 1 0 0" >> $filename
	echo "/gps/pos/rot2 0 0 1" >> $filename
	echo "/gps/ang/type iso" >> $filename
	echo "/gps/energy 1.33 MeV" >> $filename
	if [ $radius == '1.5' ]
	then
	  echo "/gps/pos/confine SteelSource" >> $filename
        fi

	echo "###" >> $filename
  fi
done } < $strengthsfile
IFS=$OLDIFS

