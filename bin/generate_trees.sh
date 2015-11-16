#!/bin/bash
EXTENSION=".newick"

if [ ! -f quicktree ] || [ ! -f rapidnj ]; then
    echo "Need both binaries 'quicktree' and 'rapidnj' to generate the to generate newick trees!"
    exit;
fi

for i in ../input/*.stockholm; do
	# Remove .stockholm from the filename
    OUTPUT=${i::-10}
    
    ./quicktree $i | tr -d '[:space:]' > "$OUTPUT-quicktree$EXTENSION"
    ./rapidnj -i sth $i | sed -e "s/'//g" | tr -d '[:space:]' > "$OUTPUT-rapidnj$EXTENSION"
done

for i in ../input/*.newick; do
    python parser.py "$i"
done
