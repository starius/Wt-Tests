// for run execute: tests/run.sh

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
#include <Wt/WWidget>
#include <Wt/WTemplate>
#include <Wt/WMenu>
#include <Wt/WDateTime>
#include <Wt/WText>
#include <Wt/WBreak>

using namespace std;
using namespace Wt;

// *********************************************************************************************************************
/** Create Page Deferred - Class */
template <typename Function>
class DeferredWidget : public Wt::WContainerWidget {
private:
  Function f_;

  void load() {
    Wt::WContainerWidget::load();

    if(count() == 0)
      addWidget(f_());
  }

public:
  DeferredWidget(Function f) : f_(f) { }
};

/** Create Page Deferred - Template */
template <typename Function>
DeferredWidget<Function> *deferCreate(Function f) {
  return new DeferredWidget<Function>(f);
}

// *********************************************************************************************************************

/** 2 others classes: Home & About */
class Home : public Wt::WContainerWidget {
private:
public:
  Home();
  void upTime();
};

Home::Home() {
  cout << "Home Created" << endl;
  upTime();
}

void Home::upTime() {
  this->clear();
  this->addWidget(new WText("<b>Home</b> Click<br>&nbsp;</br>"));
  this->addWidget(new WText(WDateTime::currentDateTime().toString()));
}

// *****************************************************************************

class About : public Wt::WContainerWidget {
private:
public:
  About();
  void upTime();
};

About::About() {
  cout << "About Created" << endl;
  upTime();
}

void About::upTime() {
  this->clear();
  this->addWidget(new WText("<b>About</b> Click<br>&nbsp;</br>"));
  this->addWidget(new WText(WDateTime::currentDateTime().toString()));
}

// *********************************************************************************************************************

/** Wt Class */
class WtApplication : public WApplication {
public:
  WtApplication(const WEnvironment& env);
  Wt::Signal<WMenuItem *>& selected();

private:
  Home* home_;
  About* about_;
  Wt::WWidget* menuHome();
  Wt::WWidget* menuAbout();
  Wt::WTemplate* staticPage(std::string str);
  Wt::Signal<WMenuItem *> selected_;

  void mnItemSelected();
};

/** Wt Session Start */
WtApplication::WtApplication(const WEnvironment& env) : WApplication(env), selected_(this), home_(NULL), about_(NULL) {
  //WtApplication *app = (WtApplication*)WApplication::instance();
  //app->internalPathChanged().connect(this, &WtApplication::appInternalPathChanged);

  new WText("<b>Updating DeferredWidget</b><br>&nbsp;</br>", root());
  new WText("How to refresh (update time) pages Home & About with each new click?", root());

  WStackedWidget* sw = new WStackedWidget();
  WMenu* mn = new WMenu(sw, Wt::Horizontal, 0);

  mn->setRenderAsList(true);
  mn->setInternalPathEnabled();
  mn->itemSelected().connect(this, &WtApplication::mnItemSelected);

  mn->addItem("Home Page", deferCreate(boost::bind(&WtApplication::menuHome, this)))->setPathComponent("Home");
  mn->addItem("About This Site", deferCreate(boost::bind(&WtApplication::menuAbout, this)))->setPathComponent("About");

  root()->addWidget(mn);
  root()->addWidget(sw);
}

WWidget* WtApplication::menuHome() {
  home_ = new Home();
  cout << "Home Instantiate" << endl;
  return home_;
}

WWidget* WtApplication::menuAbout() {
  about_ = new About();
  cout << "About Instantiate" << endl;
  return about_;
}

Signal<WMenuItem *>& WtApplication::selected() {
  cout << "Signal Emit" << endl;
  return selected_;
}

void WtApplication::mnItemSelected() {
  //selected_.emit();

  if (home_ != NULL) {
    home_->upTime();
    cout << "Home Executed" << endl;
  }

  if (about_ != NULL) {
    about_->upTime();
    cout << "About Executed" << endl;
  }
}

// *********************************************************************************************************************

WApplication* createApplication(const WEnvironment& env) {
  return new WtApplication(env);
}

int main(int argc, char** argv) {
  return WRun(argc, argv, &createApplication);
}
