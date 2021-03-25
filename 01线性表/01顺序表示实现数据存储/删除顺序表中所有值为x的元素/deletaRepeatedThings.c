//删掉顺序表中与指定值元素重复的项
int deleteRepeatedThings(List list, DataType x){
    if(list==NULL){
        printf("This list is a null list");
        return 0;
    }
    int counter=0, i=0, j;
    while (i<list->n)
    {
        if(list->num[i]==x){
            counter++;
            if(counter>1){
                //删除元素
                for(j=i+1;j<list->n;j++){
                    list->num[j-1] = list->num[j];
                }
                i--;
                list->n--;
            }
        }
        i++;
    }
    return 1;
}
