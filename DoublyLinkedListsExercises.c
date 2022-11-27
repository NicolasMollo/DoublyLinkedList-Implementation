#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <stddef.h>

struct list_node
{
    struct list_node *prev;
    struct list_node *next;
};

struct list_node *list_pop(struct list_node **head)
{
    struct list_node *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

struct list_node *list_get_tail(struct list_node **head)
{
    struct list_node *current_node = *head;
    struct list_node *last_node = NULL;

    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    return last_node;
};

struct list_node *list_append(struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}

struct list_node *list_remove_item(struct list_node **head, const int index_to_remove)
{
    struct list_node *current_node = *head;
    struct list_node *previous_node = NULL;

    for (int i = 0; i < index_to_remove; i++)
    {
        previous_node = current_node;
        current_node = current_node->next;
    }

    if (previous_node)
    {
        previous_node->next = current_node->next;
    }
    else
    {
        *head = current_node->next;
    }

    if (current_node->next)
    {
        current_node->next->prev = previous_node;
    }

    return current_node;
}

void list_insert_after(struct list_node **head, struct list_node *item, const int position)
{
    struct list_node *temp = *head;

    if (!temp)
    {
        puts("Your list does not exist");
    }

    for (int i = 0; i < position; i++)
    {
        temp = temp->next;
    }

    item->next = temp->next;
    temp->next = item;
    item->prev = temp;
};

void list_insert_before(struct list_node **head, struct list_node *item, const int position)
{
    struct list_node *temp = *head;

    if (!temp)
    {
        puts("Your list does not exist");
    }

    for (int i = 0; i < position; i++)
    {
        temp = temp->next;
    }

    temp->prev->next = item;
    temp->prev = item;
    item->next = temp;
};

struct string_item
{
    struct list_node node;
    const char *string;
};

struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}

int main()
{
    struct string_item *my_linked_list = NULL;
    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Hello World"));
    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test001"));
    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test002"));
    list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Last Item of the Linked List"));
    struct string_item *string_item = my_linked_list;

    list_remove_item((struct list_node **)&my_linked_list, 2);

    // list_insert_after((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("New element"), 3);
    // list_insert_before((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("New element"), 0);

    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item *)string_item->node.next;
    }

    return 0;
}