class Tree:
    def __init__(self, left, right):
        self.left = left
        self.right = right

t = Tree(Tree("LeafA", "LeaB"), Tree("LeafC", "LeafD"))
print t.right.left
