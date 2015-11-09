from Bio import Phylo
from sys import argv

if len(argv) != 2:
	exit()

tree = Phylo.read(argv[1], 'newick')

def to_adjacency_list(tree):
    """Inspired by http://biopython.org/wiki/Phylo_cookbook#Exporting_to_other_types
    """
    allclades = list(tree.find_clades(order='level'))
    lookup = {}
    adjlist = {}
    for i, elem in enumerate(allclades):
		lookup[elem] = unicode(i)
		adjlist[unicode(i)] = set()
    for parent in tree.find_clades(terminal=False, order='level'):
        for child in parent.clades:
            adjlist[lookup[parent]].add(lookup[child])
            adjlist[lookup[child]].add(lookup[parent])

    return (allclades, adjlist)
    

clades, adjlist = to_adjacency_list(tree)

with open(argv[1][:-7] + ".adj", 'wb') as f:
	f.write(unicode(len(adjlist)) + u"\n")
	for k in sorted(adjlist.keys(), key=int):
		adj = map(unicode, list(adjlist[k]))
		f.write(unicode(len(adj)) + ' ' + ' '.join(adj) + "\n")
