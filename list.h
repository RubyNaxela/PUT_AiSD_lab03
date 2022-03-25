#include <iostream>

template<typename _Tp>
class array_list {

    int size = 0;
    _Tp* data;

public:
    void add_at_begin(_Tp value);

    void add_at_end(_Tp value);

    void add_at_position(_Tp value, int position);

    void display();
};

template<typename _Tp>
void array_list<_Tp>::add_at_begin(_Tp value) {
    _Tp* new_data = new _Tp[size + 1];
    new_data[0] = value;
    for (int i = 0; i < size; i++) new_data[i + 1] = data[i];
    size++;
    data = new_data;
}

template<typename _Tp>
void array_list<_Tp>::add_at_end(_Tp value) {
    _Tp* new_data = new _Tp[size + 1];
    new_data[size] = value;
    for (int i = 0; i < size; i++) new_data[i] = data[i];
    size++;
    data = new_data;
}

template<typename _Tp>
void array_list<_Tp>::add_at_position(_Tp value, int position) {
    _Tp* new_data = new _Tp[size + 1];
    new_data[position] = value;
    for (int i = 0; i < position; i++) new_data[i] = data[i];
    for (int i = position; i < size; i++) new_data[i + 1] = data[i];
    size++;
    data = new_data;
}

template<typename _Tp>
void array_list<_Tp>::display() {
    for (int i = 0; i < size; i++) std::cout << data[i] << " ";
}

///////////////////////////////////////////////////////////////////////////////////////////

template<typename _Tp>
class linked_list {

    struct node {
        _Tp klucz;
        struct node* next; //pole wskaznikowe - pamietamy wskazanie do nastepnego wezla
    };

    node* head = nullptr;

public:
    void add_at_begin(_Tp value);

    void delete_from_begin();

    void add_at_end(_Tp value);

    void delete_from_end();

    void add_at_position(_Tp value, int position);

    void delete_from_position(int position);

    void display();
};

template<typename _Tp>
void linked_list<_Tp>::add_at_begin(_Tp value) {
    node* element = (node*) malloc(sizeof(node));
    element->klucz = value; //wskaznik na strukture wskazuje na pole klucz, ktoremu przypiszemy liczbe
    element->next = head; // element musi miec nastepnik
    head = element; //nowy poczatek listy
}

template<typename _Tp>
void linked_list<_Tp>::delete_from_begin() {
    node* element = head;
    if (element != nullptr) {
        head = element->next; //nowy poczatek
        free(element); //usun z pamieci
    }

}

template<typename _Tp>
void linked_list<_Tp>::add_at_end(_Tp value) {
    node* tmp = head;
    node* element = (node*) malloc(sizeof(node));
    while (tmp->next != nullptr) tmp = tmp->next;
    element->klucz = value;
    element->next = nullptr;
    tmp->next = element;
}

template<typename _Tp>
void linked_list<_Tp>::delete_from_end() {
    node* tmp, * element;
    tmp = head;
    element = head;
    while (tmp->next != nullptr) {
        element = tmp;
        tmp = tmp->next;
    }
    element->next = nullptr;
    free(tmp);
}

template<typename _Tp>
void linked_list<_Tp>::add_at_position(_Tp value, int position) {
    node* tmp = head;
    auto* element = (node*) malloc(sizeof(node));
    element->klucz = value;
    element->next = nullptr;
    while (position != 2) {
        tmp = tmp->next;
        position--;
    }
    element->next = tmp->next;
    tmp->next = element;
}

template<typename _Tp>
void linked_list<_Tp>::delete_from_position(int position) {
    node* tmp, * element;
    tmp = head;
    while (position != 2) {
        tmp = tmp->next;
        position--;
    }
    element = tmp->next;
    tmp->next = element->next;
    free(element);
}

template<typename _Tp>
void linked_list<_Tp>::display() {
    node* element = head; //wskaznik element do iterowania
    while (element != nullptr) { // do konca listy, ostatni element ma wskaznik na nullptr
        std::cout << element->klucz << " ";
        element = element->next;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////

template<typename _Tp>
class bi_linked_list {

    struct node {
        _Tp key;
        struct node* prev;
        struct node* next;
    };

    int size = 5;
    node* head = nullptr;
    node* tail = nullptr;

    void add_at_position(_Tp value, int position);

    void add_at_begin(_Tp value);

    void display();

    int get_size();
};

template<typename _Tp>
void bi_linked_list<_Tp>::add_at_position(_Tp value, int position) {
    if (position < size / 2) {
        node* tmp = head;
        node* element = (node*) malloc(sizeof(node));
        element->key = value;
        element->next = nullptr;
        element->prev = nullptr;
        while (position != 2) {
            tmp = tmp->next;
            position--;
        }
        element->next = tmp->next;
        tmp->next = element;
        element->prev = tmp;
    } else {
        node* tmp = tail;
        node* element = (node*) malloc(sizeof(node));
        element->key = value;
        element->next = nullptr;
        element->prev = nullptr;
        while (position != 2) {
            tmp = tmp->prev;
            position--;
        }
        element->next = tmp->next;
        tmp->next = element;
        element->prev = tmp;
    }
}

template<typename _Tp>
void bi_linked_list<_Tp>::add_at_begin(_Tp value) {
    if (head == nullptr) {
        node* element = (node*) malloc(sizeof(node));
        head->prev = nullptr;
        head->next = nullptr;
        head->key = value;
        tail = head;
    } else {
        node* element = (node*) malloc(sizeof(node));
        element->key = value;
        element->next = head;
        head->prev = element;
        element->prev = nullptr;
        head = element;
    }
}

template<typename _Tp>
void bi_linked_list<_Tp>::display() {
    node* ptr = head;
    while (ptr != nullptr) {
        std::cout << ptr->key << " ";
        ptr = ptr->next;
    }
}

template<typename _Tp>
int bi_linked_list<_Tp>::get_size() {
    return size;
}