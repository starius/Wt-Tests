#include <iostream>
#include <Wt/WApplication>
#include <Wt/WString>
#include <Wt/WTemplate>
#include <Wt/WBreak>

using namespace std;
using namespace Wt;

class WtApplication : public WApplication { public: WtApplication(const WEnvironment& env); };

WtApplication::WtApplication(const WEnvironment& env) : WApplication(env) {
  messageResourceBundle().use(appRoot() + "Localized/main");

  WTemplate* tp = new WTemplate(WString::tr("index"), root());
}

WApplication *createApplication(const WEnvironment& env) { return new WtApplication(env); }

int main(int argc, char **argv) { return WRun(argc, argv, &createApplication); }
