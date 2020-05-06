/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q)
    {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q)
    {
        list_ele_t *curr = q->head;
        while (curr)
        {
            list_ele_t *item = curr;
            curr = curr->next;
            free(item->value);
            free(item);
        }

        free(q);
    }
}

static int string_length(char *s)
{
    int count = 0;
    while (s[count] != '\0')
    {
        count += 1;
    }
    return count + 1; // include null character.
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
    { // q is NULL.
        return false;
    }

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
    { // fail to allocate space.
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    char *val = malloc(sizeof(char) * string_length(s));
    /* What if either call to malloc returns NULL? */
    if (!val)
    {
        free(newh);
        return false;
    }

    strcpy(val, s);
    newh->value = val;
    newh->next = q->head;
    q->head = newh;

    /* If q->tail is NULL, which means we are inserting to an empty queue. */
    /* So tail should point to newh. */
    /* Otherwise, q->tail is unchanged. */
    if (!q->tail)
    {
        q->tail = newh;
    }

    /* Increment size value. */
    q->size += 1;

    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    if (!q)
    {
        return false;
    }

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (!newt)
    {
        return false;
    }

    char *val = malloc(sizeof(char) * string_length(s));
    if (!val)
    {
        free(newt);
        return false;
    }

    strcpy(val, s);
    newt->value = val;
    newt->next = NULL;

    if (q->tail)
    {
        q->tail->next = newt;
        q->tail = newt;
    }
    else
    { // we are inserting to an empty queue.
        q->head = newt;
        q->tail = newt;
    }

    /* Increment size value. */
    q->size += 1;

    /* Remember: It should operate in O(1) time */
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q || !q->head)
    { // q is NULL or q is empty.
        return false;
    }

    list_ele_t *item = q->head;
    list_ele_t *new_head = q->head->next;

    /* If sp is not NULL, copy as much as possible to sp. */
    if (sp)
    {
        int i;
        for (i = 0; i < bufsize - 1 && item->value[i] != '\0'; i += 1)
        {
            sp[i] = item->value[i];
        }
        sp[i] = '\0';
    }

    /* Free list element and string. */
    free(item->value);
    free(item);

    /* Update queue head. */
    q->head = new_head;

    /* Update size. */
    q->size -= 1;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
    {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (!q || q->size == 0 || q->size == 1)
    {
        return;
    }

    list_ele_t *old_head = q->head;
    list_ele_t *old_tail = q->tail;
    list_ele_t *curr = q->head, *prev = NULL, *next = NULL;
    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    q->head = old_tail;
    q->tail = old_head;
}
