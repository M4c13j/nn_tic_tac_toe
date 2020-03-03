/*
    Autor: Maciej Cuper

    Data ostatniej aktualizacji: 23 01 2020

    Przy projekcie pomogli: hw, mr, js.

    Creative commons BY-NC-SA 4.0 (uznanie autorstwa, użycie niekomercyjne, te same warunki)
*/
#include "tic_tac_toe.cpp"
#include <cmath>

using namespace std;

const int inl = 18;
const int hide1 = 15;
const int hide2 = 12;
const int out = 9;

float sigmoid(float x) {
    return 1 / (1 + exp(-x));
}

class neuron {
    public:
        float state = 0;
};

class network {
    private:
        neuron in_layer[ inl ];
        neuron hide_layer_1[ hide1 ];
        neuron hide_layer_2[ hide2 ];
        neuron out_layer[ out ];

        float input;

        float in_hi1[ inl ][ hide1 ];
        float h1_h2[ hide1 ][ hide2 ];
        float hi2_out[ hide2 ][ out ];

    public:
        int wins;

        // przypisuje każdemu aksonowi losową wartość

        void make_aksons_boi() {

            for(int i = 0 ; i < inl ; i++) {
                for(int j = 0; j < hide1 ; j++) {
                    in_hi1[ i ][ j ] = ((rand() % 1000)-500) * 0.001;
                }
            }

            for(int i = 0 ; i < hide1 ; i++) {
                for(int j = 0; j < hide2 ; j++) {
                    h1_h2[ i ][ j ] = ((rand() % 1000)-500) * 0.001;
                }
            }

            for(int i = 0 ; i < hide2 ; i++) {
                for(int j = 0; j < out ; j++) {
                    hi2_out[ i ][ j ] = ((rand() % 1000)-500) * 0.001;
                }
            }
        }


        // kopiuje wartości z wejścia do pierwszej warstwy neuronów
        void get(vector<int> activation) {
            for(int i = 0 ; i < inl ; i++) in_layer[i].state = activation[i];
        }



        //ustawia wartości wyjścia ( cała magia sieci )
        void use_the_brain_luke() {
            for( int i = 0 ; i < inl ; i++) {
                float x = in_layer[i].state;

                for( int j = 0 ; j < hide1 ; j++) {
                    hide_layer_1[ j ].state += x * in_hi1[ i ][ j ];
                }
                hide_layer_1[i].state = sigmoid( hide_layer_1[i].state );

            }

            for( int i = 0 ; i < hide1 ; i++) {
                float x = hide_layer_1[i].state;


                for( int j = 0 ; j < hide2 ; j++) {
                    hide_layer_2[ j ].state += x * h1_h2[ i ][ j ];
                }

                hide_layer_2[i].state = sigmoid( hide_layer_2[i].state );
            }

            for( int i = 0 ; i < hide2 ; i++) {
                float x = hide_layer_2[i].state;


                for( int j = 0 ; j < out ; j++) {
                    out_layer[ j ].state += x * hi2_out[ i ][ j ];
                }

                out_layer[i].state = sigmoid( out_layer[i].state );
            }

        }


        //wypisuje całą sieć (nieczytelne)
        void draw() {

            for(int i = 0 ; i < inl ; i++) {
                cout << i << "\n";

                for( int j = 0 ; j < hide1 ; j++) {
                    cout << " " << in_hi1[ i ] [ j ] << " ";
                }
                cout << "\n";
            }

            for(int i = 0 ; i < hide1 ; i++) {
                cout << i << "\n";

                for( int j = 0 ; j < hide2 ; j++) {
                    cout << " " << h1_h2[ i ] [ j ] << " ";
                }
                cout << "\n";
            }

            for( int i = 0 ; i < inl ; i++) cout << in_layer[ i ].state << " ";
            cout << "\n";
            for( int i = 0 ; i < hide1 ; i++) cout << hide_layer_1[ i ].state << " ";
            cout << "\n";
            for( int i = 0 ; i < hide2 ; i++) cout << hide_layer_2[ i ].state << " ";
            cout << "\n";
            for( int i = 0 ; i < out ; i++) cout << out_layer[ i ].state << " ";
            cout << "\n";
        }


        void draw_output() {
            for( int i = 0 ; i < out ; i++ ) {
                cout << out_layer[ i ].state << " ";
            }
            cout << "\n";
        }


        //zapisuje sieć do pliku
        void save();


        void mutuj( int chance) {
            srand(time(NULL));

            for( int i = 0 ; i < inl ; i++) {

                for( int j = 0 ; j < hide1 ; j++) {
                    if ( (rand () % 100) <= chance ) {
                        in_hi1[ i ][ j ] *= ((rand() % 100) ) * 0.01;
                    }
                }

            }

            for( int i = 0 ; i < hide1 ; i++) {

                for( int j = 0 ; j < hide2 ; j++) {
                    if ( (rand () % 100) <= chance ) {
                        h1_h2[ i ][ j ] *= ((rand() % 100) ) * 0.01;
                    }
                }

            }

            for( int i = 0 ; i < hide2 ; i++) {

                for( int j = 0 ; j < out ; j++) {
                    if ( (rand () % 100) <= chance ) {
                        hi2_out[ i ][ j ] *= ((rand() % 150) ) * 0.01;
                    }
                }

            }

        }



        //zwraca wartość wyjścia (najwyższa w ostatniej warstwie
        int answer(char mapa[]) {
            float mx = -1000000000;
            int index = 5;

            for(int i = 0 ; i < out ; i++) {
                if ( mx <= out_layer[i].state && mapa[ i ] != 'X' && mapa[ i ] != 'O' ) {
                    mx = out_layer[i].state;
                    index = i;
                }
            }

            return index;
        }
};
