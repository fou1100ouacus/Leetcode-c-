// Problem2_Insert front.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <bits/stdc++.h>
using namespace std;
struct ListNode {
	int data{ };
	ListNode* next{ };
	ListNode(int data) :
		data(data) {
	}

	~ListNode() {
		//To easily test your nodes are destructed
		cout << "Destroy value: " << data << "\n";
	}
};

class LinkedList {
private:
	ListNode* head{ };
	ListNode* tail{ };
	int length = 0;	// let's maintain how many nodes
	vector<ListNode*> debug_data;	// add/remove nodes you use
	void debug_add_node(ListNode* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(ListNode* node) {
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}
public:
	// Below 2 deletes prevent copy and assign to avoid this mistake
	LinkedList() {
	}
	LinkedList(const LinkedList&) = delete;
	LinkedList& operator=(const LinkedList& another) = delete;
	void debug_print_address() {
		for (ListNode* cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}
	void debug_print_node(ListNode* node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}
		cout << node->data << " ";
		if (node->next == nullptr)
			cout << "X ";
		else
			cout << node->next->data << " ";

		if (node == head)
			cout << "head\n";
		else if (node == tail)
			cout << "tail\n";
		else
			cout << "\n";
	}
	void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int)debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n" << flush;
	}
	string debug_to_string() {
		if (length == 0)
			return "";
		ostringstream oss;
		for (ListNode* cur = head; cur; cur = cur->next) {
			oss << cur->data;
			if (cur->next)
				oss << " ";
		}
		return oss.str();
	}
	void debug_verify_data_integrity() {
		if (length == 0) {
			assert(head == nullptr);
			assert(tail == nullptr);
		}
		else {
			assert(head != nullptr);
			assert(tail != nullptr);
			if (length == 1)
				assert(head == tail);
			else
				assert(head != tail);
			assert(!tail->next);
		}
		int len = 0;
		for (ListNode* cur = head; cur; cur = cur->next, len++)
			assert(len < 10000);	// Consider infinite cycle?
		assert(length == len);
		assert(length == (int)debug_data.size());
	}
	////////////////////////////////////////////////////////////

	void print() {
		for (ListNode* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

	// These 2 simple functions just to not forget changing the vector and length
	void delete_node(ListNode* node) {
		debug_remove_node(node);
		--length;
		delete node;
	}
	void add_node(ListNode* node) {
		debug_add_node(node);
		++length;
	}
	void insert_end(int value) {
		ListNode* item = new ListNode(value);
		add_node(item);

		if (!head)
			head = tail = item;
		else
			tail->next = item, tail = item;
	}
	void insert_front(int val) {
		// O(1) time - O(1) memory
		ListNode* item = new ListNode(val);
		add_node(item);

		item->next = head;
		head = item;

		if (length == 1)
			tail = head;

		debug_verify_data_integrity();
	}
	void Delete_front()
	{
		// O(1) time - O(1) memory
		assert(length);
		ListNode* cur = head->next;
		delete_node(head);
		head = cur;

		if (length <= 1)
			tail = head;

		debug_verify_data_integrity();
	}
	ListNode* get_nth(int n) {
		int cnt = 0;
		for (ListNode* cur = head; cur; cur = cur->next)
			if (++cnt == n)
				return cur;

		return nullptr;
	}
	ListNode* FromBack_get_nth(int n) {			// O(n) time - O(1) memory
		// If we know the length, we can compute its normal position
		if (length < n)
			return nullptr;
		return get_nth(length - n + 1);	// give it its 1-based index forward
	}
	bool is_same1(const LinkedList& other) {		// O(n) time - O(1) memory
		ListNode* h1 = head, * h2 = other.head;

		while (h1 && h2)
		{
			if (h1->data != h2->data)
				return false;
			h1 = h1->next, h2 = h2->next;
		}
		return !h1 && !h2;	// make sure both ends together
	}
	bool is_same(const LinkedList& other) {	// using length
		if (length != other.length)
			return false;

		ListNode* other_h = other.head;

		for (ListNode* cur_h = head; cur_h; cur_h = cur_h->next) {
			if (cur_h->data != other_h->data)
				return false;
			other_h = other_h->next;
		}
		return true;
	}
	int search(int value) {
		int idx = 0;
		for (ListNode* cur = head; cur; cur = cur->next, idx++)
			if (cur->data == value) // Common Mistake to use head
				return idx;
		return -1;
	}
	int search_improved(int value) {
		int idx = 0;
		ListNode* prv = nullptr;
		for (ListNode* cur = head; cur; cur = cur->next, idx++)
		{
			if (cur->data == value) {
				if (!prv)// first item in list
					return idx;
				swap(prv->data, cur->data);
				return idx - 1;
			}
			prv = cur;
		}
		return -1;
	}
	void delete_nth_node(int n) {
		if (n < 1 || n > length)
			cout << "Error. No such nth node\n";
		else if (n == 1)
			Delete_front();
		else
		{
			// Connect the node before nth with node after nth
			ListNode* before_nth = get_nth(n - 1);
			ListNode* nth = before_nth->next;// we can get it from getnth method          gen_nth(n)
			bool is_tail = nth == tail;
			// connect before node with after
			before_nth->next = nth->next;
			if (is_tail)
				tail = before_nth;

			delete_node(nth);

			debug_verify_data_integrity();
		}
	}
	void delete_node_with_key(int value) {
		// These checks in method delete nth node
		/*if (!length)
			cout << "Empty list!\n";
		else if (head->data == value)
			Delete_front();*/

		int target = search(value);// O(n)
		//	Node * selectedNode=get_nth(target+1);
		delete_nth_node(target + 1);



	}

	//void swap_pairs()
	//  {
	//	Node* cur = head;
	//	int counter = 0;
	//	Node* prev = NULL;

	//	for (cur = head; cur; cur = cur->next)
	//	{
	//		counter++;
	//		prev = cur;

	//		cur = cur->next;
	//		if (counter == 2)
	//		{
	//			swap(cur->data, prev->data);
	//			counter = 0;
	//		}
	//	}
	//}
	void swap_pairs() {		// O(n) time - O(1) memory
		// For each 2 consecutive, swap data and jump cur->next->next
		for (ListNode* cur = head; cur; cur = cur->next) {
			if (cur->next) {// not null
				swap(cur->data, cur->next->data);
				cur = cur->next;
			}
		}
	}

	//void delete_even_positions()
	//{

	//	int evenPostion = 1;
	//	while (head->next!=NULL)
	//	{
	//		
	//		if (evenPostion%2==0)
	//		{
	//			Node* cur = head;
	//			delete_node(cur);
	//			//	delete_nth_node(evenPostion);

	//		}
	//    	 head = head->next;
	//		 evenPostion++;

	//	}
	//}

	void delete_next_node(ListNode* node) {
		// Delete the next of the current node
		// Handle if next is tail case
		assert(node);

		ListNode* to_delete = node->next;
		bool is_tail = to_delete == tail;

		// node->next in middle to delete
		node->next = node->next->next;

		delete_node(to_delete);
		if (is_tail)
			tail = node;
	}
	void delete_even_positions() {		// O(n) time - O(1) memory
		if (length <= 1)
			return;
		// maintain previous and delete its next (even order)
		for (ListNode* cur = head->next, *prv = head; cur;) {
			delete_next_node(prv);	// prev is odd, prev-next is even
			if (!prv->next)	// tail
				break;
			cur = prv->next->next;
			prv = prv->next;
		}
		debug_verify_data_integrity();
	}
	void embed_after(ListNode* node, int value) {
		// Add a node with value between node and its next
		ListNode* item = new ListNode(value);
		++length;
		debug_add_node(item);

		item->next = node->next;
		node->next = item;
	}
	void insert_sorted(int value) {
		if (!length || value <= head->data)
			insert_front(value);
		else if (tail->data <= value)
			insert_end(value);
		else
		{
			ListNode* node = new ListNode(value);
			ListNode* cur = head;
			for (cur = head; cur; cur = cur->next)
			{
				if (node->data > cur->data && node->data < cur->next->data)
				{
					embed_after(cur, value);

				}
			}
		}

	}
	ListNode* get_previous(ListNode* target) {		// O(n) time - O(1) memory
		for (ListNode* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
			if (cur == target)	// memory wise
				return prv;
		}
		return nullptr;	// still more steps needed - NOT found
	}
	void swap_head_tail() {		// O(n) time - O(1) memory
		// 0 or 1 node. We can use length also if(length <= 1)
		if (!head || !head->next)
			return;

		if (length == 2)
		{
			swap(tail, head);
			head->next = tail;
			tail->next = nullptr;
			return;
		}

		ListNode* prv = get_previous(tail);	// node before tail

		// Let's make current tail as head
		// Link tail to the 2nd node
		tail->next = head->next;

		// Let's make current head as tail
		// Link tail's previous to head
		prv->next = head;
		head->next = nullptr;

		swap(tail, head);	// Set new head and tail

		debug_verify_data_integrity();
	}
	/*void DeleteNextNode(Node*prev)
	{
		Node* toDelete = prev->next;
		bool istail = toDelete == tail;

		prev->next = prev->next->next;
		delete_node(prev->next);
		if (istail)
		{
			tail = prev;

		}
	}
	void RemoveDuplicates()
	{
		for (Node* cur1  = head ;cur1; cur1 = cur1->next)
		{
			for (Node* cur2 = cur1->next ,*prev=cur2; cur2 ;)
			{
				if (cur2->data==cur2->data)
				{
					DeleteNextNode(prev);
					cur2 = prev->next;
				}
				else
				{
					prev = cur2;

					cur2 = cur2->next;
				}
			}

		}
		debug_verify_data_integrity();

	}

*/
//void delete_next_node(Node* node) {
//	// Delete the next of the current node
//	// Handle if next is tail case
//	assert(node);

//	Node* to_delete = node->next;
//	bool is_tail = to_delete == tail;

//	// node->next in middle to delete
//	node->next = node->next->next;

//	delete_node(to_delete);
//	if (is_tail)
//		tail = node;
//}

	void remove_duplicates_from_not_sorted() {		// O(n^2) time - O(1) memory
		if (length <= 1)
			return;

		// Just like 2 nested loops, find all duplicates and delete

		for (ListNode* cur1 = head; cur1; cur1 = cur1->next) {
			for (ListNode* cur2 = cur1->next, *prv = cur1; cur2;) {
				if (cur1->data == cur2->data) {
					delete_next_node(prv);// counter here then the max counter delete the node
					cur2 = prv->next;
				}
				else
					prv = cur2, cur2 = cur2->next;	// normal move
			}
		}
		debug_verify_data_integrity();
	}


	//void remove_last_occurance(int target)
	//{
	//	bool isfound = false;

	//	Node* deletenext =nullptr;
	//	for (Node* cur = head, *prev = nullptr; prev=cur; cur = cur->next;) {
	//			
	//			if (cur->data == target) 
	//			{
	//				bool isfound = true;
	//				deletenext = prev;
	//			}
	//			if (isfound)
	//			{


	//				if (deletenext)
	//				{
	//					delete_next_node(deletenext);
	//				}
	//				else
	//				{
	//					Delete_front();

	//				}
	//			}

	//		}
	//

	//	debug_verify_data_integrity();


	//}

	void delete_last_occurrence(int target) {		// O(n) time - O(1) memory
		if (!length)
			return;

		ListNode* delete_my_next_node = nullptr;
		bool is_found = false;

		// Find the last one and remove it

		for (ListNode* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next)
		{
			if (cur->data == target)
				is_found = true,
				delete_my_next_node = prv;
		}
		if (is_found)
		{
			if (delete_my_next_node)
				delete_next_node(delete_my_next_node);
			else
				// if prv is null, then found at head
				Delete_front();
		}
		debug_verify_data_integrity();
	}


	void left_rotate(int k) {		// O(n) time - O(1) memory
		if (length <= 1 || k % length == 0)
			return;	// 0 or 1 elements or useless rotation
		k %= length;	// Remove useless cycles

		ListNode* nth = get_nth(k);// firstnode
		tail->next = head;		// create cycle

		// Reset tail/head
		tail = nth;
		head = nth->next;

		tail->next = nullptr;	// disconnect cycle
		debug_verify_data_integrity();
	}


	//void moveToEnd(int key)
	//{
	//	if (!length)
	//		return;

	//	if (head->data==key)
	//	{
	//		left_rotate(1);
	//	}
	//	//int counter = 0;
	//	for (Node* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next)
	//	{
	//		Node* tempStorecur = NULL;
	//		if (cur->data==key)
	//		{
	//			tempStorecur = cur;
	//			tail = cur;
	//			//move current first to back      
	//			prv->next = prv->next->next;
	//			tail->next = NULL;
	//			cur = tempStorecur;
	//		//	left_rotate(1);
	//			
	//		}
	//	}
	//	
	//	debug_verify_data_integrity();

	//}
	void link(ListNode* first, ListNode* sec)
	{
		if (first)
		{
			first->next = sec;
		}
		ListNode* prev = get_previous(sec);
		if (sec)
		{
			prev = first;

		}
	}
	void ArrangeOddEven()
	{
		if (length <= 2)
			return;

		ListNode* Oddpos = head;
		ListNode* EvenPos = head->next;
		while (Oddpos->next && Oddpos->next->next) {
			ListNode* nextEven = Oddpos->next;
			Oddpos->next = Oddpos->next->next;
			nextEven->next = nextEven->next->next;
			Oddpos = Oddpos->next;// counter

			if (length % 2 == 1)
				tail = nextEven;// 1 2 3 === 1 3 2
		}

		Oddpos->next = EvenPos;





		//for( Oddpos = head; Oddpos;)
		//{
		////	EvenPos->next = pos->next->next;
		//	Oddpos->next = Oddpos->next->next;
		//	Oddpos;

		//	// link betwen head and temp and pos

		//}
		//link(head, pos);


	}
	void insert_after(ListNode* src, ListNode* target) {
		// Given node src, link target after it with my list before/after
		assert(src && target);
		target->next = src->next;
		src->next = target;
		debug_add_node(target);
		++length;
	}

	void insert_alternate(LinkedList& another) {		// O(n) time - O(1) memory
		if (!another.length)
			return;

		if (!length) {
			// copy data
			head = another.head;
			tail = another.tail;
			length = another.length;
			debug_data = another.debug_data;

		}
		else
		{
			// Iterate one by one, add node in right place
			// If this ended first, then we link the remain in this list
			ListNode* cur2 = another.head;
			for (ListNode* cur1 = head; cur1 && cur2;)
			{
				ListNode* cur2_next_temp = cur2->next;
				insert_after(cur1, cur2);
				another.length--;
				cur2 = cur2_next_temp;

				if (cur1 == tail)
				{
					tail = another.tail;
					cur1->next->next = cur2;
					length += another.length;
					break;

					// there is a missing thing here
					// we need to add remaining nodes to debug data
					// let's skip
				}

				cur1 = cur1->next->next;
			}
		}

		another.head = another.tail = nullptr;
		another.length = 0;
		another.debug_data.clear();
		debug_verify_data_integrity();
	}

	void reverse() {		// O(n) time - O(1) memory
		if (length <= 1)
			return;

		tail = head;
		ListNode* prv = head;
		head = head->next;
		while (head) {
			// store & reverse link
			ListNode* next = head->next;
			head->next = prv;

			// move step
			prv = head;
			head = next;
		}
		// Finalize head and tail
		head = prv;
		tail->next = nullptr;

		debug_verify_data_integrity();
	}

	void add_num(LinkedList& another) {
		if (!length)
		{
			another.reverse();

		}
		if (!another.length)
		{
			reverse();
		}


	}

};






int main()
{
	LinkedList list, list2;

	cout << "-------" << endl;

	list.insert_end(1);
	list.insert_end(2);
	list.insert_end(35);
	list.insert_end(2);
	list.insert_end(3);
	list2.insert_end(11);
	list2.insert_end(21);
	list2.insert_end(351);
	list2.insert_end(21);
	list2.insert_end(31);
	list.insert_alternate(list2);

	list.print();
	//list.ArrangeOddEven();
	////list.moveToEnd(2);

	//cout << "___________________" << endl;
	////	list.delete_even_positions();
	//list.print();



}

