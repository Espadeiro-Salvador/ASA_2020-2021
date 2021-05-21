#!/bin/bash

#Verify args
if [ $# -ne 1 ]; then
    echo "Usage: ./runTests <folder>"
    exit
fi

make project;
cd $1
rm test_results.csv
touch test_results.csv

for f in *.in; do
    #Redirect output
    time (../project <$f) 1>output.txt 2>exectime.txt

    #Get execution time
    filename='exectime.txt'
    n=1
    while read line; do
        if (($n == 2)); then
            i=1
            for word in $line; do
                if (($i == 2)); then
                    exectime=$word
                fi
                i=$((i+1))
            done
        fi
        n=$((n+1))
    done <$filename

    #Get output
    filename='output.txt'
    read output <$filename

    #Get size
    filename=$f
    read input <$filename
    i=1
    for word in $input; do
        if (($i == 1)); then
            p=$word
        else
            c=$word
        fi
        i=$((i+1))
    done

    x_axis=$(($(($p*$p))+$(($c*$p))))

    echo "============ $f ============"
    echo "Size:            $x_axis"
    echo "Output:          $output"
    echo "Execution time:  ${exectime:2:6}"
    echo
    
    echo "$x_axis, ${exectime:2:5}" >> test_results.csv
done

rm exectime.txt
rm output.txt
cd ..
rm project