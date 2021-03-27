//删除单链表中重复的元素
int deleteRepeatThings_link(LinkList list){
    if(list->link==NULL){
        printf("This is a null list.\n");
        return 0;
    }
    pNode q, next, p=list->link;
    DataType x;
    while(p->link!=NULL){
        x = p->info;
        q = p;
        while(q->link!=NULL){
            if(q->link->info==x){
                next = q->link;
                q->link = q->link->link;
                free(next);
            }
            else{
                q = q->link;
            }
        }
        p = p->link;

    }
}
