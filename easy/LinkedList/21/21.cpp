#include <iostream>


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (list1 && list2) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            }
            else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        if (list1) {
            tail->next = list1;
        }
        if (list2) {
            tail->next = list2;
        }

        return dummy.next;
    }
};

// Function to print linked list
void printList(ListNode* head) {
    ListNode* curr = head;
    while (curr) {
        std::cout << curr->val << " -> ";
        curr = curr->next;
    }
    std::cout << "nullptr" << std::endl;
}

// Function to create a list from an array
ListNode* createList(int arr[], int size) {
    if (size == 0) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* curr = head;
    for (int i = 1; i < size; ++i) {
        curr->next = new ListNode(arr[i]);
        curr = curr->next;
    }
    return head;
}

// Function to delete a list to prevent memory leaks
void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // Create two sorted linked lists
    int arr1[] = { 1, 3, 5 };
    int arr2[] = { 2, 4, 6 };
    ListNode* list1 = createList(arr1, 3); // list1: 1 -> 3 -> 5
    ListNode* list2 = createList(arr2, 3); // list2: 2 -> 4 -> 6

    // Print input lists
    std::cout << "List 1: ";
    printList(list1);
    std::cout << "List 2: ";
    printList(list2);

    // Merge lists
    Solution solution;
    ListNode* merged = solution.mergeTwoLists(list1, list2);

    // Print merged list
    std::cout << "Merged List: ";
    printList(merged);

    // Clean up memory
    deleteList(merged);
    // Note: list1 and list2 nodes are reused in merged, so don't delete them separately

    return 0;
}