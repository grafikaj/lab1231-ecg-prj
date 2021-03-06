#include "ecg_array_const.h"
#include <ecg_file_util.h>

using namespace lab1231_ecg_prj;

char ECGArrayContructor::set_array_to_frame(int sample_num_per_frame,int beat_found, std::vector<double>& data_norm_in, std::vector< std::vector<double> >& frame_all_out, char verbose) {
using namespace std;
	cout << "Array to Frame : BEGIN\n";
	
  int i,j,k,m,h;
	int start,end;
  int lead_num = 8 ;
  
  //convert multi to single lead
	vector<double> one_beat;
  vector<double> data_single_arrange;
  vector<double> one_frame;

  int frame_num = floor(data_norm_in.size()/pow(sample_num_per_frame,2));
  printf("frame_num %d \n", frame_num);    
   
  int start_beat_in;
  
  for(h=0;h<beat_found;h++){
    start_beat_in=h*sample_num_per_frame;
    for(i=0;i<lead_num;i++){
      start = (i)*(data_norm_in.size()/8)+start_beat_in; 
      end = start+sample_num_per_frame;
      for(k=start;k<end;k++){
        one_beat.push_back(data_norm_in[k]);
        }
      for(m=0;m<one_beat.size();m++){
        data_single_arrange.push_back(one_beat[m]);
      }
      one_beat.clear();  
    }
  }
  printf("convert multi to single arrange \n");
  
  for(i=0;i<frame_num;i++){
    start = (i)*pow(sample_num_per_frame,2);
    end = (i+1)*pow(sample_num_per_frame,2);
    for(j=start;j<end;j++){
      one_frame.push_back(data_single_arrange[j]);
    }
    frame_all_out.push_back(one_frame);
    one_frame.clear();
  }
  
  for(i=end;i<(frame_num+1)*pow(sample_num_per_frame,2);i++){
    if(i<data_single_arrange.size()){
      one_frame.push_back(data_single_arrange[i]);
      }else{ //padd with zero
        one_frame.push_back(0.0);
      }  
  }
  frame_all_out.push_back(one_frame);
  one_frame.clear();
  
  
  printf("frame all size %d \n", frame_all_out.size());

	cout << "Array to Frame : END\n";
	
}

char ECGArrayContructor::set_frame_to_matrix(int sample_num_per_frame, std::vector<double>& frame_in, std::vector< std::vector<double> >& matrix_out){
  
  using namespace std;
  cout << "One Frame to Matrix : BEGIN\n";
  
  int i,j,k;
  int start,end;
  vector<double> temp_frame_in;
  
  //for(i=0;i<frame_in.size();i++){
    //temp_frame_in.push_back(frame_in[i]);
  //}
  
  for(i=0;i<sample_num_per_frame;i++){
    start = (i)*sample_num_per_frame;
    end = start + sample_num_per_frame;
    for(j=start;j<end;j++){
      temp_frame_in.push_back(frame_in[j]);
    }
    matrix_out.push_back(temp_frame_in);  
    temp_frame_in.clear();  
  }
  
  
  cout << "One Frame to Matrix : END\n";
}





