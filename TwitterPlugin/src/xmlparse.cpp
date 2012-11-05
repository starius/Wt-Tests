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

#include <iostream>
#include <string>
#include <cstring>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WAnchor>
#include <tinyxml.h>
#include "xmlparse.h" 


#ifndef XML_PARSER_CPP
#define XML_PARSER_CPP

//Wt::WContainerWidget 
Wt::WContainerWidget *Xmlparse::getFollowers(std::string FollowerXml){
  Wt::WContainerWidget *followersWidget = new Wt::WContainerWidget();
  followersWidget->setStyleClass("followers");
  followersWidget->addWidget(new Wt::WText("<h2>Followers</h2>"));
  TiXmlDocument followerxml;
  followerxml.Parse((const char*)FollowerXml.c_str(), 0, TIXML_ENCODING_UTF8);
  TiXmlElement *root = followerxml.RootElement();
  for(TiXmlElement* user = root->FirstChildElement(); user; user = user->NextSiblingElement()) {   
    TiXmlElement* uimg = user->FirstChildElement("profile_image_url")->ToElement();
    TiXmlElement* name = user->FirstChildElement("name")->ToElement();
    TiXmlElement* url = user->FirstChildElement("url");
    if (uimg && name ){
      Wt::WContainerWidget *followerWidget = new Wt::WContainerWidget();
      followerWidget->setList(true);
      followerWidget->setStyleClass("follower");
      Wt::WImage *img = new Wt::WImage(uimg->GetText(), followerWidget);
      if(!url){
        followerWidget->addWidget(new Wt::WText(name->GetText()));
      }else{
        url = url->ToElement();
        Wt::WAnchor *a  = new Wt::WAnchor(url->GetText(), name->GetText(), followerWidget);
      }
      followersWidget->addWidget(followerWidget ); 
    }    

  }
  return followersWidget;
}

Wt::WText *Xmlparse::youtube(std::string url){
  std::size_t start,end;
  std::string yurl = "http://www.youtube.com/watch?v=";
  if (url.rfind(yurl)!=std::string::npos){
    start=yurl.length();
  }
  end = url.find("&");
  if(end==std::string::npos){
     if(url.rfind(yurl)!=std::string::npos)
       end=url.length();
  }

  if(end!= std::string::npos && start!=std::string::npos){
    Wt::WText *uyoutube = new Wt::WText("<iframe title=\"YouTube video player\" width=\"480\" height=\"390\" src=\"http://www.youtube.com/embed/"+url.substr(start,(end-start))+"\" frameborder=\"0\" allowfullscreen></iframe>");
    uyoutube->setTextFormat(Wt::XHTMLUnsafeText);
    return uyoutube;
  }else
    return new Wt::WText(url);
}

Wt::WContainerWidget *Xmlparse::getTweets(std::string TweetsXml){
  Wt::WContainerWidget *tweetsWidget = new Wt::WContainerWidget();
  tweetsWidget->setList(true);
  tweetsWidget->setStyleClass("tweetswidget");  
  TiXmlDocument tweetsxml;
  tweetsxml.Parse((const char*)TweetsXml.c_str(), 0, TIXML_ENCODING_UTF8);
  TiXmlElement *root = tweetsxml.RootElement();
  for(TiXmlElement* user = root->FirstChildElement(); user; user = user->NextSiblingElement()) {   
    TiXmlElement* date = user->FirstChildElement("created_at")->ToElement();
    TiXmlElement* text = user->FirstChildElement("text")->ToElement();
    if (date && text){
      Wt::WContainerWidget *tweetWidget = new Wt::WContainerWidget();
      tweetWidget->addWidget(new Wt::WText(date->GetText()));
      tweetWidget->addWidget(new Wt::WBreak());
      Wt::WText *tweettext = youtube(text->GetText());
      tweetWidget->addWidget(tweettext);
      tweetWidget->addWidget(new Wt::WBreak());
      tweetWidget->setStyleClass("tweetswidgets");
      tweetsWidget->addWidget(tweetWidget);
    }    

  }
  return tweetsWidget;
}

#endif
