
#include <vector>
#include <stdio.h>
#include <string>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <sys/times.h>
#include  "helper.h"

using namespace std;


#define GRAPH_DUMP 
//#define TOPO_DUMP
//#define REDUCTION_DEBUG
#define CHECK_CYCLE


#define SHOW_PROCESS
#define TIME_PROFILE

#define PRE_NIL -1
#define MIN_INFINITE ((int)0x80000000)


//#define FLOYD_WARSHALL
#ifndef FLOYD_WARSHALL
#define JOHNSON
#endif


#ifdef TIME_PROFILE
#define TIME_PROFILE_START { \
	struct tms __start; \
	times(&__start);
#define TIME_PROFILE_END \
	struct tms __end; \
	double __tps = sysconf(_SC_CLK_TCK); \
	times(&__end); \
	std::cout << "sys: " << (__end.tms_stime - __start.tms_stime) / __tps << std::endl; \
	std::cout << "usr: " << (__end.tms_utime - __start.tms_utime) / __tps << std::endl; \
}
#else
#define TIME_PROFILE_START
#define TIME_PROFILE_END
#endif


void FileReader::prepare()
{
	struct stat stat;
	Bp_Shdr *shdr;
	int j;
	int fd;
	
	fd = open(_name.c_str(), O_RDWR);
	if (fd < 0){
		perror("open");
		throw int();
	}
	
	if (fstat(fd, &stat) < 0){
		perror("stat");
		throw int();
	}

	_base = reinterpret_cast<int>(mmap(0, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,
				fd, 0));
	if (-1 == _base){
		perror("mmap");
		throw int();
	}

	if (close(fd) < 0){
		perror("close");
		throw int();
	}
	
	shdr = reinterpret_cast<Bp_Shdr *>(_base + 
		reinterpret_cast<Bp_Bhdr *>(_base)->b_shoff);

	
	_size = sizeof(Bp_Bhdr);
	_size += sizeof(*shdr) * BPS_SECTION_NUM;
	
	for (j = BPS_DEPENDENCE; j < BPS_SECTION_NUM; j++){
		_size += shdr[j].sh_size;
	}

	if (stat.st_size != _size){
		fprintf(stderr, "file size: %d, cal size: %d, NOT match\n", (int)stat.st_size, _size);
		throw int();
	}
}

void FileReader::finalize()
{
	if (munmap(reinterpret_cast<void *>(_base), _size) < 0){
		perror("munmap");
		throw int();
	}
}

void FileReader::FileDump()
{
	Bp_Bhdr *bhdr;
	Bp_Shdr *shdr;
	Dependence *pd;	
	Gettimeofday *gt;
	Environ *env;
	FutexRecord *ft;
	int i, j;


	bhdr = reinterpret_cast<Bp_Bhdr *>(_base);
	shdr = reinterpret_cast<Bp_Shdr *>(_base + bhdr->b_shoff);

	
	printf("bp file header: (b_shoff, b_shnum, b_shentsize) = (%d, %d, %d)\n", 
				bhdr->b_shoff, bhdr->b_shnum, bhdr->b_shentsize);
	printf("bp section header:\n");
	for (i = BPS_DEPENDENCE; i < BPS_SECTION_NUM; i++){
		printf("\t%d: (sh_offset, sh_size, sh_entsize, sh_hsize) = (%d, %d, %d, %d)\n", 
					i, shdr[i].sh_offset, shdr[i].sh_size, shdr[i].sh_entsize, 
					shdr[i].sh_hsize);
	}

	printf("\n*********************\n\nDetails:\n\n");

	for (j = BPS_DEPENDENCE; j < BPS_SECTION_NUM; j++){
		if (BPS_DEPENDENCE == j){
			pd = reinterpret_cast<Dependence *>(_base + shdr[j].sh_offset);
			printf("entry size: %d, entry number: %d\n*****\n", sizeof(Dependence), 
						shdr[j].sh_size / shdr[j].sh_entsize);

			for (i = 0; i < shdr[j].sh_size / shdr[j].sh_entsize; i++){
				printf("%2d:%#8x:%#8llx->%2d:%#8x:%#8llx\n", pd[i].dep[0].tid, 
							pd[i].dep[0].pc, pd[i].dep[0].ic, pd[i].dep[1].tid,
							pd[i].dep[1].pc, pd[i].dep[1].ic);
			}
		}else if (BPS_GETTIMEOFDAY == j){
			gt = reinterpret_cast<Gettimeofday *>(_base + shdr[j].sh_offset);	
			printf("entry size: %d, entry number: %d\n*****\n", sizeof(Gettimeofday), 
						shdr[j].sh_size / shdr[j].sh_entsize);
			for (i = 0; i < shdr[j].sh_size / shdr[j].sh_entsize; i++){
				printf("%#llx:(%#x:%#x):(%#x:%#x):%d\n", gt[i].ic, 
							(int)gt[i].tv.tv_sec, (int)gt[i].tv.tv_usec, 
							gt[i].tz.tz_minuteswest, gt[i].tz.tz_dsttime, 
							gt[i].tid);
			}
		}else if (BPS_ENVIRON == j){
			env = reinterpret_cast<Environ *>(_base + shdr[j].sh_offset);
			printf("entry size: %d, entry number: %d\n*****\n", sizeof(Environ), 
						shdr[j].sh_hsize / shdr[j].sh_entsize);
			for (i = 0; i < shdr[j].sh_hsize / shdr[j].sh_entsize; i++){
				printf("%s\n", (_base + env[i].ev));
			}
		}else if (BPS_FUTEX == j){
			ft = reinterpret_cast<FutexRecord *>(_base + shdr[j].sh_offset);
			printf("entry size: %d, entry number: %d\n*****\n", sizeof(FutexRecord), 
						shdr[j].sh_size / shdr[j].sh_entsize);
			for (i = 0; i < shdr[j].sh_size / shdr[j].sh_entsize; i++){
				printf("%d\n", ft[i].ret);
			}
		}
	}

	
}

void FileReader::ConstructDepGraph(GraphBuilder * builder)
{
	Dependence *pd = GetDep();
	int dep_num = GetDepNum();
	SignalHandle sig_int(SIGINT, SignalHandle::SIGINT_handler);
	

	TIME_PROFILE_START;
	cout << "construct dependence graph: \033[s";
	
	for (int i = 0; i < dep_num; i++){
#ifdef SHOW_PROCESS	
		if (!(i & ((1 << 7) - 1)) || (dep_num - 1 == i)){
			cout << "\033[u\033[?25l\033[K" << (i +1 ) * 100.0 / dep_num
				<< "%\t" << "[" << i + 1 << "/" << dep_num << "]";
			cout.flush();
		}
#endif
		builder->NewArc(builder->NewVertex(&pd[i].dep[TAIL]), 
			builder->NewVertex(&pd[i].dep[HEAD]));
	}	
	cout << "\033[?25h\033[0m" << endl;
	TIME_PROFILE_END;
}
void FileReader::backup()
{
	stringstream ss;
	string cmd = "cp " + _name + " " + _name + ".bak";

	ss << getpid();
	cmd += ss.str();
	
	/*backup*/
	if (system(cmd.c_str()) < 0){
		perror("system");
		throw int();
	}

}

void FileReader::doModify(vector<Dependence> &dep_new, int offset)
{
	Bp_Shdr *shdr;
	Dependence *pd;
	int move_size = 0;

	shdr = reinterpret_cast<Bp_Shdr *>(_base + 
			reinterpret_cast<Bp_Bhdr *>(_base)->b_shoff);

	/*modify section header*/
	shdr[BPS_DEPENDENCE].sh_size += offset;
	for (int i = BPS_DEPENDENCE + 1; i < BPS_SECTION_NUM; i++){
		/*special section*/
		if (BPS_ENVIRON == i){
			Environ *env = reinterpret_cast<Environ *>(_base + shdr[i].sh_offset);
			for (int j = 0; j < shdr[i].sh_hsize / shdr[i].sh_entsize; j++, env++){
				env->ev += offset;
			}
		}
		shdr[i].sh_offset += offset;
		move_size += shdr[i].sh_size;
	}


	pd = reinterpret_cast<Dependence *>(_base + shdr[BPS_DEPENDENCE].sh_offset);

	for (vector<Dependence>::iterator it = dep_new.begin(); dep_new.end() != it; 
		it++, pd++){
		*pd = *it;
	}
	
	memmove(pd, reinterpret_cast<char *>(pd) - offset, move_size);

	if (truncate(_name.c_str(), _size + offset) < 0){
		perror("truncate");
		throw int();
	}
	
}

void FileReader::Modify(std::vector<VerNode *> &vertices, 
	Matrix<int> &matrix, const int left_num)
{
	int offset = (left_num - GetDepNum()) * sizeof(Dependence);
	vector<Dependence> dep_new;

	/*we only do reducting*/
	assert(offset <= 0);

	assert(matrix.GetSize() == vertices.size());

	if (0 == offset){
		/*nothing need to do*/
		return;
	}

	this->backup();

	for (unsigned int i = 0; i < matrix.GetSize(); i++){
		for (unsigned int j = 0; j < matrix.GetSize(); j++){
			if (MIN_INFINITE != matrix[i][j]){
				dep_new.push_back(Dependence(*vertices[i]->GetKey(), 
					*vertices[j]->GetKey()));
			}
		}
	}

	this->doModify(dep_new, offset);
	
}

int FileReader::Modify(ALGraph &graph)
{
	vector<Dependence> dep_new;
	int offset;
	

	for (vector<VerNode *>::iterator it = graph.GetVertices().begin(); 
		graph.GetVertices().end() != it; it++){
		for (vector<ArcNode *>::iterator it2 = (*it)->GetArcs().begin();
			(*it)->GetArcs().end() != it2; it2++){
			if ((*it2)->GetInfo().GetMark()){
				dep_new.push_back(Dependence(*(*it)->GetKey(), 
					*(*it2)->GetVertex()->GetKey()));
			}
		}
	}

	offset = (dep_new.size() - graph.GetArcNum()) * sizeof(Dependence);

	if (0 == offset){
		return dep_new.size();
	}else if (offset > 0){
		/*increase dependences*/
		throw int();
	}

	this->backup();

	this->doModify(dep_new, offset);

	return dep_new.size();
	
}


void ALGraph::CheckCycle()
{
	this->GraphDump();
	this->DFS();
}

void ALGraph::TransitiveReduction(FileReader &fr)
{
	AllLongestPath();
	doTR(fr);
}

void ALGraph::AllLongestPath()
{	
#ifdef FLOYD_WARSHALL	
	int tmp;
	Matrix<int> *longest_path, *predecessor;
	int ver_num = GetVertexNum();

	cout << "vertices: " << ver_num << ", arcs: " << GetArcNum() 
		<< ", memory need about: " << sizeof(int) * ver_num * ver_num 
		<< " Bytes * 3"<< endl;

	if (sizeof(int) * ver_num * ver_num >= (1 << 29)){
		cerr << "out of memory" << endl;
		throw int();
	}

	if (NULL == _info.GetArcLen()){
		_info.GetArcLen() = new Matrix<int>(GetVertexNum());
		assert(_info.GetArcLen());
	}
	if (NULL == _info.GetPred()){
		_info.GetPred() = new Matrix<int>(GetVertexNum());
		assert(_info.GetPred());
	}


	longest_path = _info.GetArcLen();
	predecessor = _info.GetPred();

	/*init predecessor matrix*/
	for (int i = 0; i < ver_num; i++){
		for (int j = 0; j < ver_num; j++){
			(*longest_path)[i][j] = MIN_INFINITE;
			(*predecessor)[i][j] = PRE_NIL;
		}
	}

	/*init longest path matrix and predecessor matrix*/
	for (int i = 0; i < ver_num; i++){
		for (int j = 0; j < ver_num; j++){
			for (std::vector<ArcNode *>::iterator it = _vertices[i]->GetArcs().begin(); 
				_vertices[i]->GetArcs().end() != it; it++){
				if (*_vertices[j] == *(*it)->GetVertex()){
					(*longest_path)[i][j] = 1;
					(*predecessor)[i][j] = i;
					break;
				}
			}
		}
	}

	TIME_PROFILE_START;
	cout << "compute all longest path: \033[s";
	for (int k = 0; k < ver_num; k++){
#ifdef SHOW_PROCESS	
		cout << "\033[u\033[?25l\033[K" << (k +1 ) * 100.0 / ver_num
			<< "%\t" << "[" << k + 1 << "/" << ver_num << "]";
		cout.flush();
#endif
		for (int i = 0; i < ver_num; i++){
			for (int j = 0; j < ver_num; j++){
				if (MIN_INFINITE != (*longest_path)[i][k] && MIN_INFINITE != (*longest_path)[k][j]){
					tmp = (*longest_path)[i][k] + (*longest_path)[k][j];
					if ((*longest_path)[i][j] < tmp){
						(*longest_path)[i][j] = tmp;
						(*predecessor)[i][j] = (*predecessor)[k][j];
					}
				}
			}
		}
	}
	cout << "\033[?25h\033[0m" << endl;
	TIME_PROFILE_END;
#elif defined(JOHNSON)
	VerNode *u, *v;
	vector<ArcNode *>::iterator arc;
	int i;

	cout << "vertices: " << GetVertexNum() << ", arcs: " << GetArcNum() << endl;

	this->TopologicalSort();
	i = 1;
	
	TIME_PROFILE_START;
	cout << "compute all longest path: \033[s";
	for (vector<VerNode *>::iterator it = _vertices.begin(); 
		_vertices.end() != it; it++, i++){
#ifdef SHOW_PROCESS	
		cout << "\033[u\033[?25l\033[K" << i * 100.0 / GetVertexNum()
			<< "%\t" << "[" << i << "/" << GetVertexNum() << "]";
		cout.flush();
#endif		
		this->initializeSingleSource(*it);
		for (vector<VerNode *>::iterator it = _vertices.begin(); _vertices.end() != it; it++){
			for (vector<ArcNode *>::iterator it2 = (*it)->GetArcs().begin();
				(*it)->GetArcs().end() != it2; it2++){
				relax((*it), (*it2)->GetVertex());
			}
		}
		/*mark arcs*/
		for (vector<VerNode *>::iterator it = _vertices.begin(); _vertices.end() != it; it++){
			for (v = (*it), u = v->GetInfo().GetPI(); NULL != u; 
				v = u, u = v->GetInfo().GetPI()){
				arc = std::find_if(u->GetArcs().begin(), u->GetArcs().end(), ArcEqualSameTail(v));
				assert(u->GetArcs().end() != arc);
				(*arc)->GetInfo().GetMark() = true;
			}
		}
		
	}
	cout << "\033[?25h\033[0m" << endl;
	TIME_PROFILE_END;
#else
#error "You have not defined which algorithm to be used to compute all longest path of an graph"
#endif
}

void ALGraph::GraphDump()
{
#ifdef GRAPH_DUMP
#define DUMP_DETAIL_THRESHOLD 0x7fffffff
//#define DUMP_DETAIL_THRESHOLD 0
	if (_vertices.size() > DUMP_DETAIL_THRESHOLD){
		for (std::vector<VerNode *>::iterator it = _vertices.begin(); _vertices.end() != it; it++){
			printf("%p[%d]: ", (*it)->GetKey(), (*it)->GetDegree());
			for (std::vector<ArcNode *>::iterator it2 = (*it)->GetArcs().begin(); 
				(*it)->GetArcs().end() != it2; it2++){
				printf("%p->", (*it2)->GetVertex()->GetKey());
			}
			printf("\n");
		}
	}else{
		for (std::vector<VerNode *>::iterator it = _vertices.begin(); _vertices.end() != it; it++){
			printf("%d:%#x:%#llx[%d]: ", (*it)->GetKey()->tid, (*it)->GetKey()->pc, 
				(*it)->GetKey()->ic, (*it)->GetDegree());
			for (std::vector<ArcNode *>::iterator it2 = (*it)->GetArcs().begin(); 
				(*it)->GetArcs().end() != it2; it2++){
				printf("%d:%#x:%#llx->", (*it2)->GetVertex()->GetKey()->tid, 
					(*it2)->GetVertex()->GetKey()->pc, (*it2)->GetVertex()->GetKey()->ic);
			}
			printf("\n");
		}
	}
#ifdef DUMP_DETAIL_THRESHOLD
#undef DUMP_DETAIL_THRESHOLD
#endif
#endif	
}

void ALGraph::DFS()
{
	_info.GetTC() = 0;/*init time counter*/
	for (std::vector<VerNode *>::iterator it = _vertices.begin(); _vertices.end() != it; it++){
		if (WHITE == (*it)->GetInfo().GetColor()){
			dfsVisit(*it);
		}
	}
}

void ALGraph::dfsVisit(VerNode *v)
{
	v->GetInfo().GetColor() = GRAY;
	v->GetInfo().GetDT() = ++_info.GetTC();
	for (std::vector<ArcNode *>::iterator it = v->GetArcs().begin(); 
		v->GetArcs().end() != it; it++){
		if (WHITE == (*it)->GetVertex()->GetInfo().GetColor()){
			(*it)->GetVertex()->GetInfo().GetPI() = v;
			dfsVisit((*it)->GetVertex());
		}
#if 0//def CHECK_CYCLE
		else if (GRAY == it->GetVertex()->GetColor()){
			printf("\033[31m cycle[%d] found: ", ++cycle_num);
			pathDump(it->GetVertex(), v);
			printf("%2d:%#8x:%#8llx", it->GetVertex()->GetKey()->tid, 
				it->GetVertex()->GetKey()->pc, it->GetVertex()->GetKey()->ic);
			printf("\033[0m\n");
			throw int();
		}
#endif		
	}
	v->GetInfo().GetColor() = BLACK;
	v->GetInfo().GetFT() = ++_info.GetTC();
}
void ALGraph::pathDump(VerNode * u, VerNode * v)
{
	if (v->GetInfo().GetPI() == u){
		printf("%d:%#x:%#llx->", u->GetKey()->tid, u->GetKey()->pc, u->GetKey()->ic);
	}else{
		if (NULL == v->GetInfo().GetPI()){
			printf("no path from (%d:%#x:%#llx) to (%d:%#x:%#llx)\n", 
				u->GetKey()->tid, u->GetKey()->pc, u->GetKey()->ic, 
				v->GetKey()->tid, v->GetKey()->pc, v->GetKey()->ic);
			return;
		}
		pathDump(u, v->GetInfo().GetPI());
		printf("%d:%#x:%#llx->", v->GetKey()->tid, v->GetKey()->pc, v->GetKey()->ic);
	}
}

void ALGraph::doTR(FileReader &fr)
{
#ifdef FLOYD_WARSHALL	
	Matrix<int> *pre_tree;
	int arc_left = 0;
	int ver_num = GetVertexNum();

	if(NULL == _info.GetPreTree()){
		_info.GetPreTree() = new Matrix<int>(GetVertexNum());
		assert(_info.GetPreTree());
	}
	pre_tree = _info.GetPreTree();
	
	for (int i = 0; i < ver_num; i++){
		for (int j = 0; j < ver_num; j++){
			(*pre_tree)[i][j] = MIN_INFINITE;
		}
	}

#ifdef REDUCTION_DEBUG
	graphDump(*_info.GetArcLen());
	cout << endl << endl;
	graphDump(*_info.GetPred());
#endif

	for (int i = 0; i < ver_num; i++){
		for (int j = 0; j < ver_num; j++){
			if (PRE_NIL != (*_info.GetPred())[i][j]){
				for (int k = j; k != i; k = (*_info.GetPred())[i][k]){
					(*pre_tree)[(*_info.GetPred())[i][k]][k] = 1;
				}
			}
		}
	}

#ifdef REDUCTION_DEBUG
	cout << endl << endl;
	graphDump(*_info.GetPreTree());
#endif

	for (int i = 0; i < ver_num; i++){
		for (int j = 0; j < ver_num; j++){
			if (MIN_INFINITE != (*pre_tree)[i][j]){
				arc_left++;
			}
		}
	}

	fr.Modify(_vertices, *pre_tree, arc_left);

	cout << "vertices: " << ver_num << endl << "all arcs: " << GetArcNum() << endl
		<< "arcs left: " << arc_left << endl << "reduction: " << GetArcNum() - arc_left
		<< "\t[" << (GetArcNum() - arc_left) * 100.0 / GetArcNum() << "%]" << endl;
#elif defined(JOHNSON)
	int left = fr.Modify(*this);
	cout << "vertices: " << GetVertexNum() << endl << "all arcs: " << GetArcNum() << endl
		<< "arcs left: " << left << endl << "reduction: " << GetArcNum() - left
		<< "\t[" << (GetArcNum() - left) * 100.0 / GetArcNum() << "%]" << endl;
	
#else
#error "You have not defined which algorithm to be used to compute all longest path of an graph"
#endif
}

void ALGraph::TopologicalSort()
{

	this->DFS();
	
	std::stable_sort(_vertices.begin(), _vertices.end(), VerFTGTComp());

#ifdef TOPO_DUMP
	for (vector<VerNode *>::iterator it = _vertices.begin(); _vertices.end() != it; it++){
		cout << (*it)->GetInfo().GetFT() << "/" << (*it)->GetInfo().GetDT() 
			<< "->";
	}
	cout << endl;
#endif	
}



void ALGraph::pathDump(int i, int j, int **predecessor)
{
	if (i == j){
		printf("%d->", i);
	}else if (PRE_NIL == predecessor[i][j]){
		/*no path from i to j*/
		return;
	}else{
		pathDump(i, predecessor[i][j], predecessor);
		printf("%d->", j);
	}
}

template <typename T>
void ALGraph::graphDump(Matrix<T> &matrix)
{
	for (unsigned int i = 0; i < matrix.GetSize(); i++){
		for (unsigned int j = 0; j < matrix.GetSize(); j++){
			if (MIN_INFINITE != matrix[i][j] && 
				PRE_NIL != matrix[i][j]){
				cout << setw(3) << matrix[i][j];
			}else{
				cout << setw(3) << 0;
			}
		}
		cout << endl;
	}
}

void ALGraph::initializeSingleSource(VerNode *ver)
{
	for (vector<VerNode *>::iterator it = _vertices.begin(); _vertices.end() != it; it++){
		(*it)->GetInfo().GetDistance() = MIN_INFINITE;
		(*it)->GetInfo().GetPI() = NULL;
	}
	ver->GetInfo().GetDistance() = 0;
}
void ALGraph::relax(VerNode * u, VerNode * v)
{
	/*(u, v) must exist*/
	int t;
	if (MIN_INFINITE != u->GetInfo().GetDistance()){
		t = u->GetInfo().GetDistance() + 1;
		/*no matter whether d[v] is -infinite*/
		if (t > v->GetInfo().GetDistance()){
			v->GetInfo().GetDistance() = t;
			v->GetInfo().GetPI() = u;
		}
	}
}

