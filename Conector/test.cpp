/**
	Wt Test
	Simulate some error.
	
	Paste code:		http://paste.ubuntu.com/
	Paste image:	http://imagebin.org/

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
#include <Wt/WLineEdit>
#include <Wt/WPushButton>

using namespace Wt;

class WtApplication : public WApplication {
	public:
		WtApplication(const WEnvironment& env);

	private:
		WLineEdit *nameEdit_;
		WText *greeting_;

		void greet();
};

WtApplication::WtApplication(const WEnvironment& env) : WApplication(env) {
	setTitle("Hello world");

	root()->addWidget(new WText("Your name, please ? "));
	nameEdit_ = new WLineEdit(root());
	nameEdit_->setFocus();

	WPushButton *b = new WPushButton("Greet me.", root());
	b->setMargin(5, Left);

	root()->addWidget(new WBreak());

	greeting_ = new WText(root());

	b->clicked().connect(this, &WtApplication::greet);

	nameEdit_->enterPressed().connect(boost::bind(&WtApplication::greet, this));
}

void WtApplication::greet() {
	greeting_->setText("Hello there, " + nameEdit_->text());
}

WApplication *createApplication(const WEnvironment& env) { return new WtApplication(env); }

int main(int argc, char **argv) { return WRun(argc, argv, &createApplication); }
