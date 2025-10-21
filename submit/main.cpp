#include <iostream>
#include <stack>

using namespace std;

// Node
class Node {
public:
	int key;
	Node* left;
	Node* right;
	int height;
	Node(int key=0, Node* left=nullptr, Node* right=nullptr, int height=0) \
		: key(key), left(left), right(right), height(height) {}
};

// Node 생성하는 함수
Node* getNode() {
	return new Node();
}

class BST {
public:
	Node* root_;
	BST(Node* root_ = nullptr) : root_(root_) {}

	// 트리의 높이
	int height(BST T) {
		return T.root_->height;
	}

	int size(Node* T) {
		if (T == nullptr) { return 0; }
		return size(T->left) + 1 + size(T->right);
	}
	// 트리의 노드의 개수
	int size(BST T) {
		return size(T.root_);
	}

	Node* minNode(Node* T) {
		Node* p = T;
		while (p->left != nullptr) {
			p = p->left;
		}
		return p;
	}
	// 트리 중 키 값이 가장 작은 노드
	Node* minNode(BST T) {
		return minNode(T.root_);
	}

	Node* maxNode(Node* T) {
		Node* p = T;
		while (p->right != nullptr) {
			p = p->right;
		}
		return p;
	}
	// 트리 중 키 값이 가장 큰 노드
	Node* maxNode(BST T) {
		return maxNode(T.root_);
	}

	bool insertBST(BST& T, int newKey) {
		Node* q = nullptr;	// p의 부모노드
		Node* p = T.root_;	// position
		stack<Node*> stack;

		while (p != nullptr) {	// 현재 노드가 None이 아니라면
			if (newKey == p->key) { return false; } // already exists
			q = p; // q가 position을 가리킴, p는 다음 노드로 이동할 거라 이동하기 전에 현 위치를 부모노드로 가리켜야하기 때문
			stack.push(q);	// q를 저장하는 이유는 p는 어짜피 leaf node일거라 height=0이기 때문, height 값이 바뀌는건 q만 해당
			// 현재 노드의 key 값에 따라서 p가 왼쪽, 오른쪽으로 감
			if (newKey < p->key) { p = p->left; }
			else { p = p->right; }
		}

		// 현재 노드가 None이므로 노드 하나 새로 만들어서 넣어야한다
		Node* newNode = getNode();
		// newNode.left = nullptr
		// newNode.right = nullptr
		newNode->key = newKey;


		if (T.root_ == nullptr) { T.root_ = newNode; }	// 아무 것도 없을때 삽입했다면
		// while 문 빠져나왔을 때의 상황: 삽입 위치는 p 위치, p 위치 접근하려면 부모노드인 q를 통해 접근해야 함
		else if (newKey < q->key) { q->left = newNode; }
		else { q->right = newNode; }

		// 모든 노드 height 계산
		// stack에 저장되어 있는건 삽입된 노드 p 위치, leaf node의 부모 노드들
		while (!stack.empty()) {
			q = stack.top();	// 가장 최근이 삽입된 노드 위치로부터 가장 가까운 부모노드
			stack.pop();
			Node* left = q->left;
			Node* right = q->right;
			if (left != nullptr && right != nullptr) {	// 자식 노드가 모두 존재한다면
				// height가 큰 쪽의 값에 1 더한거
				if (height(BST(left)) < height(BST(right))) { q->height = 1 + height(BST(right)); }
				else { q->height = 1 + height(BST(left)); }
			}
			else if (q->left == nullptr) { q->height = 1 + height(BST(q->right)); }	// 오른쪽 자식 노드만 있다면
			else { q->height = 1 + height(BST(q->left)); }	// 왼쪽 자식 노드만 있다면, 자식 노드가 없는 상황은 고려 할 필요X
		}
		
		// 키가 정상적으로 삽입되면 true 반환
		return true;
	}

	Node* eraseBST(BST &T, int deleteKey) {
		Node* q = nullptr;	// q의 부모노드
		Node* p = T.root_;	// position
		stack<Node*> stack;
		

		while (p != nullptr && deleteKey != p->key) {	// 현재노드가 None이 아니고 삭제할 노드가 현재 노드가 아닐때 까지
			q = p;	// p는 다음 노드로 움직이므로 q에 현재 위치를 저장
			stack.push(q);

			// 삭제할 노드를 찾아 p가 이동
			if (deleteKey < p->key) { p = p->left; }
			else { p = p->right; }
		}
		
		if (p == nullptr) { return nullptr; } // was not found
		

		// case if degree of p == 2
		if (p->left != nullptr && p->right != nullptr) {
			stack.push(p);
			Node* tempNode = p;

			if (height(BST(p->left)) < height(BST(p->right))) {
				// p->right의 minNode로 이동
				Node* r = minNode(BST(p->right));
				p = p->right;
				while (p != r) {
					stack.push(p);
					p = p->left;
				}
			}
			else if (height(BST(p->left)) > height(BST(p->right))) {
				// p->left의 maxNode로 이동
				Node* r = maxNode(p->left);
				p = p->left;
				while (p != r) {
					stack.push(p);
					p = p->right;
				}
			}
			else {	// 왼쪽 오른쪽 모두 높이가 같다면
				// 노드의 개수가 더 많은 쪽으로 이동
				if (size(BST(p->left)) < size(BST(p->right))) {
					// p->right의 minNode로 이동
					Node* r = minNode(BST(p->right));
					p = p->right;
					while (p != r) {
						stack.push(p);
						p = p->left;
					}
				}
				else {
					// p->left의 maxNode로 이동
					Node* r = maxNode(p->left);
					p = p->left;
					while (p != r) {
						stack.push(p);
						p = p->right;
					}
				}
			}

			tempNode->key = p->key;
			q = stack.top();
		}

		// now degree of p is 0 or 1
		// delete p from T
		if (p->left == nullptr && p->right == nullptr) { // case of degree 0
			if (q == nullptr) { T.root_ = nullptr; } // case of root
			else if (q->left == p) { q->left = nullptr; }
			else { q->right = nullptr; }
		}
		else { // case of degree 1
			if (p->left != nullptr) {
				if (q == nullptr) { T.root_ = T.root_->left; } // case of root
				else if (q->left == p) { q->left = p->left; }
				else { q->right = p->left; }
			}
			else {
				if (q == nullptr) { T.root_ = T.root_->right; } // case of root
				else if (q->left == p) { q->left = p->right; }
				else { q->right = p->right; }
			}
		}

		delete p;

		while (!stack.empty()) {
			q = stack.top();
			stack.pop();
			Node* left = q->left;
			Node* right = q->right;
			if (left != nullptr && right != nullptr) {	// 자식 노드가 모두 존재한다면
				// height가 큰 쪽의 값에 1 더한거
				if (height(BST(left)) < height(BST(right))) { q->height = 1 + height(BST(right)); }
				else { q->height = 1 + height(BST(left)); }
			}
			// 자식 노드가 원래 있었는데 삭제 연산 후 자식 노드가 모두 없어진 경우 존재
			else if (left == nullptr && right == nullptr) { q->height = 0; }
			// 자식노드가 한 쪽에만 존재할 때
			else if (q->left == nullptr) { q->height = 1 + height(BST(q->right)); }
			else { q->height = 1 + height(BST(q->left)); }

		}

		// 키가 정상적으로 삭제되면 삭제한 노드의 부모 노드 반환
		// Root 노드 삭제를 했다면 q == nullptr 이므로 예외처리
		return q;
	}

	Node* inOrder(Node* T) {
		if (T != nullptr) {
			cout << '<';
			if (T->left != nullptr) { inOrder(T->left); }
			cout << ' ';
			cout << T->key;
			cout << ' ';
			if (T->right != nullptr) { inOrder(T->right); }
			cout << '>';
		}

		return T;
	}

	void inOrder(BST T) {
		inOrder(T.root_);
	}

	Node* clear(Node* &T) {
		if (T == nullptr) { return nullptr; }
		clear(T->left);
		clear(T->right);
		delete T;
		return nullptr;
	}

	void clear(BST &T) {
		clear(T.root_);
	}
};

int main() {
	char command;
	int key;
	BST root;

	while (cin >> command >> key) {
		if (command == 'i') {
			if (root.insertBST(root, key) == false) { cout << "i " << key << ": The key already exists\n"; }
			else { root.inOrder(root); cout << '\n'; }
		}
		else {
			// Root 노드를 지운다고 한다면
			// 이때는 정상적으로 eraseBST() 호출되어도 nullptr 반환되므로 예외처리 해야한다
			if (root.root_ != nullptr && key == root.root_->key) {
				root.eraseBST(root, key);
				root.inOrder(root); cout << '\n';
			}
			// 그게 아닌데 nullptr이 반환됐다면 not exist
			else if (root.eraseBST(root, key) == nullptr) {
				cout << "d " << key << ": The key does not exist\n";
			}
			else { root.inOrder(root); cout << '\n'; }
		}
	}

	root.clear(root);
	return 0;
}
