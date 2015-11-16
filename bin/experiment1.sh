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

FILES="../input/clustalo-quicktree.adj
../input/clustalo-rapidnj.adj
../input/kalign-quicktree.adj
../input/kalign-rapidnj.adj
../input/mafft-quicktree.adj
../input/mafft-rapidnj.adj
../input/muscle-quicktree.adj
../input/muscle-rapidnj.adj"

for f1 in ${FILES}; do
    tmp=${f1%.adj}
    tmp=${tmp##*/}
    printf "%-18s " "$tmp"
    for f2 in ${FILES}; do
        DISTANCE="$(./AiBToS_Project1 ${f1} ${f2})"
        printf "%5s" "${DISTANCE}"
    done
    printf "\n"
done

