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

#include <cstring>

#include <curl/curl.h>
#include "twitter.h"

bool Twitter::getdata(){
  try {
    Session->createTables();
  }catch (...) { }
  Wt::Dbo::Transaction transaction(*Session);
  Accounts accounts;
  accounts = Session->find<Twitter>();
  for (Accounts::const_iterator i = accounts.begin(); i != accounts.end(); ++i){
    twitterObj.getOAuth().setConsumerKey( std::string( "" ) );
    twitterObj.getOAuth().setConsumerSecret( std::string( "" ) );
    myOAuthAccessTokenKey =  (*i)->oauth_token.toUTF8();
    myOAuthAccessTokenSecret = (*i)->oauth_secret.toUTF8();
    qid = (*i)->id;
    if( myOAuthAccessTokenKey.size() && myOAuthAccessTokenSecret.size() ){
        twitterObj.getOAuth().setOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.getOAuth().setOAuthTokenSecret( myOAuthAccessTokenSecret );
        bool err;
        err = twitterObj.timelineUserGet();
        if(err==false){
          std::cerr << "could not get user tweets" << std::endl;
        }else{
           twitterObj.getLastWebResponse(*Tweets);
        }
        err = twitterObj.followersGet();
        if(err==false){
          std::cerr << "could not get Followers" << std::endl;
        }else{
          twitterObj.getLastWebResponse(*Followers);
        }
    }else{     
      twitterObj.oAuthRequestToken(RequestToken);
      return false;    
    } 
  }
  transaction.commit();  
  return true;
}

void Twitter::RegisterApp(){
  std::cout << "Qid: " << qid << std::endl;
  twitterObj.getOAuth().setOAuthPin(AuthPin);
  twitterObj.oAuthAccessToken();
  twitterObj.getOAuth().getOAuthTokenKey( myOAuthAccessTokenKey );
  twitterObj.getOAuth().getOAuthTokenSecret( myOAuthAccessTokenSecret );  
  Wt::Dbo::Transaction transaction(*Session);
  Wt::Dbo::ptr<Twitter> auth = Session->find<Twitter>().where("id = ?").bind(qid);
  auth.modify()->oauth_token = myOAuthAccessTokenKey;
  auth.modify()->oauth_secret = myOAuthAccessTokenSecret;
  transaction.commit();  
}