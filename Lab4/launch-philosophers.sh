

EXEC=dining-p
SEATS=$1
child=$!
pids=()


sig_handler(){

	for((i=0; $i<$SEATS; i+=1))
	do
		kill -TERM ${pids[i]} 2>/dev/null
	done


	exit 0
}


trap 'sig_handler' TERM


for ((i=0; $i<$SEATS; i+=1))
do


	./$EXEC $SEATS $i &


	pids[${i}]=$! #pid of children
done
wait
