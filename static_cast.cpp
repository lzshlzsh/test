/**
 *	Created Time: 2009-09-10 16:51:16
 *	Last Modified: 2009-09-10 16:51:16
 *	File Name: static_cast.cpp
 *	Description: 
 */

class base {};
class derived : public base{
public:
	operator int() {return 1;}
};
void func(int){}
class other {};

int main(){
	int i = 0x7fff;
	long l; 
	float f;
	l = i;
	f = i;
	l = static_cast<long>(i);
	f = static_cast<float>(i);

	i = l;
	i = f;
	i = static_cast<int>(l);
	i = static_cast<int>(f);

	char c = static_cast<char>(i);

	void *vp = &i;
	float *fp = (float *)vp;
	fp = static_cast<float *>(vp);

	derived d;
	base *bp = &d;
	bp = static_cast<base *>(&d);

	int x = d;
	x = static_cast<int>(d);
	func(d);
	func(static_cast<int>(d));

	derived *dp = static_cast<derived *>(bp);
	 
	other *op2 = (other *)bp;
//	op2 = static_cast<other *>(bp); //ops
//	op2 = dynamic_cast<other *>(bp); //ops
//	op2 = const_cast<other *>(bp); //ops
	op2 = reinterpret_cast<other *>(bp);

	return 0;
}
