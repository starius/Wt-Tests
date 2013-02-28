#include <iostream>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WTemplate>
#include <Wt/WText>
#include <Wt/WString>

using namespace std;
using namespace Wt;

class WtApplication : public WApplication { public: WtApplication(const WEnvironment& env); };

WtApplication::WtApplication(const WEnvironment& env) : WApplication(env) {
  messageResourceBundle().use(appRoot() + "Localized/main");

  instance()->require("http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML");

  //WTemplate* tp = new WTemplate(WString::tr("index"), root());

  WText* t = new WText(WString::tr("index"));
  t->setTextFormat(Wt::XHTMLUnsafeText);
  root()->addWidget(t);
}

WApplication *createApplication(const WEnvironment& env) { return new WtApplication(env); }

int main(int argc, char **argv) { return WRun(argc, argv, &createApplication); }
