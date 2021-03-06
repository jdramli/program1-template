//List.cpp Program1

#include <iostream>
#include <cstdlib>
#include "List.h"
#include "Planet.h"


Node::Node(){
	this->next = NULL;
	this->prev = NULL;
}

Node::~Node(){
	 delete this->next;
	 delete this->prev;
	 delete this->planet;
}

List::List(){
	this->head = NULL;
	this->tail = NULL;
}


List::~List(){
	//might need to be populated
}



void List::insert(int index, Planet* planet){

	Node * temp_add = new Node();
	temp_add->planet = planet;

	if(head == NULL){
		head = temp_add;
		return;
	}

	int counter = 1;
	Node * current = head;
	while(counter < index){ //THIS LOOP IS DESIGNED TO APPEND TO THE TAIL AND RETURN -- IF THE INDEX IS OUT OF BOUNDS
		if(current->next == NULL){
			//append temp node to end of list and return out of the function.
			current->next = temp_add;
			temp_add->prev = current;
			temp_add->next = NULL;
			this->tail = temp_add;
			return;
		}
		current = current->next;
		counter++;
	}

	if(current->next == NULL){
		//temp_add is the new tail.
		current->next = temp_add;
		temp_add->next = NULL;
		temp_add->prev = current;
		tail = temp_add;

		return;
	}
	/*
	Node* temp_end = current->next;
	temp_add->next = temp_end;
	temp_add->prev = current;
	current->next = temp_add;
	temp_end->prev = temp_add;
	*/
	temp_add->next = current->next; // points addition to right side of insert
	current->next->prev = temp_add; //points the right side of current back at temp_add
	temp_add->prev = current;       //points the temp_add to the left side of insert (back at current)
	current->next = temp_add;      //points the current to the temp_add to finish the double link.
	//THE ORDER IS IMPORTANT -- DON'T BREAK THE LINK OF CURRENT->NEXT UNTIL CURRENT->NEXT->PREV IS POINTED BACKWARDS AT TEMP_ADD
	//made next_node after temp_add point back to temp_add

}

Planet* List::read(int index){

	if(head == NULL){ //This will check initially if the array is empty and therefore the index is out of bounds, and return NULL
		return NULL;
	}
	if(index == 0){ // This will make sure that we check index 0 first @ head, and return the head->planet if it is indeed valid and populated.  //we know head != NULL here because of above "if" statment.
		return head->planet;
	}

	int counter = 0; //might not need this if we iterate using current->data?
	Node * current = head;
	while(counter < index){
		if(current->next == NULL){ //This will stop iteration if the index is out of bounds
			return NULL;
		}
		current = current->next;
		counter++;
	}
	return current->planet;


}
bool List::remove(int index){
//This part handles if the head is NULL
	if(head == NULL){
		return false;
	}
//This part hndles if the head is the index AND the only memeber in the list
	int counter = 0;
	Node * current = this->head;
	if(index == 0){
		if(head->next == NULL){
			//TODO: finish these
			//delete head and underlying object?
			//make new head and point to null?
			return true;
		}
//This part handles if the head is the target and the node to the right is populated.
		//delete head underlying object to avoid memory leak, and point head to null
		delete head->planet;
		current = head->next;
		current->prev = NULL;
		//DELETE HEAD data -- delete this->head->planet; //?
		this->head = current;
		return true;
	}

//This part handles if the deletion is in the middle of the list	//AFter coding this -- we might only need this part and (if(head == NULL){}
	while(counter < index){
		current = current->next;
		counter++;
	}
	Node * temp_left = current->prev;
	Node * temp_right = current->next;
	delete current;
	temp_left->next = temp_right;
	temp_right->prev = temp_left;
	return true;

}
unsigned long List::size(){
	if(head == NULL){
			return 0;
	}
	long counter = 1; // if head->next == NULL then we won't enter the loop, and head will be the 1 element in the list
	Node * current = head;

	while(current->next !=NULL){
			current = current->next;
			counter++;
	}
	return counter;
}
