#include <stdlib.h>
#include <stdio.h>
#include <math.h>
 
/**
 * https://en.wikipedia.org/wiki/Perlin_noise
 * https://www.youtube.com/watch?v=6-0UaeJBumA
 */

/*
 static unsigned int hash[] = { 
    208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
    185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
    9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
    70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
    203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
    164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
    228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
    232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
    193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
    101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
    135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
    114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219
}; 
 */

int p[512] = {
   151,160,137,91,90,15,
   131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
   190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
   88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
   77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
   102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
   135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
   5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
   223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
   129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
   251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
   49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
   138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};
 
static inline double
fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

static inline double
lerp(double t, double a, double b)
{ 
    return a + t * (b - a);
}

static double 
grad(int hash, double x, double y, double z)
{
    int h = hash & 15;                      
    double u = h<8 ? x : y,                 
            v = h<4 ? y : h==12||h==14 ? x : z;
    return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}
 
double
noise(double x, double y, double z)
{
    int X = (int)floor(x) & 255,                  
        Y = (int)floor(y) & 255,                  
        Z = (int)floor(z) & 255;
    x -= floor(x);                                
    y -= floor(y);                                
    z -= floor(z);
    double u = fade(x),                                
            v = fade(y),                                
            w = fade(z);
    int A = p[X  ]+Y, AA = p[A]+Z, AB = p[A+1]+Z,      
        B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;   

    return lerp(w, lerp(v, lerp(u, grad(p[AA  ], x  , y  , z   ), 
                                    grad(p[BA  ], x-1, y  , z   )),
                            lerp(u, grad(p[AB  ], x  , y-1, z   ), 
                                    grad(p[BB  ], x-1, y-1, z   ))),
                    lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ), 
                                    grad(p[BA+1], x-1, y  , z-1 )), 
                            lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
                                    grad(p[BB+1], x-1, y-1, z-1 ))));
}
 
void loadPermutation(char *fileName)
{
	FILE *fp = fopen(fileName, "r");
	int permutation[256];
 
	for (int i = 0; i < 256; i++) {
		fscanf(fp,"%d",&permutation[i]);
    }
 
	fclose(fp);
 
	for (int i = 0; i < 256; i++) {
        p[256+i] = p[i] = permutation[i];
    }
}
 
 /*
int main(int argc, char *argv[])
{
	if (argc != 5) {
		printf("Usage : %s <permutation data file> <x,y,z co-ordinates separated by space>");
	} else {
		//loadPermutation(argv[1]);
		printf("Perlin Noise for (%s,%s,%s) is %.17lf",argv[2],argv[3],argv[4],noise(strtod(argv[2],NULL),strtod(argv[3],NULL),strtod(argv[4],NULL)));
	}
 
	return 0;
}
*/

/*
uint32_t 
noise_perlin_2d(uint32_t x, uint32_t y, uint32_t seed)
{
    uint32_t tmp = hash[(y + seed) % 256];
    return hash[(tmp + x) % 256];
}

float 
lin_inter(float x, float y, float s)
{
    return x + s * (y-x);
}

float
smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3-2*s));
}

float noise2d(float x, float y)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int);
    int t = noise2(x_int+1, y_int);
    int u = noise2(x_int, y_int+1);
    int v = noise2(x_int+1, y_int+1);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);
}

float perlin2d(float x, float y, float freq, int depth)
{
    float xa = x*freq;
    float ya = y*freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for (i=0; i<depth; i++) {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin/div;
}

*/