#include <iostream>
#include <functional>
#include <boost/lexical_cast.hpp>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WTextArea>
#include <Wt/WSelectionBox>

using namespace std;
using namespace Wt;

class WtApplication : public WApplication { public: WtApplication(const WEnvironment& env); };

void sbChanged(Wt::WTextArea* ta, Wt::WSelectionBox* sb) {

  cout << sb->currentIndex() << endl;
  cout << sb->currentText() << endl;

  ta->setText(boost::lexical_cast<string>(sb->currentText()));

}

WtApplication::WtApplication(const WEnvironment& env) : WApplication(env) {
	new WText("WSelectionBox & WTextArea", root()); new WBreak(root());

  // SelectionBox
  WSelectionBox* sb = new WSelectionBox(root());
  sb->addItem("one");
  sb->addItem("two");
  sb->addItem("three");


  // Text Area
  WTextArea* ta = new WTextArea(root());

  sb->activated().connect(std::bind(&sbChanged, ta, sb));

}

WApplication *createApplication(const WEnvironment& env) { return new WtApplication(env); }

int main(int argc, char **argv) { return WRun(argc, argv, &createApplication); }
