search=$1
replace=$2
ack -li $search | xargs sed -i.bak "s/$search/$replace/g"

