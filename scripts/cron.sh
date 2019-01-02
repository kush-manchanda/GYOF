#!/bin/sh

# Load configuration to cron
# Author: Howard Webb
# Date: 11/16/2017

#######################################

TARGET=/home/pi/Seed
PYTHON=$TARGET/Python

# Declarations
RED='\033[31;47m'
NC='\033[0m'

# Exit on error
error_exit()
{
	echo ${RED} $(date +"%D %T") "${PROGNAME}: ${1:="Unknown Error"}" ${NC} 1>&2
	exit 1
}

##########################################


# Seed script to load cron job file

timestamp="$(date +"%D %T")"

crontab /home/pi/Seed/scripts/Seed_cron.txt || error_exit "Failure loading Cron"
echo $(date +"%D %T") "Cron loaded"