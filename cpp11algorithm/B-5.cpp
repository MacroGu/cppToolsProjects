// ConsoleApplication44.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <memory>
#include <iostream>
#include <queue>
#include <string>
#include <set>
#include <stack>
#include <exception>      // std::exception



class Node : public std::enable_shared_from_this<Node>
{
	std::shared_ptr<Node> parent{ nullptr };
	std::vector<std::shared_ptr<Node>> children{};
	int value{};
public:
	Node(int a_value) : value(a_value) {}
	~Node() {}
	
	std::vector<std::shared_ptr<Node>> getChildren() { return children; }
	std::shared_ptr<Node> getParent() { return parent; }

	int getValue()
	{
		return value;
	}
	std::shared_ptr<Node> addChild(const std::shared_ptr<Node>& child) {
		children.push_back(child);
		children.back()->parent = shared_from_this();
		return children.back();
	}

	void constructTree();
	std::shared_ptr<Node> getNodeBFS(int searchValue, bool includeThis = false);
	int getDepth();

	std::shared_ptr<Node> getNodeDFS(int searchValue, bool includeThis = false);

};

void Node::constructTree()
{
	int value;
	std::cout << "is this leaf node?  y or n" << std::endl;
	char isLeaf;
	std::cin >> isLeaf;
	if (isLeaf == 'y')
	{
		return;
	}

	std::cout << "please input the value of this node" << std::endl;
	std::cin >> value;
	std::shared_ptr<Node> node(new Node(value));
	node->constructTree();
	this->addChild(node);
}

std::shared_ptr<Node> Node::getNodeBFS(int searchValue, bool includeThis )
{
	std::queue<std::shared_ptr<Node>> Q;
	std::vector<std::shared_ptr<Node>> children;
	std::string searchPath = "";

	if (includeThis)
	{
		Q.push(this->shared_from_this()); // this should be root
	}
	else
	{
		children = this->getChildren();
		for (auto oneChild : children)
		{
			Q.push(oneChild);
		}
	}

	while (!Q.empty())
	{
		std::shared_ptr<Node> t = Q.front();
		searchPath += std::to_string(t->getValue());

		Q.pop();

		if (t->getValue() == searchValue)
		{
			std::cout << "search Path: " << searchPath << std::endl;
			return t->shared_from_this();
		}
		children = t->getChildren();
		for (auto oneChild : children)
		{
			Q.push(oneChild);
		}
	}

	std::cout << "final not found search Path: " << searchPath << std::endl;
}

std::shared_ptr<Node> Node::getNodeDFS(int searchValue, bool includeThis)
{
	std::stack<std::shared_ptr<Node>> Q;
	std::vector<std::shared_ptr<Node>> children;
	std::string searchPath = "";

	if (includeThis)
	{
		Q.push(this->shared_from_this());
	}
	else
	{
		children = this->getChildren();
		std::reverse(children.begin(), children.end());

		for (size_t i = 0; i < children.size(); i++)
		{
			Q.push(children[i]);
		}
	}

	while (!Q.empty())
	{
		std::shared_ptr<Node> t = Q.top();
		searchPath += std::to_string(t->getValue());

		Q.pop();
		if (t->getValue() == searchValue)
		{
			std::cout << "search path: " << searchPath << std::endl;
			return t;
		}
		children = t->getChildren();
		std::reverse(children.begin(), children.end());

		for (size_t i = 0; i < children.size(); i++)
		{
			Q.push(children[i]);
		}

	}

	std::cout << "final not found search Path: " << searchPath << std::endl;
}

int Node::getDepth()
{
	std::queue<std::shared_ptr<Node>> Q;
	std::vector<std::shared_ptr<Node>> children;
	int depth = 0;

	Q.push(this->shared_from_this()); // this should be root
	depth++;
	std::set<std::shared_ptr<Node>> parentSet;
	parentSet.insert(this->shared_from_this());

	while (!Q.empty())
	{
		std::shared_ptr<Node> t = Q.front();
		// get depth of t
		std::shared_ptr<Node> temp = t;
		int tempDepth = 0;
		while (temp->getParent() != nullptr)
		{
			tempDepth++;
			temp = temp->getParent();
		}
		if (tempDepth > depth)
		{
			depth = tempDepth;
		}

		Q.pop();

		children = t->getChildren();
		for (auto oneChild : children)
		{
			Q.push(oneChild);
		}
	}

	return depth;
}

int main()
{
	/*
	int a{1};
	int b = a;
	std::cout << a << std::endl;


	Node node1(1);
	Node node2(1);
	std::shared_ptr<Node> p1(nullptr);
	std::shared_ptr<Node> p2(new Node(42));
	try
	{
		if (p1 == nullptr)
		{
			std::cout << "equal" << std::endl;
			return 0;
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	*/

	std::shared_ptr<Node> root(new Node(1));
	std::shared_ptr<Node> TwoNode(new Node(2));
	std::shared_ptr<Node> threeNode(new Node(3));
	std::shared_ptr<Node> FourNode(new Node(4));
	root->addChild(TwoNode);
	root->addChild(threeNode);
	root->addChild(FourNode);
	std::shared_ptr<Node> FiveNode(new Node(5));
	std::shared_ptr<Node> SixNode(new Node(6));
	TwoNode->addChild(FiveNode);
	TwoNode->addChild(SixNode);
	std::shared_ptr<Node> SevenNode(new Node(7));
	SixNode->addChild(SevenNode);
	std::shared_ptr<Node> EigthNode(new Node(8));
	SevenNode->addChild(EigthNode);

	std::shared_ptr<Node> findNode = root->getNodeDFS(1,true);
	if (findNode != nullptr)
	{
		std::cout << findNode->getValue() << std::endl;
	}

	std::cout << root->getDepth() << std::endl;

    return 0;
}

