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

FILES="../input/clustalo-permuted-quicktree.adj
../input/clustalo-permuted-rapidnj.adj
../input/kalign-permuted-quicktree.adj
../input/kalign-permuted-rapidnj.adj
../input/mafft-permuted-quicktree.adj
../input/mafft-permuted-rapidnj.adj
../input/muscle-permuted-quicktree.adj
../input/muscle-permuted-rapidnj.adj"

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

