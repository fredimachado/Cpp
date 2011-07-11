template <class T>
class Stack
{
    public:
        Stack(int = 10) ; 
        ~Stack() { delete[] stackPtr; }
        int push(const T&); 
        int pop(T&);
        int isEmpty() const { return top == -1; } 
        int isFull() const { return top == size - 1; } 

    private:
        int size;
        int top;  
        T* stackPtr;  
};

template <class T>
Stack<T>::Stack(int s)
{
    size = s > 0 && s < 1000 ? s : 10;  
    top = -1;
    stackPtr = new T[size];
}

template <class T>
int Stack<T>::push(const T& item)
{
    if (!isFull())
    {
        stackPtr[++top] = item;
        return 1;
    }
    return 0;
}

template <class T> 
int Stack<T>::pop(T& popValue) 
{
    if (!isEmpty())
    {
        popValue = stackPtr[top--];
        return 1;
    }
    return 0;
}
