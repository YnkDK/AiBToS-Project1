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

FILES="../input/clustalo-permuted-quicktree.adj,../input/clustalo-quicktree.adj
../input/clustalo-permuted-rapidnj.adj,../input/clustalo-rapidnj.adj
../input/kalign-permuted-quicktree.adj,../input/kalign-quicktree.adj
../input/kalign-permuted-rapidnj.adj,../input/kalign-rapidnj.adj
../input/mafft-permuted-quicktree.adj,../input/mafft-quicktree.adj
../input/mafft-permuted-rapidnj.adj,../input/mafft-rapidnj.adj
../input/muscle-permuted-quicktree.adj,../input/muscle-quicktree.adj
../input/muscle-permuted-rapidnj.adj,../input/muscle-rapidnj.adj"

for i in ${FILES}; do
    IFS=","
    set ${i}
    tmp=${2%.adj}
    tmp=${tmp##*/}
    printf "%-18s " "$tmp"
    DISTANCE="$(./AiBToS_Project1 ${1} ${2})"
    printf "%5s\n" "${DISTANCE}"
done

