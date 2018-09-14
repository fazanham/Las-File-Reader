/*Example*/
#include <fstream>
#include <iostream>
#include "LasInput.h"

using namespace std;

int main() {

	char * LasFileName = "../Example.las";

	CLasInput *LasInput = NULL;
	LasInput = new CLasInput(LasFileName);
	LasInput->ReadHeader();

	// no. of points
	int n = LasInput->file_header.Num_p;

	//Check if the las file was read
	if (LasInput->file_header.DataFormat != 1)
	{
		cout << "The data format is supported by this code!\n";
		exit(0);
	}

	FILE *fpInputFile = fopen(LasFileName, "rb");

	// offset to the data points
	fseek(fpInputFile, LasInput->file_header.OffsetToData, SEEK_SET);

	long* x_l;
	long x_o;
	x_l = &x_o;
	unsigned short* x_us;
	unsigned short i_us;
	x_us = &i_us;
	unsigned long num;
	unsigned long *k;
	k = &num;
	double *x_d;
	double t_d;
	x_d = &t_d;

	//Flight information
	double *LL, L;
	LL = &L;
	double *BB, B;
	BB = &B;
	double *HH, H;
	HH = &H;

	for (int i = 0; i < n; ++i)
	{
		fread(x_l, 4, 1, fpInputFile);
		double x = x_o*LasInput->file_header.x_s + LasInput->file_header.x_offset;

		fread(x_l, 4, 1, fpInputFile);
		double y = x_o*LasInput->file_header.y_s + LasInput->file_header.y_offset;

		fread(x_l, 4, 1, fpInputFile);
		double z = x_o*LasInput->file_header.z_s + LasInput->file_header.z_offset;

		fread(x_us, 2, 1, fpInputFile);
		double intensity = i_us;

		fread(k, 1, 1, fpInputFile);
		bitset<8> b(num);
		int return_no = b[0] * 1 + b[1] * 2 + b[2] * 4;

		fseek(fpInputFile, 5, 1);
		fread(x_d, 8, 1, fpInputFile);
	}

	return 0;
}