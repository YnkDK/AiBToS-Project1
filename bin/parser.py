from Bio import Phylo
from sys import argv

if len(argv) != 2:
    print 'Usage: python parser.py <newick-file>'
    exit()
elif not argv[1].endswith('.newick'):
    print 'Only supports .newick files'
    exit()


def to_adjacency_list(tree):
    """Inspired by http://biopython.org/wiki/Phylo_cookbook#Exporting_to_other_types

    :param tree:


    """
    lookup = {}
    adjacency_list = {}
    internal_nodes = []
    leaves = []

    for clade in list(tree.find_clades(order='level')):
        if clade.name is not None:
            leaves.append(clade)
        else:
            internal_nodes.append(clade)
    i = 0
    # For any n identical named laves, we ensure that we map that leaf to the same number
    for clade in sorted(leaves, key=lambda x: x.name):
        lookup[clade] = str(i)
        adjacency_list[str(i)] = set()
        i += 1
    # Add the internal nodes to the lookup after
    for clade in internal_nodes:
        lookup[clade] = str(i)
        adjacency_list[str(i)] = set()
        i += 1
    del leaves
    del internal_nodes

    for parent in tree.find_clades(terminal=False, order='level'):
        for child in parent.clades:
            # We do not have any direction, hence parents are links to children and
            # visa versa
            adjacency_list[lookup[parent]].add(lookup[child])
            adjacency_list[lookup[child]].add(lookup[parent])
    del lookup

    return adjacency_list


adjacent = to_adjacency_list(Phylo.read(argv[1], 'newick'))

# Crop the ".newick" ending of the file and add ".adj"
with open(argv[1][:-7] + '.adj', 'wb') as f:
    # Write the number of nodes
    f.write(str(len(adjacent)) + "\n")

    for k in sorted(adjacent.keys(), key=lambda x: len(adjacent[x])):
        adj = list(adjacent[k])
        # Write the length of the adjecency list and then all adjacent nodes
        f.write(str(len(adj)) + ' ' + ' '.join(adj) + "\n")

print 'Written to', argv[1][:-7] + '.adj'
