#########################################################################
# File Name: shm.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: Thu 16 Feb 2017 04:58:20 PM PST
#########################################################################
#!/bin/bash
while : ; do
	ipcs -m | grep -v "admin"
	sleep 1
	echo "##############"
done
