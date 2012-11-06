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

// *****************************************************************************

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

// *****************************************************************************

class Home : public Wt::WContainerWidget {
private:
public:
  Home();
  void upTime();
};

Home::Home() {
cout << "Home upTime" << endl;
  upTime();
}

void Home::upTime() {
  this->clear();
  this->addWidget(new WText("<b>Home</b> Click<br>&nbsp;</br>"));
  this->addWidget(new WText(WDateTime::currentDateTime().toString()));
}

// *****************************************************************************

class Users : public Wt::WContainerWidget {
public:
  //Users();
  void showPage(int page);
  void upTime();
private:
  WTemplate* Register();
  WTemplate* Login();
};

//Users::Users() { }

void Users::showPage(int page) {
  this->clear();

  switch(page) {
  case 1: {
    Register();
    break;
  }
  case 2: {
    Login();
    break;
  }
  }

  upTime();
}

void Users::upTime() {
  this->addWidget(new WText(WDateTime::currentDateTime().toString()));
}

WTemplate* Users::Register() {
  this->addWidget(new WText("<br>&nbsp;</br><b>Users</b> Register<br>&nbsp;</br>"));
cout << "Users - Register" << endl;
}

WTemplate* Users::Login() {
  this->addWidget(new WText("<br>&nbsp;</br><b>Users</b> Login<br>&nbsp;</br>"));
cout << "Users - Login" << endl;
}

// *****************************************************************************

/** Wt Class */
class WtApplication : public WApplication {
public:
  WtApplication(const WEnvironment& env);

private:
  Home* home_;
  Users* usersRegister_;
  Users* usersLogin_;
  Wt::WWidget* menuHome();
  Wt::WWidget* menuRegister();
  Wt::WWidget* menuLogin();
  Wt::WTemplate* staticPage(std::string str);
  Wt::WMenuItem* home_item_;
  Wt::WMenuItem* users_register_;
  Wt::WMenuItem* users_login_;

  void mnItemSelected(WMenuItem*);
};

// *****************************************************************************

/** Wt Session Start */
WtApplication::WtApplication(const WEnvironment& env) : WApplication(env), home_(NULL), usersRegister_(NULL), usersLogin_(NULL) {
  //WtApplication *app = (WtApplication*)WApplication::instance();
  //app->internalPathChanged().connect(this, &WtApplication::appInternalPathChanged);

  new WText("<b>Updating DeferredWidget</b><br>&nbsp;</br>", root());
  new WText("How to using the same class Users (in two different links), regardless if it is to Login or Register?", root());
  new WText("<br>&nbsp;</br>I created 2 instances for the class Users (1 for register and 1 for login), this is the correct solution?", root());

  WStackedWidget* sw = new WStackedWidget();
  WMenu* mn = new WMenu(sw, Wt::Horizontal, 0);

  mn->setRenderAsList(true);
  mn->setInternalPathEnabled();
  mn->itemSelected().connect(this, &WtApplication::mnItemSelected);

  home_item_ = mn->addItem("Home Page", deferCreate(boost::bind(&WtApplication::menuHome, this)));
  home_item_->setPathComponent("Home");

  users_register_ = mn->addItem("User Register", deferCreate(boost::bind(&WtApplication::menuRegister, this)));
  users_register_->setPathComponent("Register");

  users_login_ = mn->addItem("User Login", deferCreate(boost::bind(&WtApplication::menuLogin, this)));
  users_login_->setPathComponent("Login");

  root()->addWidget(mn);
  root()->addWidget(sw);
}


WWidget* WtApplication::menuHome() {
cout << "Home Instantiate" << endl;
  return home_ = new Home();
}

WWidget* WtApplication::menuRegister() {
cout << "Register Instantiate" << endl;

  if(usersRegister_ == NULL) {
    usersRegister_ = new Users();
  }

  return usersRegister_;
}

WWidget* WtApplication::menuLogin() {
cout << "Login Instantiate" << endl;

  if(usersLogin_ == NULL) {
    usersLogin_ = new Users();
  }

  return usersLogin_;
}

void WtApplication::mnItemSelected(WMenuItem* item) {

  if(item == home_item_) {
cout << "Home Selected" << endl;

    if(home_ != NULL) {
      home_->upTime();
cout << "Home Executed" << endl;
    }
  }

  if(item == users_register_) {
cout << "Register Selected" << endl;

    if(usersRegister_ != NULL) {
      usersRegister_->showPage(1);
cout << "Register Executed" << endl;
    }
  }

  if(item == users_login_) {
cout << "Login Selected" << endl;

    if(usersLogin_ != NULL) {
      usersLogin_->showPage(2);
cout << "Login Executed" << endl;
    }
  }
}

// *****************************************************************************

WApplication* createApplication(const WEnvironment& env) {
  return new WtApplication(env);
}

int main(int argc, char** argv) {
  return WRun(argc, argv, &createApplication);
}
