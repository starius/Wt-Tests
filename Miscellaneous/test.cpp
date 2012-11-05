/**
	Wt Test
	Simulating some error.

	Save in:	/tmp/wt/
						$ cd /tmp/wt/
	Compile:	$ cmake -DEXAMPLES_CONNECTOR="wt;wthttp"
						$ make
	Run: 			$ ./test.wt --docroot . --http-addr 0.0.0.0 --http-port 10100
*/

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WDateTime>

using namespace std;
using namespace Wt;

class WtApplication : public WApplication {
	private:
		void ConvertDate();
	public:
		WtApplication(const WEnvironment& env);
};

void WtApplication::ConvertDate() {
	// http://www.geekzilla.co.uk/View00FF7904-B510-468C-A2C8-F859AA20581F.htm
	
	WString date = WDateTime::fromString("6/14/2011 4:07pm",	WString::fromUTF8("M/dd/yyyy h:mmAP")).toString();
	new WText(date, root()); new WBreak(root());
	
	date = WDateTime::fromString("Wed Jun 29 13:55:14 2011",	WString::fromUTF8("ddd MMM dd HH:mm:ss yyyy")).toString();
	new WText(date, root()); new WBreak(root());
	
	date = WDateTime::fromString("Wed Jun 29 13:55:14 +0000 2011",	WString::fromUTF8("ddd MMM dd HH:mm:ss +0000 yyyy")).toString();
	new WText(date, root()); new WBreak(root());
	
	date = WDateTime::fromString("Wed Jun 29 13:55:14 +0000 2011",	WString::fromUTF8("ddd MMM dd HH:mm:ss zzz yyyy")).toString();
	new WText(date, root()); new WBreak(root());
}

WtApplication::WtApplication(const WEnvironment& env) : WApplication(env) {
	new WText("Miscellaneous", root()); new WBreak(root());
	ConvertDate(); new WBreak(root());
	
}

WApplication *createApplication(const WEnvironment& env) { return new WtApplication(env); }

int main(int argc, char **argv) { return WRun(argc, argv, &createApplication); }
