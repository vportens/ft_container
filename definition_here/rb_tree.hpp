#include "utils.hpp"
#include <iostream>


namespace ft
{

const // It is a const object...
class nullptr_t 
{
  public:
    template<class T>
    inline operator T*() const // convertible to any type of null non-member pointer...
    { return 0; }

    template<class C, class T>
    inline operator T C::*() const   // or any type of null member pointer...
    { return 0; }

  private:
    void operator&() const;  // Can't take address of nullptr

} nullptr = {};

template<typename T>
struct Node {
	typedef T value_type;
	value_type value;

	Node *parent;
	Node *left;
	Node *right;
	int color;

	Node(const value_type& val) : value(val),  parent(0), left(0), right(0), color(0){}

	Node(const value_type& val, Node *par, Node *l, Node *r, int col) : value(val),  parent(par), left(l), right(r), color(col){}

	Node() : value(), parent(0) , left(0), right(0), color(0) {}

	Node(const Node& cpy) : value(cpy.value), parent(cpy.parent), left(cpy.left), right(cpy.right), color(cpy.color) {}

	Node(const Node* cpy) {
		value = cpy->value;
		parent = cpy->parent;
		left = cpy->left;
		right = cpy->right;
		color = cpy->color;
	}

/*	template<typename U, typename T1>
	bool	operator!=(const ft::Node<U>* x, const ft::Node<T1>* xa) const {
		return (x != xa);
	}
	*/
/*	operator Node<const T> const() {
		return (Node<const T>(value, parent, left, right, color));
	}

	operator Node<const T>* const() {
		return (Node<const T>*(value, parent, left, right, color));
	} */

/*
	Node(const Node* cpy) {
		color = cpy->color;
		value = cpy->value;
		parent = cpy->parent;
		right = cpy->right;
		left = cpy->left;
	
	}

	Node(const Node& cpy) {
		color = cpy.color;
		value = cpy.value;
		parent = cpy.parent;
		right = cpy.right;
		left = cpy.left;
	}
*/

	virtual ~Node() {}

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
		return (*this);
	}

	Node*	operator=(Node* cpy) {
		if (this == cpy)
			return (this);
		this->value = cpy->value;
		this->color = cpy->color;

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
		return (this);
	}


};


template<typename T>
class RedBlackTree {

	typedef Node<T> *NodePtr;
	public:

	NodePtr root;
	NodePtr TNULL;

   private:
  void initializeNULLNode(NodePtr node, NodePtr parent) {
    node->value = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
  }

  // Preorder
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
    while (x != root && x->color == 0) {
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
          x = root;
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
          x = root;
        }
      }
    }
    x->color = 0;
  }

  void rbTransplant(NodePtr u, NodePtr v) {
    if (u->parent == nullptr) {
      root = v;
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
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 1) {//rb_tree.cpp:39:18: error: a typedef cannot be a template
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
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0;
  }

  void printHelper(NodePtr root, std::string indent, bool last) {
    if (root != TNULL) {
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
  RedBlackTree() {
    TNULL = new ft::Node<T>;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  }

  void preorder() {
    preOrderHelper(this->root);
  }

  void inorder() {
    inOrderHelper(this->root);
  }

  void postorder() {
    postOrderHelper(this->root);
  }

  NodePtr searchTree(int k) {
    return searchTreeHelper(this->root, k);
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
    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
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
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
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
    node->parent = nullptr;
//    node->value = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = nullptr;
    NodePtr x = this->root;

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
      root = node;
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

    insertFix(node);
  }

  NodePtr getRoot() {
    return this->root;
  }

  void deleteNode(T value) {
    deleteNodeHelper(this->root, value);
  }

  void deleteNode(NodePtr node) {
	  deleteNodeHelper(this->root, node->value);
  }

  void printTree() {
    if (root) {
      printHelper(this->root, "", true);
    }
  }

	operator RedBlackTree<const T>() const {
		return RedBlackTree<const T>();
	}

};
}

/*
int main() {

	ft::pair<char *, int> test;
	ft::pair<char *, int> test1;
	ft::pair<char *, int> test2;
	ft::pair<char *, int> test3;
	ft::pair<char *, int> test4;
	ft::pair<char *, int> test5;
	ft::pair<char *, int> test6;
	ft::pair<char *, int> test7;
	ft::pair<char *, int> test8;
	ft::pair<char *, int> test9;
	
	char   str[] = "bonjour";
	char   str1[] = "aurevoir";
	char   str2[] = "tu fais";
	char   str3[] = "quoi";
	char   str4[] = "aujourd'hui";
	char   str5[] = "yes";
	char   str6[] = "davidGetta";
	char   str7[] = "skusku";
	char   str8[] = "vroumvroum";
	char   str9[] = "skipadadoua";

	test = ft::make_pair(str, 0);
	test1 = ft::make_pair(str1, 1);
	test2 = ft::make_pair(str2, 2);
	test3 = ft::make_pair(str3, 3);
	test4 = ft::make_pair(str4, 4);
	test5 = ft::make_pair(str5, 5);
	test6 = ft::make_pair(str6, 6);
	test7 = ft::make_pair(str7, 7);
	test8 = ft::make_pair(str8, 8);
	test9 = ft::make_pair(str9, 9);


  ft::RedBlackTree<ft::pair<char *, int> > bst;
*/
/*
	bst.insert(55);
	bst.insert(40);
	bst.insert(65);
	bst.insert(60);
	bst.insert(75);
	bst.insert(57);
*/
/*
	bst.insert(test);
	bst.insert(test1);
	bst.insert(test2);
	bst.insert(test3);
	bst.insert(test4);
	bst.insert(test5);
	bst.insert(test6);
	bst.insert(test7);
	bst.insert(test8);
	bst.insert(test9);

	bst.printTree();
	cout << endl
     << "After deleting" << endl;
//  bst.deleteNode(40);
  bst.printTree();
}

*/