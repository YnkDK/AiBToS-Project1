from Bio import Phylo
from sys import argv

if len(argv) != 2:
	print 'Usage: python parser.py <newick-file>'
	exit()
elif not argv[1].endswith('.newick'):
	print 'Only supports .newick files'
	exit()

tree = Phylo.read(argv[1], 'newick')

def to_adjacency_list(tree):
    """Inspired by http://biopython.org/wiki/Phylo_cookbook#Exporting_to_other_types
    """
    allclades = list(tree.find_clades(order='level'))
    lookup = {}
    adjlist = {}
    for i, elem in enumerate(allclades):
		# Map app Clade-objects to a number
		lookup[elem] = unicode(i)
		# Represent the adjacency list as a set to avoid duplicates
		adjlist[unicode(i)] = set()
    for parent in tree.find_clades(terminal=False, order='level'):
        for child in parent.clades:
        	# We do not have any direction, hence parants are links to children and
        	# visa versa
            adjlist[lookup[parent]].add(lookup[child])
            adjlist[lookup[child]].add(lookup[parent])

    return adjlist
    

adjlist = to_adjacency_list(tree)

# Crop the ".newick" ending of the file and add ".adj"
with open(argv[1][:-7] + '.adj', 'wb') as f:
	# Write the number of nodes
	f.write(unicode(len(adjlist)) + u"\n")
	for k in sorted(adjlist.keys(), key=int):
		adj = list(adjlist[k])
		# Write the length of the adjecency list and then all adjacent nodes
		f.write(unicode(len(adj)) + ' ' + ' '.join(adj) + "\n")
		
print 'Written to', argv[1][:-7] + '.adj'
