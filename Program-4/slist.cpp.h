#include "slist.h"

template<class Object>
SList<Object>::SList() {
	init();
}

template<class Object>
SList<Object>::SList(const SList &rhs) {
	init();
	*this = rhs;                                   // then assign rhs to this.
}

template<class Object>
void SList<Object>::init() {
	for (int i = 0; i < LEVEL; i++) {  // for each level
		// create the left most dummy nodes;
		header[i] = new SListNode<Object>;
		header[i]->prev = NULL;
		header[i]->down = (i > 0) ? header[i - 1] : NULL;
		header[i]->up = NULL;
		if (i > 0)
			header[i - 1]->up = header[i];

		// create the right most dummy nodes;
		header[i]->next = new SListNode<Object>;
		header[i]->next->next = NULL;
		header[i]->next->prev = header[i];
		header[i]->next->down = (i > 0) ? header[i - 1]->next : NULL;
		header[i]->next->up = NULL;
		if (i > 0)
			header[i - 1]->next->up = header[i]->next;
	}

	// reset cost.
	cost = 0;
}

template<class Object>
SList<Object>::~SList() {
	clear();                                      // delete items starting 1st
	for (int i = 0; i < LEVEL; i++) {
		delete header[i]->next;                   // delete the right most dummy
		delete header[i];                          // delete the left most dummy
	}
}

template<class Object>
bool SList<Object>::isEmpty() const {
	return (header[0]->next->next == NULL);
}

template<class Object>
int SList<Object>::size() const {
	SListNode<Object> *p = header[0]->next; // at least the right most dummy
	int size = 0;

	for (; p->next != NULL; p = p->next, ++size)
		;
	return size;
}

template<class Object>
void SList<Object>::clear() {
// for each level, iterate from the first to last item.
	for (int i = 0; i < LEVEL; i++) {
		SListNode<Object> *p = header[i]->next;  // get the 1st item
		while (p->next != NULL) {              // if this is not the left most
			SListNode<Object> *del = p;
			p = p->next;                           // get the next item
			delete del;                            // delete the current item
		}
		header[i]->next = p;                   // p now points to the left most
	}
}

template<class Object>
void SList<Object>::insert(const Object &obj) {
// right points to the level-0 item before which a new object is inserted.
	SListNode<Object> *right = searchPointer(obj);
	SListNode<Object> *up = NULL;
	if (right->next != NULL && right->item == obj) {
		// there is an identical object
		return;
	}
	int x = rand() % 2;
	SListNode<Object> *newNode = new SListNode<Object>;
	newNode->item = obj; //Inserting the item in the lowest level
	newNode->up = NULL; //No Node that is up and down so far
	newNode->down = NULL;
	newNode->next = right; // Insert before "right"
	newNode->prev = right->prev; //point to the one before "right"
	right->prev->next = newNode; //the one before "right" point to the new Item
	right->prev = newNode; //previous of "right" point to the newNode
	if (x != 1) {
		return; // Do not insert if random != 1;
	}
	up = newNode; // if it is not, start inserting item
	int count = 1; // Counter to make sure not to insert at top level
	while (x == 1) // If we still getting 1, keep inserting
	{
		while (up->prev != NULL) // Check for leftmost case
		{

			up = up->prev;
			if (up->up != NULL) // Check for top level case
			{
				up = up->up;
				up = up->next;

				SListNode<Object> *insert = new SListNode<Object>;
				insert->item = obj;

				// Changing all the node around the new Node including node on right, left, and below. Set up = NULL
				insert->next = up;
				insert->up = NULL;
				insert->prev = up->prev;
				insert->down = newNode;
				newNode->up = insert;
				up->prev->next = insert;
				up->prev = insert;

				count++; // insert item in 1 level, increment.
				newNode = insert; //Save the current location to insert for next iteration
				break;
			}
		}
		if (count == LEVEL)
			break; // Not to reach top level
	}
	x = rand() % 2; //check for continue iteration
}

template<class Object>
bool SList<Object>::find(const Object &obj) {
// points to the level-0 item close to a given object
	SListNode<Object> *p = searchPointer(obj);

	return (p->next != NULL && p->item == obj); // true if obj was found
}

template<class Object>
SListNode<Object> *SList<Object>::searchPointer(const Object &obj) {
	SListNode<Object> *p = header[LEVEL - 1];     // start from the top left
	while (p->down != NULL) {                   // toward level 0
		p = p->down;                   // shift down once
		cost++;

		if (p->prev == NULL) {                    // at the left most item
			if (p->next->next == NULL)                  // no intermediate items
				continue;
			else {                                    // some intermadiate items
				if (p->next->item <= obj)                  // if 1st item <= obj
					p = p->next;                        // shift right to item 1
				cost++;
			}
		}

		while (p->next->next != NULL && p->next->item <= obj) {
			// shift right through intermediate items as far as the item value <= obj
			p = p->next;
			cost++;
		}
	}

// now reached the bottom. shift right once if the current item < obj
	if (p->prev == NULL || p->item < obj) {
		p = p->next;
		cost++;
	}
	return p; // return the pointer to an item >= a given object.
}

template<class Object>
void SList<Object>::remove(const Object &obj) {
	// p points to the level-0 item to delete
	SListNode<Object> *p = searchPointer(obj);

	// validate if p is not the left most or right most and exactly contains the
	// item to delete
	if (p->prev == NULL || p->next == NULL || p->item != obj)
		return;
	if (p->up == NULL) // Check if it only has 1 level
	{
		//Reconfigure the adjacent Node
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p; // Deallocate memory
		return;
	}
	SListNode<Object> *deleteNode = p;
	while (p != NULL) // going through each level to delete
	{
		p->prev->next = p->next; // Reconfigure the adjacent Node
		p->next->prev = p->prev;
		p = p->up; // Go up
		delete deleteNode;
		deleteNode = p;
	}
}

template<class Object>
const SList<Object> &SList<Object>::operator=(const SList &rhs) {
	if (this != &rhs) { // avoid self-assignment
		clear(); // deallocate old items

		int index;
		SListNode<Object> *rnode;
		for (index = 0, rnode = rhs.header[0]->next; rnode->next != NULL;
				rnode = rnode->next, ++index)
			insert(rnode->item);

		cost = rhs.cost;
	}
	return *this;
}

template<class Object>
int SList<Object>::getCost() const {
	return cost;
}

template<class Object>
void SList<Object>::show() const {
	cout << "contents:" << endl;
	for (SListNode<Object> *col = header[0]; col != NULL; col = col->next) {
		SListNode<Object> *row = col;
		for (int level = 0; row != NULL && level < LEVEL; level++) {
			if (row->prev == NULL)
				cout << "-inf\t";
			else if (row->next == NULL)
				cout << "+inf\t";
			else
				cout << row->item << "\t";
			row = row->up;
		}
		cout << endl;
	}
}

