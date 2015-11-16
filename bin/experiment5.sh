#!/usr/bin/env bash
if [ ! -f AiBToS_Project1_perf ]; then
    mkdir tmp
    cd tmp

    cmake ../..
    make AiBToS_Project1_perf
    mv bin/AiBToS_Project1_perf ../
    cd ..
    rm -rf tmp/
    echo "Compiled new version"
fi

mkdir -p ../output
printf "Time n dist\n" > ../output/performance.txt

for i in $(seq 2 24); do
    DISTANCE="$(./AiBToS_Project1_perf ../input/test${i}.adj ../input/test${i}.adj)"
    printf "%s\n" "${DISTANCE}" >> ../output/performance.txt
    DISTANCE="$(./AiBToS_Project1_perf ../input/test${i}.adj ../input/test${i}.adj)"
    printf "%s\n" "${DISTANCE}" >> ../output/performance.txt
    DISTANCE="$(./AiBToS_Project1_perf ../input/test${i}.adj ../input/test${i}.adj)"
    printf "%s\n" "${DISTANCE}" >> ../output/performance.txt
    printf "Done with 2^${i}\n"
done

#Rscript ../output/performanxce.txt
#
#if hash evince 2>/dev/null; then
#    evince ../output/graph.pdf &
#fi

