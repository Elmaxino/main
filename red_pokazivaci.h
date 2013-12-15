struct pacijent{
    char ime[10], prez[20], spol[2];
    int a, b, c, d, e, dan, mjes, god;
};

struct listnode{
    pacijent node;
    listnode *next;
};

struct que{
    listnode *rear, *front;
};

que *initQ( que *point ){
    point = new que;
    listnode *list = new listnode;

    list -> next = NULL;

    point -> rear = point -> front = list;

    return point;
}

bool is_emptyQ( que *point ){
    if ( point -> rear == point -> front ) return true;
    return false;
}

pacijent frontQ( que *point ){
    if ( !is_emptyQ( point ) ) return point -> front -> next -> node;
}

void en_queueQ( pacijent A, que *point ){
    listnode *new_node = new listnode;
    new_node -> node = A;

    point -> rear -> next = new_node;
    point -> rear = new_node;
    new_node -> next = NULL;
}

void de_queueQ( que *point ){
    listnode *first = point -> front;
    point -> front = first -> next;

    delete first;
}
