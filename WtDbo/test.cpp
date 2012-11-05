/**
	Save in:	/tmp/wt/
						$ cd /tmp/wt/
	Compile:	$ cmake -DEXAMPLES_CONNECTOR="wt;wthttp"
						$ make
	Run: 			$ ./test.wt --docroot . --http-addr 0.0.0.0 --http-port 10100
	
	Create PostgreSQL db:
		Connect:			$ sudo -u postgres psql postgres
		Create User, DB and set Privileges:
			postgres=# create role foo encrypted password 'bar' login createdb;
			CREATE ROLE
			postgres=# create database test with owner foo encoding 'unicode' template template1;
			CREATE DATABASE
			postgres=# grant all privileges on database test to foo;
			GRANT
*/

#define POSTGRES // POSTGRES / SQLITE

#include <string>
//#include <boost/lexical_cast.hpp>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/Dbo/Dbo>
#include <Wt/WDateTime>
#include <Wt/WText>
#include <Wt/WBreak>

#ifdef POSTGRES
#include <Wt/Dbo/backend/Postgres>
#endif
#ifdef SQLITE
#include <Wt/Dbo/backend/Sqlite3>
#endif

using namespace std;
using namespace Wt;
using namespace Wt::Dbo;

class A;
class B;
typedef ptr<A> ptrA;
typedef ptr<B> ptrB;
typedef collection< ptrA > colA;
typedef collection< ptrB > colB;

class A {
public:
	//Wt::WDateTime date;
	std::string date;
  colB Bs;

  template<class Action>
  void persist(Action& a) {
		field(a, date, "dat");
    hasMany(a, Bs, ManyToMany, "a_b");
  }
};

class B {
public:
  std::string date;
  colA As;

  template<class Action>
  void persist(Action& a) {
    field(a, date, "dat");
    hasMany(a, As, ManyToMany, "a_b");
  }
};

/*
class AB {
public:
  int b_id;
  int a_id;

  template<class Action>
  void persist(Action& a) {
    field(a, b_id, "b_id");
		field(a, a_id, "a_id");
  }
};
*/

class WtApplication : public WApplication {
	private:
#ifdef POSTGRES
    backend::Postgres connection_;
#endif
#ifdef SQLITE
    backend::Sqlite3 connection_;
#endif
		Session session_;
		
		void msg(string str);
		void populate();
		void lists();
		void listAB(int id);

	public:
		WtApplication(const WEnvironment& env);
};

WtApplication::WtApplication(const WEnvironment& env) : WApplication(env),
#ifdef POSTGRES
		connection_("host=127.0.0.1 user=foo password=bar port=5432 dbname=test")
#endif
#ifdef SQLITE
		connection_("test.db")
#endif
{
	msg("<b>N-M Relationship</b>");

	connection_.setProperty("show-queries", "true");
	session_.setConnection(connection_);
	session_.mapClass<A>("a");
	session_.mapClass<B>("b");
	//session_.mapClass<AB>("a_b");
	try { Transaction tt(session_);
		session_.createTables();
		tt.commit();
	} catch (Exception &e) { cerr << "Exception: " << e.what() << endl; }
	populate();
	lists();
	listAB(1);
}

void WtApplication::msg(string str) {
	root()->addWidget(new WText(str));
	root()->addWidget(new WBreak());
}

void WtApplication::populate() {
	msg("<b>Populate</b>");
	
	ptrA a;
	
	{ A *tuple = new A();
		//tuple->date = WDateTime::currentDateTime();
		tuple->date = "A: " + WDateTime::currentDateTime().toString("dd/MM/yy HH:mm:ss").toUTF8();
	  
    try { Transaction tt(session_);
			a = session_.add(tuple);
			tt.commit();
		} catch (...) {}
  }

  { B *tuple = new B();
		tuple->date = "B: " + WDateTime::currentDateTime().toString("dd/MM/yy HH:mm:ss").toUTF8();
		
    try { Transaction tt(session_);
			ptrB b = session_.add(tuple);
			a.modify()->Bs.insert(b);
			tt.commit();
		} catch (...) {}
  }
}

void WtApplication::lists() {
	msg("<b>List All As:</b>");

	try {
		Transaction tt(session_);
		colA collect = session_.find<A>();
		
		for (colA::const_iterator i = collect.begin(); i != collect.end(); ++i)
			msg((*i)->date);
		
		tt.commit();
	} catch (...) {}
	
	msg("<b>List All Bs:</b>");

	try {
		Transaction tt(session_);
		colB collect = session_.find<B>();
		
		for (colB::const_iterator i = collect.begin(); i != collect.end(); ++i)
			msg((*i)->date);
		
		tt.commit();
	} catch (...) {}
}

void WtApplication::listAB(int id) {
	msg("<b>List Bs From A: " + boost::lexical_cast<string>(id) + "</b>");

	try {
		Transaction tt(session_);
		ptrA a = session_.find<A>().where("id = ?").bind(id);
		colB collect = a->Bs;
		
		for (colB::const_iterator i = collect.begin(); i != collect.end(); ++i)
			msg((*i)->date);
		
		tt.commit();
	} catch (...) {}
	
	msg("<b>List As From B: " + boost::lexical_cast<string>(id) + "</b>");

	try {
		Transaction tt(session_);
		ptrB b = session_.find<B>().where("id = ?").bind(id);
		colA collect = b->As;
		
		for (colA::const_iterator i = collect.begin(); i != collect.end(); ++i)
			msg((*i)->date);
		
		tt.commit();
	} catch (...) {}
}

WApplication *createApplication(const WEnvironment& env) { return new WtApplication(env); }

int main(int argc, char **argv) { return WRun(argc, argv, &createApplication); }
