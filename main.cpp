#include <iostream>

class Pinacle
{
private:
    struct Node
    {
        int data;
        int index;
        Node *next;
        Node(int dataToStore) : data(dataToStore), next(nullptr), index(-1)
        {
        }
    };
    Node *front;
    Node *back;
    int totalNodes;

public:
    Pinacle() : front(nullptr), back(nullptr), totalNodes(0)
    {
    }
    void show();
    int getTotalNodes();
    void addFront(int dataToStore);
    void addBack(int dataToStore);
    void add(int dataToStore, int index);
    void removeFront();
    void removeBack();
    void remove(int index);
};

void Pinacle::show()
{
    Node *cursor = front;
    if (cursor == nullptr)
    {
        std::cout << "Nothing to Show ! " << std::endl;
        return;
    }
    std::cout << "Total Nodes : " << getTotalNodes() << std::endl;
    while (cursor != nullptr)
    {
        std::cout << cursor->data << " [" << cursor->index << "]" << std::endl;
        cursor = cursor->next;
    }
    std::cout << std::endl;
}

int Pinacle::getTotalNodes()
{
    return totalNodes;
}

void Pinacle::addFront(int dataToStore)
{
    Node *newNode = new Node(dataToStore);
    if (!newNode)
    {
        std::cout << "Out of Memory ! " << std::endl;
        return;
    }
    newNode->index = 0;
    totalNodes++;
    if (front == nullptr && back == nullptr)
    {
        front = back = newNode;
    }
    else
    {
        Node *cursor = front;
        while (cursor != nullptr)
        {
            cursor->index++;
            cursor = cursor->next;
        }
        newNode->next = front;
        front = newNode;
    }
    std::cout << "Added to Front : " << front->data << std::endl;
    std::cout << "Total Nodes : " << getTotalNodes() << std::endl;
    newNode = nullptr;
}

void Pinacle::addBack(int dataToStore)
{
    Node *newNode = new Node(dataToStore);
    if (!newNode)
    {
        std::cout << "Out of Memory ! " << std::endl;
        return;
    }
    newNode->index = totalNodes;
    totalNodes++;
    if (front == nullptr && back == nullptr)
    {
        front = back = newNode;
    }
    else
    {
        back->next = newNode;
        back = newNode;
    }
    std::cout << "Added to Back : " << back->data << std::endl;
    std::cout << "Total Nodes : " << getTotalNodes() << std::endl;
    newNode = nullptr;
}

void Pinacle::add(int dataToStore, int index)
{
    if (index == 0)
    {
        addFront(dataToStore);
        return;
    }
    else if (index == totalNodes)
    {
        addBack(dataToStore);
        return;
    }
    else
    {
        Node *newNode = new Node(dataToStore);
        if (!newNode)
        {
            std::cout << "Out of Memory ! " << std::endl;
            return;
        }
        newNode->index = index;
        Node *cursor = front;
        while (cursor->index == index - 1)
        {
            cursor = cursor->next;
        }
        newNode->next = cursor->next;
        cursor->next = newNode;
        cursor = newNode->next;
        while (cursor != nullptr)
        {
            cursor->index++;
            cursor = cursor->next;
        }
        totalNodes++;
        std::cout << "Added at " << newNode->index << " : " << newNode->data << std::endl;
        std::cout << "Total Nodes : " << getTotalNodes() << std::endl;
        newNode = nullptr;
    }
}

void Pinacle::removeFront()
{
    if (front == nullptr)
    {
        std::cout << "No Element Found to Remove" << std::endl;
        return;
    }
    else if (front == back)
    {
        std::cout << "Removed : " << front->data << " (was at " << front->index << ")" << std::endl;
        delete front;
        front = back = nullptr;
        totalNodes--;
    }
    else
    {
        Node *save = front;
        front = front->next;
        Node *cursor = front;
        while (cursor != nullptr)
        {
            cursor->index--;
            cursor = cursor->next;
        }
        totalNodes--;
        std::cout << "Removed : " << save->data << " (was at " << save->index << ")" << std::endl;
        delete save;
        save = nullptr;
    }
    std::cout << "Total Nodes : " << getTotalNodes() << std::endl;
}

void Pinacle::removeBack()
{
    if (back == nullptr)
    {
        std::cout << "No Element Found to Remove" << std::endl;
        return;
    }
    else if (front == back)
    {
        std::cout << "Removed : " << back->data << " (was at " << back->index << ")" << std::endl;
        delete back;
        back = front = nullptr;
        totalNodes--;
    }
    else
    {
        Node *save = back;
        Node *cursor = front;
        while (cursor->index != back->index - 1)
        {
            cursor = cursor->next;
        }
        back = cursor;
        back->next = nullptr;
        totalNodes--;
        std::cout << "Removed : " << save->data << " (was at " << save->index << ")" << std::endl;
        delete save;
        save = nullptr;
    }
    std::cout << "Total Nodes : " << getTotalNodes() << std::endl;
}

void Pinacle::remove(int index)
{
    if (index == 0)
    {
        removeFront();
        return;
    }
    else if (index == totalNodes - 1)
    {
        removeBack();
        return;
    }
    else
    {
        Node *cursor = front;
        while (cursor->index != index - 1)
        {
            cursor = cursor->next;
        }
        Node *save = cursor->next;
        cursor->next = (cursor->next)->next;
        std::cout << "Removed : " << save->data << " (was at " << save->index << ")" << std::endl;
        cursor = save->next;
        while (cursor != nullptr)
        {
            cursor->index--;
            cursor = cursor->next;
        }
        delete save;
        save = nullptr;
    }
    std::cout << "Total Nodes : " << getTotalNodes() << std::endl;
}

int main()
{
    Pinacle pinacle;
    pinacle.addFront(5);
    pinacle.addFront(6);
    pinacle.addBack(10);
    pinacle.addBack(8);
    pinacle.remove(0);

    pinacle.show();
}