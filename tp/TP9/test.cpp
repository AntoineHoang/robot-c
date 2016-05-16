#include <iostream>
using namespace std;

int main()
{
    int lu[25] = {0x62,0x00,0x61,0x00,0x02,0x00,0x44,0x00,0x45,0x00,0xC0,0x02,0x48,0x00,0x09,0x00,0x64,0x00,0x65,0x00,0xC1,0x00,0x63,0x00,0xFF};
    int pointLecture = 0; // variables de lecture
    int compteur = 0, temp = 0; // variable boucle
    bool verifBoucle = false;

    while(lu[pointLecture] != 0xFF)  //fin
    {
        switch(lu[pointLecture])
        {
            case 0x02 : //att
            cout << "correctement.";
            pointLecture++;
            break ;

            case 0x44 :  //dal
            cout << endl;
            pointLecture++;
            break;

            case 0x45 :  //det
            cout << endl;
            pointLecture++;
            break;

            case 0x48 :  //sgo
            cout << "go go ";
            pointLecture ++;
            break;

            case 0x09 : //sar
            cout << "power rangers ";
            pointLecture++;
            break;

            case 0x62 :  // mav
            cout << "Ok ";
            pointLecture++;
            break;

            case 0x60 :  //mar1

            case 0x61 :  //mar2
            cout << "fonctionne ";
            pointLecture++;
            break;

            case 0x63 : //mre
            cout << endl << "fini." << endl;
            pointLecture++;
	    break;

            case 0x64 :  //trd
            cout << "!";
            pointLecture++;
            break;

            case 0x65 :  //trg
            cout << "!";
            pointLecture++;
            break;

            case 0xC0 :  //dbc
            pointLecture++;
            compteur = lu[pointLecture] + 1;
            temp = pointLecture;
            verifBoucle = true;

            case 0xC1 :  //fbc
            if(verifBoucle && compteur)
            {
                compteur-- ;
                pointLecture = temp;
		cout << endl;
            }
            else
	    {
		cout<< endl;
                pointLecture++;
	    }
            break;
	    
	    default :
	    break;
        }

        pointLecture ++;
    }

    return 0;
}
