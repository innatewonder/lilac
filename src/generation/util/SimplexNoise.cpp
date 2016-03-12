/* Copyright (c) 2007-2012 Eliot Eshelman
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include "CommonPrecompiled.h"
#include <math.h>

#include "SimplexNoise.h"

// The gradients are the midpos32s of the vertices of a cube.
static const s32 grad3[12][3] =
{
  { 1, 1, 0 }, { -1, 1, 0 }, { 1, -1, 0 }, { -1, -1, 0 },
  { 1, 0, 1 }, { -1, 0, 1 }, { 1, 0, -1 }, { -1, 0, -1 },
  { 0, 1, 1 }, { 0, -1, 1 }, { 0, 1, -1 }, { 0, -1, -1 }
};


// The gradients are the midpos32s of the vertices of a hypercube.
static const s32 grad4[32][4] =
{
  { 0, 1, 1, 1 }, { 0, 1, 1, -1 }, { 0, 1, -1, 1 }, { 0, 1, -1, -1 },
  { 0, -1, 1, 1 }, { 0, -1, 1, -1 }, { 0, -1, -1, 1 }, { 0, -1, -1, -1 },
  { 1, 0, 1, 1 }, { 1, 0, 1, -1 }, { 1, 0, -1, 1 }, { 1, 0, -1, -1 },
  { -1, 0, 1, 1 }, { -1, 0, 1, -1 }, { -1, 0, -1, 1 }, { -1, 0, -1, -1 },
  { 1, 1, 0, 1 }, { 1, 1, 0, -1 }, { 1, -1, 0, 1 }, { 1, -1, 0, -1 },
  { -1, 1, 0, 1 }, { -1, 1, 0, -1 }, { -1, -1, 0, 1 }, { -1, -1, 0, -1 },
  { 1, 1, 1, 0 }, { 1, 1, -1, 0 }, { 1, -1, 1, 0 }, { 1, -1, -1, 0 },
  { -1, 1, 1, 0 }, { -1, 1, -1, 0 }, { -1, -1, 1, 0 }, { -1, -1, -1, 0 }
};


// Permutation table.  The same list is repeated twice.
static const s32 perm[512] =
{
  151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
  8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117,
  35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
  134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41,
  55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89,
  18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226,
  250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182,
  189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43,
  172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97,
  228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239,
  107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
  138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180,

  151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
  8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117,
  35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
  134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41,
  55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89,
  18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226,
  250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182,
  189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43,
  172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97,
  228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239,
  107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
  138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};


// A lookup table to traverse the simplex around a given pos32 in 4D.
static const s32 simplex[64][4] =
{
  { 0, 1, 2, 3 }, { 0, 1, 3, 2 }, { 0, 0, 0, 0 }, { 0, 2, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 2, 3, 0 },
  { 0, 2, 1, 3 }, { 0, 0, 0, 0 }, { 0, 3, 1, 2 }, { 0, 3, 2, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 3, 2, 0 },
  { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
  { 1, 2, 0, 3 }, { 0, 0, 0, 0 }, { 1, 3, 0, 2 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 2, 3, 0, 1 }, { 2, 3, 1, 0 },
  { 1, 0, 2, 3 }, { 1, 0, 3, 2 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 2, 0, 3, 1 }, { 0, 0, 0, 0 }, { 2, 1, 3, 0 },
  { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
  { 2, 0, 1, 3 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 3, 0, 1, 2 }, { 3, 0, 2, 1 }, { 0, 0, 0, 0 }, { 3, 1, 2, 0 },
  { 2, 1, 0, 3 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 3, 1, 0, 2 }, { 0, 0, 0, 0 }, { 3, 2, 0, 1 }, { 3, 2, 1, 0 }
};

f64 Dot(const s32* g, f64 x, f64 y)
{
  return g[0] * x + g[1] * y;
}

f64 Dot(const s32* g, f64 x, f64 y, f64 z)
{
  return g[0] * x + g[1] * y + g[2] * z;
}

f64 Dot(const s32* g, f64 x, f64 y, f64 z, f64 w)
{
  return g[0] * x + g[1] * y + g[2] * z + g[3] * w;
}

s32 fastfloor(f64 x)
{
  return x > 0 ? (s32)x : (s32)x - 1;
}

// 2D Multi-octave Simplex noise.
//
// For each octave, a higher frequency/lower amplitude function will be added to the original.
// The higher the persistence [0-1], the more of each succeeding octave will be added.
f64 SimplexNoise::GetOctaves(f64 octaves, f64 persistence, f64 scale, f64 x, f64 y)
{
  f64 total = 0;
  f64 frequency = scale;
  f64 amplitude = 1;

  // We have to keep track of the largest possible amplitude,
  // because each octave adds more, and we need a value in [-1, 1].
  f64 maxAmplitude = 0;

  for(s32 i = 0; i < octaves; i++)
  {
    total += Get(x * frequency, y * frequency) * amplitude;

    frequency *= 2;
    maxAmplitude += amplitude;
    amplitude *= persistence;
  }

  return total / maxAmplitude;
}


// 3D Multi-octave Simplex noise.
//
// For each octave, a higher frequency/lower amplitude function will be added to the original.
// The higher the persistence [0-1], the more of each succeeding octave will be added.
f64 SimplexNoise::GetOctaves(f64 octaves, f64 persistence, f64 scale, f64 x, f64 y, f64 z)
{
  f64 total = 0;
  f64 frequency = scale;
  f64 amplitude = 1;

  // We have to keep track of the largest possible amplitude,
  // because each octave adds more, and we need a value in [-1, 1].
  f64 maxAmplitude = 0;

  for(s32 i = 0; i < octaves; i++)
  {
    total += Get(x * frequency, y * frequency, z * frequency) * amplitude;

    frequency *= 2;
    maxAmplitude += amplitude;
    amplitude *= persistence;
  }

  return total / maxAmplitude;
}


// 4D Multi-octave Simplex noise.
//
// For each octave, a higher frequency/lower amplitude function will be added to the original.
// The higher the persistence [0-1], the more of each succeeding octave will be added.
f64 SimplexNoise::GetOctaves(f64 octaves, f64 persistence, f64 scale, f64 x, f64 y, f64 z, f64 w)
{
  f64 total = 0;
  f64 frequency = scale;
  f64 amplitude = 1;

  // We have to keep track of the largest possible amplitude,
  // because each octave adds more, and we need a value in [-1, 1].
  f64 maxAmplitude = 0;

  for(s32 i = 0; i < octaves; i++)
  {
    total += Get(x * frequency, y * frequency, z * frequency, w * frequency) * amplitude;

    frequency *= 2;
    maxAmplitude += amplitude;
    amplitude *= persistence;
  }

  return total / maxAmplitude;
}



// 2D Scaled Multi-octave Simplex noise.
//
// Returned value will be between loBound and hiBound.
f64 SimplexNoise::GetScaledOctaves(f64 octaves, f64 persistence, f64 scale, f64 loBound, f64 hiBound, f64 x, f64 y) {
  return GetOctaves(octaves, persistence, scale, x, y) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}


// 3D Scaled Multi-octave Simplex noise.
//
// Returned value will be between loBound and hiBound.
f64 SimplexNoise::GetScaledOctaves(f64 octaves, f64 persistence, f64 scale, f64 loBound, f64 hiBound, f64 x, f64 y, f64 z) {
  return GetOctaves(octaves, persistence, scale, x, y, z) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}

// 4D Scaled Multi-octave Simplex noise.
//
// Returned value will be between loBound and hiBound.
f64 SimplexNoise::GetScaledOctaves(f64 octaves, f64 persistence, f64 scale, f64 loBound, f64 hiBound, f64 x, f64 y, f64 z, f64 w) {
  return GetOctaves(octaves, persistence, scale, x, y, z, w) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}



// 2D Scaled Simplex raw noise.
//
// Returned value will be between loBound and hiBound.
f64 SimplexNoise::GetScaled(f64 loBound, f64 hiBound, f64 x, f64 y) {
  return Get(x, y) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}


// 3D Scaled Simplex raw noise.
//
// Returned value will be between loBound and hiBound.
f64 SimplexNoise::GetScaled(f64 loBound, f64 hiBound, f64 x, f64 y, f64 z) {
  return Get(x, y, z) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}

// 4D Scaled Simplex raw noise.
//
// Returned value will be between loBound and hiBound.
f64 SimplexNoise::GetScaled(f64 loBound, f64 hiBound, f64 x, f64 y, f64 z, f64 w) {
  return Get(x, y, z, w) * (hiBound - loBound) / 2 + (hiBound + loBound) / 2;
}



// 2D raw Simplex noise
f64 SimplexNoise::Get(f64 x, f64 y) {
  // Noise contributions from the three corners
  f64 n0, n1, n2;

  // Skew the input space to determine which simplex cell we're in
  f64 F2 = 0.5 * (sqrtf(3.0) - 1.0);
  // Hairy factor for 2D
  f64 s = (x + y) * F2;
  s32 i = fastfloor(x + s);
  s32 j = fastfloor(y + s);

  f64 G2 = (3.0 - sqrtf(3.0)) / 6.0;
  f64 t = (i + j) * G2;
  // Unskew the cell origin back to (x,y) space
  f64 X0 = i - t;
  f64 Y0 = j - t;
  // The x,y distances from the cell origin
  f64 x0 = x - X0;
  f64 y0 = y - Y0;

  // For the 2D case, the simplex shape is an equilateral triangle.
  // Determine which simplex we are in.
  s32 i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
  if(x0 > y0)
  {  // lower triangle, XY order: (0,0)->(1,0)->(1,1)
    i1 = 1; j1 = 0;
  }
  else
  { // upper triangle, YX order: (0,0)->(0,1)->(1,1) 
    i1 = 0; j1 = 1;
  }

  // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
  // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
  // c = (3-sqrt(3))/6
  f64 x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
  f64 y1 = y0 - j1 + G2;
  f64 x2 = x0 - 1.0 + 2.0 * G2; // Offsets for last corner in (x,y) unskewed coords
  f64 y2 = y0 - 1.0 + 2.0 * G2;

  // Work out the hashed gradient indices of the three simplex corners
  s32 ii = i & 255;
  s32 jj = j & 255;
  s32 gi0 = perm[ii + perm[jj]] % 12;
  s32 gi1 = perm[ii + i1 + perm[jj + j1]] % 12;
  s32 gi2 = perm[ii + 1 + perm[jj + 1]] % 12;

  // Calculate the contribution from the three corners
  f64 t0 = 0.5 - x0*x0 - y0*y0;
  if(t0 < 0)
    n0 = 0.0;
  else
  {
    t0 *= t0;
    n0 = t0 * t0 * Dot(grad3[gi0], x0, y0); // (x,y) of grad3 used for 2D gradient
  }

  f64 t1 = 0.5 - x1*x1 - y1*y1;
  if(t1 < 0)
    n1 = 0.0;
  else
  {
    t1 *= t1;
    n1 = t1 * t1 * Dot(grad3[gi1], x1, y1);
  }

  f64 t2 = 0.5 - x2*x2 - y2*y2;
  if(t2 < 0)
    n2 = 0.0;
  else
  {
    t2 *= t2;
    n2 = t2 * t2 * Dot(grad3[gi2], x2, y2);
  }

  // Add contributions from each corner to get the final noise value.
  // The result is scaled to return values in the s32erval [-1,1].
  return 70.0 * (n0 + n1 + n2);
}


// 3D raw Simplex noise
f64 SimplexNoise::Get(f64 x, f64 y, f64 z) {
  f64 n0, n1, n2, n3; // Noise contributions from the four corners

  // Skew the input space to determine which simplex cell we're in
  f64 F3 = 1.0 / 3.0;
  f64 s = (x + y + z)*F3; // Very nice and simple skew factor for 3D
  s32 i = fastfloor(x + s);
  s32 j = fastfloor(y + s);
  s32 k = fastfloor(z + s);

  f64 G3 = 1.0 / 6.0; // Very nice and simple unskew factor, too
  f64 t = (i + j + k)*G3;
  f64 X0 = i - t; // Unskew the cell origin back to (x,y,z) space
  f64 Y0 = j - t;
  f64 Z0 = k - t;
  f64 x0 = x - X0; // The x,y,z distances from the cell origin
  f64 y0 = y - Y0;
  f64 z0 = z - Z0;

  // For the 3D case, the simplex shape is a slightly irregular tetrahedron.
  // Determine which simplex we are in.
  s32 i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
  s32 i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords

  if(x0 >= y0)
  {
    if(y0 >= z0)
    {// X Y Z order
      i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 1; k2 = 0;
    }
    else if(x0 >= z0)
    {// X Z Y order
      i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 0; k2 = 1;
    }
    else
    { // Z X Y order 
      i1 = 0; j1 = 0; k1 = 1; i2 = 1; j2 = 0; k2 = 1;
    }
  }
  else
  { // x0<y0
    if(y0 < z0)
    {// Z Y X order
      i1 = 0; j1 = 0; k1 = 1; i2 = 0; j2 = 1; k2 = 1;
    }
    else if(x0 < z0)
    {// Y Z X order
      i1 = 0; j1 = 1; k1 = 0; i2 = 0; j2 = 1; k2 = 1;
    }
    else
    {// Y X Z order
      i1 = 0; j1 = 1; k1 = 0; i2 = 1; j2 = 1; k2 = 0;
    }
  }

  // A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
  // a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
  // a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
  // c = 1/6.
  f64 x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
  f64 y1 = y0 - j1 + G3;
  f64 z1 = z0 - k1 + G3;
  f64 x2 = x0 - i2 + 2.0*G3; // Offsets for third corner in (x,y,z) coords
  f64 y2 = y0 - j2 + 2.0*G3;
  f64 z2 = z0 - k2 + 2.0*G3;
  f64 x3 = x0 - 1.0 + 3.0*G3; // Offsets for last corner in (x,y,z) coords
  f64 y3 = y0 - 1.0 + 3.0*G3;
  f64 z3 = z0 - 1.0 + 3.0*G3;

  // Work out the hashed gradient indices of the four simplex corners
  s32 ii = i & 255;
  s32 jj = j & 255;
  s32 kk = k & 255;
  s32 gi0 = perm[ii + perm[jj + perm[kk]]] % 12;
  s32 gi1 = perm[ii + i1 + perm[jj + j1 + perm[kk + k1]]] % 12;
  s32 gi2 = perm[ii + i2 + perm[jj + j2 + perm[kk + k2]]] % 12;
  s32 gi3 = perm[ii + 1 + perm[jj + 1 + perm[kk + 1]]] % 12;

  // Calculate the contribution from the four corners
  f64 t0 = 0.6 - x0*x0 - y0*y0 - z0*z0;
  if(t0 < 0)
    n0 = 0.0;
  else
  {
    t0 *= t0;
    n0 = t0 * t0 * Dot(grad3[gi0], x0, y0, z0);
  }

  f64 t1 = 0.6 - x1*x1 - y1*y1 - z1*z1;
  if(t1 < 0)
    n1 = 0.0;
  else
  {
    t1 *= t1;
    n1 = t1 * t1 * Dot(grad3[gi1], x1, y1, z1);
  }

  f64 t2 = 0.6 - x2*x2 - y2*y2 - z2*z2;
  if(t2 < 0)
    n2 = 0.0;
  else
  {
    t2 *= t2;
    n2 = t2 * t2 * Dot(grad3[gi2], x2, y2, z2);
  }

  f64 t3 = 0.6 - x3*x3 - y3*y3 - z3*z3;
  if(t3 < 0)
    n3 = 0.0;
  else
  {
    t3 *= t3;
    n3 = t3 * t3 * Dot(grad3[gi3], x3, y3, z3);
  }

  // Add contributions from each corner to get the final noise value.
  // The result is scaled to stay just inside [-1,1]
  return 32.0*(n0 + n1 + n2 + n3);
}


// 4D raw Simplex noise
f64 SimplexNoise::Get(f64 x, f64 y, f64 z, f64 w) {
  // The skewing and unskewing factors are hairy again for the 4D case
  f64 F4 = (sqrtf(5.0) - 1.0) / 4.0;
  f64 G4 = (5.0 - sqrtf(5.0)) / 20.0;
  f64 n0, n1, n2, n3, n4; // Noise contributions from the five corners

  // Skew the (x,y,z,w) space to determine which cell of 24 simplices we're in
  f64 s = (x + y + z + w) * F4; // Factor for 4D skewing
  s32 i = fastfloor(x + s);
  s32 j = fastfloor(y + s);
  s32 k = fastfloor(z + s);
  s32 l = fastfloor(w + s);
  f64 t = (i + j + k + l) * G4; // Factor for 4D unskewing
  f64 X0 = i - t; // Unskew the cell origin back to (x,y,z,w) space
  f64 Y0 = j - t;
  f64 Z0 = k - t;
  f64 W0 = l - t;

  f64 x0 = x - X0; // The x,y,z,w distances from the cell origin
  f64 y0 = y - Y0;
  f64 z0 = z - Z0;
  f64 w0 = w - W0;

  // For the 4D case, the simplex is a 4D shape I won't even try to describe.
  // To find out which of the 24 possible simplices we're in, we need to
  // determine the magnitude ordering of x0, y0, z0 and w0.
  // The method below is a good way of finding the ordering of x,y,z,w and
  // then find the correct traversal order for the simplex we're in.
  // First, six pair-wise comparisons are performed between each possible pair
  // of the four coordinates, and the results are used to add up binary bits
  // for an s32eger index.
  s32 c1 = (x0 > y0) ? 32 : 0;
  s32 c2 = (x0 > z0) ? 16 : 0;
  s32 c3 = (y0 > z0) ? 8 : 0;
  s32 c4 = (x0 > w0) ? 4 : 0;
  s32 c5 = (y0 > w0) ? 2 : 0;
  s32 c6 = (z0 > w0) ? 1 : 0;
  s32 c = c1 + c2 + c3 + c4 + c5 + c6;

  s32 i1, j1, k1, l1; // The s32eger offsets for the second simplex corner
  s32 i2, j2, k2, l2; // The s32eger offsets for the third simplex corner
  s32 i3, j3, k3, l3; // The s32eger offsets for the fourth simplex corner

  // simplex[c] is a 4-vector with the numbers 0, 1, 2 and 3 in some order.
  // Many values of c will never occur, since e.g. x>y>z>w makes x<z, y<w and x<w
  // impossible. Only the 24 indices which have non-zero entries make any sense.
  // We use a thresholding to set the coordinates in turn from the largest magnitude.
  // The number 3 in the "simplex" array is at the position of the largest coordinate.
  i1 = simplex[c][0] >= 3 ? 1 : 0;
  j1 = simplex[c][1] >= 3 ? 1 : 0;
  k1 = simplex[c][2] >= 3 ? 1 : 0;
  l1 = simplex[c][3] >= 3 ? 1 : 0;
  // The number 2 in the "simplex" array is at the second largest coordinate.
  i2 = simplex[c][0] >= 2 ? 1 : 0;
  j2 = simplex[c][1] >= 2 ? 1 : 0;
  k2 = simplex[c][2] >= 2 ? 1 : 0;
  l2 = simplex[c][3] >= 2 ? 1 : 0;
  // The number 1 in the "simplex" array is at the second smallest coordinate.
  i3 = simplex[c][0] >= 1 ? 1 : 0;
  j3 = simplex[c][1] >= 1 ? 1 : 0;
  k3 = simplex[c][2] >= 1 ? 1 : 0;
  l3 = simplex[c][3] >= 1 ? 1 : 0;
  // The fifth corner has all coordinate offsets = 1, so no need to look that up.

  f64 x1 = x0 - i1 + G4; // Offsets for second corner in (x,y,z,w) coords
  f64 y1 = y0 - j1 + G4;
  f64 z1 = z0 - k1 + G4;
  f64 w1 = w0 - l1 + G4;
  f64 x2 = x0 - i2 + 2.0*G4; // Offsets for third corner in (x,y,z,w) coords
  f64 y2 = y0 - j2 + 2.0*G4;
  f64 z2 = z0 - k2 + 2.0*G4;
  f64 w2 = w0 - l2 + 2.0*G4;
  f64 x3 = x0 - i3 + 3.0*G4; // Offsets for fourth corner in (x,y,z,w) coords
  f64 y3 = y0 - j3 + 3.0*G4;
  f64 z3 = z0 - k3 + 3.0*G4;
  f64 w3 = w0 - l3 + 3.0*G4;
  f64 x4 = x0 - 1.0 + 4.0*G4; // Offsets for last corner in (x,y,z,w) coords
  f64 y4 = y0 - 1.0 + 4.0*G4;
  f64 z4 = z0 - 1.0 + 4.0*G4;
  f64 w4 = w0 - 1.0 + 4.0*G4;

  // Work out the hashed gradient indices of the five simplex corners
  s32 ii = i & 255;
  s32 jj = j & 255;
  s32 kk = k & 255;
  s32 ll = l & 255;
  s32 gi0 = perm[ii + perm[jj + perm[kk + perm[ll]]]] % 32;
  s32 gi1 = perm[ii + i1 + perm[jj + j1 + perm[kk + k1 + perm[ll + l1]]]] % 32;
  s32 gi2 = perm[ii + i2 + perm[jj + j2 + perm[kk + k2 + perm[ll + l2]]]] % 32;
  s32 gi3 = perm[ii + i3 + perm[jj + j3 + perm[kk + k3 + perm[ll + l3]]]] % 32;
  s32 gi4 = perm[ii + 1 + perm[jj + 1 + perm[kk + 1 + perm[ll + 1]]]] % 32;

  // Calculate the contribution from the five corners
  f64 t0 = 0.6 - x0*x0 - y0*y0 - z0*z0 - w0*w0;
  if(t0 < 0)
    n0 = 0.0;
  else
  {
    t0 *= t0;
    n0 = t0 * t0 * Dot(grad4[gi0], x0, y0, z0, w0);
  }

  f64 t1 = 0.6 - x1*x1 - y1*y1 - z1*z1 - w1*w1;
  if(t1 < 0)
    n1 = 0.0;
  else
  {
    t1 *= t1;
    n1 = t1 * t1 * Dot(grad4[gi1], x1, y1, z1, w1);
  }

  f64 t2 = 0.6 - x2*x2 - y2*y2 - z2*z2 - w2*w2;
  if(t2 < 0)
    n2 = 0.0;
  else
  {
    t2 *= t2;
    n2 = t2 * t2 * Dot(grad4[gi2], x2, y2, z2, w2);
  }

  f64 t3 = 0.6 - x3*x3 - y3*y3 - z3*z3 - w3*w3;
  if(t3 < 0)
    n3 = 0.0;
  else
  {
    t3 *= t3;
    n3 = t3 * t3 * Dot(grad4[gi3], x3, y3, z3, w3);
  }

  f64 t4 = 0.6 - x4*x4 - y4*y4 - z4*z4 - w4*w4;
  if(t4 < 0)
    n4 = 0.0;
  else
  {
    t4 *= t4;
    n4 = t4 * t4 * Dot(grad4[gi4], x4, y4, z4, w4);
  }

  // Sum up and scale the result to cover the range [-1,1]
  return 27.0 * (n0 + n1 + n2 + n3 + n4);
}
