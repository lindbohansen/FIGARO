#!/bin/bash
# $ 07/2017 lindbohansen@gmail.com $

width=-151.5
length=-958.5
# looping over heights 
for height in -76.75 -76.25 -75.75 -75.25 -74.75 -74.25 -73.75 -73.25 -72.75 -72.25 -71.75 -71.25
do
  for radius in 0.5 1.5
  do
    if [ $radius == 0.5 ]
    then
	filename="minisource$radius$width$height$length.mac"
        echo "# FIGARO source iterator" > $filename
	echo "# $ 07/2017 lindbohansen@gmail.com $" >> $filename

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
	echo "/gps/source/intensity 1" >> $filename

	echo "/gps/source/add 1" >> $filename
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

	echo "###" >> $filename
    else
	filename="minisource$radius$width$height$length.mac"
        echo "# FIGARO source iterator" > $filename
	echo "# $ 07/2017 lindbohansen@gmail.com $" >> $filename

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
	echo "/gps/source/intensity 1" >> $filename

	echo "/gps/source/add 1" >> $filename
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

	echo "###" >> $filename
    fi
  done
done

