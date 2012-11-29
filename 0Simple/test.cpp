/**
  Wt Test
  Simulate some error.

  Paste code:   http://paste.ubuntu.com/
  Paste image:  http://imagebin.org/

  Folder:   $ mkdir /tmp/wt/; cd /tmp/wt/
  Git:    $ git clone git://github.com/JohnRobson/Wt-Tests.git  [or]  git clone https://github.com/JohnRobson/Wt-Tests.git
        $ cd tests/WTextArea/
  Compile:  $ cmake -DEXAMPLES_CONNECTOR="wt;wthttp"
        $ make
  Run:    $ ./test.wt --docroot . --http-addr 0.0.0.0 --http-port 10100
*/

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WBreak>

using namespace std;
using namespace Wt;

class WtApplication : public WApplication { public: WtApplication(const WEnvironment& env); };

WtApplication::WtApplication(const WEnvironment& env) : WApplication(env) {
	new WText("Hello World", root()); new WBreak(root());
}

WApplication *createApplication(const WEnvironment& env) { return new WtApplication(env); }

int main(int argc, char **argv) { return WRun(argc, argv, &createApplication); }
