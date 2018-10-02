#ifndef TREE_H
#define TREE_H
#include<iostream>
#include<string>
#include"Tile.h"
template<typename T>
class Tree
{
private:
	class Node
	{
	public:
		Node* left;
		Node* right;
		Node* parent;
		Tile* element;

		Node()
		{
			this->x = int();
			this->y = int();
			this->left = nullptr;
			this->right = nullptr;
			//this->point = 0;
		}
		Node(Tile* obj)
		{
			this->element = obj;
			this->left = nullptr;
			this->right = nullptr;
			//this->point = 0;
		}
		~Node()
		{
			if (this->right != nullptr)
			{
				delete this->right;
			}
			if (this->left != nullptr)
			{
				delete this->left;
			}
		}

	};
	int nrOfNodes;
	Node* first;
public:
	Tree();
	virtual~Tree();
	Tree(const Tree& obj);
	//void operator=(const Tree& obj);
	void insert(Tile* obj);
	//void insert(int x, int y);
	void printAll();
	void printAllPrivate(Node* root);
	void leftRotation(Node* ptr);
	void rightRotation(Node* ptr);
	void setPoints(Node* node);
	int getLength()const;
	Tile* getAt(int x, int y);

};
template<typename T>
void Tree<T>::printAllPrivate(Node* root)
{
	if (root != nullptr)
	{
		if (root->left != nullptr)
		{
			printAllPrivate(root->left);
		}
		//std::cout << root->x << "," << root->y << " ";
		if (root->right != nullptr)
		{
			printAllPrivate(root->right);
		}
	}
	else
	{
		//std::cout << "The tree is empty";
	}
}

template<typename T>
Tree<T>::Tree()
{
	this->first = nullptr;
	this->nrOfNodes = 0;
}
template<typename T>
Tree<T>::~Tree()
{
	delete this->first;
}
template<typename T>
Tree<T>::Tree(const Tree & obj)
{
}
//template<typename T>
//void Tree<T>::insert(Tile obj)
//{
//	bool added = false;
//	Node* walker = nullptr;
//	walker = first;
//	if (nrOfNodes == 0)
//	{
//		this->first = new Node(element);
//	}
//	else
//	{
//		while (added == false)
//		{
//			if (walker->element < element)
//			{
//				std::cout << "Before change Address: " << walker << std::endl;
//				std::cout << element << std::endl;
//				if (walker->right == nullptr)
//				{
//					walker->right = new Node(obj.getXID(), obj.getYID, obj.getTileType(), obj.getImageId());
//					walker->point += 1;
//					walker->right->parent = walker;
//					//walker->parent = walker;
//					added = true;
//				}
//				walker = walker->right;
//				std::cout << "walker after " << walker;
//				std::cout << element << std::endl;
//
//			}
//			else
//			{
//				std::cout << "Before change Address: " << walker << std::endl;
//				std::cout << element << std::endl;
//				std::cout << "next->";
//
//				if (walker->left == nullptr)
//				{
//					walker->left = new Node(obj.getXID(), obj.getYID, obj.getTileType(), obj.getImageId());
//					walker->point += -1;
//					walker->left->parent = walker;
//					added = true;
//					std::cout << "this is left after insert node" << walker << std::endl;
//				}
//				walker = walker->left;
//				//walker->parent = walker;
//				std::cout << "walker after " << walker;
//				std::cout << element << std::endl;
//			}
//		}
//
//	}
//	nrOfNodes++;
//}
template<typename T>
void Tree<T>::insert(Tile* obj)
{
	bool added = false;
	Node* walker = nullptr;
	walker = first;
	if (nrOfNodes == 0)
	{
		this->first = new Node(obj);
	}
	else
	{
		while (added == false)
		{
			if (walker->element->getXID() < obj->getXID())
			{
				//std::cout << "Before change Address: " << walker << std::endl;
				//std::cout << x << std::endl;
				if (walker->right == nullptr)
				{
					walker->right = new Node(obj);
					//walker->point += 1;
					walker->right->parent = walker;
					//walker->parent = walker;
					added = true;
				}
				walker = walker->right;
				//std::cout << "walker after " << walker;
				//std::cout << x << std::endl;

			}
			else if (walker->element->getXID() > obj->getXID())
			{
				//std::cout << "Before change Address: " << walker << std::endl;
				//std::cout << x << std::endl;
				//std::cout << "next->";

				if (walker->left == nullptr)
				{
					walker->left = new Node(obj);
					//walker->point += -1;
					walker->left->parent = walker;
					added = true;
					//std::cout << "this is left after insert node" << walker << std::endl;
				}
				walker = walker->left;
				//walker->parent = walker;
				//std::cout << "walker after " << walker;
				//std::cout << x << std::endl;
			}
			else if (walker->element->getXID() == obj->getXID())
			{
				if (walker->element->getYID() < obj->getYID())
				{
					if (walker->right == nullptr)
					{
						walker->right = new Node(obj);
						//walker->point += 1;
						walker->right->parent = walker;
						added = true;
					}
					walker = walker->right;
				}
				else
				{
					if (walker->left == nullptr)
					{
						walker->left = new Node(obj);
						//walker->point += 1;
						walker->left->parent = walker;
						added = true;
					}
					walker = walker->left;
				}
			}
		}

	}
	nrOfNodes++;
}
template<typename T>
void Tree<T>::printAll()
{
	this->printAllPrivate(this->first);
}
template<typename T>
void Tree<T>::leftRotation(Node* ptr)
{
	Node* temp = ptr->right;
	ptr->right = temp->left;
	temp->left = ptr;
}
template<typename T>
void Tree<T>::rightRotation(Node* ptr)
{
	Node* temp = ptr->left;
	ptr->left = temp->right;
	temp->right = ptr;
}
template<typename T>
void Tree<T>::setPoints(Node * node)
{

}
template<typename T>
int Tree<T>::getLength() const
{
	return this->nrOfNodes;
}
template<typename T>
Tile* Tree<T>::getAt(int x, int y)
{
	int nrOfTImes = 0;
	bool added = false;
	Node* walker = nullptr;
	walker = first;
	if (nrOfNodes == 0)
	{
		return nullptr;
	}
	else
	{
		while (added == false)
		{
			if (walker->element->getXID() < x)
			{
				nrOfTImes++;
				walker = walker->right;
				if (walker == nullptr)
				{
					return nullptr;
				}
			}
			else if (walker->element->getXID() > x)
			{
				nrOfTImes++;
				walker = walker->left;
				if (walker == nullptr)
				{
					return nullptr;
				}
			}
			else
			{
				if (walker->element->getYID() < y)
				{
					nrOfTImes++;
					walker = walker->right;
					if (walker == nullptr)
					{
						return nullptr;
					}
				}
				else if (walker->element->getYID() > y)
				{
					nrOfTImes++;
					walker = walker->left;
					if (walker == nullptr)
					{
						return nullptr;
					}
				}
				else
				{
					nrOfTImes++;
					added = true;
					if (walker != nullptr)
					{
						//std::cout << walker->element->getXID() << "," << walker->element->getYID() << std::endl;
						//std::cout << nrOfTImes;
						return walker->element;
					}
				}
			}
		}
	}
	return nullptr;

}
#endif // !TREE_H
