#!/bin/bash

#Verify args
if [ $# -ne 1 ]; then
    echo "Usage: ./runTests <folder>"
    exit
fi

make a.out;
cd $1

for f in *.in; do
    #Redirect output
    time (../a.out <$f) 1>output.txt 2>exectime.txt

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
            vertexes=$word
        else
            edges=$word
        fi
        i=$((i+1))
    done

    echo "============ $f ============"
    echo "Size(V+E):       $(($vertexes+$edges))"
    echo "Output:          $output"
    echo "Execution time:  ${exectime:2:6}"
    echo
    
done

rm exectime.txt
rm output.txt
cd ..
rm a.out