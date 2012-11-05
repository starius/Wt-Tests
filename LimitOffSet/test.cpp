#include <iostream>
#include <string>
#include <exception>

#include "Wt/Dbo/backend/Sqlite3"
#include "Wt/Dbo/Exception"

#include <Wt/WServer>
#include <Wt/WGlobal>
#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WTableView>
#include <Wt/Dbo/Dbo>
#include <Wt/WText>
#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>
#include <Wt/WStringListModel>
#include <Wt/Dbo/Query>
#include <Wt/Dbo/QueryModel>
#include <Wt/Dbo/QueryModel_impl.h>

using namespace Wt;
using namespace std;
using namespace Wt::Dbo;

WApplication *createApplication(const WEnvironment& env);

class Test {
	public:
		std::string col1;
		std::string col2;
		
	public:
		Test() : col1("notSet"), col2("") { }
		Test(const std::string& acol1) : col1(acol1), col2("") { }
		Test(const std::string& acol1, std::string& acol2) : col1(acol1), col2(acol2) { }
		Test(const char *acol1, const char *acol2) : col1(acol1), col2(acol2) { }

		template<class Action>
		void persist(Action& a) {
			field(a, col1, "column1");
			field(a, col2, "column2");
		}
};

class myAppl : public WApplication {
	public:
		myAppl(const WEnvironment& env);

	private:
		backend::Sqlite3 sqlite3;
		Session session;
};

myAppl::myAppl(const Wt::WEnvironment& env) : WApplication(env), sqlite3("test.db") {
	session.setConnection(sqlite3);
	session.mapClass<Test>("test");
	
	try {
		Transaction tt(session);
		session.createTables();
		tt.commit();
	} catch (Exception &e) {
		cerr << "Exception: " << e.what() << endl;
	}

	Transaction transaction(session);
	Test *test1 = new Test("apple","red");
	Test *test2 = new Test("grape","green");
	Test *test3 = new Test("orange","orange");
	Test *test4 = new Test("banana","yellow");
	ptr<Test> test1Ptr = session.add(test1);
	ptr<Test> test2Ptr = session.add(test2);
	ptr<Test> test3Ptr = session.add(test3);
	ptr<Test> test4Ptr = session.add(test4);
	transaction.commit();

	QueryModel< ptr<Test> > *model = new QueryModel< ptr<Test> > ();
	Query< ptr<Test> > dboquery = session.query< ptr<Test> >("select test from test").limit(2);
	model->setQuery(dboquery);
	model->addAllFieldsAsColumns();

	WTableView *view = new WTableView();
	view->resize(800, 400);
	view->setModel(model);
	view->setAlternatingRowColors(true);

	root()->addWidget(new WText("<h1>Table1: Limit does not work through model->setQuery:</h1>"));
	root()->addWidget(view);

	typedef collection< ptr<Test> > Tests;

	Transaction transaction2(session);
	Tests tests = session.query< ptr<Test> >("select test from test").limit(2);
	transaction2.commit();

	std::string table = "<h1>Table2: Limit does work through collection:</h1><table>";
	for (Tests::const_iterator i = tests.begin(); i != tests.end(); ++i)
		table += "<tr><td>"+ (*i)->col1 + "</td><td>" + (*i)->col2 +"</td></tr>";
	table+="</table>";
	root()->addWidget(new WText(table));
}

WApplication *createApplication(const WEnvironment& env) { return new myAppl(env); }

int main(int argc, char **argv) { return WRun(argc, argv, &createApplication); }
