#!/bin/bash

# Author: Liam Lawrence
# Date: 3.3.2017
# Restart script for 2017 Vision Processing file in case it crashes

while :
do
	echo "STARTING VISION"
	$(build/processor/2017-Vision-processor)
	
	EXITCODE=$(echo $?)

	if [ $EXITCODE !=  0 ]; then
		echo "ERROR: VISION CRASHED -- $EXITCODE -- RESTARTING NOW"
		continue
	else
		echo "EXITING VISION"
		break
	fi
done
