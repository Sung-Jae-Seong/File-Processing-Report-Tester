#include <iostream>
#include <stack>

template <class _Tp> class Node;
template <class _Tp> class BST;

/*
* 아래는 반드시 사용해야하는 Node 클래스입니다.
* height, size를 제외한 멤버 변수는 추가, 삭제 및 변경이 불가능합니다.
*/
template <class _Tp>
class Node {
	public: // Member types
		typedef _Tp					__key_type;
		typedef Node<__key_type>*	__node_pointer_type;
	
	public: // Member variables
		__key_type			__key_;
		__node_pointer_type	__left_;
		__node_pointer_type	__right_;
	
	public: // Constructor
		Node(): __key_(__key_type()), __left_(nullptr), __right_(nullptr) {}
		Node(const __key_type& key): __key_(key), __left_(nullptr), __right_(nullptr) {}

	/*
	* 아래는 inorder traversal을 대체할 수 있는 operator<< 입니다.
	* 반드시 아래의 함수를 사용해야할 필요는 없습니다.
	*/
};

/*
* 아래 함수들의 설계 방식은 Tree와 Node의 구동부를 구현하기 위해 추천드리는 설계 방식입니다.
* 반드시 아래의 설계 방식을 따라야 하는 것은 아닙니다.
*/

template <class _NodePtr>
unsigned __height(_NodePtr __x) {
	if(__x == nullptr) return 0;
	return std::max(__height(__x->__left_), __height(__x->__right_))+1;
	// write your own code here
}

template <class _NodePtr>
unsigned __size(_NodePtr __x) {
	if(__x == nullptr) return 0;
	return __size(__x->__left_) + __size(__x->__right_) + 1;
	// write your own code here
}

/*
* 아래 함수는 minNode와 동일한 역할을 하는 함수입니다.
* 매개 변수 타입과 반환 타입을 참조 타입으로 수정하셔도 무방합니다.
*/
template <class _NodePtr>
_NodePtr __tree_min(_NodePtr __x, _NodePtr parent = nullptr) {
	if(__x->__left_==nullptr) return parent;
	return __tree_min(__x->__left_, __x);
	// write your own code here
}

/*
* 아래 함수는 maxNode와 동일한 역할을 하는 함수입니다.
* 매개 변수 타입과 반환 타입을 참조 타입으로 수정하셔도 무방합니다.
*/
template <class _NodePtr>
_NodePtr __tree_max(_NodePtr __x, _NodePtr parent = nullptr) {
	if(__x->__right_==nullptr) return parent;
	return __tree_max(__x->__right_, __x);
	// write your own code here
}

/*
* PDF에 명시되어있는 출력 형식에 유의하세요.
* ❗️잘못된 출력 형식은 0점 처리됩니다.❗️
*/
template <class _NodePtr>
void __inorder(_NodePtr __x) {
	if(__x == nullptr) return;
	std::cout << '<';
	__inorder(__x->__left_);
	std::cout << " " << __x->__key_ << " ";
	__inorder(__x->__right_);
	std::cout << '>';
	// write your own code here
}

/*
* 아래 함수는 삽입된 노드의 위치와 삽입 여부를 반환합니다.
* 예시) 이미 같은 키 값이 존재하는 경우: return std::pair<_NodePtr, bool>(__p, false);
*/
template <class _NodePtr, class _Tp>
std::pair<_NodePtr, bool> __insertBST(_NodePtr& __root, const _Tp& key) { // ???
	if (__root == nullptr){
		__root = new Node<_Tp>(key);
		return std::pair<_NodePtr, bool>(__root, true);
	}
	else if(__root->__key_ == key) return std::pair<_NodePtr, bool>(nullptr, false);
	else if(__root->__key_ > key){
		if(__root->__left_ == nullptr){
			__root->__left_ = new Node<_Tp>(key);
			return std::pair<_NodePtr, bool>(__root->__left_, true);
		}
		return __insertBST(__root->__left_, key);
	}
	else if(__root->__key_ < key){
		if(__root->__right_ == nullptr){
			__root->__right_ = new Node<_Tp>(key);
			return std::pair<_NodePtr, bool>(__root->__right_, true);
		}
		return __insertBST(__root->__right_, key);
	}
	// write your own code here
}


template <class _NodePtr>
_NodePtr __erase_left_subtree(_NodePtr& root){
	_NodePtr max_node_parent = __tree_max(root->__left_); //왼쪽 서브트리의 최대 노드의 부모를 찾음
	if(max_node_parent == nullptr){ // 부모가 nullptr이면 root->left가 최대라는 뜻 
		_NodePtr max_node = root->__left_; // 최대 노드
		root->__key_ = max_node->__key_; // 최대 노드의 키 복사
		root->__left_ = max_node->__left_; // 최대 노드의 right은 존재하지 않으므로 left를 복사
		return max_node;
	}
	else {
		_NodePtr max_node = max_node_parent->__right_; // 최대 노드는 부모 노드의 오른쪽 값
		root->__key_ = max_node->__key_; // 최대값을 root에 복사하기
		max_node_parent->__right_ = max_node->__left_; // 최대 노드의 right는 존재하지 않으므로 left를 복사
		return max_node; // 해당 노드 삭제
	}
}

template <class _NodePtr>
_NodePtr __erase_right_subtree(_NodePtr& root) {
    _NodePtr min_node_parent = __tree_min(root->__right_); // 오른쪽 서브트리의 최소 노드의 부모를 찾음
    if (min_node_parent == nullptr) { // 부모가 nullptr이면 root->right가 최소 노드라는 뜻
        _NodePtr min_node = root->__right_; // 최소 노드
        root->__key_ = min_node->__key_; // 최소 노드의 키 복사
        root->__right_ = min_node->__right_; // 최소 노드의 left는 존재하지 않으므로 right를 복사
        return min_node; // 해당 노드 삭제
    } 
    else {
        _NodePtr min_node = min_node_parent->__left_; // 최소 노드는 부모 노드의 왼쪽 값
        root->__key_ = min_node->__key_; // 최소값을 root에 복사
        min_node_parent->__left_ = min_node->__right_; // 최소 노드의 left는 존재하지 않으므로 right를 복사
        return min_node; // 해당 노드 삭제
    }
}


/*
* Root node가 삭제되는 경우를 고려하여 매개 변수 "__root" 를 참조 타입으로 받도록 설계하였습니다.
* "__root = 대체될 노드"로 BST class의 멤버 변수 __root_ 값을 변경할 수 있습니다.
* 현재 로직에서 존재하지 않는 key를 erase하려고 할 때, nullptr을 반환해야 정상 작동하도록 설계되어 있습니다.
*/
template <class _NodePtr, class _Tp>
_NodePtr __eraseBST(_NodePtr& __root, const _Tp& key) {
	if(__root==nullptr) return nullptr;
	else if(__root->__key_ == key) {
		if(__root->__left_==nullptr&&__root->__right_==nullptr){
			_NodePtr temp = __root;
        	__root = nullptr;
        	return temp;
		}
		else if(__root->__left_==nullptr) return __erase_right_subtree(__root);
		else if(__root->__right_==nullptr) return __erase_left_subtree(__root);
		// degree가 2인 경우
		unsigned h_left = __height(__root->__left_);
		unsigned h_right = __height(__root->__right_);
		if(h_left > h_right) return __erase_left_subtree(__root);
		else if(h_left < h_right) return __erase_right_subtree(__root);
		// 양쪽 h가 같은 경우
		unsigned s_left = __size(__root->__left_);
		unsigned s_right = __size(__root->__right_);
		if(s_left >= s_right) return __erase_left_subtree(__root);
		else if(s_left < s_right) return __erase_right_subtree(__root);
	}
	else if (__root->__key_ > key){
		if(__root->__left_ == nullptr) return nullptr;
		return __eraseBST(__root->__left_, key);
	}
	else if (__root->__key_ < key){
		if(__root->__right_ == nullptr) return nullptr;
		return __eraseBST(__root->__right_, key);
	}
	// write your own code here
}

// Dangling pointer를 방지하기 위해 __x를 참조 타입으로 받도록 설계하였습니다.
template <class _NodePtr>
void __clear(_NodePtr& __x) {
	if(__x == nullptr) return;
	__clear(__x->__left_);
	__clear(__x->__right_);
	delete __x;
	__x = nullptr;
	return ;
	// write your own code here
}

// 아래는 반드시 사용해야하는 BST 클래스입니다.
template <class _Tp>
class BST {
	public: // Member types
		typedef _Tp						key_type;
		typedef std::size_t				size_type;
		typedef Node<key_type>*			pointer;
		typedef const Node<key_type>*	const_pointer;
	
	private: // Member variables
		pointer	__root_;
	
	public: // Constructor
		BST(): __root_(nullptr) {}
	
	/*
	* 아래는 반드시 구현해야하는 부분입니다.
	* 위의 추천드리는 설계 방식을 이용하여 구현하는 것을 추천합니다.
	* 추전드리는 설계 방식을 이용하지 않고 새로 구현하셔도 무방합니다.
	*/

	public: // Capacity
		size_type height() const {
			// use __height or write your own code here
			return __height(__root_);
		}

		size_type size() const {
			// use __size or write your own code here
			return __size(__root_);
		}
	
	public: // Lookup
		void inorder() const {
			// use __inorder or write your own code here
			__inorder(__root_);
			std::cout << std::endl;
		}
		
	public: // Modifier
		std::pair<const_pointer, bool> insert(const key_type& key) {
			// use __insertBST or write your own code here
			return __insertBST(__root_, key);
		}

		const_pointer erase(const key_type& key) {
			// use __eraseBST or write your own code here
			pointer __r = __eraseBST(__root_, key);
			if (__r == nullptr) return nullptr;
			if (__r == __root_) __root_ = nullptr;
			// Client still needs to destruct/deallocate it
			// Or memory leak will occur
			delete __r;
			return __r;
		}

		void clear() {
			// use __clear or write your own code here
			__clear(__root_);
		}
	
	/*
	* 아래는 inorder traversal을 대체할 수 있는 operator<< 입니다.
	* 반드시 아래의 함수를 사용해야할 필요는 없습니다.
	*/
};

/*
* 아래는 추천드리는 main 함수의 예시입니다.
* 반드시 아래의 main 함수를 사용해야할 필요는 없습니다.
* ❗️새로 구현하실 경우, 출력 형식에 주의하세요.❗️
*/
int main(int argc, char **argv) {
	BST<int>	tree;
	char		command;
	int			key;

	while (std::cin >> command >> key) {
		switch ((int)command) {
			case (int)'i':
				if (tree.insert(key).second == false) {
					std::cerr << "i " << key << ": The key already exists" << std::endl;
					continue;
				}
				tree.inorder();
				break;
			case (int)'d':
				if (tree.erase(key) == nullptr) {
					std::cerr << "d " << key << ": The key does not exist" << std::endl;
					continue;
				}
				tree.inorder();
				break;
			default:
				std::cerr << "Invalid command: " << command << std::endl;
				return (1);
				break;
		}
	}

	// 프로그램 종료 전, 메모리 누수가 발생하지 않도록 할당받은 메모리를 반드시 해제해야 합니다.
	tree.clear();

	return (0);
}
