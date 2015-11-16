#!/usr/bin/env bash
if [ ! -f AiBToS_Project1 ]; then
    mkdir tmp
    cd tmp

    cmake ../..
    make
    mv bin/AiBToS_Project1 ../
    cd ..
    rm -rf tmp/
    echo "Compiled new version"
fi

FILES="../input/christians/clustalo-permuted-quicktree.adj
../input/christians/clustalo-permuted-rapidnj.adj
../input/christians/kalign-permuted-quicktree.adj
../input/christians/kalign-permuted-rapidnj.adj
../input/christians/mafft-permuted-quicktree.adj
../input/christians/mafft-permuted-rapidnj.adj
../input/christians/muscle-permuted-quicktree.adj
../input/christians/muscle-permuted-rapidnj.adj"

for f1 in ${FILES}; do
    tmp=${f1%.adj}
    tmp=${tmp##*/}
    printf "%-27s " "$tmp"
    for f2 in ${FILES}; do
        DISTANCE="$(./AiBToS_Project1 ${f1} ${f2})"
        printf "%5s" "${DISTANCE}"
    done
    printf "\n"
done

