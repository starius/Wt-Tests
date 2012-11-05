/*
   Copyright 2010 Jan Koester

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WStackedWidget>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WWidget> 
#include <Wt/WComboBox> 
#include <Wt/WTextArea>
#include <Wt/WCssStyleSheet>
#include <Wt/WColor>
#include <Wt/WHBoxLayout> 
#include <Wt/WLength>
#include <Wt/WJavaScript>
#include <Wt/WImage>
#include <Wt/WLogger>

#include <tuxlibs/navbar.h>

#include "twitter.h"
#include "webui.h"
#include "xmlparse.h"

TuxistApp::TuxistApp(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
   //will be replaced agqainst multi db support
  db_con.setProperty("show-queries", "true");
  Session = new Wt::Dbo::Session;
  Session->setConnection(db_con);
  Session->mapClass<Navbar>("navbar");
  Session->mapClass<Twitter>("twitter");

    
  setTitle("Twitter @ Tuxist.de");               // application title
  useStyleSheet("style/main.css");
  Navbar navbar;
  navbar.Session=Session;
  navbar.getNavbar(root());
  twitter.Session=Session;
  twitter.Tweets = &tweets;
  twitter.Followers = &followers;
  if(twitter.getdata()==false){
    root()->addWidget(new Wt::WText("Please visit this link in web browser and authorize this application: <a href=\""+ twitter.getRequestToken()+"\">Token</a> "));
    root()->addWidget(new Wt::WText("Enter the PIN provided by twitter: " ));
    PinLine = new Wt::WLineEdit(root());
    PinLine->enterPressed().connect(SLOT(this, TuxistApp::RegisterApp));
  }else{
//     root()->addWidget(new Wt::WText(tweets));
//     root()->addWidget(new Wt::WText(followers));
    Xmlparse xmlparse;
    root()->addWidget(xmlparse.getTweets(tweets));
    Wt::WContainerWidget *twitter_right = new Wt::WContainerWidget(); 
    twitter_right->setStyleClass("twitter_right"); 
    addAutoJavaScript("document.getElementsByClassName('twitter_right')[0].style.marginLeft = document.getElementsByClassName('logo')[0].offsetWidth-document.getElementsByClassName('twitter_right')[0].offsetWidth+'px';");   
    twitter_right->addWidget(xmlparse.getFollowers(followers));
    root()->addWidget(twitter_right);
  }
}

void TuxistApp::RegisterApp(){
  twitter.AuthPin=PinLine->text().toUTF8();  
  twitter.RegisterApp();
}

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
    return new TuxistApp(env);
}

int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}