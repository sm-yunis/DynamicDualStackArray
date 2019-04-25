#ifndef DDS_H
#define DDS_H

#include <exception>
#include <iostream>
#include <string.h>
#include <algorithm>

template <typename T>
class Dynamic_dual_stack{
    private:
        T *stack_array;
		int initial_capacity;
		int array_capacity;
		int stack_size[2];

		void adjust_size(int);

   public:
		//Dynamic_dual_stack();
		Dynamic_dual_stack(int s=10);
		Dynamic_dual_stack(const Dynamic_dual_stack &);
		~Dynamic_dual_stack();

		int capacity() const;
		bool empty(int) const;
		int size(int) const;
		T top(int) const;

		void swap( Dynamic_dual_stack & );
		Dynamic_dual_stack &operator=( const Dynamic_dual_stack & );
		void push( int, T const & );
		T pop( int );
		void clear();  
   
};


template <typename T>
Dynamic_dual_stack<T>::Dynamic_dual_stack(int s){
	this->stack_size[0]=0;
	this->stack_size[1]=0;
	this->initial_capacity = s;
	this->array_capacity = this->initial_capacity;
	stack_array = new T[this->initial_capacity];
}

template<typename T>
Dynamic_dual_stack<T>::Dynamic_dual_stack(const Dynamic_dual_stack &obj){
	this->array_capacity = obj.array_capacity;
	this->initial_capacity = obj.initial_capacity;
	this->stack_array = new T[obj.array_capacity];

	for(int i = 0;i < 2;i++){
		this->stack_size[i] = obj.stack_size[i];
	}
	for(int i = 0;i < array_capacity;i++){
		this->stack_array[i] = obj.stack_array[i];
	}
}

template<typename T>
Dynamic_dual_stack<T>::~Dynamic_dual_stack(){
	delete[] stack_array;
}

template<typename T>
void Dynamic_dual_stack<T>::adjust_size(int action_code){

	T *temp;
	int half_size = this->array_capacity / 2;
	int double_size = this->array_capacity * 2;
	int no_elements = this->stack_size[0] + this->stack_size[1];

	if(action_code == 0 && half_size <= this->initial_capacity){
		return;
	}
	else{
		if(action_code == 1){
			if(no_elements >= this->array_capacity){

				temp = new T[double_size];

				for(int i = 0; i < this->stack_size[0] ;i++){
					temp[i] = this->stack_array[i];
				}

				for(int i = 0; i < this->stack_size[1] ;i++){
					temp[double_size - (1+i)] = this->stack_array[this->array_capacity - (1+i)];
				}

				this->array_capacity = double_size;	

			}
			else{
				return;
			}
		}
		else if(action_code == 0){

			if(no_elements <= (this->array_capacity/4)){
				temp = new T[half_size];

				for(int i = 0; i < this->stack_size[0] ;i++){
					temp[i] = this->stack_array[i];
				}

				for(int i = 0; i < this->stack_size[1]; i++){
					temp[half_size - (1+i)] = this->stack_array[this->array_capacity - (1+i)];
				}

				this->array_capacity = half_size;
			}
			else{
				return;
			}
			
		}
	}

	delete[] stack_array;
	stack_array = temp;
	
}

// exception classes
namespace iarg{
	class illegal_argument
	{
		private:
			char err_msg[50];
			int arr_wrong;
		public:
			illegal_argument(int arr_wrong){
				strcpy(this->err_msg,"Illegal Argument Used");
				this->arr_wrong = arr_wrong;
			}
			void show_message(){
				std::cerr << err_msg << " : " << arr_wrong;
				std::cerr << " ,use 0/1 to identify stack." <<  std::endl;
			}	
	};

	class stk_underflow{
		private:
			char err_msg[50];
		public:
			stk_underflow(){
				strcpy(err_msg,"Stack Underflow! The Stack is empty.");
			}
			void show_message(){
				std::cerr << err_msg << std::endl;
			}
	};
}



template<typename T>
 int Dynamic_dual_stack<T>::capacity() const{
	 return this->array_capacity;
 }

template<typename T>
int Dynamic_dual_stack<T>::size(int arr) const{
	
	try
	{
		if(!(arr == 0 || arr == 1))
		  throw iarg::illegal_argument(arr);
		else{
			return this->stack_size[arr];
		}	
	}
	catch(iarg::illegal_argument exp)
	{
		exp.show_message();
	}
}

 template<typename T>
 bool Dynamic_dual_stack<T>::empty(int arr) const{
	 
	 try
	 {
		if(!(arr == 0 || arr == 1))
		  throw iarg::illegal_argument(arr);
		else if(this->size(arr) <= 0){
			return true;	
		}
		else{
			return false;
		}
	 }
	 catch(iarg::illegal_argument exp)
	 {
		 exp.show_message();
	 }
 }


template<typename T>
T Dynamic_dual_stack<T>::top(int arr) const{
	try{
		if(!(arr == 0 || arr == 1))
			throw iarg::illegal_argument(arr);
		else if(this->stack_size[arr] <= 0)
			throw iarg::stk_underflow(); 
		else{
			int top_index;
			if(arr == 0)
				top_index = this->stack_size[0] - 1;
			else if(arr == 1)
				top_index = this->array_capacity - this->stack_size[1];
			else
				throw iarg::illegal_argument(arr);

			return this->stack_array[top_index];	
		}
	}
	catch(iarg::illegal_argument exp){
		exp.show_message();
	}
	catch(iarg::stk_underflow exp){
		exp.show_message();
	}
}



// mutators

template<typename T>
void Dynamic_dual_stack<T>::swap(Dynamic_dual_stack &obj){

	std::swap( initial_capacity, obj.initial_capacity );
	std::swap( array_capacity, obj.array_capacity );
	std::swap( stack_array, obj.stack_array );
	std::swap( stack_size[0], obj.stack_size[0] );
	std::swap( stack_size[1], obj.stack_size[1] );

}

template <typename T>
Dynamic_dual_stack<T> &Dynamic_dual_stack<T>::operator=(Dynamic_dual_stack<T> const &rhs) {

	Dynamic_dual_stack<T> copy(rhs);
	swap(copy);
	return *this;
}


// push and pop

template<typename T>
void Dynamic_dual_stack<T>::push(int arr, T const &new_obj){
	try{
		if(!(arr == 0 || arr == 1))
			throw iarg::illegal_argument(arr);
		else{
			if(arr == 0){
				int top_index;
				this->adjust_size(1);
				top_index = this->stack_size[0] - 1;
				this->stack_array[top_index + 1] = new_obj;
				this->stack_size[0]++;	
			}
			else if(arr == 1){
				int top_index;
				this->adjust_size(1);
				top_index = this->array_capacity - this->stack_size[1];
				this->stack_array[top_index - 1] = new_obj;
				this->stack_size[1]++;
			}
			else{
				throw iarg::illegal_argument(arr);
			}
		}
	}
	catch(iarg::illegal_argument exp){
		exp.show_message();
	}
}

template<typename T>
T Dynamic_dual_stack<T>::pop(int arr){

	T poped_value;

	try{
		
		if(!(arr == 0 || arr == 1))
			throw iarg::illegal_argument(arr);
		else if(this->stack_size[arr] <= 0)
			throw iarg::stk_underflow();
		else{
			int top_index;
			if(arr == 0){
				top_index = this->stack_size[0] - 1;
				poped_value = this->stack_array[top_index];
				this->stack_size[0]--;
				this->adjust_size(0);
			}
			else if(arr == 1){
				top_index = this->array_capacity - this->stack_size[1];
				poped_value = this->stack_array[top_index];
				this->stack_size[1]--;
				this->adjust_size(0); 	
			}
			else{
				throw iarg::illegal_argument(arr);
			}

			return poped_value;
		}

	}
	catch(iarg::illegal_argument exp){
		exp.show_message();
	}
	catch(iarg::stk_underflow exp){
		exp.show_message();
	}
	
}


template<typename T>
void Dynamic_dual_stack<T>::clear(){

	T *temp;
	temp = new T[this->initial_capacity];

	this->array_capacity = this->initial_capacity;
	this->stack_size[0] = 0;
	this->stack_size[1] = 0;

	delete[] stack_array;
	stack_array = temp;

}


#endif