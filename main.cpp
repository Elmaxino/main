#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <algorithm>
//#include "red_pokazivaci.h"
#include "red_polja.h"

using namespace std;

int generate( que *point ){
    int N;

    printf( "Koliko zapisa zelite generirati?: " ); scanf( "%d", &N );

    srand( time( NULL ) );

    for ( int i = 0; i < N; ++i ){

        pacijent tmp;

        tmp.a = rand() % 250 + 50;
        tmp.b = rand() % 250 + 50;
        tmp.c = rand() % 5 + 1;
        tmp.d = rand() % 4 + 1;
        tmp.e = rand() % 5 + 1;

        if ( tmp.c == 1 ){
            if ( tmp.e == 1 ) tmp.e = rand() % 4 + 2;
            if ( tmp.d == 3 || tmp.d == 4 ) tmp.d = rand() % 2 + 1;
        }

        if ( tmp.c == 3 || tmp.c == 4 && tmp.e == 4 ){
            while ( tmp.e == 4 ) tmp.e = rand() % 5 + 1;
        }

        en_queueQ( tmp, point );

    }

    return N;
}

bool cmp( const pacijent &A, const pacijent &B ){
    return A.c < B.c;
}

void sortiraj( que *point ){
    pacijent niz[10001];
    int i = 0;

    while ( !is_emptyQ( point ) ){
        niz[i++] = frontQ( point );
        de_queueQ( point );
    }

    sort( niz, niz + i, cmp );

    for ( int k = 0; k < i; ++k ){
        en_queueQ( niz[k], point );
    }
}

void dodaj( que *point ){
    char m_ime[12][10] = { "Luka", "Ivan", "Jakov", "Marko", "Josip", "Ivano", "Filip", "David", "Daniel", "Antonio" };
    char z_ime[12][10] = { "Lucija", "Ema", "Lana", "Mia", "Lara", "Ana", "Petra", "Eva", "Sara", "Iva" };
    char prezime[12][15] = { "Horvat", "Kovacevic", "Babic", "Maric", "Novak", "Juric", "Kovacic", "Vukovic", "Knezevic", "Markovic" };
    char spol[2][2] = { "M", "Z" };
    pacijent trodupli[10000], tmp[1000];
    int i = 0, novi_i = 0;

    while ( !is_emptyQ( point ) ){
        tmp[i++] = frontQ( point );
        de_queueQ( point );
    }

    for ( int j = 0; j < i; ++j ){
        if ( tmp[j].dan ){ en_queueQ( tmp[j], point ); continue; }

        for ( int k = 0; k < 3; ++k ){
            trodupli[novi_i] = tmp[j];

            strcpy( trodupli[novi_i].spol, spol[ rand() % 2 ] );
            strcpy( trodupli[novi_i].prez, prezime[ rand() % 10 ] );

            trodupli[novi_i].dan = rand() % 31 + 1;
            trodupli[novi_i].mjes = rand() % 12 + 1;

            if ( trodupli[novi_i].c == 4 ) trodupli[novi_i].god = rand() % 6 + 2007;
            else trodupli[novi_i].god = rand() % 45 + 1930;

            if ( trodupli[novi_i].spol[0] == 'M' ){
                strcpy( trodupli[novi_i].ime, m_ime[ rand() % 10 ] );

                if ( trodupli[novi_i].c == 3 ) while ( trodupli[novi_i].c == 3 ) trodupli[novi_i].c = rand() % 5 + 1;
            }
            else strcpy( trodupli[novi_i].ime, z_ime[ rand() % 10 ] );

            en_queueQ( trodupli[novi_i], point );

            ++novi_i;
        }
    }

    sortiraj( point );

    printf( "Pacijenti stariji od 25 godina koji idu oftalmologu: \n" );

    for ( int k = 0; k < novi_i; ++k ){
        if ( trodupli[k].god < 1985 && trodupli[k].e == 2 ) printf( "%s %s - Godiste: %d\n", trodupli[k].ime, trodupli[k].prez, trodupli[k].god );
    }   printf( "\n" );
}

void ispis( que *point ){
    pacijent niz[1000];
    int i = 0, cnt = 0;

    char prio[6][30] = { "Hitni slucaj", "Invalid", "Trudnica", "Djeca mlada od 6 god", "Ostali pacijenti" };
    char usluga[5][20] = { "Pregled", "Previjanje", "Recepti", "Uputnice" };
    char ordi[6][30] = { "Obiteljska medicina", "Oftalmologija", "Dermatovenerologija", "Ginekologija", "Urologija" };

    while ( !is_emptyQ( point ) ){
        niz[i++] = frontQ( point );
        de_queueQ( point );
    }

    for ( int k = 0; k < i; ++k ){
        ++cnt;
        printf( "Ime: %s\nPrezime: %s\n", niz[k].ime, niz[k].prez );
        printf( "Spol: %s\nDatum: %d.%d.%d.\n", niz[k].spol, niz[k].dan, niz[k].mjes, niz[k].god );
        printf( "Prioritet: %s\nVrsta usluge: %s\nVrsta ordinacije: %s\n\n", prio[ niz[k].c - 1 ], usluga[ niz[k].d - 1 ], ordi[ niz[k].e - 1 ] );

        en_queueQ( niz[k], point );
    }

    printf( "Broj zapisa: %d\n\n", cnt );
}

int invalidi( que *point ){
    printf( "Stanje na pocetku: \n" );
    ispis( point );

    pacijent niz[1000];
    int i = 0;

    while ( !is_emptyQ( point ) ){
        if ( frontQ( point ).c != 2 ) niz[i++] = frontQ( point );
        else {
            if ( frontQ( point ).god > 1962 ) niz[i++] = frontQ( point );
        }
        de_queueQ( point );
    }

    for ( int k = 0; k < i; ++k ){
        en_queueQ( niz[k], point );
    }

    printf( "Stanje poslije: \n" );
    ispis( point );

    return i;
}

que *brzi_que = initQ( brzi_que );

void brzi( int K, int curr, que *point ){
    if ( is_emptyQ( point ) ) return;

    pacijent tmp = frontQ( point );
    de_queueQ( point );
    brzi( K, curr - 1, point );

    if ( curr < K * 30 / 100 + 1 ){
        if ( tmp.d == 3 || tmp.d == 4 ) en_queueQ( tmp, brzi_que );
        else en_queueQ( tmp, point );
    }
    else en_queueQ( tmp, point );
}

void pocetno( que *point ){
    if ( is_emptyQ( point ) ) return;

    pacijent tmp = frontQ( point );
    de_queueQ( point );

    pocetno( point );

    en_queueQ( tmp, point );
}

int main( void ){

    que *point = initQ( point );

    int M, len;

    do {

        printf( "1. Generiranje brojeva\n" );
        printf( "2. Upis pacijenata\n" );
        printf( "3. Brisanje invalida starijih od 50 godina\n" );
        printf( "4. Red brzih usluga\n" );
        printf( "9. Izlaz iz programa\n\n" );

        scanf( "%d", &M );

        switch( M ){
            case 1: len = generate( point ) * 3; break;
            case 2: dodaj( point ); break;
            case 3: len = invalidi( point ); break;
            case 4:
                brzi( len, len, point );
                printf( "Brzi red: \n" ); ispis( brzi_que );
                pocetno( point );
                printf( "Spori red: \n" ); ispis( point );
                break;

            default: printf( "Kraj programa!\n" ); break;
        }

    } while ( M != 9 );

    return 0;
}
