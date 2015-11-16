import dendropy
from dendropy.calculate import treecompare
tns = dendropy.TaxonNamespace()
tree1 = dendropy.Tree.get(
    path="/home/mys/Documents/git/AiBToS-Project1/input/clustalo-quicktree.newick",
    schema='newick',
    taxon_namespace=tns
)
tree2 = dendropy.Tree.get(
    path="/home/mys/Documents/git/AiBToS-Project1/input/clustalo-rapidnj.newick",
    schema='newick',
    taxon_namespace=tns
)


tree1.encode_bipartitions()
tree2.encode_bipartitions()

print(treecompare.symmetric_difference(tree1, tree2))
