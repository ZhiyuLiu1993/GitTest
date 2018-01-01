#include <stdio.h>
#include <stdlib.h>

#define TAILQ_HEAD(name, type)              \
struct name {                       \
    struct type *tqh_first; /* first element */ \
    struct type **tqh_last; /* addr of last next element */\
}

#define TAILQ_ENTRY(type)                   \
struct {                            \
    struct type *tqe_next;  /* next element */      \
    struct type **tqe_prev;/* addr of previous next element*/ \
}

#define TAILQ_INIT(head) do {               \
    (head)->tqh_first = NULL;                \
    (head)->tqh_last = &(head)->tqh_first;        \
} while (0)

#define TAILQ_INSERT_TAIL(head, elm, field) do {        \
    (elm)->field.tqe_next = NULL;            \
    (elm)->field.tqe_prev = (head)->tqh_last;     \
    *(head)->tqh_last = (elm);               \
    (head)->tqh_last = &(elm)->field.tqe_next;        \
} while (0)

#define TAILQ_INSERT_BEFORE(listelm, elm, field) do {       \
    (elm)->field.tqe_prev = (listelm)->field.tqe_prev;    \
    (elm)->field.tqe_next = (listelm);           \
    *(listelm)->field.tqe_prev = (elm);          \
    (listelm)->field.tqe_prev = &(elm)->field.tqe_next;   \
} while (0)
#define TAILQ_FIRST(head)       ((head)->tqh_first)

#define TAILQ_NEXT(elm, field)      ((elm)->field.tqe_next)
#define TAILQ_LAST(head, headname)                  \
     (*(((struct headname *)((head)->tqh_last))->tqh_last))
/* XXX */
#define TAILQ_PREV(elm, headname, field)                \
    (*(((struct headname *)((elm)->field.tqe_prev))->tqh_last))


struct QUEUE_ITEM{
    int value;
    TAILQ_ENTRY(QUEUE_ITEM) entries;
};
TAILQ_HEAD(queue_list,QUEUE_ITEM) queue_head;

int main(){
    struct QUEUE_ITEM *item;
    struct QUEUE_ITEM *tmp_item;

    TAILQ_INIT(&queue_head);
    int i=0;
    for(i=5;i<10;i+=2){
        item=(QUEUE_ITEM *)malloc(sizeof(item));
        item->value=i;
        TAILQ_INSERT_TAIL(&queue_head, item, entries);
    }

    struct QUEUE_ITEM *ins_item;
    ins_item=(QUEUE_ITEM *)malloc(sizeof(ins_item));

    ins_item->value=100;
    TAILQ_INSERT_BEFORE(item,ins_item,entries);

    tmp_item=TAILQ_LAST(&queue_head,queue_list);
    printf("last element is %d\n",tmp_item->value);


    tmp_item=TAILQ_FIRST(&queue_head);
    printf("first element is %d\n",tmp_item->value);

    tmp_item=TAILQ_NEXT(tmp_item,entries);
    printf("next element is %d\n",tmp_item->value);

    tmp_item=TAILQ_PREV(tmp_item,queue_list,entries);
    printf("prevsious element is %d\n",tmp_item->value);

    tmp_item=TAILQ_NEXT(tmp_item,entries);
    printf("next element is %d\n",tmp_item->value);

    tmp_item=TAILQ_NEXT(tmp_item,entries);
    printf("next element is %d\n",tmp_item->value);
}


