#include <iostream>
#include <random>
#include <fstream>

using namespace std;

int main(){

    random_device generator ;
    uniform_int_distribution <int> distributor_d6(1, 6) ;
    uniform_int_distribution <int> distributor_liv(1, 10) ;
    uniform_int_distribution <int> distributor_soglia(1, 3) ;
    ofstream file ;

    int liv_gen = 0, soglia_c = 6, soglia_m = 6, soglia_s = 6, punti = 4, dadi = 0 ;
    int vigore = 1, agilita = 1, intelletto = 1, consapevolezza = 1, personalita = 1, fortuna = 1 ;
    int cont_succ = 0, check_rius = 0, check_fall = 0, avanzi = 0, car_sc = 0, num_tiri = 0, sog_sc = 0 ;
    double  media_succ = 0, perc_rius = 0, media_av = 0 ;
    bool limite = false ;

    file.open("analisi.txt") ;

    for(int l = 0; l < 1000; l++){

        while(punti > 0){

            car_sc = distributor_d6(generator) ;

            switch(car_sc){

                case 1:

                    if(vigore < 3){

                        vigore++ ;
                        punti-- ;

                    }    
                
                break ;

                case 2:

                    if(agilita < 3){

                        agilita++ ;
                        punti-- ;

                    }    

                break ;

                case 3:

                    if(intelletto < 3){

                        intelletto++ ;
                        punti-- ;

                    }    

                break ;

                case 4:

                    if(consapevolezza < 3){

                        consapevolezza++ ;
                        punti-- ;

                    }    

                break ;

                case 5:

                    if(personalita < 3){

                        personalita++ ;
                        punti-- ;

                    }    

                break ;

                case 6:

                    if(fortuna < 3){

                        fortuna++ ;
                        punti-- ;

                    }    

                break;    

            }

        }

        file <<"Le caratteristiche generate sono:" << endl << endl ;
        file <<"Vigore: " << vigore << endl ;
        file <<"Agilità: " << agilita << endl ;
        file <<"Intelletto: " << intelletto << endl ;
        file <<"Consapevolezza: " << consapevolezza << endl ;
        file <<"Personalità: " << personalita << endl ;
        file <<"Fortuna: " << fortuna << endl << endl ;

        liv_gen = distributor_liv(generator) ;

        switch(liv_gen){
            case 1:

                dadi = 1 ;

            break ;

            case 2:

                dadi = 1 ;

            break ;

            case 3:

                dadi = 2 ;

            break ;

            case 4:

                dadi = 2 ;

            break ;

            case 5:

                dadi = 3 ;

            break ;

            case 6:

                dadi = 3 ;

            break ;

            case 7:

                dadi = 4 ;

            break ;

            case 8:

                dadi = 4 ;

            break ;

            case 9:

                dadi = 5 ;

            break ;

            case 10:

                dadi = 5;

            break ;

        }

        file <<"Il livello del personaggio è: " << liv_gen << endl << endl ;

        while(limite == false){

            sog_sc = distributor_soglia(generator) ;

            switch(sog_sc){

                case 1:

                    if((soglia_c + soglia_m + soglia_s) < 21){

                        if(soglia_c < 8){

                            soglia_c++ ;

                        }

                    }else{

                        limite = true ;

                    }
                
                break ;

                case 2:

                    if((soglia_c + soglia_m + soglia_s) < 21){

                        if(soglia_m < 8){

                            soglia_m++ ;

                        }

                    }else{

                        limite = true ;

                    }

                break ;

                case 3:

                    if((soglia_c + soglia_m + soglia_s) < 21){

                        if(soglia_s < 8){

                            soglia_s++ ;

                        }

                    }else{

                        limite = true ;

                    }

                break ;

            }

        }

        file <<"Le soglie generate sono:" << endl << endl ;
        file <<"CORPO:" << soglia_c << endl ;
        file <<"MENTE: " << soglia_m << endl ;
        file <<"SPIRITO: " << soglia_s << endl << endl ;

        int tiri[dadi + vigore] ;

        for(int i = 0; i < (dadi + vigore); i++){

            tiri[i] = distributor_d6(generator) ;

            if(tiri[i] == 6){

                cont_succ++ ;
                tiri[i] = 0 ;

            }

        }

        for(int i = 0; i < (dadi + vigore); i++){

            int num_att = tiri[i], ind_att = i, num_min = tiri[i], ind_min = i ;

            for(int j = i + 1; j < (dadi + vigore); j++){

                int num = tiri[j], ind = j ;

                if(num < num_min){

                    num_min = num ;
                    ind_min = ind ;

                }

            }

            int temp = num_att ;

            tiri[ind_att] = num_min ;
            tiri[ind_min] = temp ;

        }

        file <<"Il tiro su Vigore: " ;

        for(int i = 0; i < (dadi + vigore); i++){

            file << tiri[i] <<" " ;

        }

        file << endl << endl ;

        for(int i = (dadi + vigore) - 1; i > 0; i -= 2){

            int temp = 0 ;

            if(tiri[i] != 0){

                if(tiri[i - 1] == 0){
                
                    if(temp >= soglia_c){

                        cont_succ++ ;

                    }

                    break ;

                }else{

                    temp += (tiri[i] + tiri[i - 1]) ;
                
                    if(temp >= soglia_c){

                        cont_succ++ ;
                        tiri[i] = 0 ;
                        tiri[i - 1] = 0 ;

                    }else{

                        for(int j = i - 2; j > -1; j--){

                            temp += tiri[j] ;

                            if(temp >= soglia_c){

                                tiri[i] = 0 ;
                                tiri[i - 1] = 0 ;
                                cont_succ++ ;
                                tiri[j] = 0 ;
                                temp = 0 ;
                                break ;

                            }else{

                                if(j == 0){

                                    break ;

                                }

                            }

                        }

                    }

                }

            }else{

                break ;

            }

        }

        for(int i = 0; i < (dadi + vigore); i ++){

            avanzi += tiri[i] ;

        }

        file <<"I successi sono: " << cont_succ << endl ;
        file <<"Gli avanzi sono: " << avanzi << endl << endl ;

        media_succ += cont_succ ;
        media_av += avanzi ;
        num_tiri++ ;

        if(cont_succ > 0){

            cont_succ = 0 ;
            check_rius++ ;

        }else{

            check_fall++ ;

        }
    
        avanzi = 0 ;

        int tiri2[dadi + agilita] ;

        for(int i = 0; i < (dadi + agilita); i++){

            tiri2[i] = distributor_d6(generator) ;

            if(tiri2[i] == 6){

                cont_succ++ ;
                tiri2[i] = 0 ;

            }

        }

        for(int i = 0; i < (dadi + agilita); i++){

            int num_att = tiri2[i], ind_att = i, num_min = tiri2[i], ind_min = i ;

            for(int j = i + 1; j < (dadi + agilita); j++){

                int num = tiri2[j], ind = j ;

                if(num < num_min){

                    num_min = num ;
                    ind_min = ind ;

                }

            }

            int temp = num_att ;

            tiri2[ind_att] = num_min ;
            tiri2[ind_min] = temp ;

        }

        file <<"Il tiro su Agilità: " ;

        for(int i = 0; i < (dadi + agilita); i++){

            file << tiri2[i] <<" " ;

        }

        file << endl << endl ;

        for(int i = (dadi + agilita) - 1; i > 0; i -= 2){

            int temp = 0 ;

            if(tiri2[i] != 0){

                if(tiri2[i - 1] == 0){
                
                    if(temp >= soglia_c){

                        cont_succ++ ;

                    }

                
                    break ;

                }else{

                    temp += (tiri2[i] + tiri2[i - 1]) ;
                
                    if(temp >= soglia_c){

                        cont_succ++ ;
                        tiri2[i] = 0 ;
                        tiri2[i - 1] = 0 ;

                    }else{

                        for(int j = i - 2; j > -1; j--){

                            temp += tiri2[j] ;

                            if(temp >= soglia_c){

                                tiri2[i] = 0 ;
                                tiri2[i - 1] = 0 ;
                                cont_succ++ ;
                                tiri2[j] = 0 ;
                                temp = 0 ;
                                break ;

                            }else{

                                if(j == 0){

                                    break ;

                                }

                            }

                        }

                    }

                }

            }else{

                break ;

            }

        }

        for(int i = 0; i < (dadi + agilita); i ++){

            avanzi += tiri2[i] ;

        }

        file <<"I successi sono: " << cont_succ << endl ;
        file <<"Gli avanzi sono: " << avanzi << endl << endl ;

        media_succ += cont_succ ;
        media_av += avanzi ;
        num_tiri++ ;

        if(cont_succ > 0){

            cont_succ = 0 ;
            check_rius++ ;

        }else{

            check_fall++ ;

        }
    
        avanzi = 0 ;

        int tiri3 [dadi + intelletto] ;

        for(int i = 0; i < (dadi + intelletto); i++){

            tiri3[i] = distributor_d6(generator) ;

            if(tiri3[i] == 6){

                cont_succ++ ;
                tiri3[i] = 0 ;

            }

        }

        for(int i = 0; i < (dadi + intelletto); i++){

            int num_att = tiri3[i], ind_att = i, num_min = tiri3[i], ind_min = i ;

            for(int j = i + 1; j < (dadi + intelletto); j++){

                int num = tiri3[j], ind = j ;

                if(num < num_min){

                    num_min = num ;
                    ind_min = ind ;

                }

            }

            int temp = num_att ;

            tiri3[ind_att] = num_min ;
            tiri3[ind_min] = temp ;

        }

        file <<"Il tiro su Intelletto: " ;

        for(int i = 0; i < (dadi + intelletto); i++){

            file << tiri3[i] <<" " ;

        }

        file << endl << endl ;

        for(int i = (dadi + intelletto) - 1; i > 0; i -= 2){

            int temp = 0 ;

            if(tiri3[i] != 0){

                if(tiri3[i - 1] == 0){
                
                    if(temp >= soglia_m){

                        cont_succ++ ;

                    }

                    break ;

                }else{

                    temp += (tiri3[i] + tiri3[i - 1]) ;
                
                    if(temp >= soglia_m){

                        cont_succ++ ;
                        tiri3[i] = 0 ;
                        tiri3[i - 1] = 0 ;

                    }else{

                        for(int j = i - 2; j > -1; j--){

                            temp += tiri3[j] ;

                            if(temp >= soglia_m){

                                tiri3[i] = 0 ;
                                tiri3[i - 1] = 0 ;
                                cont_succ++ ;
                                tiri3[j] = 0 ;
                                temp = 0 ;
                                break ;

                            }else{

                                if(j == 0){

                                    break ;

                                }

                            }

                        }

                    }

                }

            }else{

                break ;

            }

        }

        for(int i = 0; i < (dadi + intelletto); i ++){

            avanzi += tiri3[i] ;

        }

        file <<"I successi sono: " << cont_succ << endl ;
        file <<"Gli avanzi sono: " << avanzi << endl <<endl ;

        media_succ += cont_succ ;
        media_av += avanzi ;
        num_tiri++ ;

        if(cont_succ > 0){

            cont_succ = 0 ;
            check_rius++ ;

        }else{

            check_fall++ ;

        }
    
        avanzi = 0 ;

        int tiri4[dadi + consapevolezza] ;

        for(int i = 0; i < (dadi + consapevolezza); i++){

            tiri4[i] = distributor_d6(generator) ;

            if(tiri4[i] == 6){

                cont_succ++ ;
                tiri4[i] = 0 ;

            }

        }

        for(int i = 0; i < (dadi + consapevolezza); i++){

            int num_att = tiri4[i], ind_att = i, num_min = tiri4[i], ind_min = i ;

            for(int j = i + 1; j < (dadi + consapevolezza); j++){

                int num = tiri4[j], ind = j ;

                if(num < num_min){

                    num_min = num ;
                    ind_min = ind ;

                }

            }

            int temp = num_att ;

            tiri4[ind_att] = num_min ;
            tiri4[ind_min] = temp ;

        }

        file <<"Il tiro su Consapevolezza: " ;

        for(int i = 0; i < (dadi + consapevolezza); i++){

            file << tiri4[i] <<" " ;

        }

        file << endl << endl ;

        for(int i = (dadi + consapevolezza) - 1; i > 0; i -= 2){

            int temp = 0 ;

            if(tiri4[i] != 0){

                if(tiri4[i - 1] == 0){
                
                    if(temp >= soglia_m){

                        cont_succ++ ;

                    }

                    break ;

                }else{

                    temp += (tiri4[i] + tiri4[i - 1]) ;
                
                    if(temp >= soglia_m){

                        cont_succ++ ;
                        tiri4[i] = 0 ;
                        tiri4[i - 1] = 0 ;

                    }else{

                        for(int j = i - 2; j > -1; j--){

                            temp += tiri4[j] ;

                            if(temp >= soglia_m){

                                tiri4[i] = 0 ;
                                tiri4[i - 1] = 0 ;
                                cont_succ++ ;
                                tiri4[j] = 0 ;
                                temp = 0 ;
                                break ;

                            }else{

                                if(j == 0){

                                    break ;

                                }

                            }

                        }

                    }

                }

            }else{

                break ;

            }

        }

        for(int i = 0; i < (dadi + consapevolezza); i ++){

            avanzi += tiri4[i] ;

        }

        file <<"I successi sono: " << cont_succ << endl ;
        file <<"Gli avanzi sono: " << avanzi << endl << endl ;

        media_succ += cont_succ ;
        media_av += avanzi ;
        num_tiri++ ;

        if(cont_succ > 0){

            cont_succ = 0 ;
            check_rius++ ;

        }else{

            check_fall++ ;

        }
    
        avanzi = 0 ;

        int tiri5[dadi + personalita] ;

        for(int i = 0; i < (dadi + personalita); i++){

            tiri5[i] = distributor_d6(generator) ;

            if(tiri5[i] == 6){

                cont_succ++ ;
                tiri5[i] = 0 ;

            }

        }

        for(int i = 0; i < (dadi + personalita); i++){

            int num_att = tiri5[i], ind_att = i, num_min = tiri5[i], ind_min = i ;

            for(int j = i + 1; j < (dadi + personalita); j++){

                int num = tiri5[j], ind = j ;

                if(num < num_min){

                    num_min = num ;
                    ind_min = ind ;

                }

            }

            int temp = num_att ;

            tiri5[ind_att] = num_min ;
            tiri5[ind_min] = temp ;

        }

        file <<"Il tiro su Personalità: " ;

        for(int i = 0; i < (dadi + personalita); i++){

            file << tiri5[i] <<" " ;

        }

        file << endl << endl ;

        for(int i = (dadi + personalita) - 1; i > 0; i -= 2){

            int temp = 0 ;

            if(tiri5[i] != 0){

                if(tiri5[i - 1] == 0){
                
                    if(temp >= soglia_s){

                        cont_succ++ ;

                    }

                    break ;

                }else{

                    temp += (tiri5[i] + tiri5[i - 1]) ;
                
                    if(temp >= soglia_s){

                        cont_succ++ ;
                        tiri5[i] = 0 ;
                        tiri5[i - 1] = 0 ;

                    }else{

                        for(int j = i - 2; j > -1; j--){

                            temp += tiri5[j] ;

                            if(temp >= soglia_s){

                                tiri5[i] = 0 ;
                                tiri5[i - 1] = 0 ;
                                cont_succ++ ;
                                tiri5[j] = 0 ;
                                temp = 0 ;
                                break ;

                            }else{

                                if(j == 0){

                                    break ;

                                }

                            }

                        }

                    }

                }

            }else{

                break ;

            }

        }

        for(int i = 0; i < (dadi + personalita); i ++){

            avanzi += tiri5[i] ;

        }

        file <<"I successi sono: " << cont_succ << endl ;
        file <<"Gli avanzi sono: " << avanzi << endl << endl ;

        media_succ += cont_succ ;
        media_av += avanzi ;
        num_tiri++ ;

        if(cont_succ > 0){

            cont_succ = 0 ;
            check_rius++ ;

        }else{

            check_fall++ ;

        }
    
        avanzi = 0 ;

        int tiri6[dadi + fortuna] ;

        for(int i = 0; i < (dadi + fortuna); i++){

            tiri6[i] = distributor_d6(generator) ;

            if(tiri6[i] == 6){

                cont_succ++ ;
                tiri6[i] = 0 ;

            }

        }

        for(int i = 0; i < (dadi + fortuna); i++){

            int num_att = tiri6[i], ind_att = i, num_min = tiri6[i], ind_min = i ;

            for(int j = i + 1; j < (dadi + fortuna); j++){

                int num = tiri6[j], ind = j ;

                if(num < num_min){

                    num_min = num ;
                    ind_min = ind ;

                }

            }

            int temp = num_att ;

            tiri6[ind_att] = num_min ;
            tiri6[ind_min] = temp ;

        }

        file <<"Il tiro su Fortuna: " ;

        for(int i = 0; i < (dadi + fortuna); i++){

            file << tiri6[i] <<" " ;

        }

        file << endl << endl ;

        for(int i = (dadi + fortuna) - 1; i > 0; i -= 2){

            int temp = 0 ;

            if(tiri6[i] != 0){

                if(tiri6[i - 1] == 0){
                
                    if(temp >= soglia_s){

                        cont_succ++ ;

                    }

                    break ;

                }else{

                    temp += (tiri6[i] + tiri6[i - 1]) ;
                
                    if(temp >= soglia_s){

                        cont_succ++ ;
                        tiri6[i] = 0 ;
                        tiri6[i - 1] = 0 ;

                    }else{

                        for(int j = i - 2; j > -1; j--){

                            temp += tiri6[j] ;

                            if(temp >= soglia_s){

                                tiri6[i] = 0 ;
                                tiri6[i - 1] = 0 ;
                                cont_succ++ ;
                                tiri6[j] = 0 ;
                                temp = 0 ;
                                break ;

                            }else{

                                if(j == 0){

                                    break ;

                                }

                            }

                        }

                    }

                }

            }else{

                break ;

            }

        }

        for(int i = 0; i < (dadi + fortuna); i ++){

            avanzi += tiri6[i] ;

        }

        file <<"I successi sono: " << cont_succ << endl ;
        file <<"Gli avanzi sono: " << avanzi << endl << endl ;

        media_succ += cont_succ ;
        media_av += avanzi ;
        num_tiri++ ;

        if(cont_succ > 0){

            cont_succ = 0 ;
            check_rius++ ;

        }else{

            check_fall++ ;

        }
    
        avanzi = 0 ;
        punti = 4 ;
        vigore = 1 ;
        agilita = 1 ;
        intelletto = 1 ;
        consapevolezza = 1 ;
        personalita = 1 ;
        fortuna = 1 ;
        limite = false ;
        soglia_c = 6 ;
        soglia_m = 6 ;
        soglia_s = 6 ;

    }

    media_succ /= num_tiri ;
    media_av /= num_tiri ;
    perc_rius = ((double)check_rius / (double)num_tiri) * 100 ;

    file <<"I tiri riusciti sono: " << check_rius << endl ;
    file <<"I tiri falliti sono: " << check_fall << endl ;
    file <<"La media dei successi per tiro è: " << media_succ << endl ;
    file <<"La media degl'avanzi per tiro è: " << media_av << endl ;
    file <<"La percentuale di tiri superati è: " << perc_rius <<" %" << endl << endl << endl << endl ;

    file.close() ;
    
    return 0 ;

}