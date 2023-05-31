#include "string.h"

using namespace lmq;

void test1() {
	string s("abcdef");
	string::iterator it = s.begin();
	while (it != s.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
	string s2 = s;
	string s3 = "xxxxx";
	s2 = s3;
	cout << s2[0] << endl;
	cout << s3 << endl;
	s3.clear();
	cout << s3 << endl;
}

void test2() {
	string s1 = "";
	cout << s1.size() << endl;
	s1.push_back('c');
	s1.push_back('c');
	s1.push_back('c');
	s1.push_back('c');
	string s2 = "abcdef";
	s2.push_back('x');
	string s3 = "";
	s3.append("qqqwda");
	cout << s3 << endl;
	cout << s1 << endl;
}

void test3() {
	string s1 = "abdef";
	s1 += "xxxxxxx";
	cout << s1 << endl;
	string s2 = "abcdee";
	string s3 = "abcdef";
	bool res = s2 != s3;
	cout << res << endl;
}

void test4() {
	/*string s1 = "dwafklwan";
	int res = s1.find('f');
	cout << res << endl;
	string s2, s3;
	cin >> s2 >> s3;
	cout << s3 << endl;
	cout << s2 << endl;

	string s3 = "dwadjkwna";
	cout << s3 << endl;
	s3.clear();
	cout << s3 << endl;*/

	string s1, s2;
	cin >> s1 >> s2;
	cout << s2 << endl;
}

void test5() {
	string s = "abcdef";
	s.insert(5, 'c');
	cout << s << endl;
	s.insert(1, "xxxx");
	cout << s << endl;
	string s2 = "abcdefg";
	s2.erase(0, 5);
	cout << s2 << endl;
}

void test6() {
	string s = "abcxxxabc";
	int res = s.find("abc", 7);
	cout << res << endl;
	string s1, s2;
	cin >> s1 >> s2;
	cout << s1 << endl;
	cout << s2 << endl;
}

int main() {
		
	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	test6();

	return 0;
}