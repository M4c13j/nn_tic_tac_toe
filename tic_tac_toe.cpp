#include <bits/stdc++.h>
using namespace std;

class game  {
    public:

        char mapa[9];

        void draw() {
            cout << "     |     |     " << endl;
            cout << "  " << mapa[0] << "  |  " << mapa[1] << "  |  " << mapa[2] << endl;

            cout << "_____|_____|_____" << endl;
            cout << "     |     |     " << endl;

            cout << "  " << mapa[3] << "  |  " << mapa[4] << "  |  " << mapa[5] << endl;

            cout << "_____|_____|_____" << endl;
            cout << "     |     |     " << endl;

            cout << "  " << mapa[6] << "  |  " << mapa[7] << "  |  " << mapa[8] << endl;

            cout << "     |     |     " << endl << endl;
        }

        bool ifwin( char znak ) {
            if (mapa[ 0 ]==mapa[ 1 ] && mapa[ 1 ]==mapa[ 2 ] && mapa[ 1 ]== znak ) return true;
            else if (mapa[ 3 ]==mapa[ 4 ] && mapa[ 4 ]==mapa[ 5 ] && mapa[ 3 ]== znak ) return true;
            else if (mapa[ 6 ]==mapa[ 7 ] && mapa[ 7 ]==mapa[ 8 ] && mapa[ 6 ]== znak ) return true;
            else if (mapa[ 0 ]==mapa[ 3 ] && mapa[ 3 ]==mapa[ 6 ] && mapa[ 0 ]== znak ) return true;
            else if (mapa[ 1 ]==mapa[ 4 ] && mapa[ 4 ]==mapa[ 7 ] && mapa[ 1 ]== znak ) return true;
            else if (mapa[ 2 ]==mapa[ 5 ] && mapa[ 5 ]==mapa[ 8 ] && mapa[ 2 ]== znak ) return true;
            else if (mapa[ 0 ]==mapa[ 4 ] && mapa[ 4 ]==mapa[ 8 ] && mapa[ 0 ]== znak ) return true;
            else if (mapa[ 2 ]==mapa[ 4 ] && mapa[ 4 ]==mapa[ 6 ] && mapa[ 6 ]== znak ) return true;
            return false;
        }

        bool ifdraw() {
            for( char x : mapa ) {
                if( x != 'X' && x != 'O') return false;
            }

            return true;
        }

        void move( char znak , int pole ) {
            if( mapa[ pole ] != 'X' && mapa[ pole ] != 'O') mapa[ pole ] = znak;
        }

        void zeruj() {
            for(int i=0; i<9;i++) {
                mapa[i]=0;
            }
        }

        vector<int> give(int z) {
            vector<int> re;

            for( char k : mapa ) {
                if (k == 'X') re.push_back(-1);
                else re.push_back(1);
            }

            for( char k : mapa ) {
                if (k == 'O') re.push_back(-1);
                else re.push_back(1);
            }

            if( z == 1 ) reverse( re.begin() , re.end() );

            return re;
        }

};
