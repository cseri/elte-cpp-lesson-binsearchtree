#ifndef BINTREE_H_
#define BINTREE_H_

template <typename T>
class binsearchtree {
  class node {
  public:
    node(const T& value) : val(value), left(nullptr), right(nullptr) {}

    node(const node& other) :
      val(other.val),
      left(other.left ? new node(*(other.left)) : nullptr),
      right(other.right ? new node(*(other.right)) : nullptr) {
    }
    void operator=(const node& other) = delete;

    ~node() {
      if (left) {
        delete left;
        left = nullptr;
      }
      if (right) {
        delete right;
        right = nullptr;
      }
    }

    static void insert(node*& curr, const T& value) {
      if (curr == nullptr) {
        curr = new node(value);
      } else {
        if (value < curr->val) {
          insert(curr->left, value);
        } else {
          insert(curr->right, value);
        }
      }
    }

    template <typename Func>
    void do_action(Func action) {
      if (left)
        left->do_action(action);
      action(val);
      if (right)
        right->do_action(action);
    }

  private:
    T val;
    node* left;
    node* right;
  };

public:
  binsearchtree() : root(nullptr) {}
  binsearchtree(const binsearchtree& other) :
    root(other.root ? new node(*(other.root)) : nullptr) {
  }
  binsearchtree& operator=(const binsearchtree& other) {
    clear();
    if (other.root) {
      root = new node(*(other.root));
    }
    return *this;
  }

  ~binsearchtree() {
    clear();
  }

  void insert(const T& value) {
    node::insert(root, value);
  }

  template <typename Func>
  void do_for_each(Func action) {
    if (root)
      root->do_action(action);
  }

  void clear() {
    if (root) {
      delete root;
      root = nullptr;
    }
  }

private:
  node* root;
};

#endif // BINTREE_H_
