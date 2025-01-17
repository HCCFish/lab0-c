#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *q = malloc(sizeof(struct list_head));
    if (!q) {
        free(q);
        return NULL;
    }
    INIT_LIST_HEAD(q);
    return q;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;
    element_t *entry, *safe;
    list_for_each_entry_safe (entry, safe, l, list) {
        q_release_element(entry);
    }
    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head) {
        return false;
    }
    element_t *new_element = malloc(sizeof(element_t));
    if (!new_element) {
        free(new_element);
        return false;
    }
    size_t len = strlen(s);
    new_element->value = strdup(s);
    new_element->value[len] = '\0';
    list_add(&new_element->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head) {
        return false;
    }
    element_t *new_element = malloc(sizeof(element_t));
    if (!new_element) {
        free(new_element);
        return false;
    }
    size_t len = strlen(s);
    new_element->value = strdup(s);
    new_element->value[len] = '\0';
    list_add_tail(&new_element->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    element_t *head_element = list_first_entry(head, element_t, list);
    if (sp != NULL) {
        strncpy(sp, head_element->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
    list_del(&head_element->list);
    return head_element;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    element_t *head_element = list_last_entry(head, element_t, list);
    if (sp != NULL) {
        strncpy(sp, head_element->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
    list_del(&head_element->list);
    return head_element;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head) {
        return -1;
    }
    struct list_head *cur;
    int len = 0;
    list_for_each (cur, head) {
        len++;
    }
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || !head->next)
        return false;
    struct list_head *slow = head, *fast = head->next->next;
    while (fast != head && fast->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast != head) {
        slow->next = slow->next->next;
    }
    element_t *mid = list_entry(slow->next, element_t, list);
    list_del(&mid->list);
    q_release_element(mid);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
    if (!head)
        return;
    struct list_head *first, *second;
    for (struct list_head *cur = head->next; cur != head && cur->next != head;
         cur = cur->next) {
        first = cur;
        second = cur->next;
        first->next = second->next;
        second->next = first;
        second->prev = first->prev;
        first->prev = second;
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head)
        return;
    struct list_head *cur, *safe;
    list_for_each_safe (cur, safe, head) {
        list_move(cur, head);
    }
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
    if (!head || k < 2)
        return;
    struct list_head *cur, *safe, *tmp_head = head;
    LIST_HEAD(dummy);
    int i = 1;
    list_for_each_safe (cur, safe, head) {
        if (i == k) {
            list_cut_position(&dummy, tmp_head, cur);
            q_reverse(&dummy);
            list_splice_init(&dummy, tmp_head);
            i = 0;
            tmp_head = safe->prev;
        }
        i++;
    }
    q_free(&dummy);
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
