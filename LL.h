#include <iostream>
using namespace std;

template <typename T>
class LL
{
    // contents of struct Node
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
    };
    // iterator class to allow access of each node in main
public:
    class Iterator
    {
    public:
        friend class LL;
        Iterator();
        Iterator(Node *);
        T operator*() const;
        const Iterator &operator++(int);
        const Iterator &operator--(int);
        bool operator==(const Iterator &) const;
        bool operator!=(const Iterator &) const;

    private:
        Node *current;
    };

    LL();
    LL(const LL<T> &);
    const LL<T> &operator=(const LL<T> &);
    ~LL();
    void headInsert(const T &);
    void tailInsert(const T &);
    Iterator begin() const;
    Iterator end() const;
    void swapNodes(Iterator &, Iterator &);

private:
    Node *head;
    Node *tail;
};

/*
///  LL CLASS //
*/

// Defualt ctor sets head and tail to nullptr
template <typename T>
LL<T>::LL()
{
    tail = nullptr;
    head = nullptr;
}

// copy ctor
template <typename T>
LL<T>::LL(const LL<T> &copy)
{
    // makes sure our DLL currently is empty
    this->tail = nullptr;
    this->head = nullptr;

    // creates a copy of node head
    Node *temp = copy.head;

    // iterates through DLL
    // loops through will temp != nullptr/NULL
    while (temp)
    {
        Node *trvsl = new Node();
        trvsl->data = temp->data;
        trvsl->next = nullptr;
        trvsl->prev = nullptr;

        // checks to see if DLL is only one node
        if (this->head != nullptr)
        {
            this->tail->next = trvsl;
            trvsl->prev = tail;
            this->tail = trvsl;
        }
        else
        {
            this->head = trvsl;
            this->tail = trvsl;
        }
        temp = temp->next;
    }
}

// dtor
template <typename T>
LL<T>::~LL()
{
    // makes a traversal node to go through linked list
    Node *traversal = head;
    while (traversal != nullptr)
    {
        head = head->next;
        delete traversal;
        traversal = head;
    }
    head = nullptr;
    tail = nullptr;
}

// headInsert
template <typename T>
void LL<T>::headInsert(const T &item)
{

    // creates a new node and puts item data in it
    Node *temp = new Node();
    temp->data = item;
    temp->next = nullptr;
    temp->prev = nullptr;
    // checks to see if DLL is one node
    if (head != nullptr)
    {
        temp->next = head;
        head->prev = temp;
        temp->prev = nullptr;
        head = temp;
    }
    else
    {
        head = temp;
        tail = temp;
    }
}

// tailInsert
template <typename T>
void LL<T>::tailInsert(const T &item)
{
    // creates a new node and puts prev to tails prev
    Node *temp = new Node();
    temp->data = item;
    temp->next = nullptr;
    temp->prev = nullptr;

    // checks to see if DLL is one Node
    if (head != nullptr)
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    else
    {
        head = temp;
        tail = temp;
    }
}

// Iterator
template <typename T>
typename LL<T>::Iterator LL<T>::end() const
{
    return Iterator(this->tail);
}

// begin
template <typename T>
typename LL<T>::Iterator LL<T>::begin() const
{
    return Iterator(this->head);
}

// Assignment Operator
template <typename T>
const LL<T> &LL<T>::operator=(const LL<T> &rhs)
{

    // Checks to see if anything is in the head of *this
    if (this->head)
    {
        // if somethings found, loop deallocates DLL
        Node *temp = this->head;
        while (temp != nullptr)
        {
            this->head = this->head->next;
            delete temp;
            temp = this->head;
        }
        // Clean up head and tail
        this->head = nullptr;
        this->tail = nullptr;
    }

    // Checks rhs head to see if theres something in it, otherwise skip
    if (rhs.head != nullptr)
    {
        // if something found, traverse through rhs to copy
        Node *temp = rhs.head;
        while (temp != nullptr)
        {
            // creates a traversal node to copy node by node
            Node *traversal = new Node();
            traversal->data = temp->data;
            // just in case DLL is only one node
            traversal->next = nullptr;
            traversal->prev = nullptr;

            // Checks what to do with head and tail
            if (this->head != nullptr)
            {
                // organizes DLL by putting linking a node at end
                this->tail->next = traversal;
                traversal->prev = tail;
                this->tail = traversal;
            }
            // makes DLL one node
            else
            {
                this->head = traversal;
                this->tail = traversal;
            }
            temp = temp->next;
        }
    }
    return *this;
}

// swapNodes
template <typename T>
void LL<T>::swapNodes(Iterator &it1, Iterator &it2)
{
    // start with two temps, will add more on case by case
    Node *num1 = it1.current;
    Node *num2 = it2.current;

    // two next to each other
    if (num1->next == num2 && num2->prev == num1)
    {
        // Checks to see if num1 is head
        if (num1 == head)
        {
            // checks to see if num2 is tail
            if (num2 == tail)
            {
                // head and tail swap
                num1->next = nullptr;
                num1->prev = num2;
                num2->next = num1;
                num2->prev = nullptr;

                head = num2;
                tail = num1;
            }
            else
            {
                // head and normal node swap next to eachother
                Node *num2_right = num2->next;
                num1->next = num2_right;
                num2_right->prev = num1;
                num1->prev = num2;
                num2->prev = nullptr;
                num2->next = num1;
                head = num2;
            }
        }
        // if num1 isnt a head
        else
        {
            // checks to see if num2 is tail
            if (num2 == tail)
            {
                //cout << "tail is " << tail->data << endl;
                //cout << "swapping with " << num1->data << endl;
                // tail node swap thats next to tail
                Node *num1_left = num1->prev;

                num1_left->next = num2;
                num1->prev = num2;
                num1->next = nullptr;
                num2->prev = num1_left;
                num2->next = num1;

                tail = num1;

                //cout << "tail is now " << tail->data << endl;
                //cout << "behind tail is now " << tail->prev->data << endl;

            }
            else
            {
                // normal node swap next to each other
                Node *num1_left = num1->prev;
                Node *num2_right = num2->next;

                num1_left->next = num2;
                num1->prev = num2;
                num1->next = num2_right;
                num2->prev = num1_left;
                num2->next = num1;
                num2_right->prev = num1;
            }
        }
    }
    // If nodes weren't next to eachother
    else
    {
        // checks to see if num1 is head
        if (num1->prev == nullptr)
        {
            // checks to see if num2 is tail
            if (num2->next == nullptr)
            {
                // head and tail swap

                // checks if theres a middle node
                if (num1->next == num2->prev)
                {
                    Node *middle = num1->next;

                    num1->next = nullptr;
                    num1->prev = middle;
                    middle->prev = num2;
                    middle->next = num1;
                    num2->next = middle;
                    num2->prev = nullptr;

                    head = num2;
                    tail = num1;
                }
                // Head and tail are further apart
                else
                {
                    Node *num1_right = num1->next;
                    Node *num2_left = num2->prev;

                    num1->prev = num2_left;
                    num1->next = nullptr;
                    num1_right->prev = num2;
                    num2_left->next = num1;
                    num2->prev = nullptr;
                    num2->next = num1_right;

                    head = num2;
                    tail = num1;
                }
            }
            else
            {
                // head and normal swap not next to eachother

                // checks for middle node
                if (num1->next == num2->prev)
                {
                    Node *middle = num1->next;
                    Node *num2_right = num2->next;

                    num1->next = num2_right;
                    num1->prev = middle;
                    middle->prev = num2;
                    middle->next = num1;
                    num2->prev = nullptr;
                    num2->next = middle;
                    num2_right->prev = num1;

                    head = num2;
                }
                else
                {
                    // head swap with no middle node
                    Node *num1_right = num1->next;
                    Node *num2_right = num2->next;
                    Node *num2_left = num2->prev;

                    num1->prev = num2_left;
                    num1->next = num2_right;
                    num1_right->prev = num2;
                    num2_left->next = num1;
                    num2->prev = nullptr;
                    num2->next = num1_right;
                    num2_right->prev = num1;

                    head = num2;
                }
            }
        }
        else
        {
            // checks if num2 is tail
            if (num2->next == nullptr)
            {
                // normal & tail swap not next to eachother

                // Checks for a middle case
                if (num1->next == num2->prev)
                {
                    Node *middle = num1->next;
                    Node *num1_left = num1->prev;

                    num1_left->next = num2;
                    num1->prev = middle;
                    num1->next = nullptr;
                    middle->prev = num2;
                    middle->next = num1;
                    num2->prev = num1_left;
                    num2->next = middle;

                    tail = num1;
                }
                // tail swap with no middle node
                else
                {
                    Node *num1_left = num1->prev;
                    Node *num1_right = num1->next;
                    Node *num2_left = num2->prev;

                    num1_left->next = num2;
                    num1->prev = num2_left;
                    num1->next = nullptr;
                    num1_right->prev = num2;
                    num2_left->next = num1;
                    num2->prev = num1_left;
                    num2->next = num1_right;

                    tail = num1;
                }
            }
            else
            {
                // normal swap not next to eachother

                // checks for middle case
                if (num1->next == num2->prev)
                {
                    Node *num1_left = num1->prev;
                    Node *middle = num1->next;
                    Node *num2_right = num2->next;

                    num1_left->next = num2;
                    num1->prev = middle;
                    num1->next = num2_right;
                    middle->prev = num2;
                    middle->next = num1;
                    num2->prev = num1_left;
                    num2->next = middle;
                    num2_right->prev = num1;
                }
                else
                {
                    Node *num1_left = num1->prev;
                    Node *num1_right = num1->next;
                    Node *num2_left = num2->prev;
                    Node *num2_right = num2->next;

                    num1_left->next = num2;
                    num1->prev = num2_left;
                    num1->next = num2_right;
                    num1_right->prev = num2;
                    num2_left->next = num1;
                    num2->prev = num1_left;
                    num2->next = num1_right;
                    num2_right->prev = num1;
                }
            }
        }
    }
    //  swaps it1 & it2 addresses
    Node *temp = it1.current;
    it1.current = it2.current;
    it2.current = temp;
}
/*
///  ITERATOR CLASS //
*/

// Default ctor
template <typename T>
LL<T>::Iterator::Iterator()
{
    current = nullptr;
}

// ptr ctor
template <typename T>
LL<T>::Iterator::Iterator(Node *ptr)
{
    current = ptr;
}

// operator*
template <typename T>
T LL<T>::Iterator::operator*() const
{
    return current->data;
}

// operator++
template <typename T>
const typename LL<T>::Iterator &LL<T>::Iterator::operator++(int)
{
    // moves current to next node
    current = current->next;
    return *this;
}

// Operator--
template <typename T>
const typename LL<T>::Iterator &LL<T>::Iterator::operator--(int)
{
    // moves current to previous
    current = current->prev;
    return *this;
}

//==operator
template <typename T>
bool LL<T>::Iterator::operator==(const Iterator &rhs) const
{
    // checks to see if lhs and rhs are equal
    if (current == rhs.current)
    {
        return true;
    }
    return false;
}

//!=operator
template <typename T>
bool LL<T>::Iterator::operator!=(const Iterator &rhs) const
{
    // checks to see if lhs and rhs are equal
    if (current != rhs.current)
    {
        return true;
    }
    return false;
}