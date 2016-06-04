#!/bin/bash                                                                                                                           

res="0"
nb="0"
while read line
do
v=$(echo "$line"| sed -r "s:\x1B\[[0-9;]*[mK]::g"  | grep "AVERAGE");
if [ "$v" != "" ]
then
    v=${v#"[AVERAGE]	"}
    v=${v%" per day"}
    if [ "$v" != "0" ]
        then
	res+=" ";
        res+=$v;
	v=${v#"+"};
	if [ $(echo "$v > 0.0" | bc -l) == "0" ]
	    then
	    res+=" * 2";
	fi
    fi
    nb=$(($nb + 1));
fi
done

if [ "$nb" != 0 ]
then
    
    res=$(echo "( $res ) / $nb.0" | bc -l)
else
    res=0
fi
printf %.3f $res;
echo ""
