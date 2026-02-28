#include "../dsa.hpp"

class LinkedList {
private:

    struct Node {
        int content;
        Node* next;
    };

    Node* root;

    void create_root(int content) {
        if (root)
            return ;
        root = new Node;
        root->content = content;
        root->next = nullptr;
    }

    static void clear(Node& node){
        node.content = 0;
    }

    static void destroy(Node* node) {
        delete node;
    }

    static void print_node(Node& node) {
        std::cout << node.content;
        if (node.next) std::cout << " -> ";
    }


    void iterate_apply(void (*fn)(Node&)) {
        Node* current = root;

        while (current) {
            fn(*current);
            current = current->next;
        }
    }

    void iterate_consume(void (*fn)(Node*)) {
        Node* current = root;

        while (current) {
            Node* next = current->next;
            fn(current);
            current = next;
        }
        root = nullptr;
    }

    Node* new_node(int content) {
        Node* node = new Node;
        node->content = content;
        node->next = nullptr;
        return node;
    }

public:
    LinkedList(int content) : root(nullptr) {
        create_root(content);
    }

    ~LinkedList(){
        iterate_consume(destroy);
    }

    void push_back(int content) {
        if (!root) { create_root(content); return; }
        Node* current = root;
        while (current->next)
            current = current->next;
        current->next = new_node(content);
    }

    void push_front(int content) {
        Node* node = new_node(content);
        node->next = root;
        root = node;
    }

    void pop_front() {
        if (!root) return;
        Node* old = root;
        root = root->next;
        destroy(old);
    }

    void pop_back() {
        if (!root) return;
        if (!root->next) { destroy(root); root = nullptr; return; }
        Node* current = root;
        while (current->next->next)
            current = current->next;
        destroy(current->next);
        current->next = nullptr;
    }

    bool remove(int content) {
        if (!root) return false;
        if (root->content == content) { pop_front(); return true; }
        Node* current = root;
        while (current->next) {
            if (current->next->content == content) {
                Node* target = current->next;
                current->next = target->next;
                destroy(target);
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool contains(int content) {
        Node* current = root;
        while (current) {
            if (current->content == content) return true;
            current = current->next;
        }
        return false;
    }

    int size() {
        int count = 0;
        Node* current = root;
        while (current) { ++count; current = current->next; }
        return count;
    }

    void print() {
        iterate_apply(print_node);
        std::cout << "\n";
    }

};

int main(){
    int dbg_num = 10;
    {
        LinkedList list(5);

        list.print();
        list.contains(5);
        list.push_back(1);
        list.push_front(1);
        list.print();
    }
}