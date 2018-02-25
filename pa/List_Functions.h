#include "List.h"

template<typename T>
const T* kth_to_last(List<T>& l, int k){
  Node<T>* h = l.m_head;
  for(int i = 0; i < k; ++i){
    if(h == nullptr) return nullptr;
    h = h->m_next;
  }
  Node<T>* c = l.m_head;
  while(h->m_next != nullptr){
    h = h->m_next;
    c = c->m_next;
  }
  return &(c->m_data);
}
