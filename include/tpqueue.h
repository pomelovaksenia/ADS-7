// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>

template<typename T>
class TPQueue {
  struct Item {
        T data;
        Item* next;
        Item* prev;
  };
  Item* head;
    Item* tail;
    Item* createItem(const T& data) {
        Item* newItem = new Item;
        newItem->data = data;
        newItem->next = nullptr;
        newItem->prev = nullptr;
        return newItem;
    }

 public:
    TPQueue() : head(nullptr), tail(nullptr) {}
    T pop() {
        if (!head)
            throw std::underflow_error("Queue is Empty!");
        Item* temp = head->next;
        T data = head->data;
        delete head;
        head = temp;
        return data;
    }
    void clear() {
        while (head)
            pop();
    }
    ~TPQueue() {
        clear();
    }
    void push(const T& newData) {
        if (head == nullptr) {
            head = createItem(newData);
            tail = head;
        } else if (tail->data.prior >= newData.prior) {
            if (tail->data.ch == newData.ch) {
              tail->data = newData;
            } else {
                tail->next = createItem(newData);
                tail->next->prev = tail;
                tail = tail->next;
            }
        } else if (head == tail) {
            tail->prev = createItem(newData);
            head = tail->prev;
            head->next = tail;
        }
        Item* item = tail;
        while (item != head && item->data.prior < newData.prior) {
          item = item->prev;
        }
        if (item->data.prior > newData.prior) {
            Item* newItem = createItem(newData);
            newItem->prev = item;
            newItem->next = item->next;
            item->next->prev = newItem;
            item->next = newItem;
        }
        if (item == head && item->data.prior < newData.prior) {
            head->prev = createItem(newData);
            head = head->prev;
            head->next = item;
        }
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
