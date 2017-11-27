#!/bin/bash
# $ 07/2017 lindbohansen@gmail.com $
clear
echo "The FIGARO minisource Perpetuator is starting up..."
read -e -p "Please enter the location of geant4.10.03.p01-install: " dirGeant4
read -e -p "Please enter the location of FIGARO: " dirFIGARO
libGeant4=${dirGeant4%/}/lib64/Geant4-10.3.1/
shGeant4=${dirGeant4%/}/bin/geant4.sh
if [ -d $libGeant4 ] && [ -x $shGeant4 ] && [ -d $dirFIGARO ]
then
    # Geant4 libraries
    . $shGeant4
    # set an infinite loop
    while :
    do
	clear
	# display menu
	echo "$ 07/2017 lindbohansen@gmail.com $"
	echo "Server Name - $(hostname)"
        echo "geant4.10.03.p01-install : $dirGeant4"
        echo "FIGARO: $dirFIGARO"
	echo "-----------------------------------------"
	echo "  ~ The FIGARO Minisource Perpetuator ~"
	echo "-----------------------------------------"
	echo "1. Build and make FIGARO"
        echo "2. Run FIGARO interactively with a minisource"
	echo "3. Run FIGARO via a macro forall the minisource macros"
        echo "4. (not available with minisources)"
	echo "5. Copy minisource FIGARO results to the results folder"
	echo "6. Analyse FIGARO minisource output"
	echo "7. Todo: Run the FIGARO dose planning R app"
	echo "8. Todo: View FIGARO article with xdvi"
	echo "9. Exit The FIGARO Perpetuator"
	# get input from the user 
	read -p "Please enter your choice [ 1 - 9 ] " choice
	# make decision using case..in..esac 
	case $choice in
	    1)
		cd ${dirFIGARO%/}/figaro-build/
		echo "Awesome. Let's build and make FIGARO!"
		sleep 1.5
		
		cmake -DGeant4_DIR=$libGeant4 ${dirFIGARO%/}/figaro
    		make -j2

		read -p "Press [Enter] key to continue..." readEnterKey
		;;
	    
	    2)
		cd ${dirFIGARO%/}/figaro-build/
		echo "Here are the available minisource macros: "
		ls minisource*
		read -e -p "Please type in the name of the minisource macro you want: " macroName
		if [ -f $macroName ]
		then  
		  echo "Sweet! Let's play around with FIGARO for a while."
		  sleep 1.5
		  # NB DANGEROUS NEED TO COPY BACK SOURCE
		  cp figaro-fullsource.mac temp.mac
		  cp $macroName figaro-fullsource.mac
		  ./figaro
		  cp temp.mac figaro-fullsource.mac
		else
		  echo "I can't find that macro. Sorry!"  
		fi
	
		read -p "Press [Enter] key to continue..." readEnterKey
		;;
	   

	    3)
		datestamp=$(date +"%Y%m%d%H%M")
		cd ${dirFIGARO%/}/figaro-build/
		mkdir -p ${dirFIGARO%/}/figaro-build/$datestamp
		echo "Here are the available user macros: "
		ls *.usermacro
		read -e -p "Please type in the name of the user macro you want: " macroName
		if [ -f $macroName ]
		then
		    # Remove old data if allowed or exit
		    echo "To continue, I'll remove any old .csv files from the figaro-build directory."
		    read -e -p "Ok? y/n: " csvBool
		    if [ "$csvBool" == "y" ]
		    then
			echo "Removing old .csv files..."
			rm ${dirFIGARO%/}/figaro-build/*.csv*
			sleep 1.5
		    else
			echo "Alright. I'll exit and let you sort out the .csv files."
			echo "Run me again when you're ready!"
			exit 0
		    fi
		  echo "Alright! I'll stay here and run FIGARO with all minisources."
		  echo "I'll pipe the output to a datestamped folder: $datestamp"
		  echo "including any .csv files output from your macro"
		  sleep 3.0
		  thisLoop=0
		  thisLoopDir=0
		  now=0
		    for minimac in minisource*.mac
		    do
		      now=$(date +"%Y/%m/%d %H:%M")
		      thisLoop=${minimac%.mac}
	              thisLoopDir=${dirFIGARO%/}/figaro-build/$datestamp/$thisLoop
		      mkdir -p $thisLoopDir
		      echo "Starting loop $thisLoop at $now..."		  
		      # NB DANGEROUS NEED TO COPY BACK SOURCE
		      cp figaro-fullsource.mac temp.mac
		      cp $minimac figaro-fullsource.mac
		      ./figaro -m $macroName > $thisLoopDir/$thisLoop.out
		      cp temp.mac figaro-fullsource.mac
		      # Handle any output .csv files
		      cp ${dirFIGARO%/}/figaro-build/*.csv $thisLoopDir/
		      #for csvFile in $dirFIGARO/figaro-build/*.csv
		      #do
		      #  mv $dirFIGARO/figaro-build/$csvFile $thisLoopDir
		      #done
		      echo "Loop $thisLoop finished."
		      #((thisLoop++))
		    done
		else
		  echo "I can't find that macro. Sorry!"  
		fi
	
		read -p "Press [Enter] key to continue..." readEnterKey
		;;

	    4) echo "(option not available with minisources)"
	       
               read -p "Press [Enter] key to continue..." readEnterKey
	       ;;

	    5)  
		cd ${dirFIGARO%/}/figaro-build/
		echo "Here are the available folders from the build directory: "
		ls -d 20*/
		read -e -p "Please type in the name of the folder you want to copy to the results directory: " folderName
		if [ -d $folderName ]
		then  
		  echo "Roger that. Coping the folder to the results directory."
		  sleep 1.5

		  cp -r $folderName ${dirFIGARO%/}/figaro-results/
		  
		else
		  echo "I can't find that folder. Sorry!"  
		fi
		
		read -p "Press [Enter] key to continue..." readEnterKey
		;;

	    6)
		cd ${dirFIGARO%/}/figaro-results/
		echo "Here are the available timestamped folders in the results directory: "
		ls -d 20*/
		read -e -p "Please type in the name of the folder you want to analyse: " folderName
		if [ -d $folderName ]
		then  
		  echo "Exciting! I'll pop the results open in your browser."
		  sleep 1.5
		  if [ ! -f ${folderName%/}.csv ]
		  then
		      echo "There's no .csv summary file for the folder you specified, so I'm creating it now."
		      cd ${dirFIGARO%/}/figaro-analysis/
		      Rscript -e "date=date() ; rmarkdown::render('figaro-analysis-prep.Rmd',params=list(inFullPath='${dirFIGARO%/}/figaro-results/${folderName%/}'))"
		  fi
		cd ${dirFIGARO%/}/figaro-analysis/
		Rscript -e "date=date() ; rmarkdown::render('figaro-analysis.Rmd',params=list(inFullPath='${dirFIGARO%/}/figaro-results/${folderName%/}'))"
		xdg-open figaro-analysis.html &
		else
		  echo "I can't find that folder. Sorry!"  
		fi

		read -p "Press [Enter] key to continue..." readEnterKey
		;;

	    7)
	        echo "todo"

		read -p "Press [Enter] key to continue..." readEnterKey
		;;

	    8)
	        echo "todo"

		read -p "Press [Enter] key to continue..." readEnterKey
		;;

	    9)
		clear
		echo "The FIGARO Minisource Perpetuator has exited. Goodbye!"
		exit 0
		;;
	    *)
		echo "Sorry, I don't recognize that command. Try again!"	
		read -p "Press [Enter] key to continue..." readEnterKey
		;;
	esac
    done
else
  echo "The directories you specified do not exist."
  echo "The FIGARO Minisource Perpetuator has exited. Goodbye!"
  exit 0
fi
