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

FILES="../input/christians/clustalo-permuted-quicktree.adj,../input/christians/clustalo-normal-quicktree.adj
../input/christians/clustalo-permuted-rapidnj.adj,../input/christians/clustalo-normal-rapidnj.adj
../input/christians/kalign-permuted-quicktree.adj,../input/christians/kalign-normal-quicktree.adj
../input/christians/kalign-permuted-rapidnj.adj,../input/christians/kalign-normal-rapidnj.adj
../input/christians/mafft-permuted-quicktree.adj,../input/christians/mafft-normal-quicktree.adj
../input/christians/mafft-permuted-rapidnj.adj,../input/christians/mafft-normal-rapidnj.adj
../input/christians/muscle-permuted-quicktree.adj,../input/christians/muscle-normal-quicktree.adj
../input/christians/muscle-permuted-rapidnj.adj,../input/christians/muscle-normal-rapidnj.adj"

for i in ${FILES}; do
    IFS=","
    set ${i}
    tmp=${2%.adj}
    tmp=${tmp##*/}
    printf "%-25s " "$tmp"
    DISTANCE="$(./AiBToS_Project1 ${1} ${2})"
    printf "%5s\n" "${DISTANCE}"
done

