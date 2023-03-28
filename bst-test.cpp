#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    AVLTree<int,int> bt;
bt.insert(std::make_pair(-93, 0));
bt.insert(std::make_pair(27, 0));
bt.insert(std::make_pair(1, 0));
bt.insert(std::make_pair(-109, 0));
bt.insert(std::make_pair(62, 0));
bt.insert(std::make_pair(37, 0));
bt.insert(std::make_pair(-14, 0));
bt.insert(std::make_pair(135, 0));
bt.insert(std::make_pair(-47, 0));
bt.insert(std::make_pair(-74, 0));
bt.insert(std::make_pair(133, 0));
bt.insert(std::make_pair(-115, 0));
bt.insert(std::make_pair(78, 0));
bt.insert(std::make_pair(-78, 0));
bt.insert(std::make_pair(147, 0));
bt.insert(std::make_pair(-5, 0));
bt.insert(std::make_pair(72, 0));
bt.insert(std::make_pair(-94, 0));
bt.insert(std::make_pair(10, 0));
bt.insert(std::make_pair(28, 0));
bt.insert(std::make_pair(68, 0));
bt.insert(std::make_pair(-64, 0));
bt.insert(std::make_pair(73, 0));
bt.insert(std::make_pair(-62, 0));
bt.insert(std::make_pair(66, 0));
bt.insert(std::make_pair(65, 0));
bt.insert(std::make_pair(-40, 0));
bt.insert(std::make_pair(7, 0));
bt.insert(std::make_pair(-102, 0));
bt.insert(std::make_pair(55, 0));



bt.print();
bt.clear();
    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<int,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     //cout << it->first << " " << it->second << endl;
    // }
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    //bt.clear();
    // // AVL Tree Tests
    // AVLTree<char,int> at;
    // at.insert(std::make_pair('a',1));
    // at.insert(std::make_pair('b',2));

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // at.remove('b');

    return 0;
}
