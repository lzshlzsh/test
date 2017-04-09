#include <iostream>
#include <memory>
#include <unistd.h>

using namespace std;

int main()
{
	cout << __cplusplus << endl;
#ifdef _GLIBCXX_USE_WCHAR_T
	cout << "_GLIBCXX_USE_WCHAR_T defined" << endl;
#else
	cout << "_GLIBCXX_USE_WCHAR_T \033[31mNOT\033[0m defined" << endl;
#endif	
#ifdef _GLIBCXX_CONSTEXPR
	cout << "_GLIBCXX_CONSTEXPR defined" << endl;
	_GLIBCXX_CONSTEXPR int a = 0;
	//a = 1;
	cout << a << endl;
#else
	cout << "_GLIBCXX_CONSTEXPR \033[31mNOT\033[0m defined" << endl;
#endif	
#ifdef __osf__
	cout << "__osf__ defined" << endl;
#else
	cout << "__osf__ \033[31mNOT\033[0m defined" << endl;
#endif	
#ifdef _REENTRANT
	cout << "_REENTRANT defined" << endl;
#else
	cout << "_REENTRANT \033[31mNOT\033[0m defined" << endl;
#endif	
	cout << "_GTHREAD_USE_MUTEX_TIMEDLOCK = " << _GTHREAD_USE_MUTEX_TIMEDLOCK << endl;
	cout << "_POSIX_TIMEOUTS = " << _POSIX_TIMEOUTS << endl;
#ifdef _GTHREAD_USE_MUTEX_INIT_FUNC
	cout << "_GTHREAD_USE_MUTEX_INIT_FUNC defined" << endl;
#else
	cout << "_GTHREAD_USE_MUTEX_INIT_FUNC \033[31mNOT\033[0m defined" << endl;
#endif	
#ifdef __GXX_WEAK__
	cout << "__GXX_WEAK__ defined" << endl;
#else
	cout << "__GXX_WEAK__ \033[31mNOT\033[0m defined" << endl;
#endif	
	cout << "_GLIBCXX_GTHREAD_USE_WEAK = " << _GLIBCXX_GTHREAD_USE_WEAK << endl;
#ifdef __BIONIC__
	cout << "__BIONIC__ defined" << endl;
#else
	cout << "__BIONIC__ \033[31mNOT\033[0m defined" << endl;
#endif	
#ifdef _LIBOBJC
	cout << "_LIBOBJC defined" << endl;
#else
	cout << "_LIBOBJC \033[31mNOT\033[0m defined" << endl;
#endif	
#ifdef _LIBOBJC_WEAK
	cout << "_LIBOBJC_WEAK defined" << endl;
#else
	cout << "_LIBOBJC_WEAK \033[31mNOT\033[0m defined" << endl;
#endif	
#ifdef __FreeBSD__
	cout << "__FreeBSD__ defined" << endl;
#else
	cout << "__FreeBSD__ \033[31mNOT\033[0m defined" << endl;
#endif	
#ifdef __sun
	cout << "__sun defined" << endl;
#else
	cout << "__sun \033[31mNOT\033[0m defined" << endl;
#endif	
#ifdef __svr4__
	cout << "__svr4__ defined" << endl;
#else
	cout << "__svr4__ \033[31mNOT\033[0m defined" << endl;
#endif	
	return 0;
}
