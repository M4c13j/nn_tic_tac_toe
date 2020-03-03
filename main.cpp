#include "ai_main.cpp"
using namespace std;

const int size = 100;

network net[ size ];  // tutaj tworzymy moi drodzy sieć neuronową
game gra;

void make_your_choice( int a , char znak) {
    vector<int> ma;
    if( znak == 'O') ma = gra.give(1);
    else ma = gra.give(0);
    net[ a ].get( ma );
    net[ a ].use_the_brain_luke();

    int ruch = net[ a ].answer(gra.mapa);

    gra.move(znak , ruch);
}


int play(int mode , int a , int b) {
    gra.zeruj();
    int owins;
    for(int i = 0 ; i < 5 ; i++) {


        make_your_choice( a , 'X' );



        if( mode == 1) {
            gra.draw();
            net[ a ].draw_output();
        }
        if( gra.ifwin('X') && mode == 0 ) {
            net[ a ].wins += 2;
            owins = net[ b ].wins - 2;
            net[ b ] = net[ a ];
            net[ b ].mutuj( 12 );
            net[ b ].wins = owins;
            return a;
        } else if( gra .ifwin( 'X' ) && mode == 1) {
            cout << "bot won \n";
            return 0;
        } else if( gra.ifdraw() == true ) return -1;




        if( mode == 0) make_your_choice( b , 'O');
        else {
            int p;
            cin >> p;
            gra.move( 'O' , p );
            gra.draw();
        }



        if( gra.ifwin('O') && mode == 0 ) {
            net[ b ].wins += 2;
            owins = net[ a ].wins - 3;
            net[ a ] = net[ b ];
            net[ a ].mutuj( 12 );
            net[ a ].wins = owins;
            return b;
        } else if( gra.ifwin('O') && mode == 1) {
            cout << "maciek won \n";
            net[ a ].mutuj( 3 );
            return 0;
        }

    }

}


void seq() {
    for( int i = 0 ; i < size ; i++ ) {
            for( int j = i+1 ; j < size ; j ++ ) {
                play( 0 , i , j);
            }
        }

        for( int i = size-1 ; i > 0 ; i-- ) {
            for( int j = i-1 ; j > 0 ; j -- ) {
                play( 0 , i , j);
            }
        }
}



int main() {
    srand( time( NULL ) );

    for(int i = 0 ; i < size ; i++) {
        net[ i ].make_aksons_boi();
    }

    thread wontek[ 5 ];
    for( int wo = 1 ; wo < 40 ; wo ++) {
        cout << wo << "\n";

        for(int l = 0 ; l < 5 ; l++ ) {
            wontek[ l ] = thread( seq );
            wontek[ l ].join();
        }

    }


    int best[ size ];
    for( int i = 0; i < size ; i++ ) {
        cout << i << "   " << net[ i ].wins << "\n";
        best[ i ] = net[ i ].wins;
    }
    while(true) {
        cout << "Wybierz numer bota";
        int z;
        cin >> z;

        gra.zeruj();
        gra.draw();

        net[ z ].draw();
        play( 1 , 67 , z);

        gra.draw();
    }



    return 0;
}
