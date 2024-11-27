template <typename T>
class Node
{
private:
    T item; // A data item
    Node<T>* next; // Pointer to next node
    int priority;
public:
    Node();
    Node(const T& Item, int Priority);
    Node(const T& r_Item);
    Node(const T& r_Item, Node<T>* nextNodePtr);
    void setItem(const T& r_Item);
    void setNext(Node<T>* nextNodePtr);
    T getItem() const;
    Node<T>* getNext() const;
    int GetPriority() const;
    void SetPriority(int p);
}; // end Node

template < typename T>
Node<T>::Node()
{
    next = nullptr;
    priority = 0;
}

template<typename T>
inline Node<T>::Node(const T& Item, int Priority)
{
    item = Item;
    priority = Priority;
}

template < typename T>
Node<T>::Node(const T& r_Item)
{
    item = r_Item;
    next = nullptr;
    priority = 0;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr)
{
    item = r_Item;
    next = nextNodePtr;
}
template < typename T>
void Node<T>::setItem(const T& r_Item)
{
    item = r_Item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
    next = nextNodePtr;
}

template < typename T>
T Node<T>::getItem() const
{
    return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
    return next;
}

template<typename T>
inline int Node<T>::GetPriority() const
{
    return priority;
}

template<typename T>
inline void Node<T>::SetPriority(int p)
{
    priority = p;
}