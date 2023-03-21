#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool hasChild(Node * node){
	if(node == nullptr){
		return false;
	}
	if(node->left || node->right){
		return true;
	}
	return false;
}


bool equalPaths(Node * root)
{
    // Add your code below
	if(!hasChild(root)){
		return true;
	}
	
	if(!hasChild(root->left) && !hasChild(root->right)) return true;
	else if(hasChild(root->left) != hasChild(root->right)) return false;

	bool left; bool right;
	if(root->left)left = equalPaths(root->left);
	if(root->right)right = equalPaths(root->right);

	return left == right;

}

