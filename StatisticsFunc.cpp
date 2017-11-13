//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>
#include <float.h>
#include <math.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

bool statistics(const float dataset[], const int size,
                float& min, float& avg, float& max,
	        float& popSD, float& smplSD, float& mdn);

float minimum(const float dataset[], const int size);
float average(const float dataset[], const int size);
float maximum(const float dataset[], const int size);
float popStdDev(const float dataset[], const int size);
float smplStdDev(const float dataset[], const int size);
float median(const float dataset[], const int size);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

bool statistics(const float dataset[], const int size,
	   float& min, float& avg, float& max,
	   float& popSD, float& smplSD, float& mdn) {
	if(size<1)
		return false;
	min=minimum(dataset,size);
	avg=average(dataset,size);
	max=maximum(dataset,size);
	popSD=popStdDev(dataset,size);
	smplSD=smplStdDev(dataset,size);
	mdn=median(dataset,size);
	return true;
  
}

float minimum(const float dataset[], const int size) {
	int i=0;
	float min=dataset[0];
	while(i<size){
		if(dataset[i]<min)
			min=dataset[i];
		i++;
	}
	return min;
}

float average(const float dataset[], const int size) {
	int i=0;
	float sum=0;
	float avg;
	while(i<size){
		sum=sum+dataset[i];
		i++;
	}
	avg=sum/size;
	return avg;
}

float maximum(const float dataset[], const int size) {
	int i=0;
	float max=dataset[0];
	while(i<size){
		if(dataset[i]>max)
			max=dataset[i];
		i++;
	}
	return max;
}

float popStdDev(const float dataset[], const int size) {
	int i=0;
	float sum=0;
	float stdp;
	while(i<size){
		sum=(sum+(dataset[i]-average(dataset,size))*(dataset[i]-average(dataset,size)));
		i++;
	}
	stdp=sqrt(sum / size);
	return stdp;
}

float smplStdDev(const float dataset[], const int size) {
	if(size<2)
		return std::numeric_limits<float>::quiet_NaN();
	int i=0;
	float sum=0;
	float stds;
	while(i<size){
		sum=(sum+(dataset[i]-average(dataset,size))*(dataset[i]-average(dataset,size)));
		i++;
	}
	stds=sqrt(sum / (size-1));
	return stds;
}

float median(const float dataset[], const int size) {
	float A[size];
	float median;
	
    for(int i = 0; i < size; i++) {
		A[i] = dataset[i];
    }
	for(int n = size; n > 1; n--) {
		for(int i = 1; i < n; i++) {
			if(A[i-1] > A[i]) {
				float tmp = A[i-1];
				A[i-1] = A[i];
				A[i] = tmp;
			}
		}
	}
	if(size%2==0)
		median=(A[(size-2)/2]+A[size/2])/2;
	if(size%2==1)
		median=A[(size-1)/2];
	return median;
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {
  int size = 5;
  float dataset[] = {1, 2, 3, 4, 5};
  float min;
  float avg;
  float max;
  float popStDev;
  float smplStDev;
  float median;

  if (statistics(dataset, size, min, avg, max, popStDev, smplStDev, median)) {
    cout << "Minimum: " << min << endl
	 << "Average: " << avg << endl
	 << "Median:  " << median << endl
	 << "Maximum: " << max << endl
	 << "Population Standard Deviation: " << popStDev << endl
	 << "Sample Standard Deviation:     " << smplStDev << endl;
  }
  else
    cout << "Error: unable to compute statistics" << endl;

  return 0;
}

#endif
