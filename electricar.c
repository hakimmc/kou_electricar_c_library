#include "electricar.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "stdio.h"
#include "stdbool.h"


float GpsToDecimalDegrees(const float value, char quadrant)
{

	if(value==0.0){
		return 0;
	}
  float sayi[2];
  int temp_sayi[10];
  int i=0;
  int kalan;
  char* token;
  char nmeaPos[50];
  sprintf(nmeaPos,"%f.6",value);
  token = strtok(nmeaPos,".");
  while (token != NULL){
      sayi[i]= atoi(token);
      token = strtok(NULL,".");
      i++;
  }
  i=0;
  int degree = sayi[0];
  int temp = sayi[1];
     while ( temp > 0 ){
         kalan = temp % 10;
         temp /= 10;
         temp_sayi[i]=kalan;
         i++;
     }
  float min = temp_sayi[5]*10.0+temp_sayi[4]*1.0;
  int carpim_deger=1.0;
  float sec=0.0;
  int j=0;
  for(j=0;j<4;j++){
	 sec+=temp_sayi[j]*carpim_deger;
	 carpim_deger*=10.0;
  }
  min+=sec*pow(10,-4);
  float result;
  result=degree+(min/60.0);
    if(quadrant=='W' || quadrant=='S'){
      result= -1*result;
    }
  return result;
}


float CalculateHeadingVehicle(const float new_lat,const float new_long,const float old_lat,const float old_long){

	double angle;
	double starting_degree=0.0;
	double dif_lat = new_lat-old_lat;
	double dif_long = new_long-old_long;
	bool status[4]={false,false,false,false};
	if(dif_lat==0 || dif_long==0){
		return 404;
	}
	else
	{
		angle = atan(abs(new_long-old_long/new_lat-old_lat));
		double direction_angle;

		if(dif_long<0 && dif_lat<0){
			starting_degree=180.0;
			status[0]=true;
			//++
		}
		if(dif_long<0 && dif_lat>0){
			starting_degree=360.0;
			status[1]=true;
			//--
		}
		if(dif_long>0 && dif_lat>0){
			starting_degree=0.0;
			status[2]=true;
			//++
		}
		if(dif_long>0 && dif_lat<0){
			starting_degree=180.0;
			status[3]=true;
			//--
		}
		if(status[0] || status[2]){
			return direction_angle=starting_degree+angle;
		}
		if(status[1] || status[3]){
			return direction_angle=starting_degree+angle;
		}
	}
}


int IS_FLOAT(char* arr){//Çalışıyor
	int i=0;
	while(arr[i]!='.'){
		i++;
		if(arr[i]=='\0'){
			return 0;
		}
	}
	return 1;
	
	/*USAGE 
	IS_FLOAT("55.32")  //%c
	OUTPUT: 1 for "55.32";
	*/
}


char ci2a(char *num){//Çalışıyor
	return (char) atoi(num);
	/*USAGE 
	printf("\r%c\n",ci2a("65"));  //%c
	OUTPUT: A for "65";
	*/
}

char* cf2a(char *num){//Çalışıyor
	
	char firstascii=(char)(int)atof(num);
	char secondascii=  (char)((int)(atof(num)*100)-(int)(atof(num))*100);
	char temp[3];
	int i=0;
	for(i=0;i<3;i++){
		temp[i] = (i==0) ? firstascii : ((i==1) ? '.' : secondascii);	
	}
	return temp;
	
	/*USAGE 
	printf("\r%s\n",ci2a("65.68")); //%s
	OUTPUT: A.D for "65.68";
	*/
}



int IS_CONTAIN(char* num,char parameter){//Çalışıyor
	int state = strlen(num);
	int i=0;
	while(i+1<=state){
		if(num[i]==parameter){
			return 1;
		}
		i++;
	}
	return 0;
	
	/*USAGE 
	IS_CONTAIN("43.32",'.')
	OUTPUT: 1 for "43.32" & '.';
	*/
}

char* CONVERT_ASCII(char* arr[],int count){
	int i=0;
	char tmp[100];
	char int_tmp[count];
	char *float_tmp[count];
	while(i+1<=count){
		if(IS_FLOAT(arr[i])){
			float_tmp[i] = cf2a(arr[i]);
			printf("girdi1:%s\n",float_tmp[i]);
			strcat(tmp,float_tmp[i]);		
		}
		else{
			int_tmp[i]=ci2a(arr[i]);
			printf("girdi0:%c\n",int_tmp[i]);
			strcat(tmp,&int_tmp[i]);
		}
		i++;
	}
	return tmp;
	/*USAGE 
	char* array1[] = {"65.68","66.54","43","65","23","21"};	
	printf("\n\r%s",CONVERT_ASCII(array,(sizeof(array)/sizeof(array[0]))));
	
	OUTPUT: A.DB.6+A for array1;
	*/
}

