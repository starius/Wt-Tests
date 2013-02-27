#include <iostream>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WString>
#include <Wt/WTemplate>
#include <Wt/WBreak>

using namespace std;
using namespace Wt;

class WtApplication : public WApplication { public: WtApplication(const WEnvironment& env); };

WtApplication::WtApplication(const WEnvironment& env) : WApplication(env) {
	new WText("HTML", root()); new WBreak(root());

  new WText("Test 1", root());
  new WText("<html><head><title>Title</title></head><body><h1>First</h1><h2>Second</h2><p>Paragraph</p></body></html>", root());

  /* Wt Output - Remove everything inside "<html>" tags.
  <span id="ou8lcal">Test 1</span><div id="ou8lcam"><html></html></div>
  */

  new WText("Test 2", root());
  WText* t = new WText("<html><head><title>Title</title></head><body><h1>First</h1><h2>Second</h2><p>Paragraph</p></body></html>", Wt::PlainText);
  root()->addWidget(t);

  /* Wt Output - Translate everything.
  <span id="ou8lcan">Test 2</span><span id="ou8lcao">&lt;html&gt;&lt;head&gt;&lt;title&gt;Title&lt;/title&gt;&lt;/head&gt;&lt;body&gt;&lt;h1&gt;First&lt;/h1&gt;&lt;h2&gt;Second&lt;/h2&gt;&lt;p&gt;Paragraph&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</span>
  */

  new WText("Test 3", root()); // from: http://www.w3schools.com/html/
  new WText("<!DOCTYPE html><html><body><h1>My First Heading</h1><p>My first paragraph.</p></body></html>", root());

  /* Wt Output - Same Test1 "<html>(removed)</html>"
  <span id="ou8lcap">Test 3</span><div id="ou8lcaq"><html></html></div>
  */

  new WText("Test 4", root());
  new WText("<h1>My First Heading</h1><p>My first paragraph.</p>", root());

  /* Wt Output - this is OK
  <span id="ou8lcar">Test 4</span><div id="ou8lcas"><h1>My First Heading</h1><p>My first paragraph.</p></div>
  */

  new WText("Test 5", root());
  new WText("<script type=""text/x-mathjax-config"">  MathJax.Hub.Config({    tex2jax: {inlineMath: [[""$"",""$""],[""\\("",""\\)""]]}  });</script><script type=""text/javascript"" src=""http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML""></script><p>When $a \ne 0$, there are two solutions to \(ax^2 + bx + c = 0\) and they are$$x = {-b \pm \sqrt{b^2-4ac} \over 2a}.$$</p>", root());

  /* Wt Output - Translate "<" to "&lt;" and ">" to "&gt;"
  <span id="ou8lcat">Test 5</span><span id="ou8lcau">&lt;script type=text/x-mathjax-config&gt;  MathJax.Hub.Config({    tex2jax: {inlineMath: [[$,$],[\(,\)]]}  });&lt;/script&gt;&lt;script type=text/javascript src=http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML&gt;&lt;/script&gt;&lt;p&gt;When $a <br />e 0$, there are two solutions to (ax^2 + bx + c = 0) and they are$$x = {-b pm sqrt{b^2-4ac} over 2a}.$$&lt;/p&gt;</span></div>
  */

  new WText("Test 6", root());
  new WTemplate(WString("<html><head><title>Title</title></head><body><h1>First</h1><h2>Second</h2><p>Paragraph</p></body></html>"), root());

  /* Wt Output - Remove everything inside "<html>" tags.
  <span id="ou8lcat">Test 6</span><div id="ol41jru"><html></html></div>
  */

  new WText("END", root());
}

WApplication *createApplication(const WEnvironment& env) { return new WtApplication(env); }

int main(int argc, char **argv) { return WRun(argc, argv, &createApplication); }
