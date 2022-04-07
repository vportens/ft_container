
#ifndef RB_TREE_NOOB_HPP
#define RB_TREE_NOOB_HPP

#include "utils_noob.hpp"
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
	int color;

	Node(const value_type& val) : value(val),  parent(0), left(0), right(0), TNULL(0), color(0){	}


//	Node(const value_type& val, Node *par, Node *l, Node *r, int col) : value(val),  parent(par), left(l), right(r), color(col){}

	Node() : value(), parent(0) , left(0), right(0), TNULL(0), color(0) {
		
/*	
		TNULL = new ft::Node<T>;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right= nullptr;
		
		*/
	}

	Node(const Node& cpy) : value(cpy.value), parent(cpy.parent), left(cpy.left), right(cpy.right),TNULL(cpy.TNULL), color(cpy.color) {
		/*
		TNULL = new ft::Node<T>;
		TNULL->color = cpy->TNULL->color;
		TNULL->left = cpy->TNULL->left;
		TNULL->right = cpy->TNULL->right;
		*/
	}

	Node(const Node* cpy) {
		/*
		TNULL = new ft::Node<T>;
		TNULL->color = cpy->TNULL->color;
		TNULL->left = cpy->TNULL->left;
		TNULL->right = cpy->TNULL->right;
		*/
		TNULL = cpy->TNULL;
		value = cpy->value;
		parent = cpy->parent;
		left = cpy->left;
		right = cpy->right;
		color = cpy->color;
	}


	virtual ~Node() {
		//delete TNULL;
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
		return (*this);
	}

	Node*	operator=(Node* cpy) {
		if (this == cpy)
			return (this);
		this->value = cpy->value;
		this->color = cpy->color;
		std::cout << "here" << std::endl;
		TNULL = cpy->TNULL;
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
		return (this);
	}
/*------------------------utils-------------------*/
	Node *getRoot() {
		NodePtr tmp = this;
		while (tmp->parent)
			tmp = tmp->parent;
		return (tmp);
	}

	Node *getRoot(Node *node)
	{
		Node *tmp(node);
		while (tmp->parent)
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
    while (x != getRoot() && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
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

        if (s->right->color == 0 && s->right->color == 0) {
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

  void deleteNodeHelper(NodePtr node, T key) {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL) {
      if (node->value == key) {
        z = node;
      }

      if (node->value <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == TNULL) {
      std::cout << "Key not found in the tree" << std::endl;
      return;
    }

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
    if (y_original_color == 0) {
      deleteFix(x);
    }
  }

  // For balancing the tree after insertion
  void insertFix(NodePtr k) {
    NodePtr u;
    NodePtr tmp = getRoot();
//	std::cout << "addr k->parent: " << k->parent << std::endl;
//	std::cout << "k->parent: " << k->parent->value << std::endl;
    while (k->parent->color == 1) {
//		std::cout << "boucle dans le while du fix" <<  std::endl;
      if (k->parent == k->parent->parent->right) {
	//	  std::cout << "go a droite" << std::endl;
        u = k->parent->parent->left;
        if (u->color == 1) {//rb_tree.cpp:39:18: error: a typedef cannot be a template
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1; // ici
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
//		  std::cout << "go a droite" << std::endl;
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
//	  std::cout << "left rotation done on: " << x->value << std::endl;
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
//	  std::cout << "right rotation done" << std::endl;
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

  // Inserting a node

  void insert(NodePtr node) {
//    NodePtr node = new ft::Node<T>;
	NodePtr tmp = getRoot();
    node->parent = nullptr;
//    node->value = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = nullptr;
    NodePtr x = tmp;

    while (x != TNULL) {
      y = x;
      if (node->value < x->value) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr) {
      tmp = node;
    } else if (node->value < y->value) {
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
	//std::cout << "node to fix: " << node->value << std::endl;
    insertFix(node);
  }

 
  void deleteNode(T value) {
    deleteNodeHelper(getRoot(), value);
  }

  void deleteNode(NodePtr node) {
	  deleteNodeHelper(getRoot(), node->value);
  }

  void printTree() {
    if (getRoot()) {
      printHelper(getRoot(), "", true);
    }
  }


};

}
#endif