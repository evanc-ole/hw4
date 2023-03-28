#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void rightRotate(AVLNode<Key,Value>* node);
    void leftRotate(AVLNode<Key,Value>* node);
    void removeHelper(AVLNode<Key,Value>* node, int8_t diff);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    //empty tree
    //std::cout << new_item.first << std::endl;
    //this->print();
	if(!this->root_){
		this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
		return;
	}
	//Key already exists
	if(BinarySearchTree<Key, Value>::internalFind(new_item.first)){
		BinarySearchTree<Key, Value>::internalFind(new_item.first)->setValue(new_item.second);
		return;
	}

	AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value> *>(this->root_);
	while(true){
		if(temp->getKey() < new_item.first){
				if(!temp->getRight()){
					AVLNode<Key, Value>* insert = new AVLNode<Key, Value>(new_item.first, new_item.second, temp);
					temp->setRight(insert); temp->setBalance(temp->getBalance() + 1);
                    if(temp->getBalance()) insertFix(temp, temp->getRight());
                    return;
				}
				else{
					temp = temp->getRight();
				}
			}
		else{
			if(!temp->getLeft()){
				AVLNode<Key, Value>* insert = new AVLNode<Key, Value>(new_item.first, new_item.second, temp);
				temp->setLeft(insert); temp->setBalance(temp->getBalance() - 1);
                if(temp->getBalance()) insertFix(temp, temp->getLeft());
				return;
			}
			else{
				temp = temp->getLeft();
			}
		}
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n){
    if(p == this->root_) return;
    if(p->getParent()->getLeft() == p){
        p->getParent()->setBalance(p->getParent()->getBalance() - 1);
        if(p->getParent()->getBalance() == 0) return;
        else if(p->getParent()->getBalance() == -1) insertFix(p->getParent(), p);
        else if(p->getParent()->getBalance() == -2){
            if(p->getLeft() == n){
                rightRotate(p->getParent());
                p->setBalance(0); p->getRight()->setBalance(0);
            }
            else{
                leftRotate(p); rightRotate(n->getParent());
                if(n->getBalance() == -1){
                    p->setBalance(0); n->getRight()->setBalance(1); n->setBalance(0);
                    return;
                }
                else if(n->getBalance() == 0){
                    n->setBalance(0); p->setBalance(0); n->getRight()->setBalance(0);
                    return;
                }
                else{
                    n->setBalance(0); p->setBalance(-1); n->getRight()->setBalance(0);
                }
            }
        }
    }
    else{
        p->getParent()->setBalance(p->getParent()->getBalance() + 1);
        if(p->getParent()->getBalance() == 0) return;
        else if(p->getParent()->getBalance() == 1) insertFix(p->getParent(), p);
        else if(p->getParent()->getBalance() == 2){
            if(p->getRight() == n){
                leftRotate(p->getParent());
                p->setBalance(0); p->getLeft()->setBalance(0);
            }
            else{
                rightRotate(p); leftRotate(n->getParent());
                if(n->getBalance() == 1){
                    p->setBalance(0); n->getLeft()->setBalance(-1); n->setBalance(0);
                    return;
                }
                else if(n->getBalance() == 0){
                    n->setBalance(0); p->setBalance(0); n->getLeft()->setBalance(0);
                    return;
                }
                else{
                    n->setBalance(0); p->setBalance(1); n->getLeft()->setBalance(0);
                }
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rightRotate(AVLNode<Key,Value>* node){
    AVLNode<Key, Value> tempP = *node;
    AVLNode<Key, Value> tempC = *(node->getLeft());
    if(node == this->root_) this->root_ = node->getLeft();
    node->setParent(node->getLeft());
    node->getLeft()->setParent(tempP.getParent());
    node->getLeft()->setRight(node);
    node->setLeft(tempC.getRight());
    if(tempC.getRight()) tempC.getRight()->setParent(node);
    if(!tempP.getParent()) return;
    else if(tempP.getParent()->getRight() == node) tempP.getParent()->setRight(node->getParent());
    else tempP.getParent()->setLeft(node->getParent());
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftRotate(AVLNode<Key,Value>* node){
    AVLNode<Key, Value> tempP = *node;
    AVLNode<Key, Value> tempC = *(node->getRight());
    if(node == this->root_) this->root_ = node->getRight();
    node->setParent(node->getRight());
    node->getRight()->setParent(tempP.getParent());
    node->getRight()->setLeft(node);
    node->setRight(tempC.getLeft());
    if(tempC.getLeft()) tempC.getLeft()->setParent(node);
    if(!tempP.getParent()) return;
    else if(tempP.getParent()->getRight() == node) tempP.getParent()->setRight(node->getParent());
    else tempP.getParent()->setLeft(node->getParent());
}
/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
   // TODO
	AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
	if(!temp) return;
    //both
    if(temp->getLeft() && temp->getRight()){
        this->nodeSwap(temp, static_cast<AVLNode<Key, Value>*>(this->predecessor(temp)));
    }
    AVLNode<Key, Value>* parent = temp->getParent();
    int8_t diff;
    if(parent){
        if(parent->getLeft() == temp) diff = 1;
        else diff = -1;
    }
	//No Children
	if(!(temp->getLeft() || temp->getRight())){
		//just root
		if(!parent){
			this->root_ = NULL;
		}
		//right child
		else if(parent->getRight() == temp){
			parent->setRight(NULL);
            //parent->updateBalance(diff);
		}
		//left child
		else{
			parent->setLeft(NULL);
            //temp->getParent()->updateBalance(diff);
		}
	}

	//one child (left)
	if(temp->getLeft() && !temp->getRight()){
		if(temp == this->root_){
			this->root_ = temp->getLeft();
		}
		else if(parent->getRight() == temp){
			temp->getParent()->setRight(temp->getLeft());
            //temp->getParent()->updateBalance(diff);
		}
		else{
			parent->setLeft(temp->getLeft());
            //temp->getParent()->updateBalance(diff);
		}

		temp->getLeft()->setParent(parent);
	}
    //(right)
	else if(!temp->getLeft() && temp->getRight()){
		if(temp == this->root_){
			this->root_ = temp->getRight();
		}
		else if(parent->getRight() == temp){
			parent->setRight(temp->getRight());
            //temp->getParent()->updateBalance(diff);
		}
		else{
			parent->setLeft(temp->getRight());
            //temp->getParent()->updateBalance(diff);
		}
		temp->getRight()->setParent(temp->getParent());
    }

    delete temp;
    removeHelper(parent, diff);

}

template<class Key, class Value>
void AVLTree<Key, Value>::removeHelper(AVLNode<Key,Value>* node, int8_t diff)
{
    if(!node) return;
    int8_t ndiff;
    AVLNode<Key, Value>* p = node->getParent();
    if(node->getParent()){
        if(node->getParent()->getLeft() == node) ndiff = 1;
        else ndiff = -1;
    }

    if(diff == -1){
        if(node->getBalance() + diff == -2){
            AVLNode<Key, Value>* c = node->getLeft();
            if(c->getBalance() == -1){
                rightRotate(node);
                node->setBalance(0); c->setBalance(0); removeHelper(p, ndiff);
            }
            else if(c->getBalance() == 0){
                rightRotate(node); 
                node->setBalance(-1); c->setBalance(1); return; 
            }
            else if(c->getBalance() == 1){
                AVLNode<Key, Value>* g = c->getRight();
                leftRotate(c); rightRotate(node);
                if(g->getBalance() == 1){
                    node->setBalance(0); c->setBalance(-1); g->setBalance(0);
                }
                else if(g->getBalance() == 0){
                    node->setBalance(0); c->setBalance(0); g->setBalance(0);
                }
                else if(g->getBalance() == -1){
                    node->setBalance(1); c->setBalance(0); g->setBalance(0);
                }
                removeHelper(p, ndiff);
            }
        }
        else if(node->getBalance() + diff == -1){
            node->setBalance(-1);
            return;
        }
        else if(node->getBalance() + diff == 0){
            node->setBalance(0);
            removeHelper(p, ndiff);
        }
    }

    if(diff == 1){
        if(node->getBalance() + diff == 2){
            AVLNode<Key, Value>* c = node->getRight();
            if(c->getBalance() == 1){
                leftRotate(node);
                node->setBalance(0); c->setBalance(0); removeHelper(p, ndiff);
            }
            else if(c->getBalance() == 0){
                leftRotate(node); 
                node->setBalance(1); c->setBalance(-1); return; 
            }
            else if(c->getBalance() == -1){
                AVLNode<Key, Value>* g = c->getLeft();
                rightRotate(c); leftRotate(node); 
                if(g->getBalance() == -1){
                    node->setBalance(0); c->setBalance(1); g->setBalance(0);
                }
                else if(g->getBalance() == 0){
                    node->setBalance(0); c->setBalance(0); g->setBalance(0);
                }
                else if(g->getBalance() == 1){
                    node->setBalance(-1); c->setBalance(0); g->setBalance(0);
                }
                removeHelper(p, ndiff);
            }
        }
        else if(node->getBalance() + diff == 1){
            node->setBalance(1);
            return;
        }
        else if(node->getBalance() + diff == 0){
            node->setBalance(0);
            removeHelper(p, ndiff);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
