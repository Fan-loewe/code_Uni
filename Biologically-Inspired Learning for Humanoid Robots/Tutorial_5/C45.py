import math
import argparse
import pygraphviz as pyg
from collections import Counter


class Node:
    """
    C45Decision Tree contains follow information：
    1. Which attributes can be used to split this node；
    2. This node includes which sub-tree；
    """

    def __init__(self, select_row, attribute, parent_a, value):
        self.sample = select_row
        self.attribute = attribute
        self.parent_attr = parent_a
        self.value = value
        self.child = []


class Tree:


    def __init__(self, data):
        self.matrix = data
        self.row = len(data)
        self.col = len(data[0])
        self.root = Node(list(range(self.row)), list(range(self.col - 1)), self.col, 'root')
        self.build(self.root)

    def split(self, node):
        gain_max = 0
        gain_max_attr = 0
        gain_max_dict = {}
        res = []
        if len(node.attribute) == 0:
            return res
        for attr in node.attribute:
            t = self.entropy(node.sample)
            if t == 0:
                return res
            d = self.classify(node.sample, attr)
            c = self.conditional_entropy(node.sample, d)
            if c[1] == 0 and len(node.attribute) == 1:
                return res
            c_e = (t - c[0]) / (c[1] + 0.000001)
            if c_e > gain_max:
                gain_max = c_e
                gain_max_attr = attr
                gain_max_dict = d
        used_attr = node.attribute[:]
        used_attr.remove(gain_max_attr)
        for (k, v) in gain_max_dict.items():
            res.append(Node(v, used_attr, gain_max_attr, k))
        return res

    def entropy(self, index_list):
        """
        Calculate the entropy
        :param index_list
        :return: Entropy。
        """
        sample = {}
        for index in index_list:
            key = self.matrix[index][self.col - 1]
            if key in sample:
                sample[key] += 1
            else:
                sample[key] = 1
        entropy_s = 0
        for k in sample:
            entropy_s += -(sample[k] / len(index_list)) * math.log2(sample[k] / len(index_list))
        return entropy_s

    def classify(self, select_row, column):
        res = {}
        for index in select_row:
            key = self.matrix[index][column]
            if key in res:
                res[key].append(index)
            else:
                res[key] = [index]
        return res

    def conditional_entropy(self, select_row, d):
        c_e = 0
        total = len(select_row)
        spilt_info = 0
        for k in d:
            c_e += (len(d[k]) / total) * self.entropy(d[k])
            spilt_info += -(len(d[k]) / total) * math.log2((len(d[k]) / total))
        return (c_e, spilt_info)

    def build(self, root):
        child = self.split(root)
        root.child = child
        if len(child) != 0:
            for i in child:
                self.build(i)

    def save(self, filename):
        g = pyg.AGraph(strict=False, directed=True)
        g.add_node(self.root.value)
        self._save(g, self.root)
        g.layout(prog='dot')
        g.draw(filename)
        print("The file is save to %s." % filename)

    def _save(self, graph, root):
        if root.child:
            for node in root.child:
                graph.add_node(node.value)
                graph.add_edge(root.value, node.value)
                self._save(graph, node)
        else:
            class_list = []
            for i in range(len(root.sample)):
                class_list.append(self.matrix[root.sample[i]][self.col - 1])

            common_class = Counter(class_list).most_common(1)

            graph.add_node(self.matrix[root.sample[0]], label=common_class[0][0], shape="box")
            graph.add_edge(root.value, self.matrix[root.sample[0]])


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--file', dest='data', type=argparse.FileType('r'), default="data.txt")
    args = parser.parse_args()
    matrix = []
    lines = args.data.readlines()
    for line in lines:
        matrix.append(line.split())
    C45tree = Tree(matrix)
    C45tree.save("data.png")