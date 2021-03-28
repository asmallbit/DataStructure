int reserveData(List list){
    if(list->n<=0){
        printf("This list is a null list!\n");
        return 0;
    }
    List temp = (List)malloc(sizeof(struct Test));
    temp->num = (DataType*)malloc(sizeof(DataType[1]));
    int i, j;
    temp->n = temp->max = 1;
    j = list->n - 1;
    for(i=0;i<(list->n)/2;i++){
        temp->num[0] = list->num[i];
        list->num[i] = list->num[j];
        list->num[j] = temp->num[0];
        j--;
    }
    free(temp->num);
    free(temp);
    return 1;
}
