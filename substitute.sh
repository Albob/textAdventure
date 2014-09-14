#
# substitute, by Alexis Bauchu, 2014
# This script allows substitution of a string is several files.
# Files where the substitution has been made are backed up in a .bak file.
#

search=$1
replace=$2
ack -li $search | xargs sed -i.bak "s/$search/$replace/g"

