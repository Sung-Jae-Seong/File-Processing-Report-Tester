/*
* File Processing Report 2024 - Binary Search Tree skeleton code in C/C++
*
* 본 Skeleton code는 구현에 도움을 주기 위해 작성된 코드입니다.
* ❗️본 Skeleton code는 과제의 요구 조건을 완전히 충족시키지 않을 수 있습니다.❗️
* ❗️최종 점수 산정은 과제 PDF에 명시된 요구 사항을 기준으로 이루어집니다.❗️
*
* 미리 말씀드리면, skeleton code가 다소 어려울 수 있습니다.
* C++ 스러운 코딩 스타일과 코드 설계 방식에 관한 고찰이 담겨있으니, 충분한 시간을 들여 분석해보시기 바랍니다.
* 또, 재사용성을 고려하여 설계된 코드인 만큼 처음에는 이해하기 어려울 수 있습니다.
* 이후 AVL-Tree, B-Tree 과제에서도 그대로 사용되니, 이번 BST에서 잘 이해하고 넘어가시길 바랍니다.
*
*/

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
	friend std::ostream& operator<<(std::ostream& os, const __node_pointer_type& np) {
		__inorder(np);
		return os;
		// write your own code here
	}
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
_NodePtr __tree_min(_NodePtr __x) {
	if(__x->__left_==nullptr) return __x;
	return __tree_min(__x->__left_);
	// write your own code here
}
/*
* 아래 함수는 maxNode와 동일한 역할을 하는 함수입니다.
* 매개 변수 타입과 반환 타입을 참조 타입으로 수정하셔도 무방합니다.
*/
template <class _NodePtr>
_NodePtr __tree_max(_NodePtr __x) {
	if(__x->__right_==nullptr) return __x;
	return __tree_max(__x->__right_);
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

template <class _NodePtr, class _Tp>
_NodePtr searchBST(_NodePtr __x, const _Tp& key) {
	if (__x == nullptr) return nullptr;
	if (__x->__key_ == key) return __x;
	return (key < __x->__key_) ? searchBST(__x->__left_, key):searchBST(__x->__right_, key);
}

template <class _NodePtr, class _Tp>
_NodePtr searchParent(_NodePtr __x, const _Tp& key) {
	_NodePtr q = nullptr;
	_NodePtr p = __x;
	while(p != nullptr){
		if(key == p->__key_) return q;
		q = p;
		if(key < p->__key_) p=p->__left_;
		else p=p->__right_;
	}
	return nullptr;
}

/*
* 아래 함수는 삽입된 노드의 위치와 삽입 여부를 반환합니다.
* 예시) 이미 같은 키 값이 존재하는 경우: return std::pair<_NodePtr, bool>(__p, false);
*/
template <class _NodePtr, class _Tp>
std::pair<_NodePtr, bool> __insertBST(_NodePtr& __root, const _Tp& key) {
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

/*
* Root node가 삭제되는 경우를 고려하여 매개 변수 "__root" 를 참조 타입으로 받도록 설계하였습니다.
* "__root = 대체될 노드"로 BST class의 멤버 변수 __root_ 값을 변경할 수 있습니다.
* 현재 로직에서 존재하지 않는 key를 erase하려고 할 때, nullptr을 반환해야 정상 작동하도록 설계되어 있습니다.
*/
template <class _NodePtr, class _Tp>
_NodePtr __eraseBST(_NodePtr& __root, const _Tp& key) {
	_NodePtr p = searchBST(__root, key);
	_NodePtr q = searchParent(__root, key);
	if (p==nullptr) return nullptr;
	else if (q==nullptr){ // 삭제하려는게 루트노드일 때
		if (p->__left_ == nullptr && p->__right_ == nullptr) {
			__root = nullptr;
			return p;
		} else if (p->__left_ == nullptr) {
			__root = p->__right_;
			return p;
		} else if (p->__right_ == nullptr) {
			__root = p->__left_;
			return p;
		} else {
			_NodePtr r;
			int flag;
			unsigned h_left = __height(p->__left_);
			unsigned h_right = __height(p->__right_);
			if (h_left > h_right) { r = __tree_max(p->__left_); flag = 0; }
			else if (h_left < h_right) { r = __tree_min(p->__right_); flag = 1; }
			else {
				unsigned s_left = __size(p->__left_);
				unsigned s_right = __size(p->__right_);
				if (s_left >= s_right) { r = __tree_max(p->__left_); flag = 0; }
				else { r = __tree_min(p->__right_); flag = 1; }
			}
			p->__key_ = r->__key_;
			if (flag) return __eraseBST(p->__right_, r->__key_);
			else return __eraseBST(p->__left_, r->__key_);
		}
	}
	else if(p->__left_==nullptr&&p->__right_==nullptr){ // p에 자식 노드가 없을 때
		if(q->__left_==p){
			q->__left_=nullptr;
			return p;
		}
		else{
			q->__right_=nullptr;
			return p;
		}
	}
	else if(p->__left_==nullptr){ // p에 오른쪽 서브트리만 있을 때
		if(q->__left_==p){
			q->__left_=p->__right_;
			return p;
		}
		else{
			q->__right_=p->__right_;
			return p;
		}

	}
	else if(p->__right_==nullptr){ // p에 왼쪽 서브트리만 있을 때
		if(q->__left_==p){
			q->__left_=p->__left_;
			return p;
		}
		else{
			q->__right_=p->__left_;
			return p;
		}
	}
	else{ // p에 왼쪽 오른쪽 서브트리가 있을 때 (degree가 2일 때)
		_NodePtr r;
		int flag; //0이면 왼쪽 1이면 오른쪽
		unsigned h_left = __height(__root->__left_);
		unsigned h_right = __height(__root->__right_);
		if(h_left > h_right) { r = __tree_max(p->__left_); flag = 0;}
		else if (h_left < h_right) { r = __tree_min(p->__right_); flag = 1;}
		else{
			unsigned s_left = __size(__root->__left_);
			unsigned s_right = __size(__root->__right_);
			if(s_left >= s_right) {r = __tree_max(p->__left_); flag = 0;}
			else if(s_left < s_right) {r = __tree_min(p->__right_); flag = 1;}
		}
		p->__key_=r->__key_;
		if(flag) return __eraseBST(p->__right_, r->__key_);
		else return __eraseBST(p->__left_, r->__key_);
	}
		
	// write your own code here
}

// Dangling pointer를 방지하기 위해 __x를 참조 타입으로 받도록 설계하였습니다.
template <class _NodePtr>
void __clear(_NodePtr& __x) {
	if (__x == nullptr)return;
	__clear(__x->__left_);
	__clear(__x->__right_);
	delete __x;
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
			if(__r==nullptr) return nullptr;
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
	friend std::ostream& operator<<(std::ostream& os, const BST& tree) {
		os << tree.__root_;
		return os;
	}
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
				break;
			case (int)'d':
				if (tree.erase(key) == nullptr) {
					std::cerr << "d " << key << ": The key does not exist" << std::endl;
					continue;
				}
				break;
			default:
				std::cerr << "Invalid command: " << command << std::endl;
				return (1);
				break;
		}
		std::cout << tree << std::endl;
	}

	// 프로그램 종료 전, 메모리 누수가 발생하지 않도록 할당받은 메모리를 반드시 해제해야 합니다.
	tree.clear();

	return (0);
}
