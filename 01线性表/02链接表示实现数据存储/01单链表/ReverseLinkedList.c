//逆置单链表中的元素
int reverseLinkedList(pList list){
    if(list==NULL){
        printf("This is a NULL list!\n");
        return 0;
    }
    pNode p, q, next;
    q = NULL;
    p = list;
    while(p!=NULL){
        next = p->next;
        p->next = q;
        q = p;
        p =next;
    }
    return 1;
}
