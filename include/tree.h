#ifndef __TREE_H__
#define __TREE_H__

template <class TNodeType> class CNode 
{
protected:
	TNodeType Node;
	CNode <TNodeType> *Left, *Right;
public:
	CNode(){Left=NULL;Right=NULL;}
	CNode(const TNodeType &N) {Node=N;Left=NULL;Right=NULL;}
	~CNode() {if (Left!=NULL) delete Left;if (Right!=NULL) delete Right;}
	void Set_Node(const TNodeType &N) {Node=N;}
	TNodeType Get_Node(void) {return Node;}
	CNode <TNodeType> * Get_Left(void) {return Left;}
	CNode <TNodeType> * Get_Right(void) {return Right;}
	void Alloc_Left(const TNodeType &N=TNodeType()){Left = new CNode <TNodeType> (N);}
	void Alloc_Right(const TNodeType &N=TNodeType()){Right = new CNode <TNodeType> (N);}

};

template <class TNodeType> class CTree 
{
protected:
	CNode <TNodeType> * Root;
public:
	//CTree(){Root=NULL;}
	CTree(const TNodeType &N=TNodeType()){Root = new CNode <TNodeType> (N);}
	
};

class CNode_Interval_3D : public CNode<CInterval_3D> 
{
public:
	void Set_Node(long double,long double,long double,long double,long double,long double);

};

class CTree_Interval_3D : public CTree<CInterval_3D> 
{
public:
	CNode <CInterval_3D>* Get_Root(void);
	CNode <CInterval_3D> Get_Root_Value(void);
	void Set_Root (CNode <CInterval_3D>* INode);
	void Set_Root (CNode <CInterval_3D> INode);
	void Set_Root (long double,long double,long double,long double,long double,long double);
friend class CList_BLob;
};



#endif /* __TREE_H__ */