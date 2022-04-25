#pragma once
#include <iostream>
using namespace std;

enum Color { RED, BLACK };

//Queue class
class Queue {
private:
	class qu_node {//node of the queue
	public:
		int value;
		qu_node* next;
	};
	qu_node* head;
	qu_node* end;
	int size;
public:
	//constructor 
	Queue() {
		head = NULL;
		end = head;
		size = 0;
	}
	//destructor 
	~Queue() {
		while (size > 0) {
			pop();
		}
	}
	//insert elem
	void push(int value) {
		if (size == 0) {
			head = new qu_node;
			head->value = value;
			end = head;
		}
		else {
			end = end->next = new qu_node;
			end->value = value;
		}
		size++;
	}
	//return the first elem of the queue and delete them
	int pop() {
		if (Empty())
			throw std::out_of_range::out_of_range("The queue is empty");
		else {
			int top_value = head->value;
			qu_node* qu_point = head->next;
			delete head;
			head = qu_point;
			size--;
			return top_value;
		}
	}
	//queue is empty
	bool Empty() {
		bool empty = false;
		if (size == 0) {
			empty = true;
		}
		return empty;
	}

	void print() {
		while (size > 0) {
			if (head->value != 0)
				cout << head->value << " ";
			head = head->next;
			size--;
		}
	}
};

template <typename T1, typename T2>

class map : public Queue {

private:

	class node {
	public:
		bool color = 0;
		int elem = 0;
		int key = 0;
		node* left = NULL, * right = NULL, * parent = NULL;
	};
	T1 key;
	T2 value;

public:
	size_t size;
	node* tail;
	node* root;//pointer to the begin
	bool check = false;
	int elem;

	//Constructor without parameter
	map() {
		root = NULL;
		tail = NULL;
		size = 0;
	}
	//Destructor 
	~map() {
		clear();
	}

	//Inserting an element into the tree
	void insert(T1 key, T2 elem)
	{
		if (root == NULL) {
			node* current = new node;
			current->elem = elem;
			current->key = key;
			current->color = BLACK;
			current->left = current->right = NULL;
			root = current;
			tail = current;
			current->parent = NULL;

			size++;
		}
		else {
			node* current = tail;
			if (elem < current->elem)
			{
				if (current->left != NULL) {
					current = current->left;
					current->parent = tail;
					tail = current;
					insert(key, elem);
				}
				else
				{
					current->left = new node;
					current = current->left;
					current->parent = tail;
					current->left = NULL;
					current->right = NULL;
					current->elem = elem;
					current->key = key;
					current->color = RED;
					tail = root;
					size++;
					recovery_insert(current);
				}
			}

			if (elem > current->elem)
			{
				if (current->right != NULL) {
					current = current->right;
					current->parent = tail;
					tail = current;
					insert(key, elem);
				}
				else
				{
					current->right = new node;
					current = current->right;
					current->parent = tail;
					current->left = NULL;
					current->right = NULL;
					current->elem = elem;
					current->key = key;
					current->color = RED;
					tail = root;
					size++;
					recovery_insert(current);
				}
			}
		}
		tail = root;

	}

	//find
	node* find(T1 key) {
		if (size == 0) {
			throw out_of_range("No more elements");
		}
		Queue queue_value;
		queue_value.push(root->elem);
		if (root->key == key) {
			return root;
		}
		bool verification = false;
		while (!queue_value.Empty()) {
			node* current;
			int temp = queue_value.pop();
			if (verification == false) {
				current = root;
				verification = true;
			}
			current = root;
			while (current->elem != temp) {
				if (temp < current->elem) {
					current = current->left;
				}
				if (temp > current->elem) {
					current = current->right;
				}
			}
			if (current->left != NULL) {
				queue_value.push(current->left->elem);
				if (current->left->key == key) {
					return current->left;
				}
			}
			if (current->right != NULL) {
				queue_value.push(current->right->elem);
				if (current->right->key == key) {
					return current->right;
				}
			}
		}
		tail = root;
	}

	//Removing an item from the tree
	void remove(T1 key) {
		if (root == NULL) {
			throw invalid_argument("List is empty");
		}
		else {
			//If an element has no leaves or both
			if (!check) {
				elem = find(key)->elem;
				check = true;
			}
			node* current = tail;
			if (elem == current->elem) {
				if ((current->left == NULL) && (current->right == NULL)) { //If an item has no leaves
					if (current->parent->left == current) {
						node* extra_pointer = current->parent;
						delete current;
						extra_pointer->left = new node;
						current = extra_pointer->left;
						current->color = BLACK;
						current->elem = 0;
						current->parent = extra_pointer;
						size--;
						recovery_remove(current);
						check = false;
						tail = root;
						return;
					}
					else {
						current->color = BLACK;
						current->elem = 0;
						current->parent = tail->parent;
						current->parent->right = current;
						size--;
						recovery_remove(current);
						current->parent->right = NULL;
						current = NULL;
						check = false;
						tail = root;
						return;
					}

				}
				else {
					if ((root->right == NULL) && (root->left != NULL)) {
						node* extra_pointer = root;
						root = root->left;
						size--;
						tail = root;
						delete extra_pointer;
						recovery_remove(current);
						check = false;
						return;
					}
					node* extra_pointer = current;
					node* remove_elem = current;
					extra_pointer = extra_pointer->right;
					int min_elem = extra_pointer->elem;
					while (extra_pointer->left != NULL) {
						current = extra_pointer;
						extra_pointer = extra_pointer->left;
						if (extra_pointer->left == NULL) {
							min_elem = extra_pointer->elem;
							break;
						}
					}
					if ((root->right == NULL) && (root->left == NULL)) {
						delete root;
						root = NULL;
						size--;
						recovery_remove(current);
						check = false;
						return;
					}

					if (current == root) {
						current->elem = extra_pointer->elem;
						current->right = extra_pointer->right;
						extra_pointer->right = NULL;
						tail = root;
						size--;
						recovery_remove(current);
						check = false;
						return;
					}
					if ((extra_pointer->right != NULL) && (extra_pointer->left == NULL)) {
						current->left = extra_pointer->right;
						delete extra_pointer->right;
						current->left->right = NULL;
						remove_elem->elem = min_elem;
						tail = root;
						size--;
						recovery_remove(current);
						check = false;
						return;
					}
					else {
						remove_elem->elem = min_elem;
						delete extra_pointer;
						current->left = NULL;
						tail = root;
						size--;
						recovery_remove(current);
						check = false;
						return;
					}
				}
			}
			else {
				if ((elem == root->elem) && (root->right == NULL)) {
					current = root;
					root = root->left;
					delete current;
					size--;
					recovery_remove(current);
					check = false;
					return;
				}
				if ((elem == root->elem) && (root->left == NULL)) {
					current = root;
					root = root->right;
					delete current;
					size--;
					recovery_remove(current);
					check = false;
					return;
				}
				//4 cases (2 straight and 2 zig-zag)
				if (current->left != NULL) {
					if (elem == current->left->elem) {
						if ((current->left->left == NULL) && (current->left->right != NULL)) {
							node* extra_pointer = current->left;
							current->left = extra_pointer->right;
							delete extra_pointer;
							tail = root;
							size--;
							recovery_remove(current);
							check = false;
							return;
						}
						if ((current->left->left != NULL) && (current->left->right == NULL)) {
							node* extra_pointer = current->left;
							current->left = extra_pointer->left;
							delete extra_pointer;
							tail = root;
							size--;
							recovery_remove(current);
							check = false;
							return;
						}
					}
				}
				if (current->right != NULL) {
					if (elem == current->right->elem) {
						if ((current->right->left == NULL) && (current->right->right != NULL)) {
							node* extra_pointer = current->right;
							current->right = extra_pointer->right;
							delete extra_pointer;
							tail = root;
							size--;
							recovery_remove(current);
							check = false;
							return;
						}
						if ((current->right->left != NULL) && (current->right->right == NULL)) {
							node* extra_pointer = current->right;
							current->right = extra_pointer->left;
							delete extra_pointer;
							tail = root;
							size--;
							recovery_remove(current);
							check = false;
							return;
						}
					}
				}
				if ((current->right == NULL) && (current->left == NULL)) {
					throw invalid_argument("Element doesn't exist");
				}
				if (elem > current->elem) {
					current->parent = tail;
					current = current->right;
					tail = current;
				}
				if (elem < current->elem) {
					current->parent = tail;
					current = current->left;
					tail = current;
				}
				remove(elem);
			}
		}
		tail = root;
	}

	// left rotation
	void left_rotate_for_insert(node* current) {
		node* extra_pointer = current->right;
		current->right = extra_pointer->left;
		if (extra_pointer->left != NULL) {
			extra_pointer->left->parent = current;
		}
		extra_pointer->parent = current->parent;
		if (current->parent == nullptr) {
			root = extra_pointer;
		}
		else if (current == current->parent->left) {
			current->parent->left = extra_pointer;
		}
		else {
			current->parent->right = extra_pointer;
		}
		extra_pointer->left = current;
		current->parent = extra_pointer;
	}
	void left_rotate_for_remove(node* current) {
		node* extra_pointer = current->right;
		current->right = extra_pointer->left;
		if (extra_pointer->left != NULL) {
			extra_pointer->left->parent = current;
		}
		extra_pointer->parent = current->parent;
		if (current->parent == current) {
			root = extra_pointer;
		}
		else if (current == current->parent->left) {
			current->parent->left = extra_pointer;
		}
		else {
			current->parent->right = extra_pointer;
		}
		extra_pointer->left = current;
		current->parent = extra_pointer;
	}

	// right rotation
	void right_rotate_for_insert(node* current) {
		node* extra_pointer = current->left;
		current->left = extra_pointer->right;
		if (extra_pointer->right != NULL) {
			extra_pointer->right->parent = current;
		}
		extra_pointer->parent = current->parent;
		if (current->parent == nullptr) {
			root = extra_pointer;
		}
		else if (current == current->parent->right) {
			current->parent->right = extra_pointer;
		}
		else {
			current->parent->left = extra_pointer;
		}
		extra_pointer->right = current;
		current->parent = extra_pointer;
	}
	void right_rotate_for_remove(node* current) {
		node* extra_pointer = current->left;
		current->left = extra_pointer->right;
		if (extra_pointer->right != NULL) {
			extra_pointer->right->parent = current;
		}
		extra_pointer->parent = current->parent;
		if (current->parent == current) {
			root = extra_pointer;
		}
		else if (current == current->parent->right) {
			current->parent->right = extra_pointer;
		}
		else {
			current->parent->left = extra_pointer;
		}
		extra_pointer->right = current;
		current->parent = extra_pointer;
	}

	//recovery
	void recovery_insert(node* current) {
		while (current->parent->color == RED) {
			if (current->parent == current->parent->parent->left) {
				if (current->parent->parent->right->color == RED) {
					current->parent->parent->right->color = BLACK;
					current->parent->color = BLACK;
					current->parent->parent->color = RED;
					current = current->parent->parent;
				}
				else {
					if (current == current->parent->right) {
						current = current->parent;
						left_rotate_for_insert(current);
					}
					current->parent->color = BLACK;
					current->parent->parent->color = RED;
					right_rotate_for_insert(current->parent->parent);
				}
				continue;
			}
			if (current->parent == current->parent->parent->right) {
				if (current->parent->parent->left->color == RED) {
					current->parent->parent->left->color = BLACK;
					current->parent->color = BLACK;
					current->parent->parent->color = RED;
					current = current->parent->parent;
				}
				else {
					if (current == current->parent->left) {
						current = current->parent;
						right_rotate_for_insert(current);
					}
					current->parent->color = BLACK;
					current->parent->parent->color = RED;
					left_rotate_for_insert(current->parent->parent);
				}
			}
			if (current == root) break;
		}
		root->color = BLACK;
	}

	void recovery_remove(node* current) {
		node* extra_pointer;
		while (current != root && current->color == BLACK) {
			if (current == current->parent->left) {
				extra_pointer = current->parent->right;
				if (extra_pointer->color == RED) {
					extra_pointer->color = BLACK;
					current->parent->color = RED;
					left_rotate_for_remove(current->parent);
					extra_pointer = current->parent->right;
				}
				if (extra_pointer->left->color == BLACK && extra_pointer->right->color == BLACK) {
					extra_pointer->color = RED;
					current = current->parent;
				}
				else {
					if (extra_pointer->right == NULL) {
						extra_pointer->right = new node;
						extra_pointer->right->color = BLACK;
					}
					if (extra_pointer->right->color == BLACK) {
						extra_pointer->left->color = BLACK;
						extra_pointer->color = RED;
						right_rotate_for_remove(extra_pointer);
						extra_pointer = current->parent->right;
					}
					extra_pointer->color = current->parent->color;
					current->parent->color = BLACK;
					extra_pointer->right->color = BLACK;
					left_rotate_for_remove(current->parent);
					current = root;
				}
			}
			else {
				extra_pointer = current->parent->left;
				if (extra_pointer->color == RED) {
					extra_pointer->color = BLACK;
					current->parent->color = RED;
					right_rotate_for_remove(current->parent);
					extra_pointer = current->parent->left;
				}

				if (extra_pointer->right->color == BLACK && extra_pointer->left->color == BLACK) {
					extra_pointer->color = RED;
					current = current->parent;
				}
				else {
					if (extra_pointer->left == NULL) {
						extra_pointer->left = new node;
						extra_pointer->left->color = BLACK;
					}
					if (extra_pointer->left->color == BLACK) {
						extra_pointer->right->color = BLACK;
						extra_pointer->color = RED;
						left_rotate_for_remove(extra_pointer);
						extra_pointer = current->parent->left;
					}

					extra_pointer->color = current->parent->color;
					current->parent->color = BLACK;
					extra_pointer->left->color = BLACK;
					right_rotate_for_remove(current->parent);
					current = root;
				}
			}
		}
		current->color = BLACK;

	}

	//print
	void get_values() {
		if (size == 0) {
			throw out_of_range("No more elements");
		}
		Queue queue;
		queue.push(root->elem);
		bool verification = false;
		while (!queue.Empty()) {
			node* current;
			int temp = queue.pop();
			if (verification == false) {
				current = root;
				verification = true;
			}
			current = root;
			if (temp != 0) {
				while (current->elem != temp) {
					if (temp < current->elem) {
						current = current->left;
					}
					if (temp > current->elem) {
						current = current->right;
					}
				}
				if (current->left != NULL) {
					queue.push(current->left->elem);
				}
				if (current->right != NULL) {
					queue.push(current->right->elem);
				}

				cout << temp << " ";
			}
		}
		tail = root;
	}

	void get_keys() {
		if (size == 0) {
			throw out_of_range("No more elements");
		}
		Queue queue_key, queue_value;
		queue_value.push(root->elem);
		queue_key.push(root->key);
		bool verification = false;
		while (!queue_value.Empty()) {
			node* current;
			int temp = queue_value.pop();
			if (verification == false) {
				current = root;
				verification = true;
			}
			current = root;
			if (temp != 0) {
				while (current->elem != temp) {
					if (temp < current->elem) {
						current = current->left;
					}
					if (temp > current->elem) {
						current = current->right;
					}
				}
				if (current->left != NULL) {
					queue_value.push(current->left->elem);
					queue_key.push(current->left->key);
				}
				if (current->right != NULL) {
					queue_value.push(current->right->elem);
					queue_key.push(current->right->key);
				}
			}
		}
		queue_key.print();
		tail = root;
	}

	void print() {
		cout << "Keys:";
		get_keys();
		cout << endl;
		cout << "Values:";
		get_values();
		cout << endl;
	}

	//clear
	void remove_one_elem(int elem) {
		if (root == NULL) {
			throw invalid_argument("List is empty");
		}
		else {
			//If an element has no leaves or both
			node* current = tail;
			if (elem == current->elem) {
				if ((current->left == NULL) && (current->right == NULL)) { //If an item has no leaves
					current = NULL;
					tail = root;
					size--;
					return;
				}
				else {
					if ((root->right == NULL) && (root->left != NULL)) {
						node* extra_pointer = root;
						root = root->left;
						size--;
						tail = root;
						delete extra_pointer;
						return;
					}
					node* extra_pointer = current;
					node* remove_elem = current;
					extra_pointer = extra_pointer->right;
					int min_elem = extra_pointer->elem;
					while (extra_pointer->left != NULL) {
						current = extra_pointer;
						extra_pointer = extra_pointer->left;
						if (extra_pointer->left == NULL) {
							min_elem = extra_pointer->elem;
							break;
						}
					}
					if ((root->right == NULL) && (root->left == NULL)) {
						delete root;
						root = NULL;
						size--;
						return;
					}

					if (current == root) {
						current->elem = extra_pointer->elem;
						current->right = extra_pointer->right;
						extra_pointer->right = NULL;
						tail = root;
						size--;
						return;
					}
					if ((extra_pointer->right != NULL) && (extra_pointer->left == NULL)) {
						current->left = extra_pointer->right;
						delete extra_pointer->right;
						current->left->right = NULL;
						remove_elem->elem = min_elem;
						tail = root;
						size--;
						return;
					}
					else {
						remove_elem->elem = min_elem;
						delete extra_pointer;
						current->left = NULL;
						tail = root;
						size--;
						return;
					}
				}
			}
			else {
				if ((elem == root->elem) && (root->right == NULL)) {
					current = root;
					root = root->left;
					delete current;
					size--;
					return;
				}
				if ((elem == root->elem) && (root->left == NULL)) {
					current = root;
					root = root->right;
					delete current;
					size--;
					return;
				}
				//4 cases (2 straight and 2 zig-zag)
				if (current->left != NULL) {
					if (elem == current->left->elem) {
						if ((current->left->left == NULL) && (current->left->right != NULL)) {
							node* extra_pointer = current->left;
							current->left = extra_pointer->right;
							delete extra_pointer;
							tail = root;
							size--;
							return;
						}
						if ((current->left->left != NULL) && (current->left->right == NULL)) {
							node* extra_pointer = current->left;
							current->left = extra_pointer->left;
							delete extra_pointer;
							tail = root;
							size--;
							return;
						}
					}
				}
				if (current->right != NULL) {
					if (elem == current->right->elem) {
						if ((current->right->left == NULL) && (current->right->right != NULL)) {
							node* extra_pointer = current->right;
							current->right = extra_pointer->right;
							delete extra_pointer;
							tail = root;
							size--;
							return;
						}
						if ((current->right->left != NULL) && (current->right->right == NULL)) {
							node* extra_pointer = current->right;
							current->right = extra_pointer->left;
							delete extra_pointer;
							tail = root;
							size--;
							return;
						}
					}
				}
				if ((current->right == NULL) && (current->left == NULL)) {
					throw invalid_argument("Element doesn't exist");
				}
				if (elem > current->elem) {
					current = current->right;
					tail = current;
				}
				if (elem < current->elem) {
					current = current->left;
					tail = current;
				}
				remove_one_elem(elem);
			}
		}
	}

	void clear() {
		while (size != 0) {
			remove_one_elem(root->elem);
		}
	}

};
