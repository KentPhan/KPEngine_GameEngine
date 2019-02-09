#pragma once
#include <iostream>
#include <cassert>

namespace KPEngine
{
	namespace Utils
	{
		/// <summary>
/// Node Class
/// </summary>
		template <class T>
		class Node
		{
		public:
			T  data;
			Node* next;
			Node(T pdata)
			{
				this->data = pdata;
			}
			~Node()
			{
				delete data;
			}
		};


		//template <class Type>
		//Node<Type>::Node(Type pdata)
		//{
		//	
		//}
		//
		//
		//template <class Type>
		//Node<Type>::~Node()
		//{
		//	
		//}




		/// <summary>
		/// My implementation of a singly linked list - Kent Phan
		/// </summary>
		template <class T>
		class List
		{
		public:

			List()
			{
				head = nullptr;
				size = 0;
			};

			~List()
			{
				if (head == nullptr)
					return;


				// Loop through and delete
				Node<T> * front = head;
				Node<T> * temp = nullptr;

				while (front->next != nullptr)
				{
					temp = front;
					front = front->next;
					delete temp;
				}
				delete front;
			};


			/// <summary>
			/// Adds the specified item.
			/// </summary>
			/// <param name="item">The item.</param>
			void Add(T item)
			{
				assert(item);

				if (head == nullptr)
				{
					head = new Node<T>(item);
					size++;
					return;
				}


				// Loop till finding next node taht needs to be filled
				Node<T> *currentNode = head;
				while (currentNode->next != nullptr)
				{
					currentNode = currentNode->next;
				}

				currentNode->next = new Node<T>(item);
				size++;
			};


			/// <summary>
			/// Removes the specified item.
			/// </summary>
			/// <param name="item">The item.</param>
			/// <returns>True if removal was a success. Otherwise false</returns>
			bool Remove(T item)
			{
				if (head == nullptr || item == NULL || item == nullptr)
					return false;

				Node<T> * previousNode = nullptr;
				Node<T> * currentNode = head;
				while (currentNode != nullptr)
				{
					if (currentNode->data == item)
					{
						if (previousNode == nullptr)
						{
							head = currentNode->next;
						}
						else
						{
							previousNode->next = currentNode->next;

						}
						delete currentNode;
						size--;
						return true;
					}
					previousNode = currentNode;
					currentNode = currentNode->next;
				}
				return false;
			}

			/// <summary>
			/// Gets the specified i.
			/// </summary>
			/// <param name="i">The i.</param>
			/// <returns></returns>
			T Get(int i) const
			{
				assert(i >= 0);

				if (head == nullptr)
					return nullptr;

				Node<T> * currentNode = head;
				int position = 0;
				while (currentNode != nullptr)
				{
					if (position == i)
					{
						return currentNode->data;
					}
					currentNode = currentNode->next;
					position++;
				}

				// Item not found
				return nullptr;
			}


			/// <summary>
			/// Prints this instance.
			/// </summary>
			void Print() const
			{
				if (head == nullptr)
				{
					std::cout << "List is Empty\n";
					return;
				}

				Node<T> * currentNode = head;

				while (currentNode != nullptr)
				{
					std::cout << " [" << currentNode->data << "] ";
					currentNode = currentNode->next;
				}
				std::cout << "\n";
			}


			/// <summary>
			/// Gets length of list
			/// </summary>
			/// <returns></returns>
			int length() const
			{
				return this->size;
			}

		private:

			int size;
			Node<T> *head;
		};
	}
}






