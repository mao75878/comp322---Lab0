#compile using: chmod +x launch-philosophers.sh
#run with ./______
program=./dining-p
seats=$1
position=$2

#prompt user to input more args
if [ $# -gt 2 ];
then
echo "Error: input less arguments";
exit 1;
fi

#if there's no number of seats given
if [ -z ${seats} ]; 
then
echo "Enter a number of seats.";
exit 1;
fi


#if there's no position number given
if [ -z ${position} ];
then
echo "Enter a number for a philosopher.";
exit 1;
fi


#if there's less seats than philosophers/position given
if [ ${seats} -lt ${position} ];
then
echo "Error: not enough seats.";
exit 1;
fi

#prints positiona and cycles of
#philosopher's PID.
cycle=1
while [ ${cycle} -le ${position} ] ; 
      do
      ${program} ${seats} ${cycle} &
      
      echo "Philosopher #${cycle}'s PID is" $!
      cycle=$(( $cycle + 1 ))
      
done
