#define MAXN 100000

struct pacijent{
    char ime[10], prez[20], spol[2];
    int a, b, c, d, e, dan, mjes, god;
};

struct que{
    pacijent node[MAXN + 5];
    int rear, front;
};

int add_one( int N ){
    return ( N + 1 ) % MAXN;
}

que *initQ( que *point ){
    point = new que;

    point -> rear = MAXN - 1;
    point -> front = 0;

    return point;
}

bool is_emptyQ( que *point ){
    if ( add_one( point -> rear ) == point -> front ) return true;
    return false;
}

pacijent frontQ( que *point ){
    if ( !is_emptyQ( point ) ) return point -> node[point -> front];
}

void en_queueQ( pacijent A, que *point ){
    point -> node[ add_one( point -> rear ) ] = A;
    point -> rear = add_one( point -> rear );
}

void de_queueQ( que *point ){
    point -> front = add_one( point -> front );
}
