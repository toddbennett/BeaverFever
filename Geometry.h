//This will be all of the stuff regarding meshes, including types, functions, objects, and anything else
//We may decide to split it up more later

//MESH CONSTRUCTION OUTLINE
//Every mesh starts as a tlmesh. tlmesh is the reciever type from the parser
//tlmesh has no methods and there will never be more than one tlmesh for any given mesh file
//tlmeshes are never ever altered in code
//They are kept as a base to prevent loss of integrity from repeated operations and floating point cutoffs

//tlmeshinst is an instantiation of a given mesh
//it points to a tlmesh and stores data for translations, scales and rotations on it
//if we choose to make it an object, we can have a draw method that preps it for the vertex buffer 


//colour codes
#define c_white D3DCOLOR_XRGB(255,255,255)
#define c_black D3DCOLOR_XRGB(0,0,0)
#define c_red D3DCOLOR_XRGB(255,0,0)
#define c_green D3DCOLOR_XRGB(0,255,0)
#define c_blue D3DCOLOR_XRGB(0,0,255)
#define c_cyan D3DCOLOR_XRGB(0,255,255)
#define c_yellow D3DCOLOR_XRGB(255,255,0)
#define c_purple D3DCOLOR_XRGB(255,0,255)

struct CUSTOMVERTEX //This is the type we set up structured the same way as we defined in CUSTOMFVF
//a vertex must be passed to the vertex buffer in this format
{
float x,y,z,rhw;
DWORD color;
};

struct tlmesh //a triangle-list mesh
	//this holds all the data of a mesh, but has none of the methods or anything
	//it is the first step and recieves it's information from the parser
{
	CUSTOMVERTEX *points; //an array of the points in the mesh
	int *x, *y, *z; //all of these are n by 3 arrays. the first number represents which triangle we are talking about  

//It is important to note that these are not absolute coordinates, but origin-centred coordinates.
//Every object will have an "origin point", which is generally centre mass along the floor, which is defined locally as 0,0,0
//Every other point is defined away from this point
};

struct tlmeshinst //an instantiation of tlmesh. one of these is attached to every object that gets drawn
//this might be better as an object 
{
	tlmesh *base; //this is a pointer to what the mesh of the object is. 
	//never edit anything in base ever. Bad things will happen to you
float scaleX,scaleY,scaleZ; //scale values. unlike rotations and transforms, scales initialize to 1.0f, not 0.0f
float rotX,rotY,rotZ; //rotation values. I dunno if you have a convention you like but I prefer percentage of a half turn. 0.0f is no change, 1.0f is a 180 degree turn
float x,y,z; //These are the coordinates of the origin of the object in 3d space. they are used for translations
//remember that order is always scale then rotate then translate.
};

CUSTOMVERTEX draw(
	tlmesh *points, //pointer to the base tlmesh we are working on 
	float sx, float sy, float sz, float rx, float ry, float rz, float x, float y, float z,
	int size //how big the array needs to be so we can initialize it properly
	)
{
	//performs transforms and returns an array of CUSTOMVVERTEX for the vertex buffer
}

struct Cube //this is how tlmesh should work when I figure out
	//it is a one-use object and will be deleted once everything is set up
{
CUSTOMVERTEX points[8];  //points in the cube
int x[12][3],y[12][3],z[12][3];        //integer arrays that represent the triangles in the mesh
//1st value is which triangle, 2nd is which point. the actual value in the array is the index of a vertex in points

};