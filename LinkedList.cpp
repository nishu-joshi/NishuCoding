struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct DLLNode
{
    int val;
    DLLNode *prev;
    DLLNode *next;
    DLLNode() : val(0), prev(nullptr), next(nullptr) {}
    DLLNode(int x) : val(x), next(nullptr) {}
    DLLNode(int x, DLLNode *prev, DLLNode *next) : val(x), prev(prev), next(next) {}
};

// 1. Reverse a linked list
class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {

        if (!head || !head->next)
            return head;
        ListNode *prev = nullptr;
        ListNode *curr = head;
        ListNode *nxt = head->next;

        while (curr)
        {
            nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        return prev;
    }
};

// 2. Delete the node from singly linked list
// this concept will be used to delete the middle node of the linked list too
class Solution
{
public:
    void deleteNode(ListNode *node)
    {
        ListNode *nxt = node->next;
        node->val = nxt->val;
        node->next = nxt->next;
    }
};

// 3. Reverse a Double Linked List
class Solution
{
public:
    // Function to reverse a doubly linked list
    DLLNode *reverseDLL(DLLNode *head)
    {
        DLLNode *prev = nullptr;
        DLLNode *curr = head;
        DLLNode *nxt = nullptr;
        if (!head || !head->next)
            return head;

        while (curr)
        {
            nxt = curr->next;
            curr->next = prev;
            curr->prev = nxt;
            prev = curr;
            curr = nxt;
        }
        return prev;
    }
};

// 4. Detect cycle in Linked List
// Floyd's Cycle Detection Algorithm
class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        if (!head || !head->next)
            return false;

        ListNode *slow = head;
        ListNode *fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        return false;
    }
};

// 5. Node where cycles starts
class Solution
{
public:
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                break;
        }
        if (!(fast && fast->next))
            return nullptr;
        while (head != slow)
        {
            head = head->next;
            slow = slow->next;
        }
        return head;
    }
};

// 6. Linked List is Palindrome
class Solution
{
public:
    bool isPalindrome(ListNode *head)
    {
        if (!head || !head->next)
            return true;

        ListNode *ptr = head;
        ListNode *fast = head;

        // ptr will be left at first node after middle ,i.e. n/2+1 bas wahi se reverse krni h
        while (fast && fast->next)
        {
            ptr = ptr->next;
            fast = fast->next->next;
        }

        // reverse the secondhalf
        ListNode *curr = ptr;
        ListNode *nxt = nullptr;
        ListNode *prev = nullptr;

        while (curr)
        {
            nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        ptr = prev;
        // Second half has been reversed

        // now checking if nodes has same value
        while (ptr && head)
        {
            if (head->val != ptr->val)
                return false;
            ptr = ptr->next;
            head = head->next;
        }
        return true;
    }
};

// 7. Odd even Linkedlist
class Solution
{
public:
    ListNode *oddEvenList(ListNode *head)
    {

        if (!head || !head->next)
            return head;

        ListNode *odd = head;
        ListNode *even = head->next;

        ListNode *temp = even; // will stay at start of even node list to connect it to end of odd node list

        while (even && even->next)
        {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }

        odd->next = temp;

        return head;
    }
};