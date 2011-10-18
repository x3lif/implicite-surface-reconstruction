#include "mc.h"

int Edge_Table[256]={
		0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
		0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
		0x190, 0x99 , 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
		0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
		0x230, 0x339, 0x33 , 0x13a, 0x636, 0x73f, 0x435, 0x53c,
		0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
		0x3a0, 0x2a9, 0x1a3, 0xaa , 0x7a6, 0x6af, 0x5a5, 0x4ac,
		0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
		0x460, 0x569, 0x663, 0x76a, 0x66 , 0x16f, 0x265, 0x36c,
		0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
		0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff , 0x3f5, 0x2fc,
		0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
		0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55 , 0x15c,
		0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
		0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc ,
		0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
		0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
		0xcc , 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
		0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
		0x15c, 0x55 , 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
		0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
		0x2fc, 0x3f5, 0xff , 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
		0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
		0x36c, 0x265, 0x16f, 0x66 , 0x76a, 0x663, 0x569, 0x460,
		0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
		0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa , 0x1a3, 0x2a9, 0x3a0,
		0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
		0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33 , 0x339, 0x230,
		0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
		0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99 , 0x190,
		0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
		0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0   };

int Tri_Table[256][16] = {
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1},
		{3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1},
		{3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1},
		{3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1},
		{9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1},
		{1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},
		{9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
		{2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1},
		{8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1},
		{9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
		{4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1},
		{3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1},
		{1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1},
		{4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1},
		{4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1},
		{9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1},
		{1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
		{5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1},
		{2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1},
		{9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
		{0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
		{2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1},
		{10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1},
		{4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1},
		{5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1},
		{5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1},
		{9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1},
		{0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
		{1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1},
		{10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1},
		{8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1},
		{2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
		{7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1},
		{9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1},
		{2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1},
		{11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},
		{9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1},
		{5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1},
		{11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1},
		{11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
		{1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1},
		{9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},
		{5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1},
		{2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
		{0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
		{5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1},
		{6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1},
		{0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1},
		{3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1},
		{6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1},
		{5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1},
		{1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
		{10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1},
		{6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},
		{1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1},
		{8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1},
		{7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1},
		{3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
		{5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1},
		{0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1},
		{9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1},
		{8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1},
		{5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1},
		{0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1},
		{6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1},
		{10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1},
		{10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1},
		{8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1},
		{1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1},
		{3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1},
		{0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1},
		{10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1},
		{0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1},
		{3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1},
		{6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1},
		{9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1},
		{8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1},
		{3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1},
		{6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},
		{0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1},
		{10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1},
		{10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1},
		{1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1},
		{2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1},
		{7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1},
		{7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1},
		{2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1},
		{1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1},
		{11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1},
		{8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1},
		{0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1},
		{7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
		{10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
		{2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
		{6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1},
		{7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1},
		{2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1},
		{1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1},
		{10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1},
		{10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1},
		{0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1},
		{7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1},
		{6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
		{8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1},
		{9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1},
		{6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1},
		{1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1},
		{4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1},
		{10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1},
		{8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1},
		{0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1},
		{1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},
		{8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1},
		{10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1},
		{4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1},
		{10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
		{5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
		{11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1},
		{9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
		{6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1},
		{7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1},
		{3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1},
		{7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1},
		{9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1},
		{3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1},
		{6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1},
		{9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1},
		{1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1},
		{4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1},
		{7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1},
		{6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1},
		{3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1},
		{0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1},
		{6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1},
		{1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1},
		{0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1},
		{11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1},
		{6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1},
		{5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1},
		{9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1},
		{1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1},
		{1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1},
		{10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1},
		{0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1},
		{5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1},
		{10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1},
		{11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1},
		{0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1},
		{9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1},
		{7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1},
		{2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1},
		{8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1},
		{9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1},
		{9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1},
		{1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1},
		{9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1},
		{9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1},
		{5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1},
		{0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1},
		{10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1},
		{2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1},
		{0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1},
		{0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1},
		{9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1},
		{5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1},
		{3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1},
		{5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1},
		{8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1},
		{0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1},
		{9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},
		{0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1},
		{1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1},
		{3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1},
		{4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1},
		{9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1},
		{11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1},
		{11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1},
		{2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1},
		{9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1},
		{3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1},
		{1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1},
		{4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1},
		{4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1},
		{0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1},
		{3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1},
		{3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1},
		{0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1},
		{9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1},
		{1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

QVector3D VertexInterp(double isolevel,QVector3D p1,QVector3D p2,double valp1,double valp2)
{
	double mu;
        QVector3D lPoint;

        if (qAbs(isolevel-valp1) < 0.000001)
	  return(p1);
        if (qAbs(isolevel-valp2) < 0.000001)
	  return(p2);
        if (qAbs(valp1-valp2) < 0.000001)
	  return(p1);
	mu = (isolevel - valp1) / (valp2 - valp1);

        lPoint.setX( p1.x() + mu * (p2.x() - p1.x()) );
        lPoint.setY( p1.y() + mu * (p2.y() - p1.y()) );
        lPoint.setZ( p1.z() + mu * (p2.z() - p1.z()) );

        return(lPoint);
}

// --------------------
// class CIntersections
// --------------------

CIntersections::CIntersections(void)
    : x(NULL), y(NULL), z(NULL)
{
}

QVector3D* CIntersections::Get_x(void)
{
    return x;
}

QVector3D* CIntersections::Get_y(void)
{
    return y;
}

QVector3D* CIntersections::Get_z(void)
{
    return z;
}

void CIntersections::Set_x(QVector3D p)
{
    if(x==NULL) x=new QVector3D();
    *x = p;
}

void CIntersections::Set_y(QVector3D p)
{
    if(y==NULL) y=new QVector3D();
    *y=p;
}

void CIntersections::Set_z(QVector3D p)
{
    if(z==NULL) z=new QVector3D();
    *z=p;
}

// --------------------
// class CMarching_Grid
// --------------------

CMarching_Grid::CMarching_Grid(void)
{
    mVerticesTab=NULL;
    mValTab=NULL;
    mDimension=0;
    mCellLength = 0;
}

CMarching_Grid::CMarching_Grid(int d)
{
        mDimension=d;
}

void CMarching_Grid::Allocate(void)
{
    if( mVerticesTab != NULL )  DeAllocate();

    if (mDimension>0)
    {
        int i,j;

        // Creation des sommets
        mVerticesTab = new QVector3D**[mDimension];
        for (i=0;i<mDimension;i++)
        {
                mVerticesTab[i]=new QVector3D*[mDimension];
                for (j=0;j<mDimension;j++)
                        mVerticesTab[i][j]=new QVector3D[mDimension];
        }

        // Creation des valeurs aux sommets
        mValTab = new double**[mDimension];
        for (i=0;i<mDimension;i++)
        {
                mValTab[i]=new double*[mDimension];
                for (j=0;j<mDimension;j++)
                        mValTab[i][j]=new double[mDimension];
        }

        Segment_Intersection = new CIntersections**[mDimension];
        for (i=0;i<mDimension;++i)
        {
                Segment_Intersection[i]=new CIntersections*[mDimension];
                for (j=0;j<mDimension;++j)
                        Segment_Intersection[i][j]=new CIntersections[mDimension];
        }
    }
}

void CMarching_Grid::DeAllocate(void)
{
    // if marching grid hasn't been allocated quit
    if( mVerticesTab == NULL) return;


	int i,j;
        QVector3D O(0,0,0);

        /*
        // Cleaning segments
        for (i=0;i<Dim;i++)
        {
                for (j=0;j<Dim;j++)
                        delete [] Segment_Intersection[i][j];
                delete [] Segment_Intersection[i];
        }
        delete [] Segment_Intersection;
        Segment_Intersection=NULL;
        */

        //cleaning vertices
        for( i=0; i<mDimension; ++i )
        {
            for (j=0;j<mDimension;++j)
                    delete [] mVerticesTab[i][j];
            delete [] mVerticesTab[i];
        }
        delete [] mVerticesTab;
        mVerticesTab=NULL;

        // Cleaning Values
        for ( i=0; i<mDimension; ++i )
        {
            for ( j=0; j<mDimension; ++j )
                    delete [] mValTab[i][j];
            delete [] mValTab[i];
        }
        delete [] mValTab;
        mValTab=NULL;

        // resseting boxes
        for ( i=0; i<8; ++i)
	{
            mBoundedBox.Put_Vertex(i,O);
            mGlobalBox.Put_Vertex(i,O);
	}

        mDimension=0;
        mCellLength=0.0;
}


void CMarching_Grid::Init_Boxes(CVoxel_8 B)
{
	int i;
	double xmin,ymin,zmin,xmax,ymax,zmax;

	for (i=0;i<8;i++)
                mBoundedBox.Put_Vertex(i,B.Get_Vertex(i));

	double xlength,ylength,zlength;
        xlength=mBoundedBox.Get_Vertex(6).x()-mBoundedBox.Get_Vertex(0).x();
        ylength=mBoundedBox.Get_Vertex(6).y()-mBoundedBox.Get_Vertex(0).y();
        zlength=mBoundedBox.Get_Vertex(6).z()-mBoundedBox.Get_Vertex(0).z();

        if ((xlength>ylength)&&(xlength>zlength))
        {
            mCellLength=xlength/(mDimension-4);
        }
        else
        {
            if ((ylength>xlength)&&(ylength>zlength))
            {
                mCellLength=ylength/(mDimension-4);
            }
            else
            {
                mCellLength=zlength/(mDimension-4);
            }
        }

        xmin=mBoundedBox.Get_Vertex(0).x()-2*mCellLength;
        ymin=mBoundedBox.Get_Vertex(0).y()-2*mCellLength;
        zmin=mBoundedBox.Get_Vertex(0).z()-2*mCellLength;
        xmax=mBoundedBox.Get_Vertex(6).x()+2*mCellLength;
        ymax=mBoundedBox.Get_Vertex(6).y()+2*mCellLength;
        zmax=mBoundedBox.Get_Vertex(6).z()+2*mCellLength;
        QVector3D v0(xmin,ymin,zmin),v1(xmax,ymin,zmin),v2(xmax,ymin,zmax),v3(xmin,ymin,zmax),
			  v4(xmin,ymax,zmin),v5(xmax,ymax,zmin),v6(xmax,ymax,zmax),v7(xmin,ymax,zmax);
        mGlobalBox.Put_Vertex(0,v0);
        mGlobalBox.Put_Vertex(1,v1);
        mGlobalBox.Put_Vertex(2,v2);
        mGlobalBox.Put_Vertex(3,v3);
        mGlobalBox.Put_Vertex(4,v4);
        mGlobalBox.Put_Vertex(5,v5);
        mGlobalBox.Put_Vertex(6,v6);
        mGlobalBox.Put_Vertex(7,v7);
}

void CMarching_Grid::Init_Grid(void)
{
	int i,j,k;
        double xlength,ylength,zlength,xmin,ymin,zmin;
        //CPoint_3D PI;
        xmin=mGlobalBox.Get_Vertex(0).x();
        ymin=mGlobalBox.Get_Vertex(0).y();
        zmin=mGlobalBox.Get_Vertex(0).z();
        xlength=(mGlobalBox.Get_Vertex(6).x()-mGlobalBox.Get_Vertex(0).x())/mDimension;
        ylength=(mGlobalBox.Get_Vertex(6).y()-mGlobalBox.Get_Vertex(0).y())/mDimension;
        zlength=(mGlobalBox.Get_Vertex(6).z()-mGlobalBox.Get_Vertex(0).z())/mDimension;
	
        for (i=0;i<mDimension;++i)
        {
                for (j=0;j<mDimension;++j)
                {
                        for (k=0;k<mDimension;++k)
			{
                            /** New Code */
                            mVerticesTab[i][j][k] = QVector3D( xmin+i*xlength, ymin+j*ylength, zmin+k*zlength  );
			}
                }
        }
}

int CMarching_Grid::dimension(void)
{
    return mDimension;
}

void CMarching_Grid::setDimension(int d)
{ 
        if ((mVerticesTab==NULL)&&(mValTab==NULL)&&(mDimension<=0)) {
            mDimension=d;
        }
}

CVoxel_8 CMarching_Grid::boundingBox(void)
{
    return mBoundedBox;
}

CVoxel_8 CMarching_Grid::globalBox(void)
{
    return mGlobalBox;
}

void CMarching_Grid::Compute_Val(const CList_BLob& LB)
{
    int i,j,k;
    for (i=0;i<mDimension;++i)
        for (j=0;j<mDimension;++j)
            for (k=0;k<mDimension;++k)
                mValTab[i][j][k]=LB.Compute_Val( mVerticesTab[i][j][k] );
}




void CMarching_Grid::Draw_Vertex_In(CList_BLob LB)
{
    // TODO use local variable to store point?
    for ( int i=0;i<mDimension;++i)
    {
        for( int j=0;j<mDimension;++j)
        {
            for( int k=0;k<mDimension;++k)
            {
                if (mValTab[i][j][k]>=LB.Get_Threshold())
                {
                        glPointSize(3.0);
                        glBegin(GL_POINTS);
                            glVertex3d(mVerticesTab[i][j][k].x(),mVerticesTab[i][j][k].y(),mVerticesTab[i][j][k].z());
                        glEnd();
                }
            }
        }
    }
}

void CMarching_Grid::Draw_Vertex(void)
{
    // TODO use local variable to store point?
        for (int i=0;i<mDimension;++i)
        {
                for(int j=0;j<mDimension;++j)
                {
                        for(int k=0;k<mDimension;++k)
                        {
                            glPointSize(3.0);
                            glBegin(GL_POINTS);
                                glVertex3d(mVerticesTab[i][j][k].x(),mVerticesTab[i][j][k].y(),mVerticesTab[i][j][k].z());
                            glEnd();
                        }
                }
        }
}

// Pas touch car pas tout compris ce que viens faire l'arithmtique des intervalles ici...
void CMarching_Grid::computeTriangles(CList_BLob &LB,QList<CTriangle>& LT)
{
    int l,cubeindex;
    double isolevel=LB.Get_Threshold();
    QVector3D vertlist[12],v[3];

    for (int i=0;i<mDimension-1;++i)
    {
        for(int j=0;j<mDimension-1;++j)
        {
            for(int k=0;k<mDimension-1;++k)
            {
                cubeindex = 0;
                if ( mValTab[i][j][k]       >= isolevel) cubeindex |= 1;
                if ( mValTab[i+1][j][k]     >= isolevel) cubeindex |= 2;
                if ( mValTab[i+1][j][k+1]   >= isolevel) cubeindex |= 4;
                if ( mValTab[i][j][k+1]     >= isolevel) cubeindex |= 8;
                if ( mValTab[i][j+1][k]     >= isolevel) cubeindex |= 16;
                if ( mValTab[i+1][j+1][k]   >= isolevel) cubeindex |= 32;
                if ( mValTab[i+1][j+1][k+1] >= isolevel) cubeindex |= 64;
                if ( mValTab[i][j+1][k+1]   >= isolevel) cubeindex |= 128;

                // Cube is not entirely in/out of the surface
                if (Edge_Table[cubeindex] != 0)
                {
                    // Find the vertices where the surface intersects the cube
                    if (Edge_Table[cubeindex] & 1)
                    {
                            if (Segment_Intersection[i][j][k].Get_x()==NULL)
                            {
                                    Segment_Intersection[i][j][k].Set_x(VertexInterp(isolevel,mVerticesTab[i][j][k],mVerticesTab[i+1][j][k],mValTab[i][j][k],mValTab[i+1][j][k]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i][j][k].x));
                            }
                            vertlist[0] = *Segment_Intersection[i][j][k].Get_x();
                    }

                    if (Edge_Table[cubeindex] & 2)
                    {
                            if (Segment_Intersection[i+1][j][k].Get_z()==NULL)
                            {
                                    Segment_Intersection[i+1][j][k].Set_z(VertexInterp(isolevel,mVerticesTab[i+1][j][k],mVerticesTab[i+1][j][k+1],mValTab[i+1][j][k],mValTab[i+1][j][k+1]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i+1][j][k].z));
                            }
                            vertlist[1] = *Segment_Intersection[i+1][j][k].Get_z();
                    }

                    if (Edge_Table[cubeindex] & 4)
                    {
                            if (Segment_Intersection[i][j][k+1].Get_x()==NULL)
                            {
                                    Segment_Intersection[i][j][k+1].Set_x(VertexInterp(isolevel,mVerticesTab[i][j][k+1],mVerticesTab[i+1][j][k+1],mValTab[i][j][k+1],mValTab[i+1][j][k+1]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i][j][k+1].x));
                            }
                            vertlist[2] = *Segment_Intersection[i][j][k+1].Get_x();
                    }

                    if (Edge_Table[cubeindex] & 8)
                    {
                            if (Segment_Intersection[i][j][k].Get_z()==NULL)
                            {
                                    Segment_Intersection[i][j][k].Set_z(VertexInterp(isolevel,mVerticesTab[i][j][k],mVerticesTab[i][j][k+1],mValTab[i][j][k],mValTab[i][j][k+1]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i][j][k].z));
                            }
                            vertlist[3] = *Segment_Intersection[i][j][k].Get_z();
                    }

                    if (Edge_Table[cubeindex] & 16)
                    {
                            if (Segment_Intersection[i][j+1][k].Get_x()==NULL)
                            {
                                    Segment_Intersection[i][j+1][k].Set_x(VertexInterp(isolevel,mVerticesTab[i][j+1][k],mVerticesTab[i+1][j+1][k],mValTab[i][j+1][k],mValTab[i+1][j+1][k]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i][j+1][k].x));
                            }
                            vertlist[4] = *Segment_Intersection[i][j+1][k].Get_x();
                    }

                    if (Edge_Table[cubeindex] & 32)
                    {
                            if (Segment_Intersection[i+1][j+1][k].Get_z()==NULL)
                            {
                                    Segment_Intersection[i+1][j+1][k].Set_z(VertexInterp(isolevel,mVerticesTab[i+1][j+1][k],mVerticesTab[i+1][j+1][k+1],mValTab[i+1][j+1][k],mValTab[i+1][j+1][k+1]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i+1][j+1][k].z));
                            }
                            vertlist[5] = *Segment_Intersection[i+1][j+1][k].Get_z();
                    }

                    if (Edge_Table[cubeindex] & 64)
                    {
                            if (Segment_Intersection[i][j+1][k+1].Get_x()==NULL)
                            {
                                    Segment_Intersection[i][j+1][k+1].Set_x(VertexInterp(isolevel,mVerticesTab[i][j+1][k+1],mVerticesTab[i+1][j+1][k+1],mValTab[i][j+1][k+1],mValTab[i+1][j+1][k+1]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i][j+1][k+1].x));
                            }
                            vertlist[6] = *Segment_Intersection[i][j+1][k+1].Get_x();
                    }

                    if (Edge_Table[cubeindex] & 128)
                    {
                            if (Segment_Intersection[i][j+1][k].Get_z()==NULL)
                            {
                                    Segment_Intersection[i][j+1][k].Set_z(VertexInterp(isolevel,mVerticesTab[i][j+1][k],mVerticesTab[i][j+1][k+1],mValTab[i][j+1][k],mValTab[i][j+1][k+1]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i][j+1][k].z));
                            }
                                    vertlist[7] = *Segment_Intersection[i][j+1][k].Get_z();
                    }

                    if (Edge_Table[cubeindex] & 256)
                    {
                            if (Segment_Intersection[i][j][k].Get_y()==NULL)
                            {
                                    Segment_Intersection[i][j][k].Set_y(VertexInterp(isolevel,mVerticesTab[i][j][k],mVerticesTab[i][j+1][k],mValTab[i][j][k],mValTab[i][j+1][k]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i][j][k].y));
                            }
                            vertlist[8] = *Segment_Intersection[i][j][k].Get_y();
                    }

                    if (Edge_Table[cubeindex] & 512)
                    {
                            if (Segment_Intersection[i+1][j][k].Get_y()==NULL)
                            {
                                    Segment_Intersection[i+1][j][k].Set_y(VertexInterp(isolevel,mVerticesTab[i+1][j][k],mVerticesTab[i+1][j+1][k],mValTab[i+1][j][k],mValTab[i+1][j+1][k]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i+1][j][k].y));
                            }
                            vertlist[9] = *Segment_Intersection[i+1][j][k].Get_y();
                    }

                    if (Edge_Table[cubeindex] & 1024)
                    {
                            if (Segment_Intersection[i+1][j][k+1].Get_y()==NULL)
                            {
                                    Segment_Intersection[i+1][j][k+1].Set_y(VertexInterp(isolevel,mVerticesTab[i+1][j][k+1],mVerticesTab[i+1][j+1][k+1],mValTab[i+1][j][k+1],mValTab[i+1][j+1][k+1]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i+1][j][k+1].y));
                            }
                            vertlist[10] = *Segment_Intersection[i+1][j][k+1].Get_y();
                    }

                    if (Edge_Table[cubeindex] & 2048)
                    {
                            if (Segment_Intersection[i][j][k+1].Get_y()==NULL)
                            {
                                    Segment_Intersection[i][j][k+1].Set_y(VertexInterp(isolevel,mVerticesTab[i][j][k+1],mVerticesTab[i][j+1][k+1],mValTab[i][j][k+1],mValTab[i][j+1][k+1]));
                                    //LB.Compute_Gradient_and_Color_on_Surface(*(Segment_Intersection[i][j][k+1].y));
                            }
                            vertlist[11] = *Segment_Intersection[i][j][k+1].Get_y();
                    }

                    // Create the triangle
                    for (l=0;Tri_Table[cubeindex][l]!=-1;l+=3)
                    {
                            v[0] = vertlist[Tri_Table[cubeindex][l]];
                            v[1] = vertlist[Tri_Table[cubeindex][l+1]];
                            v[2] = vertlist[Tri_Table[cubeindex][l+2]];

                            LT.append(CTriangle(v));
                    }
                }
            }
        }
    }
    qWarning()<<"Nombre de triangles : "<<LT.size();

}

