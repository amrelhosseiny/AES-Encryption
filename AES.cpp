#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

typedef unsigned int word;
//typedef int byte;



//Gobal Variables
unsigned int text[16];
unsigned int textInFormat[4][4];
unsigned int inputKey[16];
unsigned int roundKey[16];
unsigned int preFirstRoundKey[4][4];
unsigned int roundKeyInFormat[4][4];
unsigned int FullKey[176];
word textInWord[4];
unsigned int sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

unsigned  int rc[11] = { 0x8d,0x01,0x02,0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };


//Methods
unsigned int gf(unsigned int entery, unsigned int element) {

	if (element == 02)
	{
		if ((entery & 128) == 0) { entery = entery << 1; }
		else { entery = (entery << 1) ^ 0x11b; }
	}
	else if (element == 03)
	{
		if ((entery & 128) == 0) { entery = (entery << 1) ^ entery; }
		else { entery = ((entery << 1) ^ 0x11b) ^ entery; }
	}
	else {}
	return entery;
}

void substituteints(unsigned int(&in)[16]) {
	for (unsigned int i = 0; i < 16; i++) {
		in[i] = sbox[in[i]];
	}
}

void putInFormat(unsigned int in[16], unsigned int(&out)[4][4]) {
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			out[j][i] = in[4 * i + j];
		}
	}
}

void getFromFormat(unsigned int in[4][4], unsigned int(&out)[16]) {
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			out[4 * i + j] = in[j][i];
		}
	}
}

void putInFormatInv(unsigned int in[16], unsigned int(&out)[4][4]) {
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			out[i][j] = in[4 * i + j];
		}
	}
}

void getFromFormatInv(unsigned int in[4][4], unsigned int(&out)[16]) {
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			out[4 * i + j] = in[i][j];
		}
	}
}

void shiftRows(unsigned int(&in)[4][4]) {
	unsigned int temp[4][4] = {};
	//temp = in;
	//std::copy(&in[0][0], &in[4][4] , &temp[0][0]);
	//memcpy(temp, in, sizeof(temp));
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			temp[i][j] = in[i][j];
		}
	}
	for (unsigned int i = 1; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			in[i][j] = temp[i][(j + i) % 4];
		}
	}
}

void addRoundKey(unsigned int(&in)[4][4], unsigned int(&key)[4][4]) {
	for (unsigned int i = 0; i < 4; i++) {
		//unsigned unsigned int inputWord = (a << 24) | (b << 16) | (c << 8) | d;
		for (unsigned int j = 0; j < 4; j++) {
			in[i][j] = in[i][j] ^ key[i][j];
		}
	}
}

void mixCol(unsigned int(&in)[4][4]) {
	unsigned int temp[4][4] = {};
	//temp = in;
	//std::copy(&in[0][0], &in[4][4], &temp[0][0]);
	//memcpy(temp, in, sizeof(temp));
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			temp[i][j] = in[i][j];
		}
	}
	for (unsigned int j = 0; j < 4; j++) {
		in[0][j] = (gf(temp[0][j], (unsigned int)02)) ^ (gf(temp[1][j], (unsigned int)03)) ^ temp[2][j] ^ temp[3][j];
		in[1][j] = temp[0][j] ^ (gf(temp[1][j], (unsigned int)02)) ^ (gf(temp[2][j], (unsigned int)03)) ^ temp[3][j];
		in[2][j] = temp[0][j] ^ temp[1][j] ^ (gf(temp[2][j], (unsigned int)02)) ^ (gf(temp[3][j], (unsigned int)03));
		in[3][j] = (gf(temp[0][j], (unsigned int)03)) ^ temp[1][j] ^ temp[2][j] ^ (gf(temp[3][j], (unsigned int)02));
	}
}

void expandKey() {

	unsigned int temp1;
	unsigned int temp2;
	unsigned int temp3;
	unsigned int temp4;

	for (unsigned int i = 0; i < 16; i++) {
		FullKey[i] = inputKey[i];// get subarray to increse performance
	}
	for (unsigned int i = 4; i < 44; i++) {

		temp1 = FullKey[(i - 1) * 4];
		temp2 = FullKey[((i - 1) * 4) + 1];
		temp3 = FullKey[((i - 1) * 4) + 2];
		temp4 = FullKey[((i - 1) * 4) + 3];

		if (i % 4 == 0) {
			unsigned int temp = temp1;
			temp1 = sbox[temp2] ^ rc[i / 4];
			temp2 = sbox[temp3];
			temp3 = sbox[temp4];
			temp4 = sbox[temp];
		}

		FullKey[i * 4] = FullKey[(i - 4) * 4] ^ temp1;
		FullKey[(i * 4) + 1] = FullKey[((i - 4) * 4) + 1] ^ temp2;
		FullKey[(i * 4) + 2] = FullKey[((i - 4) * 4) + 2] ^ temp3;
		FullKey[(i * 4) + 3] = FullKey[((i - 4) * 4) + 3] ^ temp4;
	}


}

int main() {
	string key;
	string txt;
	unsigned int noOfCases;
	unsigned int noOfEnc;

	cin >> noOfCases;


	for (unsigned int a = 0; a < noOfCases; a++) {
		//cin >> txt;
		for (unsigned int q = 0; q < 16; q++) {
			scanf("%02x", &text[q]);
		}
		//cin >> key;
		for (unsigned int q = 0; q < 16; q++) {
			scanf("%02x", &inputKey[q]);
		}
		cin >> noOfEnc;

		//cout << inputKey[0] << text[0]<<"\n";
		/*	for (unsigned int i = 1; i < 16; i++) {
		inputKey[i] = std::stoul(key.substr(i * 2, 2), nullptr, 16);
		text[i] = std::stoul(txt.substr(i * 2, 2), nullptr, 16);
		}*/

		for (unsigned int b = 0; b < noOfEnc; b++) {

			//expand key
			expandKey();


			//get pre first round key and add it to text
			for (unsigned int i = 0; i < 4; i++) {
				for (unsigned int j = 0; j < 4; j++) {
					preFirstRoundKey[i][j] = FullKey[4 * i + j];
				}
			}
			putInFormatInv(text, textInFormat);
			addRoundKey(textInFormat, preFirstRoundKey);
			getFromFormatInv(textInFormat, text);
			//printf("text after pre round add key %20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x\n", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7], text[8], text[9], text[10], text[11], text[12], text[13], text[14], text[15]);

			for (unsigned int c = 0; c < 10; c++) {

				//get round key 
				for (unsigned int d = 0; d < 16; d++) {
					roundKey[d] = FullKey[16 * c + d + 16];
				}
				//	printf("round %d key %20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x\n", c, roundKey[0], roundKey[1], roundKey[2], roundKey[3], roundKey[4], roundKey[5], roundKey[6], roundKey[7], roundKey[8], roundKey[9], roundKey[10], roundKey[11], roundKey[12], roundKey[13], roundKey[14], roundKey[15]);

				//sub unsigned ints
				substituteints(text);
				//	printf("text after sub  %20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x%20x\n", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7], text[8], text[9], text[10], text[11], text[12], text[13], text[14], text[15]);

				//put things in format
				putInFormat(text, textInFormat);
				putInFormat(roundKey, roundKeyInFormat);
				/*printf("text in format");
				for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
				printf("%20x", textInFormat[i][j]);
				}printf("\n");
				}*/

				//shifting rows
				shiftRows(textInFormat);
				/*	printf("after shifting rows\n");
				for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
				printf("%20x", textInFormat[i][j]);
				}printf("\n");
				}*/

				//mixing colums
				if (c == 9) {}
				else {
					mixCol(textInFormat);
				}
				/*	printf("after mixing columsb\n");
				for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
				printf("%20x", textInFormat[i][j]);
				}printf("\n");
				}*/

				//adding round key
				addRoundKey(textInFormat, roundKeyInFormat);
				/*	printf("after adding round key");
				for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
				printf("%20x", textInFormat[i][j]);
				}printf("\n");
				}*/

				getFromFormat(textInFormat, text);
			}
			//last round key is first key for next encryption
			//memcpy(inputKey, roundKey, sizeof(inputKey));
		/*	for (unsigned int i = 0; i < 16; i++) {
				inputKey[i] = roundKey[i];
			}*/
			getFromFormat(textInFormat, text);
			//printf("ciper text %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7], text[8], text[9], text[10], text[11], text[12], text[13], text[14], text[15]);
			//printf("round 10 key %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", inputKey[0], inputKey[1], inputKey[2], inputKey[3], inputKey[4], inputKey[5], inputKey[6], inputKey[7], inputKey[8], inputKey[9], inputKey[10], inputKey[11], inputKey[12], inputKey[13], inputKey[14], inputKey[15]);

		}
		printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7], text[8], text[9], text[10], text[11], text[12], text[13], text[14], text[15]);
		//	cout << text[0] << text[1] << text[2] << text[3] << text[4] << text[5] << text[6] << text[7] << text[8] << text[9] << text[10] << text[11] << text[12] << text[13] << text[14] << text[15] << "\n";
	}
	return 1;
}