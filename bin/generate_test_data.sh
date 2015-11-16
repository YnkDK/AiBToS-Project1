#!/usr/bin/env bash
if [ ! -f TreeGenerator ]; then
    mkdir tmp
    cd tmp

    cmake ../..
    make TreeGenerator
    mv bin/TreeGenerator ../
    cd ..
    rm -rf tmp/
    echo "Compiled new version"
fi
for i in $(seq 2 20); do
    ./TreeGenerator "${i}" > "../input/test${i}.adj"
done