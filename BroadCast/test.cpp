#include <Wt/WApplication>
#include <Wt/WText>
#include <Wt/WServer>
#include <boost/thread.hpp>

using namespace std;

class Client { };

//A (singleton) server class which would protect and manage a shared resource. In our example we take a simple counter as data.
class Server {
public:
	Server() : counter_(0), stop_(false) {
		thread_ = boost::thread(boost::bind(&Server::run, this));
	}

	~Server() {
		stop_ = true;
		thread_.join();
	}

	void connect(Client *client, const boost::function<void() >& function) {
		boost::mutex::scoped_lock lock(mutex_);

		connections_.push_back
		(Connection(Wt::WApplication::instance()->sessionId(), client, function));
	}

	void disconnect(Client *client) {
		boost::mutex::scoped_lock lock(mutex_);

		for (unsigned i = 0; i < connections_.size(); ++i) {
			if (connections_[i].client == client) {
				connections_.erase(connections_.begin() + i);
				return;
			}
		}

		assert(false);
	}

	int getCount() const {
		boost::mutex::scoped_lock lock(mutex_);
		return counter_;
	}

private:
	struct Connection {
		Connection(const string& id, Client *c, const boost::function<void() >& f) : sessionId(id), client(c), function(f) { }

		string sessionId;
		Client *client;
		boost::function<void() > function;
	};

	mutable boost::mutex mutex_;
	boost::thread thread_;
	int counter_;
	bool stop_;

	vector<Connection> connections_;

	void run();
};

Server server;

// A widget which displays the server data, keeping itself up-to-date using server push.
class ClientWidget : public Wt::WText, public Client {
public:
	ClientWidget(Wt::WContainerWidget *parent = 0) : Wt::WText(parent) {
		server.connect(this, boost::bind(&ClientWidget::updateData, this));
		Wt::WApplication::instance()->enableUpdates(true);
		updateData();
	}

	virtual ~ClientWidget() {
		server.disconnect(this);
		Wt::WApplication::instance()->enableUpdates(false);
	}

private:
	void updateData() {
		setText(Wt::WString("count: {1}").arg(server.getCount()));
		Wt::WApplication::instance()->triggerUpdate();
	}
};

void Server::run() {
	// This method simulates changes to the data that happen in a background thread.
	for (;;) {
		boost::this_thread::sleep(boost::posix_time::seconds(1));

		if (stop_)
			return;

		{
			boost::mutex::scoped_lock lock(mutex_);
			++counter_;

			/* This is where we notify all connected clients. */
			for (unsigned i = 0; i < connections_.size(); ++i) {
				Connection& c = connections_[i];
				Wt::WServer::instance()->post(c.sessionId, c.function);
			}
		}
	}
}

Wt::WApplication *createApplication(const Wt::WEnvironment& env) {
	Wt::WApplication *app = new Wt::WApplication(env);
	app->setCssTheme("");
	new ClientWidget(app->root());
	return app;
}

int main(int argc, char **argv) {
	return WRun(argc, argv, &createApplication);
}
