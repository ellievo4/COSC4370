/*	Thanh Vo _ 1148524
	COSC 4377
	Final Project
	ObjLoader.h
*/

// ----------------------------------------------------------
// include libraries
// ----------------------------------------------------------
#include "glut\glut.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#ifndef OBJLOADER_H
#define OBJLOADER_H

// ----------------------------------------------------------
// This struct contain 3 floats and a constructor, it's used for vertexes and normal vectors
// ----------------------------------------------------------
struct Coordinate {
	float x, y, z;
	Coordinate(float a, float b, float c);
};

// ----------------------------------------------------------
// This structure is store every property of a face
// ----------------------------------------------------------
struct Face {
	int facenum;    //the number of the face (it's start from 1 not 0, so if you use it as an index, subtract 1 from it), it's used for the normal vectors
	bool four;      //if true, than it's a quad else it's a triangle
	int faces[4];   //indexes for every vertex, which makes the face (it's start from 1 not 0, so if you use it as an index, subtract 1 from it)
	int texcoord[4];//indexes for every texture coorinate that is in the face (it's start from 1 not 0, so if you use it as an index, subtract 1 from it)
	int mat;		//the index for the material, which is used by the face
	Face(int facen, int f1, int f2, int f3, int t1, int t2, int t3, int m);					//constructor for triangle
	Face(int facen, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int m);  //constructor for quad
};

// ----------------------------------------------------------
// this is a structure, which contain one material
// ----------------------------------------------------------
struct Material {
	std::string name;       //the name of the material
	float alpha, ns, ni;    //some property, alpha, shininess, and some other, which we not used
	float dif[3], amb[3], spec[3];   //the color property (diffuse, ambient, specular)
	int illum;						//illum 
	int texture;					//the id for the texture, if there is no texture then -1
	//constructor
	Material(const char* na, float al, float n, float ni2, float* d, float* a, float* s, int i, int t);
};

// ----------------------------------------------------------
// texture coorinate (UV coordinate)
// ----------------------------------------------------------
struct Texcoord {
	float u, v;
	Texcoord(float a, float b);
};

// ----------------------------------------------------------
// the main class for the object loader
// ----------------------------------------------------------
class ObjLoader {
	std::vector<std::string*> coord;        //every line of code from the obj file
	std::vector<Coordinate*> vertex;        //all vertexes
	std::vector<Face*> faces;               //all faces
	std::vector<Coordinate*> normals;       //all normal vectors
	std::vector<unsigned int> texture;		//the id for all the textures (so I can delete the textures after use it)
	std::vector<unsigned int> lists;        //the id for all lists (so I can delete the lists after use it)
	std::vector<Material*> materials;       //all materials
	std::vector<Texcoord*> texturecoordinate;	//all texture coorinate (UV coordinate)
	bool ismaterial, isnormals, istexture;		//check for material, normals and texture
	unsigned int loadTexture(const char* filename); //private load texture function
	void clean();   //free all of the used memory

public:
	ObjLoader();	//constructor
	~ObjLoader();   //free the textures and lists
	int load(const char* filename); //the main model load function
};

#endif