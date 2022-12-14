/*
Author: chankruze (chankruze@gmail.com)
Created: Thu Nov 10 2022 13:54:14 GMT+0530 (India Standard Time)

Copyright (c) geekofia 2022 and beyond
*/

#include <stdio.h>

#include "../lib/linked_list.h"

// 1. delete a node from end
void delete_from_end(struct node** head) {
  // if the list is empty, nothing to delete
  if (is_empty(*head)) {
    printf("[ERROR] The linked list is already empty.");
    return;
  }

  /**
   * 1. traverse upto {n}th (last) node, keeping track of curent and prev
   * 2. set {n-1}th (prev) node's next to NULL
   * 3. free the {n}th (current) node
   */

  struct node* current = *head;
  struct node* prev = *head;

  // while (temp->next->next) {
  //   temp = temp->next;
  // }

  // 1. traverse upto {n}th (last) node, keeping track of curent and prev
  while (current->next) {
    // update prev to current node
    prev = current;
    // update current to next node
    current = current->next;
  }

  // 2. set {n-1}th (prev) node's next to NULL
  prev->next = NULL;
  // 3. free the {n}th (current) node
  free(current);
}

// 2. delete a node from start
void delete_from_start(struct node** head) {
  // if the list is empty, nothing to delete
  if (is_empty(*head)) {
    printf("[ERROR] The linked list is already empty.");
    return;
  }

  /**
   * 1. update head to point to 2nd node's address
   * 2. free 1st node
   */

  struct node* first_node = *head;
  *head = first_node->next;
  free(first_node);
}

// 3. delete a node from a specific position
void delete_from_position(struct node** head, int position) {
  // if the list is empty, nothing to delete
  if (is_empty(*head)) {
    printf("[ERROR] The linked list is already empty.");
    return;
  }

  // check if the position is valid
  int total_nodes = count_nodes(*head);
  if (position > total_nodes) {
    printf("[ERROR] The list contains %d nodes. You are trying to delete the %dth node.\n", total_nodes, position);
  }

  /**
   * 1. travers the list upto {position}, keeping track of current and previous node.
   * 2. update the {position-1}th (prev) node to point to {position}th's (current's) next.
   * 3. free the {position}th (current) node
   */

  if (position == 1) {
    // store the first node address in a temp variable
    struct node* first_node = *head;
    // update the head to point to the 2nd node
    *head = first_node->next;
    // print the deleted node
    printf("deleted: ");
    print_node(first_node);
    // free the first node
    free(first_node);
    return;
  }

  struct node* current = *head;
  struct node* prev = *head;

  //  1. travers the list upto {position}, keeping track of current and previous node.
  for (int i = 2; i <= position; ++i) {
    prev = current;
    current = current->next;
  }

  // 2. update the {position-1}th (prev) node to point to {position}th's (current's) next.
  prev->next = current->next;
  // print the deleted node
  printf("deleted: ");
  print_node(current);
  // 3. free the{position} th(current) node
  free(current);
}

// 4. delete a node after a specific node having {data}
void delete_after_node(struct node** head, int data) {
  // if the list is empty, nothing to delete
  if (is_empty(*head)) {
    printf("[ERROR] The linked list is already empty.");
    return;
  }

  // temp node* to traverse and store the address of the current node
  struct node* current = *head;

  // 1. traverse upto the node having {data} as well as checking for next node
  while (data != current->data && current->next) {
    current = current->next;
  }

  // 2. if node having data is found
  if (data == current->data) {
    // 2.1 check if the node have any node after it
    if (current->next) {
      // 2.2 if the next node present, store it's address in temp var
      struct node* next_node = current->next;
      // update the current node to next node's next
      // it can be of 2 things:
      // 1. address of next after next
      // 2. NULL if the next node is the last
      current->next = next_node->next;
      // free the next node after the node having data
      free(next_node);
      return;
    }

    // 2.2 if control is here, it means the node having desired data is the last node
    // hence, current->next is NULL, no node to delete
    printf("[ERROR] There is no node to delete after the node having data %d.\n", data);
    return;
  }

  // if control is here, it means no node having the desired data found.
  printf("[ERROR] Node with data %d not found.\n", data);
}

int main(int argc, char const* argv[]) {
  // head/start of the linked list, default NULL to represent the list is empty
  struct node* head = NULL;
  // number of nodes to create (user input), default to 0
  int n = 0;
  // ask the user to enter a number for n
  printf("How many nodes do you want to create? (i.e. 4): ");
  // save the value of n
  scanf("%d", &n);
  // create linked list
  create_linked_list(&head, n);
  // print the original linked list
  print_linked_list(head);

  // 1. delete a node from the end
  delete_from_end(&head);
  // print the new linked list
  print_linked_list(head);

  // 2. delete a node from the start
  delete_from_start(&head);
  // print the new linked list
  print_linked_list(head);

  // 3. delete a node from a specific position
  int position;
  printf("Enter the postion from which you want to delete a node: ");
  scanf("%d", &position);
  delete_from_position(&head, position);
  // print the new linked list
  print_linked_list(head);

  // 4. delete a node after a specific node
  int data;
  printf("Enter the data of the node after which you want to delete a node: ");
  scanf("%d", &data);
  delete_after_node(&head, data);
  // print the new linked list
  print_linked_list(head);

  return 0;
}
