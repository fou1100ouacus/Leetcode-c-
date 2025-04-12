
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
	bool isList1(bool flag=false)
	{
		return flag;
	}
	ListNode* Compare(ListNode*n1,ListNode*n2)
	{// how to find the next node 
		if (n1&&n2)
		{
			if ( n1->data<n2->data )
			{
				isList1(true);
				return n1;

			}
			return n2;
		}

	}
	//ListNode* MergeTwoSortedLists(const LinkedList&  list1, const LinkedList& list2)
	//{
	//	ListNode* temp1 = list1.head;
	//	ListNode* temp2 = list2.head;
	//	ListNode* NewSortedList = nullptr;
	//	ListNode* small = Compare(temp1, temp2);// compare first node of 2 lists
	//	bool isFirst = isList1();
	//	
	//	while (temp1&&temp2)
	//	{
	//		NewSortedList = small;
	//		while (isFirst)
	//		{
	//			ListNode* node = Compare(temp1->next, temp2);
	//			NewSortedList->next = node;
	//			temp1 = temp1->next;
	//		}
	//		
	//		while (!isFirst)
	//		{
	//			ListNode* node = Compare(temp1, temp2->next);
	//			NewSortedList->next = node;
	//			temp2 = temp2->next;
	//		}
	//		

	//	}
	//	return NewSortedList;
	//}


	//ListNode* MergeTwoSortedLists( const LinkedList& list2)
	//{
	//	ListNode* temp1 = head;
	//	ListNode* temp2 = list2.head;
	//	ListNode* NewSortedList = nullptr;
	//	ListNode* small = Compare(temp1, temp2);// compare first node of 2 lists
	//	bool isFirst = isList1();

	//	while (temp1 && temp2)
	//	{
	//		NewSortedList = small;
	//		while (isFirst)
	//		{
	//			ListNode* node = Compare(temp1->next, temp2);
	//			NewSortedList->next = node;
	//			temp1 = temp1->next;
	//		}

	//		while (!isFirst)
	//		{
	//			ListNode* node = Compare(temp1, temp2->next);
	//			NewSortedList->next = node;
	//			temp2 = temp2->next;
	//		}


	//	}
	//	return NewSortedList;
	//}
	ListNode* MergeTwoSortedLists(const LinkedList& list2) {
		ListNode* temp1 = head;          // Pointer to first list's head
		ListNode* temp2 = list2.head;    // Pointer to second list's head
		ListNode dummy(0);               // Dummy node to simplify merging
		ListNode* tail = &dummy;         // Pointer to build the new list

		// While both lists have nodes
		while (temp1 && temp2) {
			// Compare current nodes
			if (temp1->data <= temp2->data) {
				tail->next = temp1;      // Add temp1's node to result
				temp1 = temp1->next;     // Advance list1
			}
			else {
				tail->next = temp2;      // Add temp2's node to result
				temp2 = temp2->next;     // Advance list2
			}
			tail = tail->next;           // Move tail forward
		}

		// Append remaining nodes, if any
		if (temp1) {
			tail->next = temp1;
		}
		if (temp2) {
			tail->next = temp2;
		}

		return dummy.next;               // Return head of merged list
	}






};


int main()
{
	LinkedList list1, list2;

	cout << "-------" << endl;

	list1.insert_end(1);
	list1.insert_end(2);
	list1.insert_end(4);
	list1.print();
	cout << "--------------------" << endl;
	list2.insert_end(1);
	list2.insert_end(3);
	list2.insert_end(4);
	cout << "--------------------" << endl;

	list2.print();

	 list1.MergeTwoSortedLists( list2);
	 cout << "--------------------" << endl;

	 list1.print();


	//list.ArrangeOddEven();
	////list.moveToEnd(2);

	//cout << "___________________" << endl;
	////	list.delete_even_positions();
	//list.print();



}