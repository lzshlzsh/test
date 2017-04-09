#ifndef __HELPER_H__
#define __HELPER_H__

#include <sys/time.h>
#include <unordered_map>
#include <assert.h>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <string.h>

typedef struct DepHalf{
	int tid;
	int pc;
	long long ic;
	
	bool operator == (const DepHalf &dh)
	{
		return (dh.tid == tid && dh.pc == pc && dh.ic == ic);
	}
}DepHalf;

enum {
	TAIL = 0, 
	HEAD,
};

typedef struct Dependence{
	DepHalf dep[2];
	Dependence(DepHalf &tail, DepHalf &head)
	{
		dep[TAIL] = tail;
		dep[HEAD] = head;
	}
}Dependence;


typedef struct Bp_Bhdr{
	int b_shoff; /*section header offset*/
	int b_shnum; /*section header number*/
	int b_shentsize; /*section header entry size*/
}Bp_Bhdr;

typedef struct Bp_Shdr{
	int sh_offset;
	int sh_size;
	int sh_entsize;
	int sh_hsize; /*for string table header*/
}Bp_Shdr;

enum {
	BPS_DEPENDENCE = 0,
	BPS_GETTIMEOFDAY,
	BPS_ENVIRON, 
	BPS_FUTEX,
	BPS_SECTION_NUM,
};

typedef struct Gettimeofday{
	long long ic;
	struct timeval tv;
	struct timezone tz;
	int tid;
}Gettimeofday;

typedef struct Environ{
		char *ev;
}Environ;

typedef struct FutexRecord{
		int ret;
}FutexRecord;

/***********************************/
class ArcNode;
class VerNode;
struct VerEq;
struct VerHash;

typedef DepHalf KeyType;
typedef std::unordered_map<VerNode *, int, VerHash, VerEq> VerHashMap;
	
enum VerColor{
	WHITE,
	GRAY,
	BLACK,
};


class ArcInfoType {
private:
	bool _marked;
public:
	ArcInfoType() : _marked(false){}

	bool &GetMark(){return _marked;}
};

class ArcNode{
private:
	VerNode *_pver;
	ArcInfoType _info;
private:
public:
public:
	ArcNode() : _pver(NULL){}
	ArcNode(VerNode *ver) : _pver(ver){} 
	VerNode *GetVertex() const{return _pver;}
	ArcInfoType &GetInfo() {return _info;}
};

class VerInfoType{
private:
	VerColor _color;
	VerNode *_pi;
	unsigned int _discover_time;
	unsigned int _finish_time;
	VerNode *_hash_next;

	int _distance;
private:
public:	
public:
	VerInfoType() : _color (WHITE), _pi(NULL), _discover_time(0), 
		_finish_time(0), _hash_next(NULL), _distance(0){}
	~VerInfoType(){}
	VerColor &GetColor() {return _color;}
	VerNode * &GetPI() {return _pi;}
	unsigned int &GetDT() {return _discover_time;}
	unsigned int &GetFT() {return _finish_time;}
	VerNode * &GetHashNext(){return _hash_next;}
	int &GetDistance(){return _distance;}

};

class VerNode{
private:
	KeyType *_key;
	std::vector<ArcNode *> _arcs;
	VerInfoType _info;
private:	
public:
	VerNode() : _key(NULL){}
	VerNode(KeyType *key) : _key(key){}
	~VerNode()
	{
		for (std::vector<ArcNode *>::iterator it = _arcs.begin(); _arcs.end() != it; it++){
			delete *it;
		}
		_arcs.clear();
	}
public:
	KeyType * &GetKey() {return _key;}
	std::vector<ArcNode *> &GetArcs() {return _arcs;}
	VerInfoType &GetInfo(){return _info;}
	int GetDegree(){return _arcs.size();}
	bool operator ()(const VerNode *ver) const
	{
		/*make VerNode as a function object*/
		return *ver->_key == *_key;
	}
	/*pointer compare: condition refinemented -- ver._key == _key*/
	bool operator == (const VerNode &ver){return *ver._key == *_key;}
	bool operator != (const VerNode &ver){return !(*this == ver);}

	VerNode *&HashNext(){return _info.GetHashNext();}
};


class VerFTGTComp 
{
public:
	VerFTGTComp(){}
	bool operator() (VerNode *ver1, VerNode *ver2) const
	{
		return ver1->GetInfo().GetFT() > ver2->GetInfo().GetFT();
	}
};

class ArcEqualSameTail
{
private:
	VerNode *_vertex;
public:
	ArcEqualSameTail(VerNode *ver) : _vertex(ver){}
	bool operator() (ArcNode *arc) const
	{
		/*comparing ptr is enough*/
		return arc->GetVertex() == _vertex;
	}
};
/********************************************************************/
class FileReader;
class Graph {
private:
private:
public:
	
public:	
	virtual ~Graph(){}
	virtual void CheckCycle() = 0;
	virtual void TransitiveReduction(FileReader &fr) = 0;
	virtual int GetVertexNum() = 0;
	virtual int GetArcNum() = 0;
	virtual void DFS() = 0;
	virtual void AllLongestPath() = 0;
	virtual VerNode *AddVertex(VerNode *ver) = 0;
	virtual ArcNode *AddArc(VerNode *u, VerNode *v) = 0;
	virtual void GraphDump() = 0;
	virtual void TopologicalSort() = 0;
};

template<class T>
class Matrix {
private:
	unsigned int _n;
	T **_matrix;
private:
	void buildMatrix();
	void destructMatrix();
public:	
public:
	Matrix(const int n) :  _n(n), _matrix(NULL) {buildMatrix();}
	~Matrix() 
	{
		destructMatrix();
	}
	T **GetMatrix(){return _matrix;}
	unsigned int GetSize(){return _n;}
	T *operator[] (const int i) const
	{
		return reinterpret_cast<T *>(reinterpret_cast<int>(_matrix) + i * _n * sizeof(T));
	}
};

template <int size>
class VerHashFunc
{
public:
	unsigned int operator() (VerNode *ver)const
	{
		assert(0 == (size & (size - 1)));
		return (ver->GetKey()->tid ^ ver->GetKey()->pc ^ ver->GetKey()->ic) 
			& (size - 1);
	}
};

template <typename T1, typename HashFunc, int size>
class SimpleChainHash {
private:
	T1 **_hash_table;
	HashFunc _hf;
private:
public:
	
public:
	explicit SimpleChainHash(const HashFunc &hf) : _hf(hf)
	{
		assert (0 == (size & (size - 1)));
		if (size * sizeof(T1 *) < static_cast<unsigned int>(sysconf(_SC_PAGESIZE))){
			_hash_table = new T1 *[size];
			memset(_hash_table, 0, sizeof(_hash_table[0]) * size);
		}else{
			_hash_table = reinterpret_cast<T1 **>(mmap(0, size * sizeof(T1 *), PROT_READ | PROT_WRITE, 
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
			if (reinterpret_cast<T1 **>(-1) == _hash_table){
				std::cout << "request memory: " << size * sizeof(T1 *) 
					<< " Bytes" << std::endl;
				perror("mmap");
				throw int();
			}
			std::cout << "hash mem alloc, mmap [" << _hash_table << ", "
				<< std::hex << reinterpret_cast<int>(_hash_table) + size * sizeof(T1 *) << "]"
				<< std::dec << std::endl;
		}
	}
	~SimpleChainHash()
	{
		if (size * sizeof(T1 *) < static_cast<unsigned int>(sysconf(_SC_PAGESIZE))){
			delete []_hash_table;
		}else{
			assert(0 == munmap(reinterpret_cast<void *>(_hash_table), size * sizeof(T1 *)));
		}
	}
	
	void Insert(T1 *e)
	{
		T1 **t = &_hash_table[_hf(e)];

		while (NULL != *t){
			t = &(*t)->HashNext();
		}
		*t = e;
	}

	T1 *Find(T1 *e)
	{
		T1 *t = _hash_table[_hf(e)];

		while (NULL != t && *e != *t){
			t = t->HashNext();
		}

		return t;
	}
};

class ALGInfoType {
private:
	unsigned int _time_counter;
	Matrix<int> *_arc_len;
	Matrix<int> *_pred;
	Matrix<int> *_pre_tree;
	static const int HASH_TABLE_SIZE = 0x1000;
	typedef SimpleChainHash<VerNode, VerHashFunc<HASH_TABLE_SIZE>, 
		HASH_TABLE_SIZE> VerHash;
	VerHash _vertex_hash;
private:	
public:
	ALGInfoType() : _time_counter(0), _arc_len(NULL), _pred(NULL), 
		_pre_tree(NULL), _vertex_hash(VerHashFunc<HASH_TABLE_SIZE>()){}
	~ALGInfoType()
	{
		if (_arc_len)
			delete _arc_len;
		if (_pred)
			delete _pred;
		if (_pre_tree)
			delete _pre_tree;
	}
	unsigned int &GetTC() {return _time_counter;}
	Matrix<int> * &GetArcLen() {return _arc_len;}
	Matrix<int> * &GetPred() {return _pred;}
	Matrix<int> * &GetPreTree() {return _pre_tree;}
	VerHash &GetVerHash(){return _vertex_hash;}
};


class ALGraph : public Graph{
private:
	int _arc_num;
	std::vector<VerNode *> _vertices;
	ALGInfoType _info;
private:
	VerNode *findVertex(VerNode *ver)
	{
#if 0
		std::vector<VerNode *>::iterator it;

		it = std::find_if(_vertices.begin(), _vertices.end(), *ver);
		if (_vertices.end() == it){
			return NULL;
		}
		return *it;
#else
		VerNode *find;
		if (!(find = _info.GetVerHash().Find(ver))){
			_info.GetVerHash().Insert(ver);
			return NULL;
		}
		return find;
#endif
	}
	void dfsVisit(VerNode *v);
	void pathDump(VerNode *u, VerNode *v);
	void doTR(FileReader &fr);
	template<typename T>
	void graphDump(Matrix<T> &matrix);
	void pathDump(int i, int j, int **predecessor);

	void initializeSingleSource(VerNode *ver);
	void relax(VerNode *u, VerNode *v);
	
public:
	
public:	
	ALGraph() : _arc_num(0){}
	virtual ~ALGraph()
	{
		for (std::vector<VerNode *>::iterator it = _vertices.begin(); _vertices.end() != it; it++){
			delete *it;
		}
		_vertices.clear();
	}
	virtual void CheckCycle();
	virtual void TransitiveReduction(FileReader &fr);
	virtual int GetVertexNum(){return static_cast<int>(_vertices.size());}
	virtual int GetArcNum(){return _arc_num;}
	virtual void DFS();
	virtual void AllLongestPath();
	virtual VerNode *AddVertex(VerNode *ver)
	{
		VerNode *v;
		if ( (v = findVertex(ver))){
			delete ver;
			return v;
		}
		_vertices.push_back(ver);
		return ver;
	}
	virtual ArcNode *AddArc(VerNode *u, VerNode *v)
	{
		u->GetArcs().push_back(new ArcNode(v));
		_arc_num++;
		return u->GetArcs().back();
	}

	virtual void GraphDump();

	virtual void TopologicalSort();

	std::vector<VerNode *> &GetVertices(){return _vertices;}

};


class GraphBuilder;

class FileReader{
private:
	int _size;
	int _base;
	std::string _name;
private:
	void prepare();
	void finalize();
	void backup();
	void doModify(std::vector<Dependence> &dep_new, int offset);
public:
	FileReader(const int argc, const char **argv) : _size(0), _base(0) 
	{
		if (2 != argc){
			fprintf(stderr, "Usage: argv[0] log_file\n");
			throw int();
		}
		_name = argv[1];
		prepare();
	}
	~FileReader(){finalize();}
	void FileDump();
	Dependence *GetDep()
	{
		Bp_Shdr *shdr = reinterpret_cast<Bp_Shdr *>(_base + 
			reinterpret_cast<Bp_Bhdr *>(_base)->b_shoff);
		return reinterpret_cast<Dependence *>(_base + shdr[BPS_DEPENDENCE].sh_offset);
	}
	int GetDepNum()
	{
		Bp_Shdr *shdr = reinterpret_cast<Bp_Shdr *>(_base + 
			reinterpret_cast<Bp_Bhdr *>(_base)->b_shoff);

		return shdr[BPS_DEPENDENCE].sh_size / shdr[BPS_DEPENDENCE].sh_entsize;
	}
	void ConstructDepGraph(GraphBuilder *builder);

	void Modify(std::vector<VerNode *> &vertices, 
		Matrix<int> &matrix, const int left_num);

	int Modify(ALGraph &graph);	
};


class GraphBuilder {
private:
private:
protected:
	Graph *_graph;
public:
public:	
	GraphBuilder() : _graph(NULL){}
	virtual ~GraphBuilder(){}
	VerNode *NewVertex(KeyType * key)
	{
		return _graph->AddVertex(new VerNode(key));
	}
	ArcNode *NewArc(VerNode *u, VerNode *v)
	{
		return _graph->AddArc(u, v);
	}
	Graph *GetGraph(){return _graph;}
};

class ALGraphBuilder : public GraphBuilder {
public:
	ALGraphBuilder() {_graph = new ALGraph(); assert(_graph);}
	~ALGraphBuilder() {delete _graph;}
};


template<class T>
void Matrix<T>::buildMatrix()
{
	if (_n * _n * sizeof(T) < static_cast<unsigned int>(sysconf(_SC_PAGESIZE))){
		_matrix = reinterpret_cast<T **>(new char [_n * _n * sizeof(T)]);
		assert(_matrix);
		memset(_matrix, 0, _n * _n * sizeof(T));
	}else{
		_matrix = reinterpret_cast<T **>(mmap(0, _n * _n * sizeof(T), PROT_READ | PROT_WRITE, 
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
		if (reinterpret_cast<T **>(-1) == _matrix){
			std::cout << "request memory: " << _n * _n * sizeof(T) 
				<< " Bytes, _n = " << _n << std::endl;
			perror("mmap");
			throw int();
		}
		std::cout << "matrix mem alloc, mmap [" << _matrix << ", "
			<< std::hex << reinterpret_cast<int>(_matrix) + _n * _n * sizeof(T) << "]"
			<< std::dec << std::endl;
	}
}

template<class T>
void Matrix<T>::destructMatrix()
{
	if (_n * _n * sizeof(T) < static_cast<unsigned int>(sysconf(_SC_PAGESIZE))){
		delete []_matrix;
	}else{
		assert(0 == munmap(reinterpret_cast<void *>(_matrix), _n * _n * sizeof(T)));
	}
}


class SignalHandle
{
private:
	typedef void (*SaSigAction)(int, siginfo_t *, void *);
public:
	SignalHandle(int signum, SaSigAction handler)
	{
		struct sigaction act;

		assert (signum > 0 && signum <= SIGRTMAX);

		if (sigfillset(&act.sa_mask) < 0){
			perror("sigfillset");
			throw int();
		}
		act.sa_flags = SA_SIGINFO;

		act.sa_sigaction = handler;

		if (sigaction(signum, &act, NULL) < 0){
			perror("sigaction");
			throw int();
		}
	}
	~SignalHandle(){}

	static void SIGINT_handler(int signum, siginfo_t *info, void *uc)
	{
		std::cout << "\033[?25h\033[0m" << std::endl;
		exit(SIGINT);
	}
};
#endif /*__HELPER_H__*/

