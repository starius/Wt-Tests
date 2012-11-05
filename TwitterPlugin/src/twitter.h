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

#ifndef TWITTER_H_
#define TWITTER_H_
#include <cstdlib>

#include <Wt/Dbo/WtSqlTraits>
#include <Wt/Dbo/Types>
#include <Wt/Dbo/backend/Postgres> 
#include <Wt/Dbo/Dbo>

#include <libtwit/twitcurl.h>

class Twitter;

typedef Wt::Dbo::collection< Wt::Dbo::ptr<Twitter> > Accounts;
  
class Twitter : public  Wt::Dbo::Dbo<Twitter>{
  public:
    Wt::Dbo::Session *Session;
      
    int id;
    Wt::WDate oauth_provider;
    Wt::WString oauth_uid;
    Wt::WString oauth_token;   
    Wt::WString oauth_secret;
    Wt::WString username;
    
    bool getdata();
    
    template<class Action>
    void persist(Action& a)
    {
       Wt::Dbo::field(a, id, "id");
       Wt::Dbo::field(a, oauth_provider, "oauth_provider");
//        Wt::Dbo::field(a, oauth_uid, "oauth_uid");
       Wt::Dbo::field(a, oauth_token, "oauth_token");
       Wt::Dbo::field(a, oauth_secret, "oauth_secret");    
       Wt::Dbo::field(a, username, "username"); 
    }
        
    std::string getRequestToken(){
      return RequestToken;
    }
    
    
    std::string AuthPin;
    std::string *Followers;
    std::string *Tweets;
    
    void RegisterApp();
    
  private:
    int qid;
    std::string RequestToken;
    std::string tmpStr;
    std::string replyMsg;
    std::string myOAuthAccessTokenKey;
    std::string myOAuthAccessTokenSecret;
    twitCurl twitterObj;

};
/*
template<>
struct Wt::Dbo::dbo_traits<Twitter> : public Wt::Dbo::dbo_default_traits {
  static const char *versionField() {
    return 0;
  }
};
*/
#endif