void triInsertion( int nbrElement, void * tableau[nbrElement],
                   int (* fct_vientAvant)( void *, void * ) )
{
    int i = 0;
    int j = 0;
    for( i = 1; i < nbrElement; i++ ) {
        for( j = i; j > 0; j-- ) {
            if( ! (*fct_vientAvant)( tableau[j - 1], tableau[j] ) ) {
                void * temporaire = tableau[j - 1];
                tableau[j - 1] = tableau[j];
                tableau[j] = temporaire;
            }
        }
    }
}

int chaineOrdreCroissant( void * element1, void * element2 )
{
    return strcmp( (char *)element1, (char *)element2 ) < 0 ;
}

int chaineOrdreDecroissant( void * element1, void * element2 )
{
    return strcmp( (char *)element1, (char *)element2 ) > 0 ;
}

int main( int argc, char ** argv )
{
    int i = 0;
    triInsertion( argc, (void **)argv, chaineOrdreCroissant );
    for( i = 0; i < argc; i ++ ) {
        printf( "%s", argv[i] );
        if( i == argc - 1 ) {
            printf( "\ n");
        } else {
            printf( ", " );
        }
    }
    triInsertion( argc, (void **)argv, chaineOrdreDecroissant );
    for( i = 0; i < argc; i ++ ) {
        printf( "%s", argv[i] );
        if( i == argc - 1 ) {
            printf( "\ n");
        } else {
            printf( ", " );
        }
    }
    return 0;
}