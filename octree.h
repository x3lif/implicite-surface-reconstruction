#ifndef __OCTREE_H__
#define __OCTREE_H__

#include "voxel.h"

class CList_Octree_Node;

class COctree_Node
{
protected:
	unsigned char State;
	unsigned char Level;
	unsigned int Node_Id;
	bool IsLeaf;
	CVoxel_8 Voxel;
	COctree_Node * Father;
	COctree_Node * Sons[8];	
public:
	COctree_Node(void);
	~COctree_Node(void);
	COctree_Node(COctree_Node *,CVoxel_8,unsigned char,unsigned char);
	unsigned char Get_State(void);
	unsigned char Get_Level(void);
	CVoxel_8 Get_Voxel(void);
	COctree_Node * Get_From_Type(unsigned char);
	COctree_Node * Get_Son(unsigned char);
	COctree_Node * Get_Father(void);
	void Put_State(unsigned char);
	void Put_Level(unsigned char);
        void Compute_Octree_Cloud(QVector<QVector3D>&,unsigned char);
	void Compute_Octree_Voxellization(CVoxel_Tab VT,unsigned char Lmax, int i1, int i2, int j1, int j2, int k1, int k2);
	void Draw_Box(unsigned char);
	void Get_Leaves_Recursive(CList_Octree_Node &);
	void Delete_If_Empty_Sons(void);
friend class COctree;
friend class CList_Octree_Node;
};

class CListed_Octree_Node:public COctree_Node
{
protected:
	CListed_Octree_Node * Next;
public:
	CListed_Octree_Node(void);
	~CListed_Octree_Node(void);
	CListed_Octree_Node * Get_Next(void);
	void Put_Next(CListed_Octree_Node *);
friend class CList_Octree_Node;
friend class CList_BLob;
};

class CList_Octree_Node
{
protected:
        CListed_Octree_Node *First,*Last;
	int NBN;
public:
	CList_Octree_Node(void);
	int Get_NBN(void);
	void Add_Octree_Node(COctree_Node);
	void Draw(unsigned char);
	void Delete_List(void);
friend class CList_BLob;
};

class COctree
{
protected:
	COctree_Node *Root;
	unsigned char Level;
public:
	COctree(void);
	COctree(CVoxel_8);
	COctree_Node * Get_root(void);
        void Compute_Octree_Cloud(QVector<QVector3D>&,unsigned char);
	void Find_List_Leaves(CList_Octree_Node &);
	void Create_From_Voxellization(CVoxel_Tab);
	void Draw_Boxes(unsigned char);
	void Clear_Octree(void);
};


#endif /* __OCTREE_H__ */

