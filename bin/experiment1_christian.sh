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

FILES="../input/christians/clustalo-normal-quicktree.adj
../input/christians/clustalo-normal-rapidnj.adj
../input/christians/clustalw2-normal-quicktree.adj
../input/christians/clustalw2-normal-rapidnj.adj
../input/christians/kalign-normal-quicktree.adj
../input/christians/kalign-normal-rapidnj.adj
../input/christians/mafft-normal-quicktree.adj
../input/christians/mafft-normal-rapidnj.adj
../input/christians/muscle-normal-quicktree.adj
../input/christians/muscle-normal-rapidnj.adj"

for f1 in ${FILES}; do
    tmp=${f1%.adj}
    tmp=${tmp##*/}
    printf "%-26s " "$tmp"
    for f2 in ${FILES}; do
        DISTANCE="$(./AiBToS_Project1 ${f1} ${f2})"
        printf "%5s" "${DISTANCE}"
    done
    printf "\n"
done

