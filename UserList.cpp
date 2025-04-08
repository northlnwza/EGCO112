#include "UserList.h"
#include <iostream>

UserNode::UserNode(User u) : data(u), next(nullptr) {}

UserList::UserList() : head(nullptr) {}

void UserList::addUser(User user) {
    UserNode* newNode = new UserNode(user);
    if (!head || user.getUsername() < head->data.getUsername()) {
        newNode->next = head;
        head = newNode;
    } else {
        UserNode* current = head;
        while (current->next && current->next->data.getUsername() < user.getUsername())
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
    }
}

void UserList::displayUsers() {
    UserNode* temp = head;
    while (temp) {
        temp->data.display();
        temp = temp->next;
    }
}
