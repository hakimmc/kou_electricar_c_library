#ifndef ELECTRICAR_
#define ELECTRICAR_

float GpsToDecimalDegrees(const float value, char quadrant);
float CalculateHeadingVehicle(const float new_lat,const float new_long,const float old_lat,const float old_long);
int IS_FLOAT(char* arr);
char ci2a(char *num);
char* cf2a(char *num);
int IS_CONTAIN(char* num,char parameter);
char* CONVERT_ASCII(char* arr[],int count);

#endif
