/**
	Queue implementation
	Iterator pattern
	Rasul Kerimov (CoderINusE) 
*/
#ifndef __QUEUE_S__
#define __QUEUE_S__

#include <stdlib.h>
#include <exception>
#include <iostream>

namespace alg {
	template <typename T>
	class Queue {
		class node {
			public:
				node(const T& val_) : next(NULL), value(val_) {}
				T& getVal() {return value;}
				node* next;
			private:
				T value;
		};

		private:	
			node *head, *tail;
			int size_;
		public:
			Queue() : head(NULL), tail(NULL), size_(0) {};
			~Queue() {
				__destruct(head);
			} 
			Queue& operator=(Queue queuet) {
				__destruct(head);
				head = tail = NULL;
				swap(head, queuet.head); //Copy-Swap idiom
				swap(head, queuet.tail);
				swap(size_, queuet.size_); // 
				return *this; 
			}
			void pushBack(const T& value) {
				if(head == NULL) {
					head = new node(value);
					tail = head;
				}
				else {
					node *p = new node(value);
					tail->next = p;
					tail = p;
				}
				size_ += 1;
			}
			T popFront() {
				if(head == NULL) {
					throw std::out_of_range("Queue is empty");
				}
				else {
					node* p = head;
					head = head->next;
					T value = p->getVal();
					delete p;
					size_ -= 1;
					return value;
				}
			}
			int size() { return size_; }

			void empty() {
				__destruct(head);
				size_ = 0;
			}
			T& front() {
				return head->getVal();
			}
			T& back() {
				return tail->getVal();
			}
			// bug fix: iterator tag
			class Iterator {
				public:
					Iterator(node *p) : node_(p) {}
					~Iterator() { delete node_; }
					Iterator& operator=(const Iterator& other) {
						delete node_;
						swap(node_, other.node_);
						return (*this);
					}
					bool operator==(const Iterator& other) {
						return (node_ == other.node_);
					}
					bool operator!=(const Iterator& other) {
         				return(node_ != other.node_);
      				}
					Iterator& operator++() { //prefix
						if(node_ != NULL) {
							node_ = node_->next;
						}
						return (*this);
					}
					Iterator& operator++(int) { //postfix
						Iterator tmp(*this);
						++(*this);
						return tmp;
					}
					T& operator*() {
						return node_->getVal();
					}
					T* operator->() {
						return (&*(Queue<T>::Iterator)*this);
					}
					

				private:
					node* node_;
			};

			Iterator begin() {
				return Iterator(head);
			}
			Iterator end() {
				return Iterator(NULL);
			}

		private:
			void __destruct(node *n) {
				if(n == NULL) return;
				__destruct(n->next);
				delete n;
			}
	};
} 


#endif