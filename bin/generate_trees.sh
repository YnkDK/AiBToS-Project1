#!/bin/bash
EXTENSION=".newick"

if [ ! -f quicktree ] || [ ! -f rapidnj ]; then
    echo "Need both binaries 'quicktree' and 'rapidnj' to generate the to generate newick trees!"
    exit;
fi

for i in ../input/*.stockholm; do
	# Remove .stockholm from the filename
    OUTPUT=${i::-10}
    
    ./quicktree $i > "$OUTPUT-quicktree$EXTENSION"
    ./rapidnj -i sth $i | sed -e "s/'//g" > "$OUTPUT-rapidnj$EXTENSION"
done
