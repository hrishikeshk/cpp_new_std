#ifndef LIST_HEADERS
#define LIST_HEADERS

template<typename T>
struct Node{
  const T& m_data;
  Node* m_next;
  explicit Node(const T& t): m_data(t), m_next(nullptr){

  }
  Node(const Node&) = delete;
  Node(const Node&&) = delete;
};

template<typename T>
struct List{
  Node<T>* m_head;
  explicit List(Node<T>* h): m_head(h){
  }
};


#endif

