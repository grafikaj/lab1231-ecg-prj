#ifndef _normalization_
#define _normalization_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>



double static phi = M_PI;

void bit_reversal(double* tmp, int min_index, int max_index);
void fft(double * signal_real, double *signal_imag, int length, int p, int q, double *terima_invers_bit);
void inversefft(double* real, double* imag,int n, double *terima_invers_bit);



/*
fungsi untuk normalisasi per beat
nanti di main baru digabung 8 beat yang ada
*/


double *bantuNormalization(double *signal_real, int *letak_r,int *jarak_per_bit, int beat_num){
    char resx = 0;
    int i,j,k,m,l,n,kali,p,q,h;
	i=0;

    printf("\nmasuk bantu normalisasi\n");

    FILE *fp;
    fp = fopen("gabung_bit.csv", "w");

    double *vsignal_per_bit;
    vsignal_per_bit = (double *) malloc((beat_num-1)*128* sizeof(double));


    
    //for(i=0;i<1000;i++){
	     ////fprintf(fp, "%f,", vsignal_per_bit[i]);
    	//printf("%f,", signal_real[i]);
	//}    
    //printf("\n========================\n");
	//for(i=0;i<beat_num-1;i++){

    	//printf("%d,", jarak_per_bit[i]);
	//}
   //printf("\n========================\n");
    //for(i=0;i<beat_num;i++){
	   //printf("%d,", letak_r[i]);
	//}
   //printf("\n========================\n");
    
   //int beat_num = sizeof(letak_r)/sizeof(letak_r[0]);
    //printf("letak r %d\n",sizeof(letak_r));
    //printf("beat_num %d\n",sizeof(letak_r[0]));

    printf("beat_num %d\n",beat_num);

     //vektor 2D signal-signal
    //vector< vector<double> > vsignal_per_bit; //ukuran dah pasti jumlah lead x 128
    //double vsignal_per_bit [(beat_num-1)*128];
    //double *vsignal_per_bit;

    //vsignal_per_bit = (double *) malloc((beat_num-1)*128 * sizeof(double));

    int start;
    int finish;


    int start_res;
    int finish_res;

    start_res = 0;
    finish_res = 0;
	
	 double signal_real_bit[300];
     double signal_imag_bit[300];
     
     double tempvec [500];

       
    double tempvec_out [128];
    
      double terima_invers_bit[128];

    for(i=0; i<beat_num-1; i++) {

       // printf("masuk pengerkaaan");

        start = letak_r[i];
        finish = letak_r[i+1]-1;

        
        printf("i nya : jarak %d %d", i,jarak_per_bit[i]);
        //printf("\n start: %d \n", start);
        //printf("\n finish: %d \n", finish);
        
        //ambil per bit
        //vector< double > tempvec; //ukuran sesuai dengan jarak per bit
       // double tempvec [500];

        //vector< double > tempvec_out; //ukuran pasti 128
       // double tempvec_out [128];
		//double tempvec_out [200];



		//isi tempvec dengan nol
		//for (i=0; i<1000; i++) {
            ////tempvec.push_back(signal_real[j]);
            //tempvec[i]=0.0;
            //printf("%f, ",tempvec[i]);
        //}	

        m=0;
        for (j=start; j<=finish; j++) {
            //tempvec.push_back(signal_real[j]);
            tempvec[m]=signal_real[j];
            m++;
        }

        //cek apakah kurang 128 atau lebih 128
      

        for(h=0;h<128;h++){
            terima_invers_bit[h]=0.0;
        }
        
        
        

        if(jarak_per_bit[i]<128){
            //printf("\n Masuk 128 \n ");
            //double signal_real_bit[128];
            //double signal_imag_bit[128];
            for(k=0;k<128;k++){

                signal_imag_bit[k] = 0.0;

                if(k<jarak_per_bit[i]){
                    signal_real_bit[k] = tempvec[k];
                }
                else {
                    signal_real_bit[k] = 0.0;
                }

            }

            //printf("\n jarak per bit i %d\n ", jarak_per_bit[i]);
            fft(signal_real_bit, signal_imag_bit, 128, 128, jarak_per_bit[i]-1, terima_invers_bit);


        }else if (jarak_per_bit[i]<256 || jarak_per_bit[i]==256){
            //double signal_real_bit[256];
            //double signal_imag_bit[256];
            for(k=0;k<256;k++){

                signal_imag_bit[k] = 0.0;

                if(k<jarak_per_bit[i]){
                    signal_real_bit[k] = tempvec[k];
                }
                else {
                    signal_real_bit[k] = 0.0;
                }

            }
            fft(signal_real_bit, signal_imag_bit, 256, 128, jarak_per_bit[i]-1, terima_invers_bit);
        } 
        

        for(l=0;l<128;l++){
            //tempvec_out.push_back(terima_invers_bit[l]);
            tempvec_out[l]=terima_invers_bit[l];
        }

        //masukan kembali
        //vsignal_per_bit.push_back(tempvec_out);
        start_res = finish_res;
        finish_res = start_res + 128;
        m=0;
        for(j=start_res;j<finish_res;j++){

            vsignal_per_bit[j]=tempvec_out[m];
            m++;
        }

    }

	printf("====================");
	/*
	for (i=0; i<vsignal_per_bit.size(); i++) {
	       // cout << jarak_per_bit[i] <<"\n \n";
	    for (j=0; j<128; j++) {

	         //   cout << vsignal_per_bit[i][j] << " ";
	        fprintf(fp, "%f,", vsignal_per_bit[i][j]);
	    }
	        //cout << "\n\n\n";
	}
	*/

//	printf(" beat_num%d",beat_num-1);

//	printf(" beat_num*128 %d",(beat_num-1)*128);


	for(i=0;i<(beat_num-1)*128;i++){
	     fprintf(fp, "%f,", vsignal_per_bit[i]);

	}
    /*
    printf("\n=====================\n");
    for(i=0;i<6*128;i++){
	     //fprintf(fp, "%f,", vsignal_per_bit[i]);
    	printf("%f,", vsignal_per_bit[i]);
	}*/

 //free memory
	//free(vsignal_per_bit);
 return vsignal_per_bit;
//return resx;

}


char bantuDenormalization(double *signal_real, int *letak_r,int *jarak_per_bit, int beat_num,double *vsignal_per_bit){
    char resx = 0;
    FILE *fp;
    fp = fopen("gabung_denor_bit.csv", "w");

    //baca file
    int i,j,k,l,m;

   // printf("Masuk denormalisasi");


    //dari 512
   // double signal_real [] = {0.033071,0.040339,0.050875,0.074272,0.073885,0.107788,0.113843,0.155903,0.161843,0.193323,0.205646,0.225173,0.233219,0.222178,0.216470,0.185422,0.168711,0.122308,0.095567,0.053058,0.030831,0.003956,-0.016072,-0.029693,-0.048423,-0.051714,-0.069757,-0.066142,-0.079218,-0.073321,-0.077265,-0.070838,-0.069012,-0.074214,-0.077773,-0.092717,-0.095765,-0.118014,-0.124351,-0.141384,-0.139245,-0.143243,-0.144433,-0.144476,-0.148372,-0.143854,-0.154977,-0.155587,-0.171828,-0.173554,-0.186975,-0.191268,-0.200428,-0.206745,-0.206160,-0.208629,-0.193110,-0.189782,-0.173670,-0.172539,-0.160189,-0.158908,-0.156968,-0.160932,-0.164252,-0.154200,-0.151634,-0.136069,-0.136021,-0.121732,-0.122843,-0.113720,-0.114111,-0.113489,-0.108736,-0.109944,-0.096809,-0.096070,-0.083256,-0.088586,-0.078719,-0.078544,-0.068306,-0.066434,-0.067022,-0.053888,-0.041925,-0.010392,0.001275,0.034218,0.056235,0.094073,0.109794,0.117600,0.118159,0.108558,0.105050,0.075383,0.061910,0.024300,0.011031,-0.024313,-0.043059,-0.069230,-0.090015,-0.097657,-0.115496,-0.103867,-0.120346,-0.104606,-0.125592,-0.117209,-0.137916,-0.146336,-0.165381,-0.194130,-0.198651,-0.240378,-0.222500,-0.258151,-0.194501,-0.170884,-0.035377,0.095691,0.282638,0.510654,0.621031,0.952839,1.106640,1.384935,1.204580,0.987278,0.655010,0.408140,0.168755,0.053613,-0.052476,-0.114224,-0.189030,-0.211600,-0.239899,-0.225363,-0.223038,-0.193731,-0.187592,-0.176160,-0.191414,-0.186714,-0.203566,-0.199162,-0.200323,-0.185408,-0.188547,-0.175099,-0.174919,-0.152793,-0.139684,-0.112097,-0.105682,-0.098154,-0.108811,-0.107123,-0.111858,-0.086414,-0.058986,-0.012453,0.028419,0.080104,0.116334,0.163095,0.203160,0.261233,0.308707,0.361818,0.393809,0.414552,0.404038,0.388740,0.347523,0.304293,0.243443,0.188216,0.127070,0.085960,0.047891,0.028607,0.007142,-0.001829,-0.023881,-0.036556,-0.052600,-0.057099,-0.068209,-0.068695,-0.077154,-0.076223,-0.083588,-0.078698,-0.083141,-0.083316,-0.092789,-0.092468,-0.101751,-0.093094,-0.087934,-0.079557,-0.086104,-0.082788,-0.095960,-0.103822,-0.119346,-0.124496,-0.143348,-0.149295,-0.159489,-0.150428,-0.146013,-0.127748,-0.114958,-0.088517,-0.081368,-0.064545,-0.057801,-0.045786,-0.049479,-0.031717,-0.019596,0.007436,0.028415,0.068121,0.089697,0.121036,0.132002,0.140235,0.118978,0.097856,0.042961,0.000534,-0.054526,-0.095558,-0.148525,-0.169926,-0.207063,-0.212821,-0.225596,-0.210985,-0.236446,-0.246857,-0.299756,-0.314003,-0.330437,-0.214733,-0.036578,0.321472,0.641802,1.066774,1.108391,1.316695,1.081812,0.856955,0.530063,0.292922,0.078000,-0.032244,-0.151693,-0.212953,-0.270272,-0.279523,-0.286563,-0.258381,-0.257062,-0.238803,-0.243119,-0.236711,-0.248817,-0.245853,-0.262099,-0.260209,-0.260751,-0.239480,-0.228397,-0.198548,-0.179739,-0.157349,-0.151372,-0.133927,-0.139955,-0.145437,-0.148830,-0.131558,-0.120010,-0.084350,-0.053755,-0.029402,-0.015839,0.010104,0.025534,0.064763,0.112098,0.162949,0.208094,0.260667,0.289149,0.309610,0.311905,0.300093,0.258304,0.210256,0.151989,0.095518,0.044171,0.013478,-0.021216,-0.044768,-0.064443,-0.082130,-0.099900,-0.107111,-0.116222,-0.115400,-0.120456,-0.123265,-0.127703,-0.140080,-0.158697,-0.162820,-0.164124,-0.151767,-0.130000,-0.111099,-0.103033,-0.103425,-0.118556,-0.135081,-0.145927,-0.152307,-0.154057,-0.148645,-0.143513,-0.144904,-0.144118,-0.146279,-0.148777,-0.151198,-0.154469,-0.155417,-0.144418,-0.139186,-0.117480,-0.089491,-0.066083,-0.048565,-0.026352,-0.022113,-0.003683,0.015968,0.048837,0.084055,0.130628,0.151065,0.174823,0.178795,0.177426,0.151947,0.134633,0.083219,0.041346,-0.013946,-0.047853,-0.085641,-0.092031,-0.124656,-0.132220,-0.167635,-0.180364,-0.223269,-0.226281,-0.263265,-0.237123,-0.203887,-0.020844,0.206263,0.622111,0.931004};

    //dari 1000
    //double signal_real []= {0.025936,0.040245,0.054949,0.063475,0.085144,0.091201,0.125795,0.139228,0.169550,0.181607,0.205512,0.220922,0.226403,0.226631,0.206193,0.195462,0.159453,0.134484,0.090851,0.061952,0.031219,0.006931,-0.010146,-0.032156,-0.038803,-0.057200,-0.059227,-0.071916,-0.071162,-0.076645,-0.074595,-0.070332,-0.070799,-0.067380,-0.080657,-0.082509,-0.098411,-0.106183,-0.124424,-0.133726,-0.138681,-0.141310,-0.139377,-0.146309,-0.140888,-0.147433,-0.144758,-0.156319,-0.161925,-0.171518,-0.180283,-0.185352,-0.197310,-0.198400,-0.207771,-0.201818,-0.200250,-0.185758,-0.178904,-0.170344,-0.161794,-0.159122,-0.151685,-0.160553,-0.157614,-0.160554,-0.148124,-0.142860,-0.133636,-0.125853,-0.122345,-0.113613,-0.115425,-0.108539,-0.113501,-0.104842,-0.105065,-0.093877,-0.088118,-0.086115,-0.080252,-0.081843,-0.068547,-0.070318,-0.062220,-0.064968,-0.047787,-0.029137,-0.007076,0.016010,0.036806,0.075025,0.094426,0.117660,0.112188,0.116735,0.105725,0.093802,0.073729,0.044046,0.026808,-0.007156,-0.021634,-0.057225,-0.068895,-0.094587,-0.101291,-0.108287,-0.112953,-0.105173,-0.119750,-0.108435,-0.133165,-0.125436,-0.156678,-0.164640,-0.190584,-0.212509,-0.218411,-0.249832,-0.216791,-0.224641,-0.114898,-0.053568,0.146583,0.294253,0.502789,0.742869,1.104701,1.386876,1.202638,0.989221,0.653067,0.410082,0.166813,0.055552,-0.054413,-0.112291,-0.190960,-0.209675,-0.241819,-0.223449,-0.224946,-0.191830,-0.189485,-0.174275,-0.193291,-0.184847,-0.205423,-0.197316,-0.202158,-0.183584,-0.190357,-0.173301,-0.176704,-0.151023,-0.141440,-0.110357,-0.107406,-0.096446,-0.110502,-0.105449,-0.113514,-0.084778,-0.060604,-0.010856,0.026842,0.081661,0.114799,0.164608,0.201670,0.262701,0.307263,0.363238,0.392413,0.415923,0.402693,0.390060,0.346230,0.305558,0.242204,0.189427,0.125888,0.087113,0.046766,0.029701,0.006078,-0.000796,-0.024883,-0.035586,-0.053538,-0.056194,-0.069081,-0.067856,-0.077958,-0.075452,-0.084323,-0.077998,-0.083805,-0.082688,-0.093380,-0.091914,-0.102267,-0.092615,-0.088374,-0.079157,-0.086465,-0.082466,-0.096241,-0.103582,-0.119544,-0.124340,-0.143461,-0.149225,-0.159515,-0.150447,-0.145949,-0.127858,-0.114802,-0.088721,-0.081116,-0.064847,-0.057449,-0.046189,-0.049023,-0.032226,-0.019032,0.006816,0.029092,0.067385,0.090495,0.120175,0.132930,0.139238,0.120045,0.096713,0.044184,-0.000774,-0.053129,-0.097051,-0.146929,-0.171634,-0.205230,-0.214791,-0.223472,-0.213286,-0.233940,-0.249607,-0.296710,-0.317419,-0.326538,-0.219298,-0.031032,0.314303,0.652190,1.046651,1.106027,1.319027,1.079509,0.859230,0.527813,0.295148,0.075797,-0.030062,-0.153857,-0.210806,-0.272404,-0.277405,-0.288668,-0.256286,-0.259149,-0.236725,-0.245192,-0.234643,-0.250882,-0.243789,-0.264163,-0.258143,-0.262820,-0.237407,-0.230476,-0.196463,-0.181833,-0.155245,-0.153487,-0.131799,-0.142097,-0.143280,-0.151003,-0.129366,-0.122221,-0.082118,-0.056009,-0.027125,-0.018142,0.012432,0.023178,0.067148,0.109682,0.165396,0.205613,0.263183,0.286597,0.312200,0.309276,0.302763,0.255592,0.213012,0.149188,0.098366,0.041273,0.016426,-0.024216,-0.041715,-0.067552,-0.078962,-0.103128,-0.103822,-0.119574,-0.111982,-0.123941,-0.119709,-0.131331,-0.136377,-0.162477,-0.158960,-0.168066,-0.147739,-0.134117,-0.106892,-0.107334,-0.099026,-0.123056,-0.130475,-0.150642,-0.147480,-0.159002,-0.143580,-0.148705,-0.139581,-0.149578,-0.140676,-0.154528,-0.145291,-0.160538,-0.149178,-0.150835,-0.132581,-0.124280,-0.082483,-0.073308,-0.041111,-0.034050,-0.014158,-0.011911,0.024487,0.040008,0.093216,0.121113,0.160963,0.164513,0.189551,0.166186,0.163715,0.122287,0.096201,0.027660,0.000523,-0.063199,-0.069306,-0.109491,-0.105903,-0.152473,-0.145618,-0.204483,-0.196598,-0.256120,-0.229392,-0.276312,-0.157369,-0.078125,0.280892,0.514805,1.122754,1.193902,1.486918,1.283964,1.084152,0.745675,0.502763,0.260298,0.140231,0.011684,-0.047128,-0.121723,-0.137603,-0.172839,-0.160919,-0.174962,-0.157956,-0.169710,-0.147321,-0.155305,-0.143413,-0.157263,-0.151962,-0.178663,-0.172200,-0.188733,-0.180070,-0.181064,-0.160912,-0.164136,-0.138046,-0.136652,-0.115137,-0.101958,-0.063902,-0.040694,0.012278,0.045438,0.090024,0.118292,0.165138,0.190802,0.235424,0.265596,0.304822,0.313382,0.331371,0.327437,0.321972,0.289032,0.264218,0.211096,0.163986,0.106361,0.064862,0.014615,-0.014634,-0.047045,-0.059695,-0.077650,-0.079406,-0.095219,-0.103637,-0.119075,-0.126901,-0.138907,-0.130821,-0.139385,-0.139518,-0.143602,-0.156258,-0.175555,-0.169609,-0.172098,-0.158457,-0.130916,-0.110793,-0.112181,-0.111556,-0.134716,-0.167210,-0.191464,-0.206392,-0.220340,-0.226015,-0.231513,-0.231285,-0.229263,-0.228101,-0.218461,-0.210642,-0.217198,-0.222405,-0.216278,-0.209301,-0.180258,-0.137433,-0.088497,-0.040462,0.004953,0.029052,0.055255,0.070371,0.092375,0.108539,0.124463,0.111729,0.087481,0.024118,-0.040527,-0.113868,-0.166268,-0.226840,-0.249418,-0.281200,-0.291311,-0.316023,-0.315007,-0.352915,-0.367748,-0.417914,-0.405763,-0.370750,-0.176803,0.085880,0.512779,0.830850,1.199392,1.065072,0.709320,0.679476,0.482546,0.469581,0.308734,0.226343,0.157035,0.057716,0.044904,-0.014077,-0.035757,-0.049709,-0.089641,-0.083711,-0.111374,-0.117159,-0.116485,-0.137018,-0.123235,-0.134202,-0.130460,-0.118988,-0.127989,-0.113930,-0.121464,-0.121933,-0.117013,-0.129393,-0.122559,-0.132266,-0.134219,-0.128095,-0.135195,-0.123657,-0.124795,-0.119729,-0.108403,-0.111627,-0.098809,-0.097799,-0.092855,-0.080417,-0.082997,-0.071881,-0.067663,-0.060939,-0.048562,-0.048279,-0.036851,-0.034578,-0.028622,-0.015893,-0.016086,-0.003741,0.001260,0.007168,0.021165,0.024344,0.039605,0.049759,0.061242,0.080952,0.089757,0.109483,0.124012,0.137042,0.155477,0.161672,0.178528,0.191461,0.203856,0.224367,0.232035,0.245512,0.251213,0.250546,0.252148,0.237165,0.224829,0.202994,0.177420,0.162049,0.137017,0.121794,0.104072,0.083386,0.073606,0.055268,0.045116,0.031581,0.014581,0.007896,-0.006444,-0.008061,-0.009637,-0.014082,-0.006917,-0.012303,-0.012801,-0.018041,-0.031337,-0.034575,-0.049000,-0.056246,-0.063456,-0.072200,-0.063976,-0.064448,-0.057233,-0.052197,-0.055029,-0.045185,-0.049080,-0.048197,-0.049946,-0.061732,-0.061020,-0.074905,-0.081057,-0.084353,-0.093294,-0.080567,-0.075510,-0.055752,-0.031168,-0.019579,0.004264,-0.003849,-0.062061,-0.311967,-0.458082,-0.523392,-0.428037,-0.334788,-0.225392,-0.178857,-0.097064,-0.061238,0.031339,0.067138,0.108711,0.078308,0.057410,0.027434,0.045892,0.064997,0.112576,0.140322,0.208650,0.284664,0.422124,0.559327,0.727910,0.832667,0.945980,0.991483,1.042213,1.025537,0.966679,0.846957,0.720563,0.567279,0.444829,0.302331,0.187144,0.062273,-0.044462,-0.149886,-0.222370,-0.276877,-0.283169,-0.293393,-0.272733,-0.274417,-0.269811,-0.303240,-0.348235,-0.406120,-0.422887,-0.437007,-0.403012,-0.397040,-0.381680,-0.413153,-0.443169,-0.471113,-0.460236,-0.459326,-0.452612,-0.474319,-0.465649,-0.442594,-0.417846,-0.406979,-0.390626,-0.380816,-0.331752,-0.317016,-0.280159,-0.279456,-0.266469,-0.284254,-0.279089,-0.289249,-0.265306,-0.267021,-0.248117,-0.269441,-0.266842,-0.278834,-0.263042,-0.254191,-0.221119,-0.193437,-0.141893,-0.150274,-0.164318,-0.226045,-0.228935,-0.228659,-0.165383,-0.131510,-0.084470,-0.088172,-0.074795,-0.084429,-0.055992,-0.081100,-0.062979,-0.086026,-0.032586,-0.008847,0.057445,0.075303,0.126773,0.140158,0.214991,0.256973,0.355487,0.366100,0.382756,0.271707,0.213038,0.080184,0.052635,-0.058326,-0.063676,-0.152536,-0.123193,-0.254896,-0.234919,-0.332582,0.099770,0.549684,1.664546,0.866336};


    //oleh data
    //int jarak_per_bit []= {114,163,165,166};
    //int letak_r [] = {0,114,277,442};

    //int jarak_per_bit []= {114,163,165,166,102,231};
    //int letak_r [] = {0,114,277,442,608,710,941};


    //int beat_num = sizeof(letak_r)/sizeof(letak_r[0]);

    //vector< vector<double> > vsignal_per_bit;
    //double *vsignal_per_bit;
    //vsignal_per_bit = (double *) malloc((letak_r[beat_num-1])* sizeof(double));


    int start = 0 ;
    int finish = 0;

    int start_res =0;
    int finish_res =0;



    for(i=0;i<beat_num-1;i++){
        start = finish;
        finish = finish+128;

        //printf("i nya : %d", i);
        //printf("\n start: %d \n", start);
        //printf("\n finish: %d \n", finish);

         //ambil per bit
        //vector< double > tempvec; //pasti 128
        double tempvec[128];
        //vector< double > tempvec_out; // jarak per bi
        double tempvec_out[jarak_per_bit[i]+2];

        m=0;
        for (j=start; j<=finish; j++) {
            //tempvec.push_back(signal_real[j]);
            tempvec[m]=signal_real[j];
            m++;
        }

        //pasti sesuai ukuran asli sebelum di normalisai
        double terima_invers_bit[jarak_per_bit[i]+2];

        double signal_imag_bit[128];
        double signal_real_bit[128];

        for(k=0;k<128;k++){
            signal_imag_bit[k]=0.0;
            signal_real_bit[k]=tempvec[k];
        }
        fft(signal_real_bit, signal_imag_bit, 128, jarak_per_bit[i], 128, terima_invers_bit);

        for(l=0;l<jarak_per_bit[i]+2;l++){
            //tempvec_out.push_back(terima_invers_bit[l]);
            tempvec_out[l]=terima_invers_bit[l];
        }

        start_res = letak_r[i];
        finish_res = letak_r[i+1];

         //masukan kembali
        //vsignal_per_bit.push_back(tempvec_out);
         m=0;
         for(j=start_res;j<finish_res;j++){
            vsignal_per_bit[j]=tempvec_out[m];
            m++;
         }



    }
    //print
   // printf("====================");
    /*
    for (i=0; i<vsignal_per_bit.size(); i++) {
           // cout << jarak_per_bit[i] <<"\n \n";
        for (j=0; j<jarak_per_bit[i]; j++) {

             //   cout << vsignal_per_bit[i][j] << " ";
            fprintf(fp, "%f,", vsignal_per_bit[i][j]);
        }
            //cout << "\n\n\n";
    }*/

    for(i=0;i<letak_r[beat_num-1];i++){
        fprintf(fp, "%f,", vsignal_per_bit[i]);
    }

   // return vsignal_per_bit;
    return  resx;
}



void inversefft(double* real, double* imag,int n, double *terima_invers_bit) {
    int i, j, k;
    FILE *fp;
    fp = fopen("inverseFFT.csv", "w");

   // printf("nnnnnnn %d", n);

    //double hasil[n];

    double rexbar[1+(n/2)],imxbar[1+(n/2)];
    for (j=0; j<= n/2;j++) {
        rexbar[j]=real[j]/(n/2);
        if (j==0||j== n/2) {
            rexbar[j]/= 2;
        }

        imxbar[j]=imag[j]/(n/2)*-1;
    }

    for (i=0;i<n;i++) {
        double re = 0, im = 0;

        for (k=0; k<= n/2; k++) {
            re += rexbar[k]*cos(2*i*phi*k/n);
            im += imxbar[k]*sin(2*i*phi*k/n);
        }
       // hasil[i] =re+im;
        terima_invers_bit[i] = re+im;
    }


    fprintf(fp,"hasil inverse");
    fprintf(fp,"\n");
    for(i = 0; i< 128; i++) {
            fprintf(fp, "%f, ", terima_invers_bit[i]);
    }
   // printf("masuk inverse");


}



void fft(double *signal_real, double *signal_imag, int length, int p, int q, double *terima_invers_bit) 
{
   int divisor = 1;
   int signal_count = length/divisor;

   // printf("length mbul %d \n", length);
    printf("sin count %d\n", signal_count);

    int k;
    int i;
    int j;
    int current_index;
    current_index = 0;
    //double ddddM;
    double UR;
    double UI;
    double SR;
    double SI;
    double TR;
    double TI;
    int LE;
    int LE2;
    int stage;
    int pad_size;

    FILE *fp;
    fp = fopen("outputFFT.csv","w");


    //double *tempInverse;

   // printf("masuk FFT \n");


    /**
      * Proses dekomposisi untuk mendapatkan bit reversal keseluruhan
      */
    while (divisor <= length) {
        for(i = 0; i<divisor; i++) {
            int min_ind = i*signal_count;
            int max_ind = min_ind + signal_count-1;
            bit_reversal(signal_real, min_ind, max_ind);
            bit_reversal(signal_imag, min_ind, max_ind);
        }
        divisor *= 2;
        signal_count = length/divisor;
    }

    /**
      * Lakukan implementasi proses Butterfly di sini
      */
    //printf("\n masuk butterfly %f \n",signal_count);
    if((log(length)/log(2)) == 0){
        stage = log(length)/log(2);
    } else {
        stage = ceil(log(length)/log(2));
    }
      pad_size = pow(2,stage);

   double pad_real [length];
    for(i=0; i<length; i++){
        if (i < length) pad_real[i] = signal_real[i];
            else pad_real[i] = 0;
    }

    double pad_imag [length];
      for(i=0; i<length; i++){
        if (i < length) pad_imag[i] = signal_imag[i];
            else pad_imag[i] = 0;
    }

    int JM1,IP;
    for(i=0;i<=stage;i++){
        LE = pow(2,i);
        LE2 = LE/2;
        UR=1.0;
        UI=0.0;
        SR = cos(phi/LE2);
        SI = -1*sin(phi/LE2);


        for(j=1;j<=LE2;j++){
             JM1 = j-1;
            for(k=JM1;k<=(pad_size-1);k=k+LE){
                IP=k+LE2;
                TR = pad_real[IP]*UR - pad_imag[IP]*UI;
                TI = pad_real[IP]*UI + pad_imag[IP]*UR;
                pad_real[IP]= pad_real[k]-TR;
                pad_imag[IP]= pad_imag[k]-TI;
                pad_real[k]= pad_real[k]+TR;
                pad_imag[k]= pad_imag[k]+TI;

            }
            TR=UR;
            UR = (TR*SR)-(UI*SI);
            UI = (TR*SI)+(UI*SR);

        }

    }

    fprintf(fp,"tes real");
    fprintf(fp,"\n");
    for(i = 0; i< pad_size; i++) {
        fprintf(fp, "%f, ", pad_real[i]);
    }
    fprintf(fp,"\n");
    fprintf(fp,"tes imag");
    fprintf(fp,"\n");
    for(i = 0; i< pad_size; i++) {
            fprintf(fp, "%f, ", pad_imag[i]);
    }


//==========================================================
//Proses normalisasi
//printf("\n =================================== \n");
//printf(" Masuk Normalisasi p = %d, q = %d\n ", p, q );
int d;

int hilang1;
int hilang2;
int delta;

int len1 = pad_size;
//double len2 = round(len1*p/q);
double len2 = len1*p/q;

if(len2>=0){len2+0.5;}
else{len2-0.5;}


int lby2 = 1 + (len1/2);
/*
printf("len1 %d\n", len1);
printf("len2 %f\n", len2);
printf("lby2 %d\n", lby2);
*/

if (len2 < len1){
    //printf("Dikecilkan");
    //hilangkan high frekuensi sampling
    d = len1 - len2;
    //hilangkan komponen dari
    hilang1 = floor(lby2-(d-1)/2);
    hilang2 = floor(lby2+(d-1)/2);
    delta = hilang2-hilang1;
    int del = pad_size-(delta)-1;
    double res_nor[del];

    /*
    printf("hilang1 %d\n", hilang1);
    printf("hilang2 %d\n", hilang2);
    printf("pad_size-(delta) %d\n", del);
    */
     //printf(" \nhasil hilangkan\n");
    j=0;
    for(i=0;i<pad_size;i++){
        if(i >= (hilang1-1) && i <= (hilang2-1) ){
            // do nothing
        } else {
           // printf(" ada : %d \n", i);
                res_nor[j]=pad_real[i];
                j++;

        }

    }
   // res[0]=1;

    /*
    for(j=0;j<(del);j++){
        printf("%f ", res_nor[j]);
    }
    */
    double res_nor_imag[del];

    for(i=0;i<del;i++){
        res_nor_imag[i] = pad_imag[i];

    }
     inversefft(res_nor,res_nor_imag,del,terima_invers_bit);

} else if(len2 > len1) {
    //printf("\nDibesarkan\n");

    d = len2-len1;
    lby2 = floor(lby2);
    int ambil = 0;
    double res_nor[pad_size+d];

    //printf("d %d\n", d);
    //printf("lby2 %d\n", lby2);

    j=0;
    for (i=0; i < pad_size+d ; i++){

        if(i>=lby2 && ambil < d){
            res_nor[i] = 0.0;
            ambil++;
        }else {
            res_nor[i] = pad_real[j];
            j++;
        }
    }

    double res_nor_imag[pad_size+d];
    j=0;
    ambil=0;
    for (i=0; i < pad_size+d ; i++){

        if(i>=lby2 && ambil < d){
            res_nor_imag[i] = 0.0;
            ambil++;
        }else {
            res_nor_imag[i] = pad_imag[j];
            j++;
        }
    }

    inversefft(res_nor,res_nor_imag,pad_size+d,terima_invers_bit);
    //printf("pad size + d %d", pad_size+d);

} else {
 //  printf("\nTetap\n");
   inversefft(pad_real,pad_imag,pad_size,terima_invers_bit);

}
//===========================================================   // inversefft(pad_real,pad_imag,pad_size);
  //  printf("\n =================================== \n");
    //return tempInverse;
   // printf("Process is done");
}

/**
* Fungsi ini berfungsi untuk melakukan bit reversal satu level
*/
void bit_reversal(double* tmp, int min_index, int max_index) {
    double div1[max_index-min_index+1];
    double div2[max_index-min_index+1];
    int index1=0, index2=0, index=min_index;
    int i;
    for(i = min_index; i <= max_index; i++) {
        if((i%2)==0) div1[index1++] = tmp[i];
        else div2[index2++] = tmp[i];
    }
    for(i = 0; i<index1; i++) {
        tmp[index++] = div1[i];
    }
    for(i = 0; i<index2; i++) {
        tmp[index++] = div2[i];
    }
}







#ifdef __cplusplus
}
#endif

#endif
