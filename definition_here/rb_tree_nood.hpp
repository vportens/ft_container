  
#ifndef RB_TREE_NOOB_HPP
#define RB_TREE_NOOB_HPP

#include "utils_map.hpp"
#include <iostream>

namespace ft {





template<typename T>
struct Node{
	typedef T value_type;
	typedef ft::Node<T> *NodePtr;
	value_type value;

	Node *parent;
	Node *left;
	Node *right;
	Node *TNULL;
	Node *root;
	int color;

	Node(const value_type& val) : value(val),  parent(0), left(0), right(0), TNULL(0), root(0), color(0){	}
	Node() : value(), parent(0) , left(0), right(0), TNULL(0), root(0), color(0) { }

	Node(const Node& cpy) : value(cpy.value), parent(cpy.parent), left(cpy.left), right(cpy.right),TNULL(cpy.TNULL), root(cpy.root), color(cpy.color) {	}

	Node(const Node* cpy) {
		TNULL = cpy->TNULL;
		root = cpy->root;
		value = cpy->value;
		parent = cpy->parent;
		left = cpy->left;
		right = cpy->right;
		color = cpy->color;
	}


	virtual ~Node() {
	}


	operator Node<const T> const() {
		return (Node<const T>(value,parent, left, right, color));
	}


	Node&	operator=(Node& cpy) {
		if (*this == cpy)
			return (*this);
		value = cpy.value;
		color = cpy.color;
		parent = cpy.parent;
		right = cpy.right;
		left = cpy.left;
		TNULL = cpy.TNULL;
		root = cpy.root;
		return (*this);
	}

	Node*	operator=(Node* cpy) {
		if (this == cpy)
			return (this);
		this->value = cpy->value;
		this->color = cpy->color;
		TNULL = cpy->TNULL;
		root = cpy->root;
		this->parent = cpy->parent;
		this->right = cpy->right;
		this->left = cpy->left;
		return (this);
	}

	Node*	operator=(const Node* cpy) {
		if (this == cpy)
			return (this);
		value = cpy->value;
		color = cpy->color;
		parent= cpy->parent;
		right = cpy->right;
		left = cpy->left;
		TNULL = cpy->TNULL;
		root = cpy->root;
		return (this);
	}
/*------------------------utils-------------------*/

	Node *getRoot() {
		NodePtr tmp = this;
		while (tmp->parent)
			tmp = tmp->parent;
		return (tmp);
	}

	Node *getRoot(Node *node) {
		Node *tmp(node);
		while (tmp->parent != tmp->TNULL && tmp->parent != nullptr && tmp->parent)
			tmp = tmp->parent;
		return (tmp);
	}

  void preOrderHelper(NodePtr node) {
    if (node != TNULL) {
      std::cout << node->value->first << " ";
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  }

  // Inorder
  void inOrderHelper(NodePtr node) {
    if (node != TNULL) {
      inOrderHelper(node->left);
      std::cout << node->value->first << " ";
      inOrderHelper(node->right);
    }
  }

  // Post order
  void postOrderHelper(NodePtr node) {
    if (node != TNULL) {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      std::cout << node->value->first << " ";
    }
  }

  NodePtr searchTreeHelper(NodePtr node, int key) {
    if (node == TNULL || key == node->value) {
      return node;
    }

    if (key < node->value) {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void deleteFix(NodePtr x) {
    NodePtr s;

    while (x != getRoot(x) && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
			s->color = 0;
			x->parent->color = 1;
			leftRotate(x->parent);
			if (s == s->getRoot())
		  		break;
          	s = x->parent->right;
		  	x->printTree();
        }
        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
     		if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
     		}
        	s->color = x->parent->color;
    		x->parent->color = 0;
      		s->right->color = 0;
       		leftRotate(x->parent);
        	x = getRoot();
        }
  	} else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }
        if (s->right->color == 0 && s->left->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
     		if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
    		}
     		s->color = x->parent->color;
     		x->parent->color = 0;
      		s->left->color = 0;
       		rightRotate(x->parent);
        	x = getRoot();
			}
		}
    }
	x = getRoot();
    x->color = 0;
}

void rbTransplant(NodePtr u, NodePtr v) {
	NodePtr tmp = getRoot();
    if (u->parent == nullptr) {
		tmp = v;
    } else if (u == u->parent->left) {
 		u->parent->left = v;
    } else {
  		u->parent->right = v;
    }
    v->parent = u->parent;
  }

void deleteNodeHelper(NodePtr z) { //, T key) {
  //  NodePtr z = TNULL;
    NodePtr x, y;

	/*
    while (node != TNULL) {
    	if (node->value.first == key.first) {
   			z = node;
    	}
  		if (node->value.first <= key.first) {
   			node = node->right;
   		} else {
   			node = node->left;
    	}
    }
	*/
    if (z == TNULL)
      return;
    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
    	x = z->right;
    	rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
    	x = z->left;
    	rbTransplant(z, z->left);
    } else {
    	y = minimum(z->right);
    	y_original_color = y->color;
   		x = y->right;
    	if (y->parent == z) {
    	x->parent = y;
	} else {
		rbTransplant(y, y->right);
 		y->right = z->right;
  		y->right->parent = y;
	}
	rbTransplant(z, y);
    y->left = z->left;
    y->left->parent = y;
 	y->color = z->color;
    }
    delete z;
	if (x == y->TNULL)
    if (y_original_color == 0) {
      deleteFix(x);
    }
  }

  // For balancing the tree after insertion
  void insertFix(NodePtr k) {
//	std::cout << "entre dans insert fix`k: " << k->value << std::endl;
    NodePtr u;
    NodePtr tmp = getRoot(k);

//	std::cout << "entre dans insert fix`" << std::endl;
    while (k->parent->color == 1) {
//		std::cout<< "while" << std::endl;
    	if (k->parent == k->parent->parent->right) {
    	    u = k->parent->parent->left;
    	    if (u->color == 1) {
  				u->color = 0;
    	    	k->parent->color = 0;
     		   	k->parent->parent->color = 1;
      		  	k = k->parent->parent;
    		} else {
        	if (k == k->parent->left) {
            	k = k->parent;
            	rightRotate(k);
          	}
          	k->parent->color = 0;
          	k->parent->parent->color = 1; // ici
          	leftRotate(k->parent->parent);
        	}
    	} else {
        	u = k->parent->parent->right;
        	if (u->color == 1) {
        		u->color = 0;
        		k->parent->color = 0;
        		k->parent->parent->color = 1; // ici
       			k = k->parent->parent;
        	} else {
        		if (k == k->parent->right) {
        			k = k->parent;
        			leftRotate(k);
        		}
        		k->parent->color = 0;
        		k->parent->parent->color = 1; // ici
        		rightRotate(k->parent->parent);
      		}
      	}
    	if (k == getRoot()) {
       		break;
    	}
    }
	tmp = getRoot();
    tmp->color = 0;
	}

  void printHelper(NodePtr root, std::string indent, bool last) {
    if (root != NULL && root != TNULL) {
      std::cout << indent;
      if (last) {
        std::cout << "R----";
        indent += "   ";
      } else {
        std::cout << "L----";
        indent += "|  ";
      }

      std::string sColor = root->color ? "RED" : "BLACK";
      std::cout << root->value << "(" << sColor << ")" << std::endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

   public:


  void preorder() {
    preOrderHelper(getRoot());
  }

  void inorder() {
    inOrderHelper(getRoot());
  }

  void postorder() {
    postOrderHelper(getRoot());
  }

  NodePtr searchTree(int k) {
    return searchTreeHelper(getRoot(), k);
  }

  NodePtr minimum(NodePtr node) {
    while (node->left != TNULL) {
      node = node->left;
    }
    return node;
  }

  NodePtr maximum(NodePtr node) {
    while (node->right != TNULL) {
      node = node->right;
    }
    return node;
  }

  NodePtr successor(NodePtr x) {
    if (x->right != TNULL) {
      return minimum(x->right);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  NodePtr predecessor(NodePtr x) {
    if (x->left != TNULL) {
      return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(NodePtr x) {
    NodePtr y = x->right;
    NodePtr tmp = getRoot();

    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      tmp = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;

  }

  void rightRotate(NodePtr x) {
    NodePtr y = x->left;
    NodePtr tmp = getRoot();
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      tmp = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

/*
  void insert(NodePtr node) {
	NodePtr tmp = getRoot();
    node->parent = nullptr;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = nullptr;
    NodePtr x = tmp;

    while (x != TNULL) {
      y = x;
      if (node->value.first < x->value.first) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr) {
      tmp = node;
    } else if (node->value.first < y->value.first) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == nullptr) {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr) {
      return;
    }
    insertFix(node);
  }
*/
 
  void deleteNode(T value) {
    deleteNodeHelper(getRoot(), value);
  }

  void deleteNode(NodePtr node) {
	  deleteNodeHelper(node); //, node->value);
  }

  void printTree() {
    if (getRoot()) {
      printHelper(getRoot(), "", true);
    }
  }


};

}
#endif